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
        printf("useage:\n  cbsnd �ļ���\n");
        return -1;
    }

    /*�˿ں�,�����������޸�,�ڴ˴��޸�*/
    int port = 9767 ; 

    /**������ʽsocket**/
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)/*IPPROTO_TCP��ֱ����Ϊ0*/
    {
        perror("socket");
        printf("--->%s,%d����sockʧ��!!!", __FILE__, __LINE__);
        exit(1);
    }

    bzero(&sin,sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;/*Internet��ַ��AF_xxx*/
    sin.sin_port = htons(port);              /*�˿ں�*���Ϊ0��bind����ѡ��һ���˿�*/
    sin.sin_addr.s_addr = inet_addr(ip);     /*Internet��ַ*INADDR_ANY(0)Ϊ������ַ*/
    bzero(&(sin.sin_zero), 8);               /*�ṹ��ʣ�ಿ��������Ϊ0*/

    /**����Ŀ������**/
    if( connect(sock, (struct sockaddr *) & sin,sizeof(sin)) <0 )
    {
        printf("���Ӵ���\n");
        close(sock);
        return -1;
    }

    sprintf( filename, "%s/src/hf/test/msg/%s",getenv("HOME"),argv[1]);
    printf("Ҫ�򿪵ķ����ļ���[%s]\n",filename);
    fp = fopen( filename, "r");
    if (fp==NULL)
    {
        printf( "���ļ�ʧ��[%s]", filename);
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
    
    /*** ��ͨѶ����ͷ ***/

    char *pHead=NULL;

    pHead=(char *)malloc(21);
     
    memcpy(pHead,"313053",6);  /**ϵͳ��ʶ��**/
    
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


    /** ���� **/
    int enclen = des3enc(key,msg,strlen(msg),realPkg,sizeof(realPkg));
    if(enclen == -1)
    {
        /** APPLOG("E","����ʧ��[%d]",enclen); **/
        free(pHead);
        return -10;
    }


    memcpy(buffer,pHead,20);
    memcpy(buffer+20,realPkg,strlen(realPkg));

    /*** ���� ***/


    send = write(sock,buffer,strlen(buffer));

    printf( "�Ѿ����ͱ��ĳ���[%d]����:\n[%s]\n", strlen(buffer), buffer);/*׼��msg����Ҫ���͸�����*/

    /*���ӳɹ��ˣ�����-----��Ӧ��response   */
    bzero(tmp,sizeof(tmp));
    while((len=read(sock,buffer,1))==1)
    {
        i++;
        strcat(tmp,buffer);
    }
    printf("�Ѿ��յ���������Ϊ:\n[%s]\n",tmp);
    fclose(fp);
    /*   ����ͨѶ   */
    close(sock);
    exit(0);
}
