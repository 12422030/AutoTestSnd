/**
 * 小写转换大写
**/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char s[21]="wqwqwqwq";
    char newname[21];
    int i,l,c;
    l=strlen(s);
    for(i=0;i<l;i++)
    {
      if(islower(s[i]))
      {
          c=toupper(s[i]);
      }
      newname[i]=c;
    }
    /**必须初始化**/
    newname[l]=0;
    printf("字符串长度为[%ld]-----转换前的字符串为[%s]\n",l,s);  
    printf("字符串长度为[%ld]-----转换后的字符串为[%s]\n",l,newname);
    return 0;
}
