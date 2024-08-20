##### **获取输入**

scanf("%d",&a)

**内置函数**

accumulate(v.begin(),v.end(),0);

##### vector

重置vector大小：v.resize()

初始化：vector<int> v(n,0);

push_back()

pop_back()

sort：

sort(v.begin(),v.end());

反向排序：sort(vec.rbegin(), vec.rend());

v.size().(获取字符串长度使用length)

**自定义sort**： 

```c++
//若为true,则a在b前面。
 bool comp(const student &a, const student &b){
     return a.score < b.score;
 }
//类内：
static bool cmp(const vector<int>& a,const vector<int>& b){
        if(a[0]<b[0]) return true;
        else if(a[0]==b[0] && a[1]<b[1]) return true;
        return false;
};
sort(v.begin(),v.end(),Solution::comp);
```

sort(v.begin(),v.end(),comp);

erase(v.begin()+i)

erase(v.begin()+i,v.begin()+j)

find:find(v.begin(),v.end(),findNum)     返回迭代器。如果是end则说明没找到。

at方法跟数组一样用[]就好

合并两个vector：vector1.insert(vector1.end(),vector2.begin(),vector2.end());

swap(v[i],v[j])

v.insert(iterator,value)

copy：copy(vector1.begin(),vector1.end(),vector2.begin())：把vector1的内容复制到vector2开头的位置

//清空数组并回收空间

*vecInt.swap(vector<int>()) ;* 



拷贝：auto ...=...

##### queue

队列，FIFO，用法和vector几乎一样

```cpp
myqueue5.push(45);
myqueue5.pop(); // 无返回值，出队了一个55
int b2 = myqueue4.back(); // 66
myqueue4.back() = 33; // 给末尾元素66赋值为33
myqueue3.front() = 88; // 给头元素77赋值为88
bags.swap(teeth); //交换
```

##### 字符串

获取size：对于string：s.length()或s.size()；对于char[]:strlen(s)

at获取字符，substr(1):从第一个字符到最末

substr(1,5):从第一个字符起的五个字符组成的字符串

查找子串：s.find(subs),返回值为下标。不存在：返回string::npos

转大写/小写：头文件: string, algorithm    

 transform(str.begin(),str.end(),str.begin(),tolower);

字符串拼接： 

```cpp
string str3 =str1+str2；
char* str1 = "Hello";
char*str2 = "World";
char str3[20];
strcpy(str3, str1);
strcat(str3, str2);
```

字符串是否以某个字符串开头

```cpp
string s = "hello world"
s.startswith("h")>>true

```

查找给定字符是否在某个集合中

```c++
#include<algorithm>
 int points[] = {23, 45, 56, 12, 34, 56};
    int key = 56;

    bool present = std::find(begin(points), end(points), key) != end(points);
```

int转char*:

```c++
#include <charconv>
int number = 1234;
    char num_char[MAX_DIGITS + sizeof(char)];

    std::to_chars(num_char, num_char + MAX_DIGITS, number);
```

string转char数组：

string to int：stoi()

int to string:

to_string(num);



**sstream**

读入：ss<<"first string"<<" "<<val;

输出：ss.str();

清空：ss.str("");

把空格前的字符赋值给str:ss>>str



##### unordered_map

用法很像vector。

erase：参数为键值。

插入直接map[key]=value;

map.count(key)用法同vector

查找：map.find(key)。返回一个迭代器。没找到：map.end()

遍历：

①for(unordered_map<key,T>::iterator iter=mp.begin();iter!=mp.end();iter++)          

cout<<"key value is"<<iter->first<<" the mapped value is "<< iter->second;

②    for(auto& v : mp)       

 print v.first and v.second

##### unordered_set

```cpp
unordered_set<int> num_set;
num_set.insert(num);
num_set.erase(num);
if (!num_set.count(num - 1));
```



##### priority_queue

优先级队列。

```cpp
//升序队列，最小堆
priority_queue <int,vector<int>,greater<int> > q;
//降序队列，最大堆（默认）
priority_queue <int,vector<int>,less<int> >q；
    
// 利用 vector 容器来初始化优先级队列     
vector<int> v{400, 100, 500, 200, 300};
priority_queue<int> priorQue(v.begin(), v.end());


//取堆顶
q.top();
//弹出堆顶、加入堆中
q.pop()
q.push(v)/q.emplace(v)
//自定义比较函数（此处为创建最小堆示例）
// true:前后需要交换。
struct cmp
{
    bool operator()(node& a,node& b)
    {
        if(a.x == b.x)  return a.y >= b.y;
        else return a.x > b.x;
    }
};
priority_queue<node,vector<node>,cmp>;
```



##### multiset

#include<set>

与set区别：set不能存储重复值

模拟出的平衡二叉树。

一个奇怪的地方：multiset的迭代器似乎不能加数字？

```c++
//插入
set.insert(val);
//删除值为val的所有元素
set.erase(val);
//删除第一个val
set.erase(set.find(val));
//删除某一个
set.erase(set.begin());
```

##### queue

queue.front(),queue.pop(),queue.push(v)

##### stack

stk.top(),stk.push(v),stk.pop()

##### deque

可以从后面/前面pop/获取元素值。

```cpp
deque<int> q;
q.pop_back();
q.push_back(num);
q.back();
q.pop_front();
q.push_front(num);
q.front();
```



##### switch

```cpp 
switch(expression){    
	case constant-expression  :       			statement(s);       
		break; // 可选的    
    case constant-expression  :       			statement(s);       
        break; // 可选的      
    default : // 可选的       
        statement(s); 
}
```

##### random

```cpp
int generateRandomInt(int start, int end) {    
    // 随机数引擎，使用随机设备来获得种子    
    std::random_device rd;    
    std::mt19937 gen(rd());    // 定义一个分布范围    
    std::uniform_int_distribution<> distrib(start, end);     
    // 生成并返回一个随机数    
    return distrib(gen); 
}
```

##### 自动引用计算

目的：让多个键指向同一块内存，自动管理引用计数。

```cpp
shared_ptr<int> current = make_shared<int>(1);
```

使用例子：

```cpp
unordered_map<int, shared_ptr<int>> t;
auto it1 = t.find(num-1);
auto it3 = t.find(num+1);
shared_ptr<int> current = make_shared<int>(1);
if(it1 != t.end() && it3 != t.end()){
    *it1->second += 1 + *it3->second;
    current = it1->second;
    t[num+1] = current;
}
```

可以正常像操作int一样操作它。

##### 各种复杂运算

