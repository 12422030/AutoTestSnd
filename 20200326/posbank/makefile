#
# NAME:       makefile
# AUTHOR:     yangwanchun
# VERSION:    1.0
# DATE:       2007/08/25
#

include $(HOME)/etc/makefile.xip

KLIBS = -lkpublib -lkcfglib -lkinitlib -lkdblib -lktablib -lkdbuslib -lkflowlib -lktcplib -lkloglib -lkmaplib

APLIBS = -ldb2

OBJ = cmsnd.o

all :  snd clean

snd: $(OBJ) 
	$(CC) $(EXEFLAGS) $@ $(OBJ) -I$(DBINCLPATH) -L$(APLIBPATH) -L$(DBLIBPATH) $(KLIBS) $(APLIBS)
#$(MV) $@ $(BINPATH)/$@

cmsnd.o : cmsnd.c
	$(CC) $(CCFLAGS) cmsnd.c

clean:
	$(RM) -f *.o
