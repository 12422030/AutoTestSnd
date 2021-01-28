#include "kernel/syspub.h"

#define SPECCHAR   " \t\n\r"  /*特殊字符*/ 

char *strtrim(char *str);
char *spchtrim(char *str);
void TcpCliClose(int sock);

char host_ip[21];
int  host_port = 0;
int  sock_id = 0;

int main(int argc, char *argv[])
{
   char pkg_id[5];
   char pkg_buf[2049];
   int  ret = 0;

   if (argc < 2)
   {
      printf("\n cli 交易代码\n");
      return -1;
   }

   ret = GetTestConfig(host_ip, &host_port);
   if (ret != 0)
   {
      printf("\n 读取配置文件错误=[%d]\n", ret);
      return -2;
   }

   printf("\n host_ip=[%s]", host_ip);
   printf("\n host_port=[%d]", host_port);
   printf("\n");
   
   strcpy(pkg_id, argv[1]);

   /*发送报文*/
   ret = TestTcpSend(pkg_id);
   if (ret)
   {
      printf("\nCall TestTcpSend Error=[%d][%s]!", ret, pkg_id);
      return ret;
   }

   /*接收报文*/
   memset(pkg_buf, 0x00, sizeof(pkg_buf));
   ret = TestTcpRecv(pkg_id);
   if (ret)
   {
      printf("\nCall HtcTcpRecv Error=[%d]!", ret);
      return ret;
   }

   printf("\n<---调用[%s]进行通讯处理完毕!\n\n", argv[1]);

   printf("\n");
   
   return 0;
}

int GetTestConfig(char *ip, int *port)
{
    char line[201];
    char tmpstr[201];
    char *p = NULL;
    char *q = NULL;
    FILE *fp = NULL;

    fp = fopen("./test.cfg", "r");
    if (fp == NULL)
    {
       printf("\n fopen test.cfg Error!");
       return -5;
    }

    memset(line, 0x00, sizeof(line)); 

    if (fgets(line, 200, fp) == NULL)
    {
       printf("\nREAD test.cfg FILE ERROR!");
       fclose(fp);
       return -10;
    }
   
    while(!feof(fp))
    {
       strtrim(line);
       spchtrim(line);

       p = line;

       q = strchr(p, '=');
       if (q == NULL)
       {
          printf("\ntest.cfg Format ERROR!");
          fclose(fp);
          return -15;
       }
       else if (q != NULL)
       {
          memset(tmpstr, 0x00, sizeof(tmpstr));
          memcpy(tmpstr, p, q-p);
          strtrim(tmpstr);
          if (strcmp(tmpstr, "HOST_IP") == 0)
          {
             memset(tmpstr, 0x00, sizeof(tmpstr));
             strcpy(tmpstr, q+1);
             strtrim(tmpstr);
             strcpy(ip, tmpstr);
          }
          else if (strcmp(tmpstr, "HOST_PORT") == 0)
          {
             memset(tmpstr, 0x00, sizeof(tmpstr));
             strcpy(tmpstr, q+1);
             strtrim(tmpstr);
             *port = atoi(tmpstr);
          }
       }

       memset(line, 0x00, sizeof(line));
       fgets(line, 200, fp);
    }

    fclose(fp);

    return 0;

}

char *strtrim(char *str)
{
   int i=0;
   int b1=0, e1=0;

   if (strlen(str) == 0) return str;

   if (str) 
   {
      for(i = 0; str[i] == ' '; i++);

      b1 = i;

      for(i = strlen(str) - 1; i >= b1 && str[i] == ' '; i--);

      e1 = i;

      if (e1 >= b1)
         memmove(str, str+b1, e1-b1+1);

      str[e1-b1+1] = 0;
      return str;
   }
   else return str;
}

int IsSpecChar(char ch, char *specChar)
{
   int len = 0;
   while (*(specChar + len))
   {
     if (ch == *(specChar + len))
        return 1;
     len ++;
   }
   return 0;
}

char *spchtrim(char *str)
{
    int i = 0;

    if (str)
    {
       i  = strlen(str) - 1;
       if (i == -1) return str;

       while(IsSpecChar(*(str + i), SPECCHAR) && i >= 0) i--;

       if (i == -1) return str;
       else
       {
          *(str + i + 1) = 0;
          return str;
       }
    }
    else
    {
       return str;
    }
}

