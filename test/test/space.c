#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    long len=10;
    char *p=NULL;
    char *liwei=NULL;
    //char *buf=NULL;
    long lXmlLen=0;
    char *pXmlBeg=NULL;
    char *pXmlEnd=NULL;
    char buf[]="abcdBdsE";
    char s[]="pwpwpep121212epepepepebcdefg";

    p=(char *)calloc(len+1,sizeof(char));
    if(p==NULL)
    {
        printf("…Í«Îƒ⁄¥Ê ß∞‹!");
        return -1;
    }
    memcpy(p,s+7,len);
    printf("%s\n",p);

    pXmlBeg = strstr(buf,"B");
    if(pXmlBeg==NULL)
    {
        printf("…Í«Î¥ÌŒÛ1!");
        return -2;
    }
    pXmlEnd=strstr(buf,"E");
    if(pXmlEnd==NULL)
    {
        printf("…Í«Î¥ÌŒÛ2!");
        return -3;
    }
    lXmlLen=pXmlEnd-pXmlBeg+1;
    printf("%d\n",pXmlEnd);
    printf("%d\n",pXmlBeg);
    printf("%d\n",lXmlLen);
    
    liwei=(char *)calloc(lXmlLen+1,sizeof(char));
    if(liwei==NULL)
    {   
        printf("…Í«Îƒ⁄¥Ê ß∞‹!");
        return -1; 
    }
    memcpy(liwei,buf+lXmlLen,lXmlLen);
    printf("%s\n",liwei);
    return 0;
}
