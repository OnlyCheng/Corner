//删除数组中的指定元素，并将删除后的数组大小返回
class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        if(n <= 0)
            return 0;
        int r = n-1;
        int i = 0;
        for( ;i<=r;i++)
        {
            if(A[i] == elem)
            {
                swap(A[i],A[r]);
                i--;
                r--;
            }
        }
        return i;
    }
};
