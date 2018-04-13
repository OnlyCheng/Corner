#include <stdio.h>
#include <stdlib.h>
#inlcude <unistd.h>
#inlcude <string.h>

int main()
{
	//char* argv[] = {ls" , "-l" , NULL};
	if(execl("./a.out","ls","-l",NULL) == -1)
		perror("exec"),exit(1);
}

///////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	printf("before execvp\n");
	char* argv[] = {"hello",NULL};
	execvp("./hello",argv);
	printf("after execvp\n");
}

//////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[],char* envp[])
{
	int i = 0;
	for(; envp[i] != NULL;i++)
		printf("%s",envp[i]);

	return 0;
}