幂次：include<math.h>     pow(double x,double y)

### 2021

#### 3.5

经典的化递归为动态规划，降低时间复杂度：91题（又绕又难）

反向思考：<=26时当前的结果res[i]=res[i-1]+res[i-2]

#### 3.6

94题。二叉树的中序遍历，巧用引用来节省空间和时间。

124题。二叉树的最大路径和[困难]。

自己的硬解：判断以根节点为中间点（本身+左节点为起始点+右节点为起始点），左节点为中间点，右节点为中间点哪个最大，逐级返回（看了一圈题解感觉自己的思路已经蛮精简了。。）

改进：1.可以去掉mid的那个方法（但也没提升多少。。）

2.代码跑出来复杂度高的原因：进行了重复遍历。复用可以用的重复遍历就好了。

用一个后序遍历，复用左右结点的结果。

（用一个全局变量记录最大的数值而非逐级返回，逐级返回的只有以该点为起始点的最大边）

解法：https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/solution/124hou-xu-bian-li-kuang-jia-bu-zuo-zhong-8nlu/（但其实也没提升太多。。）



236题。二叉树的最近公共祖先。（没啥难度，也就写了半小时🆒）

不重复的后序遍历一遍，两个都找齐了就停止，直接往上返回。

二刷：先序遍历其实应该更快。

找到返回自己，没找到返回null。（只考虑找到一个节点的情况）。

左右节点都不为空：返回自己。

左/右节点不为空：返回左/右节点

否则返回NULL。



#### 3.7

240题。二维矩阵搜索。一看就要用二分搜索。。

自己凭直观写的搜索（每次拿二维最中间的数据，然后搜索两个矩阵）只击败了30%嘤嘤嘤。

看了解答改完变20%了

。

（小坑：取中间的数尽量用(r+l+1)/2,否则奇数会漏了一个）





#### 3.16

15.三数之和。自己不重复的遍历一次超时了。

做了一次筛选（第一个元素大于0的直接否掉，有和前面重复的元素也否掉）依然超时真的让人脑壳疼。

原来筛选并不能减轻太多复杂度。。依然是三次方的复杂度。

精选解答：用L和R**从最左最右逼近**。三数之和大于0：降R；小于0：升L；等于0：先加入，再改同时改L和R。改降成两次方的复杂度就过了。（真的好妙，怎么想到的啊┭┮﹏┭┮



384.打乱数组。额外加了两个容器放拷贝后的数组，和结果数组。结果内存只击败了5%。（并不是关键。但打乱还可以优化一下。）

精选解答的洗牌算法：每次交换两张牌，且保证一次方的复杂度照顾到每张牌。



#### 3.18

121.股票买卖。自己的解法：找到最大元素，以及到最大元素为止的最小元素，相减。再往后找最大元素。。解的太烦了。

简化：记录每天卖出赚最多的方案。直接遍历一遍，记录最小元素，以及与最小元素相减是否超过记录的最大值。



53.最大子数组和。动态规划：如果之前的sum>0:对结果有利，sum+nums[i].否则sum=nums[i].每次和之前的max比较

leetcode官方建议尝试了分治法。虽然并不能提高性能但还是可以学习一下的。（左边最大，右边最大，中间最大<向左向右延伸>比较得出最大值）



450.删除二叉树结点。

好好复习数据结构吧。。cpp的指针不能随便改真的很烦。**面试之前得看看这题**



#### 3.19 

*146.LRU

把键值对查找复杂度降到O（1）：用**hashmap**。（unordered_map）

LRU:用双向链表（其实vector好像也很好用，还不用写轮子）



22.括号生成

一看就知道**递归**就是不知道怎么递归。。

"("+p时+")"+q时,p+q=n-1,均可为0.



#### 3.20

543.二叉树最长直径

简化版的124，只看124就行。



98.检查二叉搜索树。

后续遍历检查一遍。自己用了一个struct结构分别存储每棵树的max,min和isValid，空间复杂度较高。

精解用的中序遍历！太有道理了！每个节点都要大于中序遍历的前一个节点



#### 3.21

200.岛屿数量

每次遍历到1就暴力把前后左右都改成2，并再对前后左右是1的节点扩展。。然后岛屿数量++思路很简单（虽然写了很久）。

递归调用出现了stackoverflow。。debug了超级久



415.字符串相加[简单]

常规做法。。双指针优化，直接改s1，可以同时省内存和时间



151.翻转字符串。遍历就行



#### 3.22

69.求一个数的平方根。**牛顿迭代法**：求a的平方根x：不断用x=(x+a/x)/2



#### 3.23

62.一个矩形两个角之间的不同路径。

用迭代怎么优化都超时（第一步向下走或第一步向右走），最后运用了我优秀的排列组合知识把它给硬解出来了（向右向下的排列组合，Cn+m-2 n-1）

看了精解，直接解可以直接**动态规划**啊。。要得到最终的dp\[i]\[j]=dp\[i][j-1]+dp\[i-1][j],维护一个mxn的矩阵，复杂度m*n

**本题本质是一个杨辉三角**



89.格雷码

根据n-1时的情况反向扩展：每一位前面添一个1，倒序插进去。



297.序列化与反序列化

尝试了两种方案：广度遍历和广义表达式，但都挺慢的。精解用先序遍历，应该会快一点。。

#### 3.25

468.验证IP地址。

巨烦的一道题，里面有非常多坑（包括但不限于数字out of range，间隔符过少，以及题目给出的一些情况），**有时间可以再看一遍**



206.反转链表

要求用两种解法。

递归用一个while循环，两个指针标记一下前一个结点和后一个结点就行了。

迭代要重写一个函数——因为返回值应该是尾结点，而迭代的完成返回末端结点然后直接把当前结点加上是最省时间的。



47.全排列

经典的回溯问题。去重剪枝的关键：要找到重复元素，所以先做一次排序，让所有重复的元素靠在一起。

回溯的思路：在第n个位置上填上一个数字（不重复），然后回溯n-1



207.课程表（前继课程问题）

经典的判断图中有无环。用了最原始的删节点方式，用一个大矩阵存两边的联系，逐个删除没有入度的结点，但发现时间空间复杂度都很高。



138.复制带随机指针的链表

一开始没想到可以用**哈希表**。

把复制过的<原节点，新节点>存到哈希表里，再迭代遍历当前节点的随机指针和next指针，然后赋值就好了。

用哈希表可以知道有没有复制过。复制过就直接返回，否则复制并加表。



#### 3.26

