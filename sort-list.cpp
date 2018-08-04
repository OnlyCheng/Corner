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
    ListNode *sortList(ListNode *head) {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode* res = NULL;
        multimap<int,ListNode*> mp;
        ListNode* pCur = head;
        while(pCur)
        {
            mp.insert(pair<int,ListNode*>(pCur->val,pCur));
            pCur = pCur->next;
        }
        multimap<int,ListNode*>::iterator it = mp.begin();
        res = it->second;
        ListNode* tail = res;
        ++it;
        while(it != mp.end())
        {
            tail->next = it->second;
            tail = tail->next;
            it++;
        }
        tail->next = NULL;
        return res;
    }
};
