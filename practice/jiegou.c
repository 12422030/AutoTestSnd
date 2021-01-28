#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int array[3]={1,4,3};
    int *pa=array;
    //printf("%d%d%d\n",*pa,*(pa+1),*(pa+2));
    printf("%d\n",sizeof(int));
    printf("%d%d%d\n",pa,(pa+1),(pa+2));
    return 0;
}
