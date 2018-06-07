#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("./Server [addr:] [port:]\n");
		return 1;
	}
	int sock = socket(AF_INET, SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}

	struct sockaddr_in server_socket;
	server_socket.sin_family = AF_INET;
	server_socket.sin_addr.s_addr=inet_addr(argv[1]);
	server_socket.sin_port = htons(atoi(argv[2]));

	printf("start connet..\n ");
	if(connect(sock,(struct sockaddr*)&server_socket,sizeof(server_socket)) < 0)
	{
		perror("connect");
		close(sock);
		return 3;
	}

	printf("connect success..\n ");
	char buf[1024];
	buf[0] = 0;
	while(1)
	{
		printf("please enter>: ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			write(sock,buf,strlen(buf));
		}
		buf[0] = 0;
		s = read(sock,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			printf("server$$ %s\n",buf);
		}
		buf[0] = 0;
	}
	close(sock);
	return 0;
}
