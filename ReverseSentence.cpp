//方法一  在原串末尾加上一个空格，处理完再去掉
class Solution {
public:
    string ReverseSentence(string str) {
        int size = str.size();
        if(size == 0 || size == 1)
            return str;
        _reverse(str,0,size);
        str += ' ';  //给原串后边添加一个空格，
        int flag = 0;
        int tail = 0;
        for(int i = 0;i<size+1;i++)
        {
            if(str[i] == ' ' || str[i] == '\0')//以空格作为一个单词结束的标志
            {
                _reverse(str,tail,i);
                tail = i+1;
                flag = 1;
            }
        }
        if(flag == 0)
            _reverse(str,0,size);
        str = str.substr(0,size);//去掉最初加上的空格
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


//方法二，借助库函数
class Solution {
public:
    string ReverseSentence(string str) {
        int size = str.size();
        if(size == 0 || size == 1)
            return str;
        int tail = 0;
        for(int i = 0;i<size;i++)
        {
            if(str[i] == ' ')//以空格作为结束的标志
            {
                reverse(str.begin()+tail,str.begin()+i);
                tail = i+1;
            }
            else if(i == size-1)//已经到达最后一个字符了，也代表一个单词结束了
                reverse(str.begin()+tail,str.begin()+i+1);
        }
        reverse(str.begin(),str.end());
        return str;
    }
};
