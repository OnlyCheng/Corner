class Solution {
public:
    string multiply(string num1, string num2) {
        int s1 = num1.size();
        int s2 = num2.size();
        int s = s1+s2;
        string res(s,'0');
        
        if(s1 == 0 || s2 == 0 || num1 == "0" || num2 == "0")
        {
            res = "0";
            return res;
        }
        for(int i = s2-1; i >= 0; i--)
        {
            int carry = 0;
            int n1 = num2[i]-'0';
            for(int j = s1-1; j>=0; j--)
            {
                int n2 = num1[j]-'0';
                int sum = res[i+j+1]-'0'+n1*n2+carry;
                carry = sum/10;
                char c = sum%10+'0';
                res[i+j+1] = c;
            }
            if(carry)
                res[i] = carry+'0';
        }
        const char* p = res.c_str();
        while(p[0] == '0')
            p++;
        res = p;
      //  int i = 0;
      //  while (i<res.size()&&res[i]=='0') ++i;
      //  return i==res.size()?"0":res.substr(i);
        return res;
    }
};
