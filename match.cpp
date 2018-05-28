class Solution {
public:
    bool match(char* str, char* pattern)
    {
        if(NULL == str || NULL == pattern)
            return false;
        
        return _match(str,pattern);
    }
    
    bool _match(char* str, char* pattern)
    {
        if('\0' == *str && '\0'== *pattern)
            return true;
        
        if(*str != '\0' && '\0'== *pattern)
            return false;
        
        if(*(pattern+1) == '*')
        {
            if(*str == *pattern || ('.' == *pattern && *str!= '\0'))
                return _match(str,pattern+2)||_match(str+1,pattern)||_match(str+1,pattern+2);
            else
                return _match(str,pattern+2);
        }
        if(*str == *pattern || ('.' == *pattern&&*str!= '\0'))
            return _match(str+1,pattern+1);
        
        return false;
    }
};
