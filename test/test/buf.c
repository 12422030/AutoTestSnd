#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char *p;
    int i,n;

    printf("请输入要申请的内存大小:\n");
    scanf("%d",&n);
    
    p=calloc(n+1,sizeof(char));
    if(p==NULL)
    {
      printf("申请内存不足!!,分配报文存储位置错误!");
      free(p);
      return -1;
    }
    printf("申请内存成功\n");
    for(i=0;i<n;i++)
    {
       p[i]=i+1;
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
