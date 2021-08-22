/*******************************************************
	> File Name: 8_sem_write.c
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
#include <sys/sem.h>

#include <unistd.h>
#include <fcntl.h>

#define SHMSIZE 1024
#define DSIZE 32
#define SEMNUM 2

#define ERR_LOG(LOG)    do{perror(LOG);exit(-1);}while(0)   //宏不要加;号，且do while是因为有两条语句

union semun
{
	int val;
};

int main(int argc, char *argv[])
{
    union semun sem_un;
    struct sembuf sem_pv;

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

    /*信号灯集创建*/
    int sem_id = semget(key, SEMNUM, 0664 | IPC_CREAT);
    if(-1 == sem_id)
    {
        ERR_LOG("semget");
    }
    printf("sem_id: %d\n", sem_id);

    /*使用semctl()函数进行信号量初始化*/
    sem_un.val = 1;
    if(-1 == semctl(sem_id, 0, IPC_SET, &sem_un))
    {
        ERR_LOG("semctl");
    }

    //映射共享内存
    char *p = (char *)shmat(shmid, NULL, 0);
    if((char *)-1 == p)
    {
        ERR_LOG("shamat");
    }
    system("ipcs -m");
    system("ipcs -s");
    
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
        /*V操作--释放资源*/
        sem_pv.sem_num = 1;
        sem_pv.sem_op = 1;
        sem_pv.sem_flg = 0;
        if(-1 == semop(sem_id, &sem_pv, 1))     //相当于sem_post()
        {
            ERR_LOG("semop");
        }
    }

    if(-1 == shmdt(p))                      //取消映射
    {
        perror("shmdt");
    }
    if(-1 == shmctl(shmid, IPC_RMID, NULL)) //理论上跳过shmdt()直接删除也是可以的
    {
        perror("shmctl");
    }
    if(-1 == semctl(sem_id, 1, IPC_RMID))   //删除信号灯集
    {
        perror("semctl");
    }
    unlink("./shmFile");

    system("ipcs -m");
    system("ipcs -s");

    return 0;
}

