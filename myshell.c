#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

void Do_Action(char* argv[])
{
	if(fork() == 0)//child
		execvp(argv[0],argv);
	else
		wait(NULL);
}

void Do_prase(char* buf)
{
	char* argv[8];
	int argc = 0;
	int status = 0;
	int i = 0;
	for(i = 0; buf[i]!='\0'; i++)
	{
		if(!isspace(buf[i]) && status == 0)
		{
			argv[argc++] = buf+i;
			status = 1;
		}
		else if(isspace(buf[i]) && status == 1)
		{	
			status = 0;
			buf[i] = 0;
		}
	}
	argv[argc] = NULL;
	Do_Action(argv);
}

int main()
{
	char buf[1024]={};
	while(1)
	{
		printf("[@_@] :");
		memset(buf,0x00,sizeof(buf));
		//scanf("%s",buf);
		//if(fork() == 0)//child
		//{
		//	execlp(buf,"abcdef",NULL);
		//	exit(0);
		//}
		//wait(NULL);
		scanf("%[^\n]",buf);
		scanf("%*c");
		if(strcmp(buf,"exit") == 0)
			break;

		Do_prase(buf);
	}
}
