//要跳n级台阶，假设前边n-1级台阶已经跳完成，将n-1级台阶看做一个整体，那么，到第n级台阶有两种跳法，
//先跳一级，再跳n-1级或先跳n-1级，再跳1级。那么只要将前边跳n-1级的方法与这两种方法组合起来就可以了
class Solution {
public:
    int jumpFloorII(int number) {
        if(1 == number)
            return 1;
        else 
            return 2*jumpFloorII(number-1);
    }
};
