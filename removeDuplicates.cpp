class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n == 0)
            return 0;
        int res = 0;
        for(int i = 1; i<n; i++)
        {
            if(A[res] != A[i])
            {
                A[++res] = A[i];//将不重复的元素插入到数组中
            }
        }
        return res+1;
    }
};
