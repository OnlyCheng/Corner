#include <iostream>
using namespace std;

int MaxSumOfSubarray(int* arr,int n)
{
    if(NULL == arr || 0 == n)
        return 0;
    
    int sum = 0;
    int s = 0;
    int max = arr[0];
    for(int i = 0; i<n; i++)
    {
        if(max < arr[i])
            max = arr[i];
        s += arr[i];
        if(s < 0)
            s = 0;
        if(s >= sum)
            sum = s;
    }
    if(max < 0)
        return max;
    
    return sum;
}

int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i = 0; i<n; i++)
        cin>>arr[i];
    
    int ret = MaxSumOfSubarray(arr,n);
    cout<<ret<<endl;
    return 0;
}
