/*******************************************************
	> File Name: 3_mkfifo_read.c
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
    int rfd = open("./myfifo", O_RDONLY);
    if(0 > rfd)
    {
        perror("open");
        return -1;
    }

    char buf[64] = "0";

    read(rfd, buf, sizeof(buf) - 1);

    printf("buf: %s\n", buf);

    return 0;
}

