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
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        int len1 = 0;
        int len2 = 0;
        ListNode* pCur = pHead1;
        ListNode* first = pHead1;
        ListNode* second = pHead2;
        while(pCur)
        {
            len1++;
            pCur = pCur->next;
        }
        pCur = pHead2;
        while(pCur)
        {
            len2++;
            pCur = pCur->next;
        }
        int dif = 0;
        if(len1 > len2)
            dif = len1-len2;
        else
        {
            first = pHead2;
            second = pHead1;
            dif = len2 - len1;
        }
        while(first)
        {
            if(second == first)
                break;
            first =  first->next;
            if(--dif < 0)
                second = second->next;
        }
       if(first)
           return first;
       else
           return NULL;
    }
};
