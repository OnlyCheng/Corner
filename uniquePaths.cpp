class Solution {
public:
    int uniquePaths(int m, int n) {
        if(n == 1)
            return 1;
        vector<int> res(m,1);
        for(int i = 1;i<n;i++)
        {
            for(int j = 1;j<m;j++)
                res[j] += res[j-1];
        }
        return res[m-1]; 
    }
};
