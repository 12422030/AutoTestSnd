/**
 * Сдת����д
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
    /**�����ʼ��**/
    newname[l]=0;
    printf("�ַ�������Ϊ[%ld]-----ת��ǰ���ַ���Ϊ[%s]\n",l,s);       �ַ�������Ϊ[%ld
    printf("�ַ�������Ϊ[%ld]-----ת������ַ���Ϊ[%s]\n",l,newname); �ַ�������Ϊ[%ld
    return 0;
}
