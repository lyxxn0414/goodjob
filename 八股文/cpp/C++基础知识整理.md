### 

### C++基本用法

#### 一些小点

- CPP中IO被定义为操作符。
- C++是**面向对象**的（模拟人与世界的交互），C语言是**面向过程**的（基于**过程调用**的概念，重点是函数）
- C++是C的**超集**，任何C的程序都能在C++中以**同等开销**编写和运行。

#### 基本数据类型

##### primitive

四种基本类型: int, double, char, float

修饰符：short, long, signed, unsigned

int可以用四种; double 只能用long; char只能用signed/unsigned；float啥也不能用。

double(64位)相对float(32位)精度更高



**typedef**: 取一个别名

##### sizeof

返回变量/数据类型所占字节数。

```cpp
double f = 95.0629;
double *p=&f;
printf("a=%d",sizeof(p));//4or8，取决于寻址位数
```

#### 左值右值

左值：具有存放数据的**空间**

赋值时：先计算右值表达式的值，再转换为左值的类型，再赋值。

#### 常量和只读的区别

常量强调程序运行中不变性，只读代表一种访问权限，在某些操作或上下文中不能被修改。

常量实现：const/constexpr

只读实现：C++中的const成员函数，const&

#### 表达式

##### a++/++a

前增量（++a）：先将变量+1，然后返回变量对应的实体，是**左值**

后增量(a++)：先将变量保存在一个**临时变量**中，再对对应实体+1，再**返回临时变量**。返回的**不是左值，且是原来a的值**，

后增量比前增量多一步，所以一般用前增量做自增。

```cpp
int a=1;
++a=100;
++++++a;
//正确，前增量可用作左值。

int a=1;
a++=100;
a++++;
++a++;
//错误
```

##### \<exp1> ? \<exp2> : \<exp3> （条件运算符）

只计算一个分量。若<exp2> : <exp3>**都为左值**，则该表达式也是左值。

##### \<exp1>,\<exp2>,…,\<expn> （逗号表达式）

从左向右计算，取\<expn>作为逗号表达式的值。

若**\<expn>为左值**，则整个表达式为左值

```cpp
int  a, b, c;
d = (a = 1, b = a+2, c = b+3);
cout <<d <<endl;	//6	
```

##### 字位运算符

```cpp
a|b; //或
a&b; //与
~a; //取反
a^b; //异或
```

异或的特性：与0为本身，与1取反，与自己清0.

##### lambda表达式

定义：

```cpp
//这里按引用捕获a和b
auto add=[&a,&b](){
    return a+b;
};
```

通常和stl中的算法结合使用，例如sort

```cpp
std::vector<Item> items;
sort(items.begin(),items.end(),[](const Item& a, const Item& b){return a.price<b.price;});
```

编译器如何看待lambda表达式：

编译器会将其定义为**一个类**，其中包含一个**'()'的操作符重载**。在调用时生成一个实例化的对象（例如在上述例子中，实例化的对象名为add）。

若包含捕获对象，

若为**按值捕获**：则会在构造函数中将其赋值给**私有成员变量**。且操作符重载是**const函数**

若为按**引用捕获**：同样赋值给私有的**引用成员变量**，但重载**非const**函数。

```cpp
// 模拟编译器的大致翻译结果
class LambdaClass
{
public:
    LambdaClass(int xx, int yy)
    : x(xx), y(yy) {}

    int operator () (int a, int b) const
    {
        return x + y + a + b;
    }

private:
    int x;
    int y;
}
```



#### 语句

##### switch

```cpp
switch(整型表达式){
    case 整形常量:
        cout<<"do something"<<endl;
        break; 
}
```

case后面的值必须为**编译时常量**

case的顺序只做标号，**不会影响执行顺序**（类似表驱动。改进：用表驱动，**空间换时间**）。

#### 函数

##### 两个原则

1.定义不允许嵌套

2.先定义后使用

编译器调用函数时只会**检查参数类型**(包括根据参数决定调用哪个overload的函数)，并**生成每个函数的目标代码和符号（包括函数的符号，全局变量的符号）**。

链接时会解析符号，变成相应的地址。

##### 执行机制

1. 建立被调用函数栈空间
2. 参数传递（值传递，引用传递，指针传递）
3. 保存调用函数状态
4. 控制权交给被调用函数。

##### 函数重载

同名**不同参数**（返回值不同不行）

匹配遵循严格匹配或内部转换，如下例子不会通过编译

![image-20240113223053664](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240113223053664.png)

##### 默认参数

1. 必须在**函数定义**中给出
2. **从右向左**，**不可间断**

```cpp
void f(int,int=2,int=3);
void f(int);
f(2);
//编译器因无法确定调用哪个函数而报错。
```

##### inline（内联函数）

实现：**编译器**为它**创建**一段代码，**函数代码被放入符号表中，在使用时进行替换**

**减少函数调用的开销**，作用域、类型检查、链接规则等和普通函数一致。

适用对象：**频率高**，简单**小段**的代码

目的：提高代码可读性和编译器效率（不用单独生成函数目标代码并链接）

限制：**不能递归**；由编译系统控制

申请内联函数**可能被编译器驳回**：当函数过长/过复杂（包含loop,switch）。**驳回后会生成static函数**在该文件中。

![image-20240113230013958](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240113230013958.png)

#### 程序组织

![image-20240113225646048](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240113225646048.png)

##### 作用域和生命周期

![image-20240113230236072](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240113230236072.png)

程序级作用域和文件级作用域都是全生命周期。

但文件级(**声明了static的变量和函数**)只有本CPP文件能使用。

###### static

作用：在文件中：限制作用域。在类中：不需要实例化，通过该类就能使用变量/函数。可以用作实例间的共享变量。

类的成员函数属于类本身，static成员函数/参数并不受该限制。

![image-20240113232103397](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240113232103397.png)

![image-20240113231650944](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240113231650944.png)

