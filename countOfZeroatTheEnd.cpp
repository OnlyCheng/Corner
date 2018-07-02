#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int count = 0;
    for(int i = 1; i<=n; i++)
    {
        int num = i;
        while(num%5 == 0)
        {
            count++;
            num /= 5;
        }
    }
    cout << count<<endl;
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
    while(n)
    {
        count+=n/5;
        n /= 5;
    }
    cout << count<<endl;
    return 0;
}
