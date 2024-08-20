### 腾讯wxg 技术架构

#### 一面

自我介绍3min，面试官特意问了一下能不能接受在深圳实习和转正，表示没问题（骗他的，其实还是有点犹豫，但它是微信诶）

直接扔过来三道算法题：

1. 手撕快排(swap+partition+sort)
2. 给定不重复的userid列表，求无放回取样n个用户的结果（n≤userid列表长度）
   A：选中的index的用户加入结果，然后swap到最后，再取的时候不取后面的就好了。
3. 2进阶版：再给一个权重数组w,表示每个用户的权重，求按权重无放回取n个用户的结果
   A：做w的前缀和，落在选中前缀和区间的index用户摘出去，相当于index及后面的前缀和都要减去w[index]。
   面试官让分析一下复杂度，时间复杂度是O(Nn)，因为每次摘掉一个用户都要O(N)的复杂度。
   问能不能把复杂度降下来，实在想不到，面试官说可以用树状数组，这个结构可以将前缀和的更新复杂度降到O（logn）.

项目：问了两段实习经历

八股：了解协程吗，用过吗（讲了用过goroutine）；讲讲I/O多路复用；消息队列不断地来用户id，这个时候怎么随机无放回取n个

QA:

Q：你们主要是做啥的

A：介绍了主要是做数据相关的，有数据分析，数据存储，在开发变更后做数据测试，做统计推断（方差，假设检验等。也有做后台开发的。技术栈比较杂，主要是C++,也有golang，java，python等

Q：你觉得你们平时强度大吗？

A：（沉默三秒）跟你之前在微软肯定不能比（笑），最近几年都不咋忙了，很多同事八点多就下班了（？？？



#### 二面

自我介绍后面试官就开始了长达50分钟的数学拷打。

1. 有很多很多上亿规模的int16数据，怎么做排序=》统计排序。每个int16分配一个空间做计数。
2. 讲讲你对哈希函数的理解（一对多映射，尽量均匀分布）
3. 设计一下string->int32的哈希函数（这题答了半天也答不好，很难做到均匀分布，最后也不知道答案是什么）
4. 设计一下random(5)=>random(7)（random(5)x5+random(5)，超过21部分舍去，再模7）
5. 知道泰勒展开吗，讲讲为什么sin能用泰勒展开做计数（不知道）
6. 一大堆数学的（我说我不知道，用的不多），密码学学过吗（没学过）

开始操作系统：

1. MMU知道吗，讲一讲
2. 怎么做cache hit优化（数据缓存=》按顺序读；指令缓存=》数据有序，做分支预测的时候就能更容易命中；多核CPU=》把某个线程绑定到一个CPU上）
3. 编译原理熟吗，用过bison吗（写过图形编译作业），做过编译器优化吗（没有）

最后讲了项目，讲到也设计了类似文件系统多级索引的路由表，讨论了一下怎么优化。

QA：

能接受来深圳吗，表示没问题（骗他的）

Q：从这次面试能感觉到，这个岗位是偏数学吗

A：我们是做数据优化的，单靠软件优化会遇到瓶颈，所以数学是门槛，数学能解决数据分析中的很多问题。



#### 三面（面委会）

聊项目30分钟。做了两道leetcode hard：

1. 给定num个people，用随机函数random(65536)从中随机抽取k个人。
2. 数组中逆序对的个数(即i<j但num[i]>num[j])

#### 四面（面委会）

上来45分钟写4道题，真的很难绷。

1、

给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [−2^31, 2^31 − 1] ，就返回 0。

假设环境不允许存储 64 位整数（有符号或无符号）。

Input: -123

Output: -321





```
int reverse(int x) {//-2^31 <= x <= 2^31 - 1
	int res = 0;
	while (x != 0) {
		if (res<INT_MIN / 10 || res>INT_MAX / 10) {
//here ? res == INT_MIN / 10 
			return 0;
		}
        res *= 10;
        if(res> INT_MAX - x%10 || res<INT_MIN - x%10){
            return 0;
        }
		res += x % 10;
		x /= 10;
	}
	return res;
}
```







2、给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

输入: "abcabcbb"

输出: 3 

解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

输入: "bbbbb"

输出: 1

解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

输入: "pwwkew"

输出: 3

解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。

 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。





```
int lengthOfLongestSubstring(string s) {
	unordered_set<char> dir;
	int l = 0;
	int r = 0;
	int maxLen = 0;
	while (r < s.size()) {
		while (r<s.size() && dir.count(s[r]) == 0) {
			dir.insert(s[r]);
			r++;
		}
		maxLen = max(maxLen, r - l);// r-l or r-l+1
		if (r == s.size()) break;
		while (s[l] != s[r]) {
			dir.erase(s[l]);
			l++;
		}
		l++;//对的

		r++;//?
	}
	return maxLen;
}
```







3、

给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

示例：

给你这个链表：

1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next; };
 */}
ListNode* reverseList(ListNode* head) {
	if (!head->next) return head;
	ListNode* pre = head;
	ListNode* cur = head->next;
	head->next = nullptr;
	while (cur) {
		ListNode* next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}

ListNode* reverseKGroup(ListNode* head, int k) {
	ListNode* dummy = new ListNode();// here 内存泄漏
	ListNode* last = dummy;
	ListNode* cur = head;
	while (cur) {
		int count = 1;
		ListNode* new_head = cur;
		while (cur && count < k) {
			cur = cur->next;
			count++;
		}
		ListNode* next = nullptr;
		if (cur) {
			next = cur->next;
			cur->next = nullptr;
		}
		last->next = reverseList(new_head);
		last = new_head;
		cur = next;
	}
    ListNode* res = dummy->next;
    delete dummy;
    dummy = nullptr;
	return res;
}
```





# 

​            4、     

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：

输入：n = 3

输出：["((()))","(()())","(())()","()(())","()()()"]



示例 2：

输入：n = 1

输出：["()"]





```
vector<string> generateParenthesis(int n) {
	vector<vector<string>> dp(n + 1);
	dp[0] = { {""} };
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			for (auto s1 : dp[j]) {
				for (auto s2 : dp[i - j - 1]) {
					dp[i].push_back("(" + s1 + ")" + s2);
				}
			}
		}
	}
	return dp[n];
}

// here

//a -> +A -> (a->c)
//b (丢包了) ？

// here
// TCP 报头， seq、ack 、flag in{ SYN、ACK ...}
// c -> s
// 1: seq = client_seq SYN=1
// s -> c
// 2: seq = server_seq, ack = client_seq+1 ACK=1 SYN=1
// c -> s
// 3: ACK=1
// c:

// TLS ?? 

// s -> c
// 1 : s 公钥

// c -> s
// 2: 生成随机 key

//  
```

问了在微软做的在线画板，其中有一些网络同步的细节答得不是很好。



然后问了如上的一些网络问题，可以说答得一塌糊涂。

包括HTTPS建立连接过程（tcp+tls），以及其中的报文细节。

但由于对tls真的一窍不通可以说是一窍不通。



epoll的过程，和poll相比的好处（省掉copy和两次遍历的开销）。

它的机制：事件驱动+回调进就序列表。



最后提问了关于网卡如何找到对应应用进程的问题（网络，我的一生之敌），绕了一大圈想起来直接通过端口号找应用不就行了！



用什么来处理多个数据库？答了可以开单个进程的一个线程库，问为什么不能用进程池，答进程开销大。尤其是在切换页表上的开销。



