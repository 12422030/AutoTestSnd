# 本工程文件要求在  VC 命令行环境下执行 
#
# 	nmake -f win32.mak
#
# wukun 2012/5

HOME=..
#export OBJECT_MODE=$(OBJECT_MODE)

#######################################################
#######################################################
#######################################################
#VC路径
#VCINSTALLDIR=C:\Program Files\Microsoft Visual Studio 10.0\VC\
#VCDIR=C:\Program Files\Microsoft Visual Studio 10.0\VC\

# OPENSSL 路径
# ZLIB 路径
#OPENSSL=C:\OpenSSL-Win32
OPENSSL=../openssl-0.9.8u
ZLIB=../zlib-1.2.7

# 附加编译标志
DEPCC= -I$(OPENSSL)/include -I$(ZLIB)
#DEPLD= -lssl -lz
#DEPLD= -lz $(HOME)/lib/libssl.a $(HOME)/lib/libcrypto.a
DEPLD= $(HOME)/lib/libz.a $(HOME)/lib/libcrypto.a

#######################################################
#######################################################
#######################################################

# variables
STATICLIB = librefbdc.a
SHAREDLIB = 
IMPLIB    = 

CC = cc -q$(OBJECT_MODE) -qcpluscmt -qmaxmem=32768 #-b elf
AS = 
LD = cc
AR = ar -X$(OBJECT_MODE)
RC = 
CFLAGS  = -g $(DEPCC)
ASFLAGS =
LDFLAGS =
ARFLAGS = crv
RCFLAGS =

OBJS = dllmain.o bdc_des.o bdc_rsa.o bdc_zip.o
OBJA =


# targets
all:$(STATICLIB) tt

$(STATICLIB): $(OBJS) $(OBJA)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(OBJA)
	cc -bexpall -G -o  librefbdc.so $@ $(OBJS)
	cp librefbdc.so $(HOME)/lib/
	cp $(STATICLIB) $(HOME)/lib/

#$(IMPLIB): $(SHAREDLIB)

$(SHAREDLIB): $(OBJS) $(OBJA) 
	$(LD) -G $(LDFLAGS) -o $@ $(OBJS) $(OBJA) $(DEPLD)

tt: test.o $(SHAREDLIB)
	$(LD) $(LDFLAGS) -ott test.o $(STATICLIB) $(DEPLD)

.c.o:
	$(CC) -c $(CFLAGS) $<

.asm.obj:
	$(AS) -c $(ASFLAGS) $<

bdc_des.obj: bdc_des.c 
bdc_rsa.obj: bdc_rsa.c
bdc_zip.obj: bdc_zip.c
dllmain.obj: dllmain.c
test.obj: test.c

bdcdll.res: bdcdll.rc
	$(RC) $(RCFLAGS) /fo$@ bdcdll.rc


# cleanup
clean:
	rm -f $(STATICLIB)
	rm -f $(SHAREDLIB)
	rm -f $(IMPLIB)
	rm -f *.obj
	rm -f *.o
	rm -f *.res
	rm -f *.exp
	rm -f *.exe

