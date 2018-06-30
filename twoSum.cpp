class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int size = numbers.size();
        vector<int> res;
        if(size == 0 )
            return res;
        int i = 0;
        for(; i<size; i++)
        {
            for(int j = i+1; j<size; j++)
            {
                if( numbers[i] + numbers[j] == target)
                {
                    res.push_back(i+1);
                    res.push_back(j+1);
                    return res;
                }
            }
        }
        return res;
    }
};
