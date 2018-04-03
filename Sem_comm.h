#ifndef __COMM_H__
#define __COMM_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
	struct seminfo* _buf;
}

#define ERR_EXIT(n) \
	do\
	{\
		perror("n");\
		exit(EXIT_FAILURE);\
	}while(0)

int creatSemSet(int nums);
int initSem(int semid,int nums,int initval);
int getSemSet(int nums);
int P(int semid,int num);
int V(int semid,int num);
int destroySetSet(int semid);

#endif
