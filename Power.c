//求数值的整数次方
//方法1

class Solution {
public:
    double Power(double base, int exponent) 
    {
        if(exponent == 0)
            return 1;
        int n;
        if(exponent > 0)
            n = exponent;
        else
            n = -exponent;
        double ret = 1.0;
        while(n)
        {
            ret *= base;
            n--;
        }
        if(exponent > 0)
            return ret;
        else
            return 1/ret;
    }
};

//方法2
//主要是对while循环里边求次方的优化。将次幂化作二进制序列来表示，将每一以为求取出来，为1是乘以base
//由于比特位越高，代表需要乘以的倍数也就也就越高，所以每次以为都要交base翻倍
class Solution {
public:
    double Power(double base, int exponent) {
        double ret = 1.0;
        int n = exponent;
        if(exponent < 0)
            n = -n;
        while(n)
        {
            if(n&1)
                ret *= base;
            base *= base;
            n = n>>1;
        }
        return (exponent > 0)?ret:(1/ret);
    }
};
