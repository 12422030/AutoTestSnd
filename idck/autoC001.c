/**************************************
* FileName --- auto.c
* Author ----- Mountain
* Date ------- Dec 13 2018
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(int argc, char *argv[])
{
    long cnt=0;
    long num = 0;
    long sleeptime=0;
    char fileName[40];
    char filePath[128];
    char tmpBuf[2560];
    FILE *fp=NULL;
    double usetime=0.0;
    struct timeval show;

    if (gettimeofday(&show, NULL)) usetime = -1;

    memset(fileName,0x00,sizeof(fileName));
    memset(filePath,0x00,sizeof(filePath));
    memset(tmpBuf,0x00,sizeof(tmpBuf));
    
    if (argc != 2)
    {   
        printf("\n usage: %s  循环次数 \n\n", argv[0]);
        printf("\n usage: auto 10 \n\n" );
        exit(-1);
    } 
    
    strcpy(tmpBuf,argv[1]);
    cnt = atol(tmpBuf);
    printf("循环次数[%ld]\n",cnt);
    
    num = 1;
    while(1)
    {

        if (gettimeofday(&show, NULL)) usetime = -1;

    
    
        num ++;
        printf("开始自动发送[%d]\n",num);

        memset(tmpBuf,0x00,sizeof(tmpBuf));
        sprintf(tmpBuf," ./snd C001");
       
        system(tmpBuf);
        
        printf("num=[%ld]cnt=[%ld]\n",num-1,cnt);
        if(num > cnt)
        {
            break;
        }

    }

    return 0;

}
