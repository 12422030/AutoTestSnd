/**************************************
* FileName --- 35.c
* Author ----- icesky
* Date ------- 3ÔÂ 05 2019
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int ret=0;
    ret=creat("/app/user/liwei/test/35",0777);
    if(ret<0)
    {
        printf("%d",ret);
        return -1;
    }
     
    return 0;
}
