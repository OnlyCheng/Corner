/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* pre = NULL;
    bool isValidBST(TreeNode *root) {
        if(NULL == root)
            return true;
        bool ret = isValidBST(root->left);
        if(ret)
        {
            if(pre && pre->val >= root->val)
                return false;
            pre = root;
            return isValidBST(root->right);
        }
        else
            return false;
    }
};
