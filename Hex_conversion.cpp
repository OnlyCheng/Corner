#include <iostream>
using namespace std;
#include <string>

int main()
{
    int m,n;
    cin>>m>>n;
    string s = "0123456789ABCDEF";
    string res = "";
    
    if(m < 0)//是负数的话要输出负号，并将其转换为正数
    {
        cout<<"-";
        m = -m;
    }
    
    while(m)
    {
        res = s[m%n]+res;
        m /= n;
    }
    cout<<res<<endl;
    return 0;
}
