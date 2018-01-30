#pragma once
#include "Vector.h"
#include <iostream>
using namespace std;

template <class T,class Container=Vector<T>>
class Stack
{
public:
	Stack()
	{}

	void Push(const T& data)
	{
		_c.PushBack(data);
	}

	void Pop()
	{
		_c.PopBack();
	}

	size_t Size()const
	{
		return _c.Size();
	}

	bool Empty()const
	{
		return _c.Empty();
	}

	T& Top()
	{
		return _c.Back();
	}

	const T& Top()const
	{
		return _c.Back();
	}
private:
	Container _c;
};
