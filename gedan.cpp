#include <iostream>
using namespace std;

long long count[105][105];
int mod = 1000000007;

int main()
{
    int K;
    scanf("%d",&K);
    
    int A,B,X,Y;
    scanf("%d%d%d%d",&A,&X,&B,&Y);
    long long result = 0;
    
    count[0][0] = 1;
    for(int i = 1;i<=100;i++)
    {
        count[i][0] = 1;
        for(int j = 1;j<=100;j++)
            count[i][j] = (count[i-1][j-1]+count[i-1][j])% mod;
    }
    
    for(int i = 0;i<=X; i++)
        if(i*A <= K && (K-A*i)%B == 0 && (K-A*i)/B<= Y)
            result = (result+(count[X][i] * count[Y][(K-A*i)/B])%mod)%mod;
    cout<<result<<endl;
    return 0;
}
