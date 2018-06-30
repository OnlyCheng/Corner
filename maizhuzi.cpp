#include <iostream>
using namespace std;
#include <map>
#include <string.h>

int main()
{
    char str1[1000];
    char str2[1000];
    cin>>str1;
    cin>>str2;
    
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    map<char,int> m1;
    map<char,int> m2;
    for(int i = 0; i<size1; i++)
    {
        m1[str1[i]]++;
    }
    for(int i = 0; i<size2; i++)
    {
        m2[str2[i]]++;
    }
    int count = 0;
    for(int i = 0; i<size2; i++)
    {
        int tmp1 = m1[str1[i]];
        int tmp2 = m2[str2[i]];
        if( tmp1 < tmp2)
            count+= tmp2-tmp1;
    }
    if(count)
        cout<<"No"<<" "<<count<<endl;
    else
        cout<<"Yes"<<" "<<size1-size2<<endl;
}
