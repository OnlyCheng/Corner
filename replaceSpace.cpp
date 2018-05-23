class Solution {
public:
	void replaceSpace(char *str,int length) {
        if(NULL == str)
            return;
        int oldlen = 0;
        int count = 0;
        for(int i = 0;str[i]!='\0';i++)
        {
             oldlen++;
            if(str[i] == ' ')
                count++;
        }
        int len = oldlen + 2*count;
        
        if(len > length)
            return;
        
        str[len] = 0;
        oldlen--;
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
