#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
#include <vector>
#include <map>

int main()
{
    int N,L;
    cin>>N>>L;
    vector<string> vs(N);
    for(int i = 0;i<N;i++)
        getline(cin,vs[i]);
    
    string res;
    int flag = 1;
    int pre = 0;
    int cur = 0;
    
    
    for(int i = 0;i<L;i++)
    {
        char c = vs[0][i];
        map<char,int> tmp;
        for(int j = 0;j<N;j++)
        {
            tmp[vs[j][i]] = j;
        }
        
        auto it = tmp.begin();
        if(i == L-1 && flag == 1)
        {
            it++;
        }
        c = it->first;
        cur = it->second;
        if(i != 0)
        {
            if(pre != cur)
                flag = 0;
        }
        pre = it->second;
        res += c;
    }
    cout<<res<<endl;
}
