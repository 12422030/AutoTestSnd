#include<stdio.h>
void main()//主函数
{
    int a[10];
    int i,j,w;
    int n;
    printf("请输入长度:");
    scanf("%d",&n);
    printf("请输入[%d]个数字:\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i]<a[j])
            {
                w=a[i];
                a[i]=a[j];
                a[j]=w;
            }
        }
    }
    printf("排序后:\n");
    for(i=0;i<n;i++)
    {
        printf("%4d",a[i]);
    }
    printf("\n");
}
