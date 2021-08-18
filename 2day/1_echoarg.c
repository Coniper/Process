/*******************************************************
	> File Name: 1_echoarg.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月15日
 *******************************************************/
#include <stdio.h>

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}

