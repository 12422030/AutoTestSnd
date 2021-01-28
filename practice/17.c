#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  
    int Mxip_pkglen=10;
    char *pRecvBuf=NULL;     
    pRecvBuf = calloc(Mxip_pkglen+1, sizeof(char)) ;
    if( pRecvBuf != NULL)
    {
       printf("内存不足!!,分配报文存储位置成功!\n");
    }

    printf("11111");  
    printf("%s",pRecvBuf);
    printf("22222");
    strcpy(pRecvBuf,"13223");
    printf("%s",pRecvBuf);
    free(pRecvBuf);
    printf("%s",pRecvBuf);
    return 0;
}
