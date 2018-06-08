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
    ListNode *rotateRight(ListNode *head, int k) {
        if(NULL == head || k<=0)
            return head;
        ListNode* first = head;
        ListNode* second = head;
        
        while(first->next)
        {
            first = first->next;
            if(--k < 0)
                second = second->next;
        }
        if(k>=0)
            return NULL;
        first->next = head;
        head = second->next;
        second->next = NULL;
        
        return head;
    }
};
