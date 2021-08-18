/*******************************************************
	> File Name: 1_execl.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月17日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <wait.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    int stat;

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork");
        goto ERR_STOP;
    }
    else if(pid > 0)
    {
        printf("this is father process %d \n", getpid());
        waitpid(-1, &stat, 0);

        sleep(3);

        exit(0);
    }
    else
    {
        printf("this is child process %d \n", getpid());

        //可执行程序及路径、可执行程序、参数……、NULL结尾
        //execl("/bin/ls", "ls", "-l", ".", "NULL");

        execl("./echoarg", "./echoarg", "hello", "world", NULL);

        exit(0);
    }

ERR_STOP:
    return 0;
}

