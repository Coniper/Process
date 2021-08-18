/*******************************************************
	> File Name: 3_execv.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月17日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
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

        waitpid(-1, &stat, 0);

        exit(0);
    }
    else
    {
        printf("this is child process %d\n", getpid());

        char *arg[] = {"./echoarg", "hello", "world", NULL};

        //可执行程序、存放参数的数组
        execv("./echoarg", arg);
    }

    return 0;
}

