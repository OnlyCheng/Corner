class Solution {
public:
    string LeftRotateString(string str, int n) {
        int len = str.length();
        if(len == 0 || n >= len || n == 0)
            return str;
        
        reverse(str,0,n-1);
        reverse(str,n,len-1);
        reverse(str,0,len-1);
         return str;
    }
    
    void reverse(string& str, int left,int right)
    {
        while(left <= right)
        {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;right--;
        }
    }
};
