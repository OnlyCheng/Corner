class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int size = numbers.size();
        if(size == 0)
            return 0;
        
        map<int,int> m;
        for(int i = 0; i<size; i++)
            m[numbers[i]]++;
        
        int j = 0; 
        int num = size>>1;
        for(; j<size; j++)
        {
            if(num < m[numbers[j]])
                break;
        }
        if(j == size)
            return 0;
        return numbers[j];
    }
};
