/*******************************************************
	> File Name: 4_alarm.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月19日
 *******************************************************/
#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    alarm(2);   //默认终止

    pause();    //挂起

    printf("resr\n");

    return 0;
}

