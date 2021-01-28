#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "bdcdll.h"


// �����õ�key·��
#define KEY_DIR "./key"

// ģ��Զ�̻�ȡ�Ự��Կ
char* receive_key() {
	static char out[512];
#if 0
	unsigned char key[24] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,1,2,3,4,5,6,7,8}; //��Կ
#endif
	unsigned char key[24]  ; //��Կ
    strcpy(key,"31305320170307RWefUDT0vi");
#if 0
    encSessionKey(KEY_DIR"/rsa_private_key.pem", key, 24, out);
	printf("ģ��ǩ���󣬵õ�key:[%s]\n", out);
#endif
	return out;
}

static unsigned char sessionKey[24]; // ������ĻỰ��Կһֱ����
void decKey(char* stringKey) {
    memset(sessionKey,0x00,sizeof(sessionKey));
    memset(stringKey,0x00,sizeof(stringKey));
    strcpy(stringKey,"bf7a6459730c8c9ab7db7bb4061f7770aad96cb911011e64295cd06be0efb3f8e46df7a947278da5ae33f89a664c2e06235fe13b8b3e4d31e6ad40eb7ad07d4c3c8de7d116d2e5397a1cd084862e280228aad9d9f08d8a2debb99840325d017bd1972f966fd4538c973612dc780f27e8ce786b3f88135ce9695f1aaa25cf01fe");
    printf("data=[%s]\n",stringKey);
    if (decSessionKey(KEY_DIR"/key", stringKey, sessionKey) != 24) {
		printf("�Ự��Կ����ʧ��\n");
		exit(-1);
	}
    printf("sessionKey=[%s]\n",sessionKey);
}

void test_enc()
{
    int i, len;
	char intext[1024];
	unsigned char buf[1024];
    unsigned char out[1024];
	char* remoteKey;

	setLogFile("err.log");

	// �����Ự��Կ
	remoteKey = receive_key();
    decKey(remoteKey);
	strcpy(sessionKey,"31305320170307RWefUDT0vi");
	printf("\n\n\n");
	printf("sessionKey:[%s]",sessionKey);
	// ���Ա���
	strcpy(intext, "abc123-ס�����������н������ݲɼ�ϵͳ-���Ľӿ����˵����V1.0.0"); 
	sprintf(intext,"abcd1234");
	printf("ԭʼ����Ϊ:[%s]\n", intext);

	// ����
    len = des3enc(sessionKey, (unsigned char*)intext, strlen(intext), buf, sizeof(buf));
	if (len == -1) {
		printf("����ʧ��\n");
		exit(-1);
	}
	printf("���ܺ���:[%s]\n",buf);
	printf("���ܺ�ı���(len=%d)\n", len);
    for (i=0;i<len;i++) {
        printf("%02x", (unsigned char)buf[i]);
    }

	// ����
    len = des3dec(sessionKey, buf, len, out, sizeof(out));
	if (len == -1) {
		printf("����ʧ��\n");
		exit(-1);
	}
    out[len]=0;
    printf("���ܺ�ı���(len=%d)Ϊ:[%s]\n",len, out);
}

void test_zip() {
	int ret = bdc_zip("a", "b");
	printf("bdc_zip=%d\n", ret);
}

void main(int argc, char *argv[])
{
printf("test start\n");
	setLogFile("/tmp/log");
	test_zip();
	test_enc();
}
