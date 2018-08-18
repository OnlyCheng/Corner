#include <iostream>
using namespace std;
#include <vector>

struct Time
{
    int _s;
    int _end;
};

bool Compare(Time& t1,Time& t2)
{
    if(t1._s < t2._s)
    {
        if(t1._end > t2._s)
            return true;
        else
            return false;
    }
    else if(t1._s > t2._s)
    {
        if(t2._end > t1._s)
            return true;
        else
            return false;
    }
    else
        return true;
}

int FindSolution(vector<Time>& v,int n, vector<int>& res)
{
    if(n == 0)
        return 0;
    int count = 0;
    for(int i = 0;i<n; i++)
    {
        int j = 0;
        for(;j < n; j++)
        {
            if(i == j)
                continue;
            if(Compare(v[i],v[j]))//有交叉
                break;
        }
        if(j == n)
        {
            count++;
            res.push_back(i);
        }
    }
    return count;
}

int main()
{
    int n;
    cin>>n;
    vector<Time> v(n);
    for(int i = 0; i<n; i++)
    {
        cin>>v[i]._s>>v[i]._end;
    }
    vector<int> res;
    int ret = FindSolution(v,n,res);
    cout<<ret<<endl;
    for(int i = 0;i<res.size();i++)
    {
        if(i == res.size()-1)
            cout<<res[i]<<endl;
        else
     	   cout<<res[i]<<" ";
    }
     
    return 0;
}
