#include<stdio.h>
#include<string.h>
int main()
{
    char sbuf[70]={"1111111111222"};
    char buf[70]={"    1111111111333     "};
    printf("%s\n",sbuf);
    printf("%s\n",buf);
    CutSpace(buf);
    printf("%s\n",sbuf);
    printf("%s\n",buf);
    if(strncmp(sbuf,buf,2)==0)
    {
        printf("equals\n");
    }
    else 
    { 
        printf("not equals\n");
    }
    return 0;
}
