/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode* pHead = NULL;
        ListNode** ppHead = &pHead;
        while(pHead1 && pHead2)
        {
            if(pHead1->val < pHead2->val)
            {
                 *ppHead = pHead1;
                pHead1 = pHead1->next;
            }
            else
            {
                *ppHead = pHead2;
                pHead2 = pHead2->next;
            }
            ppHead = &((*ppHead)->next);
        }
        if(pHead1 == NULL)
            *ppHead = pHead2;
        else
            *ppHead = pHead1;
        return pHead;
    }
};
