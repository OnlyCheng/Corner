class Solution {
public:
    int flag = 0;
    int minimumTotal(vector<vector<int> > &triangle) {
        int res = 0;
        _minimumTotal(triangle,res,0,0,0);
        return res;
    }
    void _minimumTotal(vector<vector<int> > &triangle,int &res,int index,int sum,int pos)
    {
        int size = triangle.size();
        if(index == size)
        {
            if(res == 0 && flag == 0)
            {
                res = sum;
                flag = 1;
            }
            else if(sum < res)
                res = sum;
            return;
        }
        int len = triangle[index].size();
        if(pos < len)
        {
            sum += triangle[index][pos];
            _minimumTotal(triangle,res,index+1,sum,pos);
            _minimumTotal(triangle,res,index+1,sum,pos+1);
        }
    }
};
