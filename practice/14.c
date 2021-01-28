/**************************************
* FileName --- 15.c
* Author ----- icesky
* Date ------- 9ÔÂ 02 2019
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main()
{
    int result=0;
    int year,month,day;
    scanf("%d\n",&year);
    scanf("%d\n",&month);
    scanf("%d",&day); 
    result=day_of_week(year,month,day);
    printf("%d",result);
    return ;
}
