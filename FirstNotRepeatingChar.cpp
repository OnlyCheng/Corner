class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int len  = str.length();
        if(len == 0)
            return -1;
        
        map<char,int> m;
        for(int i = 0; i<len; i++)
            m[str[i]]++;
        
        int j = 0;
        for(; j<len; j++)
        {
            if(1 == m[str[j]])
                break;
        }
        if(j == len)
            return -1;
        return j;
    }
};
