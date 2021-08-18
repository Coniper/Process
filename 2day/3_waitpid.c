/*******************************************************
	> File Name: 3_waitpid.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月16日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid > 0)
    {
        int stat;

        //waitpid(-1, &stat, 0);        //阻塞
        waitpid(-1, &stat, WNOHANG);    //非阻塞

        if(WIFSIGNALED(stat));

        printf("father: %d\n", getpid());

        while(1);
    }
    else
    {
        printf("child: %d\n", getpid());

        sleep(3);

        while(1);
    }


    return 0;
}

