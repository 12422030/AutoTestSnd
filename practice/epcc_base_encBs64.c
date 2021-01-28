/*******************#BEGIN#******************
 *程 序 名: epcc_base_encBs64
 *中 文 名: 编码base64
 *程序功能: 编码base64
 *程序作者: heqy
 *版 本 号: 1.0.0
 *创建日期: 20161021
********************#END#********************/
/*******************#epcc_base_encBs64-BEGIN#******************
 *函 数 名: epcc_base_encBs64
 *中 文 名: 编码base64
 *函数功能: 
 *函数作者: heqy
 *版 本 号: 1.0.0
 *创建日期: 20161021
 *表 操 作: 
 *            表名         操作方式
 *程序参数: 
 *           数据编码      输入/输出      说明
 *修改历史: 
 *  日期    作者       版本号    变更原因:
 ******************************************************/
#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"

int epcc_base_encBs64(char *bindata,int datalen, char *base64)
{

    int len=0;

    SSLBase64Encode(bindata, datalen, base64,&len) ;

    /*去掉最后一位\n */
    if( base64[len-1] == '\n')
    {
        base64[len-1] = 0x00;
        len -= 1;
    }

    return 0;
}

/********************#epcc_base_encBs64-END#********************/
