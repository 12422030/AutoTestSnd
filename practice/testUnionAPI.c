#include<stdio.h>
int main()
{
    int ret;
    char *srcFile=NULL;
    char *dstFile=NULL;
    char *key=NULL;
    char *keyType=NULL;

    srcFile="HZ_D202004160001.xml.sec";
    dstFile="HZ_D202004160001.xml";
    key="0457BD802D1485B464391C11C3A7235E";
    keyType="S";
    printf("入口参数[%s][%s][%s][%s]\n", srcFile, dstFile, key, keyType);

    ret = UnionAPIService_deFile( -1, srcFile, dstFile, key, keyType);
    if( ret < 0)
    {
        printf("解密文件失败[%d]!\n", ret);
        return ret;
    }
    printf("解密文件成功[%d]\n",ret);
    printf("解密后的文件为[%s]\n",dstFile);

    return 0;
}

