/**************************************
* FileName --- cutchar.c
* Author ----- icesky
* Date ------- 5ÔÂ 09 2020
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *epcc_base_cutchar(char *str,char ichar)
{
    int i=0;
    int j=0;
    char *buf=NULL;

    if (strlen(str) == 0)
        return str;

    buf = (char *) calloc(sizeof(char), strlen(str)+1) ;

    for(i = 0; i<strlen(str); i++)
    {   
        if(str[i] != ichar)
        {   
            buf[j] = str[i];
            j++;
        }   
    }   
    memset(str,0x00,sizeof(str));
    strcpy(str,buf);

    return str;

}
