#include <stdio.h>
#include <string.h>
void Reverse(char *str, int len, int left, int right)
{
    if(NULL == str || left >= right || right > len)
        return;
    while(left < right)
    {
        char ch = str[left];
        str[left] = str[right];
        str[right] = ch;
        ++left;
        --right;
    }
}

char* ReverseString(char* str, int len)
{
    int i = 0;
    int start = 0;
    if(NULL == str || len < 2)
        return str;
    Reverse(str, len, 0, len-1);
    for(i = 0; i < len+1; ++i)
    {
        if((str[i] == ' ' || str[i] == '\0') && i-start > 1)
        {
            Reverse(str, len, start, i-1);
            start = i+1;
        }
    }
    return str;
}

int main()
{
    char buf[128] = { 0 };
    int len = 0;
    gets(buf);
    len = strlen(buf);
    ReverseString(buf, len);
    printf("%s\n", buf);
    
    return 0;
}
