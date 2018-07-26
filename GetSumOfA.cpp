#include <iostream>
#include <algorithm>
using namespace std;

void Find(int* A,int i,int n,int sum,int& c)
{
    if(i == n-1 && sum != 0)
        return;
    for(int j = i; j<n; j++)
    {
        if(A[j] == sum)
            c += 1;
        else if(A[j]<sum)
            Find(A,j,n,sum-A[j],c);
    }
}

int GetSumOfA(int* A,int n,int sum)
{
    if(n <= 0)
        return 0;
    sort(A,A+n);
    int count = 0;
    for(int i = 0; i<n; i++)
    {
        int t = sum - A[i];
        int c = 0;
        Find(A,i,n,t,c);
        count += c;
    }
    return count;
}

int main()
{
    int n,sum;
    cin>>n>>sum;
    int A[n];
    for(int i = 0; i<n; i++)
    {
        cin>>A[i];
    }
    int ret = GetSumOfA(A,n,sum);
    cout<<ret<<endl;
    return 0;
}
