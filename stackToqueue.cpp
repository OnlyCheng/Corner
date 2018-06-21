//方法1
//使用两个栈，一个当做辅助栈，入队列就是入栈操作
//出队列的时候先将所有的元素倒入到辅助栈，然后取出栈顶，再将剩下的元素倒入到原来的栈中
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int ret = 0;
        while(!stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        if(!stack2.empty())
        {
            ret = stack2.top();
            stack2.pop();
        }
        while(!stack2.empty())
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

//方法2
//入队列就是入栈，出队列的话从辅助栈里边出
//如果辅助栈为空，则先将原来栈中的元素倒入到辅助栈中
//辅助栈专门用来出栈，辅助栈中的元素出完了，再将原来的栈中的元素倒入到辅助栈中。
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int ret;
        if(stack2.empty())
        {
            while(!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        if(!stack2.empty())
        {
            ret = stack2.top();
            stack2.pop();
        }
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
