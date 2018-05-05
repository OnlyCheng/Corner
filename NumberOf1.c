//二进制中1的个数

//方法1
class Solution {
public:
     int  NumberOf1(int n) {
         if(n == 0)
             return 0;
         int count = 0;
         for(int i = 0; i< 32; i++)
         {
             if((n >> i)&1 == 1)
                 count++;
         }
         return count;
     }
};

//方法2
class Solution {
public:
     int  NumberOf1(int n) {
         if(n == 0)
             return 0;
         int count = 0;
         while(n)
         {
             ++count;
             n = n&(n-1);
         }
         return count;
     }
};
