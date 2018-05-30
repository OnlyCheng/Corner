class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> >  res;
        if(sum == 0)
            return res;
        
        int size = sum>>1;
        int s = 0;
        int count = 0;
        for(int i = 0; i<size; i++)
        {
            s = 0;
            int j = 0; 
            for(int j = i; j<=size; j++)
            {
                s += j;
                if(s >= sum)
                    break;
            }
            int k = j-i+1;
            if(s == sum)
            {
                count++;
                res.resize(count);
                res[count-1].resize(k);
                int index = 0;
                for(int m = i; m<= j; m++)
                    res[count-1][index++] = m;
            }
        }
        return res;
    }
};
