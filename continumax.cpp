#include <iostream>
using namespace std;
#include <vector>
#include <string>

int main()
{
    string s;
    while(cin>>s)
    {
        int len = s.size();
        if(len==0)
        {
            cout<<""<<","<<0<<endl;
            return 0;
        }
        vector<string> res;
        string cur;
        string t;
        for(int i=0; i<len; i++)
        {
            if(s[i] >= '0' && s[i] <='9')
                t+=s[i];
            else
                t = "";
            if(t.size() >=cur.size())
            {
                cur = t;
                res.push_back(cur);
            }
        }
        len = cur.size();
        for(int i = 0; i<res.size(); i++)
        {
            if(res[i].size() == len)
                cout<<res[i];
        }
        cout<<","<<len<<endl;
    }
    return 0;
}
