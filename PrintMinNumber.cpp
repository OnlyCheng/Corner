class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        size_t size = numbers.size();
        string result;
        if(size == 0)
            return result;
        
        sort(numbers.begin(),numbers.end(),Cmp);
        if(numbers[0] == 0 && size >1)
        {
            swap(numbers[0],numbers[1]);
        }
        
        for(size_t i = 0; i<size; i++)
        {
            result += to_string(numbers[i]);
        }
        return result;
    }
    
    static bool Cmp(int left, int right)
    {
        string LR = to_string(left)+to_string(right);
        string RL = to_string(right)+to_string(left);
        return LR < RL;
    }
};
