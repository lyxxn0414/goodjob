## 专题总结

### 树

#### DFS

主要是非递归法。非递归的本质是用一个栈来模拟递归的顺序，保证遍历到栈顶的元素时，在其之前应该遍历到的数字都遍历完了。

##### 后序遍历

理论来上来说每个节点需要入栈两次（确保左右子树都遍历完成。）可以采用一个trick：用一个pre节点记录上一个遍历过的节点，对于后序遍历来说，应该 是其右子节点||它的右子树为空 时它就可以出栈了，否则继续遍历右子树。

```cpp
vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        TreeNode* pre = nullptr;
        while(root||!stk.empty()){
            while(root){
                stk.push(root);
                root=root->left;
            }
            root = stk.top();
            if(!root->right||pre == root->right){
                res.push_back(root->val);
                pre = root;
                stk.pop();
                root=nullptr;
            }
            else{
                root=root->right;
            }
        }
        return res;
    }
```

先序遍历和中序基本同理。

#### BFS

法1：常规做法。用**队列**存上一层的层次遍历结果，顺次加入自己的左右子节点。

法2：DFS。由于DFS本身就可以保证每层的节点是从左向右被访问的，因此可以**保留每层的高度**，每层用一个队列顺次记录，最后pop出来



[117. 填充每个节点的下一个右侧节点指针 II ](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/description/)

链表问题需要保存头/尾的情况，可以考虑用一个哨兵节点。

法1：迭代：如果第i层已经完成next操作，则第i+1层可以顺藤摸瓜串起来。

法2：用DFS的方式做BFS：

先序遍历可以保证**同一层中，在自己前面的节点一定会先被访问**。

因此可以用一个vector记录每一层中最后一个遍历到的节点，DFS递归时将深度记录在内。

每次遍历到当前节点时，判断是否为该层最左边的节点，不是则更新上一个节点的next。



### 图

#### 并查集

通过一个数组来保存节点的parent（排序后，最靠前的那个做parent），以及一个size数组。

由于大帮主一定是知道自己底下有多少人的（每次merge时都会统计），因此合并时大帮主仍然可以知道合并后的人数，因此通过更新size，最终从大帮主中得到帮内的成员数量。

```C++
		int count=n;
		vector<int> fa(n);
		iota(fa.begin(),fa.end(),0);
		vector<int> size(n,1);
        function<int(int)> find;
        function<void(int,int)> merge;
        find=[&](int i){
            return fa[i]==i? i:(fa[i]=find(fa[i])); //用于查找根节点
        };
        merge = [&](int x,int y){ //用于合并
            x=find(x);
            y=find(y);
            if(x!=y){
                fa[y]=x;
                size[x]+=size[y];
                count--;
            }
        };
        for(auto c:connections){
            if(c[0]>c[1]) swap(c[0],c[1]);
            merge(c[0],c[1]);
        }
```

### 回溯+dfs

#### 典型例题

47.带剪枝的全排列

难点主要是去重的过程：确保**在该位置**，**重复的数只取1次**（已经在排列里的数不算）

即如下关键代码：

```cpp
            if(vis[i] || (i>0 && nums[i-1]==nums[i] && !vis[i-1])){
                continue;
            }
```



[207. 课程表 - 力扣（LeetCode）](https://leetcode.cn/problems/course-schedule/description/)

判断成环：vis[i]标记三种状态：未学习，正在学习，已学习。如果在学习前继课程时遇到正在学习，则已经成环。

[287. 寻找重复数 - 力扣（LeetCode）](https://leetcode.cn/problems/find-the-duplicate-number/)