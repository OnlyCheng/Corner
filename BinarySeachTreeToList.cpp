/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(NULL == pRootOfTree)
            return NULL;
        
        TreeNode* pHead = NULL;
        TreeNode* pCur = pRootOfTree;
        while(pCur->left)
            pCur = pCur->left;
        pHead = pCur;
        
        TreeNode* tail = NULL;
        _Convert(pRootOfTree,&tail);
        
        return pHead;
    }
    void _Convert(TreeNode* pRoot, TreeNode** tail)
    {
        if(NULL == pRoot)
            return;
        
        TreeNode* pCur = pRoot;
        if(pCur->left)//左子树存在，则先处理左子树
            _Convert(pCur->left,tail);
        //左子树不存在，将其左孩子指针挂到链表的最后一个节点后边
        pCur->left = *tail;
        if(*tail)//tail不为空，也就是说现在挂接的不是第一个节点，让tail右指针域指向当前节点
            (*tail)->right = pCur;
        *tail = pCur;
        
        if(pCur->right)
            _Convert(pCur->right,tail);
    }
};
