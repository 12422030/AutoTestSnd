#include<stdio.h>
int main()
{
    int i,N;
    int matrix[4];
    /**
    printf("输入数组长度:\n");
    scanf("%d",&N);
    **/
    printf("输入排序的元素个数:\n");
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
      printf("第[%d]次输入的值为:",i+1);
      scanf("%d",&matrix[i]);
    }
    bubbleSort(matrix,N);
    printf("排序后的值为:\n");
    for(i=0;i<N;i++)
    {
      printf("%-3d",matrix[i]);
    }

    return 0;
}

void bubbleSort(int *arr,int n)
{
    int m,i,j;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1-i;j++)
            if(arr[j]>arr[j+1])
            {
                m=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=m;
            }
}
