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
        vector<vector<int> > Print(TreeNode* pRoot) {
            vector<vector<int> > res;
            if(pRoot == NULL)
                return res;
            stack<TreeNode*> s1,s2;
            s1.push(pRoot);
            int index = 0;
            while(!s1.empty())
            {
                res.resize(index+1);
                while(!s1.empty())
                {
                    TreeNode* t = s1.top();
                    s1.pop();
                    res[index].push_back(t->val);
                    if(t->left)
                        s2.push(t->left);
                    if(t->right)
                        s2.push(t->right);
                }
                while(!s2.empty())
                {
                    s1.push(s2.top());
                    s2.pop();
                }
                index++;
            }
            return res;
        }
};