int TestTcpSend(char *pkg_id)
{
    char slen[9];
    char filepath[201];
    char *fileBuf;
    char *ptr;
    char pkghead[17];
    struct stat statBuf;
    ssize_t iodes;
    int n = 0;
    int left = 0;
    int bufLen = 0;
    int ret = 0;

    sprintf(filepath, "./%s.xml", pkg_id);
    if ((stat(filepath, &statBuf)) != 0)
    {
       printf("\n 读取XML报文长度失败=[%s][%s]", filepath, strerror(errno));
       return -5;
    }

    iodes = open(filepath, O_RDONLY, 0);
    if (iodes == -1)
    {
       printf("\n 读取XML报文失败=[%s][%s]", filepath, strerror(errno));
       return -10;
    }

    fileBuf = (char *)malloc(statBuf.st_size + 1);
    if (fileBuf == NULL)
    {
       printf("\n 动态分配内存失败size=[%d]", statBuf.st_size);
       return -12;
    }

    memset(fileBuf, 0x00, statBuf.st_size + 1);
    left = statBuf.st_size;
    ptr = fileBuf;

    while(left > 0)
    {
       n = read(iodes, ptr, left);
       if (n == 0) break;
       if (n < 0)
       {
          if (errno == EINTR) continue;
          else
          {
             printf("\n读文件失败[%s]", strerror(errno));
             free(fileBuf);
             return -10;
          }
       }
       ptr += n;
       left -= n;
    }
    close(iodes);

    memset(pkghead, 0x00, sizeof(pkghead));

    sprintf(pkghead, "%08d", statBuf.st_size+8);
    sprintf(pkghead+8, "1014%s", pkg_id);

    printf("\n 发送报文头=[%s]\n", pkghead);
    printf("\n 发送报文体=[%s]\n", fileBuf);

    sock_id = TcpCliOpen(host_ip,  host_port);
    if (sock_id < 0)
    {
       printf("\n Call TcpCliOpen Error=[%d]", sock_id);
       free(fileBuf);
       return sock_id;
    }

    ret = TcpCliSend(sock_id, pkghead, 16, 60);
    if (ret != 0)
    {
       printf("\n Call TcpCliSend pkg_len Error=[%d]", ret);
       free(fileBuf);
       return ret;
    }

    ret = TcpCliSend(sock_id, fileBuf, statBuf.st_size, 60);
    if (ret != 0)
    {
       printf("\n Call TcpCliSend pkg_buf Error=[%d]", ret);
       free(fileBuf);
       return ret;
    }

    free(fileBuf);

    return 0;
}

int TestTcpRecv(char *pkg_id)
{
    char slen[9];
    char *pkgbuf = NULL;
    char filepath[101];
    FILE *fp = NULL;
    int  len = 0;
    int  ret = 0;

    memset(slen, 0x00, sizeof(slen));

    ret = TcpCliRecv(sock_id, slen, 8, 60);
    if (ret != 0)
    {
       printf("\n Call TcpCliRecv pkg_len Error=[%d]", ret);
       return ret;
    }

    len = atoi(slen);

    printf("\n接收报文长度=[%d][%s]\n", len, slen);

    pkgbuf = (char *)malloc(len + 1);
    if (pkgbuf == NULL)
    {
       printf("\n 分配内存失败=[%d]", len);
       return ret;
    }

    memset(pkgbuf, 0x00, len+1);

    ret = TcpCliRecv(sock_id, pkgbuf, len, 60);
    if (ret != 0)
    {
       printf("\n Call TcpCliRecv pkgbuf Error=[%d]", ret);
       free(pkgbuf);
       return ret;
    }

    TcpCliClose(sock_id);

    printf("\n接收报文=[%s]\n", pkgbuf);

    sprintf(filepath, "./%s.recv", pkg_id);
    fp = fopen(filepath, "w");
    if (fp == NULL)
    {
       printf("\n 打开文件失败=[%s][%s]", filepath, strerror(errno));
       free(pkgbuf);
       return -10;
    }

    fwrite(pkgbuf, 1, len, fp);
    fclose(fp);

    free(pkgbuf);

    return 0;
}