**extern**了a.cpp中的**非static**变量/函数后，b.cpp可以使用它（因为在a.cpp中它们的作用域是全局的）。



#### namespace

**解决全局变量/函数的名冲突**

替代static来约束作用域。

```cpp
namespace L
{
         int   k;
         void f(int);
         …… 
}

using namespace L; //directive
using L::k; //declaration
```

##### 特点

1. 可起别名

   ```cpp
   namespace American_Telephone_and_Telegraph {…… } 
   …….  
   
   namespace ATT = American_Telephone_and_Telegraph
   
   ```

2. 全局作用域用**::**表示。

   ```cpp
   int  a;
   namespace X
   {   int a;
   
        void f()
       {   int a=0;
   
            a++;//函数内定义的a
            X::a++;//X::a
            ::a++;//全局作用域内的a
       }
   }
   ```

3. 开放定义，可以分段定义

   ```cpp
   namespace A
   {   int a;
        …….
   }
   
   …….
   
   namespace A
   {   void f() ;
        …….
   }
   ```

   

4. 可嵌套定义namespace

   ```cpp
   namespace L1
   {   int a;
       
        ……. 
        namespace L2
       {   void f() ;
            …….
        }
   }
   
   ……
   
   L1::L2::f(); 
   
   using namespace L1;
   L2::f();
   ```

   

5. 重载

   ```cpp
   namespace A
   {   void f(char) ;
        ……
   }
   ...
   void f();
   using namespace A;
   
   void g()
   {
      f(‘1’);//可以定位到A::f
   }
   ```



#### 编译预处理

潜伏于环境，**穿透作用域**

#define: 在编译预处理时做替换。

```cpp
#define max(a,b) a>b?a:b

max(1+2,2+3);
//编译器预处理替换为： 1+2>2+3? 1+2:2+3。会出现重复计算。

```

#pregma: 指示编译器完成一些特定的动作。

```cpp
#pragma alloc_text( "textsection", function1, ... )
//命名特别定义的函数驻留的代码段。
```

#### 数据结构

##### 数组(array)

一维：要显式给出大小信息，**sizeof()只会提供静态分配的空间大小**

```cpp
int a[10];
cout<<sizeof(a)<<endl;//40
```

多维：做**参数传递**时**缺省第一维**

```cpp
void f(int A[][3],int n);
int A[4][3];
//等价于如下定义
typedef T1 int[3];
T1 A[4];
```

数组作为参数传递时只有首地址会被传递。（感觉更像引用传递，因为不能改变其指向。）

##### vector

vector本身一般在栈上（包括它的成员如**大小**、**容量**、指向数据的**指针**等），

但**其管理的元素在堆上**，在内部使用**动态内存分配来管理其元素**，这允许它在运行时根据需要调整大小。

当 `vector` 对象被销毁时（例如当它离开其作用域时），它**负责释放其管理的堆内存**。

##### array

和vector很像，不同的是管理的元素在栈上，且是定长数组。

##### struct

对齐：默认向大小最大的元素对齐。

```cpp
struct B
{
    char b;   // 1
    int a;      //4
    short c; //2
};

cout << sizeof(B); //12
```

##### union

多个变量共享同一块存储空间。大小取决于**最大的元素**

```cpp
union  Matrix
{
    struct
    {   double  _a11, _a12, _a13;
        double  _a21, _a22, _a23;
        double  _a31, _a32, _a33;
    };
    double _element[3][3];
};
//两种访问方式:
Matrix m;
m._a11=1.0;
cout<<m._element[0][0]<<endl;
```

##### Union+Struct

做不用类继承的**多态**：

```cpp
enum FIGURE_TYPE  {LINE, RECTANGLE, ELLIPSE};
struct Line			 
{   FIGURE_TYPE  t ;	
    int x1, y1, x2, y2;	                        
 }; 
struct Ellipse
{   FIGURE_TYPE  t; 
     int x, y, r; 
}；
union FIGURE
{	
    FIGURE_TYPE  t; 
	Line             line;	
	Rectangle    rect; 
	Ellipse         ellipse;
};
FIGURE  figures[100];
void main()
{   input( figures, 100 );
    for (int i=0;i<100;i++){
        draw(figures[i]);
    }
} 
void draw(FIGURE  figure)				
{	switch ( figure.t )
	{	case LINE:  	draw_line(figure.line.x1, ……); break;
		case RECTANGLE:   draw_rect(figure.rect.lef, ……); break;
		case ELLIPSE:	draw_ellipse(figure.ellipse.x, ……); break;
	}
}
```

##### 指针

![image-20240122161626160](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240122161626160.png)

###### 基本操作

只能同类型赋值。特例：void* ：只管理地址信息。可以被所有指针类型赋值（作为**公共接口**）

可以+/- 整型

```cpp
int *p;	  
double *q;
p++;       //p的值加4  ( sizeof(int) )
q++;       //q的值加8  ( sizeof(double) ) 
int x;
p = &x + 2;
```

同类型指针可以相减，得到的值是值差/sizeof（基类型）

```cpp
int  a[10];
int *p, *q，offset;
p = &a[0];
q = &a[3];
offset = p - q;	  // offset = 3
```

指针和指针对象

```cpp
int  x=1;  int *p=&x;
cout << p;     //p的值 (x的地址)
cout << *p;   // p所指向元素的值

//char* 为特例
char *p="ABCD";
cout << p;             //p指向的字符串，即: ABCD
cout << *p;           //p指向的字符，即：A
cout << (int *)p   //p的值

```

###### 常量指针

const int *:指向const int的指针。只读权限，**消除函数副作用**。

变量指针(int *)不可指向常量。

```cpp
const  int  c=0;     
int y=1;
const  int *cp;       
int *q;
         
*cp = 1; //error, 常量值不可修改 
cp = &y; //ok,常量指针可以指向变量，但不能改里面的值。    
q = &c;  //error，变量指针不能指向常量。
```

`const_cast` ：将常量转换成非常量。这个操作**移除了 `c` 的常量属性**

