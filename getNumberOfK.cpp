class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int size = data.size();
        if(size == 0)
            return 0;
        int count = 0;
        for(int i = 0; i<size; i++)
        {
            if(data[i] == k)
                count++;
        }
       return count;
    }
};
