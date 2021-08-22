/*******************************************************
  > File Name: 11_msg_read.c
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

#define DSIZE 128
#define ERR_LOG(LOG) do{perror(LOG);exit(-1);}while(0)

typedef struct msgdata {
    long type;
    char info[DSIZE];
}MSG;

int main(int argc, char *argv[])
{
    MSG msg;

    key_t key = ftok("msgFile", 5);
    if(-1 == key)
    {
        ERR_LOG("ftok");
    }

    int msg_id = msgget(key, 0664);
    if(-1 == msg_id)
    {
        ERR_LOG("msgget");
    }

    system("ipcs -q");

    msg.type = 0;

    while(1)
    {
        if(-1 == msgrcv(msg_id, &msg.info, DSIZE, msg.type, 0))
        {
            ERR_LOG("msgrcv");
        }
        printf("recv: %s\n", msg.info);

        if(NULL != strstr("quit", msg.info))
        {
            break;
        }
    }
    if(-1 == msgctl(msg_id, IPC_RMID, NULL))
    {
        ERR_LOG("msgctl");
    }
    unlink("msgFile");

    return 0;
}

