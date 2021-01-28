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

#define TIMEOUT 60

int main(int argc ,char *argv[])
{
   int ret=0;
   int tgsockid=0;
   int pkglen;
   char tmpstr[10];
   char tmpsts[10];
   char tgip[20];
   char filename[100];
   char buffer[1024];
   char sbuf[1024];
   char rbuf[1024];
   long tgport;
   FILE *fp;

   memset(tmpstr, 0x00, sizeof(tmpstr));
   memset(tmpsts, 0x00, sizeof(tmpsts));
   memset(rbuf, 0x00, sizeof(rbuf));
   memset(sbuf, 0x00, sizeof(sbuf));

   strcpy(tgip,"127.0.0.1");
   tgport=9544;
   printf("\n目标渠道IP[%s][%ld]\n",tgip, tgport);

   sprintf( filename,"%s/src/test/vtmbank/lz/msg/%s",getenv("HOME"),argv[1]);
   fp = fopen( filename, "r");
   if (fp==NULL)
   {
       printf( "打开文件失败[%s]\n", filename);
       return -1;
   }

   while(1)
   {
       bzero( buffer, sizeof(buffer));
       fgets( buffer, 1024, fp);
       strcat( sbuf, buffer);
       if( feof(fp))
       {
           break;
       }
   }
   fclose(fp);
   strtrim(sbuf);
   printf("读出文件[%s]\n",sbuf);
   printf("\n开始建立连接\n");
   tgsockid = TcpCliOpen(tgip,  tgport);
   if (tgsockid < 0)
   {
     return -3; 
   }

  /*-------1、发送8位包长--------*/
   pkglen = strlen(sbuf);

   sprintf(tmpstr, "%08d", pkglen);
   printf("\n发包头[%s]\n",tmpstr);
   ret = TcpSend(tgsockid, tmpstr, 8, TIMEOUT);
   if (ret)
   {
      return -5;
   }

    /*-------  2、发送指定长度的报文体  --------*/
    ret = TcpSend(tgsockid, sbuf,pkglen,TIMEOUT);
    if (ret) 
    { 
         return -10; 
    }

    printf("\n发包体[%s]\n",sbuf);

  /**为防止发重复这里直接等待接受返回信息**/

  /*------ 先接收8位包长 ------*/
  ret = TcpRecv(tgsockid, tmpsts, 8, TIMEOUT);
  if (ret)
  {
    return -5;
  }

  /*------ 按发来的包长接到包体 ------*/
  ret = TcpRecv(tgsockid, rbuf, pkglen, TIMEOUT);
  if (ret)
  {
     return -10;
  }
   printf("\n接收包体[%s]\n",rbuf);

   close(tgsockid); 
   return 0;
}
