#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

int StartUp(int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		printf("sock error\n");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family  = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		printf("bind error\n");
		exit(3);
	}

	if(listen(sock,5)<0)
	{
		printf("listen error\n");
		close(sock);
		exit(4);
	}

	return sock;
}

int cgi = 0;

//获取一行并将 \n \r\n \r 转为\n
void GetLine(int client_fd,char buf[],int size)
{
	int i = 0;
	char ch;
	while(ch != '\n')
	{
		ssize_t s = read(client_fd,&ch,1);
		if(s < 0)
		{
			printf("read error\n");
			return;
		}
		if(ch == '\r')
		{
			recv(client_fd,(void*)&ch,1,MSG_PEEK);
			if(ch == '\n')
				read(client_fd, &ch, 1);
			else
				ch = '\n';
		}
		buf[i++] = ch;
	}
}

void ClearHead(int client_fd)
{
	char buf[1024];
	while(strcmp(buf,"\n")!= 0)
	{
		GetLine(client_fd,buf,sizeof(buf));	
	}
}

void Service(int client_fd,struct sockaddr_in* client_addr)
{
	char buf[1024];
	GetLine(client_fd,buf,sizeof(buf));	
	char* Method = buf;
	char* Url;
	char* Edition = "http/1.0";
	int errorCode;
	char* quiry_string;
	int i = 0;
	while(buf[i] != ' ')//提取请求的方法
		++i;
	buf[i] = '\0';
	
	i++;
	Url = buf+i;
	while(buf[i] != ' ')//提取请求的url
		++i;
	buf[i] = '\0';
	
	//方法、url已经获得
	if(strcasecmp(Method,"GET") == 0)//GET方法
	{
		//正文一定为空，将报文的剩下的报头信息清理掉，然后根据是否带有参数进行相应的回应
		ClearHead(client_fd);

		//判断是否带有参数
		i = 0;
		while(Url[i])
		{
			if(Url[i] == '?')//带有参数，使用CGI模式
			{
				cgi = 1;
				quiry_string = Url+i+1;
				break;
			}
			i++;
		}
		if(!cgi)//将网站的首页回显给客户端
		{
			char buff[1024] = {0};
			const char* page = "<h1>welcome to my corner</h1>";
			sprintf(buff,"HTTP/1.0 200 OK\nContent_Length:%u\n\n%s",strlen(page),page);
			write(client_fd,buff,strlen(buff));
		}
		else
		{
			//cgi处理
			//在报头信息中获取正文的长度，再根据正文长度到正文中获取参数
			int Content_Length = 0;
			char temp[1024];

			while(strcmp(temp,"\n")!= 0)
			{
				GetLine(client_fd,temp,sizeof(temp));
				char* s = temp;
				int j = 0;
				while(s[j] != ':')
				{
					i++;
				}
				s[j] = '\0';
				if(strcmp(s,"Content_Length") == 0)
				{
					Content_Length = atoi(temp+i+2);
					break;
				}
			}

		}
	}
	else if(strcasecmp(Method,"POST") == 0)//POST方法一定使用CGI模式
	{
		cgi = 1;
	}
	else
	{
		goto end;
	}
	end:switch(errorCode)
	{
		case 302:
			break;
		case 403:
			break;
		case 404:
			break;
		case 504:
			break;
		default:
			break;
	}
}

typedef struct Arg
{
	int fd;
	struct sockaddr_in addr;
}Arg;

void CreateWorker(void* str)
{
	Arg* arg = (Arg*)str;
	Service(arg->fd,&arg->addr);
	free(arg);
}

int main(int argc, char* argv[])
{
	if(2 != argc)
	{
		printf("Usage: [%s] [port]\n",argv[0]);
		return 1;
	}

	int listen_sock = StartUp(atoi(argv[1]));
	
	for(;;)
	{
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		int client_fd = accept(listen_sock,(struct sockaddr*)&client_addr, &len);
		if(client_fd < 0)
		{
			printf("accept error\n");
			continue;
		}
		pthread_t tid = 0;
		Arg* arg = (Arg*)malloc(sizeof(Arg));
		arg->fd = client_fd;
		arg->addr = client_addr;
		pthread_create(&tid,NULL,CreateWorker,(void*) arg);
		pthread_detach(tid);

	}
	return 0;
}
