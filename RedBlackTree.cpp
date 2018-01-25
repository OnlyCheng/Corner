#pragma once
#include <iostream>
using namespace std;

enum COLOR
{
	RED,
	BLACK
};

template <typename T,typename V>
struct RBTreeNode
{
	RBTreeNode()
	{}

	RBTreeNode(T key, V value,COLOR color = RED)
		:_key(key)
		, _value(value)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _color(color)
	{}

	T _key;
	V _value;
	RBTreeNode<T, V>* _pLeft;
	RBTreeNode<T, V>* _pRight;
	RBTreeNode<T, V>* _pParent;
	COLOR _color;
};

template <typename T, typename V>
class RBTree
{
	typedef RBTreeNode<T, V> Node;
	typedef Node* PNode;

public:
	RBTree()
		:_pRoot(NULL)
	{}

	void Insert(T key, V value)
	{
		_Insert(_pRoot, key, value);
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

	bool IsRBTree()
	{
		if (_pRoot->_color != BLACK)
		{
			cout << "违反性质二" << endl;
			return false;
		}
		
		int BlackCount = 0;
		int Count = 0;
		PNode pCur = _pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				BlackCount++;
			pCur = pCur->_pLeft;
		}

		return _IsRBTree(_pRoot, Count, BlackCount);
		
	}

private:

	bool _IsRBTree(PNode Root,int Count,int BlackCount)
	{
		if (NULL == Root)
			return true;

		PNode pCur = Root;
		if (BLACK == pCur->_color)
			Count++;
		else
		{
			if (RED == pCur->_pParent->_color)
			{
				cout << "有相连的两个红色结点，违反了性质3" << endl;
				return false;
			}
		}
		if (NULL == pCur->_pLeft && NULL == pCur->_pRight)
		{
			if (Count != BlackCount)
			{
				cout << "各路经的黑色结点数不相等，违反了性质4" << endl;
				return false;
			}
			else
				return true;
		}

		_IsRBTree(Root->_pLeft, Count, BlackCount) && _IsRBTree(Root->_pRight, Count, BlackCount);
			
	}

	void _InOrder(PNode& Root)
	{
		if (NULL == Root)
			return;
		_InOrder(Root->_pLeft);
		cout << "<" << Root->_key << "," << Root->_value << ">" << endl;
		_InOrder(Root->_pRight);
	}

	void RotateL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		//更新pParent的右
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		//更新PSubR的左和双亲
		pSubR->_pLeft = pParent;

		PNode parent = pParent->_pParent;
		pSubR->_pParent = parent;

		//更新pParent的双亲
		//pParent为根
		if (parent == NULL)
			_pRoot = pSubR;

		//pParent为双亲的左
		else if (pParent == parent->_pLeft)
			parent->_pLeft = pSubR;
		//pParent为双亲的右
		else if (pParent == parent->_pRight)
			parent->_pRight = pSubR;

		pParent->_pParent = pSubR;
	}

	void RotateR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		//更新pParent的左
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		//更新pSubL的位置
		PNode parent = pParent->_pParent;
		pSubL->_pRight = pParent;
		pSubL->_pParent = parent;

		//更新pParent的双亲结点的指向
		//pParent为根
		if (NULL == parent)
			_pRoot = pSubL;

		//pParent为双亲结点的左孩子
		else if (pParent == parent->_pLeft)
			parent->_pLeft = pSubL;

		//pParent为双亲结点的右孩子
		else if (pParent == parent->_pRight)
			parent->_pRight = pSubL;

		pParent->_pParent = pSubL;
	}

	bool _Insert(PNode& Root, T key, T value)
	{
		//情况一
		if (NULL == Root)
		{
			Root = new Node(key, value);
			Root->_color = BLACK;
			return true;
		}

		PNode pCur = Root;
		PNode pParent = NULL;

		//找到插入的位置
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

		//插入结点
		pCur = new Node(key, value);
		if (key < pParent->_key)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
			
		pCur->_pParent = pParent;

		//情况二----p为黑
		if (pParent->_color == BLACK)
			return true;

		PNode GrandFather = pParent->_pParent;
		if (pParent == GrandFather->_pLeft)
		{
			PNode Uncle = GrandFather->_pRight;
			while (pParent && pParent->_color == RED)
			{
				//情况三----p为红，g为黑，u存在且为红
				if (Uncle && Uncle->_color == RED && pParent->_color == RED)
				{
					Uncle->_color = BLACK;
					pParent->_color = BLACK;
					GrandFather->_color = RED;

					pCur = GrandFather;
					pParent = pCur->_pParent;
				}

				else if (pParent->_color == RED)
				{
					//情况五----P为红，g为黑,U不存在或存在且为黑色 pCur为右
					if (pCur == pParent->_pRight)
					{
						RotateL(pParent);
						swap(pCur, pParent);
					}

					RotateR(GrandFather);
					GrandFather->_color = RED;
					pParent->_color = BLACK;
				}
			}
		}
		else
		{
			PNode Uncle = GrandFather->_pLeft;
			while (pParent && pParent->_color == RED)
			{
				//情况三----p为红，g为黑，u存在且为红
				if (Uncle && Uncle->_color == RED && pParent->_color == RED)
				{
					Uncle->_color = BLACK;
					pParent->_color = BLACK;
					GrandFather->_color = RED;

					pCur = GrandFather;
					pParent = pCur->_pParent;
				}

				else if (pParent->_color == RED)
				{
					//情况五----P为红，g为黑,U不存在或存在且为黑色 pCur为右
					if (pCur == pParent->_pLeft)
					{
						RotateR(pParent);
						swap(pCur, pParent);
					}

					//情况四----P为红，g为黑,U不存在或存在且为黑色 pCur为左
					RotateL(GrandFather);
					GrandFather->_color = RED;
					pParent->_color = BLACK;
				}
			}
		}
		Root->_color = BLACK;

		return true;
	}

private:
	PNode _pRoot;
};