```cpp
const int c=128;
int * q = const_cast<int *>(&c);
*q = 111;
cout << " c " << &c << c << endl; //128，编译器在做优化时可能将其视为字面常量
cout << " q " << &q << q << endl;
cout << "*q " << q << *q << endl; //111
```

<img src="C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240122171438572.png" alt="image-20240122171438572" style="zoom:75%;" />

###### 指针常量

int * const p =&x;

必须在定义时初始化。可以修改指向的变量值，但不能指向别的对象

###### 函数指针

用法：

```cpp
double f(int x)  { … }
int g()   { … }
void main(){  
    //定义函数指针：
    double (*fp) (int);
    //等价的定义形式：（typedef的写法和直接定义一个变量的写法相同）
 	// typedef    double (*FP)(int);
	//  FP  fp;
    fp = f;
    // 等价于如下形式：
    fp = &f;
    (*fp)(10); 
    //等价于 fp(10);
     fp = g;  //Error，返回值或参数不一致都无法赋值
}

```

用途：

1. 回调函数（callback）。可以作为参数传给另一个函数，在需要的时候回调该函数
2. 函数表。例如在多态中通过查找虚函数表找到对应的调用函数。
3. 一些库函数会以函数指针作为参数。如std::sort（本质上也是callback）
4. 动态链接到共享库中的函数。
   具体做法：1.加载动态链接库得到库句柄handle 2.通过handle和函数名得到函数指针 3.通过函数指针调用对应函数。（这一步要进行正确的函数指针类型转换） 4.卸载库。
   好处：不需要重启应用的情况下可以修改功能。
   缺点：编译出的不是一整份可执行文件，在运行过程中需要时要将动态库代码加载到内存中。

###### 数组与指针

数组本质上是**指针常量**，其指向不能被修改。

```cpp
int a[12];
*(a++) = 0; //error
```

多维数组：

```cpp
int a[6][2];
int (*q)[2];//表示一个指向大小为2的数组的指针
//等价于typedef int T[2]; T *q;
q=a;//等价于q=&a[0]
*(*(q+i)+j)=1;//等价于a[i][j]
//数组本身就是一个指针，相当于定义了一个指针的指针。
```

多维数组的指针表示法

```cpp
int b[20][10];  // typedef  int   T[10];   T  b[20];

 int *q;
 q = &b[0][0]; //等价于  q = b[0]; 记得要加[0]

```

对数组做**降维/升维**：

```cpp
//降维
int  maximum(int a[], int n)
{		
    ...
}
void main()
{		
    int  A[2][4] = { {68,69,70,71} , {85,86,87,89}};
	  maximum(A[0],2*4);//直接传入地址
}	
//升维
int show(int a[][2][3], int n){}
void main(){
    int A[12];
    show((int (*)[2][3])A, 2);//做强制类型转换
}
```

###### 指针数组

```cpp
char *s1[]={“C++”, “PASCAL”, “FORTRAN”};
```

![image-20240130235220937](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240130235220937.png)

用处：命令行参数

```cpp
int main(int argc, char *argv[], char *env[]);
//argc: 参数个数
//argv: 命令行参数
//env:  环境参数
//Ex:    c:> ping  -t  192.168.0.1
//argc : 3
//argv:  ping / -t / 192.168.0.1
//env：
```



##### 动态变量（new）

###### 和malloc区别

1. new/delete属于C++关键字，malloc/free时C语言库函数。new本身也是基于malloc实现的
2. new: malloc+**构造函数**。更安全。（不仅管理内存，还管理对象的**初始化**和**清理**）
3. new不需要**计算需要内存的大小**，也不需要**强制类型转换**（返回类型是申请对象的指针），而malloc需要手动计算并做强制类型转换（返回值是**void***）
4. new失败**抛出异常**,malloc失败返回NULL，需要手动检查。

```cpp
int *p = new int[10];
int (*p2)[5] = (int (*)[5])p;
```

注意：尽量一个new对应一个delete，防止内存泄漏。

##### 引用

相当于为已有的内存空间取一个别名。

定义引用变量时**必须初始化**

应用：1. 函数参数/返回值

hint: 函数返回值为引用或指针时，**不能返回局部变量**（会被回收）

###### 右值引用和万能引用

都是T&&

区别：右值引用只能绑定到右值上；万能引用可以绑定到左值，右值，const，非const，。。。依赖类型推导,取决于实参的类型。

万能引用：

```
auto&& T=...;
<template class T>
void f(T&& ..)
```

**操作符重载**

```cpp
class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    // 重载 '+' 运算符来实现两个 Point 对象的加法
    // 函数后加const：不会修改非静态成员变量。（所属对象状态21）
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};
```

2.动态变量命名（没太见过）

#### 面向对象

##### 构造函数

1. 自动调用，**不可直接调用**

2. 当类内没有构造函数时，编译器会提供**默认构造函数**。（目的：确保对象被**正确创建和初始化**）

3. 一般定义为public。定义为private时：**限制实例化**。
   ①类内有一个static函数负责实例化一个对象（用于单例模式，工厂模式）

   ```cpp
   class Product {
   private:
       Product() {} // 私有构造函数
   
   public:
       static Product create() {
           return Product();
       }
   };
   
   int main() {
       Product product = Product::create();
   }
   ```

   ②通过类的嵌套类/友元类才能创建它的实例化对象。

```cpp
//先声明后定义
class MyClass;

class FriendClass {
public:
    MyClass createMyClass(); //先定义成员函数，无法在此处做具体实现。因为此时编译器还不知道MyClass的构造函数。
};

class MyClass {
private:
    MyClass() {} // 私有构造函数
    friend class FriendClass; //定义其为自己的友元类
};

//实现成员函数
MyClass FriendClass::createMyClass() {
    return MyClass();
}

int main() {
    FriendClass creator;
    MyClass myClass = creator.createMyClass();
}
```

调用方式

