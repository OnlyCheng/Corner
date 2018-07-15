#include <iostream>
using namespace std;
#include <string>

bool Judge(string& s, int len)
{
    if (len <= 0 || len > 10)
    	return false;
    int l = 0;
    int r = len - 1;
    int flag = 0;
    while (l < r)
    {
        if ((s[l] < 'a' || s[l] > 'z') || (s[r]<'a' || s[r] > 'z'))
            return false;
        if (s[l] == s[r])  //正常情况  hhhh
        {
            l++; r--;
            continue;
        }
        //不等
        if (flag == 0 && s[l] == s[r - 1] && r - 1 >= l)//hcchi
        {
            r--;
            flag = 1;
        }
        else if (flag == 0 && s[l + 1] == s[r] && l + 1 <= r)//ihcch
        {
            l++;
            flag = 1;
        }
        else
            break;
    }
    if (l >= r)
        return true;
    else
        return false;
}

int main()
{
    string s;
    while(cin>>s)
    {
    int len = s.length();
    bool ret = Judge(s, len);
    if (ret)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    }
    
    return 0;
}
