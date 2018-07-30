#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int count = 0;
    while(n/=5)
    {
        count += n;
    }
    cout<<count<<endl;
    return 0;
}

//方法2

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int count = 0;
    for(int i = 5;i<=n;i = i+5)
    {
        int j = i;
        while(j)
        {
            if(j%5 ==0)
                count++;
            else
                break;
            j /= 5;
        }
    }
    cout<<count<<endl;
    return 0;
}
