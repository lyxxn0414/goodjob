### 微软上海Developer工具组

#### 一面

聊了不到半小时的项目，然后做了一道LRU（大概15分钟左右）

#### 二面

简单介绍了一下近期做的模拟器，面试官不是特别感兴趣，直接开始写题

题目是addOne，判断数字是否合法，然后考虑正负号，确定做加减法。单独处理边界情况(-1)，然后分类做就可以了。

做完之后面试官让把所有需要考虑到的测试情况都写一下，结果写完面试官说还不够。但时间关系，没有多问就结束了。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<string>
#include<sstream>
#include<unordered_map>
#include<set>
#include<queue>
#include<map>
#include<numeric>
#include <functional>
#include <iomanip>
#include <mutex>
#include <future>
#include <thread>

using namespace std;

bool validNum(string& value, vector<int>& arr, bool& sign) {
	if (value.size() == 0) return false;
	int start = 0;
	sign = true;
	if (!(value[0] >= '0' && value[0] <= '9')) {
		start++;
		if (value[0] == '+') {
		}
		else if (value[0] == '-') sign = false;
		else return false;
	}
	for (int i = value.size() - 1; i >= start; i--) {
		if (!(value[i] >= '0' && value[i] <= '9')) return false;
		arr.push_back(value[i] - '0');
	}
	return true;
}

string addOne(string value) {
	vector<int> arr;
	bool sign;
	if (!validNum(value, arr, sign)) return "error";
	int c = 1;
	if (sign) {
		int ind = 0;
		while (ind < arr.size() && c == 1) {
			++arr[ind];
			if (arr[ind] == 10) {
				arr[ind] = 0;
				c = 1;
			}
			else {
				c = 0;
			}
			ind++;
		}
		if (c == 1) arr.push_back(1);
	}
	else {
		if (arr.size() == 1 && arr[0] == 1) return "0";
		int ind = 0;
		while (ind < arr.size() && c == 1) {
			if (arr[ind] == 0) {
				arr[ind] = 9;
			}
			else {
				arr[ind] -= 1;
				c = 0;
			}
			ind++;
		}
	}
	string res = "";
	if (!sign) res += "-";
	for (int i = arr.size() - 1; i >= 0; i--) {
		res += to_string(arr[i]);
	}
	return res;
}

int main() {
	//int a;
	//cin >> a;
	cout << "Hello World!" << endl;
	cout << addOne("123") << endl;
	cout << addOne("-123") << endl;
	cout << addOne("-1") << endl;
	cout << addOne("456789012345643819078900987") << endl;
	cout << addOne("345rqwsdr1") << endl;
	cout << addOne("") << endl;
	cout << addOne("9999999") << endl;
	cout << addOne("300000") << endl;
	cout << addOne("+999999") << endl;
	cout << addOne("+12312-7872") << endl;
	cout << addOne("000012") << endl;
	cout << addOne("0") << endl;
}
```

#### QA

Q：你们组具体是做什么的

A：主要是做Developer工具的，比如vscode，azure service之类的。

Q：工作强度怎么样？

（被反问了）你觉得工作强度多强算强，你的预期是什么样

我说965算正常，我自己比较希望能按点上下班。他说他们算正常工作强度。。

