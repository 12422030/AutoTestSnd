/*******************#BEGIN#******************
 *程 序 名: epcc_base_ascbcd
 *中 文 名: ascbcd转换
 *程序功能: ascbcd转换
 *程序作者: suitianmou
 *版 本 号: 1.0.0
 *创建日期: 2017.09.09
********************#END#********************/
#include <stdio.h>
#include <string.h>
/*******************#epcc_base_ascbcd#******************
 *函 数 名: epcc_base_ascbcd
 *函数功能: 二代支付转码asc转为bcd
 *函数作者: zyw
 *版 本 号: 1.0.0
 *创建日期: 20110330
******************************************************/
void epcc_base_ascbcd(bcd_buf,ascii_buf,conv_len,type)
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
 *函 数 名: epcc_base_bcdasc
 *函数功能: 二代支付转码bcd转为asc
 *函数作者: zyw
 *版 本 号: 1.0.0
 *创建日期: 20110330
******************************************************/
void epcc_base_bcdasc(ascii_buf,bcd_buf,conv_len,type)
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
