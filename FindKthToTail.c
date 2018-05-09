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
        if(pListHead == NULL)
            return NULL;
        ListNode* first = pListHead;
        ListNode* second = pListHead;
        while(first && k > 0)
        {
            first = first->next;
            k--;
        }
        if(first == NULL && k!=0)
            return NULL;
        while(first)
        {
            second = second->next;
            first = first->next;
        }
        return second;
    }
};
