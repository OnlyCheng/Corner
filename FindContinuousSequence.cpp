class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > res;
        if(sum <= 0)
            return res;
        
        int max = sum/2 + 1;
        int s = 0;
        for(int i = 1; i<max; i++)
        {
            s = 0;
            vector<int> temp;
            for(int j = i; j<=max; j++)
            {
                temp.push_back(j);
                s += j;
                if(s == sum)
                {
                    res.push_back(temp);
                    break;
                }
                else if(s > sum)
                    break;
            }
        }
        return res;
    }
};
