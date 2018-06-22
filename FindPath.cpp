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
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber)
    {
        vector<vector<int> > res;
        if(root == NULL)
            return res;
        vector<int> temp;
        int sum = 0;
        _FindPath(root, res, expectNumber, temp, sum);
        return res;
    }
    void _FindPath(TreeNode* root,vector<vector<int> >& res, int expectNumber, vector<int>& temp, int sum)
    {
        temp.push_back(root->val);
        sum += root->val;
        if(sum == expectNumber && root->left == NULL && root->right == NULL)
            res.push_back(temp);
        if(root->left)
            _FindPath(root->left, res, expectNumber, temp, sum);
        if(root->right)
            _FindPath(root->right, res, expectNumber, temp, sum);
        temp.pop_back();
    }
};
