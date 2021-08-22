/*******************************************************
	> File Name: 3_mkfifo_write.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月19日
 *******************************************************/
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    unlink("./myfifo"); //先删除已存在的管道文件，防止创建失败

    if(-1 == mkfifo("./myfifo", 0664))
    {
        perror("mkfifo");
        return -1;
    }

    //打开管道
    int wfd = open("./myfifo", O_WRONLY);
    if(0 > wfd)
    {
        perror("open");
        return -1;
    }

    char buf[] = "This is myfifo test";

    write(wfd, buf, strlen(buf));

    return 0;
}

