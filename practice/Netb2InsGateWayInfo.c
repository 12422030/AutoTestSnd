#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"
#include "epcc/tabincl/epcc_gateway_c.h"
#include "epcc/epccpub.h"
#include "libxml/xpath.h"

int Netb2InsGateWayInfo(TxipCMStc *xip)
{
    int ret;
    char filename[200];
    char filePath[256];
    long plat_date=0;
    long plat_trace=0;
    char plat_time[21]={0};

    struct epcc_gateway_c epcc_gateway;

    xmlDocPtr doc;
    xmlNodePtr curNode;
    xmlNodePtr node1;
    xmlNodePtr node2;
    xmlNodePtr node3;
    xmlNodePtr node4;
    xmlNodePtr node5;
    xmlNodePtr node6;
    xmlNodePtr node7;
    xmlNodePtr node8;
    xmlChar *szKey;

    memset(filename, 0x00, sizeof(filename));
    memset(&epcc_gateway, 0x00, sizeof(struct epcc_gateway_c));

    get_zd_data("1035",filename);
    get_zd_long("0770",&plat_date);
    get_zd_long("0780",&plat_trace);
    get_zd_data("0020",plat_time);

    xmlKeepBlanksDefault(0);

    sprintf(filePath,"%s/%s",Mxip_rfpath,filename);
    APPLOG("D","filePath--[%s]", filePath);

    doc = xmlReadFile(filePath,"GBK",XML_PARSE_RECOVER);
    if(NULL==doc)
    {
        APPLOG("E","读取根节点错误!!!![%s]", strerror(errno));
        strcpy(Mxip_rc, "EP01");
        return -5;
    }
    curNode=xmlDocGetRootElement(doc); //确定文件根元素root
    if(NULL==curNode)
    {
        APPLOG("E","读取根节点错误!!!![%s]", strerror(errno));
        strcpy(Mxip_rc, "EP01");
        return -5;
    }
    APPLOG("D","curNode-[%s]", curNode->name);

    /**1.PyerInf**/
    node1 = curNode->xmlChildrenNode;
    curNode=node1->xmlChildrenNode;
    APPLOG("D","--------curNode[%s][%s]",node1->name);
    szKey=xmlNodeGetContent(curNode);  
    if(szKey!=NULL)                 /**PyerAcctIssrId**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payerlssid, (const char *)szKey);
        strtrim(epcc_gateway.payerlssid);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**CBFlg**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.cbflg,(const char *)szKey);
        strtrim(epcc_gateway.cbflg);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**LmtAcctTpCd**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.lmtp, (const char *)szKey);
        strtrim(epcc_gateway.lmtp);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyerAcctTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeractp, (const char *)szKey);
        strtrim(epcc_gateway.payeractp);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyerTrxTrmTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payertxtrmtp, (const char *)szKey);
        strtrim(epcc_gateway.payertxtrmtp);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyerTrxTrmNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payertxtrmno, (const char *)szKey);
        strtrim(epcc_gateway.payertxtrmno);
        xmlFree(szKey);
    }

    /**2.PyeeInf**/
    node2 = node1->next;
    curNode=node2->xmlChildrenNode;
    APPLOG("D","curNode----------[%s]",node2->name);
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**PyeeAcctIssrId**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeelssid, (const char *)szKey);
        strtrim(epcc_gateway.payeelssid);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeAcctTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeeactp, (const char *)szKey);
        strtrim(epcc_gateway.payeeactp);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeAcctId**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeeacno, (const char *)szKey);
        strtrim(epcc_gateway.payeeacno);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeNm**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeeacname, (const char *)szKey);
        strtrim(epcc_gateway.payeeacname);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeCtryNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeecityno, (const char *)szKey);
        strtrim(epcc_gateway.payeecityno);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeAreaNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeeareano, (const char *)szKey);
        strtrim(epcc_gateway.payeeareano);
        xmlFree(szKey);
    }

    curNode=curNode->next;          /**PyeeTrxTrmTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeetxtrmtp, (const char *)szKey);
        strtrim(epcc_gateway.payeetxtrmtp);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeTrxTrmNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.payeetxtrmno, (const char *)szKey);
        strtrim(epcc_gateway.payeetxtrmno);
        xmlFree(szKey);
    }
    
    /**3.ResfdInf**/
    node3 = node2->next;
    curNode=node3->xmlChildrenNode;
    APPLOG("D","curNode-----------[%s]",node3->name);
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.instglssid, (const char *)szKey);
        strtrim(epcc_gateway.instglssid);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                /**InstgAcctId**/ 
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.instgacno, (const char *)szKey);
        strtrim(epcc_gateway.instgacno);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)               /**InstgAcctNm**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.instgacname, (const char *)szKey);
        strtrim(epcc_gateway.instgacname); 
        xmlFree(szKey);
    }
    /**4.RPFlg**/
    node4 = node3->next;
    szKey=xmlNodeGetContent(node4);
    if(szKey!=NULL)                
    {
        APPLOG("D","curNode------------[%s]",node4->name);
        strcpy(epcc_gateway.rp_flag, (const char *)szKey);
        strtrim(epcc_gateway.rp_flag);
        xmlFree(szKey);
    }
    
    /**5.TrxInf**/
    node5 = node4->next;
    curNode=node5->xmlChildrenNode;
    APPLOG("D","curNode-----------[%s]",node5->name);
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxId**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.epcc_trace, (const char *)szKey);
        strtrim(epcc_gateway.epcc_trace);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxDtTm**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.epcc_time, (const char *)szKey);
        strtrim(epcc_gateway.epcc_time);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxAtm**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        epcc_gateway.tx_amt=atof((const char *)szKey+3);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxCtgy**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.txctgy, (const char *)szKey);
        strtrim(epcc_gateway.txctgy);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**BizTp**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.bzitype,(const char *)szKey);
        strtrim(epcc_gateway.bzitype);
        xmlFree(szKey);
    }
    
    /**6.OrdrInf**/
    node6 = node5->next;
    curNode=node6->xmlChildrenNode;
    APPLOG("D","curNode-----------[%s]",node6->name);
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**OrdrId**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.orderid, (const char *)szKey);
        strtrim(epcc_gateway.orderid);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**OrdrDesc**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.orderdesc, (const char *)szKey);
        strtrim(epcc_gateway.orderdesc);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**OrdrExp**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.orderexp,(const char *)szKey);
        strtrim(epcc_gateway.orderexp);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**PltfrmNm**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.pltfrmnm,(const char *)szKey);
        strtrim(epcc_gateway.pltfrmnm);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**ClbckUrl**/
    {
        APPLOG("D","[%s][%s]", curNode->name, szKey);
        strcpy(epcc_gateway.clbckurl, (const char *)szKey);
        strtrim(epcc_gateway.clbckurl);
        xmlFree(szKey);
    }
    
    /**7.TrxDevcInf**/
    node7 = node6->next;
    szKey=xmlNodeGetContent(node7);
    if(szKey!=NULL)                
    {
        APPLOG("D","curNode-----------[%s]",node7->name);
        strcpy(epcc_gateway.txdevid, (const char *)szKey);
        strtrim(epcc_gateway.txdevid);
        xmlFree(szKey);
    }
    
    /**8.GwChnnlTp**/
    node8 = node7->next;
    szKey=xmlNodeGetContent(node8);
    if(szKey!=NULL)             
    {
        APPLOG("D","curNode-----------[%s]",node8->name);
        strcpy(epcc_gateway.chnltp, (const char *)szKey);
        strtrim(epcc_gateway.chnltp);
        xmlFree(szKey);
    }
    
    ret=Epcc_gateway_Ins(epcc_gateway,Mxip_rc);
    if(ret)
    {
        APPLOG("E", "插入数据库异常!!![%d]", ret);
        strcpy(Mxip_rc, "EP01");
        set_zd_data( XIPREPLYMSG, "数据库异常!");
        return -5;
    }

    xmlFreeDoc(doc);

    set_zd_data("0820",epcc_gateway.orderid);
    set_zd_data("0020",epcc_gateway.epcc_time);
    set_zd_double("0400",epcc_gateway.tx_amt);
    
    strcpy(Mxip_rc, "0000");
    return 0;
}
