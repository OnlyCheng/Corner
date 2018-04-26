#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex ;
pthread_cond_t cond ;
void* thread_run1(void* arg)
{    
    pthread_cond_wait(&cond,&mutex);
    printf("条件满足\n");
}
void* thread_run2(void* arg)
{
    sleep(2);
    pthread_cond_signal(&cond);
    printf("已发送条件满足信号\n");
}
int main()
{
    pthread_t tid1,tid2;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&tid1,NULL,thread_run1,"thread1:");
    pthread_create(&tid2,NULL,thread_run2,"thread2:");
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
