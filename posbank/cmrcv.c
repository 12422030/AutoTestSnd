#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>


/***守护进程***/
main(int argc,char *argv[])
{
	pid_t	pid ;
	char	name[21] ;
    /***创建进程***/
	if ( ( pid=fork() ) < 0  ) 
	{
		printf("创建进程失败\n") ;
		return 1 ;
	}
	else if ( pid>0 )/*终止父进程*/
	{
		exit(0) ;
	}
	if ( setsid() == -1) /*创建了一个新的进程组*/
	{
	   printf("创建进程对话期错误\n") ;
	   return 1 ;
	}

	sigset(SIGHUP,SIG_IGN) ;/*忽略用户退出时信号*SIG_DFL恢复*/
	sigset(SIGCHLD,SIG_IGN) ;/*忽略子进程结束时信号*/
	
	/** 可以用signal会在收到该信号以后，会SIG_DFL该信号.sigset则不会*/

    /*修改文件路径*/
    /*
	sprintf(name,"/home/asxip/src/agbs/gspy/test/msg") ;
	chdir( name );
    */
	/*清除文件掩码*/
	umask( 0 );
	errno=0 ;

	if (wys_rcv(argc,argv) )
	{
		printf("程序执行失败\n") ;
	}
	else
	{
		printf("程序执行成功\n") ;
    }
	return 0 ;
	/*应该在setsid之后,再次fork第二子进程，将第一子进程终止*/
}

/***  监听处理程序 ***/
int	wys_rcv(int argc, char **argv)
{
	int	newsock;
	int sock; 
	int i;
	int	optvar = 0;
	int optlen = 0;
	int ret = 0;
	unsigned short	portnum;
	char msg[25600];
	pid_t child_pid;
	socklen_t namelen;
	struct sockaddr_in sin ;
    char servicename[1024]; 
    char filename[1024];
    char buffer[10240];
    char tmp[10240];
    FILE * fp;

    char buff[102400];
    memset(buff, 0x00, sizeof(buff));

    if (argc != 2)
    {
        printf("\n 用法说明: %s 端口号\n\n", argv[0]);
        exit(-1);
    }

	/*判断端口要大于1024*/
	for (i = 0; i < strlen(argv[1]); i++) 
	{
		if (!isdigit(argv[1][i])) /*字符是否是数字*/
		{
			printf("\n 用法说明: %s 端口号\n\n", argv[0]);
			exit(-1);
		}
	}
	
	portnum = atoi(argv[1]);
	
	if (portnum <= 1024) 
	{
		printf("\n端口号[%s]小于1024!\n", argv[1]);
		exit(-1);
	}

    /**建立流式socket**/
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)/*IPPROTO_TCP可直接置为0*/
	{
		perror("socket");
		printf("--->%s,%d建立sock失败!!!", __FILE__, __LINE__);
		exit(1);
	}

	/*--服务重新启动时立即先将原来绑定的端口标记为未用，sock的bug--*/
	optvar = 1;
	optlen = sizeof(optvar);

	ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) & optvar, optlen);
	if (ret == -1) 
	{
		printf("%s: setsockopt error!", argv[0]);
		exit(-1);
	}

	bzero((char * )&sin, sizeof(sin));
	sin.sin_family = AF_INET;                /*Internet地址族AF_xxx*/
	sin.sin_port = htons(portnum);           /*端口号*如果为0则bind帮你选择一个端口*/
	sin.sin_addr.s_addr = htonl(INADDR_ANY); /*Internet地址*INADDR_ANY(0)为本机地址*/
	bzero(&(sin.sin_zero), 8);               /*结构体剩余部分数据设为0*/
    
    /**绑定端口**/
	if (bind(sock, (struct sockaddr * ) & sin, sizeof(sin)) < 0) 
	{
		perror("bind");
		printf("---> %s,%d绑定失败!!!", __FILE__, __LINE__);
		exit(1);
	}
    /*取主机信息*/
	namelen = sizeof(sin);
	if (getsockname(sock, (struct sockaddr * ) & sin, &namelen) < 0) 
	{
		perror("getsockname");
		printf("---> %s,%d取主机信息失败!!!", __FILE__, __LINE__);
		exit(1);
	}

    /**监听端口*/
	if (listen(sock, 10) < 0) /*推荐5-10之间的数*未处理的请求队列可以容纳的最大数目*/
	{
		perror("listen");
		printf("---> %s,%d建立listen失败!!!", __FILE__, __LINE__);
		exit(1);
	}

	printf("\n--->服务启动成功开始监听!\n");

	while (1) 
	{
		printf("\n--->开始等待接收请求\n");
		namelen = sizeof(sin);
		if ((newsock = accept(sock, (struct sockaddr * ) & sin, &namelen)) < 0) 
		{
			printf("--->接收请求失败!!!");
			continue;
		}

		printf("\n--->接收到【%d】【%s】的请求!\n",
		newsock, inet_ntoa(sin.sin_addr));/*inet_ntoa,按照*.*.*.*打印出来*/

		if ( (child_pid = fork()) > 0 ) /*父进程跳出，继续接收请求*/
		{
			close(newsock);/*关闭newsock*/
			continue;
		} 
		else if ( child_pid == 0 )/*子进程*/
		{
			/*开始进行主控流程的调度*/
			close(sock);/*关闭父进程sock*/
			printf("子进程--->接收到IP=%s的请求!\n", inet_ntoa(sin.sin_addr));
			
			if ( recv( newsock, msg, sizeof(msg), 0) <0)
			{
			    printf( "recv信息出错!![%d]", newsock);
			    exit(1);
			}
            printf("服务端接收到的报文是:\n[%s]\n", msg);
            memset( servicename, 0x00, sizeof( servicename));
            memcpy( servicename, msg+4, 2);

            /* 打开报文文件 */
            sprintf( filename, "%s/src/agbs/wmpy/test/msg/%s",getenv("HOME"),servicename);
            printf("[%s]\n",filename);
            /*strcpy(filename,"msg/lz");liuze test*/
            fp = fopen( filename, "r");
            if (fp==NULL)
            {
                printf( "接收程序打开文件失败[%d][%s]", filename, strerror(errno));
                return -1;
            }
            while(1)
            {
                bzero( buffer, sizeof(buffer));
                fgets( buffer, 1024, fp);
                strcat( tmp, buffer);
                if( feof(fp))
                {
                    break;
                }
            }
            bzero(buff,sizeof(buff)); 
            sprintf( buff, "%04ld%s", strlen(tmp), tmp);
            printf("服务端发送的报文是:\n[%s]\n", buff);
			
            if ( send( newsock, buff, strlen(buff), 0)<0)
			{
			    printf( "send信息出错!![%s]", newsock);
			    exit(1);
			}
			
			close(newsock);
			/*shutdown(newsock, 2)和 close效果一样*/
		}
		exit(0);
	}
}
