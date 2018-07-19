/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        if(NULL == head)
            return head;
        ListNode* cur = head;
        ListNode* pre = NULL;
        ListNode* p = NULL;
        while(cur)
        {
            if(pre == NULL)
            {
                pre = cur;
                cur = cur->next;
                continue;
            }
            //交换
            pre->next = cur->next;
            cur->next = pre;
            if(p)
                p->next = cur;
            else
                head = cur;
            
            swap(pre,cur);
            
            if(cur->next)
            {
                p = cur;
                pre = cur->next;
                cur = pre->next;
            }
            else
                break;
        }
        return head;
    }
};
