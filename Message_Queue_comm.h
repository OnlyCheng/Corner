#ifndef __COMM_H__
#define __COMM_H__

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define PATHNAME "/home/guaiguai"
#define PROJ_ID 0x7777

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct MyMsg
{
	long mtype;
	char mtext[1024];
};

int CreateMsgQueue();
int GetMsgQueue();
int DestroyQueue(int msg_id);
int SendMsg(int msg_id,int sendtype,char* massege);
int RecvMsg(int msg_id,int recvtype,char out[]);

#endif
