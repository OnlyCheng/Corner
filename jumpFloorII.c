//方法1---递归
class Solution {
public:
    int jumpFloorII(int number) {
        if(number <= 0)
            return 0;
        if(number == 1)
            return 1;
        else
            return 2*jumpFloorII(number-1);
    }
};

//方法2 ---递归
class Solution {
public:
    int jumpFloorII(int number) {
        if(number <= 0)
            return 0;
        else
            return _jumpFloor(1,number);
    }
    int _jumpFloor(int pre,int number)
    {
        if(number == 1)
            return pre;
        else
            return _jumpFloor(2*pre,number-1);
    }
};

//方法3 ---循环
class Solution {
public:
    int jumpFloorII(int number) {
        if(number <= 0)
            return 0;
        int n = 1;
        for(int i = 0; i < number-1; i++)
        {
            n = 2*n;
        }
        return n;
    }
};
