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
        printf("\n usage: %s  循环次数  发送间隔(微妙)\n\n", argv[0]);
        printf("\n usage: auto 10 500000\n\n" );
        exit(-1);
    } 
    
    strcpy(tmpBuf,argv[1]);
    cnt = atol(tmpBuf);
    sleeptime = atol(argv[2]);
    printf("循环次数[%ld]间隔时间微妙[%ld]\n",cnt,sleeptime);
    
    num = 1;
    while(1)
    {

        if (gettimeofday(&show, NULL)) usetime = -1;

        remove("./7001");
        sprintf(filePath,"7001");

        printf("filepath[%s]\n",filePath);

        fp = fopen(filePath,"w");
        if(fp==NULL)
        {
            printf("打开文件失败");
            return -5;
        }
        fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?><ebank><RequestHead><Source>IBPS</Source><Destination>QDEB</Destination><TransactionId>7001</TransactionId><SendDateTime>20200413130053</SendDateTime><MsgId>3085840000132020041313797072</MsgId></RequestHead><RequestFields><PtcId>3132270000120220191022027726</PtcId><RqlirAcct>110224115081396</RqlirAcct><RqlirNm></RqlirNm><RqlirDpsNm></RqlirDpsNm><RqlirAcctTp>AT00</RqlirAcctTp><StartDt>20191001</StartDt><DnldDt>20200413</DnldDt></RequestFields></ebank>");
        fclose(fp);
    
    
        num ++;
        printf("开始自动发送[%d]\n",num);

        memset(tmpBuf,0x00,sizeof(tmpBuf));
        sprintf(tmpBuf," ./ibpssnd 7001");
       
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
