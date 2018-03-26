#include "comm.h"

int main()
{
	int msg_id = GetMsgQueue();
	char buf[1024] = {0};

	while(1)
	{
		printf("please enter: ");
		fflush(stdout);

		ssize_t s = read(0,buf,sizeof(buf));
		if(s > 0)
		{
			buf[s-1] = 0;
			SendMsg(msg_id,CLIENT_TYPE,buf);
			if(strcasecmp("quit",buf) == 0)
				break;
			printf("please waiting..\n");
		}
		RecvMsg(msg_id,SERVER_TYPE,buf);
		printf("##server said:## %s\n",buf);
		if(strcasecmp("quit",buf) == 0)
			break;
	}

	DestroyQueue(msg_id);
	return 0;
}
