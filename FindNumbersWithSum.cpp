class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> res;
        int size = array.size();
        int mul = 0;
        int flag = 0;
        for(int i = 0;i<size;i++)
        {
            int n1 = array[i];
            int n2 = 0;
            if(n1 >= sum)
                break;
            for(int j = i+1;j<sum;j++)
            {
                if(array[j] == sum-n1)
                {
                    n2 = array[j];
                    break;
                }
            }
            if(n1 + n2 == sum)
            {
                if(mul == 0 && flag == 0)
                {
                    mul = n1*n2;
                    flag = 1;
                    res.push_back(n1);
                    res.push_back(n2);
                }
                else if(n1*n2 <mul)
                {
                    mul = n1*n2;
                    res[0] = n1;
                    res[1] = n2;
                }
            }
        }
        return res;
    }
};
