#include<stdio.h>
int main()
{
    int y,m,d;
    printf("please input date information,ended with Enter Key\n");
    scanf("%d%d%d",&y,&m,&d);
    printf("对应的是星期:%d\n",f_week(y,m,d));
    return 0;
}
