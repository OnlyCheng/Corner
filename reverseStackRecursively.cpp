//使用递归函数和栈操作逆序栈
class ReverseStack {
public:
    vector<int> reverseStackRecursively(vector<int> stack, int top) {
        vector<int> res;
        if(top<1)
            return res;
        int size = stack.size();
        int temp = stack[size-top];//保存栈顶元素
        res = reverseStackRecursively(stack,top-1);//接收返回值，保证将所有的元素放入到一个数组中
        res.resize(size);
        res[top-1] = temp;
        return res;
    }
};
