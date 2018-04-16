#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid = fork();
    if(pid < 0)
        perror("fork");
    if(pid == 0)//child
    {
        while(1)
        {
            printf("I'm child,pid is:%d\n",getpid());
            sleep(1);
        }
    }
    else//father
    {
        int count = 5;
        while(count--)
        {
            printf("##I'm father,pid is:%d##\n",getpid());
            sleep(1);
        }
    }
    return 0;
}
