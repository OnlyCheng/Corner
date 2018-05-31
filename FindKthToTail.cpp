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
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(NULL == pListHead)
            return NULL;
        
        ListNode* pF = pListHead;
        ListNode* pC = pListHead;
        
        while(pF)
        {
            pF = pF->next;
            if(k!= 0 )
            {
                k--;
                continue;
            }
            pC = pC->next;
        }
        if(k)//考虑k比结点个数大的情况
            return NULL;
        return pC;
    }
};
