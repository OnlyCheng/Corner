#pragma once
#include <iostream>
using namespace std;
#include <utility>

template<class K,int M = 3>
struct BTreeNode
{
	K keys[M];
	BTreeNode<K,M>* pSub[M+1];
	BTreeNode<K,M>* _pParent;
	size_t _size;

	BTreeNode()
		:_pParent(NULL)
		,_size(0)
	{
		for(int i = 0;i <= M ;i++)
			pSub[i] = NULL;
	}
};

template<class K,int M = 3>
class BTree
{
public:
	typedef BTreeNode<K,M> Node;
	typedef Node* PNode;

	BTree()
		:_pRoot(NULL)
	{}

	bool Insert(K key)
	{
		return _Insert(_pRoot,key);
	}

private:
	pair<PNode,int> Find(PNode pRoot,K key)
	{
		if(NULL == pRoot)
			return pair<PNode,int>(NULL ,-1);
		PNode pCur = pRoot;
		PNode pPre = NULL;

		while(pCur)
		{
			int i = 0;
			while(i < pCur->_size)
			{
				if(key == pCur->keys[i])
					return pair<PNode ,int>(pCur,i);
				else if(key < pCur->keys[i])
					break;
				else
					i++;
			}
			pPre = pCur;
			pCur = pCur->pSub[i];
		}
		return pair<PNode ,int>(pPre,-1);
	}

	bool _Insert(PNode pRoot,K key)
	{
		if(pRoot == NULL)
		{
			pRoot = new Node;
			pRoot->keys[0] = key;
			pRoot->_size++;

			cout<<"The pRoot is NULL"<<endl;

			return true;
		}

		pair<PNode ,int> kp = Find(pRoot,key);
		if(kp.second > 0)//has existed
		{

			cout<<"The key has existed"<<endl;

			return false;
		}
		else
		{
			PNode pCur = kp.first;
			int size = pCur->_size;

			for(int i = size-1;i >= 0;i--)
			{
				if(pCur->keys[i] < key )
				{
					for(int j = size-1;j > i;j--)
					{
						pCur->keys[j+1] = pCur->keys[j];
					}
					pCur->keys[i+1] = key;
					pCur->_size++;
					break;
				}
					
			}
			if(pCur->_size < M)
			{
				cout<<"manzu~"<<endl;
				return true;
			}
			else
			{
				cout<<"bumanzu----"<<endl;
				return false;
			}
		}

	}

private:
	PNode _pRoot;
};
