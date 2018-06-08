class Solution {
public:
	/**
	 *	按照左右半区的方式重新组合单链表
	 *	输入：一个单链表的头指针head
	 *	将链表调整成题目要求的样子
	 *
	 *	后台的单链表节点类如下：
	 *
	 struct ListNode {
		int val;
		struct ListNode *next;
		ListNode(int x) :
				val(x), next(NULL) {
		}
	};
	 */
	void relocateList(struct ListNode* head) {
        if(NULL == head)
            return;
        int n = 0;
        typedef struct ListNode Node;
        typedef Node* pNode;
        pNode L = head;
        pNode R = head;
        pNode pPre = NULL;
        while(L)
        {
            n++;
            L = L->next;
        }
        L = R;
        int min = n>>1;
        while(min)
        {
            pPre = R;
            R = R->next;
            min--;
        }
        min = n>>1;
        while(min)
        {
            pPre->next = R->next;
            R->next = L->next;
            L->next = R;
            L = R->next;
            R = pPre->next;
            min--;
        }
    }
};
