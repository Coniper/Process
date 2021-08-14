/*******************************************************
	> File Name: 1_fork.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月12日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(-1);
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("study\n");
            sleep(1);
        }
    }
    else
    {
        while(1)
        {
            printf("play game\n");
            sleep(1);
        }
    }


    while(1)

    return 0;
}