```cpp
class A{   …
public:
	A();
	A(int i);
	A(char *p);
};
A a1=A(1); A a1(1); A a1=1; //调A(int i)，三种形式等价
A a2=A(); A a2; 	//调A()，注意：不能写成：A a2();
A a3=A(“abcd”); A a3(“abcd”); A a3=“abcd”;  //调A(char *)
A a[4]; 	//调用a[0]、a[1]、a[2]、a[3]的A()
A b[5]={ A(), A(1), A("abcd"), 2, "xyz“ };
```

##### 成员初始化表

构造函数的补充。**先于**构造函数体执行。

尽量多使用成员初始化表代替构造函数（**效率更高**）。

类成员的**初始化顺序由它们在类定义中的声明顺序决定**。（目的：减轻编译器负担；减少错误。）

例子：

```cpp
class A{      
    int    x;
	const  int   y;
	int& z;
public:
	A(): y(1),z(x), x(0)  {  x = 100; }
};
```

执行次序：1.x被默认初始化。2.y被初始化为1 3.z被初始化为x的引用，尽管此时x是一个垃圾值。 4.x被赋值为0（z也为0） 5.进入构造函数，x被初始化为100.

##### 析构函数

- 对象消亡时自动调用
- 一般定义为public，也可以定义成private（强制**自主控制**对象存储分配，如果未主动销毁则**编译器会报错**）

```cpp
class A{   
public:
    A();
private：
    ~A();
};
int main()
{    A  aa;//error，main函数结束会尝试析构aa，但无法调用。
};
```

正确做法：

```cpp
//类内定义一个static函数
static void free(A *p) 
       { delete p; }

A::free(p);
```

数组delete写法：delete []a;

##### 拷贝构造函数

- 创建对象时，用一**同类的对象对其初始化**
- **自动调用**

几种调用场景：

```cpp
// 1.直接初始化
A a;
A b=a;
// 2.参数传递
void f(A a){...}
f(b)
// 3.返回值
A f(){...}
A c=f();
```

默认拷贝构造函数的执行：

- **逐个初始化**成员变量为拷贝对象值。
- 对于对象成员，递归调用**拷贝构造函数**。

自定义拷贝构造函数：

- 相当于一个普通的构造函数。对于对象成员，若无指定，调用**默认构造函数**

```cpp
class A
{      int x,y;
    public:
       A() { x = y = 0; }
       void inc() { x++; y++; }
};
class B
{      int z;
       A a;
   public:
       B() { z = 0; }
       B(const B& b) { z = b.z; } //可以将其当成一个特殊的构造函数
 //拷贝赋值运算符
 		B& operator= (B&& b){
            z=b.z;
            a=b.a;
        }
       void inc() { z++; a.inc(); }
};
......
B b1;     //调用B()和A() ,b1.z=b1.a.x=b1.a.y =0
b1.inc();    //b1.z=b1.a.x=b1.a.y =1
B b2(b1);   //调用A(), b2.z=1, b2.a.x=b2.a.y=0
```

需要拷贝构造函数的例子：string。通过拷贝构造函数实现**深拷贝**，**防止悬挂指针**。

```cpp
class string
{   char *p;
public:
	string(char *str) 
     {  p = new char[strlen(str)+1];  
        strcpy(p, str); 
     }
    ~string() { delete[] p; }
}
//deep copy
string::string(const string& s)
{   p = new char[strlen(s.p)+1];
    strcpy(p,  s.p);
}	
string s1="abcd";
string s2=s1;
```

###### 深拷贝和浅拷贝

在对象成员中含有指针时才能体现区别。

深拷贝会为新对象的指针**重新开辟一块空间**，然后进行cpy，而浅拷贝只是赋指针值，在原对象被析构后会产生问题。



##### 移动构造函数

&&: 右值引用。允许一个函数**安全地接管一个临时对象的资源**

std::move函数可以以非常简单的方式**将左值转换为右值引用**。

从一个**右值引用**（rvalue reference）创建新的对象，而无需进行深拷贝（deep copy）

用处：通常是把即将被销毁的对象的**资源转移**到新对象中

```cpp
A (A &&) noexcept; //表示不会抛出异常
```

具体场景：

1. 函数返回一个局部对象（编译器优化时一般会先尝试移动构造函数，如果有）

2. vector扩容时，移动原有的对象
3. 程序员显示调用：std::move

使用例子：

```cpp
class MyClass {
public:
    int* data;

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr; // 将源对象的指针设置为 nullptr，避免析构时的资源释放冲突
    }
    
    //移动赋值运算符，注意返回值是一个引用对象。
    MyClass& operator= (MyClass&& other) noexcept{
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~MyClass() {
        delete data; // 析构函数释放资源
    }
};

int main(){
    MyClass obj1;
    MyClass obj2(std::move(obj1)); //显示调用
}
```

#### 动态对象

new一个对象做了哪些事：

1. 申请对应大小空间
2. 调用对应构造函数
3. 返回对象地址

delete：析构+释放

（一般delete之后最好将对应指针指向NULL）

##### 动态对象数组

```cpp
A* a;
a = new A[100];
delete []a;//[]不能省略。
```

注意：1. delete时不要省略[]

2. A对象必须有**默认构造函数**。

动态2D数组：

```cpp
char **p=new char*[3];
for(int i=0;i<3;i++){
    p[i]=new char[4];
}

//delete
for(int i=0;i<3;i++){
    delete []p[i];
    p[i]=NULL;
}
delete []p;
p=NULL;
```

#### const成员

- **const成员**变量必须在函数**初始化表**中初始化。
- **const对象不能修改其任何成员变量**，且**只能调用const成员函数**
- const成员函数只能修改含mutable成员变量**

```cpp
class MyClass {
public:
    mutable int value; // mutable 允许在 const 函数中被修改
    int commonValue;
    MyClass(int val) : value(val) {}
    void setValue(int val) const { // 注意成员函数也被声明为 const
        value = val;
    }
};

int main() {
    const MyClass obj(10);
    obj.setValue(20); // 成功：mutable 成员可以在 const 对象中调用const函数被修改
    obj.value=20;//失败，即便value为mutable，仍然不允许直接赋值。
    obj.commonValue=20;//失败，const对象不能修改非mutable变量。
}
```

