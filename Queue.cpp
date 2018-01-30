#pragma once
#include "List.h"
#include <iostream>
using namespace std;

template<class T, class Container = List<T>>
class Queue
{
public:
	Queue()
	{}

	void Push(const T& data)
	{
		_c.PushBack(data);
	}

	void Pop()
	{
		_c.PopFrond();
	}

	size_t Size()
	{
		return _c.Size();
	}

	bool Empty()
	{
		return _c.Empty();
	}

	T& Front()
	{
		return _c.Front();
	}

	const T& Front() const
	{
		return _c.Front();
	}

	T& Back()
	{
		return _c.Back();
	}

	const T& Back() const
	{
		return _c.Back();
	}

private:
	Container _c;
};
