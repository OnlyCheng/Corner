/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //交换的两个节点除了有可能是位置上相连的两个结点 还有可能是逻辑上相连的两个节点
 //使用中序遍历，两个相连的结点不满足前面一个数比后边一个数小的两个节点就是被交换的结点
class Solution {
public:
    TreeNode* pre,*a,*b;
    void recoverTree(TreeNode *root) {
        if(NULL == root)
            return;
        pre = a = b = NULL;
        _recover(root);
        if(a && b)
            swap(a->val,b->val);
    }
    void _recover(TreeNode* pCur)
    {
        if(NULL == pCur)
            return;
        _recover(pCur->left);
        if(pre && pre->val > pCur->val)
        {
            if(a == NULL)
                a = pre;
            b = pCur;
        }
        pre = pCur;
        _recover(pCur->right);
    }
};
