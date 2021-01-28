#include<stdio.h>
int main()
{
    int y,m,d;
    printf("please input date information,ended with Enter Key\n");
    scanf("%d%d%d",&y,&m,&d);
    printf("对应的是星期:%d\n",f_week(y,m,d));
}
f_week(int y, int m, int d)    /* 0 = Sunday */
{
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= m < 3;
        return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}
