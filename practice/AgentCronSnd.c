/**************************************************************************
Author        : lardbucket
Create Date   : 2008-09-04
Function      : AgentCronSnd 模拟前台给渠道发送交易
               
Company       : 大连同方软银
Modify  by    : zyw
Reason        :
变更信息： L0001 20170224 wangxm for 增加代理业务定时
***************************************************************************/

#include "stdio.h"
#include "string.h"
#define MAX_TRD   30  			/** 最多支持模拟交易数量 **/ 

static struct cron_prog
{
	char trcode[11] ;
	int (* prog)() ;
} ;

static struct cron_prog cron_prog[MAX_TRD] = 
{
} ;

static int search_prog(char *trcode, struct cron_prog *p) 
{
	int i ;

	if ( i == MAX_TRD ) return -1 ;

	return 0 ;
}
int main(int argc, char **argv) 
{
printf("zsr test 0\n");
	int ret ;
	char trcode[11];
	struct cron_prog p ;

	memset(trcode, 0x00, sizeof(trcode)) ;

printf("zsr test 1\n");

	if ( argc < 2 ) 
	{
printf("zsr test 2\n");
		return -1 ;
	}
printf("zsr test 3\n");
	strcpy(trcode, argv[1]) ;
printf("zsr test 4\n");
	if ( !strlen(trcode) ) 
	{
		return -1 ;
	}
	ret = search_prog(trcode, &p) ;
	if ( ret )
	{
		return -1;
	}

	ret = p.prog() ;
	if ( ret ) 
	{
		return -1 ;
	}
	return 0 ;
}
