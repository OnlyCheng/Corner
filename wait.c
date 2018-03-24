#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

extern char* environ
int main()
{
        int i =0;
        for(i = 0; environ[i] != NULL ;i++)
            printf("%s\n",environ[i]);
        if(execle("./hello","hello",NULL,environ ) == -1)
            perror("exec"),exit(1);
}

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <string.h>
 
  int main()
  {
      pid_t pid;

     if((pid = fork()) < 0)
         perror("fork"),exit(1);

     if(pid == 0)
     {
         int i = 0;
         while(1)
         {
             printf("$$$\n");
             sleep(1);
             i++;
             if(i == 3)
                 break;
        }
         exit(2);
     }
    else
    {
         int st;
         pid_t r;
         if((r = wait(&st)) < 0)
            perror("wait");
         printf("pid= %d,r= %d ,ret= %d",pid,r,(st>>8)&0xff);
   }
    return 0;
 }
