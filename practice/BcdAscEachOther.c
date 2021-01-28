/**************************************
* FileName --- decBase64.c
* Author ----- icesky
* Date ------- 5月 12 2020
*
*
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char asc[100];
    char bcd[100];
    int  len;

    printf("请输入一行字符:\n");
    scanf("%s",bcd);
    printf("%d\n",sizeof(asc));
    printf("%d\n",sizeof(int));
    printf("%d\n",sizeof(long));
    printf("%d\n",sizeof(char));

    len=strlen(bcd);

    BCD_to_ASC(asc,bcd,len*2,0);
    printf("转换为ASC后的值为=[%s]\n",asc);

    memset(bcd,0x00,sizeof(bcd)) ;
    ASC_to_BCD(bcd,asc,strlen(asc),0);
    printf("转换为BCD后的值为=[%s]\n",bcd);

    return 0;
}

void ASC_to_BCD(bcd_buf,ascii_buf,conv_len,type)
unsigned char *bcd_buf,*ascii_buf,type;
int           conv_len;
{
	int  cnt;
	char ch,ch1;

	if( conv_len&0x01 && type )
		ch1 = 0;
	else
		ch1 = 0x55;

	for(cnt=0; cnt<conv_len; ascii_buf++,cnt++) 
    {
		if(*ascii_buf>='a')
		   ch=*ascii_buf-'a'+10;
		else if(*ascii_buf>='A')
		   ch=*ascii_buf-'A'+10;
		else if(*ascii_buf>='0')
		   ch=*ascii_buf-'0';
		else
		   ch=0;

		if(ch1==0x55)
		   ch1=ch;
		else 
        {
	 	   *bcd_buf++ = (ch1<<4)|ch;
			ch1=0x55;
		}
	}

	if(ch1!=0x55)
       *bcd_buf=ch1<<4;

	return;
}

/*******************#epcc_base_bcdasc#******************
 *函数功能: 转码bcd转为asc
******************************************************/
void BCD_to_ASC(ascii_buf,bcd_buf,conv_len,type)
unsigned char *ascii_buf,*bcd_buf,type;
int           conv_len;
{
	int cnt;

	if( conv_len&0x01 && type )
    {
		cnt=1;
		conv_len++;
	}
	else
		cnt=0;

	for( ; cnt<conv_len; cnt++,ascii_buf++)
    {
   	    *ascii_buf=((cnt&0x01)?(*bcd_buf++&0x0f):(*bcd_buf>>4));
		*ascii_buf+=((*ascii_buf>9)?('A'-10):'0');
	}

	return;
}
/********************#epcc_base_des-END#********************/
