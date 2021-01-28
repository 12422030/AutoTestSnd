#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int a=10;
    int add=0;
    char *p=NULL;
    *p=a;
    printf("%d\n",&a);
    printf("%d\n",*p);
    return 0;
}
