class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> res;
        int len  = str.length();
        if(len == 0)
            return res;
        _Permutation(res,str,0);
        sort(res.begin(),res.end());//其实如果只是单纯的解决这个问题，这个步骤可以不要，但是没有这个步骤可能没法AC
        return res;
    }
    void _Permutation(vector<string>& res,string& str, int n)
    {
        if(n == str.length())
            res.push_back(str);
        else
        {
            for(int i = n; i<str.length(); i++)
            {
                if(NeedExchange(str[i],str,i))
                {
                    swap(str[i],str[n]);
                    _Permutation(res,str,n+1);
                    swap(str[i],str[n]);
                }
            }
        }
    }
    bool NeedExchange(char c,string& s,int n)
    {
        int len = s.length();
        for(int i = n+1; i < len; i++)
        {
            if(s[i] == c)
                return false;
        }
        return true;
    }
};
