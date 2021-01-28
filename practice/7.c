#include<stdio.h>
#include<string.h>
int main()
{
    FILE *fp=NULL;
    char buf[23]={0x00};

    sprintf(buf,"22%s","                      "); 
    printf("[%s]\n",buf);
    return 0;
}
