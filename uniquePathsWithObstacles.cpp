class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int row = obstacleGrid.size();
        if(row == 0)
            return 0;
        int col = obstacleGrid[0].size();
        vector<int> res(col,!obstacleGrid[0][0]);//初始化第一行第一列值
        for(int i = 1;i<col;i++)//初始化第一行的值
        {
            if(obstacleGrid[0][i] == 1 || res[i-1] == 0)//当前位置设有障碍或者前边已经出现过障碍
                res[i] = 0;
            else
                res[i] = 1;
        }
        for(int i = 1;i<row;i++)
        {
            if(obstacleGrid[i][0] == 1 || obstacleGrid[i-1][0] == 1)//初始化第一列的值
                res[0] = 0;
            for(int j = 1;j<col;j++)
            {
                if(obstacleGrid[i][j] == 1)
                    res[j] = 0;
                else
                    res[j] += res[j-1];
            }
        }
        return res[col-1];
    }
};

		
