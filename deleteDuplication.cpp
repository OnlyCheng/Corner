/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(NULL == pHead)
            return pHead;
        ListNode* pCur = pHead;
        ListNode* pPre = NULL;
        while(pCur)
        {
            ListNode* Next = pCur->next;
            if(Next)
            {
                if(Next->val == pCur->val)
                {
                    while(Next && Next->val == pCur->val)
                        Next = Next->next;
                    if(pCur == pHead)
                        pHead = Next;
                    else
                    {
                        pPre->next = Next;
                        pCur = pPre;
                    }
                        
                }
            }
            pPre = pCur;
            pCur = pCur->next;
        }
        return pHead;
    }
};
