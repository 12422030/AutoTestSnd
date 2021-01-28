/*******************************************
 * 网联平台模拟前置机来账程序
 * 用法:epccsnd epcc.101.001.01
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
    

    if((host=gethostbyname(host_addr))==NULL)/*取得主机IP地址*/ 
    { 
        fprintf(stderr, "Gethostname   error,   %s\n ",   strerror(errno)); 
        exit(1); 
    } 

    /*   客户程序开始建立   sockfd描述符   */ 
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)/*建立SOCKET连接*/ 
    { 
        fprintf(stderr, "Socket   Error:%s\a\n ",strerror(errno)); 
        exit(1); 
    } 

    /*   客户程序填充服务端的资料   */ 
    bzero(&server_addr,sizeof(server_addr)); 
    server_addr.sin_family=AF_INET; 
    server_addr.sin_port=htons(portnumber); 
    server_addr.sin_addr=*((struct   in_addr   *)host-> h_addr); 

    /*   客户程序发起连接请求   */ 
    if(connect(sockfd,(struct   sockaddr   *)(&server_addr),sizeof(struct   sockaddr))==-1)/*连接网站*/ 
    { 
        fprintf(stderr, "Connect   Error:%s\a\n ",strerror(errno)); 
        exit(1); 
    } 
    
    /* 打开报文文件 */
    strcpy( filename, argv[1]);
    fp = fopen( filename, "r");
    if (fp==NULL)
    {
        printf( "打开文件失败[%d]", filename);
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
    printf( "发送报文[%s]\n",   request);/*准备request，将要发送给主机*/ 

    /*发送请求*/ 
    send = write(sockfd,request,strlen(request));

    /*   连接成功了，接收http响应，response   */ 
    bzero(tmp,sizeof(tmp));
    bzero(buffer,sizeof(buffer));
    while((len=read(sockfd,buffer,1))==1)
    {
        i++;
        strcat(tmp,buffer);
    }
    printf("已经收到报文内容为:\n[%s]\n",tmp);
    fclose(fp);
    
    /*   结束通讯   */ 
    close(sockfd); 
    exit(0); 
} 

