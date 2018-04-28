#include <iostream>
using namespace std;

template <class V,class W,bool IsDirect = false >
class Graph 
{ 
public: 
Graph(V* array, size_t size) 
	: _v(array, array+size) 
{ 
	_edges.resize(size); 
	for(size_t i = 0; i < size; ++i) 
		_edges[i].resize(size); 
} 

// 获取顶点元素在其数组中的下标 
size_t GetIndexOfV(const V& v)
{
	for(size_t i = 0;i < _v.size();i++)
	{
		if(v == _v[i])
			return i;
	}
	cout<<"顶点非法"<<endl;
}

// 获取顶点的度 
size_t GetDevOfV(const V& v)
{
	size_t count = 0;
	size_t size = _v.size();
	size_t index = GetIndexOfV(v);
	//出度
	for(size_t i = 0; i<size;i++)
	{
		if(_edges[index][i] > 0)
			count++;
	}
	if(IsDirect)
	{	
		//入度
		for(size_t i = 0;i<size; i++)
		{
			if(_edges[i][index] > 0)
				count++;
		}
	}
	return count;
}

// 添加顶点v1与v2对应的权值为weight的边 
void AddEdge(const V& v1, const V& v2, const W& weight)
{
	int index1 = GetIndexOfV(v1);
	int index2 = GetIndexOfV(v2);
	_edges[index1][index2] = weight;
	if(!IsDirect)
	{
		_edges[index2][index1] = weight;
	}
}

// 图的打印 
void PrintGraph()
{
	size_t size = _v.size();
	for(size_t i = 0;i<size; i++)
	{
		for(size_t j = 0; i<size; j++)
		{
			cout<<_edges[i][j]<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;
}

private: 
	vector<V> _v; 
	vector< vector<W> > _edges; 
}; 

void testmutrix()
{
	char buf[] = {'A','B','C','D','E'};
	Graph<char,int> g(buf,sizeof(buf)/sizeof(buf[0]));
	g.AddEdge('A','B',25);
	g.AddEdge('B','E',20);
	g.AddEdge('C','D',10);
	g.AddEdge('C','B',40);
	g.AddEdge('E','A',30);

	g.PrintGraph();
	size_t dev = g.GetDevOfV('A');
	cout<< "A的度为："<<dev<<endl;
}
