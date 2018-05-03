//方法1
class Solution {
public:
    int jumpFloor(int number) {
        if(number == 0)
            return 0;
        if(number == 1)
            return 1;
        if(number == 2)
            return 2;
        else
            return jumpFloor(number-1)+jumpFloor(number-2);
    }
};

//方法2
class Solution {
public:
    int jumpFloor(int number) {
        int left = 1;
        int right = 1;
        return _jumpFloor(left,right,number);
    }
    int _jumpFloor(int left,int right,int number)
    {
        if(number <= 0)
            return 0;
        if(number == 1)
            return 1;
        if(number == 2)
            return left+right;
        else
            return _jumpFloor(right,left+right,--number);
    }
};
