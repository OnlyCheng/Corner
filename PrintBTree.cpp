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
            if(NULL == pRoot)
                return res;
            queue<TreeNode*> q1,q2;
            int index = 0;
            q1.push(pRoot);
            while(!q1.empty())
            {
                res.resize(index+1);
                int size = q1.size();
                //将一层的保存到一行中，同时将这一行的内容按序存入到辅助队列中，以便获取下一层的结点
                for(int i = 0; i<size; i++)
                {
                    TreeNode* temp = q1.front();
                    res[index].push_back(temp->val);
                    q1.pop();
                    q2.push(temp);
                }
                //将下一层的结点按序存入队列中，方便将它们顺序存储到结果数组中
                for(int i = 0; i<size; i++)
                {
                    TreeNode* temp = q2.front();
                    q2.pop();
                    if(temp->left)
                        q1.push(temp->left);
                    if(temp->right)
                        q1.push(temp->right);
                }
                index++;
            }
            return res;
        }
    
};
