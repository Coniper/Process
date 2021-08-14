/*******************************************************
	> File Name: 6_vfork.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月13日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = vfork();

    char ch = 'k';

    if(pid < 0)
    {
        perror("vfork");
        return -1;
    }
    else if(pid > 0)
    {
        printf("父\n");
        printf("ch = %c, &ch = %p\n", ch, &ch);
        while(1);
    }
    else
    {
        ch = 'l';
        printf("子\n");
        printf("ch = %c, &ch = %p\n", ch, &ch);
        exit(0);
    }

    return 0;
}

