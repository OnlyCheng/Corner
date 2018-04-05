#include "comm.h"

static int CreatSem(int nums,int flags)
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
		ERR_EXIT("ftok");
	
	int semid = semget(key,nums,flags);
	if(semid < 0)
		ERR_EXIT("semget");
	return semid;
}

int creatSemSet(int nums)
{
	return CreatSem(nums,IPC_CREAT|IPC_EXCL|0666);
}

int initSem(int semid,int num,int initval)
{
	union semun un;
	un.val = initval;
	if(semctl(semid,num,SETVAL,un) < 0)
		ERR_EXIT("semctl");
	return 0;
}

int getSemSet(int nums)
{
	return CreatSem(nums,IPC_CREAT);
}

static int PV(int semid,int num,int op)
{
	struct sembuf _sf;
	_sf.sem_num = num;
	_sf.sem_op = op;
	_sf.sem_flg = 0;//NO_WAIT
	if(semop(semid,&_sf,1) < 0)
		ERR_EXIT("semop");
	return 0;
}

int P(int semid,int num)
{
	return PV(semid,num,-1);	
}

int V(int semid,int num)
{
	return PV(semid,num,1);
}

int destroySetSet(int semid)
{
	if(semctl(semid, 0, IPC_RMID)<0)
		ERR_EXIT("destroy");
	return 0;
}
