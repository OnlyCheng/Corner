class LCS {
public:
    int findLCS(string A, int n, string B, int m) {
        // write code here
        vector<int> v(m+1,0);
        vector<vector<int>> res(n+1,v);
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(A[i-1] == B[j-1])
                    res[i][j] = res[i-1][j-1]+1;
                else
                    res[i][j] = max(res[i-1][j],res[i][j-1]);
            }
        }
        return res[n][m];
    }
};
