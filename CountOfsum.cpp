#include <iostream>
using namespace std;
#include <vector>

int main()
{
    int n,sum;
    cin>>n>>sum;
    vector<long> v(n);
    for(int i = 0;i<n;i++)
        cin>>v[i];
    vector<long> s(sum+1,0);
    s[0] = 1;
    vector<vector<long> > res(n+1,s);
    
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=sum;j++)
        {
            if(j >= v[i-1])
                res[i][j] = res[i-1][j]+res[i-1][j-v[i-1]];
            else
                res[i][j] = res[i-1][j];
        }
    }
    cout<<res[n][sum]<<endl;
    return 0;
}