4.寻找两个有序数组的中位数。

自己直接暴力合并居然也时间复杂度超过了90%。。但题目要求log的复杂度，肯定要用二分法。

精解的思路：**转化成求第k小的数**。 利用两个数组有序的性质：看两个数组k/2位置的数，较小的那个之前必然不可能是第k个数。再往后合并。



1095.山脉数组中查找目标值

看题目的时间复杂度要求应该是要用二分法。

奋战三个多小时后终于过了。

不考虑山脉的二分法：先判断左半边，再判断自己，再判断右边。按顺序判断，有值直接返回，会超时。

做了优化的解法：用一个r，l的全局变量框住山顶的值。每次递归先判断这个区间是否一定在山脉的左边/右边，在就好做多了，直接变成一个传统二分查找，省掉了一般的复杂度。



#### 3.28

560. 和为k的子数组

     思路：遍历之前的结果，即使优化过后也有二次方的复杂度，因此要用**hash_map**存之前的值才能把复杂度降到O（n）。hash里存（sum,目前和为sum的个数），利用**sum(i,j)=sum(0,j)-sum(i,j)**[hash]，这样每次往后迭代只需要O（1）的复杂度查hashmap。



103.二叉树锯齿形层次遍历

层次遍历的变体，用一个栈，根据是奇数层还是偶数层决定怎么读取和加入子节点即可。



152.乘积最大子数组。

和今天做的560搞混了。。560是求一个等值情况，而本题应该类比53的最大子序和，做一个动态规划。

记录包括本数字在内的乘积值，保存当前的最大值和最小值。



#### 3.29

25.K个一组翻转链表

把题目分成两部分：1.分成多个长度为k的链表 2.把断开的链表分别翻转并拼到一起。

翻转链表的尾结点的next记得及时改变为nullptr，不然会出现循环链表问题。



119.杨辉三角。

题目要求空间复杂度要为O（k），用一个一维数组，dp就可以解决。

小细节是要注意做A(i,j)=A(i-1,j)+A(i-1,j-1)时，一维数组中j-1列的值上一次已经改变，所以要额外用一个int记录一下。

用组合知识暴力解似乎更爽一些？



59.螺旋矩阵（顺时针向矩阵填入1-n²）

用一个int记录方向，num自增到n²即可



#### 3.30

*300.最长递增子序列

题目不要求子数组连续，迭代不能只保存之前一个的最长递增序列，用一个动态规划数组存以i结尾的最长递增序列，dp[i]=dp[j]+1,其中nums[j]<nums[i],且为满足条件中dp[j]最大的。时间复杂度是O（n²）。

nlogn应该要用二分查找。精解是一个非常巧妙的贪心+二分。

考虑一个简单的贪心，如果我们要使上升子序列尽可能的长，则我们需要让序列上升得尽可能慢，因此我们希望每次在上升子序列最后加上的那个数尽可能的小。

基于上面的贪心思路，我们维护一个数组 d[i]，表示长度为 i的最长上升子序列的末尾元素的最小值，用len 记录目前最长上升子序列的长度，起始时len 为 1，d[1] nums[0]。

同时我们可以注意到 d[i] 是关于 i单调递增的。每次只需要二分查找并更新就可以了。

二分查找更新时的小坑：由于是要找nums[i]<k<nums[i+1]，并将nums[i+1]更新，因此二分递归时如果碰到nums[i]>k或nums[i+1]<k的情况，i与i+1仍然有可能是最后那个被替换掉的值，迭代时要作为边界带入而不能被筛出。



#### 3.31

79.单词搜索

> 给定一个二维网格和一个单词，找出该单词是否存在于网格中。单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

一个非常简单的回溯。先找到第一个字母，然后再board中对其前后左右进行搜索word(1,end)，再在下一个位置去找word(2,end)，以此类推。

其中不能忽略的点是要把走过的路封死（不能重复使用）。先标记一个值，查找完毕后再设置回去就好了。



153.旋转数组的最小值

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] 。
>
> 请找出其中最小的元素。
>

首先肯定二分法没跑了。自己想的二分解法是找到nums[mid1]>nums[mid2]的点（整个数组中只有一块是递减）。

精解提供了另一种思路：逐渐逼近这个最小值点。可以发现：第一段递增序列的值始终大于第二段递增序列。于是有以下逐渐逼近的方法

``

```C
        if(nums[mid]>nums[right])
            left=mid+1;
        else
            right=mid;
```

直到right=left.



#### 4.1

209.长度最小的子数组

>
> 给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**
>
> 找出该数组中满足其和 `≥ target` 的长度最小的 **连续子数组** `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。

使用滑动窗口。用两个指针一起向后移动。当前sum>=target就移动左指针，否则移动右指针。



73.矩阵置0

> 给定一个 `*m* x *n*` 的矩阵，如果一个元素为 **0** ，则将其所在行和列的所有元素都设为 **0** 。请使用原地算法。**空间复杂度为常量**。

由于要求空间复杂度为常量，只能在遍历时**在矩阵内部**记录哪行为0，哪列为0。但这样第一行和第一列之前的0就无法保留了。再用两个变量保存第一行和第一列初始有无0即可。



#### 4.2

*287.寻找重复数

> 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
>
> 假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。
>
> 进阶：
>
> 如何证明 nums 中至少存在一个重复的数字?
> 你可以在不修改数组 nums 的情况下解决这个问题吗？
> 你可以只用常量级 O(1) 的额外空间解决这个问题吗？
> 你可以设计一个时间复杂度小于 O(n2) 的解决方案吗？

本题的奇特之处在于本可以用O（n）时间复杂度就可以解决（建哈希表），但由于要求O（1）的空间复杂度，时间复杂度放宽到了<O(n²)，也就是nlogn.

肯定要使用二分法，但有点难想如何二分。精解的思路：猜一个数(mid),统计小于mid的数是否**严格大于**mid,是的话可能的数就去掉一半了。（**本质是抽屉原理**）

（有点像一个反向的常规二分：一般都是外层是n复杂度，内层套二分logn.但这个思路是外层logn,内层n



141.环形链表

判断链表中有无环。要求用O（1）空间复杂度。把遍历过的结点改个值即可。



#### 4.4

39.组合总和

> 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
>
> candidates 中的数字可以无限制重复被选取。
>
> **示例 1：**
>
> ```
> 输入：candidates = [2,3,6,7], target = 7,
> 所求解集为：
> [
>   [7],
>   [2,2,3]
> ]
> ```

一个还挺显然的回溯问题。

为了方便剪枝以及回溯的中止，先对原数组排个序。回溯思路：当前的target包含自己在内&当前的target不包含自己在内。回溯的结束：target==0:说明已经有满足条件的解，把该解加入到最终集合中。target<<!--candidates-->[start]：（或start超出数组范围了）不可能有了，直接返回一个空值。



40.组合总和||

上一题的变体。

> 示例 1:
>
> 输入: candidates = [10,1,2,7,6,1,5], target = 8,
> 所求解集为:
> [
>   [1, 7],
>   [1, 2, 5],
>   [2, 6],
>   [1, 1, 6]
> ]

区别在于剪枝问题：如果candidates中有重复数字的话，**第一个数字**只能选一遍。也就是回溯问题改成如下形式：

```c++
        vector<vector<int>> res2=mySum(candidates,target-candidates[start],start+1);
        for(int i=0;i<res2.size();i++){
            res2[i].push_back(candidates[start]);
        }
        int next=start+1;
        while(next<candidates.size()&&candidates[next]==candidates[start]){
            next++;
        }
        if(next==candidates.size()){
            return res2;
        }
        vector<vector<int>> res1=mySum(candidates,target,next);
        res1.insert(res1.end(),res2.begin(),res2.end());
