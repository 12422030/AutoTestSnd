#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main()
{
    struct timeval before_usleep;
    struct timeval after_usleep;
    
    FILE * fp= NULL;
    char buff[121];
    char a[4];
    char b[4];
    char c[4];
    
    gettimeofday(&before_usleep,NULL);
    fp = fopen( "/app/user/liwei/1.txt","r");
    if(fp==NULL)
    {  
       printf("no file\n"); 
       return -5;
    }
    while(!feof(fp))
    {
      memset( buff, 0x00, sizeof(buff)); 
      fgets(buff,120,fp);
      memcpy(a,buff,1);
      memcpy(b,buff+1,1);
      memcpy(c,buff+2,1);
    }
    
    gettimeofday(&after_usleep,NULL);
    
    printf("%d,\n%d\n",before_usleep.tv_usec,after_usleep.tv_usec);
    printf("used time =%dms\n",after_usleep.tv_usec-before_usleep.tv_usec);

}
