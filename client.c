#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m)\
	do\
	{\
		error(m);\
		exit(EXIT_FAILURE);\
	}while(0)

int main()
{
	int wfd = open("mypipe",O_WRONLY);
	if(wfd<0)
		ERR_EXIT("open_w");

	char buf[1024] = {0};
	while(1)
	{
		//buf[0]=0;
		printf("please enter:");
		//fflush(stdout);
		int s = read(0,buf,sizeof(buf)-1);

		if(s > 0)
		{
			buf[s] = 0;
			write(wfd,buf,strlen(buf));
			memset(buf,0x00,sizeof(buf));
		}
		else
			ERR_EXIT("write");
	}
	close(wfd);

	return 0;
}
