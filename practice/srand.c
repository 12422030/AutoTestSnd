#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    char name[61]={0};
    int count=0;
    int num=0;
    while(count < 10)
    {   
        char tmp[21]={0};
        num = rand() % 10; 
        sprintf(tmp,"%d",num);
        strcat(name,tmp);
        printf("%d",num);
        count ++; 
    }
    return 0;
}
