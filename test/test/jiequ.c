#include<stdio.h>
#include <string.h>
main()
{
   char *s="GoldenGlobalView";
   char d[20];
    
   memcpy(d,s+3,3);
   d[10]=0;
   printf("----------->%s\n<------------",d);

   getchar();
   return 0;
}
