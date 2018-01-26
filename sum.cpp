#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//int Sum(int n)
//{
//	return (1 + n)*n >> 1;
//}
//
//int Sum(int n)
//{
//	int sum = 0;
//	while (n)
//		sum += n--;
//	return sum;
//}
//
//int Sum(int n)
//{
//	if (0 == n)
//		return 0;
//	else
//		return n + Sumof1ToN(n - 1);
//}
//
//int Sumof1ToN1(int n)
//{
//	return (n > 0) ? (n + Sumof1ToN1(n - 1)) : 0;
//}

class Sum
{
public:
	Sum()//构造函数
	{
		n++;
		_sum += n;
	}
	static int sum()//类的静态成员函数
	{
		return _sum;
	}
private:
	static int n;
	static int _sum;
};
//类外初始化类的静态成员函数
int Sum::n = 0;
int Sum::_sum = 0;

void Test()
{
	Sum* p = new Sum[5];
	cout << Sum::sum() << endl;
	delete[] p;
}

int main()
{
	int ret = 0;
	Test();
	//ret = Sum(5);
	cout << ret << endl;
	return 0;
}
