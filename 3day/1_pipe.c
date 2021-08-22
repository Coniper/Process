/*******************************************************
	> File Name: 1_pipe.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月16日
 *******************************************************/
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#define BUFSZ 128

int main(int argc, char *argv[])
{
    //创建无名管道，得到读端和写端的文件描述符
    int pfd[2];
    if ( pipe(pfd) < 0)
    {
        perror("pipe");
        goto ERR_STEP;
    }

    printf("pipefd[0]: %d, pipefd[1]: %d\n", pfd[0], pfd[1]);
    
    pid_t pid;
    if ( (pid = fork()) < 0 )
    {
        perror("fork");
        goto ERR_STEP;
    }
    else if (pid > 0)
    {
        //关闭子进程读端，保证父进程只能写数据
        close(pfd[0]);
        
        int count = 0;
        char buf[] = "hello world";

        while(1){
            
            //fgets(buf, sizeof(buf)-1, stdin); 
            
            //向无名管道写入数据
            if(write(pfd[1], buf, strlen(buf)) < 0)
                break;
            printf("写%d次，成功\n", ++count);
            sleep(1);
        }
    }
    else 
    {
        //关闭写端，保证子进程只能读取数据
        close(pfd[1]);
        
        char buf[BUFSZ] = {0};
        
        while(1){
            memset(buf, 0, sizeof(buf));
            //从无名管道的读端读取数据
            if(read(pfd[0], buf, sizeof(buf)) < 0)
                break;
            printf("read: %s\n", buf);
            sleep(1);
        }
    }

ERR_STEP:

    return 0;
}
