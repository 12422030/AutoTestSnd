#include<stdio.h>
int main()
{
    int ret;
    char *srcFile=NULL;
    char *dstFile=NULL;
    char *key=NULL;
    char *keyType=NULL;

    srcFile="HZ_B202005080001_B202005080001.xml.sec";
    dstFile="HZ_B202005080001_B202005080001.xml";
    key="0592F3FF6FDF6994BE3E20A7EF2E869C";
    keyType="S";
    printf("入口参数[%s][%s][%s][%s]\n", srcFile, dstFile, key, keyType);

    ret = UnionAPIService_deFile( -1, srcFile, dstFile, key, keyType);
    if( ret < 0)
    {
        printf("解密文件失败[%d]!\n", ret);
        return ret;
    }

    return 0;
}

