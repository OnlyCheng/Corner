class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int size = array.size();
        if(size == 0)
            return;
        vector<int> temp;
        for(int i=0; i<size; i++)
        {
            if(array[i]%2 == 1)
                temp.push_back(array[i]);
        }
        for(int i=0; i<size; i++)
        {
            if(array[i]%2 == 0)
                temp.push_back(array[i]);
        }
        array = temp;
    }
};
