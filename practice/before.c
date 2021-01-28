#include<stdio.h>
#include<string.h>
#define L360 360
#define L30 30
static int leapyear[12]={31,29,31,30,31,30,31,31,30,31,30,31};
static int commyear[12]={31,28,31,30,31,30,31,31,30,31,30,31};
static int cal_date(long date1,long num,long *dqr);
void main()
{
    long plat_date=20181001;
    long before_date=0;

    cal_date(plat_date,-6,&before_date);
    printf("----------->%ld\n<------------",plat_date);
    printf("----------->%ld\n<------------",before_date);

}

static int cal_date(long date1,long num,long *dqr)
{
    short   y1,m1,d1,num1;
    long    flag=1;
    int *yn;

    num1=num;
    y1=date1/10000;
    m1=(date1/100)%100;
    d1=date1%100;
    num1+=d1;

    if(num1<0)
    {
        m1--;
        num1=-num1;
        flag=-1;
    }
    else if ( num1==0 )
    {
        m1--;
        flag=-1;
    }
    else
    {
        flag=1;
    }
    if (m1>12) {
        y1++;
        m1=m1-12;
    }
    if (m1==0) {
        y1--;
        m1=12;
    }
    while(1)
    {
        if ( (y1%4==0 && y1%100!=0 ) || (y1%400==0) )
        {
            yn=leapyear;
        }
        else
        {
            yn=commyear;
        }
        if ( num1>*(yn+m1-1) )
        {
            num1=num1-*(yn+m1-1);
            m1=m1+flag;
            if (m1>12) {
                y1++;
                m1=m1-12;
            }
            if (m1==0) {
                y1--;
                m1=12;
            }
        }
        else
        {
            if ( flag==-1 )
            {
                num1=*(yn+m1-1)-num1;
            }
            if ( num1==0 )
            {
                m1--;
                if (m1>12) {
                    y1++;
                    m1=m1-12;
                }
                if (m1==0) {
                    y1--;
                    m1=12;
                }
                continue;
            }
            break;
        }
    }
    *dqr=(long)(y1*10000+m1*100+num1);
    return 0;
}
