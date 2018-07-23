#include <iostream>
using namespace std;
#include <iostream>
using namespace std;

int main()
{
    string s1;
    string s2;
    while(cin>>s1>>s2)
    {
        string res;
        int len1 = s1.size()-1;
        int len2 = s2.size()-1;
        int carry = 0;
        
        while(len1 >= 0 && len2 >= 0)
        {
            int n1 = s1[len1]-'0';
            int n2 = s2[len2]-'0';
            int n = n1+n2+carry;
            carry = n/10; 
            char c = n %10 +'0';
            res.insert(res.begin(),c);
            len1--;len2--;
        }
        while(len1>=0)
        {
            int n1 = s1[len1]-'0';
            int n = n1+carry;
            carry = n/10; 
            char c = n % 10 +'0';
            res.insert(res.begin(),c);
            len1--;
        }
        while(len2>=0)
        {
            int n2 = s2[len2]-'0';
            int n = n2+carry;
            carry = n/10; 
            char c = n % 10 +'0';
            res.insert(res.begin(),c);
            len2--;
        }
        if(carry)
            res.insert(res.begin(),'1');
        cout<<res<<endl;
    }
    
    return 0;
}
