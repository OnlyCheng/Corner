#include "comm.h"

int Creat(int flag);
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
	{
		perror("frok");
		return -1;
	}

	int msg_id = msgget(key,flag);
	if(msg_id < 0)
	{
		perror("msgget");
		return -2;
	}
	return msg_id;
}

int CreateMsgQueue()
{
	return Creat(IPC_CREAT|IPC_EXCL);
}

int GetMsgQueue()
{
	return Creat(IPC_CREAT);
}

int DestroyQueue(int msg_id)
{
	if(msgctl(msg_id,IPC_RMID,NULL) < 0)
	{
		perror("msgctl");
		return -1;
	}

	return 0;
}

int SendMsg(int msg_id,int sendtype,char* massege)
{
	struct MyMsg mymsg;
	mymsg.mtype = sendtype;
	strcpy(mymsg.mtext,massege);

	if(msgsnd(msg_id,(void*)&mysmg,sizeof(mymsg.mtext),0) < 0)
	{
		perror("msgsnd");
		return -1;
	}
	
	return 0;
}
int RecvMsg(int msg_id,int recvtype,char out[])
{
	struct MyMsg mymsg;
	if(msgrcv(msg_id,(void*)&mymsg,sizeof(mymsg.mtest),recvtype,0) < 0)
	{
		perror("msgrcv");
		return -1;
	}

	strcpy(out,mymsg.mtext);
	return 0;
}

