#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( ) 
{
     int i,j;
     clock_t start, finish;
     double Total_time;/* 测量一个事件持续的时间*/
     start = clock();
     for(i=0;i<200000000;i++)
     {
       j=j+100;
     }
     finish = clock();
     Total_time = (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds\n", Total_time);
     return 0;
}
