#ifndef WIN32
#include <unistd.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>

#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h> // make AIX64 happy

#define TRACE 0
extern void trace(const char* fmt, ...);

extern int encSessionKey(const char* filename, unsigned char* binkey, int key_len, unsigned char* out);
extern int decSessionKey(const char* filename, unsigned char* bcdkey, unsigned char* out);

extern int base64_enc(const unsigned char *in,  int len, unsigned char* out,  int size);
extern int base64_dec(const unsigned char *in,  int len, unsigned char* out,  int size);
int bcd_enc(const unsigned char *in,  int len, unsigned char *out,  int size);
int bcd_dec(const unsigned char *in,  int len, unsigned char *out,  int size);

static RSA* readPublicKey(const char* filename);
static RSA* readPrivateKey(const char* filename);

#if 0
int main(int argc, char* argv[]) {
    //ERR_load_crypto_strings();
    char decData[1024];
    char encData[1024];

    char *data = "a1b2c3";
    int encRet = encSessionKey("rsa_private_key.pem", data, strlen(data), encData);
    int decRet = decSessionKey("key", encData, decData);

    printf("data=%s\n", data);
    printf("enc\n=%s\n", encData);
    printf("dec=%d:%s\n", decRet, decData);

    // free all openssl data
    CRYPTO_cleanup_all_ex_data();
    return 0;
}
#endif

void printError(){
    char buf[1024];
    char * errmsg = ERR_error_string(ERR_get_error(),buf);
    trace(errmsg);
}

int encSessionKey(const char* filename, unsigned char* key, int key_len, unsigned char* out) {
    int ret;
    RSA* rsa;
    char bytes[1024];
    int bytes_len = 1024;

    rsa = readPrivateKey(filename);
    if (rsa == NULL)
        return -1;
    ret = RSA_private_encrypt(key_len, key, bytes, rsa, RSA_PKCS1_PADDING);
    RSA_free(rsa);
    if (ret < 0) {
        printError();
        trace("RSA_private_encrypt error");
        return -1;
    }
    bytes[ret] = 0;
    bytes_len = bcd_enc(bytes,ret,out,bytes_len);
    out[bytes_len] = 0;
#if TRACE
printf("ENC-KEY binkey= %d:%s\n", ret, bytes);
printf("ENC-KEY strkey = %d:%s\n", bytes_len, out);
#endif
    return bytes_len;
}

int decSessionKey(const char* filename, unsigned char* key, unsigned char* out) {
    int ret;
    RSA* rsa;
    char bytes[1024];
    int bytes_len = 1024;

    bytes_len = bcd_dec(key,strlen(key),bytes,bytes_len);

#if TRACE
printf("DEC-KEY strkey= %d:%s\n", strlen(key),key);
bytes[bytes_len] = 0;
printf("DEC-KEY binkey= %d:%s\n", bytes_len, bytes);
#endif

    rsa = readPublicKey(filename);
    if (rsa == NULL) {
        trace("readPublicKey error: %s", filename);
        return -1;
	}
    ret = RSA_public_decrypt(bytes_len, bytes, out, rsa, RSA_PKCS1_PADDING);
    RSA_free(rsa);
    if (ret < 0) {
        printError();
        trace("RSA_public_decrypt error");
        return -1;
    }
    out[ret] = 0;
    return ret;
}

static RSA* readPublicKey(const char* filename) {
    RSA* rsa = NULL;
    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
            trace("open error");
            return NULL;
    }
    rsa = (RSA*) PEM_read_RSA_PUBKEY(fp, 0,0,0);
    fclose(fp);
    return rsa;
}

static RSA* readPrivateKey(const char* filename) {
    RSA* rsa = NULL;
    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
            trace("open error");
            return NULL;
    }
    rsa = (RSA*) PEM_read_RSAPrivateKey(fp, 0,0,0);
    fclose(fp);
    return rsa;
}

int base64_enc(const unsigned char *in,  int len, unsigned char *out,  int size) {
    int ret;
    BIO *bio, *b64;
    BUF_MEM *bptr = NULL;

    assert(in);
    assert(out);
    assert(size >= len*4/3);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_write(bio, in, len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    memcpy(out, bptr->data, bptr->length);
    out[bptr->length] = 0;
    ret = bptr->length;
    BIO_free_all(bio);
    return ret;
}

int base64_dec(const unsigned char *in,  int len, unsigned char* out,  int size) {
    BIO *bio, *b64;
    //BUF_MEM *bptr = NULL;
	int counts;

    assert(in);
    assert(out);
    assert(size >= len*2/3);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf((void*)in, len);
    bio = BIO_push(b64, bio);

    counts = BIO_read(bio, out, size);
    out[counts] = 0;
    BIO_free_all(bio);
    return counts;
}

int bcd_enc(const unsigned char *in,  int len, unsigned char *out,  int size) {
	int i;
	unsigned char c;
    assert(size >= len*2);

	for (i=0; i<len; i++) {
		c = (((unsigned char)in[i]) & 0xF0) >> 4;
		if (c <= 9) out[i*2] = 0x30 | c;
        else        out[i*2] = 0x40 | (c - 9);
		c = (((unsigned char)in[i]) & 0x0F) ;
		if (c <= 9) out[i*2 + 1] = 0x30 | c;        // '0' = 0x30
        else        out[i*2 + 1] = 0x40 | (c - 9);  // 'A' = 0x41
	}
    return len * 2;
}

int bcd_dec(const unsigned char *in,  int len,  unsigned char *out,  int size) {
	int i;
	char c, h, l;
    assert(size >= len/2);

	for (i=0; i<len/2; i++) {
		c = in[i*2 + 0];
        if (c >= '0' && c <= '9')
            h = c & 0x0F;
        else if (c >= 'a' && c <='f' || c >= 'A' && c <='F')
            h = (c & 0x0F) + 9;
        else
            h = 0;

		c = in[i*2 + 1];
        if (c >= '0' && c <= '9')
            l = c & 0x0F;
        else if (c >= 'a' && c <='f' || c >= 'A' && c <='F')
            l = (c & 0x0F) + 9;
        else
            l = 0;

        out[i] = h << 4 | l;
	}
    return len / 2;
}