int TcpCliOpen(char *ip,  int port)
{
   struct sockaddr_in sin;
   int sock;

   memset(&sin, 0x00, sizeof(sin));

   sin.sin_family = AF_INET;
   sin.sin_port = htons(port);
   sin.sin_addr.s_addr = inet_addr(ip);

   if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
   {
      printf("\nsocket : %s\n", strerror(errno));
      return -5;
   }

   if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
   {
      printf("\nconnect : %s\n", strerror(errno));
      close(sock);
      return -10;
   }

   return sock;

}

void TcpCliClose(int sock)
{  
   close(sock);

   return;

}

int TcpCliSend(int sock, char *msgbuf, int len, int timeout)
{
   int    ret;
   int    nfds = 1;
   struct timeval tv;
   fd_set writefds;
   long   lStartTime, lCurrentTime;
   int    iSize = 0;
        
   lStartTime = lCurrentTime = 0;
        
   /* 设置超时时间 */
   if (timeout <= 0)
   {
      tv.tv_sec  = 0;
      tv.tv_usec = 0;
   }
   else
   {
      tv.tv_sec = timeout;
      tv.tv_usec = 0;
   }

   time(&lStartTime);

   /* 设置nfds = 1, 检查当前sock */
   nfds = sock + 1;

   /* 初始化writefds, 并将当前sock加入 */
   FD_ZERO(&writefds);
   FD_SET(sock, &writefds);

   ret = select(nfds, NULL, &writefds, NULL, &tv);
   if (ret < 0)
   {
      printf("\nselect : %s", strerror(errno));
      return ret;
   }
   else if (ret == 0)  /* 超时时间到 */
   {
      printf("\nselect : 超时时间到");
      return -5;
   }
	
   /* 异常错误 */
   if (!FD_ISSET(sock, &writefds))
   {
      printf("\nselect : 异常错误");
      return -10;
   }
	
   iSize = len;
   while(iSize > 0)
   {
      if (timeout > 0)
      {
         time(&lCurrentTime);
         if (lCurrentTime - lStartTime > timeout)
         {
            printf("\nFile: %s Line: %d write timeout!\n", __FILE__,__LINE__);
            return -15;
         } 
      }
      		
      ret = write(sock, msgbuf, iSize);
      if (ret <= 0)
      {
         printf("\nwrite : %s", strerror(errno));
         return -20;
      }
      else
      {
         iSize -= ret;
         msgbuf += ret;
      }
   }
	
   return 0;

}

int TcpCliRecv(int sock, char *msgbuf, int len, int timeout)
{
   int ret;
   int i;
   int nfds = 1;
   struct timeval tv;
   fd_set readfds;
        
   int iSize = 0;
   long lStartTime, lCurrentTime;
        
   lStartTime = lCurrentTime = 0;
        
   /* 设置超时时间 */
   if (timeout <= 0)
   {
      tv.tv_sec  = 0;
      tv.tv_usec = 0;
   }
   else
   {
      tv.tv_sec = timeout;
      tv.tv_usec = 0;
   }

   /* 设置nfds = 1， 检查当前sock */
   nfds = sock + 1;

   /* 初始化readfds, 并将当前sock加入 */
   FD_ZERO(&readfds);
   FD_SET(sock, &readfds);
        
   time(&lStartTime);
        
   ret = select(nfds, &readfds, NULL, NULL, &tv);
   if (ret < 0)
   {
      printf("\nselect : %s\n", strerror(errno));
      return ret;
   }
   else if (ret == 0)  /* 超时时间到 */
   {
      printf("\nselect : 超时时间到\n");
      return -5;
   }
	
   /* 异常错误 */
   if (!FD_ISSET(sock, &readfds))
   {
      printf("\nselect : 异常错误\n");
      return -10;
   }

   /* 开始接收数据包 */
   iSize = len ;
   while(iSize > 0)
   {
      if (timeout > 0)
      {
         time(&lCurrentTime);
         if (lCurrentTime - lStartTime > timeout)
         {
            printf("\nFile: %s Line: %d read timeout!\n", __FILE__,__LINE__);
            return -15;
         } 
      }
      		
      ret = read(sock, msgbuf, iSize);
      if (ret < 0)
      {
         printf("\nFile: %s Line: %d read error!\n", __FILE__,__LINE__);
         return -20;
      }
      else if (ret == 0)
      {
         printf("\nFile: %s Line: %d diconnect by other peer!",__FILE__,__LINE__);
         return -25;
      }
      else
      {
         iSize -= ret;
         msgbuf += ret;
      }        	
   }
        
   return 0;
	
}

