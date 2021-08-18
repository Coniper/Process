/*******************************************************
	> File Name: 2_daemon.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月15日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    //1.创建子进程，父进程推出
    pid_t pid =fork();

    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid > 0)
    {
        exit(0);
    }

    //2.子进程创建新会话
    if(-1 == setsid())
    {
        perror("setsid");
        return -1;
    }

    //3.修改路径
    if(-1 == chdir("."))
    {
        perror("chdir");
        return -1;
    }

    //4.重置掩码
    umask(0);

    //5.关闭其他文件描述符
    for(int i = 0; i < getdtablesize(); i++)
        close(i);

    //6.做自身任务

    /******周期性要作的事情******/
    FILE *fp = fopen("./mylog.txt", "w");
    if(NULL == fp)
    {
        perror("fopen");
        return -1;
    }

    int i = 0;
    while(1)
    {
        fprintf(fp, "%d.hello world\n", i++);
        fflush(fp);
        sleep(1);
    }

    return 0;
}

