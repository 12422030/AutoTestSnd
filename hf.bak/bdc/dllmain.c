#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/err.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ERR_load_crypto_strings();
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

static FILE* fp;
int setLogFile(char * filename) {
    if (fp != NULL)
        return 0;
	if((fp = fopen(filename, "a+")) == NULL)
		return -1;
	return 0;
}

void trace(const char* fmt, ...)
{
	va_list	args;

	if (fp == NULL)
		return;

	va_start(args, fmt);
	vfprintf(fp, fmt, args);
	fprintf(fp, "%s", "\n");
	fflush(fp);
}
