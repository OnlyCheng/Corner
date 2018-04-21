//方法1
//利用栈先进后出的特性将所有的数据压栈，再出栈，插入到vector对象里边去，实现元素的逆置。
    vector<int> printListFromTailToHead(ListNode* head)
    {
      vector<int> ret;
      stack<int> s;
      while(head)//将结点的数据压栈
      {
          s.push(head->val);
          head = head->next;
      }
      while(!s.empty())//将数据一一出栈并插入到vector里边去
      {
          ret.push_back(s.top());
          s.pop();
      }
        return ret;
    }
};

//方法2
//通过vector本身的接口，借助使用头插的方式将数据直接插入到数组里边
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head)
    {
      vector<int> ret;
      while(head)
      {
          ret.insert(ret.begin(),head->val);//借助迭代器实现头插
          head = head->next;
      }
       return ret;
    }
};


