class Solution {
public:
    void push(int value) {
        s1.push(value);
        if(s2.empty())
            s2.push(value);
        else
            if(s2.top() > value)
                s2.push(value);
    }
    void pop() {
        if(s2.top() == s1.top())
            s2.pop();
        s1.pop();
    }
    int top() {
        return s1.top();
    }
    int min() {
        return s2.top();
    }
private:
    stack<int> s1;
    stack<int> s2;
};
