#include <iostream>
using namespace std;

//整除3
int exa_div_3_count(int l, int r)
{
	if (l < 1 ||r < 1|| r > 100000000||r<l)
		return 0;
	int count = 0;
	int index = 1;
	int num = 0;
	for (int i = 0; i < l; i++)
	{
		num = num * 10 + index;
		index++;
	}
	
	for (int i = 0; i < r; i++)
	{
		num = num * 10 + index;
		index++;
		if (num % 3 == 0)
			count++;
	}
	return count;
}

int main()
{
	int l;
	int r;
	cin >> l >> r;
	int ret = exa_div_3_count(l, r);
	cout << ret << endl;
	return 0;
}

//
//int main()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
//	int * p = arr;
//	*(p++) += 89;
//	cout << *p << endl;//2
//	int a = *(++p);
//	cout << a<<endl;//3
//}

//对象模型
//class A
//{
//public:
//	A()
//	{
//		cout << "A()" << endl;
//	}
//
//	~A()
//	{
//		cout << "~~A()" << endl;
//	}
//};
//
//class B:public A
//{
//public:
//	B(A& a)
//		:_a(a)
//	{
//		cout << "B()" << endl;
//	}
//
//	~B()
//	{
//		cout << "~~B()" << endl;
//	}
//
//private:
//	A _a;
//};
//
//int main()
//{
//	A a;
//	B b(a);
//	return 0;
//}
