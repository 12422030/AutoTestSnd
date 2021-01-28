#
# NAME:       makefile
# AUTHOR:     yangwanchun
# VERSION:    1.0
# DATE:       2007/08/25
#

include $(HOME)/etc/makefile.xip

KLIBS = -lkpublib -lkcfglib  -lunionEsscAPI  -lkdblib -lktablib -lkdbuslib  -lkloglib -lkmaplib -lfmtpub

APLIBS = -ldb2

OBJ = tranpin.o

all :  tranpin clean

snd: $(OBJ) 
	$(CC) $(EXEFLAGS) $@ $(OBJ) -I$(DBINCLPATH) -L$(APLIBPATH) -L$(DBLIBPATH) $(KLIBS) $(APLIBS)
#$(MV) $@ $(BINPATH)/$@

cmsnd.o : tranpin.c
	$(CC) $(CCFLAGS) tranpin.c

clean:
	$(RM) -f *.o
