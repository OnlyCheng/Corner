//根据中序和后序遍历序列重建二叉树
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int size1 = inorder.size();
        int size2 = inorder.size();
        if(0 == size1||0 == size2 || size1 != size2)
            return NULL;
        TreeNode* root=NULL;
        ConstructTree(root,inorder,0,size1 -1,postorder,0,size2-1);
        return root;
    }
     
    void ConstructTree(TreeNode* & root,vector<int> &inorder,int p1,int p2,vector<int> &postorder,int i1,int i2)
    {
        if(p1>p2||i1>i2)
            return;
        int data=postorder[i2];
        root=new TreeNode(data);
        int i;
        //find the index of root in inorder
        for(i=p1;i<=p2;i++)
        {
            if(inorder[i]==data)
                break;
        }
        if(i > p2)
            return;
         
        ConstructTree(root->left,inorder,p1,i-1,postorder,i1,i1+i-p1-1);
        ConstructTree(root->right,inorder,i+1,p2,postorder,i1+i-p1,i2-1);
    }
};
