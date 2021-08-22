/*******************************************************
	> File Name: 7_shm_read.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月20日
 *******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <errno.h>

#define SHMSIZE 1024

#define ERR_LOG(LOG) do{perror(LOG);exit(-1);}while(0)

int main(int argc, char *argv[])
{
    key_t key = ftok("./shmFile", 'k');
    if(-1 == key)
    {
        ERR_LOG("ftok");
    }
    printf("key: %#x\n", key);
    
    //int shmid = shmget(key, SHMSIZE, IPC_CREAT | IPC_EXCL | 0664);
    int shmid = shmget(key, SHMSIZE, 0664);
    if(-1 == shmid)
    {
        if(errno == EEXIST)
        {
            printf("shm exist\n");
        }
        else
        {
            ERR_LOG("shmget");
        }
    }
    printf("shmid: %d\n", shmid);

    char *p = (char *)shmat(shmid, NULL, 0);
    if(p == (char *)-1)
    {
        ERR_LOG("shmat");
    }

    while(1)
    {
        if(1 <= strlen(p))
        {
            printf("recv: %s\n", p);
            memset(p, 0 ,strlen(p));
        }
        else
        {
            usleep(500000);
        }
    }

    if(-1 == shmdt(p))
    {
        perror("shmdt");
    }

    return 0;
}

