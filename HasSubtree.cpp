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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot1 == NULL || pRoot2 == NULL)
            return false;
        TreeNode* location = Find(pRoot1, pRoot2);
        if(location == NULL)
            return false;
        else
        {
            bool ret = Compare(location,pRoot2);
            if(ret)
                return true;
            else
            {
                ret = HasSubtree(location->left,pRoot2);
                if(ret)
                    return true;
                return HasSubtree(location->right,pRoot2);
            }
        }
    }
    
    TreeNode*  Find(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot1 == NULL)
            return NULL;
        if(pRoot1->val == pRoot2->val)
            return pRoot1;
        else
        {
            TreeNode* ret = Find(pRoot1->left,pRoot2);
            if(ret)
                return ret;
            return Find(pRoot1->right,pRoot2);
        }
    }
    
    bool Compare(TreeNode* location, TreeNode* pRoot2)
    {
        if(!pRoot2)
            return true;
        else if(location == NULL && pRoot2 != NULL)
            return false;
        if(location->val != pRoot2->val)
            return false;
        else
            return Compare(location->left,pRoot2->left) && Compare(location->right,pRoot2->right);
    }
};
