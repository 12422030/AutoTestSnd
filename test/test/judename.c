#include<stdio.h>
#include <string.h>
int main()
{
    long day=0;
    long day1=0;
    long day2=0;
    long day3=0;
    long day4=0;
    long day5=0;
    
    day=jisuan("20181227")-jisuan("20190122");
    day1=jisuan("20180820")-jisuan("20181026");
    day2=jisuan("20181030")-jisuan("20181112");
    day3=jisuan("20181115")-jisuan("20181119");
    day4=jisuan("20181119")-jisuan("20181205");
    day5=jisuan("20181124")-jisuan("20181119");
    printf("----------->%d\n<------------",day+1);
    printf("----------->%d\n<------------",day1+1);
    printf("----------->%d\n<------------",day2+1);
    printf("----------->%d\n<------------",day3+1);
    printf("----------->%d\n<------------",day4+1);
    printf("----------->%d\n<------------",day5+1);
    printf("\n");

    return 0;
}
int jisuan(const char *pDate)
{
    char szYear[8],szMonth[4],szDay[4];
    long year,month,day,y,m;
    
    memset(szYear,0,sizeof(szYear));
    memset(szMonth,0,sizeof(szMonth));
    memset(szDay,0,sizeof(szDay));

    strncpy(szYear,pDate,4);
    strncpy(szMonth,pDate+4,2);
    strncpy(szDay,pDate+6,2);

    year=atol(szYear);
    month=atol(szMonth);
    day=atol(szDay);

    m=(month+9)%12;
    y=year-m/10;

    return 365*y + y/4 - y/100 + y/400 +(m*306+5)/10 + (day-1);
}
