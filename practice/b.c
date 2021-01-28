#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( ) 
{
     char *s="GoldenGlobalView";
     char d[20];
     int i=0;
     clock_t start, finish;
     double Total_time;/* 测量一个事件持续的时间*/
     printf( "Time to do %ld empty loops is ", i );
     start = clock();
     for(i=0;i<10;i++)
     {
       memcpy(d,s+3,3);
     }
     finish = clock();
     Total_time = (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds\n", Total_time);
     return 0;
}
