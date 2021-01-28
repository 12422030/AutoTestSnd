#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main()
{
    char time[7];
    int h,m,s;;
    GetSysTime(&h,&m,&s);
    printf("[%d][%d][%d]",h,m,s);
}
int GetSysTime(int *Hour, int *Minute, int *Second)
{
    time_t    t;  
    struct tm *local_time;

    t = time(0);
    local_time = localtime(&t);

    *Hour   = local_time->tm_hour;
    *Minute = local_time->tm_min;
    *Second = local_time->tm_sec;

    return ;
}
