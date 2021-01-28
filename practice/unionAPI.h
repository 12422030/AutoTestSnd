#ifndef _UNIONAPI_H_
#define _UNIONAPI_H_

#define LEN_OF_UNIONMSG 8192

// 交易信息
typedef struct
{
        char                    id[32+1];               // out,交易标识,8位日期+8位线程号+8位顺序号
        unsigned long           useTime;                //耗时
        char                    responseCode[6+1];      // out,响应码
        char                    responseRemark[128+1];  // out,响应描述
        unsigned int		lenOfLog;               // out,日志大小
        char                    log[20480+1];           // out,日志
        char                    serviceCode[5];        // 服务代码 added 2015-06-16
	int			writeLog_flag;		// 为1时每笔都写出，为0时缓冲，最终由UnionSetAPILogEnd写出缓冲到日志文件中
}TUnionTransInfo;
typedef TUnionTransInfo		*PUnionTransInfo;

/*
描述:  	释放API申请的资源，在进程退出时调用
参数: 	
	无

返回值: >=0 成功
	<0 错误码
*/
int UnionAPIFree();

/*
API开始
功能：
	设置请求服务码，设置日志缓存，加载API配置文件，初始化请求和响应buf。
参数：
	serviceCode[in]         服务码
	userInfo[in]            用户自定义信息，为空时api自动生成，建议传入交易流水号
	sysID[in]               外部系统ID，为空时，使用配置文件中的sysID
	appID[in]               应用系统ID，为空时，使用配置文件中的appID
返回：
	=0      成功
	<0      失败
*/
int UnionAPI_start(const char *serviceCode, const char *userInfo, const char *sysID, const char *appID);

/*
API服务结束
功能：
	结束API服务，并将缓存中的日志，写到日志文件中。
*/
int UnionAPI_end();

/*
设置API请求域
功能：
	设置API的请求域，请求域的值为字符串。
参数：
	fieldName[in]		请求域名称
	fieldValue[in]		请求域的值
	fieldLen[in]		请求域的值长度
返回：
	=0	成功
	<0	失败
*/
int UnionAPI_setString(const char *fieldName, const char *fieldValue, int fieldLen);

/*
设置API请求域
功能：
	设置API的请求域，请求域的值为整数。
参数：
	fieldName[in]		请求域名称
	fieldValue[in]		请求域的值
返回：
	=0	成功
	<0	失败
*/
int UnionAPI_setInteger(const char *fieldName, int fieldValue);

/*
读取API响应域
功能：
	读取API的响应域，响应域的值为字符串。
参数：
	fieldName[in]		响应域名称
	fieldValue[in]		响应域的值
	size[in]		缓存的大小
返回：
	>=0	响应域的值长度
	<0	失败
*/
int UnionAPI_getString(const char *fieldName, char *fieldValue, int size);

/*
读取API响应域
功能：
	读取API的响应域，响应域的值为整数。
参数：
	fieldName[in]		响应域名称
	fieldValue[in]		响应域的值
返回：
	=0	成功
	<0	失败
*/
int UnionAPI_getInteger(const char *fieldName, int *fieldValue);

/*
发送请求报文到平台，并接收响应报文
功能：
	发送API请求报文到平台，并接收响应报文
	如果后台返回错误码不为000000，则该函数返回后台响应错误码。
返回值：
	>=0	成功
	<0	失败
*/
int UnionAPI_send();

/*
获取最近一次服务报错的错误说明
功能：
	获取最近一次服务报错的错误说明，当错误说明长度超过缓存大小size时，截取缓存大小的错误说明。
	errRemark[out]		接收错误说明的缓存
	size[in]		接收错误说明的缓存大小
返回值：
	>=0	成功
	<0	失败
*/
int UnionAPI_getLastErrRemark(char *errRemark, int size);

/*
输出请求报文到缓存中
功能：
	输出请求报文到缓存中
	buf[out]	接收请求报文的缓存
	size[in]	接收请求报文的缓存大小
返回值：
	>=0	成功
	<0	失败
*/
int UnionAPI_printRequest(char *buf, int size);

/*
输出响应报文到缓存中
功能：
	输出响应报文到缓存中
	buf[out]	接收响应报文的缓存
	size[in]	接收响应报文的缓存大小
返回值：
	>=0	成功
	<0	失败
*/
int UnionAPI_printResponse(char *buf, int size);

/*
获取最近一次服务响应的userInfo（交易流水号）
功能：
	获取最近一次服务响应的userInfo（交易流水号）
	userInfo[out]		接收交易userInfo信息的缓存
	size[in]		接收交易userInfo信息的缓存大小
返回值：
	>=0     成功，交易流水号字符串长度
	<0      失败
*/
int UnionAPI_getUserInfo(char *userInfo, int size);

/*
加密SSL明文密码为密文密码
功能：
	plainText[in]		SSL明文密码，原始字符串
	cryptogram[out]		密文密码，扩展的16进制字符串
返回值：
	>=0	成功
	<0	失败
*/
int UnionAPI_encSSLPasswd(const char *plainText, char *cryptogram);

#endif 
