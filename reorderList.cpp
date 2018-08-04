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
    void reorderList(ListNode *head) {
        if(NULL == head)
            return;
        ListNode* pCur = head;
        vector<ListNode*> v;
        while(pCur)
        {
            v.push_back(pCur);
            pCur = pCur->next;
        }
        int size = v.size();
        int l = 0;
        int r = size-1;
        while(l<r)
        {
            v[r]->next = v[l]->next;
            v[l]->next = v[r];
            l++;
            r--;
        }
        v[l]->next = NULL;
    }
};
