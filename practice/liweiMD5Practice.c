#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    int i=0,InLen=0;
    char sOut[1024]={0x00};
    char pIn[1024]={0x00};
    strcpy(pIn,"liwei");

    LiweiMD5(sOut, pIn, strlen(pIn));

    printf("%s\n",sOut); 
    return 0;
}
