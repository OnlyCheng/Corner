#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CONSUMERS 2
#define PRODUCERS 3
#define COUNT ((CONSUMERS) +(PRODUCERS))

pthread_mutex_t mutex,mutex_c,mutex_p;
pthread_cond_t cond;
pthread_t threads[COUNT];

typedef struct msg
{
    int _data;
    struct msg* _pNext;
}Node,*pNode;

pNode Head = NULL;

int Push_front(int data)
{
    pNode newNode = (pNode)malloc(sizeof(struct msg));
    if(NULL == newNode)
    {
        printf("创建新结点失败\n");
        return 0;
    }
    newNode->_data = data;
    newNode->_pNext = Head;
    Head = newNode;
    
    return 1;
}
int Pop_front()
{
    pNode del = Head;
    if(del == NULL)
        return 0;
    Head = del->_pNext;
    free(del);
    del = NULL;
    return 1;
}
void* consum(void* arg)    //消费者消费过程
{
    int n = *(int*)arg;
    free(arg);
    pthread_mutex_lock(&mutex);    //上锁
    while(Head == NULL)    //缓冲区里没有数据，基于条件变量进入等待
    {
        printf("there is nothing,please waitting\n");
        pthread_cond_wait(&cond,&mutex);
    }
    printf("consumer%d : %d\n",n,Head->_data);  //消费数据
    Pop_front();
    printf("consum end..\n",n);
    pthread_mutex_unlock(&mutex);    //解锁
}
void* product(void* arg)
{
    sleep(1);
    int n = *(int*)arg;
    free(arg);
    pthread_mutex_lock(&mutex);    //上锁
    printf("producter%d start to product %d\n",n,n);
    Push_front(n);                             //生产数据
    printf("product end..\n",n);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);    //解锁
}
int main()
{
    pthread_t tid1,tid2,tid3,tid4,tid5;
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex_c,NULL);
    pthread_mutex_init(&mutex_p,NULL);
    pthread_cond_init(&cond,NULL);

    //创建消费者线程
    for(int i=0; i<CONSUMERS; i++)
    {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_mutex_lock(&mutex_c);
        pthread_create(&threads[i], NULL, consum, (void*)p);
        pthread_mutex_unlock(&mutex_c);
    }

    //创建生产者线程
    for(int i=0; i<PRODUCERS; i++)
    {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_mutex_lock(&mutex_p);
        pthread_create(&threads[CONSUMERS+i], NULL, product, (void*)p);
        pthread_mutex_unlock(&mutex_p);
    }

    //主线程等待新线程
    for(int i=0; i < COUNT; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_c);
    pthread_mutex_destroy(&mutex_p);
    pthread_cond_destroy(&cond);
    
    return 0;
}