```



105.从前序遍历与中序遍历数组构造二叉树

常规思路就是找到中序遍历的的根节点，然后划分开左树和右树。但是这样做会导致比较高的时间复杂度，用一个哈希表在开始时遍历一遍中序数组的位置。

优化后时间复杂度O(n)，空间复杂度O(h)+O(n)=O(n).



#### 4.5

145.二叉树的后序遍历

题目要求不用递归。因此只能用栈保存。

后序遍历的顺序时左子树->右子树->自己，因此用栈先压入自己再压入左子树，再次到自己时再压遍历右子树。用一个bool记录当前是否已遍历过右子树。



154.寻找旋转数组中的最小值||

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
>
> ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
>
> 请找出其中最小的元素。
>
> 注意数组中可能存在重复的元素。
>

153的变体。由于重复元素的存在，左边的旋转数组不再严格大于右边的旋转数组，而是可能相等。因而nums[mid]==nums[right]的情况两边都要算，然后取小值。



189.旋转数组

> 给定一个数组，将数组中的元素向右移动 `k` 个位置，其中 `k` 是非负数。
>
> 示例 1:
>
> 输入: nums = [1,2,3,4,5,6,7], k = 3
> 输出: [5,6,7,1,2,3,4]

本题要求使用O(1)的常量复杂度。

最巧妙的精解是直接reverse，然后再分段reverse，太神奇了。。但似乎有一点难想

官方的解答使用循环替换法：不断找到被换掉的数应该在的位置，直到所有数都换过一轮。需要注意的小细节是有可能转了一圈回到原点。此时应该直接加一继续遍历。



628.三个数的最大乘积

最暴力的解法：直接O（n）遍历一遍数组，分成大于0和小于0两个阵营，排序，然后分类讨论多种情况。

优化一点可以原地排序，空间复杂度O(logn)

更优化的解法：列出几种情况后发现，只需要最大的，第二大的，第三大的，最小的，第二小的五个数。遍历一遍就能算出来了。空间复杂度O（1).最后只需要return(三个最大的数相乘，最大的数乘以两个最小的数)



386.字典序排数

**字典序本质可以化为一棵树**，进行一个深度优先搜索就可以了。



#### 4.6

295.数据流的中位数

> 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
>
> 例如，
>
> [2,3,4] 的中位数是 3
>
> [2,3] 的中位数是 (2 + 3) / 2 = 2.5
>
> 设计一个支持以下两种操作的数据结构：
>
> void addNum(int num) - 从数据流中添加一个整数到数据结构中。
> double findMedian() - 返回目前所有元素的中位数。
> 示例：
>
> addNum(1)
> addNum(2)
> findMedian() -> 1.5
> addNum(3) 
> findMedian() -> 2

强行插入的代价还挺高的，插入一次就是O(n)的复杂度，还要查找插入的位置，不太可行

精解给了两个思路都挺巧妙的。

①双堆碰撞。维护一个n/2个最大值的最小堆和一个n/2个最小值的最大堆。用priority_queue做。插入只需要O(logn)的复杂度。

②二叉搜索树。用multiset做插入。维护两个指针：lo_high和lo_min



#### 4.8

148.排序链表

题目要求使用O（nlogn）的时间复杂度和常数级空间复杂度。

nlogn复杂度的排序：堆排、归并、快排。其中堆排并不是严格的从小到大排序。最适合链表的是归并。

由于常数级复杂度的要求，不能使用回溯，而是要自底向上的进行归并。初始子数组长度为1，两个两个一组对链表进行归并。（这次还是遇到了上次的bug：没有把没用的next置为null。。）



37.解数独

比较容易想到用三个vector存每行每列每个九宫格内是否有出现过该数。

每次遍历的时候需要O(9)的复杂度查找当前能填的数。优化：可以使用位运算进行。



877.石子游戏

> 亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。
>
> 游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。
>
> 亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。
>
> 假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。
>

预测赢家的题目用贪心算法得到的结果并不对。。必须枚举得到所有的结果才行。

动态规划应该没跑了。但规划的思路有一点难想：用一个二维矩阵表示还剩dp[i,j]的时候的最大能取数。其中dp\[i]\[i]的值是固定的，往回推就可以用一种类似逆向思维的方式判断对手接下来的所有操作。取dp\[i+1][j]和dp\[i][j-1]中更小的值（希望对手拿的少），然后用sum减一下。



还是要骂一句。这题是不是脑瘫？直接return true就对了？



114.二叉树展开为链表

> 给你二叉树的根结点 root ，请你将它展开为一个单链表：
>
> 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
> 展开后的单链表应该与二叉树 先序遍历 顺序相同。

看似先序实则后序。把左右树分别做成链表，然后串到一起拼成先序的样子就行了。

回溯的条件：结点为null.如果左节点为空直接把右树串成链表就能返回了。



#### 4.10

208.Trie前缀树

主要是一个科普项的了解。

用于拼写检查，自动补全，IP路由等

结构长这样

![无效的图片地址](https://pic.leetcode-cn.com/3463d9e7cb323911aa67cbd94910a34d88c9402a1ab41bbea10852cd0a74f2af-file_1562596867185)

![无效的图片地址](https://pic.leetcode-cn.com/0cddad836ee9a200b150a3d89f96035f44f3643c4fba0cb1f329e2307c714895-file_1562596867185)

349.两个数组的交集

一个难度为easy的题。要求对结果进行剪枝去重。

排序再做的话复杂度是nlogn，其实还可以优化到O(n):先遍历其中一个数组，用一个哈希表去存，再遍历另一个。剪枝的做法：每找到一个重复元素直接从哈希表里删掉。



692.前K个高频单词

和前K个高频元素一样

**用pair简化堆排序的代码如下，建议反复背诵**


​        
```c++
class Solution {
	public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> mp;
        for(string& ev: words) mp[ev]++;
   	    priority_queue<pair<int, string>> q;
    	for(auto& [str, cnt]: mp){
        	q.push({-cnt, str});
        	if(q.size() > k) q.pop();
    	}
	    vector<string> ans;
    	while(!q.empty()){
        	ans.push_back(q.top().second);
	        q.pop();
    	}
    	reverse(ans.begin(), ans.end());
    	return ans;
		}
	};
