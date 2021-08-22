/*******************************************************
	> File Name: 6_shm_write.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月19日
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <unistd.h>
#include <fcntl.h>

#define SHMSIZE 1024
#define DSIZE 32

#define ERR_LOG(LOG)    do{perror(LOG);exit(-1);}while(0)   //宏不要加;号，且do while是因为有两条语句

int main(int argc, char *argv[])
{
    int fd = open("./shmFile", O_RDWR | O_CREAT, 0664);
    if(-1 == fd)
    {
        ERR_LOG("open");
    }
    close(fd);

    //获取键值
    key_t key = ftok("./shmFile", 'k');
    if(-1 == key)
    {
        ERR_LOG("ftok");
        /*
         * do
         * {
         *      perror("ftok");
         *      exit(-1);
         *      
         * }while(0);
         */
    }
    printf("key: \t%#x\n", key);
    //前二位：字符(proj_id)的十六进制  中间两位：(01、02这种)由系统决定  后四位：文件节点号的十六进制

    //创建\打开共享内存
    int shmid = shmget(key, SHMSIZE, IPC_CREAT | 0664);
    if(-1 == shmid)
    {
        ERR_LOG("shmget");
    }
    printf("shmid: \t%d\n", shmid);

    //映射共享内存
    char *p = (char *)shmat(shmid, NULL, 0);
    if((char *)-1 == p)
    {
        ERR_LOG("shamat");
    }
    system("ipcs -m");
    
    //写入共享内存
    while(1)
    {
        printf("input: ");
        fgets(p, DSIZE, stdin);
        p[strlen(p) - 1] = '\0';
        
        if(0 == strcmp(p, "quit"))
        {
            break;
        }
    }

    if(-1 == shmdt(p))
    {
        perror("shmdt");
    }
    if(-1 == shmctl(shmid, IPC_RMID, NULL)) //理论上跳过shmdt()直接删除也是可以的
    {
        perror("shmctl");
    }
    unlink("./shmFile");

    system("ipcs -m");

    return 0;
}

