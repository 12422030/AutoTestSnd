/**
	 *LEVEL  修改人　修改日期     修改描述 
	 L0001  王小明   20130506   修改贷记卡渠道返回分流
**/
#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"
/** L0001 add  start **/
#include "jzibps/ibpspub.h"
/** L0001 add  start **/
int JZIBPSCommSend(TxipCMStc *xip)
{
    char fileName[31];
    char fullName[201];
    char sPkgHead[41];
    char sTmpStr[31];
    char replyMsg[51];
    char *xmlBuf = NULL;
    char command[101];
    FILE *fp = NULL;
    int  xmlBufLen = 0;
    int  y, m, d, hh, mm, ss;
    int  ret = 0;
/** L0001 add  start **/
	char fcode[11];
	char tcode[11];	
	char routeflag[9];	
	char accttp[13];	
/** L0001 add  start **/

    /*1.响应代码转换*/
    memset(sTmpStr, 0x00, sizeof(sTmpStr));
    ret = RsCodeLocalToTarget(Mxip_frid, Mxip_rc, sTmpStr, Mxip_rc);
    if (ret)
    {
       set_cm_data(TARGETRSPCODE, "PE3004"); /*响应代码转换错误时置默认错误码*/
    }
    else
    {
       set_cm_data(TARGETRSPCODE, sTmpStr); /*响应代码转换成功时置转换后代码*/
    }

    get_cm_data(XIPREPLYMSG, replyMsg);
    if (replyMsg[0] == 0)
    {
       ret = GetRsCodeName(Mxip_rc, replyMsg);
       if (ret != 0)
       {
          sprintf(replyMsg, "[%s]未找到响应信息", Mxip_rc);
       }
    }
    set_cm_data(XIPREPLYMSG, replyMsg);

    /*2.获取发送时间*/
    GetSysDateTime(&y, &m, &d, &hh, &mm, &ss);
    sprintf(sTmpStr, "%04d%02d%02d%02d%02d%02d", y, m, d, hh, mm, ss);
    set_cm_data("1609", sTmpStr);

    /*3.组报文体*/
    if (Mxip_frtrbflag[0] == '2' || Mxip_frtrbflag[0] == '3')
    {
       if (strcmp(Mxip_rc, "0000") == 0)
       {
          get_cm_data(SENDFILENAME, fileName);
          strtrim(fileName);

          sprintf(fullName, "%s/%s", Mxip_sfpath, fileName);
          fp = fopen(fullName, "r");
          if (fp == NULL)
          {
             APPLOG("E", "Open File [%s] Err![%s]", fileName, strerror(errno));
             return -5;
          }
       }
    }

/** L0001 add  start **/
	memset(fcode, 0x00, sizeof(fcode));
	memset(tcode, 0x00, sizeof(tcode));
	memset(routeflag, 0x00, sizeof(routeflag));
	memset(accttp, 0x00, sizeof(accttp));
	
	strcpy(tcode, Mxip_frtc);
	get_cm_data("1610", routeflag);
	strtrim(routeflag);
	if (strlen(routeflag) && !strcmp(routeflag, "ROUTEGO"))
	{
		get_cm_data("1602", accttp);
		strtrim(accttp);		
		if (strcmp(accttp, "AT02")) {}
		else	/*贷记卡*/
		{
		    ret = GetXipParmConv("IBPS_TRCODE", Mxip_frtc, 1, fcode, Mxip_rc);
		    if (ret != 0)	{}
		    else
		    {
		    	strtrim(fcode);
		    	memset(tcode, 0x00, sizeof(tcode));
		    	strcpy(tcode, fcode);		    	
		    }
		}
	}
	else { APPLOG("D", "正常交易") ; }
	ret = XmlCreateAndAttr(Mxip_frid, Mxip_frdcmode, tcode, Mxip_frfsign, NULL, fp, "B", NULL, &xmlBuf, &xmlBufLen, Mxip_rc);
/** L0001 add  end **/	   	

/** L0001 upd  start **/
	/**ret = XmlCreateAndAttr(Mxip_frid, Mxip_frdcmode, Mxip_frtc, Mxip_frfsign, NULL, fp, "B", NULL, &xmlBuf, &xmlBufLen, Mxip_rc);**/
/** L0001 upd  end **/	
    if (ret)
    {
       APPLOG("E", "CALL XmlCreateAndAttr Error=[%d]", ret);
       if (xmlBuf != NULL) free(xmlBuf);
       if (fp != NULL) fclose(fp);
       return -10;
    }

    xmlBuf[xmlBufLen] = 0;

APPLOG("D", "xmlBuf=[%s]", xmlBuf);

    /*4.组报文头*/
    memset(sPkgHead, 0x00, sizeof(sPkgHead));

    /*报文体长度8位*/
    sprintf(sPkgHead, "%08d", xmlBufLen+8);
   
    /*报文类型4位*/
    strcpy(sPkgHead+8, "1410");

    /*交易码*/
    Mxip_frtc[4] = 0;
    sprintf(sPkgHead+12, "%s", Mxip_frtc);

    /*5.发送报文头*/
    ret = TcpSend(Mxip_sockid, sPkgHead, 16, Mxip_frtmout);
    if (ret) 
    { 
       APPLOG("E", "TCPIP Send PackLen Failed![%d][%s]", ret, strerror(errno)); 
       free(xmlBuf);
       if (fp != NULL) fclose(fp);
       return -15; 
    }

    /*6.发送报文体*/
    ret = TcpSend(Mxip_sockid, xmlBuf, xmlBufLen, Mxip_frtmout);
    if (ret) 
    { 
       APPLOG("E", "TCPIP Send Pack Failed![%d][%s]", ret, strerror(errno)); 
       free(xmlBuf);
       if (fp != NULL) fclose(fp);
       return -20;  
    }
	if ( xmlBuf !=NULL)  
	{
		 free(xmlBuf); 
		 APPLOG("D", "关闭xmlBuf");
	}
    if (fp != NULL) fclose(fp);

    /*如果交易成功并且是对账交易则启动对账程序进行对账*/
    memset(command, 0x00, sizeof(command));
    memset(sTmpStr, 0x00, sizeof(sTmpStr));

    get_cm_data(TARGETRSPCODE, sTmpStr);

    if (strcmp(sTmpStr, "PE0000") == 0 && 
        (strcmp(Mxip_frtc, "9000") == 0 || strcmp(Mxip_frtc, "9100") == 0)
       )
    {
       /*参数:上级渠道ID 渠道ID 对账交易 对账日期 对账开始日期 对账终止日期*/
       sprintf(command, "JZIBPSChkServer %s %s %s %d %d %d 1>>%s/%s 2>>%s/%s &",
                         Mxip_frsid,
                         Mxip_frid,
                         Mxip_frtc,
                         g_chk_date,
                         g_chk_begdate,
                         g_chk_enddate, 
                         appLog.appLogPath,
                         appLog.appLogName,
                         appLog.appLogPath,
                         appLog.appLogName);
	  APPLOG("D", "对账执行=[%s]", command);
       system(command);
    }

    return 0;

}

