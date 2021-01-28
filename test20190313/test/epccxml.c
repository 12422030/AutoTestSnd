#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"
#include "epcc/tabincl/epcc_clearfile_c.h"
#include "epcc/epccpub.h"
#include "libxml/xpath.h"

int NetbAuSttlOpenFile(TxipCMStc *xip)
{
    int ret;
    char filename[200];
    char filePath[256];
    long curDate=0;
    long epcc_date=0;
    long plat_date=0;
    long plat_trno=0;
    long traceno=0;
    char plat_time[20];
    char datetmp[10];
    char datetmp1[10];

    struct epcc_clearfile_c epcc_clearfile;

    xmlDocPtr doc;
    xmlNodePtr curNode;
    xmlNodePtr node1;
    xmlNodePtr node2;
    xmlNodePtr node3;
    xmlNodePtr node4;
    xmlNodePtr node5;
    xmlNodePtr node6;
    xmlChar *szKey;

    memset(filename, 0x00, sizeof(filename));
    memset(plat_time, 0x00, sizeof(plat_time));
    memset(&epcc_clearfile, 0x00, sizeof(struct epcc_clearfile_c));

    get_zd_data("1035",fiename);
    get_zd_data(XIPTYPEPARM,plat_time);

    xmlKeepBlanksDefault(0);

    sprintf(filePath,"%s/%s",Mxip_rfpath,filename);
    APPLOG("D","filePath--[%s]", filePath);

    doc = xmlReadFile(filePath, "GBK",XML_PARSE_RECOVER);
    if( NULL == doc)
    {
        APPLOG("E","读取根节点错误!!!![%s]", strerror(errno));
        strcpy(Mxip_rc, "EP01");
        return -5;
    }
    curNode =  xmlDocGetRootElement(doc); //确定文件根元素root
    if( NULL == curNode)
    {
        APPLOG("E","读取根节点错误!!!![%s]", strerror(errno));
        strcpy(Mxip_rc, "EP01");
        return -5;
    }
    APPLOG("D","curNode-[%s]", curNode->name);

    /**1.PyerInf**/
    node1 = curNode->xmlChildrenNode;
    curNode=node1->xmlChildrenNode;
    szKey=xmlNodeGetContent(curNode);  
    if(szKey!=NULL)                 /**PyerAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**CBFlg**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    curNode=curNode->next;          /**LmtAcctTpCd**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyerAcctTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyerTrxTrmTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyerTrxTrmNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    /**2.PyeeInf**/
    node2 = curNode1->next;
    curNode=node2->xmlChildrenNode;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**PyeeAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeAcctTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    curNode=curNode->next;          /**PyeeAcctId**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeNm**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeCtryNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;          /**PyeeAreaNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    curNode=curNode->next;          /**PyeeTrxTrmTp**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    curNode=curNode->next;          /**PyeeTrxTrmNo**/
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    /**3.ResfdInf**/
    node3 = curNode1->next;
    curNode=node3->xmlChildrenNode;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    /**4.RPFlg**/
    node4 = curNode1->next;
    szKey=xmlNodeGetContent(node4);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", node4->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    /**5.TrxInf**/
    node5 = curNode1->next;
    while(node5 != NULL)
        curNode=node5->xmlChildrenNode;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxDtTm**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxAtm**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**TrxCtgy**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**BizTp**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    /**6.OrdrInf**/
    node6 = curNode1->next;
    curNode=node6->xmlChildrenNode;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**OrdrId**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**OrdrDesc**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**OrdrExp**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**PltfrmNm**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    curNode=curNode->next;
    szKey=xmlNodeGetContent(curNode);
    if(szKey!=NULL)                 /**ClbckUrl**/
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    /**7.TrxDevcInf**/
    node7 = curNode1->next;
    szKey=xmlNodeGetContent(node7);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", node4->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }
    /**8.GwChnnlTp**/
    node8 = curNode1->next;
    szKey=xmlNodeGetContent(node8);
    if(szKey!=NULL)                 /**ResfdAcctIssrId**/
    {
        APPLOG("D","curNode-[%s][%s]", node4->name, szKey);
        strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
        xmlFree(szKey);
    }

    ret=Epcc_netbinfo_Ins(epcc_clearfile,Mxip_rc);
    {
        APPLOG("E", "插入数据库异常!!![%d]", ret);
        strcpy(Mxip_rc, "EP01");
        set_zd_data( XIPREPLYMSG, "数据库异常!");
        return -5;
    }

    xmlFreeDoc(doc);

    strcpy(Mxip_rc, "0000");
    return 0;
}
