#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>
#include<unordered_map>
#include<set>
#include<queue>
#include<map>
#include<numeric>
#include <functional>
#include <iomanip>
using namespace std;

struct Trade {
	char symbol[12]; // 股票代码 "000001.SZ", "600000.SH"
	double price; // 成交价
	int qty; // 成交量
	int hhmmss_ms; // 时间戳 如102030123 表示 10:20:30.123
};

unordered_map<string, int> dir;
int ind = 0;
vector<vector<Trade*>> trades;
shared_ptr<int> ptr = make_shared<int>(3);

void OnTrade(const Trade* trade) {
	auto is_limited = [](int cur_time, int limited_time) {
		if (cur_time - limited_time <= 300000) {
			return true;
		}
		int minutes = limited_time % 10000000;
		int hour = limited_time / 10000000;
		if (minutes >= 5700000) {
			int remain = 300000 - (6000000 - minutes);
			if (cur_time <= (hour + 1) * 10000000 + remain) {
				return true;
			}
		}
		return false;
	};
	string name = trade->symbol;
	if (dir.find(name) == dir.end()) {
		dir[name] = ind;
		ind++;
		Trade* temp = const_cast<Trade*>(trade);
		trades.push_back({ temp });
		//printf("stock: %s, time: %d, high_price: %.2f, volume: %f, avg_price: %.8f\n", trade->symbol, temp->hhmmss_ms, temp->price, temp->qty, temp->price);
		cout << "stock:" << name << ", time:" << temp->hhmmss_ms << fixed << setprecision(2) << ", high_price:" << temp->price;
		cout << ", volume:" << temp->qty << ", avg_price:" <<fixed << setprecision(8) << temp->price << endl;
		cout.unsetf(ios::fixed);
	}
	else {
		trades[dir[name]].push_back(const_cast<Trade*>(trade));
		int ind = 0;
		double sum = 0;
		double qty = 0;
		double max_price = 0;
		while (ind < trades[dir[name]].size()) {
			if (!is_limited(trade->hhmmss_ms, trades[dir[name]][ind]->hhmmss_ms)) {
				trades[dir[name]].erase(trades[dir[name]].begin() + ind);
				continue;
			}
			qty += trades[dir[name]][ind]->qty;
			sum += trades[dir[name]][ind]->qty*trades[dir[name]][ind]->price;
			if (max_price < trades[dir[name]][ind]->price) {
				max_price = trades[dir[name]][ind]->price;
			}
			ind++;
		}
		cout << "stock:" << name << ", time:" << trade->hhmmss_ms << ", high_price:" << max_price;
		cout<< ", volume:" << qty << fixed << setprecision(8)<<", avg_price:" << sum / qty<<endl;
		cout.unsetf(ios::fixed);
	}
}

void test(Trade* trade) {
	OnTrade(trade);
	//.cout << A << ": ";
	//for (auto && i : res) printf("%d ", i);
	//cout << s << " ";
	printf("\n");
}

int main() {
	Trade* trade1 = new Trade();
	char symbol1[12] = "000001.SZ";
	strcpy_s(trade1->symbol, symbol1);
	trade1->price = 12;
	trade1->qty = 100;
	trade1->hhmmss_ms = 102030100;

	Trade* trade2 = new Trade();
	char symbol2[12] = "600000.SH";
	strcpy_s(trade2->symbol, symbol2);
	trade2->price = 7.5;
	trade2->qty = 100;
	trade2->hhmmss_ms = 102030500;

	Trade* trade3 = new Trade();
	char symbol3[12] = "000001.SZ";
	strcpy_s(trade3->symbol, symbol3);
	trade3->price = 12.01;
	trade3->qty = 100;
	trade3->hhmmss_ms = 102230250;

	Trade* trade4 = new Trade();
	char symbol4[12] = "600000.SH";
	strcpy_s(trade4->symbol, symbol4);
	trade4->price = 7.49;
	trade4->qty = 100;
	trade4->hhmmss_ms = 102230500;

	Trade* trade5 = new Trade();
	char symbol5[12] = "000001.SZ";
	strcpy_s(trade5->symbol, symbol5);
	trade5->price = 12.02;
	trade5->qty = 200;
	trade5->hhmmss_ms = 102355350;

	Trade* trade6 = new Trade();
	char symbol6[12] = "600000.SH";
	strcpy_s(trade6->symbol, symbol6);
	trade6->price = 7.48;
	trade6->qty = 200;
	trade6->hhmmss_ms = 105955500;

	Trade* trade7 = new Trade();
	char symbol7[12] = "000001.SZ";
	strcpy_s(trade7->symbol, symbol7);
	trade7->price = 12.03;
	trade7->qty = 200;
	trade7->hhmmss_ms = 102410500;

	Trade* trade8 = new Trade();
	char symbol8[12] = "600000.SH";
	strcpy_s(trade8->symbol, symbol8);
	trade8->price = 7.50;
	trade8->qty = 200;
	trade8->hhmmss_ms = 110010500;

	test(trade1);
	test(trade2);
	test(trade3);
	test(trade4);
	test(trade5);
	test(trade6);
	test(trade7);
	test(trade8);
	return 0;
}