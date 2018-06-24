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
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        if(NULL == root)
            return res;
        PostOrder(root,res);
        return res;
    }
    void PostOrder(TreeNode* pRoot, vector<int>& res)
    {
        if(NULL == pRoot)
            return;
        if(pRoot->left)
            PostOrder(pRoot->left,res);
        if(pRoot->right)
            PostOrder(pRoot->right,res);
        res.push_back(pRoot->val);
    }
};
