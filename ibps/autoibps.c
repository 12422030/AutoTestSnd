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
    
    if (argc != 3)
    {   
        printf("\n usage: %s  ѭ������  ���ͼ��(΢��)\n\n", argv[0]);
        printf("\n usage: auto 10 500000\n\n" );
        exit(-1);
    } 
    
    strcpy(tmpBuf,argv[1]);
    cnt = atol(tmpBuf);
    sleeptime = atol(argv[2]);
    printf("ѭ������[%ld]���ʱ��΢��[%ld]\n",cnt,sleeptime);
    
    num = 1;
    while(1)
    {

        if (gettimeofday(&show, NULL)) usetime = -1;

        remove("./7000");
        sprintf(filePath,"7000");

        printf("filepath[%s]\n",filePath);

        fp = fopen(filePath,"w");
        if(fp==NULL)
        {
            printf("���ļ�ʧ��");
            return -5;
        }
        fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?><ebank><RequestHead><Source>IBPS</Source><Destination>HOST</Destination> <TransactionId>7000</TransactionId><SendDateTime>20100705163000</SendDateTime><MsgId>12345678901234567890</MsgId></RequestHead><RequestFields><PtcId>1232456789</PtcId><RqlirAcct>6227100000001505</RqlirAcct><RqlirNm>aaa</RqlirNm><RqlirAcctTp>AT02</RqlirAcctTp><RqlirDpsNm>aaa</RqlirDpsNm></RequestFields></ebank>");
        fclose(fp);
    
    
        num ++;
        printf("��ʼ�Զ�����[%d]\n",num);

        memset(tmpBuf,0x00,sizeof(tmpBuf));
        sprintf(tmpBuf," ./ibpssnd 7000");
       
        system(tmpBuf);
        usleep(sleeptime);
        
        printf("num=[%ld]cnt=[%ld]\n",num-1,cnt);
        if(num > cnt)
        {
            break;
        }

    }

    return 0;

}
