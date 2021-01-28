#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

extern void trace(const char* fmt, ...);
extern void printError();

int des3enc(unsigned char* key, unsigned char* text, int textLength, unsigned char *out, int outLength) {
    int tmplen, ret;

    EVP_CIPHER_CTX ctx;
    const EVP_CIPHER *cipher = EVP_des_ede3_ecb();

    if (outLength < (textLength +7)/8*8) {
		trace("des3enc ������峤�Ȳ���");
        return -1;
	}

    EVP_CIPHER_CTX_init(&ctx);

    EVP_EncryptInit(&ctx, cipher, key, NULL);

    ret = EVP_EncryptUpdate(&ctx, // ���������Ķ���
        out,                // ���ܺ������
        &outLength,         // ���ܺ�����ݳ���
        text,               // Ҫ���ܵ�����
        textLength          // Ҫ���ܵ����ݳ���
        );
    if (!ret) {
		trace("des3enc EVP_EncryptUpdate error");
		printError();
		return -1;
	}
    ret = EVP_EncryptFinal(&ctx,out+outLength,&tmplen);
    if (!ret) {
		trace("des3enc EVP_EncryptFinal error");
		printError();
        return -1;
	}
    outLength += tmplen;

    EVP_CIPHER_CTX_cleanup(&ctx);

    return outLength;
}

int des3dec(unsigned char* key, unsigned char* text, int textLength, unsigned char *out, int outLength) {
    int tmplen, ret;

    EVP_CIPHER_CTX ctx;
    const EVP_CIPHER *cipher = EVP_des_ede3_ecb();

    if (outLength < (textLength +7)/8*8) {
		trace("des3dec ������峤�Ȳ���");
        return -1;
	}

    EVP_CIPHER_CTX_init(&ctx);

    EVP_DecryptInit(&ctx, cipher, key, NULL);

    ret = EVP_DecryptUpdate(&ctx, // ���������Ķ���
        out,                // ���ܺ������
        &outLength,         // ���ܺ�����ݳ���
        text,               // Ҫ���ܵ�����
        textLength          // Ҫ���ܵ����ݳ���
        );
    if (!ret) {
		trace("des3dec EVP_DecryptUpdate error");
		printError();
		return -1;
	}
    ret = EVP_DecryptFinal(&ctx,out+outLength,&tmplen);
    if (!ret) {
		trace("des3dec EVP_DecryptFinal error");
		printError();
		return -1;
	}
    outLength += tmplen;

    EVP_CIPHER_CTX_cleanup(&ctx);

    return outLength;
}


#if 0

void main(int argc, char *argv[])
{
    unsigned char key[24] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,1,2,3,4,5,6,7,8}; //��Կ
    int i;
    unsigned char buf[100];
    unsigned char out[100];
    char intext[] = "abc";
    int len = des3enc(key, (unsigned char*)intext, strlen(intext), buf, 16);
    for (i=0;i<len;i++) {
        printf("%02x", (unsigned char)buf[i]);
    }
    printf("\nlen=%d\n",len);
    len = des3dec(key, buf, len, out, 16);
    out[len]=0;
    printf("out=%s\nlen=%d\n",out, len);
}

#endif
