class Solution {
public:
    string ReverseSentence(string str) {
        int size = str.size();
        if(size == 0 || size == 1)
            return str;
        _reverse(str,0,size);
        str += ' ';
        int flag = 0;
        int tail = 0;
        for(int i = 0;i<size+1;i++)
        {
            if(str[i] == ' ' || str[i] == '\0')
            {
                _reverse(str,tail,i);
                tail = i+1;
                flag = 1;
            }
        }
        if(flag == 0)
            _reverse(str,0,size);
        str = str.substr(0,size);
        return str;
    }
    void _reverse(string& str,int l,int r)
    {
        while(l<r)
        {
            swap(str[l++],str[--r]);
        }
    }
};
