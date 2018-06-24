class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if(NULL == pRoot)
            return true;
        return IsBalanced(pRoot);
    }
    bool IsBalanced(TreeNode* pRoot)
    {
        if(NULL == pRoot)
            return true;
        int lh = GetHeight(pRoot->left)+1;
        int rh = GetHeight(pRoot->right)+1;
        int dif = lh - rh;
        if(dif < 0)
            dif = -dif;
        if(dif > 1)
            return false;
        return IsBalanced(pRoot->left)&&IsBalanced(pRoot->right);
    }
    
    int GetHeight(TreeNode* pRoot)
    {
        if(NULL == pRoot)
            return 0;
        int left = GetHeight(pRoot->left);
        int right = GetHeight(pRoot->right);
        return (left>right)?(left+1):(right+1);
    }
};
