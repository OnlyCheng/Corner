#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void* routine(void* arg)
{
	int count = 3;
    while(count--)
    {
        printf("I'm new thread,pid is:%u tid is:%u\n",getpid(),(unsigned int)pthread_self());
        sleep(1);
    }
    exit(0);
}
int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,routine,NULL);
    if(ret != 0)
    {
        fprintf(stderr,"pthread_create err:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        sleep(1);
        printf("I'm main thread,pid is:%u tid is:%u\n",getpid(),(unsigned int)pthread_self());
    }
    return 0;
}
