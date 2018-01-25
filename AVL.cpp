#pragma once
#include <iostream>
using namespace std;

template <typename T, typename V>
struct AVLTreeNode
{
	AVLTreeNode()
	{}

	AVLTreeNode(T key, V value)
		:_key(key)
		, _value(value)
		, _bf(0)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
	{}

	T _key;
	V _value;
	int _bf;
	AVLTreeNode<T, V>* _pLeft;
	AVLTreeNode<T, V>* _pRight;
	AVLTreeNode<T, V>* _pParent;
};

template <typename T, typename V>
class AVLTree
{
	typedef AVLTreeNode<int, int> Node;
	typedef Node* PNode;

public:
	AVLTree()
		:_pRoot(NULL)
	{}

	void Insert(T key, V value)
	{
		_Insert(_pRoot, key, value);
	}

	void Delete(T key, V value)
	{
		_Delete(_pRoot, key, value);
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

	bool Isbalance()
	{
		return _Isbalance(_pRoot);
	}

private:

	int GetHeight(PNode Root)
	{
		if (NULL == Root)
			return 0;

		int Left = GetHeight(Root->_pLeft);
		int Right = GetHeight(Root->_pRight);
		return (Left > Right) ? (Left + 1) : (Right + 1);
	}

	bool _Isbalance(PNode Root)
	{
		if (NULL == Root)
			return true;
		
		int LHeight = GetHeight(Root->_pLeft);
		int RHeight = GetHeight(Root->_pRight);
		int bf = RHeight - LHeight;
		if (abs(bf) >= 2)
			return false;
		else
			return _Isbalance(Root->_pLeft) && _Isbalance(Root->_pRight);
	}

	PNode Find(PNode& Root, T key, V value)
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

	PNode FirstOfInOder(PNode& Root)
	{
		if (NULL == Root)
			return NULL;
		PNode pCur = Root;
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur;
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

		pParent->_bf = 0;
		pSubR->_bf = 0;
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

		pParent->_bf = 0;
		pSubL->_bf = 0;
	}

	void RotateLR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;
		int LR = pSubLR->_bf;

		RotateL(pParent->_pLeft);
		RotateR(pParent);

		PNode parent = pParent->_pParent;
		if (parent)
		{
			int left = GetHeight(parent->_pLeft);
			int right = GetHeight(parent->_pRight);

			parent->_bf = right - left;
		}

		if (LR == -1)
			pParent->_bf = 1;

		else if (LR == 1)
			pSubL->_bf = -1;
	}

	void RotateRL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;
		int RL = pSubRL->_bf;

		PNode parent = pParent->_pParent;
		if (parent)
			parent->_bf++;

		RotateR(pParent->_pRight);
		RotateL(pParent);

		if (RL == 1)
			pParent->_bf = -1;
		else if (RL == -1)
			pSubR->_bf = 1;
	}

	//旋转平衡调整
	void _Rotate(PNode& pParent)
	{
		if(pParent)
		{
			if (pParent->_bf == -2)
			{
				if (pParent->_pLeft->_bf == -1)//较高左子树的左侧---右单旋
					RotateR(pParent);
				else if (pParent->_pLeft->_bf == 1)//较高左子树的右侧---左右双旋
					RotateLR(pParent);
			}
			else if (pParent->_bf == 2)
			{
				if (pParent->_pRight->_bf == 1)//较高右子树的右侧---左单旋
					RotateL(pParent);
				else if (pParent->_pRight->_bf == -1)//较高右子树的左侧---右左双旋
					RotateRL(pParent);
			}
		}
	}

	//调整平衡因子
	void AdjustBf(PNode& pCur)
	{
		PNode pParent = pCur->_pParent;
		while (pParent)
		{
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			if (0 == pParent->_bf)
				break;
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				_Rotate(pParent);
				break;
			}
		}
	}

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
		AdjustBf(pCur);

		return true;
	}

private:
	PNode _pRoot;
};
