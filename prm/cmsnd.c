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
    char temp[10];
    char tgip[20];
    char filename[100];
    char buffer[1024];
    char sbuf[1024];
    char rbuf[1024];
    char sPkgHead[7];
    long tgport;
    FILE *fp;

    memset(tmpstr, 0x00, sizeof(tmpstr));
    memset(tmpsts, 0x00, sizeof(tmpsts));
    memset(rbuf, 0x00, sizeof(rbuf));
    memset(sbuf, 0x00, sizeof(sbuf));

    strcpy(tgip,"16.16.17.123");
    tgport=9970;
    printf("\nĿ������IP[%s][%ld]\n",tgip, tgport);

    sprintf( filename,"%s/src/test/prm/msg/%s",getenv("HOME"),argv[1]);
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

    /*-------3����10λ����--------*/
    pkglen = strlen(sbuf);

    sprintf(tmpstr, "%10d", pkglen-1);
    printf("\n����ͷ[%s]\n",tmpstr);
    ret = TcpSend(tgsockid, tmpstr, 10, TIMEOUT);
    if (ret)
    {   
        return -5; 
    } 
     
    /*-------�̶�2λ��4λ������-------*/
    sprintf(sPkgHead,"  ");
    strcat(sPkgHead,argv[1]);

    ret = TcpSend(tgsockid, sPkgHead, 6, TIMEOUT);
    if (ret)
    {
       return -10;
    }
    printf("sPkgHead = [%s]", sPkgHead);
   
    
    /*-------4����ָ�����ȵı�����  --------*/
    ret = TcpSend(tgsockid, sbuf, pkglen, TIMEOUT);
    if (ret) 
    {   
        return -10; 
    }

    printf("\n������[%s]\n",sbuf);

    /*------ �Ƚ���8λ���� ------*/
    ret = TcpRecv(tgsockid, tmpsts, 8, TIMEOUT);
    if (ret)
    {
        printf("���ر�[%d][%s]\n", ret, strerror(errno));
        return -5;
    }

    pkglen = atol(tmpsts);

    /*------ �������İ����ӵ����� ------*/
    ret = TcpRecv(tgsockid, rbuf, pkglen, TIMEOUT);
    if (ret)
    {
        printf("���ر�[%d][%s]\n", ret, strerror(errno));
        return -10;
    }
    printf("\n���հ���[%s]\n",rbuf);

    close(tgsockid); 
    return 0;
}