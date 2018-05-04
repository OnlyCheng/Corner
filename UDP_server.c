#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc ,char* argv[])
{
	if(argc < 3)
	{
		printf("./server [addr:] [port:]\n");
		return 4;
	}

	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);
	
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		return 2;
	}

	char buf[1024];
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	while(1)
	{
		ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
		if(s<0)
		{
			perror("recvfrom");
			return 3;
		}
		else if(s == 0)
		{
			printf("client closed\n");
		}
		else
		{
			buf[s] = 0;
			printf("[%s : %d]:%s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&client,len);
			
			if(strcmp(buf,"quit") == 0)
				break;
		}

	}

	return 0;
}
