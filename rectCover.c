//其实就是斐波那契数列
//方法1
class Solution {
public:
    int rectCover(int number) {
        if(number <= 0)
            return 0;
        else if(number < 3)
            return number;
        else
            return rectCover(number-1) + rectCover(number-2);
    }
};

//方法2
class Solution {
public:
    int rectCover(int number) {
        if(number <= 0)
            return 0;
        return _rectCover(1,2,number);
    }
    int _rectCover(int first,int second,int number)
    {
        if(number == 1)
            return first;
        else if(number == 2)
            return second;
        else
            return _rectCover(second,first+second,--number);
    }
};

//方法3
class Solution {
public:
    int rectCover(int number) {
        if(number <= 0)
            return 0;
        int n1 = 1;
        int n2 = 1;
        for(int i = 0;i < number-1; i++)
        {
            int temp = n2;
            n2 += n1;
            n1 = temp;
        }
        return n2;
    }
};
