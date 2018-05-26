#include <iostream>
using namespace std;
#include <vector>
#include <iomanip>

typedef struct Goods
{
    float _price;
    int _discount;
};

float MostFavorablePrice(vector<Goods> v,int n,int m)
{
    float min = 0.0;
    float sum = 0.0;
    
    //按照特价优惠的方式来购买所需价格
    for(int i = 0; i < n; i++)
    {
        if(v[i]._discount)
            sum += (v[i]._price*8)/10;
        else
            sum += v[i]._price;
    }
    min = sum;
    float s = 0;
    
    //计算所有商品不打折时的总价s
    for(int j = 0; j<n; j++)
    {
        s += v[j]._price;
    }
    
    //计算每一种满减活动所需价格
    for(int i = n; i<n+m; i++)
    {
        if(s >= v[i]._price)//达到满减的条件
            sum = s - v[i]._discount;
        if(sum < min)
            min = sum;
    }
    return min;
}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<Goods> v;
    v.resize(n+m);
    for(int i = 0;i<n+m; i++)
    {
        cin>>v[i]._price>>v[i]._discount;
    }
    
    float ret = MostFavorablePrice(v,n,m);
    cout<<setiosflags(ios::fixed)<<setprecision(2);
    cout<<setprecision(2)<<ret<<endl;
    return 0;
}
