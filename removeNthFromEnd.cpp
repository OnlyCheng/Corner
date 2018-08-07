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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if(head == NULL || n<0)
            return head;
        int len = 0;
        ListNode* pCur = head;
        while(pCur)
        {
            len++;
            pCur = pCur->next;
        }
        if(n > len)
            return head;
        if(n == len)
        {
            ListNode* del = head;
            head = head->next;
            delete del;
            return head;
        }
        pCur = head;
        ListNode* pPre = head;
        while(pCur->next)
        {
            if(n--<=0)
                pPre = pPre->next;
            pCur = pCur->next;
        }
        ListNode* del = pPre->next;
        if(del)
            pPre->next = del->next;
        else
            pPre->next = NULL;
        delete del;
        return head;
    }
};
