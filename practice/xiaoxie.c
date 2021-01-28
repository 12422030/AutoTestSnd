/**
 * 小写转换大写
**/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char s[21]="qwertyASDFG";
    char newname[21];
    int i,l,c,max,min;
    l=strlen(s);
    for(i=0;i<l;i++)
    {
      if(isupper(s[i]))
      {
          max++;
          printf("原字符串中有大写字母!\n");
          c=tolower(s[i]);
      }
      else
      {
          min++;
          printf("原字符串中有小写字母!\n");
          c=s[i];
      }
          newname[i]=c;
    }
    /**必须初始化**/
    newname[l]=0;
    printf("字符串长度为[%ld]-----转换前的字符串为[%s]\n",l,s);
    printf("字符串长度为[%ld]-----转换后的字符串为[%s]\n",l,newname);
    printf("大写字母有[%d]个-----小写字母有[%d]个\n",max,min);
    return 0;
}
