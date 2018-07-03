class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        int size  = dict.size();
        if(0 == size)
            return 0;
        if(start.empty() || start.empty())
            return 0;
        
        int ret = 0;
        auto it = dict.begin();
        int flag = 0;
        for(;it != dict.end();it++)
        {
            if(flag == 0)
            {
                if(Compare(*it,start))
                    flag = 1;
                else
                    continue;
            }
            ret++;
            if(Compare(*it,end))
            {
                flag = 0;
                break;
            }
        }
        if(ret > 0 && flag == 0)
            return ret+2;
        else
            return 0;
    }
    bool Compare(const string& s1, string& s2)
    {
        int len1 = s1.length();
        int len2 = s2.length();
        if(len1 != len2)
            return false;
        int count = 0;
        for(int i = 0; i<len1; i++)
        {
            if(s1[i] != s2[i])
                count++;
        }
        if(count > 1)
            return false;
        else
            return true;
    }
};
