class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        int size = numbers.size();
        string res;
        sort(numbers.begin(),numbers.end(),cmp);//通过巧妙的比较方式
        for(int i = 0; i<size; i++)
        {
            res+=to_string(numbers[i]);
        }
        return res;
    }
    static bool cmp(int a,int b)
    {
        string A = to_string(a);
        string B = to_string(b);
        if(A+B < B+A)
            return true;
        else
            return false;
    }
};
