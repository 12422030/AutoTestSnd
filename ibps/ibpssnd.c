/*******************************************
 * ����ƽ̨ģ��ǰ�û����˳���
 * �÷�:epccsnd epcc.101.001.01
 *****************************************/
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
    int   sockfd; 
    char   buffer[10240]; 
    char   tmp[10240]; 
    struct   sockaddr_in   server_addr; 
    struct   hostent   *host; 
    int   portnumber,len; 
    char   host_addr[256]; 
    char   host_file[1024]; 
    char   local_file[256]; 
    FILE   *   fp; 
    char   request[10240]; 
    int   send,   totalsend; 
    int   i; 
    char zyw[50000];
    char filename[100];
    char msg_type[5];


#if 0
    strcpy(host_addr,"127.0.0.1");
#endif
#if 1
    strcpy(host_addr,"16.16.17.123");
#endif
    portnumber=7070;
    

    if((host=gethostbyname(host_addr))==NULL)/*ȡ������IP��ַ*/ 
    { 
        fprintf(stderr, "Gethostname   error,   %s\n ",   strerror(errno)); 
        exit(1); 
    } 

    /*   �ͻ�����ʼ����   sockfd������   */ 
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)/*����SOCKET����*/ 
    { 
        fprintf(stderr, "Socket   Error:%s\a\n ",strerror(errno)); 
        exit(1); 
    } 

    /*   �ͻ�����������˵�����   */ 
    bzero(&server_addr,sizeof(server_addr)); 
    server_addr.sin_family=AF_INET; 
    server_addr.sin_port=htons(portnumber); 
    server_addr.sin_addr=*((struct   in_addr   *)host-> h_addr); 

    /*   �ͻ���������������   */ 
    if(connect(sockfd,(struct   sockaddr   *)(&server_addr),sizeof(struct   sockaddr))==-1)/*������վ*/ 
    { 
        fprintf(stderr, "Connect   Error:%s\a\n ",strerror(errno)); 
        exit(1); 
    } 
    
    /* �򿪱����ļ� */
    strcpy( filename, argv[1]);
    fp = fopen( filename, "r");
    if (fp==NULL)
    {
        printf( "���ļ�ʧ��[%d]", filename);
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
    
	bzero(request,sizeof(request));
	sprintf(request,"%08ld",strlen(tmp)+8);
	sprintf(request+strlen(request),"1014%s",argv[1]);
    
    strcat( request, tmp);
#if 0
    sprintf(request+strlen(request),"\r\n");
#endif
    printf( "���ͱ���[%s]\n",   request);/*׼��request����Ҫ���͸�����*/ 

    /*��������*/ 
    send = write(sockfd,request,strlen(request));

    /*   ���ӳɹ��ˣ�����http��Ӧ��response   */ 
    bzero(tmp,sizeof(tmp));
    bzero(buffer,sizeof(buffer));
    while((len=read(sockfd,buffer,1))==1)
    {
        i++;
        strcat(tmp,buffer);
    }
    printf("�Ѿ��յ���������Ϊ:\n[%s]\n",tmp);
    fclose(fp);
    
    /*   ����ͨѶ   */ 
    close(sockfd); 
    exit(0); 
} 

