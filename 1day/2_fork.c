/*******************************************************
	> File Name: 2_fork.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月13日
 *******************************************************/
#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("hello world");
    //fflush(stdout);
    //没有刷新缓冲区，故fork拷贝前，行缓冲内有数据，被一起拷贝

    fork();

    return 0;
}

