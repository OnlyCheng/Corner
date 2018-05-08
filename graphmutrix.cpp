#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <assert.h>

template<class V, bool IsDirect = false>
class Graph
{
public:
	Graph(V* arr, int size)
		:_v(arr, arr + size)
	{
		_edges.resize(size);
		for (int i = 0; i < size; i++)
		{
			_edges[i].resize(size);
		}
	}

	bool Add(const V& v1, const V& v2, int weight)
	{
		int i1 = GetIndexOfV(v1);
		int i2 = GetIndexOfV(v2);
		assert(i1 >= 0 && i2 >= 0);

		_edges[i1][i2] = weight;
		if (!IsDirect)
			_edges[i2][i1] = weight;
		return true;
	}

	int GetDevOfV(const V& v)
	{
		int size = _v.size();
		if (size == 0)
			return 0;
		int count = 0;
		int index = GetIndexOfV(v);
		if (index >= 0)
		{
			for (int i = 0; i<size; i++)
			{
				if (_edges[index][i] != 0)
					count++;
			}
			if (IsDirect)
			{
				for (int i = 0; i<size; i++)
				{
					if (_edges[i][index] != 0)
						count++;
				}
			}
		}
		return count;
	}

	void PrintGraph()
	{
		int size = _v.size();
		if (size == 0)
			return;
		for (int i = 0; i<size; i++)
		{
			for (int j = 0; j < size; j++)
				printf("%-2d  ", _edges[i][j]);
			cout << endl;
		}
	}
private:
	int GetIndexOfV(const V& v)
	{
		int size = _v.size();
		if (size == 0)
			return -1;
		for (int i = 0; i<size; i++)
		{
			if (v == _v[i])
				return i;
		}
		return -1;
	}
private:
	vector<V> _v;
	vector<vector<int> > _edges;
};

void TestMutrix()
{
	char arr[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
	int size = sizeof(arr) / sizeof(arr[0]);
	Graph<char> g(arr,size);
	g.Add('A', 'B', 10);
	g.Add('A', 'D', 20);
	g.Add('C', 'B', 40);
	g.Add('E', 'F', 10);
	g.Add('F', 'D', 60);
	g.Add('F', 'B', 50);

	int dev = g.GetDevOfV('A');
	cout << "The dev of A is: " << dev << endl;
	g.PrintGraph();
}
