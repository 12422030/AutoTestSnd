#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <sys/types.h>
#include   <sys/socket.h>
#include   <errno.h>
#include   <unistd.h>
#include   <netinet/in.h>
#include   <limits.h>
#include   <netdb.h>
#include   <arpa/inet.h>
#include   <ctype.h>

int main(int argc,char *argv[])
{
    char reply[15];
    int sock;
    struct sockaddr_in sin;

    char msg[102400];
    char buffer[10240];
    char tmp[50000];
    char filename[100];
    int i;
    FILE * fp=NULL;
    int send,totalsend;
    int len;
    
    char ip[256];
    char key[25];
    char filepath[200];
    unsigned char realPkg[1024*10];
    char syscode[10];
    
    memset(key,0x00,sizeof(key));
    memset(filepath,0x00,sizeof(filepath));
    memset(realPkg,0x00,sizeof(realPkg));
    memset(syscode,0x00,sizeof(syscode));

    //strcpy(ip,"127.0.0.1");    
    strcpy(ip,"16.16.22.108");    

    if( argc != 2)
    {
        printf("useage:\n  cbsnd 文件名\n");
        return -1;
    }

    /*端口号,如果服务程序修改,在此处修改*/
    int port = 9767 ; 

    /**建立流式socket**/
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)/*IPPROTO_TCP可直接置为0*/
    {
        perror("socket");
        printf("--->%s,%d建立sock失败!!!", __FILE__, __LINE__);
        exit(1);
    }

    bzero(&sin,sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;/*Internet地址族AF_xxx*/
    sin.sin_port = htons(port);              /*端口号*如果为0则bind帮你选择一个端口*/
    sin.sin_addr.s_addr = inet_addr(ip);     /*Internet地址*INADDR_ANY(0)为本机地址*/
    bzero(&(sin.sin_zero), 8);               /*结构体剩余部分数据设为0*/

    /**连接目标主机**/
    if( connect(sock, (struct sockaddr *) & sin,sizeof(sin)) <0 )
    {
        printf("连接错误\n");
        close(sock);
        return -1;
    }

    sprintf( filename, "%s/src/hf/test/msg/%s",getenv("HOME"),argv[1]);
    printf("要打开的发送文件名[%s]\n",filename);
    fp = fopen( filename, "r");
    if (fp==NULL)
    {
        printf( "打开文件失败[%s]", filename);
        return -1;
    }
    while(1)
    {
        bzero( buffer, sizeof(buffer));
        fgets( buffer, 1024, fp);
        strcat( tmp, buffer);
        if( feof(fp))
        {
            break;
        }
    }
    bzero(msg,sizeof(msg));
    
    /*** 组通讯报文头 ***/

    char *pHead=NULL;

    pHead=(char *)malloc(21);
     
    memcpy(pHead,"313053",6);  /**系统标识号**/
    
    memcpy(pHead+6,"0",1);
     
    memset(pHead+7,0x00,9);
    
    len = strlen(tmp)+20;
     
    int nlen=htonl(strlen(tmp));
    memcpy(pHead+16,&nlen,4);

    memset(buffer,0x00,sizeof(buffer));

    sprintf(filepath,"%s/%s",getenv("HOME"),"etc/hf/sessionKey");
     
    fp = fopen(filepath,"r");
    if(fp == NULL)
    {
        /** APPLOG("E","Open File error [%s]",filepath); **/
        free(pHead);
        return -10;
    }
    fgets(key,1024,fp);
    fclose(fp);
    key[24]=0;


    /** 加密 **/
    int enclen = des3enc(key,msg,strlen(msg),realPkg,sizeof(realPkg));
    if(enclen == -1)
    {
        /** APPLOG("E","加密失败[%d]",enclen); **/
        free(pHead);
        return -10;
    }


    memcpy(buffer,pHead,20);
    memcpy(buffer+20,realPkg,strlen(realPkg));

    /*** 结束 ***/


    send = write(sock,buffer,strlen(buffer));

    printf( "已经发送报文长度[%d]内容:\n[%s]\n", strlen(buffer), buffer);/*准备msg，将要发送给主机*/

    /*连接成功了，接收-----响应，response   */
    bzero(tmp,sizeof(tmp));
    while((len=read(sock,buffer,1))==1)
    {
        i++;
        strcat(tmp,buffer);
    }
    printf("已经收到报文内容为:\n[%s]\n",tmp);
    fclose(fp);
    /*   结束通讯   */
    close(sock);
    exit(0);
}
