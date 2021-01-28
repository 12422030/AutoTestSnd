/**************************************
* FileName --- sign.c
* Author ----- icesky
* Date ------- 4ÔÂ 28 2020
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char *p=NULL;
    char signno[101]="EPAPdw-001112121111";
    char sign_no[101]={0x00};

    printf("%s\n",signno);
    p=signno;
    while(*(p++)=='0');
    sprintf(sign_no,"%s",p-1);
    printf("%s\n",sign_no);

    return 0;
}
