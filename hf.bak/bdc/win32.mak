# 本工程文件要求在  VC 命令行环境下执行 
#
# 	nmake -f win32.mak
#
# wukun 2012/5


#######################################################
#######################################################
#######################################################
#VC路径
#VCINSTALLDIR=C:\Program Files\Microsoft Visual Studio 10.0\VC\
#VCDIR=C:\Program Files\Microsoft Visual Studio 10.0\VC\

# OPENSSL 路径
# ZLIB 路径
OPENSSL=C:\OpenSSL-Win32
ZLIB=.\zlib-1.2.3

# 附加编译标志
DEPCC= -I$(OPENSSL)\include -I$(ZLIB)
DEPLD= -LIBPATH:$(ZLIB) -LIBPATH:$(OPENSSL)\lib\VC\static \
    zlib.lib ssleay32MT.lib libeay32MT.lib \
    kernel32.lib user32.lib gdi32.lib advapi32.lib

#######################################################
#######################################################
#######################################################

# variables
STATICLIB = refbdc.lib
SHAREDLIB = refbdc.dll
IMPLIB    = refbdcdll.lib

CC = cl
AS = ml
LD = link
AR = lib
RC = rc
CFLAGS  = -nologo -MT -O2 -DWIN32 $(DEPCC)
ASFLAGS = -coff
LDFLAGS = -nologo -release $(DEPLD)
ARFLAGS = -nologo
RCFLAGS = /dWIN32 /r

OBJS = dllmain.obj bdc_des.obj bdc_rsa.obj bdc_zip.obj
OBJA =


# targets
all: $(STATICLIB) $(SHAREDLIB) $(IMPLIB) \
     tt.exe 

$(STATICLIB): $(OBJS) $(OBJA)
	$(AR) $(ARFLAGS) -out:$@ $(OBJS) $(OBJA)

$(IMPLIB): $(SHAREDLIB)

$(SHAREDLIB): bdcdll.def $(OBJS) $(OBJA) bdcdll.res
	$(LD) $(LDFLAGS) -def:bdcdll.def -dll -implib:$(IMPLIB) \
	  -out:$@ $(OBJS) $(OBJA) bdcdll.res

tt.exe: test.obj $(IMPLIB)
	$(LD) $(LDFLAGS) test.obj $(IMPLIB) -out:tt.exe

.c.obj:
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
	-del $(STATICLIB)
	-del $(SHAREDLIB)
	-del $(IMPLIB)
	-del *.obj
	-del *.res
	-del *.exp
	-del *.exe

