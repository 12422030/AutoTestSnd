#ifndef _REF_BDC_H_
#define _REF_BDC_H_
#ifdef	__cplusplus
extern	"C" {
#endif


#ifdef WIN32
#define BDC_API __declspec(dllimport)
#else
#define BDC_API  
#endif

BDC_API int setLogFile(char * filename);

BDC_API int des3enc(unsigned char* key, unsigned char* text, int textLength, unsigned char *out, int outLength);
BDC_API int des3dec(unsigned char* key, unsigned char* text, int textLength, unsigned char *out, int outLength);
BDC_API int encSessionKey(const char* filename, unsigned char* binkey, int key_len, unsigned char* out);
BDC_API int decSessionKey(const char* filename, unsigned char* bcdkey, unsigned char* out);

BDC_API int bdc_zip(char* inFilename, char* outFilename);
BDC_API int bdc_unzip(char* inFilename, char* outFilename);

#ifdef __cplusplus
}
#endif
#endif //_REF_BDC_H_