#### static成员

一般用于①类对象之间**共享变量**②可以直接通过类来访问和调用成员

唯一拷贝，遵循类访问控制原则。

static成员函数**只能调用和存取static成员**

例子：单例模式（遵循**谁创建谁归还**原则，设置一个static函数释放instance资源）

```cpp
class  singleton
{	protected:
		 singleton(){}
		 singleton(const singleton &);
	public:
		static singleton * instance() 
		{   return  m_instance == NULL? 
				m_instance = new singleton: m_instance;
		}
 		//static函数释放static资源
		static void destroy()  { delete m_instance; m_instance = NULL; }
	private:
		static singleton * m_instance;
};
singleton * singleton ::m_instance= NULL;

```

#### 友元

目的：让一个类/函数，**访问当前类中的私有成员**

声明时分为友元函数、友元类、友元类成员函数

```cpp
class A
     {   	…
		friend void func();  	//友元函数，该函数可以访问A中私有成员，可以不用提前声明。
		friend class B; 	  	//友元类
		friend void C::f(); 	//友元类成员函数
	};
```

**友元不具备传递性**（朋友的朋友不一定是朋友）

#### 单继承

派生类**可以访问基类的protected成员**，不可访问private成员。

（实际上含有基类的所有成员，只是不可访问）

**只在定义类时说明继承关系，声明时不需要。**

```cpp
//错误声明
class Undergraduated_Student : public Student;
```



##### 友元+继承

儿子的朋友可以访问爸爸的protected。

**但儿子的朋友不一定是爸爸的朋友，爸爸的朋友也不一定是儿子的朋友**

（即友元关系不可继承，爸爸的朋友也不能通过儿子访问爸爸的隐私。）

```cpp
class Base {
public:
    friend void friendFunction(Base& b);
private:
    int basePrivate;
};

class Derived : public Base {
private:
    int derivedPrivate;
};

void attemptAccessDerived(Derived& d) {
    d.derivedPrivate = 20; // 错误：friendFunction 不能访问 Derived 的私有成员
    d.basePrivate = 20; // 错误：即使通过 Derived 实例，也不能直接访问 Base 的私有成员
}
```



##### 派生类对象初始化

1. 基类构造函数（默认执行基类的默认构造函数，**除非在派生类的成员初始化表中指出**）

   ```cpp
   class B: public A
   {   int y;
   public:
      B(int i, int j):A(i) //初始化表中指定基类的构造函数
      {   y = j;  }
   };
   ```

   

2. 派生类成员对象构造函数

3. 派生类构造函数

拷贝构造函数/移动构造函数执行流程是其子例。

析构与之相反。



using A::A 继承A的**所有构造函数**

##### virtual（虚函数）

```cpp
class B: public A{
    ...
}
A a; 	 
B b; 
a=b;//此时对象身份发生变化，无法调用B中的任何成员
B* pb;  A* pa = pb; //指针赋值，对象身份未变
B  b; 	   A &a=b; //引用赋值，对象身份未变
```



不加virtual时，同名函数**不会发生多态**，函数调用的解析是基于参数的静态类型（**编译时类型**）

```cpp
class A {
public:
    void f(){}
};

class B: public A {
public:
    void f(){}
};

void func1(A& a) {
    a.f();
}

void func2(A *pa) {
    pa->f();
}

B b;
func1(b); //A.f()
func2(&b); //A.f()
```



**C++默认是前期绑定**（依据对象的静态类型），动态绑定需要显式指出（virtual）。

类的**静态成员函数**/**内联成员函数**/**构造函数**都不能是虚函数。



*例子:

```cpp
class A
{    public:
	    A() { f();}
		virtual  void f();
	    void g();
		void h() { f(); g(); }
};
class B: public A
{   public:
	    void f(){g()};
	    void g();
};	
B b;  //A::A,A::f(),B::B
A *p=&b; 
p->f();  //B::f ,B::g  
p->g();   //A::g
p->h();	  //A::h,B::f,A::g
```

对于静态绑定函数，在哪个类内调用就调哪个类的版本。



##### 纯虚函数&抽象类

 `virtual void f()=0;`

基类**只提供接口**。派生类**必须重写**该函数的实现。（并不是必须调用）

```cpp
Person* s1 = new Student;
s1->eat();           // calls Student::eat();
s1->Person::eat();    // calls Person::eat();
```

**拥有纯虚函数的类为抽象类，不能被实例化**

应用：跨平台的GUI库；抽象工厂模式。

![image-20240222145453173](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240222145453173.png)

纯虚函数：子类继承父类的接口。

普通虚函数：子类继承父类的接口和缺省实现。

非虚函数：子类继承父类的接口和强制实现。



##### 继承限定词

private:父类的protected/public成员在子类中都变为private

protected：上述变为protected

public：不变。

C++继承默认是private继承。

（一般只用public继承，在设计上只有public继承是有意义的）



##### override/final

override作用：明确声明该派生类**必须重载**基类中的对应虚函数。（后续没有实现会通过编译器报错。）

```cpp
class Base
{
public:
	virtual void fun1() const;
	virtual void fun3() &; //限定符，表示调用该函数的对象类型只能是左值引用。
	void fun4() const;    // is not declared virtual in Base
};

class Derived : public Base
{
public:
	void fun1() const override;  
	void fun3() & override;   
	void fun4() const;   
};
```



final作用：

1. 在类中：禁止其它类继承该类
2. 在虚函数中：禁止一个虚函数被进一步重载

```cpp
class A
{
pulic:
  virtual void func() const;
};
class  B: A
{
pulic:
  void func() const override final; //OK
};
class C: B
{
pulic:
 void func()const; //error, B::func is final
};
```

#### 多继承

定义：

