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


/***�ػ�����***/
main(int argc,char *argv[])
{
	pid_t	pid ;
	char	name[21] ;
    /***��������***/
	if ( ( pid=fork() ) < 0  ) 
	{
		printf("��������ʧ��\n") ;
		return 1 ;
	}
	else if ( pid>0 )/*��ֹ������*/
	{
		exit(0) ;
	}
	if ( setsid() == -1) /*������һ���µĽ�����*/
	{
	   printf("�������̶Ի��ڴ���\n") ;
	   return 1 ;
	}

	sigset(SIGHUP,SIG_IGN) ;/*�����û��˳�ʱ�ź�*SIG_DFL�ָ�*/
	sigset(SIGCHLD,SIG_IGN) ;/*�����ӽ��̽���ʱ�ź�*/
	
	/** ������signal�����յ����ź��Ժ󣬻�SIG_DFL���ź�.sigset�򲻻�*/

    /*�޸��ļ�·��*/
    /*
	sprintf(name,"/home/asxip/src/agbs/gspy/test/msg") ;
	chdir( name );
    */
	/*����ļ�����*/
	umask( 0 );
	errno=0 ;

	if (wys_rcv(argc,argv) )
	{
		printf("����ִ��ʧ��\n") ;
	}
	else
	{
		printf("����ִ�гɹ�\n") ;
    }
	return 0 ;
	/*Ӧ����setsid֮��,�ٴ�fork�ڶ��ӽ��̣�����һ�ӽ�����ֹ*/
}

/***  ����������� ***/
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
        printf("\n �÷�˵��: %s �˿ں�\n\n", argv[0]);
        exit(-1);
    }

	/*�ж϶˿�Ҫ����1024*/
	for (i = 0; i < strlen(argv[1]); i++) 
	{
		if (!isdigit(argv[1][i])) /*�ַ��Ƿ�������*/
		{
			printf("\n �÷�˵��: %s �˿ں�\n\n", argv[0]);
			exit(-1);
		}
	}
	
	portnum = atoi(argv[1]);
	
	if (portnum <= 1024) 
	{
		printf("\n�˿ں�[%s]С��1024!\n", argv[1]);
		exit(-1);
	}

    /**������ʽsocket**/
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)/*IPPROTO_TCP��ֱ����Ϊ0*/
	{
		perror("socket");
		printf("--->%s,%d����sockʧ��!!!", __FILE__, __LINE__);
		exit(1);
	}

	/*--������������ʱ�����Ƚ�ԭ���󶨵Ķ˿ڱ��Ϊδ�ã�sock��bug--*/
	optvar = 1;
	optlen = sizeof(optvar);

	ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) & optvar, optlen);
	if (ret == -1) 
	{
		printf("%s: setsockopt error!", argv[0]);
		exit(-1);
	}

	bzero((char * )&sin, sizeof(sin));
	sin.sin_family = AF_INET;                /*Internet��ַ��AF_xxx*/
	sin.sin_port = htons(portnum);           /*�˿ں�*���Ϊ0��bind����ѡ��һ���˿�*/
	sin.sin_addr.s_addr = htonl(INADDR_ANY); /*Internet��ַ*INADDR_ANY(0)Ϊ������ַ*/
	bzero(&(sin.sin_zero), 8);               /*�ṹ��ʣ�ಿ��������Ϊ0*/
    
    /**�󶨶˿�**/
	if (bind(sock, (struct sockaddr * ) & sin, sizeof(sin)) < 0) 
	{
		perror("bind");
		printf("---> %s,%d��ʧ��!!!", __FILE__, __LINE__);
		exit(1);
	}
    /*ȡ������Ϣ*/
	namelen = sizeof(sin);
	if (getsockname(sock, (struct sockaddr * ) & sin, &namelen) < 0) 
	{
		perror("getsockname");
		printf("---> %s,%dȡ������Ϣʧ��!!!", __FILE__, __LINE__);
		exit(1);
	}

    /**�����˿�*/
	if (listen(sock, 10) < 0) /*�Ƽ�5-10֮�����*δ�����������п������ɵ������Ŀ*/
	{
		perror("listen");
		printf("---> %s,%d����listenʧ��!!!", __FILE__, __LINE__);
		exit(1);
	}

	printf("\n--->���������ɹ���ʼ����!\n");

	while (1) 
	{
		printf("\n--->��ʼ�ȴ���������\n");
		namelen = sizeof(sin);
		if ((newsock = accept(sock, (struct sockaddr * ) & sin, &namelen)) < 0) 
		{
			printf("--->��������ʧ��!!!");
			continue;
		}

		printf("\n--->���յ���%d����%s��������!\n",
		newsock, inet_ntoa(sin.sin_addr));/*inet_ntoa,����*.*.*.*��ӡ����*/

		if ( (child_pid = fork()) > 0 ) /*������������������������*/
		{
			close(newsock);/*�ر�newsock*/
			continue;
		} 
		else if ( child_pid == 0 )/*�ӽ���*/
		{
			/*��ʼ�����������̵ĵ���*/
			close(sock);/*�رո�����sock*/
			printf("�ӽ���--->���յ�IP=%s������!\n", inet_ntoa(sin.sin_addr));
			
			if ( recv( newsock, msg, sizeof(msg), 0) <0)
			{
			    printf( "recv��Ϣ����!![%d]", newsock);
			    exit(1);
			}
            printf("����˽��յ��ı�����:\n[%s]\n", msg);
            memset( servicename, 0x00, sizeof( servicename));
            memcpy( servicename, msg+4, 2);

            /* �򿪱����ļ� */
            sprintf( filename, "%s/src/agbs/wmpy/test/msg/%s",getenv("HOME"),servicename);
            printf("[%s]\n",filename);
            /*strcpy(filename,"msg/lz");liuze test*/
            fp = fopen( filename, "r");
            if (fp==NULL)
            {
                printf( "���ճ�����ļ�ʧ��[%d][%s]", filename, strerror(errno));
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
            printf("����˷��͵ı�����:\n[%s]\n", buff);
			
            if ( send( newsock, buff, strlen(buff), 0)<0)
			{
			    printf( "send��Ϣ����!![%s]", newsock);
			    exit(1);
			}
			
			close(newsock);
			/*shutdown(newsock, 2)�� closeЧ��һ��*/
		}
		exit(0);
	}
}
