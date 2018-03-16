#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define ERR_EXIT(m)\
	do\
	{\
		error(m);\
		exit(EXIT_FAILURE);\
	}while(0)

int  main()
{
	umask(0);
	if(mkfifo("mypipe",0644)<0)
		ERR_EXIT("mkfifo");

	int rfd = open("mypipe",O_RDONLY);
	if(rfd<0)
		ERR_EXIT("open_r");
	
	char buf[1024] = {0};
	while(1)
	{
		buf[0] = 0;
		int s = read(rfd,buf,sizeof(buf)-1);
		if(s<0)
			ERR_EXIT("read");
		else if(0 == s)
		{
			printf("client quik~\n");
			break;
		}
		else
			printf("client said:%s\n",buf);
	}
	close(rfd);

	return 0;
}
