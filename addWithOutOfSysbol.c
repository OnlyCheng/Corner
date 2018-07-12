//方法一
class Solution {
public:
    int Add(int num1, int num2)
    {
        int flag = 1;
        int temp = num1;
        while(flag)
        {
            temp = num1^num2;
            flag = (num1&num2)<<1;
            num1=temp;
            num2 = flag;
        }
        return num1;
    }
};

//方法二
class Solution {
public:
    int Add(int num1, int num2)
    {
        if(num2 == 0)
            return num1;
        else
            return Add(num1^num2,(num1&num2)<<1);
    }
};
