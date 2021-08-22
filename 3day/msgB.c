#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <sys/msg.h>
struct msgbuf{
	int type;
	char text[64];
};
void *fun(void* arg)
{
	int msgid=*(int*)arg;
	struct msgbuf buf;
	while(1)
	{
		if(msgrcv(msgid,&buf,64,1,0)<0)
		{
			perror("msgrcv");
			return NULL;
		}
		printf("A say:%s",buf.text);
	}
}
int main()
{
	//key
	key_t key=ftok(".",'a');
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int msgid=msgget(key,IPC_CREAT|0666);
	if(msgid<0)
	{
		perror("msgget");
		return -1;
	}
	pthread_t tid;
	if(pthread_create(&tid,NULL,fun,&msgid)<0)
	{
		perror("pthread_create");
		return -1;
	}
	struct msgbuf buf;
	buf.type=2;
	while(1)
	{
		fgets(buf.text,64,stdin);
		if(msgsnd(msgid,&buf,64,0)<0)
		{
			perror("msgsnd");
			return -1;
		}
		if(strncmp(buf.text,"quit",4)==0)
		{
			break;
		}
		
	}
	if(msgctl(msgid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}
