/************************************************
<Root>
    <ClearCntNb>2</ClearCntNb>
    <DebitCntAmt>CNY100.00</DebitCntAmt>
    <CreditCntAmt>CNY100.00</CreditCntAmt>
    <ClearList>
        <ClearInf>
            <ClearReptFlg>2017052012330901</ClearReptFlg>
            <ClearDCFlg>1</ClearDCFlg>
            <ClearAmt>CNY100.00</ClearAmt>
            <BatchList>
                <BatchInf>
                    <BatchId>B201705200001</BatchId>
                    <BatchDCFlg>1</BatchDCFlg>
                    <BatchNetAmt>CNY200.00</BatchNetAmt>
                </BatchInf>
                <BatchInf>
                    <BatchId>B201705200002</BatchId>
                    <BatchDCFlg>2</BatchDCFlg>
                    <BatchNetAmt>CNY100.00</BatchNetAmt>
                </BatchInf>
            </BatchList>
        </ClearInf>
    </ClearList>
</Root>
************************************************/
#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"
#include "epcc/tabincl/epcc_clearfile_c.h"
#include "epcc/epccpub.h"
#include "libxml/xpath.h"

int epccAuSttlOpenFile(TxipCMStc *xip)
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
    struct epcc_clearfile_c epcc_clearfile_s;

    xmlDocPtr doc;
    xmlNodePtr curNode;
    xmlNodePtr node1;
    xmlNodePtr node2;
    xmlNodePtr node3;
    xmlChar *szKey;

    memset(filename, 0x00, sizeof(filename));
    memset(plat_time, 0x00, sizeof(plat_time));
    memset(&epcc_clearfile, 0x00, sizeof(struct epcc_clearfile_c));
    memset(&epcc_clearfile_s, 0x00, sizeof(struct epcc_clearfile_c));

    get_zd_long("0440", &curDate);
    get_zd_long("0780", &plat_trno);
    get_zd_long("0770", &plat_date);
    get_zd_data(XIPTYPEPARM, plat_time);

    xmlKeepBlanksDefault (0);

    get_zd_data("0260", filename);
    sprintf(filePath, "%s/clearfile/%08ld/%s", Mxip_rfpath, curDate, filename);

    APPLOG("D","filePath--[%s]", filePath);

    doc = xmlReadFile(filePath, "GBK",XML_PARSE_RECOVER);
    if( NULL == doc)
    {
        APPLOG("E","��ȡ���ڵ����!!!![%s]", strerror(errno));
        strcpy(Mxip_rc, "EP01");
        return -5;
    }

    curNode =  xmlDocGetRootElement(doc); //ȷ���ļ���Ԫ��root
    if( NULL == curNode)
    {
        APPLOG("E","��ȡ���ڵ����!!!![%s]", strerror(errno));
        strcpy(Mxip_rc, "EP01");
        return -5;
    }
    APPLOG("D","curNode-[%s]", curNode->name);

    //**1.ClearCntNb
    node1 = curNode->xmlChildrenNode;
    szKey =  xmlNodeGetContent(node1);
    if( szKey != NULL)
    {
        APPLOG("D","curNode-[%s][%s]", node1->name, szKey);
        epcc_clearfile.sum_num  = atol((const char *)szKey);
        xmlFree(szKey);
    }
    APPLOG("D", "epcc_clearfile.sum_num=[%ld]", epcc_clearfile.sum_num);

    //**2.DebitCntAmt
    curNode = node1->next;
    szKey =  xmlNodeGetContent(curNode);
    if( szKey != NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        epcc_clearfile.debit_amt = atof((const char *)szKey+3);
        xmlFree(szKey);
    }

    //**3.CreditCntAmt
    curNode = curNode->next;
    szKey =  xmlNodeGetContent(curNode);
    if( szKey != NULL)
    {
        APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
        epcc_clearfile.credt_amt = atof ((const char *)szKey+3);
        xmlFree(szKey);
    }

    //**4.ClearList
    curNode = curNode->next;
	/*L0001 add beg*/
	if(curNode!=NULL)
    {
		APPLOG("D","curNode-[%s]", curNode->name);

		//**5.ClearInf
		node2 = curNode->xmlChildrenNode;
		while(node2 !=  NULL)
		{
			APPLOG("D","curNode-[%s]", node2->name);
			//**6.ClearReptFlg
			curNode = node2->xmlChildrenNode;
			szKey =  xmlNodeGetContent(curNode);  
			if( szKey != NULL)
			{
				APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
				strcpy(epcc_clearfile.clear_msgid, (const char *)szKey);
				xmlFree(szKey);
			}
			memset(datetmp, 0x00, sizeof(datetmp));
			strncpy(datetmp, epcc_clearfile.clear_msgid, 8);
			APPLOG("D", "datetmp=[%s]", datetmp);
			epcc_date=atol(datetmp);
			APPLOG("D", "epcc_date=[%ld]", epcc_date);

			//**7.ClearDCFlg
			curNode = curNode->next;
			szKey =  xmlNodeGetContent(curNode);
			if( szKey != NULL)
			{
				APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
				strcpy(epcc_clearfile.cd_flag, (const char *)szKey);
				xmlFree(szKey);
			}

			//**8.ClearAmt
			curNode = curNode->next;
			szKey =  xmlNodeGetContent(curNode);
			if( szKey != NULL)
			{
				APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
				epcc_clearfile.clear_amt = atof( (const char *)szKey+3);
				xmlFree(szKey);
			}
			/*Mod beg*/

			/*������Ϊ��ʱ����*/
			if (CompDoubleValue(epcc_clearfile.clear_amt,0.00 ) == 0)
			{
				memset(epcc_clearfile.clear_msgid,0x00,sizeof(epcc_clearfile.clear_msgid));
				ret=epcc_getseqence(&traceno, Mxip_rc);
				if(ret)
				{
					APPLOG("E", "ȡϵͳ��ˮ��ʧ��[%d]",ret) ;
					return -1;
				}

				sprintf(epcc_clearfile.clear_msgid,"JZ%08ld%08ld",plat_date,traceno);
				APPLOG("D","clear_msgid=[%s]",epcc_clearfile.clear_msgid);

			}
			/*Mod end*/

			strcpy(epcc_clearfile.sttl_filename, filename);  /**�����ļ�����**/
			epcc_clearfile.epcc_date = epcc_date;    /**��������**/
			strcpy(epcc_clearfile.list_type,"0");   /**�����б�־**/
			strcpy(epcc_clearfile.batchid, "");  /**���κ�**/
			strcpy(epcc_clearfile.batch_cdflag, "");  /**���ν����־**/
			epcc_clearfile.batch_netamt = 0;  /**���������**/
			epcc_clearfile.plat_date = plat_date;  /**��������**/
			epcc_clearfile.plat_trace = plat_trno;  /**������ˮ**/
			strcpy(epcc_clearfile.plat_time,  plat_time);  /**����ʱ��**/
			strcpy(epcc_clearfile.sts, "0");  /**�����־**/


			ret = Epcc_clearfile_Ins( epcc_clearfile, Mxip_rc);
			if(ret !=0)
			{
				APPLOG("E", "�������ݿ��쳣!!![%d]", ret);
				strcpy(Mxip_rc, "EP01");
				set_zd_data( XIPREPLYMSG, "���ݿ��쳣!");
				return -5;
			}
			APPLOG("D", "�����в������");
			//**9.BatchList
			curNode = curNode->next;
			APPLOG("D","curNode-[%s]", curNode->name);

			//**10.BatchInf
			node3 = curNode->xmlChildrenNode;
			APPLOG("D","curNode-[%s]", node3->name);

			while(node3 != NULL)
			{
				//**11.BatchId
				curNode = node3->xmlChildrenNode;
				szKey =  xmlNodeGetContent(curNode);
				if( szKey != NULL)
				{
					APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
					strcpy( epcc_clearfile.batchid, (const char *)szKey);
					xmlFree(szKey);
				}
				memset(datetmp1, 0x00, sizeof(datetmp1));
				strncpy(datetmp1, epcc_clearfile.batchid+1, 8);
				APPLOG("D", "datetmp1=[%s]", datetmp1);
				epcc_date=atol(datetmp1);
				APPLOG("D", "epcc_date=[%ld]", epcc_date);

				//**12.BatchDCFlg
				curNode->next;
				szKey =  xmlNodeGetContent(curNode);
				if( szKey != NULL)
				{
					APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
					strcpy(epcc_clearfile.batch_cdflag, (const char *)szKey);
					xmlFree(szKey);
				}  

				//**13.BatchNetAmt
				curNode = curNode->next;
				szKey =  xmlNodeGetContent(curNode);
				if( szKey != NULL)
				{
					APPLOG("D","curNode-[%s][%s]", curNode->name, szKey);
					epcc_clearfile.batch_netamt = atof( (const char *)szKey+3);
					xmlFree(szKey);
				}

				strcpy(epcc_clearfile.sttl_filename,filename);
				epcc_clearfile.epcc_date = epcc_date;
				epcc_clearfile.sum_num=0;
				epcc_clearfile.debit_amt=0;
				epcc_clearfile.credt_amt=0;
				strcpy(epcc_clearfile.list_type,"1");
				epcc_clearfile.clear_amt=0;
				epcc_clearfile.plat_date = plat_date;
				epcc_clearfile.plat_trace = plat_trno;
				strcpy(epcc_clearfile.plat_time,plat_time);
				strcpy(epcc_clearfile.sts,"0");

				ret = Epcc_clearfile_Ins( epcc_clearfile, Mxip_rc);
				if(ret !=0)
				{
					APPLOG("E", "�������ݿ��쳣!!![%d]", ret);
					strcpy(Mxip_rc, "EP01");
					set_zd_data( XIPREPLYMSG, "���ݿ��쳣!");
					return -5;
				}

				APPLOG("D","��ϸ�в������һ��");
				APPLOG("D","node3-[%s]", node3->name);
				node3 = node3 ->next;
			}
			APPLOG("D","һ��clear_msgid��ϸ��ȫ���������");
			APPLOG("D","!!!curNode-[%s]", node2->name);
			node2 = node2 ->next;
		}
	}
	/*L0001 add end*/

    xmlFreeDoc(doc);

    strcpy(Mxip_rc, "0000");

    return 0;


}
