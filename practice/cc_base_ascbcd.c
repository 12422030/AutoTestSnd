#define EXTERN
/**type:对于二进制或者类似数据,因为要在前4bit付值,所以type>0 **/
void asc_to_bcd(bcd_buf,ascii_buf,conv_len,type)
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

/**conv_len为结果ASCII字符串长度**/
void bcd_to_asc(ascii_buf,bcd_buf,conv_len,type)
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
