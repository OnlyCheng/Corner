#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

#define ERR_EXIT(m)\
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

int main()
{
	int pipefds[2];
	if(-1 == pipe(pipefds))
		ERR_EXIT("create pipe");
	pid_t pid;
	pid = fork();
	if(-1 == pid)
		ERR_EXIT("fork");
	
	if(0 == pid)//child
	{
		close(pipefds[0]);
		int count = 5;
		char* str = "This is my first pipe!";
		while(count--)
		{
			write(pipefds[1],str,strlen(str));
			sleep(2);
		}
		close(pipefds[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefds[1]);
		char sub[100] = {0};
		while(1)
		{
			int i = read(pipefds[0],sub,100);
			if(i < 0)
				ERR_EXIT("read");
			else if(0 == i)
			{
				printf("Maybe Child has quit~\n");
				break;
			}
			else
				printf("Child saied:%s\n",sub);
		}
		close(pipefds[0]);
	}
	return 0;
}
