/*******************#BEGIN#******************
 *程 序 名: epcc_base_decBs64
 *中 文 名: 解密base64
 *程序功能: 解密base64
 *程序作者: shigs
 *版 本 号: 1.0.0
 *创建日期: 2017.09.05
 *注意事项：
 *
********************#END#********************/
#include "kernel/syspub.h"
#include "kernel/xipcmstc.h"

int epcc_base_decBs64(char *base64, char *bindata,int *outlen)
{
    int i=0;
    int asclen=0;
    char *tmpBuf=NULL;


    tmpBuf = (char *) calloc(strlen(base64)*3, sizeof(char));
    if( tmpBuf== NULL)
    {   
        APPLOG("E","内存不足!!![%s]", strerror(errno));
        return -5; 
    }   

    if ( strchr(base64, 0x0d) ==NULL && strchr(base64,0x0a)==NULL )
    {   
        for(i=1; i<(strlen(base64)/64)+1; i++)
        {   
            memcpy(tmpBuf+strlen(tmpBuf), base64+(i-1)*64, 64) ;
            memcpy(tmpBuf+strlen(tmpBuf), "\n", 1) ;
        }   
        if ( strlen(base64)%64 ) 
        {
            sprintf(tmpBuf+strlen(tmpBuf), "%s\n", base64+(i-1)*64) ;
        }
    }
    else
    {
        strcpy(tmpBuf, base64) ;
    }

    SSLBase64Decode(tmpBuf, strlen(tmpBuf),bindata,&asclen);

    *outlen = asclen;
    free( tmpBuf);

    tmpBuf= NULL;

    return 0;

}