```cpp
class <派生类名>：[<继承方式>] <基类名1>，
			   [<继承方式>] <基类名2>，…
	{ 〈成员表〉}

```

派生类拥有所有基类的成员。

虚基类：派生类拥有虚基类的多个副本。

![image-20240222151933418](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240222151933418.png)

#### struct

与class最大区别：**默认控制方式不同**（struct默认是public，class默认是private。包括成员控制方式和**继承**形式）

struct是**C的数据结构**，C++对其做了扩展，但本质上仍然是数据结构（虽然可以像对象一样使用），class本身就是C++为面向对象而生的。

```cpp
//非法结构体声明
struct Date
{
    int day = 23,
    month = 8,
    year = 1983;
}；
```

区别2，赋值：

```cpp
struct A{
    char c;
	int a;
	double d;
};
A obja = {'a', 12, 3.14};
```

区别3：创建一个新变量/对象

```cpp
//法1
struct A{
    char c;
	int a;
	double d;
};
struct A a;
struct A a_array[10];

//法2
struct A{
    char c;
	int a;
	double d;
} a,a_array[10];

//法3
typedef struct{
    char c;
	int a;
	double d;
} A;
A a;
A a_array[10];
```

上述操作改为class会报错。相当于做了一个**成员初始化表**

若struct拥有构造函数/虚函数（即**表现出对象的特性**），则**不能再用该种方式赋值**。

但普通函数可以视为数据结构的一种算法，因此依然可用{}做赋值。



#### 智能指针

作用：**防止**new出来的对象在指针被销毁后仍然存在在内存中，发生**内存泄漏**

解决方案：分配的**动态内存都交由有生命周期的对象来处理**——智能指针。

可以通过重载->和*来像使用原有指针一样使用智能指针。



##### unique_ptr

排他性的智能指针。即

