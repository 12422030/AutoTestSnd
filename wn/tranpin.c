/**************************************
* FileName --- tranpin.c
* Author ----- icesky
* Date ------- 9ÔÂ 29 2019
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char fullKeyName[60];
    char clearPin[20];
    char accNo[20];
    char pinBlock[17]={0x00};
    int ret = 0;

    strcpy(fullKeyName,"HX.qdtohx.zpk");
#if 0    
    strcpy(fullKeyName,"PD.050007021162.zpk");
#endif 
    
    strcpy(clearPin,"123123");
    strcpy(accNo,"00000000000000000");

    ret =UnionEncryptPin(fullKeyName, clearPin, accNo, pinBlock);
    if (ret)
    {
        printf("--ret=[%d]\n",ret);
    }
    else
    {
        printf("--pinBlock[%s]\n",pinBlock);
    }
    return 0;
}
