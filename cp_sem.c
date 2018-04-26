#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <time.h>
int buf[20];
sem_t Blank;
sem_t Data;
void* consum(void* arg)
{
    int out = 0;
    while(1)
    {
        sem_wait(&Data);
        int data = buf[out];
        out++;
        out %= 20;
        printf("consum a data:%d\n",data);
        sem_post(&Blank);
    }
}
void* product(void* arg)
{
    int in = 0;
    while(1)
    {
        sem_wait(&Blank);
        int data = rand()%100;
        sleep(1);
        buf[in] = data;
        in ++;
        in %= 20;
        printf("product a data , is: %d\n",data);
        sem_post(&Data);
    }
}
int main()
{
    sem_init(&Blank,0,20);
    sem_init(&Data,0,0);
    srand((unsigned long)time(NULL));//方便后边使用rand函数
    pthread_t producer,consumer;
    pthread_create(&producer,NULL,product,NULL);
    pthread_create(&consumer,NULL,consum,NULL);
    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
    sem_destroy(&Blank);
    sem_destroy(&Data);
    return 0;
}
