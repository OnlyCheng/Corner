#include <iostream>
using namespace std;
#include <map>
#include <string.h>

int main()
{
    string str1;//卖家
    string str2;//小红想要的串
    cin>>str1;
    cin>>str2;
    
    int len1 = str1.length();
    int len2 = str2.length();
    int count = 0;
    for(int i = 0; i<len2; i++)
    {
        int index = str1.find(str2[i]);
        if(index >= 0)
            str1.erase(str1.begin()+index);
        else
            count++;
    }
    if(count == 0)
        cout<<"Yes "<<len1-len2<<endl;
    else
        cout<<"No "<<count<<endl;
}
