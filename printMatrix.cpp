class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        vector<int> res;
        if (col <= 0 || row <= 0)
            return res;
        int left = 0;
        int right = col-1;
        int up = 0;
        int down = row-1;
        while(left<=right && up<=down)
        {
            //从左到右遍历
            for(int j = left;j<=right; j++)
                res.push_back(matrix[up][j]);
            //从上到下遍历
            if(up<down)
                for(int k = up+1; k<=down; k++)
                    res.push_back(matrix[k][right]);
            //从右到左遍历
            if(up<down && left<right)
                for(int j = right-1; j>=left; j--)
                    res.push_back(matrix[down][j]);
            //从下到上遍历
            if(up<down && left<right)
                for(int k = down-1; k>up; k--)
                    res.push_back(matrix[k][left]);
            left++;right--;
            up++;down--;
        }
        return res;
    }
};
