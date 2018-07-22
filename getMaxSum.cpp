class MaxSum {
public:
    int getMaxSum(vector<int> A, int n) {
        if(n<=0)
            return 0;
        int res = A[0];
        int sum = A[0];
        for(int i = 1; i<n; i++)
        {
            sum += A[i];
            if(sum < A[i]) //前边的加上当前数的和比当前的数的值小，说明前边的和已经是负数了，那么抛弃它，重新开始计算当前的最大和
                sum = A[i];
            if(sum >= res)
                res = sum;
        }
        return res;
    }
};
