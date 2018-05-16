#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <stack>
#include <assert.h>
#include <queue>
#include "UFS.hpp"
#include <queue>

template<class V>
struct Edge
{
	V _src;
	V _dest;
	int _weight;
	struct Edge* _pNext;
};

template <class V>
struct Less
{
	bool operator() (const V& v1,const V& v2)
	{
		return v1->_weight < v2->_weight;
	}
};

template<class V,bool IsDirect = false>
class Graph
{
	typedef struct Edge<V> EdgeNode;
	typedef EdgeNode* pEdge;
public:
	Graph(V* arr,int size)
		:_v(arr,arr+size)
	{
		_edges.resize(size);
	}

	bool Add(const V & v1, const V & v2,int weight)
	{
		int i1 = GetIndexOfV(v1);
		int i2 = GetIndexOfV(v2);

		assert(i1 >= 0 && i2 >= 0);
		pEdge newEdge = new EdgeNode;
		newEdge->_src = v1;
		newEdge->_dest = v2;
		newEdge->_weight = weight;
		newEdge->_pNext = _edges[i1];
		_edges[i1] = newEdge;

		if(!IsDirect)
		{
			pEdge Edge = new EdgeNode;
			Edge->_src = v2;
			Edge->_dest = v1;
			Edge->_weight = weight;
			Edge->_pNext = _edges[i1];
			_edges[i2] = Edge;
		}
		return true;
	}

	int GetDevOfV(const V & v)
	{
		int index = GetIndexOfV(v);
		if(index < 0)
			return 0;
		
		int count = 0;
		pEdge pCur = _edges[index];
		//出度
		while(pCur)
		{
			count++;
			pCur = pCur->_pNext;
		}
		if(IsDirect)
		{
			//入度
			int size = _v.size();
			for(int i=0; i<size; i++)
			{
				pCur = _edges[i];
				while(pCur)
				{
					if(pCur->_dest == v)
						count++;
					pCur = pCur->_pNext;
				}
			}
		}
		return count;
	}

	void PrintGraph()
	{
		int size = _v.size();
		if(size < 0)
			return;

		for(int i=0; i<size; i++)
		{
			cout<<_v[i]<<": ";
			pEdge pCur = _edges[i];
			while(pCur)
			{
				cout<<"<"<<pCur->_src<<"-->"<<pCur->_dest<<">  ";
				pCur = pCur->_pNext;
			}
			cout<<endl;
		}
	}

	void BFS(const V & v)
	{
		int index = GetIndexOfV(v);
		if(index < 0)
			return;
		
		vector<V> arr;
		queue<V> q;
		q.push(v);
		while(!q.empty())
		{
			V temp = q.front();
			q.pop();
			if(Find(arr,temp) >= 0)
				continue;
			arr.push_back(temp);
			index = GetIndexOfV(temp);
			pEdge pCur = _edges[index];
			while(pCur)
			{
				q.push(pCur->_dest);
				pCur = pCur->_pNext;
			}
		}

		for(int i = 0; i < _v.size();i++)
		{
			if(Find(arr,_v[i]) < 0)
				arr.push_back(_v[i]);
		}

		for(int i = 0; i<arr.size(); i++)
		{
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}

	void DFS(const V& v)
	{
		int index = GetIndexOfV(v);
		if(index < 0)
			return;

		vector<V> arr;
		stack<V> s;
		pEdge pCur = _edges[index];
		s.push(v);

		int size = _v.size();
		int i = index;
		do
		{
			while(!s.empty())
			{
				V temp = s.top();
				s.pop();
				if(Find(arr,temp) >= 0)//已经遍历过了
					continue;
				arr.push_back(temp);
				pCur = _edges[i];
				while(pCur)
				{
					s.push(pCur->dest);
					pCur = pCur->_pNext;
				}
			}
			i++;

		}while(i<size);
	}

	vector<pEdge> Kruskal()
	{
		int size = _v.size();
		V arr[size] = {0};

		for(int i = 0; i<size; i++)
			arr[i] = _v[i];

		priority_queue <pEdge,vector<pEdge>,Less> > heap;
		for(int i = 0; i<size; i++)
		{
			pEdge pCur = _edges[i];
			while(pCur)
			{
				heap.push(pCur);
				pCur = pCur->_pNext;
			}
		}

		UFS<V> ufs(arr,size);
		vector<pEdge> res;
		
		int count = 0;
		while(res.size() < size-1 || !heap.empty())
		{
			pEdge min = heap.top();
			heap.pop();
			ufs.UnionSet(min->_src,min->_dest);
			int root1 = ufs.Find(min->_src);
			int root2 = ufs.Find(min->_dest);
			if(root1 == root2)
				continue;
			res.push_back(min);
		}

	}
private:
	int Find(vector<V> & arr,V data)
	{
		for(int i = 0; i<arr.size(); i++)
		{
			if(data == arr[i])
				return i;
		}
		return -1;
	}
	int GetIndexOfV(const V & v)
	{
		int size = _v.size();
		if(size <=0 )
			return -1;

		for(int i=0; i<size; i++)
		{
			if(_v[i] == v)
				return i;
		}
		return -1;
	}
private:
	vector<V> _v;
	vector<pEdge> _edges;
};

void TestList()
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
	g.BFS('A');
	typedef Edge* pEdge;

	vector<pEdge> ret = g.Kruskal();
	size = ret.size();
	cout<< "kruskal"<<endl;
	for(int i = 0;i<size; i++)
	{
		cout<< "<"<<ret[i]->_src<<","<<ret[i]->_dest<<">"<<"  ";
	}
	count<<endl;
}

	
