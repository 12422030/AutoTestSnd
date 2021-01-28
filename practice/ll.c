#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int *get_memory(int n);
int main()
{
    int n,i;
    char *p;
    printf("input n:");
    scanf("%d",&n);
    if((p=get_memory(n))==NULL)
    {
      return 0;
    }
    for(i=0;i<n;i++)
    {
      printf("%d",p[i]);
    }
    printf("\n");
    free(p);
    p=NULL;
    return 0;
}
/**calloc函数申请动态内存**/
int *get_memory(int n)
{
    char *p;
    int i;
    if((p=(char *)malloc(n * sizeof(char)))==NULL)//整型
    {   
       printf("malloc error\n");
    }   
    memset(p,0,n * sizeof(char));
    for(i=0;i<n;i++)
       p[i] = i+1;
}
