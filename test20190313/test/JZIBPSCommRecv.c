#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"
#include "libxml/xmlreader.h"

#include "jzibps/ibpspub.h"

int JZIBPSCommRecv(TxipCMStc *xip)
{
    char sPkgLen[9];
    char sPkgHead[31];
    char *sPkgBuf = NULL;
    char pkgType[5];
    char fileName[31];
    char fullName[201];
    char sTmpStr[31];
    FILE *fp = NULL;
    xmlDocPtr doc;
    int  memFlag = 0; /*内存动态分配标志0-未分配1-已分配*/
    int  ret;

    /*1.接收8位报文长度*/
    memset(sPkgLen, 0x00, sizeof(sPkgLen));

    ret = TcpRecv(Mxip_sockid, sPkgLen, 8, Mxip_frtmout);
    if (ret) 
    { 
       APPLOG("E", "TCPIP Receive PackLen Failed!ret=[%d]", ret); 
       return -5;
    }

    sPkgLen[8] = 0;
    Mxip_pkglen = atol(sPkgLen);

    APPLOG("W", "报文长度=[%s]", sPkgLen);

    if (Mxip_pkglen <= 60*1024)
    {
       memset(Mxip_rbuf, 0x00, sizeof(Mxip_rbuf));
       memFlag = 0;
    }
    else
    {
       sPkgBuf = (char *)malloc(Mxip_pkglen + 1);
       if (sPkgBuf == NULL)
       {
          APPLOG("E", "Malloc sPkgBuf Error!size=[%d]", Mxip_pkglen);
          return -10;
       }
       memFlag = 1;
    }

    /*2.接收8位报文头*/
    memset(sPkgHead, 0x00, sizeof(sPkgHead));

    ret = TcpRecv(Mxip_sockid, sPkgHead, 8, Mxip_frtmout);
    if (ret) 
    { 
       APPLOG("E", "TCPIP Receive sPkgHead Failed!ret=[%d][%s]", ret, strerror(errno)); 
       if (memFlag == 1) free(sPkgBuf);
       return -15;
    }
APPLOG("D", "sPkgHead = [%s]", sPkgHead);

    /*3.接收报文体*/
    if (memFlag == 0)
    { 
       ret = TcpRecv(Mxip_sockid, Mxip_rbuf, Mxip_pkglen-8, Mxip_frtmout);
       if (ret) 
       { 
          APPLOG("E", "TCPIP Receive Pack Failed![%d][%s]", ret, strerror(errno)); 
          return -20; 
       }
APPLOG("D", "Mxip_rbuf = [%s]", Mxip_rbuf);
    }
    else
    {
       ret = TcpRecv(Mxip_sockid, sPkgBuf, Mxip_pkglen-8, Mxip_frtmout);
       if (ret) 
       { 
          APPLOG("E", "TCPIP Receive Pack Failed![%d][%s]", ret, strerror(errno)); 
          free(sPkgBuf);
          return -25; 
       }
APPLOG("D", "sPkgBuf = [%s]", sPkgBuf);
    }

    /*4.解析报文头*/

    /*报文类型4位*/
    memcpy(pkgType, sPkgHead, 4);
    pkgType[4] = 0;

    /*交易码4位*/
    memset(Mxip_frtc, 0x00, sizeof(Mxip_frtc));
    memcpy(Mxip_frtc, sPkgHead+4, 4);
    Mxip_frtc[4] = 0;
    set_cm_data(FROMTRCODE, Mxip_frtc);
APPLOG("D", "Mxip_frtc = [%s]", Mxip_frtc);

    /*5.解析报文体*/
    if (memFlag == 0)
    {
       doc = xmlReadMemory(Mxip_rbuf, Mxip_pkglen-8, NULL, NULL, 0);
       if (doc == NULL)
       {
          APPLOG("E", "Call xmlReadMemory Error");
          return -30; 
       }
    }
    else
    {
       doc = xmlReadMemory(sPkgBuf, Mxip_pkglen-8, NULL, NULL, 0);
       if (doc == NULL)
       {
          APPLOG("E", "Call xmlReadMemory Error");
          free(sPkgBuf);
          return -35; 
       }
    }

    ret = TradeInfoCheck(xip);
    if (ret)
    {
       APPLOG("E", "Call TradeInfoCheck Error=[%d][%s]", ret, Mxip_frtc);
       xmlFreeDoc(doc);
       xmlCleanupParser();
       xmlMemoryDump();
       if (memFlag == 1) free(sPkgBuf);
       return -40;
    }

    memset(fileName, 0x00, sizeof(fileName));
    if (Mxip_frtrbflag[0] == '1' || Mxip_frtrbflag[0] == '3')
    {
       CreateTmpFileName(fileName);

       sprintf(fullName, "%s/%s", Mxip_rfpath, fileName);
       fp = fopen(fullName, "w");
       if (fp == NULL)
       {
          APPLOG("E", "Open File [%s] Err![%s]", fileName, strerror(errno));
          xmlFreeDoc(doc);
          xmlCleanupParser();
          xmlMemoryDump();
          if (memFlag == 1) free(sPkgBuf);
          return -45;
       }
       set_cm_data(RECVFILENAME, fileName);
    }

    ret = XmlParseAndAttr("N", Mxip_frid, Mxip_frdcmode, Mxip_frtc, Mxip_frfsign, doc, NULL, fp, Mxip_rc);
    if (ret)
    {
       APPLOG("E", "Call XmlParseAndAttr Error=[%d][%s]", ret, Mxip_rc);
       xmlFreeDoc(doc);
       xmlCleanupParser();
       xmlMemoryDump();
       if (memFlag == 1) free(sPkgBuf);
       if (fp != NULL) fclose(fp);
       return -40;
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();
    if (memFlag == 1) free(sPkgBuf);
    if (fp != NULL) fclose(fp);

    return 0;

}

