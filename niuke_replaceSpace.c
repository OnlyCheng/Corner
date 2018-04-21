class Solution {
public:
	void replaceSpace(char *str,int length) {
        if(NULL == str)
            return;
        int oldlen = 0;
        int count = 0;
        //计算字符串的长度以及空格的个数
        for(int i = 0;str[i]!='\0';i++)
        {
             oldlen++;
            if(str[i] == ' ')
                count++;
        }
        //求得字符串替换后的长度
        int len = oldlen + 2*count;
        //原空间不够大的话就不进行替换
        if(len > length)
            return;
        
        str[len] = 0;
        oldlen--;
        //替换过程
        while(len > 0)
        {
            if(str[oldlen] != ' ')
                str[--len] = str[oldlen];
            else
            {
                str[--len] = '0';
                str[--len] = '2';
                str[--len] = '%';
            }
            oldlen--;
        }
	}
};
