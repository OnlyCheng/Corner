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
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin)
    {
        size_t len1 = pre.size();
        size_t len2 = vin.size();
        if(len1 != len2 || len1 == 0 || len2 == 0)
            return NULL;
        
        return Construct(pre.begin(),pre.end(),vin.begin(),vin.end());
    }
    
    TreeNode* Construct(vector<int>::iterator  PreStart, 
                        vector<int>::iterator  PreEnd, 
                        vector<int>::iterator  VinStart, 
                        vector<int>::iterator  VinEnd)
    {
        int value = PreStart[0];
        TreeNode* Root = new TreeNode(value);
        
        if(*PreStart == *(PreEnd-1))
        {
            if(*VinStart == *(VinEnd-1) && *PreStart == *VinStart)
                return Root;
            else
                return NULL;
        }
        
        vector<int>::iterator  rootVin = VinStart;
        while(rootVin < VinEnd && *rootVin != value)
            ++rootVin;
        if(rootVin == VinEnd)
            return NULL;
        
        int leftlen = rootVin-VinStart;
        if(leftlen > 0)
            Root->left = Construct(PreStart+1,PreStart+leftlen+1,VinStart,rootVin);
        if(leftlen < VinEnd - VinStart)
            Root->right = Construct(PreStart+leftlen+1,PreEnd,rootVin+1,VinEnd);
        
        return Root;
    }
};
