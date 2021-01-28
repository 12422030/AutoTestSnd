/**************************************
* FileName --- 15.c
* Author ----- icesky
* Date ------- 9ÔÂ 04 2019
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char tmp[]="<Response><Head><TxCode>GetBlack</TxCode></Head></Response>";
    char liwei[500]={0x00};
    int len=113;
    int lenth=0;
    lenth= htonl(len);
     printf("[%d]\n",lenth);
    memcpy(liwei,"0000",4);
    memcpy(liwei+4,tmp,len);
    printf("[%s][%d]\n",liwei,len);
    memcpy(liwei+4,&lenth,4);
    printf("[%s]\n",liwei);
    return 0;
}
