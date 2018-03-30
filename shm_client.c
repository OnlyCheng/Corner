#include "comm.h"  
  
int main()  
{  
    int shm_id = GetShm(4096);  
    sleep(1);  
    char* addr = shmat(shm_id, NULL, 0);  
    int i = 0;  
    printf("hdifhowie\n");  
    while(i < 26)  
    {  
        addr[i] = 'A'+i;  
        i++;  
        addr[i] = 0;  
        sleep(1);  
    }  
  
    shmdt(addr);  
    sleep(2);  
    return 0;  
}  
