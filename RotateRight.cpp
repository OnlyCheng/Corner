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
        if(head == NULL || head->next == NULL)
            return head;
        ListNode* pCur = head;
        int len = 0;
        while(pCur)
        {
            len++;
            pCur = pCur->next;
        }
        pCur = head;
        k %= len;
        ListNode* second = head;
        while(pCur->next)
        {
            if(k--<=0)
                second = second->next;
            pCur = pCur->next;
        }
        pCur->next = head;
        head = second->next;
        second->next = NULL;
        return head;
    }
};
