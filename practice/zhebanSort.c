#include<stdio.h>
int search(int A[],int n,int key)
{
    int low=0,high=n-1,mid;
    if(A[low]==key)
        return low;
    else if(A[high]==key)
        return high;
    else
    {
        while(low<=high)
        {
            mid=(low+high)/2;
            if(A[mid]==key)
                return mid; //查找成功，返回mid 
            if(key>A[mid])
                low=mid+1;  //在后半序列中查找 
            else
                high=mid-1; //在前半序列中查找 
        }
    }
    return -1;  //查找失败，返回-1 
}
main()
{
    int A[10]={2,3,5,7,9,11,12,15,19,22},i,n,addr;
    printf("A[10]:");
    for(i=0;i<10;i++)
        printf("%d ",A[i]); //显示数组A的内容
    printf("\n输入要查找元素：");
    scanf("%d",&n);     //输入待查找元素
    addr=search(A,10,n);        //折半查找返回该元素在数组中的下标
    if(addr!=-1)        //查找成功
        printf("%d是数组中的第%d个元素\n",n,addr+1);
    else        //查找失败
        printf("A数组中无%d",n);
    return 0;
}
