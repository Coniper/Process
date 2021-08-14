/*******************************************************
	> File Name: 5_fork.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月13日
 *******************************************************/
#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    
    char ch = 'k';

    if(pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if(pid > 0)
    {
        printf("parent\n");
        printf("ch = %c, &ch = %p\n", ch, &ch);
        sleep(1);
    }
    else
    {
        ch = 'l';
        printf("child\n");
        printf("ch = %c, &ch = %p\n", ch, &ch);
    }

    //copy on write
    //物理地址在拷贝时被复制，虚拟地质去映射

    return 0;
}

