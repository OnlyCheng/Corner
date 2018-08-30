#include<iostream>
using namespace std;

int main() {
	int a, b, t, k, i;
	int book[3000] = { 0 }; //标记第一个余数
	int count[100] = { 0 };// 记录循环小数
	cin >> a >> b;

	count[0] = a / b; // 小数点左边的数
	t = a%b; // 余数
	book[t] = 1; // 记下第一个余数

	count[1] = (t * 10) / b; // 小数点后一位数
	t = (t * 10) % b; //继续求余

	k = 2;
	while (book[t] == 0) {  //循环直到出现 第一次出现 的 余数
		count[k] = (t * 10) / b;
		t = (t * 10) % b;
		k++;
	}

	cout << count[0] << ".(";
	for (i = 1; i < k; i++)cout << count[i];
	cout << ")";
	return 0;

}
