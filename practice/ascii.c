#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char c;
    char liwei[2]="e";
    int num=0;
    printf("%d",sizeof(short int));
    printf("%d",sizeof(int));
    printf("%d",sizeof(long));
    char *p;
    p=liwei;
    while(c = *p++)
    {   
        num <<= 4;
        printf("---[%d]--\n",num);
        if(c >= '0' && c <= '9')
        {  
            num += c - '0';
            printf("%d\n",num); 
            continue;
        }
        if(c >= 'a' && c <= 'f')
        {   
            num += c - 'a' + 10; 
            printf("%d\n",num);
            continue;
        }   
        if(c >= 'A' && c <= 'F')
        {   
            num += c - 'A' + 10; 
            printf("%d\n",num);
            continue;
        }   
    }    
    return 0; 
}
