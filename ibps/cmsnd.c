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

#define TIMEOUT 120

int main(int argc ,char *argv[])
{
   int ret=0;
   int tgsockid=0;
   int pkglen;
   int pkglen2;
   char tmpstr[10];
   char tmpsts[10];
   char tmpsts1[10];
   char tgip[20];
   char filename[100];
   char buffer[1024*4];
   char sbuf[1024*4];
   char sbuf1[10];
   char rbuf[1024*4];
   long tgport;
   FILE *fp;

   memset(tmpstr, 0x00, sizeof(tmpstr));
   memset(tmpsts, 0x00, sizeof(tmpsts));
   memset(tmpsts1, 0x00, sizeof(tmpsts1));
   memset(rbuf, 0x00, sizeof(rbuf));
   memset(sbuf, 0x00, sizeof(sbuf));
   memset(sbuf1, 0x00, sizeof(sbuf));

   //strcpy(tgip,"127.0.0.1");
   //strcpy(tgip,"16.16.22.108");
   //strcpy(tgip,"16.16.17.123");
   strcpy(tgip,"16.16.19.59");
   tgport=7070;
   printf("\nĿ������IP[%s][%ld]\n",tgip, tgport);

   sprintf( filename,"%s/src/test/ibps/msg/%s",getenv("HOME"),argv[1]);
   fp = fopen( filename, "r");
   if (fp==NULL)
   {
       printf( "���ļ�ʧ��[%s]\n", filename);
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
   printf("�����ļ�[%s]\n",sbuf);
   printf("\n��ʼ��������\n");
   tgsockid = TcpCliOpen(tgip,  tgport);
   if (tgsockid < 0)
   {
     return -3; 
   }

  /*-------1������8λ����--------*/
   pkglen = strlen(sbuf)+8;

   sprintf(tmpstr, "%08d", pkglen);
   printf("\n����ͷ[%s]\n",tmpstr);
   ret = TcpSend(tgsockid, tmpstr, 8, TIMEOUT);
   if (ret)
   {
      return -5;
   }

    /*-------  2������8λ����ͷ  --------*/
   sprintf( sbuf1,"1014%s",argv[1]);
    ret = TcpSend(tgsockid, sbuf1,8,TIMEOUT);
    if (ret) 
    { 
         return -6; 
    }

    /*-------  3������ָ�����ȵı�����  --------*/
    ret = TcpSend(tgsockid, sbuf,pkglen,TIMEOUT);
    if (ret) 
    { 
         return -10; 
    }

    printf("\n������[%s]\n",sbuf);

  /**Ϊ��ֹ���ظ�����ֱ�ӵȴ����ܷ�����Ϣ**/


  /*------ �Ƚ���8λ���� ------*/
  ret = TcpRecv(tgsockid, tmpsts1, 8, TIMEOUT);
  if (ret)
  {
    return -5;
  }
  /*------ ����8λ����ͷ ------*/
  ret = TcpRecv(tgsockid, tmpsts, 8, TIMEOUT);
  if (ret)
  {
    return -5;
  }
  /*------ �������İ����ӵ����� ------*/
  pkglen2=atol(tmpsts1);
  ret = TcpRecv(tgsockid, rbuf, pkglen2-8, TIMEOUT);
  if (ret)
  {
     return -10;
  }
   printf("\n���հ���[%s]\n",rbuf);

   close(tgsockid); 
   return 0;
}