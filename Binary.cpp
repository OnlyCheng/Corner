#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <queue>
#include <stack>

template<typename T>
struct BinTreeNode
{
	BinTreeNode()
		:_data(0)
		, _LChild(NULL)
		, _RChild(NULL)
	{}

	T _data;
	BinTreeNode* _LChild;
	BinTreeNode* _RChild;
};

template <typename T>
class BinTree
{
	typedef BinTreeNode<T> Node;
	typedef BinTreeNode<T>* PNode;
public:
	BinTree()
		: _pRoot(NULL)
	{}

	BinTree(const T* array, size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreateBinTree(_pRoot, array, size, index, invalid);
	}

	BinTree(const BinTree& bt)
	{
		_pRoot = _CopyBinTree(bt._pRoot);
	}

	BinTree& operator=(const BinTree& bt)
	{
		assert(this != bt);
		if (_pRoot != NULL)
			_DistroyBinTree(_pRoot);
		_pRoot = _CopyBinTree(bt);
	}

	~BinTree()
	{
		_DistroyBinTree(_pRoot);
	}

	void PreOrder()
	{
		_PreOrder(_pRoot);
	}

	void PreOrder_Nor()
	{
		_PreOrder_Nor(_pRoot);
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

	void InOrder_Nor()
	{
		_InOrder_Nor(_pRoot);
	}

	void PostOrder()
	{
		_PostOrder(_pRoot);
	}

	void PostOrder_Nor()
	{
		_PostOrder_Nor(_pRoot);
	}

	void LevelOrder()
	{
		queue<PNode> q;
		_LevelOrder(_pRoot,q);
	}
	size_t Size()
	{
		return _Size(_pRoot);
	}
	size_t GetLeafCount()
	{
		return _GetLeafCount(_pRoot);
	}
		// 获取第K层结点的个数 
	size_t GetKLevelCount(size_t K)
	{
		return _GetKlevelCount(_pRoot,K);
	}
	size_t Height();
	PNode Find(const T& data)
	{
		return _Find(_pRoot,data);
	}
	PNode Parent(PNode pNode)
	{
		return _Parent(pNode);
	}
	PNode LeftChild(PNode pNode)
	{
		return _LeftChild(pNode);
	}
	PNode RightChild(PNode pNode)
	{
		return _RightChild(pNode)
	}
private:
	// 根+左子树+右子树 
	void _CreateBinTree(PNode& pRoot, const T* array, size_t size, size_t& index, const T& invalid)
	{
		if (index < size&&invalid != array[index])
		{
			pRoot = new Node;
			pRoot->_data = array[index];
		}

		if (invalid == array[index])
			return;

		if (index < size)
			_CreateBinTree(pRoot->_LChild, array, size, ++index, invalid);
		if (index < size)
			_CreateBinTree(pRoot->_RChild, array, size, ++index, invalid);

	}

	PNode _CopyBinTree(PNode pRoot)
	{
		if (NULL == pRoot)
			return NULL;
		PNode tmp = new Node;
		tmp->_data = pRoot->_data;

		tmp->_LChild = _CopyBinTree(pRoot->_LChild);
		tmp->_RChild = _CopyBinTree(pRoot->_RChild);
		return tmp;
	}

	void _DistroyBinTree(PNode& pRoot)
	{
		if (NULL == pRoot)
			return;
		_DistroyBinTree(pRoot->_LChild);
		_DistroyBinTree(pRoot->_RChild);
		delete pRoot;
	}
		// 根--->根的左子树---->根的右子树 
	void _PreOrder(PNode& pRoot)
	{
		if (NULL == pRoot)
			return;
		cout << pRoot ->_data << " ";
		_PreOrder(pRoot->_LChild);
		_PreOrder(pRoot->_RChild);
	}
	
	//非递归实现先序遍历
	void _PreOrder_Nor(PNode pRoot)
	{
		if (NULL == pRoot)
			return;
		stack<PNode> s;
		PNode pCur = pRoot;
		s.push(pCur);

		while (!s.empty())
		{
			pCur = s.top();
			cout << pCur->_data << " ";
			s.pop();
			
			if (NULL != pCur->_RChild)
				s.push(pCur->_RChild);

			if (NULL != pCur->_LChild)
				s.push(pCur->_LChild);
		}
	}

		// 左子树--->根节点--->右子树 
	void _InOrder(PNode pRoot)
	{
		if (NULL == pRoot)
			return;

		_InOrder(pRoot->_LChild);
		cout << pRoot ->_data << " ";
		_InOrder(pRoot->_RChild);
	}

	//非递归实现中序遍历
	void _InOrder_Nor(PNode pRoot)
	{
		if (NULL == pRoot)
			return;
		PNode pCur = pRoot;
		stack<PNode> s;
		while (pCur||!s.empty())
		{
			while (pCur)
			{
				s.push(pCur);
				pCur = pCur->_LChild;
			}

			pCur = s.top();
			cout << pCur->_data << " ";
			s.pop();
			if (pCur->_RChild)
			{
				pCur->_RChild;
			}
		}
	}

	//非递归实现后序遍历
	void _PostOrder_Nor(PNode pRoot)
	{
		if (pRoot == NULL)
			return;

		PNode pCur = pRoot;
		PNode pPre = NULL;
		stack<PNode> s;
		while (pCur || !s.empty())
		{
			while (pCur && pPre != pCur)
			{
				s.push(pCur);
				pCur = pCur->_LChild;
			}

			if (s.empty())
				break;

			pCur = s.top();

			if (NULL == pCur->_RChild || pCur->_RChild == pPre)
			{
				cout << pCur->_data << " ";
				pPre = pCur;
				s.pop();
			}
			else
				pCur = pCur->_RChild;
		}
	}

		// 左子树--->右子树--->根节点 
	void _PostOrder(PNode pRoot)
	{
		if (NULL == pRoot)
			return;

		_PostOrder(pRoot->_LChild);
		_PostOrder(pRoot->_RChild);

		cout << pRoot ->_data << " ";
	}

	void _LevelOrder(PNode pRoot,queue<PNode> q)
	{
		if (NULL == pRoot)
			return;
		q.push(pRoot);
		while (!q.empty())
		{
			PNode pCur = q.front();
			cout << pCur->_data << " ";
			if (pCur->_LChild)
				q.push(pCur->_LChild);
			if (pCur->_RChild)
				q.push(pCur->_RChild);
			q.pop();
		}
	}

	size_t _Size(PNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		return _Size(pRoot->_LChild) + _Size(pRoot->_RChild) + 1;
	}

	size_t _GetLeafCount(PNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		if (pRoot->_LChild == NULL&&pRoot->_RChild == NULL)
			return 1;
		return _GetLeafCount(pRoot->_LChild) + _GetLeafCount(pRoot->_RChild);
	}

	size_t _Height(PNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		if (NULL == pRoot->_LChild && NULL == pRoot)
			return 1;

		sise_t LHeight = _Height(pRoot->_LChild)
		sise_t RHeight = _Height(pRoot->_RChild);
		return (LHeight > RHeight) ? LHeight + 1 : RHeight + 1;
	}

	PNode _Find(PNode pRoot, const T& data)
	{
		if (NULL == pRoot)
			return NULL;
		if (data == pRoot->_data)
			return _find;
		_Find(pRoot->_LChild, data);
		_Find(pRoot->_RChild, data);
	}

	PNode _Parent(PNode pRoot, PNode pNode)
	{
		if (NULL == pRoot||pNode == pRoot)
			return NULL;
		if (pNode == pRoot->_LChild || pNode == pRoot->_RChild)
			return pRoot;
		_Parent(pRoot->_LChild, pNode);
		_Parent(pRoot->_RChild, pNode);
	}

	PNode _LeftChild(PNode pRoot, PNode pNode)
	{
		if (NULL == pRoot)
			return NULL;
		if (pNode == pRoot)
			return pRoot->_LChild;
		_LeftChild(pRoot->_LChild, pNode);
		_LeftChild(pRoot->_RChild, pNode);
	}

	PNode _RightChild(PNode pRoot, PNode pNode)
	{
		if (NULL == pRoot)
			return NULL;
		if (pNode == pRoot)
			return pRoot->_RChild;
		_RightChild(pRoot->_LChild, pNode);
		_RightChild(pRoot->_RChild, pNode);
	}

	size_t _GetKlevelCount(PNode pRoot, int K)
	{
		if (NULL == pRoot || K <= 0)
			return 0;
		if (1 == K)
			return 1;
		return _GetKlevelCount(pRoot->_LChild, --K) + _GetKlevelCount(pRoot->_RChild, K);
	}

private:
	PNode _pRoot;
};

int main()
{
	char* p = "ABD###CE##F";
	BinTree<char> bt1(p, 11, '#');
	BinTree<char> bt2(bt1);
	BinTree<char> bt3 = bt1;

	/*bt1.PreOrder();
	cout << endl;

	bt1.PreOrder_Nor();
	cout << endl;*/

	/*bt1.InOrder();
	cout << endl;

	bt1.InOrder_Nor();
	cout << endl;*/

	/*bt1.LevelOrder();
	cout << endl;*/

	bt1.PostOrder();
	cout << endl;

	bt1.PostOrder_Nor();
	cout << endl;

	/*size_t count = bt1.GetKLevelCount(2);
	cout << "The Node of Klevel is : " << count << endl;*/

	/*bt2.InOrder();
	cout << endl;

	bt3.InOrder();
	cout << endl;

	bt1.PreOrder();
	cout << endl;

	bt1.PostOrder();
	cout << endl;*/

	/*size_t leafcout = bt1.GetLeafCount();
	cout <<"leafcout is : "<< leafcout << endl;

	size_t size = bt1.Size();
	cout << "size is : " << size << endl;*/


	return 0;
}
