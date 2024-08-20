### C++多线程

#### thread

在一个thread对象被定义时就会开始执行。

**没有执行join或detach的线程在程序结束时会引发异常**（thread析构函数调用时会检查该线程是否仍然可连接，能则抛异常）。（避免未定义的行为）

##### 成员函数

void join()：等待该线程结束并清理资源（该线程结束才能继续执行当前线程。阻塞。

bool joinable():是否可join

void detach():与当前线程分离，**彼此独立**执行（失去了该线程的控制权，不再能与它同步）。子线程在**后台执行**。用途：守护线程，做一些后台监视功能。（并不是主线程结束了子线程就也结束，而是转入后台执行）

get_id():获取线程id

```cpp
#include <iostream>
#include <thread>
using namespace std;
void doit() { cout << "World!" << endl; }
int main() {
	// 这里的线程a使用了lambda函数
	thread a([]{
		cout << "Hello, " << flush;
	}), b(doit);
	a.join();
	b.join();
	return 0;
}
//控制台结果可能是'Hello,World!'也可能是'Word!\nHello,'
```



若线程执行的函数带引用：必须包裹一个std::ref。原因：thread传递参数时按右值引用传递。

```cpp
for (int i = 0; i < 100; i++)
		th[i] = thread(changevalue<int>, ref(nums[i]), i+1);
```

##### atomic和mutex

硬件层面支持锁的几种方式：关中断，锁总线，锁缓存行(cache line lock)。



atomic/mutex都用来保证多个线程操作同一变量的安全性。

mutex:只有获得锁后才能进行操作，操作完后释放，将锁**随机递给申请锁失败而阻塞的线程**。

bool try_lock()：尝试上锁，若成功则上锁，返回true;否则返回false



atomic：可以有效避免mutex带来的死锁，且效率比mutex高一些（主要是**不需要阻塞**，也有能用一条指令完成整个操作的原因。）

（**不需要申请锁**就能执行：CPU可以做CAS，实际上CPU执行的cmpxchg也是上了锁的，保证了操作的原子性）

atomic包含的用法：fetch_and_add,fetch_and_sub,store,load

原理：可以汇编成一行代码操作。

几个常用的成员函数：

bool compare_exchange_weak/compare_exchange_strong(T& expected, T& desired)



##### promise

用于获取thread的返回值。放在线程函数的返回值中，**注意一定要是引用参数**

成员变量：void set_value(T/void)：可以将future_status置为ready，同时设置promise的值（若指定为void则不设置promise的值）

```cpp
template<class ... Args> void sum_thread(promise<long long> &val, Args&&... args) {
	val.set_value(sum(args...));
}
int main() {
	promise<long long> sum_value;
	thread get_sum(sum_thread<int, int, int>, ref(sum_value), 1, 10, 100);//注意引用参数要加ref
	cout << sum_value.get_future().get() << endl;
	get_sum.join(); 
	return 0;
}
```



#### async

```cpp
#include <future>
```

相比thread的好处：可以手动选择同步执行/创建新线程异步执行，且方便操作返回值。

最明显区别：async**不一定创建新线程**。

创建异步任务时不一定创建新线程。不容易因为系统资源紧张而让整个系统崩溃。



async本身是函数不是类。

future<T > async(launch policy, Fn&& fn, Args&& ... args); policy:lauch::async或launch::deffered

或future<T> async(Fn&& fn, Args&& ...args);具体执行同步还是异步**视操作系统而定**

```cpp
future<int> f = async(launch::async,sum,a,b);
cout<<f.get()<<endl
```



##### future

成员函数：

T get()：阻塞等待线程结束并返回结果

void wait()：阻塞等待线程执行结束

future_status wait_for(const chrono::durations t)：阻塞等待t时间并返回future状态(future_status::ready或timeout)）（若同步启动：不会阻塞，立即返回deffered（感觉没啥用））

例子：加载画面

```cpp
void f(int){...};
future<void> fut = async(launch::async,f,1);
while(fut.wait_for(chrono::seconds(1))!=future_status::ready){
    cout<<'.'<<flush;
}
cout<<"Finish!"<<endl;
```

#### this_thread

成员函数：

get_id()

void sleep_for(chrono::durations):阻塞一会。

yield:暂时放弃执行机会（可以用在忙等待中提升性能）

#### mutex

通常用lock_unique,lock_guard或scoped_lock（C++ 17）来更加安全地使用（避免拿锁后线程异常退出等情况）

##### lock_guard

创建时阻塞直到拿到锁，销毁时自动放锁。

```cpp
mutex mtx;
lock_guard<mutex> lck(mtx);
```

##### recursive_mutex

同一个线程可以递归加锁，只要释放次数和拿锁次数相同就可以放锁。

**避免嵌套调用造成的死锁**

例子：func1调用func2，二者都在临界区前创建lock_guard<recursive_mtx>，可以正常运行。

##### shared_mutex

配合shared_lock（读锁）和unique_lock（写锁），实现**读写锁**

读时其它线程可读不可写，写时其它线程既不能读也不能写。

```cpp
typedef shared_lock<shared_mutex> r_lock;
typedef unique_lock<shared_mutex> w_lock;
shared_mutex mtx;

void read(){
    r_lock lck(mtx);
    read...
}

void write(){
    w_lock lck(mtx);
    write...
}
```

##### scope_lock

- scope_lock和lock_guard相比，可以简单的理解，在生命周期内，scope_lock**不允许手动加锁和释放锁**，而lock_guard可以。

#### condition_variable

**必须和unique_lock一起配合工作**

条件变量：提供**睡眠/唤醒机制**，避免忙等。

通知：notify_one()：通知被阻塞的一个线程

notify_all()：通知所有

等待：wait(unique_lock):阻塞直到被唤醒

