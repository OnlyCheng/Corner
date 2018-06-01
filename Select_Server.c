#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>

#define MAX_DATA 1024

int StartUp(int port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	addr.sin_port = port;

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0);
	{
		perror("bind");
		exit(3);
	}

	int ret = listen(sock,5);
	if(ret < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}

void Init(int* arr, int num)
{
	int i = 0;
	for(; i<num; i++)
	{
		arr[i] = -1;
	}
}

int AddFdToArray(int fd,int* arr, int num)
{
	int i = 0;
	for(; i<num; i++)
	{
		if(-1 == arr[i])
		{
			arr[i] = fd;
			return i;
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	if(2 != argc)
	{
		printf("./%s [port]\n",argv[0]);
		exit(1);
	}

	int listen_sock = StartUp(atoi(argv[1]));
	fd_set* rfds;
	FD_ZERO(rfds);

	int fd_array[MAX_DATA];
	Init(fd_array,MAX_DATA);
	
	int ret = AddFdToArray(listen_sock,fd_array,MAX_DATA);
	if(ret < 1)
	{
		return 3;
	}
	for(;;)
	{
		//重新设置文件描述符集
		int fd_max = fd_array[0];
		for(int i = 0; i<MAX_DATA; i++)
		{
			int fd = fd_array[i];
			if(-1 != fd)
			{
				FD_SET(fd,rfds);
				if(fd > fd_max)
					fd_max = fd;
			}
		}
		//调用select
		select(fd_max+1,rfds,NULL,NULL,NULL);
		for(int i = 0; i<MAX_DATA; i++)
		{
			int fd = fd_array[i];
			if(FD_ISSET(fd,rfds))
			{
				//连接事件就绪
				if(fd == fd_array[0])
				{
					struct sockaddr_in client_addr;
					socklen_t len = sizeof(client_addr);
					int connect_fd = accept(listen_sock,(struct sockaddr*)&client_addr, &len);
					if(connect_fd < 0)
					{
						perror("accept");
						continue;
					}
					printf("get a connect:%s %d \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
					AddFdToArray(connect_fd,fd_array,MAX_DATA);
					continue;
				}
				//其他读事件就绪
				char buf[1024] = {0};
				ssize_t s = read(fd,buf,1023);
				if(s < 0)
				{
					close(fd);
					fd_array[i] = -1;
					perror("read");
					continue;
				}
				else if(s == 0)
				{
					close(fd);
					fd_array[i] = -1;
					printf("client quit!\n");
					continue;
				}
				buf[s] = 0;
				printf("client## %s\n",buf);
			}
		}
		close(listen_sock);
	}
	return 0;
}
