class Solution {
public:
    int run(TreeNode *root) {
        if(NULL == root)
            return 0;
        return _run(root);
    }
    int _run(TreeNode* root)
    {
        if(NULL == root)
            return 0;
        
        int l = _run(root->left);
        int r = _run(root->right);
        if(l<r)
        {
            if(l == 0)
                return r+1;
            else
                return l+1;
        }
        else
        {
            if(r == 0)
                return l+1;
            else
                return r+1;
        }
    }
};
