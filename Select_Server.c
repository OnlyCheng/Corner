#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_DATA 1024

//监听套接字的准备工作
int StartUp(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr)) ;
	if(ret < 0)
	{
		perror("bind");
		exit(3);
	}

	ret = listen(sock,5);
	if(ret < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}

//将保存文件描述符的数组的元素都初始化为-1
void Init(int* arr, int num)
{
	int i = 0;
	for(; i<num; i++)
	{
		arr[i] = -1;
	}
}

//新添要关心的文件描述符
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
	return -1;//添加失败
}

//重新设置要关心的文件描述符集
int Max_ResetRfds(int* arr, int num,fd_set* rfds)
{
	FD_ZERO(rfds);
	int fd_max = arr[0];
	for(int i = 0; i<num; i++)
	{
		int fd = arr[i];
		if(-1 != fd)
		{
			FD_SET(fd,rfds);
		}
		if(fd > fd_max)
			fd_max = fd;
	}
	return fd_max;
}

//提供服务
void Serverce(int* arr, int num, fd_set* rfds)
{
	for(int i = 0; i<num; i++)
	{
		int fd = arr[i];
		if(fd == -1)
			continue;
		//连接事件就绪
		if(i == 0 && FD_ISSET(fd,rfds))
		{
			struct sockaddr_in client_addr;
			socklen_t len = sizeof(client_addr);
			int connect_fd = accept(arr[0],(struct sockaddr*)&client_addr, &len);
			if(connect_fd < 0)
			{
				perror("accept");
				continue;
			}
			printf("get a connect:%s %d \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			if( AddFdToArray(connect_fd, arr, MAX_DATA)<0)
			{
				printf("array is ful\n");
				close(connect_fd);
			}
		}
		//其他读事件就绪
		else if(FD_ISSET(arr[i],rfds))
		{
			char buf[1024];
			ssize_t s = read(arr[i],buf,sizeof(buf)-1);
			if(s < 0)
			{
				perror("read");
				sleep(5);
			}
			else if(s == 0)
			{
				close(fd);
				arr[i] = -1;
				printf("client quit!\n");
			}
			else
			{
				buf[s] = 0;
				printf("client##:%s\n",buf);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if(2 != argc)
	{
		printf("./%s [port]\n",argv[0]);
		exit(1);
	}

	int listen_sock = StartUp(atoi(argv[1]));
	fd_set rfds;
	FD_ZERO(&rfds);

	int fd_array[MAX_DATA];
	Init(fd_array,MAX_DATA);
	
	int ret = AddFdToArray(listen_sock,fd_array,MAX_DATA);
	if(ret < 0)
	{
		return 3;
	}
	for(;;)
	{
		//重新设置文件描述符集
		int fd_max = Max_ResetRfds(fd_array, MAX_DATA, &rfds);
		if(fd_max == -1)
			continue;
		//调用select
		switch(select(fd_max+1,&rfds,NULL,NULL,NULL))
		{
			case -1:
				break;
			case 0:
				printf("timeout..\n");
				break;
			default:
				Serverce(fd_array,MAX_DATA, &rfds);
				break;
		}
	}
	return 0;
}
