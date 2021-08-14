/*******************************************************
	> File Name: 3_fork.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月13日
 *******************************************************/
#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    fork();
    printf("hello world\n");

    fork();
    printf("hello world\n");

#if 0
    fork();
    printf("hello world\n");

    //再写入第三条，又是在4个进程的基础上开新进程，故2+4+8=14，打印14次

#endif
    //开始便创建两个进程，父子进程各输出一次，父子进程各再创建子进程，故 共打印6次

    return 0;
}

