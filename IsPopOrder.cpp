//有缺陷的方法
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        int size1 = pushV.size();
        int size2 = popV.size();
        if(size1 != size2)
            return false;
        
        int max = GetSeqOfPush(pushV,popV[0]);
        int flag = 0;
        for(int i = 1; i<size2; i++)
        {
            int seq0 = GetSeqOfPush(pushV,popV[i-1]);
            int seq = GetSeqOfPush(pushV,popV[i]);
            if(seq0<0 || seq < 0)
                return false;
            if(seq > max)
            {
                max = seq;
                flag = i;
            }
            if(seq0 < seq && i>flag)
                return false;
        }
        return true;
        
    }
    int GetSeqOfPush(vector<int> pushV,int num)
    {
        int size = pushV.size();
        for(int i = 0; i<size; i++)
        {
            if(num == pushV[i])
                return i;
        }
        return -1;
    }
};

