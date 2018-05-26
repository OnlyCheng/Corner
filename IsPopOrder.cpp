//借助一个辅助栈来实现
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        int size1 = pushV.size();
        int size2 = popV.size();
        if(size1 != size2)
            return false;
        
        stack<int> s;//辅助栈
        int index = 0;
        int i = 0;
        for(; i<size2; i++)
        {
            //如果在辅助栈中还没有当前的数字，先将当前数字以及前边还没有压过的都压入辅助栈中
            while(index <= GetIndex(pushV,popV[i]))
                s.push(pushV[index++]);
            //栈顶元素与当前元素对比，相同则表示可以取到当前数字，直接将当前数字出栈，循环继续
            if(!s.empty() && s.top() == popV[i])
            {
                s.pop();
                continue;
            }
            //说明当前想要出栈的元素已经压入到辅助栈了且不在栈顶，那么，当前序列肯定不满足条件
            break;
        }
        if(i == size2)
            return true;
        return false;
    }
    
    int GetIndex(vector<int> pushV,int num)
    {
        int size = pushV.size();
        for(int i = 0; i<size; i++)
            if(pushV[i] == num)
                return i;
        return -1;
    }
};

