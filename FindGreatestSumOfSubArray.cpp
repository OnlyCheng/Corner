class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        int size = array.size();
        if(size <= 0)
            return 0;
        int max = array[0];
        int sum = 0;
        for(int i = 0;i<size; i++)
        {
            if(sum<=0)
                sum = array[i];
            else
                sum += array[i];
            if(sum > max)
                max = sum;
        }
        return max;
    }
};
