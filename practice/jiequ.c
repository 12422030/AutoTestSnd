#include<stdio.h>
#include <string.h>
main()
{
   char s[21]="woca00001swess";
   char d[21]={0x00};
   int i=strlen(s);
   int j=0;

   /**memcpy(d,s,9);**/
   strncpy(d,s,11);
   for(j=0;j<=i;j++)
   {
       printf("----------->%c\n<------------",d[j]);
   }
   getchar();
   return 0;
}
