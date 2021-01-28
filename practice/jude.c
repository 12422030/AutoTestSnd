#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    char s[10]="123456789";
    char d[2]={0x00};
    char e[3]={0x00};
    char f[4]={0x00};
 
    memcpy(d,s,1);
    memcpy(e,s+1,2);
    memcpy(f,s+3,3);
    printf("%s\n",d);
    printf("%s\n",e);
    printf("%s\n",f);

    return 0;
}
