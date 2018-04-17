#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define ERR_EXIT(n) \
	do\
	{\
		perror(n);\
		exit(EXIT_FAILURE);\
	}while(0)

void MyDaemon()
{
	int i;
	int fd0;
	pid_t pid;
	struct sigaction sa;
	//调用umask函数设置文件屏蔽字
	umask(0);

	//调用fork函数
	pid = fork();
	if(pid < 0)//调用fork失败
		ERR_EXIT("fork");

	if(pid > 0)//父进程
		exit(0);
	
	//调用setsid函数
	setsid();

	//忽略SIGCHILD信号
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGCHLD,&sa,NULL) < 0)
		return;

	//再次fork（）
	if((pid = fork()) < 0)
		ERR_EXIT("fork");
	else if(fork > 0)//父进程
		exit(0);
	
	//更改当前目录为根目录
	if(chdir("/") < 0)
	{
		printf("change child dir error\n");
		return;
	}

	//关闭不需要的文件描述符
	//
	//close(0);
	//close(1);
	//close(2);
	
	//重定向到/dev/null
	fd0 = open("/dev/null",O_RDWR);
	dup2(fd0,0);
	dup2(fd0,1);
	dup2(fd0,2);

	//已成功创建一个守护进程，为了方便验证，让守护进程为我们提供一项服务
	while(1)
	{
		fd0 = open("daemon.txt", O_WRONLY|O_CREAT|O_APPEND, 0644);
		if(fd0 == -1)
			ERR_EXIT("open");
		char *buf = "I'm offering you a service\n";
		write(fd0, buf, strlen(buf));
		close(fd0);
		sleep(60);
	
	}
}

int main()
{
	MyDaemon();
	while(1)
	{
		sleep(1);
	}
	return 0;
}
