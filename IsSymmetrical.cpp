/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(NULL == pRoot || (pRoot->left == NULL && NULL == pRoot->right))
            return true;
        
        if(pRoot->right == NULL || pRoot->left == NULL )
            return false;
        
        if(pRoot->left->val != pRoot->right->val)
            return false;
        
        return _isSymmetrical(pRoot->left,pRoot->right);
    }
    bool _isSymmetrical(TreeNode* L,TreeNode* R)
    {
        if(NULL == L && NULL == R)
            return true;
        if(L == NULL || R == NULL)
            return false;
        
        if(L->val != R->val)
            return false;
        
        return _isSymmetrical(L->left,R->right)&&_isSymmetrical(L->right,R->left);
    }
};
