#ifndef __COMM_H__  
#define __COMM_H__  
  
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
#include <stdlib.h>  
  
#define PATHNAME "."  
#define PROJ_ID 0x6666  
  
#define ERR_EXIT(n)\  
    do\  
    {\  
        perror(n);\  
        exit(EXIT_FAILURE);\  
    }while(0)  
  
int CreatShm(int size);  
int DestroyShm(int shm_id);  
int GetShm(int size);  
  
#endif  
