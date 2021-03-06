/*******************************************************
	> File Name: 2_pipe.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月19日
 *******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(2 != argc)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    pid_t cpid;
    char buf;

    if(-1 == pipe(pipefd))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if(-1 == cpid)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(cpid == 0)
    {
        close(pipefd[1]);   //关闭写端
        while(read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);

        _exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);

        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}

