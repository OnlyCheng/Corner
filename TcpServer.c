#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BACKLOG 10

int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		printf("./tcpServer [addr:] [port:]\n");
		return 1;
	}
	int listen_sock = socket(AF_INET, SOCK_STREAM,0);
	if(listen_sock < 0)
		printf("create listen_socket error,errno is:%d errstring is: %s\n",errno,strerror(errno));

	struct sockaddr_in server_socket;
	struct sockaddr_in client_socket;
	bzero(&server_socket,sizeof(server_socket));
	server_socket.sin_family = AF_INET;
	server_socket.sin_addr.s_addr = htonl(INADDR_ANY);
	server_socket.sin_port = htons(atoi(argv[2]));

	if(bind(listen_sock,(struct sockaddr*)&server_socket,sizeof(server_socket)) < 0)
	{
		printf("bind failed,errno is:%d ,errstring is:%s\n",errno,strerror(errno));
		close(listen_sock);
		return 2;
	}

	if(listen(listen_sock,BACKLOG) < 0)
	{
		printf("listen failed,errno is:%d ,errstring is:%s\n",errno,strerror(errno));
		close(listen_sock);
		return 3;
	}

	printf("bind done and listening,waitting accept..\n ");
	
	for(;;)
	{
		socklen_t len = 0;
		int client_sock = accept(listen_sock,(struct sockaddr*)&client_socket,&len);
		if(client_sock < 0)
		{
			printf("accept failed,errno is:%d ,errstring is:%s\n",errno,strerror(errno));
			close(listen_sock);
			return 4;
		}
		char buf_ip[INET_ADDRSTRLEN];
		buf_ip[0] = 0;
		inet_ntop(AF_INET,&client_socket.sin_addr.s_addr,buf_ip,sizeof(buf_ip));
		printf("get a connect,ip is: %s port is:%d\n",buf_ip,ntohs(client_socket.sin_port));
		while(1)
		{
			char buf[1024];
			buf[0] = 0;
			ssize_t s = read(client_sock,buf,sizeof(buf)-1);
			if(s > 0)
			{
				buf[s-1] = 0;
				if(strcmp(buf,"quit") == 0)
				{
					printf("client requet quit\n");
					return 0;
				}

				printf("client ## %s\n",buf);
				printf("server $$ ");
				fflush(stdout);
				memset(buf,'\0',sizeof(buf));
				s = read(0,buf,sizeof(buf)-1);
				if(s > 0)
				{
					buf[s-1] = 0;
					write(client_sock,buf,sizeof(buf)-1);	
				}
			}
		}
	}
	close(listen_sock);
	return 0;
}

