//等待与分离是相互矛盾的
#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
  
pthread_t ptid;  
  
void* thread_run(void* arg)  
{  
    pthread_detach(pthread_self());  
    printf("%s\n",(char*)arg);  
    return (void*)0;  
}  
  
int main()  
{  
    int ret;  
    ret = pthread_create(&ptid,NULL,thread_run,"new thread is running");  
    if(ret != 0)  
    {  
        printf("can't create a thread\n");  
        exit(0);  
    }  
  
    sleep(1);  
    ret = pthread_join(ptid,NULL);  
    if(ret == 0)  
        printf("thread wait success\n");  
    else  
        printf("thread wait failure\n");  
    return 0;  
    }
