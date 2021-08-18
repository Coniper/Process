/*******************************************************
	> File Name: 2_execlp.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月17日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

#include <wait.h>

int main(int argc, char *argv[])
{
    int stat;
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid > 0)
    {
        printf("this is father process %d\n", getpid());
        wait(&stat);

        exit(0);
    }
    else
    {
        printf("this is father process %d\n", getpid());

        execlp("ls", "ls", "-l", "-a", NULL);
        //从这里往下 子进程内已被替换不再执行

        printf("test\n");

        exit(0);
    }

    return 0;
}

