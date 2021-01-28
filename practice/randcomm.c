#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
int main()
{
    int i=0,feno=0;
    char menu[7];
    int a[10][10]={'1','2','3','4','5','6'};
    memset(menu,0x00,sizeof(menu));
    srand((unsigned)time(NULL));
    for(i=0;i<6;i++)
    {
        menu[i]='0'+rand()%9;
        if(i==5)
        {
            printf("ֵΪ---%s---\n",menu);
        }
    }
    return 0;
}
