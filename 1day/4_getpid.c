/*******************************************************
	> File Name: 4_getpid.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月13日
 *******************************************************/
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    printf("%d\n", pid);

    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("hello\n");
            sleep(1);
            printf("%d\n",getpid());
        }
    }
    else
    {
        while(1)
        {
            printf("world\n");
            sleep(1);
            printf("%d\n", getppid());
        }
    }

    return 0;
}

