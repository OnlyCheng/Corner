//test the exit num

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(0);
	}
	else if(pid == 0)//child
	{
		while(1)
		{
			sleep(1);
			printf("pid = %d ppid = %d\n",getpid(),getppid());
		}
	}
	else//parent
	{
		int status;
		wait(&status);
		printf("the exit num is : %d\n",status);
	}
	return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(0);
	}
	else if(pid == 0)//child
	{
		int* p;
		*p = 0;
		printf("I'm child,I'm OK\n");
	}
	else//father
	{
		int status;
		wait(&status);
		printf("the exit num is:%d\n",status);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
		perror("fork");
	else if(pid == 0)//child
	{
		while(1)
		{
			printf("I'm child, my pid is:%d\n",getpid());
			sleep(1);
		}
	}
	else//father
	{
		int status;
		sleep(3);
		kill(pid,9);
		wait(&status);
		printf("the exit num is: %d\n",status);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
		perror("fork");
	else if(pid == 0)//child
	{
		int count = 5;
		while(count--)
		{
			sleep(1);
			printf("I'm child,my pid is :%d \n",getpid());
		}
		abort();
	}
	else//father
	{
		int status;
		wait(&status);
		printf("the exit num is: %d\n",status);
	}
	return 0;
}

//div zero
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(0);
	}
	else if(pid == 0)//child
	{
		int num = 3/0;
		printf("I'm child,I'm OK\n");
	}
	else//father
	{
		int status;
		wait(&status);
		printf("the exit num is:%d\n",status);
	}
	return 0;
}

//alarm
#include <stdio.h>
#include <unistd.h>

int main()
{
	int t0 = alarm(10);
	printf("剩余 %d 秒\n",t0);
	sleep(2);
	int t1 = alarm(2);
	sleep(1);
	printf("剩余 %d 秒\n",t1);
	sleep(5);

	return 0;
}

//信号捕捉测试
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig)
{
	printf("catch a signal : %d\n",sig);
}

int main()
{
	signal(2,handle);
	while(1)
	{
		printf("I'm action...\n");
		sleep(1);
	}
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle(int signo)
{
	printf("received a signal:%d\n",signo);
}

int main()
{
	signal(9,handle);
	while(1)
	{
		printf("I'm active...\n");
		sleep(1);
	}
	return 0;
}
