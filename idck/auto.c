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

        remove("./epcc.201.001.01");
        sprintf(filePath,"epcc.201.001.01");

        printf("filepath[%s]\n",filePath);

        fp = fopen(filePath,"w");
        if(fp==NULL)
        {
            printf("打开文件失败");
            return -5;
        }
        fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        fprintf(fp,"<root xmlns=\"namespace_string\"><MsgHeader><SndDt>2018-07-12T14:12:11</SndDt><MsgTp>epcc.201.001.01</MsgTp><IssrId>G4000311000018</IssrId><Drctn>22</Drctn><SignSN>4000227191</SignSN></MsgHeader><MsgBody><PyerInf><PyerAcctIssrId>C1081421000051</PyerAcctIssrId><PyerAcctTp>00</PyerAcctTp><SgnNo>EPPAP00HRDYIPBQCPAPFQCYG</SgnNo><PyerTrxTrmTp></PyerTrxTrmTp><PyerTrxTrmNo></PyerTrxTrmNo></PyerInf><RPFlg>1</RPFlg><PyeeInf><PyeeAcctIssrId>Z2004344000017</PyeeAcctIssrId><PyeeAcctId>INSTCOUNT00001</PyeeAcctId><PyeeNm>TestPayer</PyeeNm><PyeeAcctTp>03</PyeeAcctTp><PyeeCtryNo></PyeeCtryNo><PyeeAreaNo></PyeeAreaNo><PyeeTrxTrmTp></PyeeTrxTrmTp><PyeeTrxTrmNo></PyeeTrxTrmNo></PyeeInf><ResfdInf><InstgAcctId>99010176680005004</InstgAcctId><InstgAcctNm>TestInstgid</InstgAcctNm><ResfdAcctIssrId>C1010611003601</ResfdAcctIssrId></ResfdInf><TrxInf><TrxId>201101010000000000000%08ld</TrxId><TrxDtTm>2018-07-12T14:11:54</TrxDtTm><TrxAmt>CNY1.00</TrxAmt><TrxCtgy>0110</TrxCtgy><BizTp>100001</BizTp><AcctInTp></AcctInTp></TrxInf><OrdrInf><OrdrId>4999927394594272976911343300000000000002</OrdrId><OrdrDesc>test</OrdrDesc><PltfrmNm>he</PltfrmNm></OrdrInf><BatchId>B201807120015</BatchId><TrxDevcInf></TrxDevcInf></MsgBody></root>\r\n",show.tv_usec);

        fclose(fp);
    
    
        num ++;
        printf("开始自动发送[%d]\n",num);

        memset(tmpBuf,0x00,sizeof(tmpBuf));
        sprintf(tmpBuf," ./snd 8000");
       
        system(tmpBuf);
        usleep(sleeptime);
        
        printf("num=[%ld]cnt=[%ld]\n",num,cnt);
        if(num > cnt)
        {
            break;
        }

    }

    return 0;

}
