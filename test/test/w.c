#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    char *s="121212121";
    char d[20];
    char e[20];
    char f[20];
    struct timeval before_usleep;
    struct timeval after_usleep;

 
    gettimeofday(&before_usleep,NULL);
    memcpy(d,s+3,3);
    memcpy(e,s+3,3);
    memcpy(f,s+3,3);

    gettimeofday(&after_usleep,NULL);
    printf("%d,\n%d\n",before_usleep.tv_usec,after_usleep.tv_usec);
    printf("used time =%dms\n",after_usleep.tv_usec-before_usleep.tv_usec);
    return 0;
}
