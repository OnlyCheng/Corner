#pragma once
#include <iostream>
using namespace std;
#include <vector>

template <class V>
class UFS
{
public:
	UFS(V* arr,int size)
		:_arr(arr,arr+size)
	{
		_set.resize(size,-1);
	}

	bool UnionSet(const V& v1, const V& v2)
	{
		int i1 = Find(v1);
		int i2 = Find(v2);
		if(i1 < 0 || i2 < 0)
			return false;
		if(i1 == i2)
			return true;
		else
		{
			_set[i2] = i1;
			return true;
		}
	}

	int Find(const V& v)
	{
		int index = GetIndex(v);
		if(index < 0)
			return -1;

		int pos = _set[index];
		while(pos >= 0)
		{
			index = pos;
			pos = _set[index];
		}
		return index;
	}

private:
	int GetIndex(const V& v)
	{
		int size = _arr.size();
		if(size <= 0)
			return -1;
		for(int i = 0; i<size; i++)
		{
			if(_arr[i] == v)
				return i;
		}
		return -1;
	}

private:
	vector<V> _arr;
	vector<int> _set;
	
};

void test()
{
	char arr[] = {'A','B','C','D','E','F'};
	int size = sizeof(arr)/sizeof(arr[0]);
	UFS<char> ufs(arr,size);
	ufs.UnionSet('A','B');
	ufs.UnionSet('C','B');
	ufs.UnionSet('E','F');
	ufs.UnionSet('D','F');
	ufs.UnionSet('D','E');

	int i = ufs.Find('A');
	cout<<"A:"<<i<<endl;
	i = ufs.Find('B');
	cout<<"B:"<<i<<endl;
	i = ufs.Find('C');
	cout<<"C:"<<i<<endl;
	i = ufs.Find('D');
	cout<<"D:"<<i<<endl;
	i = ufs.Find('E');
	cout<<"E:"<<i<<endl;
	i = ufs.Find('F');
	cout<<"F:"<<i<<endl;
}
