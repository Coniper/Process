/*******************************************************
	> File Name: 10_msg_write.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月21日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include <unistd.h>

#define DSIZE 512
#define ERR_LOG(LOG) do{perror(LOG);exit(-1);}while(0)

typedef struct msgdata {
    long type;
    char info[DSIZE];
}MSG;

int main(int argc, char *argv[])
{
    MSG msg;

    int fd = open("msgFile", O_RDWR | O_CREAT, 0664);
    if(-1 == fd)
    {
        ERR_LOG("open");
    }
    close(fd);

    key_t key = ftok("msgFile", 5);
    if(-1 == key)
    {
        ERR_LOG("ftok");
    }
    printf("key: %d\n", key);

    int msg_id = msgget(key, 0664 | IPC_CREAT);
    if(-1 == msg_id)
    {
        ERR_LOG("msgget");
    }
    printf("msgid: %d\n", msg_id);

    system("ipcs -q");

    msg.type = 100;

    while(1)
    {
        printf("input info: ");
        fgets(msg.info, DSIZE, stdin);
        msg.info[strlen(msg.info) - 1] = '\0';

        if(-1 == msgsnd(msg_id, &msg, DSIZE, 0))   //0: 默认模式:阻塞
        {
            ERR_LOG("msgsnd");
        }
        
        if(NULL != strstr("quit", msg.info))
        {
            break;
        }
    }

    return 0;
}

