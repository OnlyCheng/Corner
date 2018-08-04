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
        if(pRootOfTree == NULL)
            return NULL;
        TreeNode* head = NULL;
        TreeNode* pCur = pRootOfTree;
        TreeNode* pPre = NULL;
        while(pCur->left)
        {
            pCur = pCur->left;
        }
        head = pCur;
        Inorder(pRootOfTree,pPre);
        return head;
    }
    void Inorder(TreeNode* root,TreeNode*& pPre)
    {
        if(root == NULL)
            return;
        Inorder(root->left,pPre);
        
        if(pPre != NULL)
            pPre->right = root;
        root->left = pPre;
        pPre = root;
        
        Inorder(root->right,pPre);
    }
};