wait(unique_lock,lambda):阻塞直到被唤醒且lambda为真，否则继续阻塞（**避免虚假唤醒问题**）

wait_for(unique_lock,time):阻塞直到被唤醒，或到达指定时间





多线程用法：

```cpp
void wait( std::unique_lock<std::mutex>& lock );
//Predicate是lambda表达式。
template< class Predicate >
void wait( std::unique_lock<std::mutex>& lock, Predicate pred );
//以上二者都被notify_one())或notify_broadcast()唤醒，但是
//第二种方式是唤醒后也要满足Predicate的条件。
//如果不满足条件，继续解锁互斥量，然后让线程处于阻塞或等待状态。
//第二种等价于
while (!pred())
{
    wait(lock);
}
```

示例：

```cpp
std::mutex m;
std::condition_variable cv;
bool ready = false;
void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    //子进程的中wait函数对互斥量进行解锁，同时线程进入阻塞或者等待状态。
    cv.wait(lk, []{return ready;});
 
    // 得到锁
    std::cout << "Worker thread is processing data\n";
 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    //通知其它进程
    cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
 
    data = "Example data";
    // send data to the worker thread
    {
        //主线程堵塞在这里，等待子线程的wait()函数释放互斥量。
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}
```



#### future

成员函数：get(),wait(),wait_for()

通过async或promise创建。（promise可以设置值，future不能）

发送结果时：通过**修改链接到创建者的 std::future 的共享状态**进行。

promise使用过程：通过promise创建的future异步获得结果。

1. 主线程获取值，子线程设置值：

   ```cpp
   void Task(promise<int>& p,int& value){
       p.set_value(value)
   }
   int main(){
       promise<int> p;
       int k=1;
       thread t(Task,ref(p),ref(k));
       cout<< p.get_future.get();
       t.join();
   }
   ```

   

2. 主线程设置值，子线程获取值：

   ```cpp
   void Task(promise<int>& p){
       cout<<p.get_future.get();
   }
   int main(){
       promise<int> p;
       thread t(Task,ref(p));
       p.set_value(1);
       t.join();
   }
   ```

#### package_task

打包一个函数，并存储其返回值（放到自己的future对象里，感觉有点像包了promise的函数）。

```cpp
int Task(int a,int b){
	return a+b;
}
int main(){
    package_task<int(int,int)> t(Task);
	t(1,2);
	cout<<t.get_future().get()<<endl;
}
```

也可以用**bind**直接指定执行函数的参数：

bind：返回一个std::function

```cpp
int Task(int a,int b){
	return a+b;
}
int main(){
    package_task<int()> t(bind(Task,1,2);
	t();
	cout<<t.get_future().get()<<endl;//future<int> f = t.get_future();
}
```



#### shared_future

future只能get一次，shared_future可以get多次。

`std::shared_future` 的多个副本可以并发地等待异步操作完成，并且可以**独立地多次获取结果**。



#### semaphore

C++20起，可以用semaphore做线程间通信。

此前只支持进程用信号量：需要创建一个信号量文件，并获取它的句柄。通过操作该句柄进行信号量通信。

```cpp
#include<semaphore>
counting_semaphore<3> c_sem(0); //信号量最大值为1，初始值为0
csem.release(2);//释放两个信号量
csem.acquire();//获取一个信号量
csem.try_acquire();//尝试获取一个信号量，成功则获取并返回true，否则返回false。
```



### 生产者消费者

#### 用lock_unique

```cpp
queue<int> products;
int size;
mutex mtx;
void produce(){
    while(true){
        lock_unique<mutex> lck(mtx);
        if(products.size()<size){
            products.push(...);
        }
        else{
            lck.unlock();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}
void consume(){
    while(true){
        lock_unique<mutex> lck(mtx);
        if(products.size()>0){
            t=products.front();
            products.pop();
        }
        else{
            lck.unlock();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}
```

#### 用condition_variable

```cpp
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

std::queue<int> products;
int size = 10; // 假设队列大小为10
std::mutex mtx;
std::condition_variable cv_products;
std::condition_variable cv_empty;

void produce(){
    while(true){
        std::unique_lock<std::mutex> lck(mtx);
        if(products.size() < size){
            int product = ...; 
            products.push(product);
            cv_products.notify_one();
        }
        else{
            cv_empty.wait(lck, [&]{ return products.size() < size; });
        }
    }
}

void consume(){
    while(true){
        std::unique_lock<std::mutex> lck(mtx);
        if(!products.empty()){
            int t = products.front();
            products.pop();
            // 对消费的产品 `t` 进行处理，例如输出
            std::cout << "Consumed: " << t << std::endl;
            cv_empty.notify_one();
        }
        else{
            cv_products.wait(lck, [&]{ return !products.empty(); });
        }
    }
}
```



### 多线程基础知识

#### 死锁

进程/线程间**资源竞争**而分别占用对方的资源，发生**永久等待**

##### 四个必要条件

1. 互斥：资源独占，一个资源任意时刻只能给一个进程
2. 不可剥夺：进程使用完毕资源前，资源不可被剥夺
3. 请求和保持：申请新资源时，仍然占用旧资源
4. 循环等待：进程间互相等待，形成一个循环队列。

##### 检测

线程长时间未执行完成，则检查它们各自被卡住的锁的持有对象，构建图，判断是否出现死锁。

##### 解决方法

预防：

1. 一次性申请所有所需资源。只要有一个资源不可得，则都不能申请（破坏请求保持）
2. 超时放弃（破坏不可剥夺）
3. 给资源编号，必须按顺序请求资源（破坏循环等待）

解决：

检测到死锁后直接break掉一个。（超时放弃）

银行家算法：在申请资源前判断该申请会不会让系统不安全。

