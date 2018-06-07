#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 256

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

void ServiceForRead(int listen_sock, int fd, int epoll_fd)
{
	struct epoll_event event;
	if(fd == listen_sock)//连接
	{
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		int connect_fd = accept(listen_sock,(struct sockaddr*)&client_addr, &len);
		if(connect_fd < 0)
			return;

		printf("get a connect : %s : %d\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		event.events = EPOLLIN;
		event.data.fd = connect_fd;
		epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connect_fd,&event);
	}
	else
	{
		char buf[1024];
		ssize_t s = read(fd,buf,sizeof(buf)-1);
		if(s < 0)
		{
			perror("read");
		}
		else if(s == 0)
		{
			printf("client quit~\n");
			epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,NULL);
			close(fd);
		}
		else
		{
			buf[s-1] = 0;
			printf("client## : %s\n",buf);
			event.events = EPOLLIN|EPOLLOUT;
			event.data.fd = fd;
			epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&event);
		}
				
	}
}

void ServiceForWrite(int fd)
{
	char buf[1024];
	int s = read(0,buf,sizeof(buf)-1);
	if(s > 0)
	{
		buf[s-1] = 0;
		write(fd,buf,strlen(buf));
	}
}

int main(int argc, char* argv[])
{
	if(2 != argc)
	{
		printf("Usage: %s : [port]",argv[0]);
		return 1;
	}

	int listen_sock = StartUp(atoi(argv[1]));
	
	int epoll_fd = epoll_create(MAX);
	if(epoll_fd < 0)
	{
		perror("epoll_create");
		return 5;
	}

	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = listen_sock;
	int ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_sock,&event);
	if(ret < 0)
	{
		perror("event_ctl");
		return 6;
	}

	for(;;)
	{
		struct epoll_event events[MAX];
		int size = epoll_wait(epoll_fd,events, MAX , -1);
		if(size < 0)
		{
			perror("epoll_wait");
			continue;
		}
		else if(0 == size)
		{
			printf("timeout...\n");
			continue;
		}

		for(int i = 0; i < size; i++)
		{
			int fd = events[i].data.fd;//处理就绪的读事件
			if(events[i].events & EPOLLIN)
			{
				ServiceForRead(listen_sock,fd,epoll_fd);
			}
			else if(events[i].events & EPOLLOUT)//处理就绪的写事件
			{
				ServiceForWrite(fd);
			}
		}
	}
	return 0;
}
