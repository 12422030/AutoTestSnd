#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>


int main(int argc ,char *argv[])
{

    char buf[32] = {0};
    struct timeval tv;
    struct tm      tm;
    size_t         len = 28;
    int i,j;

    memset(&tv, 0, sizeof(tv));
    memset(&tm, 0, sizeof(tm));
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm);
    strftime(buf, len, "%Y-%m-%d %H:%M:%S", &tm);
    len = strlen(buf);
    sprintf(buf + len, ".%-6.3d", (int)(tv.tv_usec/1000)); 
    printf("开始前时间:%s\n", buf);
    for(i=0;i<1000000000;i++)
    {
        j=j+i;
    }
    char buf1[32] = {0};
    struct timeval tv1; 
    struct tm      tm1; 
    size_t         len1 = 28; 

    memset(&tv1, 0, sizeof(tv1));
    memset(&tm1, 0, sizeof(tm1));
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec,&tm1);
    strftime(buf1, len1, "%Y-%m-%d %H:%M:%S", &tm1);
    len1 = strlen(buf1);
    sprintf(buf1 + len1, ".%-6.3d", (int)(tv.tv_usec/1000)); 
    printf("结束前时间:%s\n", buf1);

    return 0;
}
