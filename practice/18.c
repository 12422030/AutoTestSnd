#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int   len=100;
    char  *liwei=NULL;
    char  test[101]={"1111"};
    liwei =(char *)malloc(sizeof(len)+1);
    if(liwei==NULL)
    {
        printf( "1111\n" );
    }
        printf( "2222\n" );
    
    strcpy(liwei,test);
    printf("liwei=[%s]\n",liwei);
    printf("liwei=[%10s]\n",liwei);
    printf("liwei=[%-34s]\n",liwei);
    printf("liwei=[%.10s]\n",liwei);
    return 0;
}
