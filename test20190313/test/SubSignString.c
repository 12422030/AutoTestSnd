/*******************************************************
 * 公    司: 大连同方软银科技有限公司
 * 程 序 名: SubSignString.c
 * 程序功能: 根据指定分隔符截取子字符串
 * 输入参数:
 *           num     指定获取域
 *           sign    指定拆分分隔符
 *           buf     要拆分的字符串缓冲区
 * 输出参数:
 *           tag     返回子字符串
 * 返 回 值:
 *           去掉后后的字符串
 * 作    者: zyw
 * 开发日期: 2008/10
 * 修 改 人:
 * 修改日期:
*******************************************************/

#include "string.h"
#include "stdio.h"

int SubSignString(int num, char sign, char *buf, char *tag)
{
    char *p, *q;
    int i;

    q = buf;

    num--;

    while(num != 0)
    {
      if (*q == sign) num--;
      q++;
	  if(*q=='\0') return 1;	
    }

    p = q;
    i = 0;
    while(*q != sign)
    {
	  if(*q=='\0') return 1;	
      q++;
      i++;
    }
    strncpy(tag, p, i);
    tag[i] = 0;

    return 0;

}

