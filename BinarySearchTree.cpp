#pragma once
#include <iostream>
using namespace std;

template <typename T,typename V>
struct BSTreeNode
{
	BSTreeNode()
	{}

	BSTreeNode(T key, V value)
		:_key(key)
		, _value(value)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
	{}

	T _key;
	V _value;
	BSTreeNode<T, V>* _pLeft;
	BSTreeNode<T, V>* _pRight;
	BSTreeNode<T, V>* _pParent;
};

template <typename T,typename V>
class BSTree
{
	typedef BSTreeNode<int, int> Node;
	typedef Node* PNode;

public:
	BSTree()
		:_pRoot(NULL)
	{}

	void Insert(T key, V value)
	{
		_Insert(_pRoot, key, value);
	}

	void Delete(T key, V value)
	{
		_Delete(_pRoot, key);
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

private:
	PNode Find(PNode& Root,T key,V value)
	{
		PNode pCur = Root;
		while (pCur)
		{
			if (key < pCur->_key)
				pCur = pCur->_pLeft;
			else if (key > pCur->_key)
				pCur = pCur->_pRight;
			else
				return pCur;
		}
		return NULL;
	}

	/*PNode FirstOfInOrder(PNode& Root)
	{
		if (NULL == Root)
			return NULL;

		PNode pCur = Root;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}*/

private:
	void _InOrder(PNode& Root)
	{
		if (NULL == Root)
			return;
		_InOrder(Root->_pLeft);
		cout << "<" << Root->_key << "," << Root->_value << ">" << endl;
		_InOrder(Root->_pRight);
	}

	bool _Insert(PNode& Root, T key, V value)
	{
		if (NULL == Root)
		{
			Root = new Node(key, value);
			return true;
		}

		PNode pCur = Root;
		PNode pParent = NULL;

		while (pCur)
		{
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}

			else if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}

		pCur = new Node(key, value);

		if (key < pParent->_key)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		pCur->_pParent = pParent;
		return true;
	}

	bool _Delete(PNode& Root, T key)
	{
		//查找Del在二叉搜索树中的位置,用pPre标记其双亲
		PNode pCur = Root;
		PNode pPre = NULL;
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pPre = pCur;
				pCur = pCur->_pLeft;
			}
			else if (key > pCur->_key)
			{
				pPre = pCur;
				pCur = pCur->_pRight;
			}
			else
				break;
		}

		if (NULL == pCur)//不存在
			return false;

		//删除结点
		PNode Del = pCur;

		if (Del == Root && NULL == Root->_pLeft && NULL == Root->_pRight)//为根
		{
			delete Root;
			Root = NULL;
			return true;
		}

		if (NULL == Del->_pLeft)//左子树为空
		{
			if (Del == pPre->_pLeft)
				pPre->_pLeft = Del->_pRight;
			else
				pPre->_pRight = Del->_pRight;

			delete Del;
			return true;
		}
		else if (NULL == Del->_pRight)//右子树为空
		{
			if (Del == pPre->_pLeft)
				pPre->_pLeft = Del->_pLeft;
			else
				pPre->_pRight = Del->_pLeft;

			delete Del;
			return true;
		}

		//左右子树都存在---在右子树中找中序遍历的第一个结点来替代该结点
		//Del = FirstOfInOrder(pCur->_pRight);
		pPre = Del;
		Del = Del->_pRight;
		while (Del->_pLeft)
		{
			pPre = Del;
			Del = Del->_pLeft;
		}
		pCur->_key = Del->_key;

		if (Del == pPre->_pLeft)
			pPre->_pLeft = Del->_pRight;
		else
			pPre->_pRight = Del->_pRight;

		delete Del;
		return true;
	}
private:
	PNode _pRoot;
};
