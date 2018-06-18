    
   //求1+2+3+...+n，不能使用while for if else switch case等关键字
   int Sum_Solution(int n) {
        int i = 1;
        int sum = 0;
        return Sum(n,i,sum);
    }
    int Sum(int n,int& i,int& sum)
    {
        sum += i;
        return (n == i)? sum :(Sum(n,++i,sum));
    }
