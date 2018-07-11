class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > res;
        int size = num.size();
        if(size  == 0)
            return res;
        
        vector<int> flag(size,-1);
        vector<int> temp(size);
        _permute(res,flag,num,temp,0);
        return res;
    }
    void _permute(vector<vector<int> >& res, vector<int> &flag,vector<int> &num,vector<int>temp,int n)
    {
        int size = num.size();
        if(n == size)
            res.push_back(temp);
        else
        {
            for(int i = 0; i<size; i++)
            {
                if(flag[i] == -1)
                {
                    temp[n]=num[i];
                    flag[i] = 0;
                    _permute(res,flag,num,temp,n+1);
                    flag[i] = -1;
                    continue;
                }
            }
        }
    }
};
