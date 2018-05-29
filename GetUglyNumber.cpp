class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index < 7 && index >= 0)
            return index;
        vector<int> res(index);
        res[0] = 1;
        int id2 = 0, id3 = 0, id5 = 0;
        for(int i = 1; i<index; i++)
        {
            res[i] = min(res[id2]*2,min(res[id3]*3,res[id5]*5));
            if(res[i] == res[id2]*2)
                id2++;
            if(res[i] == res[id3]*3)
                id3++;
            if(res[i] == res[id5]*5)
                id5++;
        }
        return res[index-1];
    }
};
