#include <iostream>
using namespace std;
#include <vector>

int main()
{
    string s;
    while(cin>>s)
    {
        string res;
        string cur;
        int size = s.size();
        //vector<string> v;
        for(int i = 0; i<size; i++)
        {
            if(s[i] < '0' || s[i] > '9')
            {
               // if(cur.size() == res.size())
               //     v.push_back(cur);
                cur = "";
                continue;
            }
            cur += s[i];
            if(cur.size() > res.size())
                res = cur;
        }
    //   int len = res.size();
    //   for(int i=0; i<v.size(); i++)
    //   {
    //       if(v[i].size() == len)
    //           cout<<v[i];
    //   }
    //    cout<<endl;
        cout<<res<<endl;
    }
    return 0;
}

//上边的方法OJ能过66.7%，去掉循环就能过了
#include <iostream>
using namespace std;
#include <string>

int main()
{
    string s;
    cin>>s;
    //while(cin>>s)
    //{
        int size = s.size();
        if(size == 0)
        {
            cout<<""<<endl;
            return 0;
        }
        string res;
        string cur;
        for(int i = 0; i<size;i++)
        {
            if(s[i]>='0' && s[i]<='9')
                cur+=s[i];
            else
                cur = "";
            if(cur.size()>res.size())
                res = cur;
        }
        cout<<res<<endl;
    //}
    
    return 0;
}
