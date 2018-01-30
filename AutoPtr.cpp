#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class A
{
public:
	int _a;
	int _b;
	int _c;
};

//管理指针:资源转移---两个对象公用同一块空间的时候（拷贝构造和赋值）
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{
			cout << "AutoPtr()" << endl;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}

	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

void FunTest()
{
	int *p = new int;
	*p = 10;
	delete p;

	AutoPtr<int> ap1(new int);
	*ap1 = 10;

	AutoPtr<A> ap2(new A);
	ap2->_a = 1;

}
