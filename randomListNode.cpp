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
        RandomListNode* Head = NULL;
        RandomListNode* pCur = pHead;
        if(pHead == NULL)
            return NULL;
        //复制原链表，将其插到对应结点的后边，
        while(pCur)
        {
            RandomListNode* newNode = new RandomListNode(pCur->label);
            newNode->next = pCur->next;
            pCur->next = newNode;
            pCur = newNode->next;
        }
        //更新random指针
        pCur = pHead;
        RandomListNode* p = pCur->next;
        while(pCur)
        {
            if(pCur->random)
                p->random = pCur->random->next;
            pCur = p->next;
            if(pCur)
                p = pCur->next;
        }
        //将新链表与原链表拆开
        pCur = pHead;
        Head = pCur->next;
        p = pCur->next;
        while(pCur)
        {
            p = pCur->next;
            pCur->next = p->next;
            if(pCur->next)
                p->next = pCur->next->next;
            pCur = pCur->next;
        }
        return Head;
    }
};
