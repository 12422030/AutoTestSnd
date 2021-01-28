#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "zlib.h"

#define CHUNK 16384

extern void trace(const char* fmt, ...);

/* report a zlib or i/o error */
static void zerr(int ret, char* msg)
{
    trace("bdc_zip: %s error", msg);
    switch (ret) {
    case Z_ERRNO:
    case Z_STREAM_ERROR:
        trace("invalid compression level\n");
        break;
    case Z_DATA_ERROR:
        trace("invalid or incomplete deflate data\n");
        break;
    case Z_MEM_ERROR:
        trace("out of memory\n");
        break;
    case Z_VERSION_ERROR:
        trace("zlib version mismatch!\n");
    }
}

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        zerr(err, msg); \
    } \
}

/* Compress from file source to file dest until EOF on source.
   def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_STREAM_ERROR if an invalid compression
   level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
   version of the library linked do not match, or Z_ERRNO if there is
   an error reading or writing the files. */
static int bdc_deflate(FILE *source, FILE *dest)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    char in[CHUNK];
    char out[CHUNK];
	int level = Z_DEFAULT_COMPRESSION;

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
	CHECK_ERR(ret, "deflateInit");
    if (ret != Z_OK)
        return -1;

    /* compress until end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)deflateEnd(&strm);
			trace("read source file error");
            return -1;
        }
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)deflateEnd(&strm);
				trace("write compression file error");
				return -1;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);
    return 0;
}

/* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */
static int bdc_inflate(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    char in[CHUNK];
    char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
	CHECK_ERR(ret, "inflateInit");
    if (ret != Z_OK)
        return -1;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
			trace("read compression file error");
            return -1;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
				CHECK_ERR(ret, "inflate");
                return -1;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
				trace("write uncompression file error");
                return -1;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
	CHECK_ERR(ret, "inflateEnd");
    return ret == Z_STREAM_END ? 0 : -1;
}

static int bdc_zipX(char* inFilename, char* outFilename, int isDeflate) {
	FILE *source;
	FILE *dest;
	int ret;

	source = fopen(inFilename, "rb");
	if (source == NULL) {
		trace("fopen error: %s", inFilename);
		return -1;
	}
	dest = fopen(outFilename, "wb+");
	if (dest == NULL) {
		fclose(source);
		trace("fopen error: %s", outFilename);
	}

	if (isDeflate) {
		ret = bdc_deflate(source, dest);
	} else {
		ret = bdc_inflate(source, dest);
	}

	fclose(source);
	fclose(dest);
	return ret;
}

int bdc_zip(char* inFilename, char* outFilename) {
	return bdc_zipX(inFilename, outFilename, 1);
}

int bdc_unzip(char* inFilename, char* outFilename) {
	return bdc_zipX(inFilename, outFilename, 0);
}

#if 0
/* compress or decompress from stdin to stdout */
int main(int argc, char **argv)
{
    int ret;
	char *filename = argv[0];
	FILE *file;

	file = fopen(filename, "wb+");
    ret = bdc_deflate(stdin, file);
	fflush(file);
	printf("zip = %d\n", ret);
	ret = bdc_inflate(file, stdout);
    return ret;
}
#endif