```

88.合并两个有序数组

> 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
>
> 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1 的空间大小等于 m + n，这样它就有足够的空间保存来自 nums2 的元素。
>
>  
>
> 示例 1：
>
> 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
> 输出：[1,2,2,3,5,6]

一个逆向双指针。



*剑指offer51.数组中的逆序对。

> 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

用dp并不好解。暴力解法最高复杂度是O(n²)，优化的空间非常有限。

其实本质是一个排序题：因为要找的答案本身就包含了大小的比较。一开始想到了快排但会遗漏很多情况，用归并排序是最容易解决的。

一个小细节：归并在相等的情况下优先考虑左边的数加入，不然答案会比原来的偏多。



1155.掷骰子的N种方法

> 这里有 d 个一样的骰子，每个骰子上都有 f 个面，分别标号为 1, 2, ..., f。
>
> 我们约定：掷骰子的得到总点数为各骰子面朝上的数字的总和。
>
> 如果需要掷出的总点数为 target，请你计算出有多少种不同的组合情况（所有的组合情况总共有 f^d 种），模 10^9 + 7 后返回。
>

一个可以重复的全排列问题，回溯是非常显然的思路，但会存在重复计算的问题，所以采用动态规划更为合适。

dp为一个二维矩阵，大小dp\[d]\[target]，初始全部为0。

存下d个骰子抛掷出t值能有多少种可能。往下迭代时：dp\[i][j]=sum(dp\[i-1][j-k]),k从1到d。



#### 4.12

*84.柱状图中的最大矩形

> 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
>
> 求在该柱状图中，能够勾勒出来的矩形的最大面积。
>

暴力解法时间复杂度也只有O(n²)，且通过不了用例。

从动态规划来看：找到当前柱子前后（连续）大于等于自己的柱子个数。用一个栈存单调递增的序列（比自己大的柱子最高高度是可以确定的），遇到大于自己的弹出。栈中保存元素值和index。**解法建议反复背诵**。

单调栈解决的问题：**连续**大于/小于当前数的个数

用哨兵单调栈解法，从左到右再从右到左遍历两遍。

#### 5.18

*160.相交链表

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/14/160_example_1.png)

用哈希表，把A链表放到哈希表，再遍历B，时间复杂度O(A+B),空间复杂度O(A)。
最优的解法把空间复杂度降到了常数：用双指针遍历A+B和B+A，到末尾相同的部分即为相交处。

#### 6.10

搜索旋转排序数组。

思路很清晰：相当于两段单调递增的数组，其中第一段严格大于第二段。找到第一段结束的点再搜索就可以了。

一个小坑：在[3,1]这种情况下（只有两个数，且正好倒序），找第一段结束的点会进入死循环。需要加个额外条件判断一下。

#### 9.1

*44.通配符匹配

> 给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
>
> '?' 可以匹配任何单个字符。
> '*' 可以匹配任意字符串（包括空字符串）。
> 两个字符串完全匹配才算匹配成功。

难点在于‘*’是不确定的，迭代遍历会超时。

本质是是一个动态规划，找到状态转移方程就ok。

### 2022

#### 一些总结

##### 单调栈

一般是维护一个正向栈和一个反向栈。本质其实也是一个动态规划问题。

实现时需要一个栈，两个数组（left和right，用于记录入栈出栈的边界）。每次push前先判断栈顶元素是否大于/小于自己，来不断pop。

通过线性次的入栈和出栈保证O（n）的时间复杂度，一般用于连续子数组中的最小值/最大值。

###### 10.28

[907](https://leetcode.cn/problems/sum-of-subarray-minimums/solution/zi-shu-zu-de-zui-xiao-zhi-zhi-he-by-leet-bp3k/)

单调栈问题。

要注意单调栈问题中的去重问题：可以维护正向栈严格大于/小于，反向栈大于等于/小于等于。

##### dp

###### 双指针包括快慢指针，双向指针

### 2023

#### 7.4

[238](https://leetcode.cn/problems/product-of-array-except-self/)

不难摸索到这题应该是个类似动规的需要填表的题，但要想到具体的乘积怎么计算能够在一次遍历(O(n))内完成。

挖掉自己：计算左边的乘积，乘上右边的乘积，得到最终结果。因此只需要维护L[i]和R[i]

减少需要的内存空间：只需要保存L[i]，计算R[i]时边算边乘到L[i]里，节省遍历时间和空间。



[283](https://leetcode.cn/problems/move-zeroes/submissions/)

把0想象成空位，所有的物品全部移到最前面，后面的补上0标记为空位。

双指针。



[392](https://leetcode.cn/problems/is-subsequence/solution/pan-duan-zi-xu-lie-by-leetcode-solution/)

主要考虑进阶问题：大量的子串怎么判断。

对于字符串t，不能每个子串s都遍历一遍t，因此要预处理t。用动态规划：对t的每一个字符，记录下下一个char出现的位置。填表$f[i][j]$，代表位置i及之后第一个出现字母j的位置。



[11](https://leetcode.cn/problems/container-with-most-water/?envType=study-plan-v2&envId=leetcode-75)

面积大：宽且高。宽：由左右的index决定。高：由短边决定。

可以一开始在最宽处开始，则收窄时，若短边变长，有可能面积变大。而其它情况都不会面积变大（**但之后在更窄的地方可能变大）**。

双指针夹逼，遇到其它情况时任意更新其中一个指针，确保最优情况并没有丢失即可（被丢掉的都比当前的最大值要小）。

#### 12.22

**120.三角形最小路径和**

一个动态规划问题，一定要先写好转移方程式，考虑到一些i=0和i=n的边界情况。

#### 12.23

**322.零钱**

一道比较显然的dp题，也很容易想到是一个二维数组去填表。

但填的方向（先填列还是先填行）有时会很大程度影响复杂度，要想一下每种填法背后的意义，列出转移方程式。

**46.全排列**

回溯法：先找分支解，再加入自己。类似dp。

想明白回溯的终点和当前节点怎么加入子序列最划算是关键。

#### 12.24

127.单词接龙

看到最短路径问题：首先考虑广搜。涉及到建图/建树。

考虑到单词间两两比较效率很低，可以采用一个虚拟节点h*t，连接多个单词。

**LCR134 Pow(x,n)**

快速幂思想

**460.LFU**

关于平衡二叉树的使用可以看一下（但这个好像并不符合题解的O（1）复杂度）

#### 12.25

**215.数组中第K大的元素**

对于无序列表找第K大的数=》快排的简化版。

快排优化：1.随机挑选基准数。2.三路划分：避免大量重复数字的情况。

#### 12.28

**128.最长连续序列**

=》如何遍历常数遍数组就能得到答案。

1.只遍历一次：用哈希表记录包含对应数字的连续序列长度——但由于连续序列不包含重复数字，这里其实只需要保证序列的头和尾在哈希表中的对应键值是正确的（每次新数字只会加在原序列的头部/尾部）。因此每次遍历新数字只需要更新头尾的哈希值，为常数复杂度。

2.第一次遍历将所有数字加入哈希集合，第二次遍历再只从每个序列的头部开始计算长度。

①对于set.count(t[num-1])!=0的数字，可以直接跳过。

②否则说明为某个连续队列的头部，向后寻找最后一个连续序列数。

由于在②中每个数字至多只会遍历一次，因此整体复杂度仍为O（n）。②可以计算包含重复数字的连续序列。

**49.字母异位词分组**

用哈希表记录已有单词char排序后的string，键值为该char组合的单词列表。遍历一遍单词表后再遍历一次哈希表。

优化=》哈希表：排好序的string-》在res中的index值。不需要再遍历哈希表。

**42.接雨水**

1.每个位置能接的雨水=min(左边最大的数,右边最大的数)-h。两次遍历。

2.单调栈：min(左边第一个大于自己的数,右边第一个大于自己的数)-h*二者下标之差的水一定能被放下（考虑一块一块矩形去接雨水）

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rainwatertrap.png)

#### 12.30

239.滑动窗口最大值

1. k个数中的最大值，最容易想到的就是最大堆(priority_queue)。若堆顶的index过期，则删去堆顶。因此最大堆可以用pair来构建。
2. 执行一遍滑动窗口，若遇到该窗口内的最大值，则在该index之前的数再也不会被选中。因此可以考虑维护一个单调递减队列。
   该队列应该能够根据新增的值重新调整队列(pop_back,push_back())。同时也能删除不在窗口内的过期值(pop_front())。因此可以用双端队列deque。



76.最小覆盖子串

遇到字符类找子串/异位词等涉及字符级别的数量比较：vector/unordered_map记录字符的个数。配合滑动窗口。

189.轮转数组

1.环状替代：先用辗转相除法求最大公约数（或者直接调库，gcd），再以公约数为轮数做环状替换。

2.翻转法：翻转所有元素后，再翻转0-k，k-n。



41.缺失的第一个正数

在只能用O(1)空间且必须用哈希（时间复杂度为O（N））的情况下，可以考虑**原地哈希**。将原有的数组当成一个哈希表使用，哈希规则视题目而定。



### 2024

#### 1.1

160.相交链表

做链表题的时候一定要画图，可以利用其中一定的数学关系。

设a链表不同的长度为a，b链表不同的长度为b，二者相交的部分长度为c。

则利用a+c+b=b+c+a,pa指针在走过a链表和b的独立部分，pb指针走过b链表和a的独立部分后到达共同顶点（也包括NULL，即不相交）。

#### 1.3

994.腐烂的橘子

多源广度优先搜索=》使用队列。

搜索结束：队列为空/腐烂橘子的个数=橘子的总个数



207.课程表

判断图中是否有环/是否存在拓扑序问题。

dfs依次搜索图中的节点：用visited标记访问状态（此时应该有三种状态，未访问，访问中，已访问。访问完所有前继节点后将访问状态设为已访问。若访问前继节点时遇到“访问中”节点，则说明存在环。）



#### 1.4

**230.二叉搜索树中第K小的元素**

利用二叉搜索树中序遍历结果为顺序遍历，遍历到第K个即为要找的数。



[22. 括号生成 ](https://leetcode.cn/problems/generate-parentheses/description/)

1.考虑回溯法：寻找下一个字符应该是什么。若左括号数\<n:可以是左括号。若左括号数\>右括号数：可以是右括号。 用一个vector\<string\>引用记录所有可能的答案，用一个string记录现在走过的路径。



2.考虑dp：由于任何一个序列都以'('开头，且有唯一的')'与之对应。当n=k时，括号一定可以进行分组$(n_{i})n_{k-i-1}$,i=0-k-1



**139.单词拆分**



**5.最长回文子串**

1.中心扩散思想

2.dp，每一轮新增加一个字符



#### 1.5

**169.多数元素**

可以抽象成该元素和其它元素的对抗，遍历到最后该元素一定能胜出。

用candidate置为目前被选中的元素值，count为投票数。若当前元素!=candidate:count--。count为0时换人。



**394.字符串解码**

用栈来操作：

遇到数字时：解析，进栈。

遇到字符/‘[’：直接进栈。

遇到']':开始出栈。直到遇到'['。将其中的字符拼到一起并✖之前的count数。

#### 1.6

[437. 路径总和 III ](https://leetcode.cn/problems/path-sum-iii/)

本题是树的路径总和。一次dp做完的核心思想是要能联想到前缀和：即sum[i,j]=sum[0,j]-sum[0,i]。

而后只需要看sum[0,i]中是否有cur-targetSum的个数即可。

注意初始化：prefix[0]=1.可以保证sum[0,j]也被包含在内(sum[0,0]=0)



#### 1.18

[2571. 将整数减少到零需要的最少操作数 ](https://leetcode.cn/problems/minimum-operations-to-reduce-an-integer-to-0/description/)

如果一个二进制数仅含一个1：只需要一次就能归0

如果一个二进制数含有2个及以上**连续**的1：可以先将其变成只剩一个1，再归0，需要两步。

考虑有可能出现110110（54），前面的连续1和后面的隔了一个0，可能可以+1合并连续1，再消除。

因此遍历连续1可以先只将ans+1,cnt置为1，看能否与后面的连续1合并。不能再花一步消除。



#### 1.21

**134.加油站**

假如当前一段路无法走下去了，就该放弃 换个新的起点了。这个起点最多只能到这里了，**从这段路的任何地方重新开始都到达不了更远的地方了，因为放弃之前走的路都是帮你的**，不然早就无法走下去了，因此 起点只能选在下一站，错的不是你，是你的起点和你的路。



#### 1.22

[32. 最长有效括号](https://leetcode.cn/problems/longest-valid-parentheses/description/)

记以s[i]结尾的最长有效括号长度为dp[i]。

若s[i]为')'：

可以对前一个字符s[i-1]做分类讨论。

若s[i-1]为'('：则以s[i]结尾的最长有效括号为(...........)()。因此dp[i]=dp[i-2]+2

若s[i-1]为')'：则已有(......))，要为s[i]找到匹配的'('。

但此时不可能是((......)(......))，因为这样的话dp[i-1]得到的就不是其最长有效括号，因此s[i-dp[i-1]]一定是'('dp[i]才不为0.

因此应该长这样：(......)((......))。所以dp[i]=dp[i-1]+dp[i-dp[i-1]-2]+2

#### 1.25

**2859.[计算 K 置位下标对应元素的和](https://leetcode.cn/problems/sum-of-values-at-indices-with-k-set-bits/)**

本题的关键是如何快速用**位运算**得到一个数的二进制表示的位数。

n&(n-1)：可以去掉最右边的一个1。

用途：1.判断n是否为2的幂次（=0） 2.判断n的二进制表示中1的个数

#### 1.31

[452.用最少的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)

一开始把问题想复杂了。。其实贪心就可以做了。

从左往右打出第一支箭，确保能射中第一个气球的同时射中最多的气球，再向前走，继续射箭。

（反正最后每个气球都必须被解决，不如在第一次遍历到它就解决。）

#### 2.1

205.[同构字符串](https://leetcode.cn/problems/isomorphic-strings/)

同构：a中的每个元素，b中有唯一元素与之对应，反之亦然。

因此应该构建两个哈希表，检查是否符合**双向唯一映射**（双射）。



#### 2.20

[224. 基本计算器 - 力扣（LeetCode）](https://leetcode.cn/problems/basic-calculator/solutions/646369/ji-ben-ji-suan-qi-by-leetcode-solution-jvir/?envType=study-plan-v2&envId=top-interview-150)

如何将中缀表达式转后缀表达式，并计算。

1. 预处理：去空格，对于单目计算符转为双目(0±n)
2. 转后缀：根据优先级来压栈/弹栈。
   思路：对于字符串中的数字部分：直接加入后缀表达式最终结果（相邻的二者一定会被某个计算符连接到一起）；
   对于操作符：单独建栈。
   普通操作符：在其前面的且优先级>=自己的，弹出加入后缀表达式结果。
   '('：直接进栈（相当于开辟了一个新的栈），普通运算符遇到它直接进栈（栈底）。
   ')'：弹栈，直到遇到'('。
3. 计算，这一步也可以和2结合到一起做。



#### 3.3

[117. 填充每个节点的下一个右侧节点指针 II ](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/description/)

链表问题需要保存头/尾的情况，可以考虑用一个哨兵节点。

法1：迭代：如果第i层已经完成next操作，则第i+1层可以顺藤摸瓜串起来。

法2：用DFS的方式做BFS：

先序遍历可以保证**同一层中，在自己前面的节点一定会先被访问**。

因此可以用一个vector记录每一层中最后一个遍历到的节点，DFS递归时将深度记录在内。

每次遍历到当前节点时，判断是否为该层最左边的节点，不是则更新上一个节点的next。



#### 3.8

[2. 两数相加 - 力扣（LeetCode）](https://leetcode.cn/problems/add-two-numbers/solutions/7348/hua-jie-suan-fa-2-liang-shu-xiang-jia-by-guanpengc/?company_slug=nvidia)

涉及到返回链表的问题一般一定要设置一个dummy指针，返回头节点。

对于两个不一样长的链表，在相加问题中可以一起处理(p1||p2)，对于为空的指针补0，会比单独处理长出来的部分更快。

### 考前背一下

最大公约数：辗转相除法

![img](https://img-blog.csdnimg.cn/2019042711185680.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NoZW5femFuX3l1Xw==,size_16,color_FFFFFF,t_70)

146

23.归并排序

```cpp
class Solution {
public:
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;
        }
    };
