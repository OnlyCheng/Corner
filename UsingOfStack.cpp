#include <iostream>
using namespace std;
#include <stack>

struct Input
{
    char _ch;
    int _num;
};
 
int main()
{
    stack<int> s;
    int n;
    cin>>n;
    struct Input arr[n];
    for(int i = 0; i<n; i++)
    {
        cin>>arr[i]._ch;
        if(arr[i]._ch == 'P')
            cin>>arr[i]._num;
    }
    
    for(int i = 0;i<n; i++)
    {
        switch(arr[i]._ch)
        {
            case 'P':
                s.push(arr[i]._num);
                break;
            case 'O':
                if(!s.empty())
                    s.pop();
                break;
            case 'A':
                if(!s.empty())
                    cout<<s.top()<<endl;
                else
                    cout<<"E"<<endl;
                break;
            default:
                break;
        }
    }
    cout<<endl;
    
    return 0;
}
