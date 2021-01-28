/*******************************************************
 * 公    司: 大连同方软银科技有限公司
 * 程 序 名: CalEndDate.c
 * 程序功能: 计算增加或减少指定天数后的日期
 * 输入参数:
 *           date1 原日期
 *           num   天数
 * 输出参数:
 *           drq   计算后天数
 * 返 回 值:
 *           =0    成功
 *           !0    失败
 * 作    者: yangwc
 * 开发日期: 2007/1
 * 修 改 人:
 * 修改日期:
*******************************************************/
#include "stdio.h"
#include "math.h"

static int leapyear[12]={31,29,31,30,31,30,31,31,30,31,30,31};
static int commyear[12]={31,28,31,30,31,30,31,31,30,31,30,31};

int CalEndDate(long date1, long num, long *dqr)
{
    short y1, m1, d1, num1;
    long  flag = 1;
    int *yn;

    num1 = num;
    y1 = date1 / 10000;
    m1 = (date1 / 100) % 100;
    d1 = date1 % 100;
    num1 += d1;

    if (num1 < 0)
    {
       m1--;
       num1 = -num1;
       flag =- 1;
    }
    else if (num1 == 0)
    {
       m1--;
       flag = -1;
    }
    else
    {
       flag = 1;
    }

    if (m1 > 12) {y1++; m1 = m1 - 12;}      
    if (m1 == 0) {y1--; m1 = 12;}      

    while(1)
    {
       if ((y1 % 4 == 0 && y1 % 100 != 0) || (y1 % 400 == 0))
       {
          yn = leapyear;
       }
       else
       {
          yn = commyear;
       }

       if (num1 >* (yn + m1 - 1))
       {
          num1 = num1 - *(yn + m1 - 1);
          m1 = m1 + flag;
          if (m1 > 12) {y1++; m1 = m1 - 12;}      
          if (m1 == 0) {y1--; m1 = 12;}      
       }
       else
       {
          if (flag == -1)
          {
             num1 = *(yn + m1 - 1) - num1;
          }
          if (num1 == 0)
          {
             m1--;
             if (m1 > 12) {y1++; m1 = m1 - 12;}      
             if (m1 == 0) {y1--; m1 = 12;}      
             continue;
          }
          break;
       }
    }

    *dqr = (long)(y1 * 10000 + m1 * 100 + num1);

    return 0;

}

int CalTrueDayes(long begrq,long endrq)
{
   int i,a,leap,flag;
   int year;
   long arq,brq,date1,date2;
   int *yn;

   if ( endrq<begrq )
   {
       flag=-1;
       date1=endrq;
       date2=begrq;
   }
   else
   {
       flag=1;
       date1=begrq;
       date2=endrq;
   }

   arq=date1/100;
   brq=date2/100;
	a=0;

   while( arq<brq )
   {
       year=arq/100;
       if ( (year%4==0 && year%100!=0 ) || (year%400==0) )
       {
           yn=leapyear;
       }
       else
       {
           yn=commyear;
       }

       for( i=arq%100; i<=12; i++ )
       {
           a=a+*(yn+i-1);
           arq++;
           if ( i==12 ) arq=(arq/100+1)*100+01;
           if( arq>=brq ) break;
       }
   }
   if ( arq>brq )
   {
       a=a-date1%100-*(yn+i-1)+date2%100;
   }
   else
   {
       a=a-date1%100+date2%100;
   }

   return (a*flag);
}

