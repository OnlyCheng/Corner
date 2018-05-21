class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int size = sequence.size();
        if(size <= 0)
            return false;
        int root = sequence[size-1];
        return _VerifySquenceOfBST(sequence,root,0,size-1);
    }
    bool _VerifySquenceOfBST(vector<int> sequence,int root,int left,int right)
    {
        if(left >= right)
            return true;
        
        int R = 0;
        int i = 0;
        for(i = left; i<right;i++)
        {
            if(sequence[i] > root)
            {
                R = i;
                break;
            }
        }
        if(i == right)
            return true;
        else
        {
            for(int j = R; j<right; j++)
                if(sequence[j] < root)
                    return false;
        }
        
        bool ret = _VerifySquenceOfBST(sequence,sequence[R],left,R);
        if(ret)
            ret = _VerifySquenceOfBST(sequence,sequence[right],R+1,right);
        return ret;
    }
};
