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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > res;
        if(NULL == root)
            return res;
        queue<TreeNode*> q1,q2;
        q1.push(root);
        int count = 0;
        int index = 0;
        while(!q1.empty())
        {
            res.resize(index+1);
            int size = q1.size();
            for(int i = 0; i<size; i++)
            {
                TreeNode* tmp = q1.front();
                res[index].push_back(tmp->val);
                q2.push(tmp);
                q1.pop();
            }
            if(count%2 == 1)
                Reverse(res[index]);
            for(int i = 0; i<size; i++)
            {
                TreeNode* tmp = q2.front();
                if(tmp->left)
                    q1.push(tmp->left);
                if(tmp->right)
                    q1.push(tmp->right);
                q2.pop();
            }
            count++;index++;
        }
        return res;
    }
    void Reverse(vector<int >& v)
    {
        int size = v.size();
        int l = 0;
        int r = size-1;
        while(l <= r)
        {
            swap(v[l],v[r]);
            l++;r--;
        }
    }
};
