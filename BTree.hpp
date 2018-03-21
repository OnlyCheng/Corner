#pragma once
#include <iostream>
using namespace std;
#include <utility>

template<class K, int M = 3>
struct BTreeNode
{
	K keys[M];
	BTreeNode<K, M>* pSub[M + 1];
	BTreeNode<K, M>* _pParent;
	size_t _size;

	BTreeNode()
		:_pParent(NULL)
		, _size(0)
	{
		for (int i = 0; i <= M; i++)
			pSub[i] = NULL;
	}
};

template<class K, int M = 3>
class BTree
{
public:
	typedef BTreeNode<K, M> Node;
	typedef Node* PNode;

	BTree()
		:_pRoot(NULL)
	{}

	bool Insert(K key)
	{
		pair<PNode, int> kp = Find(_pRoot, key);
		if (kp.second > 0)//已经存在
			return false;

		_Insert(kp.first, key, NULL);
		if (!Check(kp.first))
				Division(kp.first);
		
		return true;
	}

	void PrintBTree()  //后面加的
	{
		_PrintBTree(_pRoot);
		cout << endl;
	}

	size_t Size()
	{
		return _pRoot->_size;
	}

private:
	void _PrintBTree(PNode pRoot)  //加的
	{
		if (pRoot)
		{
			for (int i = 0; i < pRoot->_size; i++)
			{
				_PrintBTree(pRoot->pSub[i]);
				cout << pRoot->keys[i] << " ";
			}
			_PrintBTree(pRoot->pSub[pRoot->_size]);
		}
	}
	bool _Insert(PNode& pCur, K key,PNode Child)
	{
		if (pCur == NULL)//树为空
		{
			pCur = new Node;
			pCur->keys[0] = key;
			pCur->_size++;
			_pRoot = pCur;

			cout << "The pRoot is NULL" << endl;
			return true;
		}

		int size = pCur->_size;
		int i = size;
		//利用插入排序算法思想将关键字插入
		if (pCur->keys[size - 1] > key)
		{
			pCur->pSub[size + 1] = pCur->pSub[size];
			for (i = size - 1; i >= 0; i--)
			{
				if (pCur->keys[i] > key)
				{
					pCur->keys[i + 1] = pCur->keys[i];
					pCur->pSub[i + 1] = pCur->pSub[i];
				}
				else
					break;
			}
			i++;
		}
		pCur->keys[i] = key;
		pCur->pSub[i + 1] = Child;
		pCur->_size++;
		//for (int i = size - 1; i >= 0; i--)
		//{
		//	if (pCur->keys[i] < key)
		//	{
		//		for (int j = size - 1; j > i; j--)
		//		{
		//			pCur->keys[j + 1] = pCur->keys[j];
		//		}
		//		pCur->keys[i + 1] = key;
		//		pCur->pSub[i + 2] = Child;
		//		pCur->_size++;
		//		break;
		//	}
		//}
		return true;
	}

	bool Check(PNode pCur)
	{
		return pCur->_size < M;
	}

	void Division(PNode& Cur)
	{
		PNode pCur = Cur;
		size_t size = pCur->_size;
		size_t mid = size >> 1;
		
		while (size == M)
		{
			//将中间位置元素后边的关键字搬移到一个新的结点中去
			PNode NewNode = new Node;
			K key = pCur->keys[mid];
			size_t i = 0;
		
			for(i = mid + 1; i < size; i++)//搬移关键字及孩子
			{
				NewNode->keys[NewNode->_size] = pCur->keys[i];
				NewNode->pSub[NewNode->_size++] = pCur->pSub[i];
			}
			NewNode->pSub[NewNode->_size] = pCur->pSub[i];//孩子比关键字多搬一次
			pCur->_size = size - NewNode->_size - 1;

			//将中间位置的关键字往双亲位置提
			PNode pParent = pCur->_pParent;
			if (pParent == NULL)//pCur为根
			{
				pParent = new Node;
				pParent->keys[0] = key;
				pParent->_size = 1;

				pParent->pSub[0] = pCur;
				pCur->_pParent = pParent;
				pParent->pSub[1] = NewNode;
				NewNode->_pParent = pParent;

				_pRoot = pParent;

				break;
			}
			else
			{
				_Insert(pParent, key, NewNode);
				pCur = pCur->_pParent;
				size = pCur->_size;
			}
		}
	}

	pair<PNode, int> Find(PNode pRoot, K key)
	{
		if (NULL == pRoot)
			return pair<PNode, int>(NULL, -1);
		PNode pCur = pRoot;
		PNode pPre = NULL;

		while (pCur)
		{
			size_t i = 0;
			while (i < pCur->_size)
			{
				if (key == pCur->keys[i])
					return pair<PNode, int>(pCur, i);
				else if (key < pCur->keys[i])
					break;
				else
					i++;
			}
			pPre = pCur;
			pCur = pCur->pSub[i];
		}
		return pair<PNode, int>(pPre, -1);
	}

private:
	PNode _pRoot;
};

