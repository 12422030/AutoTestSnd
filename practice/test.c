#include<stdio.h>
void main()
{
    char strlen1[20];
    char strlen2[20];
    strcpy(strlen1,"123 1111111111");
    printf("[%s]\n",strlen1);
    strncpy(strlen2,strlen1,8);
    printf("[%s]\n",strlen2); 
}
