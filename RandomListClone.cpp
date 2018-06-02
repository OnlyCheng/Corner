/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(NULL == pHead)
            return NULL;
        RandomListNode* pCur = pHead;
        RandomListNode* newHead = NULL;
        //将新链表插入到原链表中
        while(pCur)
        {
            RandomListNode* p = new RandomListNode(pCur->label);
            p->next = pCur->next;
            pCur->next = p;
            pCur = p->next;
        }
        
        //跟新新链表的random指针域
        pCur = pHead;
        while(pCur)
        {
            if(pCur->random == NULL)
                pCur->random = NULL;
            else
                pCur->next->random = pCur->random->next;
            pCur = pCur->next->next;
        }
        //将新链表从原链表里边拆下来
        pCur = pHead;
        newHead = pCur->next;
        RandomListNode* p = newHead;
        while(pCur)
        {
            pCur->next = p->next;
            if(pCur->next)
                p->next = pCur->next->next;
            else
                p->next = NULL;
            p = p->next;
            pCur = pCur->next;
        }
        return newHead;
    }
};