priority_queue <Status> q;

ListNode* mergeKLists(vector<ListNode*>& lists) {
    for (auto node: lists) {
        if (node) q.push({node->val, node});
    }
    ListNode head, *tail = &head;
    while (!q.empty()) {
        auto f = q.top(); q.pop();
        tail->next = f.ptr; 
        tail = tail->next;
        if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
    }
    return head.next;
}
};
```

#### 各种排序

##### 快排

##### 归并排序

复杂度：时间O(nlogn)，空间O(logn)（栈空间）

递归版：

思路：用快慢指针把整个链表分成两块，分别做sort后再merge。

分的时候：注意tail指的是尾巴的后一个

一些坑：为防止merge时出现循环，在sort时应该**把队尾的指针指向null**

```cpp
Node* mergeSort(Node* head, Node* tail) {
	if (head->next == tail) {
		head->next = nullptr;
		return head;
	}
	auto merge = [](Node* h1, Node* h2)->Node* {
		Node* dummy = new Node();
		Node* temp = dummy;
		while (h1&&h2) {
			if (h1->val < h2->val) {
				temp->next = h1;
				h1 = h1->next;
			}
			else {
				temp->next = h2;
				h2 = h2->next;
			}
			temp = temp->next;
		}
		temp->next = h1 ? h1 : h2;
		return dummy->next;
	};
	Node *slow = head, *fast = head;
	while (fast->next != tail) {
		slow = slow->next;
		fast = fast->next;
		if (fast->next != tail) fast = fast->next;
	}
	return merge(mergeSort(head, slow), mergeSort(slow, tail));
}

