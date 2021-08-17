/*******************************************************
	> File Name: 7_wait.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月13日
 *******************************************************/
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int
main(int argc, char *argv[])
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
		wait(&stat);//阻塞

		if(WIFSIGNALED(stat))
		{
			printf("child is killed by %d signal\n", stat);
		}

		printf("parent:%d\n", getpid());
		while(1);
	}
	else 
	{
		printf("child:%d\n", getpid());
		sleep(3);
		while(1);
	}


    return 0;
}

