#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BACKLOG 10

int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		printf("./tcpServer [addr:] [port:]\n");
		return 1;
	}
	int sock = socket(AF_INET, SOCK_STREAM,0);
	if(sock < 0)
	{
		printf("create sock error,errno is:%d errstring is: %s\n",errno,strerror(errno));
		return 2;
	}

	struct sockaddr_in server_socket;
	bzero(&server_socket,sizeof(server_socket));
	server_socket.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&server_socket.sin_addr);
	server_socket.sin_port = htons(atoi(argv[2]));

	if(connect(sock,(struct sockaddr*)&server_socket,sizeof(server_socket)) < 0)
	{
		printf("connect failed, errno is %d error string is %s\n",errno,strerror(errno));
		close(sock);
		return 3;
	}

	printf("connect success..\n ");
	
	char buf[1024];
	buf[0] = 0;
	while(1)
	{
		printf("client:## ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			write(sock,buf,strlen(buf));
			s = read(sock,buf,sizeof(buf));
			if(s > 0)
			{
				buf[s-1] = 0;
				if(strcmp(buf,"quit") == 0)
				{
					printf("Server requst to quit\n");
					return 0;
				}
				printf("server: $ %s\n",buf);
			}
		}
	}
	close(sock);
	return 0;
}