Node* mergeSort(Node* head) {
	return mergeSort(head, nullptr);
}
```

非递归：

思路：自底向上的归并，迭代法。用sublen记录当前归并的长度，每次归并一小段。

注意点同上，merge前要将尾节点指向空指针。

```cpp
Node* mergeSort(Node* head) {
	auto merge = [](Node* h1, Node* h2)->Node* {
		Node* dummy = new Node();
		Node* temp = dummy;
		while (h1&&h2) {
			if (h1->val < h2->val) {
				temp->next = h1;
				h1 = h1->next;
			}
			else {
				temp->next = h2;
				h2 = h2->next;
			}
			temp = temp->next;
		}
		temp->next = h1 ? h1 : h2;
		return dummy->next;
	};
	int sub_len = 1;
	int len = 0;
	Node* countNode = head;
	while (countNode) {
		len++;
		countNode = countNode->next;
	}
	Node* dummy = new Node();
	dummy->next = head;
	while (sub_len < len) {
		Node* temp = dummy;
		Node* cur = dummy->next;
		while (cur) {
			int count = 1;
			Node* h1 = cur;
			while (cur && count < sub_len) {
				cur = cur->next;
				count++;
			}
			Node* t1 = cur;
			cur = cur->next;
			Node* h2 = cur;
			count = 1;
			while (cur && count < sub_len) {
				cur = cur->next;
				count++;
			}
			Node* t2 = cur;
			if (cur) cur = cur->next;
			t1->next = nullptr;
			if (t2) t2->next = nullptr;
			temp->next = merge(h1, h2);
			while (temp->next) {
				temp = temp->next;
			}
		}
		sub_len *= 2;
	}
	return dummy->next;
}
```



##### 堆排

#### 215.堆排，快排

快排优化：1.随机挑选基准数。2.三路划分：避免大量重复数字的情况。

快排的两种写法：1.迭代法。用栈记录要划分的起点和终点，依次做分区。做完分区再对分区两端入栈。

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <utility>

// 用于生成随机数的函数
int getRandomPivotIndex(int low, int high) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

// 分区函数
int partition(std::vector<int>& arr, int low, int high) {
    // 随机选择基准数，并与第一个元素交换
    std::swap(arr[low], arr[getRandomPivotIndex(low, high)]);
    int pivot = arr[low];
    
    int i = low, j = high;
    while (i < j) {
        // 从右向左找第一个小于基准的数
        while (i < j && arr[j] >= pivot) {
            j--;
        }
        // 从左向右找第一个大于基准的数
        while (i < j && arr[i] <= pivot) {
            i++;
        }
        // 如果找到则交换
        if (i < j) {
            std::swap(arr[i], arr[j]);
        }
    }
    // 基准数归位
    std::swap(arr[low], arr[i]);
    return i; // 返回基准数的位置
}

// 迭代快速排序
void quickSortIterative(std::vector<int>& arr) {
    std::stack<std::pair<int, int>> stack;
    stack.push({0, static_cast<int>(arr.size()) - 1});

    while (!stack.empty()) {
        auto [low, high] = stack.top();
        stack.pop();

        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            stack.push({low, pivotIndex - 1});
            stack.push({pivotIndex + 1, high});
        }
    }
}

int main() {
    std::vector<int> data = {3, 6, 8, 10, 1, 2, 1};
    quickSortIterative(data);

    for (int i : data) {
        std::cout << i << ' ';
    }

    return 0;
}

```

