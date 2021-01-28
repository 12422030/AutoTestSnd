#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
main()
{
    int ret;
    long hh,mm,ss;
    long s=0,h=0,m=0;
    long interval=0;
    char space[2];
    time_t t;
    struct tm *ltime;

    strcpy(space,"2");
    interval=atol(space);

    /*获取机器时间*/
    hh=9;
    mm=30;
    ss=30;
    s=hh*60+mm+interval;
    h=s/60%24;
    m=s%60;
    printf("%d\n",h);
    printf("%d\n",m);
    return 0;
}
