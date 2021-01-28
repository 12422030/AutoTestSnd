#include<stdio.h>
#include <string.h>
#define SIGNHEAD "<?xml"
#define SINGTAIL "<root"
int main()
{
    char buf[]="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\r\n<root xmlns=\"namespace_string\"><MsgHeader><SndDt>2020-05-08T16:43:51</SndDt><MsgTp>epcc.113.001.01</MsgTp><IssrId>C1081421000051</IssrId><Drctn>12</Drctn><SignSN>4002498830</SignSN><NcrptnSN>4022248123</NcrptnSN><DgtlEnvlp>MHwCIC+CrtsOzEX999PmTJjMjsLCMgCLoNAqhOTfyxYLsnp9AiEAlLllFWJQKqRaYrQjV26Vmcp8CasNXtzgtdArpGxsQ0sEIJ9Ey6W46z16Ac2Qq2hq/O3DCX77nCRid5x+yjEM12nVBBO2NetBUV49YI3lcqJbyd3bJebh</DgtlEnvlp></MsgHeader><MsgBody><SysRtnInf><SysRtnCd>00000000</SysRtnCd><SysRtnDesc>ф║дц.?..</SysRtnDesc><SysRtnTm>2020-05-08T16:43:51</SysRtnTm></SysRtnInf><BizInf><BizStsCd>00000000</BizStsCd><BizStsDesc>111111</BizStsDesc><SgnNo>EPTEN001642143035373529</SgnNo></BizInf><SgnInf><SgnAcctIssrId>C1081421000051</SgnAcctIssrId><SgnAcctTp>00</SgnAcctTp><SgnAcctId>IMJCAv2ojfDCIxhNyvlbv0jabaYHF9aetB+tiMMnCsk=</SgnAcctId><SgnAcctNm>jxARCrowpzhUw+27ErbpIg==</SgnAcctNm><IDTp>01</IDTp><idno>zONqOl6ndwshrbuYGxreECP1+YoO/tK1LIa1KSAK4sE=</IDNo><MobNo>Qx0RjolS3qflVIm0CDQPxA==</MobNo><LglRepNm></LglRepNm><LglRepIDTp></LglRepIDTp><LglRepIDNo></LglRepIDNo></SgnInf><InstgInf><InstgId>Z0000000000088</InstgId><InstgAcct>B3xEFibr6gEISw7coqy5BezkmLE+Z/qyJ7YTTEFek9o=</InstgAcct></InstgInf><OriTrxInf><TrxCtgy>0204</TrxCtgy><BizTp>110001</BizTp><TrxId>2020050816421430353735291770101</TrxId><TrxDtTm>2020-05-08T16:42:14</TrxDtTm><PyeeMrchntNo>D2143569-X</PyeeMrchntNo><PyeeMrchntNm>user</PyeeMrchntNm><EntrstAuthNo>130073386132613997</EntrstAuthNo><EntrstAmtLmt>CNY10.00</EntrstAmtLmt><EntrstStrDtTm>2018-01-01T00:00:00</EntrstStrDtTm><EntrstEndDtTm>2018-12-31T23:59:59</EntrstEndDtTm><EntrstDtUnt>04</EntrstDtUnt><EntrstDtStp>3</EntrstDtStp><EntrstDtDsc>111111</EntrstDtDsc><EntrstFrqcy>0</EntrstFrqcy></OriTrxInf></MsgBody></root>";
    /**char buf[]="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";**/
    /**char buf[]="<?xml version="1.0" encoding="UTF-8" standalone="no"?>**/
    char *beg=NULL;
    char *end=NULL;
    char *res=NULL;
    char *out=NULL;
    char final[8*1024];
    int  lXmlLen=0;

    res = strstr(buf,SIGNHEAD);
    out = strstr(buf,SINGTAIL);

    char liwei[8*1024];
    lXmlLen=out-res;
    memcpy(liwei,res,lXmlLen);

    char *p;
    strcpy(p,liwei);

    int len=strlen(p);
    p[len-1]="\0";

    printf("00000000000[%s]",liwei);
    printf("11111111111[%s]\n",out); 
    strcat(final,p);
    strcat(final,out);
    printf("------------------------\n");
    printf("4444444%s\n",final);

    return 0;
}
