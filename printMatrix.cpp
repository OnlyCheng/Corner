class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix)
    {
        int col = matrix.size();
        int row = matrix[0].size();
        vector<int> res;
        if (col <= 0 || row <= 0)
            return res;
        for (int i = 0; res.size()<col*row && i<row; i++)
        {
            int j = i;
            if(j < col-1)
            {
                for (; j < col - i - 1; j++)
                    res.push_back(matrix[i][j]);
            }
            int k = i;
            if(k < row)
            {
                for (; k<row - i - 1; k++)
                    res.push_back(matrix[k][j]);
            }
            
            int m = j;
            if(m < col)
            {
                for (; m > i; m--)
                    res.push_back(matrix[k][m]);
            }
            
            int n = k;
            if(n < row)
            {
                for (; n > i; n--)
                    res.push_back(matrix[n][m]);
            }
        }
        return res;
    }
};
