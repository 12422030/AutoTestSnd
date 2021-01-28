#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(){
    char *s="GoldenGlobalView";
    char d[20];
    char e[20];
    char f[20];
 
    struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("second:%ld\n",tv.tv_sec);
    printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);
    printf("microsecond:%ld\n",tv.tv_sec*1000000 + tv.tv_usec);

    memcpy(d,s+3,3);
    memcpy(e,s+3,3);
    memcpy(f,s+3,3);

    gettimeofday(&tv,NULL);
    printf("second:%ld\n",tv.tv_sec); 
    printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);
    printf("microsecond:%ld\n",tv.tv_sec*1000000 + tv.tv_usec);

    return 0;
}
