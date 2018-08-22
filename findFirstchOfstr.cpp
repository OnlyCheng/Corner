#include <iostream>
using namespace std;
#include <map>
#include <string>

int main()
{
    string str;
    while(cin>>str)
    {
        int size = str.size();
        map<char,int> m;
        if(size < 1)
            continue;
        for(int i = 0;i<size;i++)
            m[str[i]]++;
        int i = 0;
        for(;i<size;i++)
        {
            if(m[str[i]] == 1)
                break;
        }
        if(i != size)
            cout<<str[i]<<endl;
        else
            cout<<-1<<endl;
    }
    return 0;
}
