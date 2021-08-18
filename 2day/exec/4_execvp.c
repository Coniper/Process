/*******************************************************
	> File Name: 4_execvp.c
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

        wait(&stat);

        exit(0);
    }
    else
    {
        printf("this is child process %d\n", getpid());

        char *arg[] = {"ls", "-l", NULL};

        //可执行程序及路径、存放参数的数组
        execvp("ls", arg);
    }

    return 0;
}

