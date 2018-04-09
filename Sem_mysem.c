#include "comm.h"

int main()
{
	int semid = creatSemSet(1);
	if(initSem(semid,0,1) < 0)
		ERR_EXIT("init");
	
	pid_t id = fork();
	if(id == 0)//child
	{
		int _semid = getSemSet(0);
		while(1)
		{
			P(_semid,0);
			printf("A");
			fflush(stdout);
			usleep(123456);
			printf("A ");
			fflush(stdout);
			sleep(1);
			V(_semid,0);
		}
	}
	else//father
	{
		while(1)
		{
			P(semid,0);
			printf("B");
			fflush(stdout);
			usleep(123456);
			printf("B ");
			fflush(stdout);
			sleep(1);
			V(semid,0);
		}
		wait(NULL);
	}

	destroySemSet(semid);
	return 0;
}