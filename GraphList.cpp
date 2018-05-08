#include <iostream>
using namespace std;
#include <vector>
#include <assert.h>

template<class V>
struct Edge
{
	V _src;
	V _dest;
	int _weight;
	struct Edge* _pNext;
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

private:
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

void TestListGraph()
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

int main()
{
  TestListGraph();
  return 0;
}
	
