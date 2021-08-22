/*******************************************************
	> File Name: 5_signal.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月19日
 *******************************************************/
#include <stdio.h>

#include <signal.h>

sig_t sig;

void func(int signum)
{
    static int count = 1;
    if(count == 2)
        signal(SIGINT, sig);
    ++count;
}

int main(int argc, char *argv[])
{
    sig = signal(SIGINT, func);
    if(sig == SIG_ERR)
        return -1;

    while(1);

    return 0;
}

