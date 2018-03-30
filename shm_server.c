#include "comm.h"  
  
int main()  
{  
    int shm_id = CreatShm(4096);  
    char* addr = shmat(shm_id,NULL,0);  
    sleep(2);  
    int i = 0;  
    while(i++ < 26)  
    {  
        printf("client said:%s\n",addr);  
        sleep(1);  
    }  
  
    shmdt(addr);  
    sleep(2);  
    DestroyShm(shm_id);  
  
    return 0;  
}  
