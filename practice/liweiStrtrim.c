/**************************************
* FileName --- liweiStrtrim.c
* Author ----- icesky
* Date ------- 6ÔÂ 03 2020
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char liwei[20]="  2333  ";
    printf("[%s]\n",liwei);
    strtrim(liwei);
    printf("[%s]\n",liwei);

}