2.递归法：分区后直接对左右两端做下一轮的quickSort

```cpp
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// 随机数生成器初始化
std::mt19937 rng(std::random_device{}());

int getRandomPivotIndex(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

// 分区函数
int partition(std::vector<int>& arr, int low, int high) {
    // 随机选择基准数，并与第一个元素交换
    int randomPivotIndex = getRandomPivotIndex(low, high);
    std::swap(arr[low], arr[randomPivotIndex]);
    int pivot = arr[low];

    int i = low + 1;
    for (int j = low + 1; j <= high; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[low], arr[i - 1]);
    return i - 1;
}

// 快速排序的递归函数
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// 一个方便的包装函数，开始整个排序过程
void quickSort(std::vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

int main() {
    std::vector<int> data = {10, 7, 8, 9, 1, 5};
    quickSort(data);
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}

```

#### 二叉树遍历

迭代法（下图示例为中序遍历）：

维护栈的目的：确保出栈顶的元素一定左子树已经被遍历过。

```cpp
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        while(root!=nullptr || !stk.empty()){
            while(root!=nullptr){
                stk.push(root);
                root=root->left;
            }
            TreeNode* temp=stk.top();
            stk.pop();
            res.push_back(temp->val);
            root=temp->right;
        }
        return res;
    }
```

#### 堆排序——最大堆/最小堆

一棵完全二叉树/近似完全二叉树。一般用**数组**做存储。父节点一定>/<子节点

下标为i的结点：左右节点下标分别为2i+1,2i+2

##### 建堆（无序堆调整）

从第一个有子节点的堆开始递归调整($(size-2)/2$).若父节点变为子节点，还要再递归调整子节点。

##### 堆排序（最大堆调整）

![img](https://pic4.zhimg.com/80/v2-cf88501a8092e7b0c4712aa81a875f03_720w.webp)

![img](https://pic3.zhimg.com/80/v2-e96b570c470785e19936abceee95c8ca_720w.webp)

取堆顶元素即得到最大值/最小值，将它和末尾元素交换，末尾为**有序区**。

而后将堆最末端的元素移到堆顶，向下调整，直到左右子节点都比父节点大/小

![img](https://pic2.zhimg.com/80/v2-5bbfec3cb200b9fa7efcf29fe71fc7dd_720w.webp)

![img](https://pic2.zhimg.com/80/v2-1f490e927a5d7d5e97e9609f7e99b6e5_720w.webp)

逐步扩大有序区。

#### 各种解法适用的问题

##### 单调栈

1.**连续**大于/小于当前数的个数
2.上一个大于/小于自己的数

典型题目：84（最大矩形），42（接雨水），739.下一个更高温度

##### 滑动窗口

若i<j，则end[i]<end[j]时可以考虑用滑动窗口

##### 前缀和

连续子串问题可以归约到前缀和问题。

##### 位运算

满足交换律和结合律。

异或的性质：

```cpp
a^0=a;
a^a=0;
```

n&(n-1)：可以去掉最右边的一个1。用途：1.判断n是否为2的幂次（=0） 2.判断n的二进制表示中1的个数

典型例题：136.只出现一次的数字 2859.[计算 K 置位下标对应元素的和](https://leetcode.cn/problems/sum-of-values-at-indices-with-k-set-bits/)

#### 经常犯的错误

1.善用数组的初始化数据（0等），节省计算时间



