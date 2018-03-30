#include "comm.h"  
  
static int Creat(int size,int flags)  
{  
    key_t key = ftok(PATHNAME,PROJ_ID);  
    if(key < 0)  
        ERR_EXIT("ftok");  
      
    int shmid = 0;  
    if((shmid = shmget(key,size,flags)) < 0)  
        ERR_EXIT("shmget");  
      
    return shmid;  
}  
  
int DestroyShm(int shm_id)  
{  
    if(shmctl(shm_id,IPC_RMID,NULL)<0)  
        ERR_EXIT("shmctl");  
    return 0;  
}  
  
int CreatShm(int size)  
{  
    return Creat(size, IPC_CREAT|IPC_EXCL|0666);  
}  
  
int GetShm(int size)  
{  
    return Creat(size, IPC_CREAT);  
}  