![在这里插入图片描述](https://img-blog.csdnimg.cn/6b0a0e1ec3984107a1787671c7cad0fa.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NwcF9sZWFybmVy,size_16,color_FFFFFF,t_70#pic_center)

同一个对象不能交给两个智能指针管理。

构造/赋值

```cpp
unique_ptr<Test> t7(new Test);
unique_ptr<Test> t8(new Test);
unique_ptr<int[]> array(new int[5]);
t7 = std::move(t8);	// 必须使用移动语义，结果，t7的内存释放，t8的内存交给t7管理
t7->doSomething();
```



##### shared_ptr

多个智能指针可以共享同一个对象，有一个引用计数记录当前对象被引用的次数。

构造：

```cpp
//1.直接初始化/reset
shared_ptr<Person> sp1(new Person(1)); 

Person *person1 = new Person(1); 
sp1.reset(person1);

//2.通过另一个智能指针来初始化
shared_ptr<Person> sp2(sp1);

//3.通过make_shared
shared_ptr<int> sp3 = make_shared<int>(3);
```



#### 四种cast

##### const_cast

常量转非常量

可以转指针、对象、引用。

##### dynamic_cast

**运行时转换**（其余都是编译时转换）

主要用于**安全的下行转换**（因为会做**类型检查**，但需要根据**运行时信息（在虚函数表中）**，因此要**包含虚函数**）

上行转换和下行转换都安全，但只有**基类指针指向派生类对象**时才能成功。

```cpp
Base* base = new Derived;
Derived* der = dynamic_cast<Derived*>(base);
//基类指针指向派生类对象时能够安全转换

Base *base1 = new Base;
Derived* der1 = dynamic_cast<Derived*> (base1));
//der1=nullptr,基类指针指向的不是派生类对象。
```

引用同上，但会报运行时错误bad_cast（没有空引用）



##### static_cast

编译时转换，不进行运行时类型检查。

和dynamic_cast不同：不会进行运行时类型检查。

因此**向下转换是不安全的**。

用途：

1. 基本类型间的互相转换：枚举类型转整型/浮点，int转float，void*转具体指针(有关联的类型转换)
2. 基类/派生类的互相转换（向下转换可能并不安全）



##### reinterpret_cast

完成任意指针向任意指针的转换，即**复制一份完全相同的二进制**。

用途：需要一套完全不同的解释机制。



### STL

本质上是cpp的模板类

![在这里插入图片描述](https://pic.leetcode-cn.com/1606133610-QUcEKY-file_1606133616622)

#### vector

动态数组，由一个**指针**指向一块**堆区的连续空间**。（连续：确保能快速随机访问）

（vector本身可能在任何位置，取决于它被定义的位置和方式，但容器里的**元素一定在堆上**）

随机读写快，尾部插入/删除可能慢（涉及扩容）

扩容：申请一块更大的区域（+50%/100%），将数据移过去，将原来的空间释放掉。

对比string：string**较短时会直接放在string容器里**，比较长时会触发短字符串优化（SSO），分配元素在堆上。（string一般有一个SSO缓冲区，还要存必要的指针和长度信息）

![img](https://img-blog.csdnimg.cn/e5ba8b04b1b741ad9846701afabc3c18.jpeg)

```cpp

template<typename T>
    class vector
	{
	public:		
        typedef T valueType;
		typedef T* iterator;
    private:
		iterator _start;
		iterator _finish;
		iterator _endOfStorage;
    }


void push_back(const valueType& x) 
		{
			// 增容
			if (_finish == _endOfStorage){
				valueType* tmp = new valueType[newCapacity]();
				size_t sz = size();
			// 如果有数据，需拷贝到新空间
				if (_start){
					memcpy(tmp, _start, sizeof(valueType) * size());
                    //但这一步由于是浅拷贝，可能会导致野指针。
                    //更好的做法是一个个赋值，做深拷贝。
				}
			// 释放旧空间
				delete[] _start;
				_start = tmp;
				_finish = _start + sz;
				_endOfStorage = _start + newCapacity;
			}
			// 尾插
			*_finish = x;
			++_finish;
		}


		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
		}

//vector拷贝
// 传统写法
		vector(const vector<valueType>& obj)
		{
			_start = new valueType[obj.size()];
			_finish = _start + obj.size();
			_endOfStorage = _start + obj.capacity();
 
			//memcpy(_start, obj._start, obj.size() * sizeof(valueType));
			for (size_t i = 0; i < size(); i++)
			{
				_start[i] = obj._start[i];
			}
		}


// 现代写法
		//类模板的成员函数也可以变成函数模板
		vector(const vector<valueType>& obj)
			:_start(nullptr)
			,_finish(nullptr)
			,_endOfStorage(nullptr)
		{
			vector<valueType> tmp(obj.begin(), obj.end());
 
			// “外卖员送饭又倒垃圾的例子”
			swap(tmp);
		}
```





#### list

以双向链表形式组成，每个节点是一个模板struct。

数据按节点形式申请，需要时申请一个新节点（不用连续），删除时释放节点空间。



#### unordered_map

vector+list

#### sort

混合排序。结合了快排，堆排和插入排序。

当数组很小时用插入排序。

否则用快排，当快排的栈到一定阈值时改用堆排（避免On²的最坏情况）。

### 问答

#### 编译过程

##### 具体编译过程

1. 预处理（处理所有#）
2. 编译和优化，生成.s汇编代码
3. 汇编，生成机器指令文件.o（目标文件）
4. 链接，将目标文件连成一个可执行程序的整体(.exe)



##### 动态链接和静态链接

静态：从动态链接库中**拷贝**一份代码，到最终的可执行程序中对应位置。

动态：代码被放到动态链接库/某个共享对象中，程序执行到对应位置时**映射**到相应地址空间。



区别：静态：**空间换时间**，会有多份相同的代码，但运行更快；且如果被链接的对象**修改**后，需要重新编译链接整个程序。

动态：**时间换空间**，节省内存，更新方便。但每次执行都需要链接到对应位置。



##### define和const

阶段：define只涉及编译预处理阶段（做程序中的字符替换）,const既涉及编译，运行阶段也起作用。

安全性：const有类型安全检查

内存占用：const只占一份拷贝，define每遇到一次就会替换一次



##### 编译器优化

1. 常量优化：用常量代替变量
2. 常量折叠：多个变量冗余计算替换成一个计算
3. 复写传播：多个一样的变量变成一个。
4. 





#### 内存分配

##### 内存分配情况

**栈**：是由**编译器**在需要时**自动分配**，不需要时自动清除的变量存储区。通常存放**局部变量**、**函数参数**等。

**堆**/**自由存储区**：是由**new/malloc**分配的内存块，由**程序员**释放（编译器不管），一般一个new与一个delete对应，一个new[]与一个delete[]对应。如果程序员没有释放掉， 资源将由**操作系统**在**程序结束后自动回收**。

**全局/静态存储区**：**全局**变量和**静态**变量被分配到同一块内存中（在C语言中，全局变量又分为初始化的和未初始化的，C++中没有这一区分。）。在**全生命周期**中

**常量存储区**：这是一块特殊存储区，里边存放常量，不允许修改。

**代码区**：存放程序二进制代码



##### 堆和栈的区别

栈：**编译器**管理。需要时分配，不需要时回收。放局部变量和函数参数。**连续**的存储空间。

堆：**程序员**管理。自己申请和释放空间。不释放：会**内存泄漏**。有**内存碎片**的问题。**不连续**的空间。会有一个**空闲的内存链表**，记录空闲的内存地址和大小。

栈上申请空间比堆效率更高。



##### new和malloc区别

1. new/delete属于C++关键字，malloc/free时C语言库函数。new本身也是基于malloc实现的
2. new: malloc+**构造函数**。更安全。（不仅管理内存，还管理对象的**初始化**和清理）
3. new不需要计算需要内存的大小，也不需要强制类型转换（返回类型是申请对象的指针），而malloc需要手动计算并做强制类型转换（返回值是void*）
4. new失败抛出异常,malloc失败返回NULL，需要手动检查。



#### 面向对象

##### struct和class

struct来自C，本质上是一种数据类型，C++扩展其也可以像对象一样使用

和C++作为对象使用相比：默认是public



##### 封装、继承、多态

**封装**：将**具体实现过程和数据**封装成一个函数，只能通过接口进行访问。意义：解耦;使类功能独立;保护类内成员。

**继承**：子类继承父类的特征和行为，复用基类的成员变量和成员函数。基类私有成员可被继承，但是无法被访问。意义：提高了**复用**的效率。

**多态**：分为动态多态（运行时多态，通过虚函数，子类必须重写虚函数）和静态多态（编译期多态，编译器决定执行哪个函数）。

动态多态：子类调用虚函数时，在虚函数表（存储虚函数的指针，每个指针指向调用它的地方）中找对应的函数指针，实现多态。

静态多态：函数重载/运算符重载/重定义（子类实现一个和父类名字一样的函数）

多态优点：代码更灵活。

##### final关键字的作用

放在类的后面表示该类无法被继承，也就是**阻止**了从类的**继承**，放在虚函数后面该**虚函数无法被重写**，表示阻止虚函数的重载

##### 虚函数的实现

和普通函数一样放在代码段。

虚函数表：存放该类中所有虚函数指针（知道该类执行的具体是哪个虚函数）。

每个对象的会包含一个虚函数指针，指向该对象对应的虚函数表。（编译器为有虚函数的类额外添加的）

![这里写图片描述](https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTcxMTE2MjI0NTEwMTUz?x-oss-process=image/format,png)



#### C++特性

##### 面向对象的思想

封装：成员和方法在一起。

继承：创建层次化的模块结构。

多态：**同一个接口可以被不同的对象以不同的方式实现**。分为运行时多态和静态多态

抽象：允许程序员站在更高的角度思考。例如定义接口（纯虚函数）

##### 匿名函数

本质是一个**对象**。在其定义的过程中会创建出一个**栈对象**。通过**重载()符号**实现函数调用的外表。

优点：免去函数的声明和定义。仅在调用函数的时候**才会创建**函数对象，而调用结束后**立即释放**



##### 强/弱类型 动态/静态语言

类型规定了**数据操作的规范性**



C++是**强类型**语言（一个变量一旦确定为某种类型，除非进行强制类型转换，否则永远是这种类型）

强弱类型**区别**：**是否会隐形进行语言类型转变**。

弱类型的例子：

```vbscript
var A=5;
var B="5"
sumA=A+B;//55，会将A转换为字符串型
sumB=A-B;//0，会将B转换为int型
```

强类型相比弱类型更慢（对于上述例子），但更严谨。



动态类型：在**运行时做类型检查**（**不用指定数据类型**，运行时第一次赋值才会**记录数据类型**）。

典型：python,ruby

静态类型：它的数据类型在**编译期间检查**，也就是说在写程序时要**声明**所有变量的**数据类型**。

典型：JAVA,C++/C,C#



##### C和C++

C是面向过程，特点是函数，C++是面向对象，特点是类。

C++扩展了C，支持泛型编程，操作符重载，新增名空间避免冲突。



##### C++和JAVA

指针：JAVA程序员不能使用指针（虚拟机内部有），C++可以用，有内存泄漏风险

多重继承：JAVA不支持类的多重继承，但可以实现多个接口。更安全

全局变量：JAVA是完全面向对象的语言，没有全局变量、全局函数，所有变量和函数都定义在对象里

垃圾回收：JAVAnew的内存不需要由程序员释放，有垃圾回收机制。C++要自己回收。

运行机制：JAVA运行在虚拟机上，和平台无关，但效率不如C++；C++直接编译成对应机器的二进制文件，执行更快，但跨平台需要重新编译。



##### const

修饰变量：不可修改。成员变量必须在初始化表中被初始化

修饰函数：不能修改成员（除非mutable），只能调const成员函数

修饰对象：不能修改成员;只能调用const成员函数。

修饰参数：参数不可修改。

###### const和constexpr

`const`和`constexpr`都用于声明常量

`const`关键字用于**声明任何常量值**，这个值在**编译时不一定需要已知**，但一旦被初始化后，在程序运行期间就不能被改变。`const`可以用于变量、指针、引用以及类的成员函数等。



`constexpr`是C++11引入的关键字，表示变量或函数的值（或返回值）是**常量表达式**，必须在**编译时已知**。

（是**真正的编译时常量**）

- **编译时求值**：`constexpr`保证变量或函数在编译时求值，而`const`变量可能在运行时初始化。
- **上下文使用**：`constexpr`变量或函数可以用在需要**编译时常量的上下文中**，比如数组大小、模板参数、整数常量表达式等，而`const`变量则不行。
- **函数和构造函数**：在C++11及以后的标准中，`constexpr`还可以用于函数和构造函数，表示函数或构造函数可以在编译时执行，前提是所有参数也都是编译时常量。







##### static

在非面向对象中：1.生命周期变了（全） 2.作用域变了（文件级）

面向对象中：每个类只有一份拷贝；static函数只能访问static成员。

##### noexcept

编译器会生成一些额外代码包裹代码，来处理异常，返回错误的堆栈信息等。

noexcept告诉编译器这段代码不会发生异常，减轻编译器负担。

##### std::ref

返回值是referrence_wrapper()，里面包裹一个指针，代替原本会被识别的值类型。它可以隐式地转换成被包裹的值的引用类型。

##### 流运算符为什么不能操作符重载？怎么解决？

重载自由函数。将自由函数声明为类的友元。

##### main函数执行前，还会执行什么代码？

程序启动代码，由编译器执行，初始化执行环境。

初始化全局变量和静态变量（一般是设0）.

初始化常量。

##### #error和#pregma

#error：预处理期间生成一个错误消息，**停止编译**过程。一般是配置错误时用。



##### 为什么类的声明和实现尽量分开

1. 减少编译依赖，提高编译效率。实现改变时，不需要重新编译使用该类的所有文件。
2. 增强封装性。隐藏实现细节，提高可维护性。
3. 提高可读性和可维护性。

##### 在类的内部定义成员函数的函数体会发生什么

编译器自动尝试将其定义为一个内联函数，减少函数调用开销。

##### C++17 的折叠表达式

目的：用于**简化可变参数模板中对参数的处理**

可变参数模板：允许函数或类模板**接受任意数量的模板参数**。（包括各种类型的参数）

C++17前，一般用**递归模板参数**

```cpp
template<typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << ", ";
    print(args...); // 调用自身，参数包中的下一个参数成为first
}
```

折叠表达式例子：

```cpp
template<typename... Args>
auto sum(Args... args) {
    return (... + args); // 使用一元右折叠，即从右向左计算
    // return (args + ...); 一元左折叠
    // return (1+...+args); 带参数的一元右折叠
}
```



#### 指针和引用

##### 函数传递参数的三种方式

值传递：形参是实参的拷贝

指针传递：形参是实参的地址。

引用传递：把引用对象的**地址**放在开辟的栈空间中。对形参的操作可以直接映射到实参上。

##### 指针和引用的区别

1. 指针本身有空间（是一个实体），引用只是一个别名
2. 指针指向对象可变，引用不行。
3. 指针可以为空，引用不行。



都是一种**内存地址**的概念。**指针是一个实体，而引用只是一个别名**。

指针有const和非const的区别，引用没有。



指针传递**本质上是值传递**。如果指针**指向**的对象变了，则无法操作实参。

引用：对形参的任何操作都**直接映射**到实参。



### 设计模式

#### 单例模式

#### 建造者（生成器）

生成的对象有复杂的构建过程/固定顺序。

#### 抽象工厂

#### 原型模式

对对象进行**clone**，然后做出一定的修改。

#### 策略模式

给业务逻辑和具体实现解耦。（例：游戏中选用武器，武器进行具体攻击）

#### 观察者模式

一个目标变化时，通知多个观察者。