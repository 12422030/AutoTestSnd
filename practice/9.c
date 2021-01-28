#include<stdio.h>
#include<string.h>
int main()
{
    char sbuf[70]={"111111111122222222223333333333444444444411111111112222222222"};
    char liwei[70];
    printf("11111111111\n");
    sbuf[26] = 0x7A;
    sbuf[27] = 0x56;
    sbuf[28] = 0x4C;
    sbuf[29] = 0x00;
    sbuf[20] = 0x2F;
    sbuf[21] = 0x05;
    sbuf[22] = 0x87;
    sbuf[23] = 0x67;
    printf("22222222\n");
    int  i=45;
    printf("Ωÿ»°«∞%dŒª\n",i);
    memmove(liwei,sbuf,50);
    printf("-----%s-----\n",liwei);
    return 0;
}
