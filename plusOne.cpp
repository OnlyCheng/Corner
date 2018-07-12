class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int size = digits.size();
        vector<int> res(size);
        if(size == 0)
            res.push_back(1);
        else
        {
            int flag = 1;
            for(int i = size-1; i >= 0; i--)
            {
                int cur = digits[i]+flag;
                res[i] = cur%10;
                flag = cur/10;
            }
            if(flag)
                res.insert(res.begin(),1);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int size = digits.size();
        vector<int> res(size);
        if(size == 0)
            res.push_back(1);
        else
        {
            int flag = 1;
            for(int i = size-1; i >= 0; i--)
            {
                int cur = digits[i]+flag;
                res[i] = cur%10;
                if(cur <= 9)
                    flag = 0;
                else
                    flag = 1;
            }
            if(flag)
                res.insert(res.begin(),1);
        }
        return res;
    }
};
