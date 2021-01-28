/*******************************************************
* 公    司: 大连同方软银科技有限公司
* 程 序 名: SSLBase64Decode.c
* 程序功能: BASE64码转换成ASC码制
* 输入参数:
*           in			需要转换的ASC码数据
*           inl			需要转换的ASC码数据长度
*           out			转换后的BASC64码数据
*           outl		转换后的BASC64码数据长度
			建议out变量的长度=in变量的长度
* 输出参数:
* 返 回 值:
			0		成功
			!0		失败
* 作    者: zyw
* 开发日期: 2011/2
* 修 改 人:
* 修改日期:
*******************************************************/

#include <stdio.h>
#include <string.h>
int SSLBase64Decode(char *in,int inl,char *out,int *outl)
{
		EVP_ENCODE_CTX	dctx;
		int		total=0,outlen=0,ret=0;

		EVP_DecodeInit(&dctx);

		outlen=0;
		ret=EVP_DecodeUpdate(&dctx,out,&outlen,in,inl);
		if(ret<0)
		{
			printf("Call EVP_DecodeUpdate ERROR");
			return -1;
		}
		total+=outlen;

		outlen=0;
		ret=EVP_DecodeFinal(&dctx,out,&outlen);
		total+=outlen;

		*outl=total;

		return 0;
}
