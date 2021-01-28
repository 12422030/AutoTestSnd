#
# NAME:       makefile
# AUTHOR:     yangwanchun
# VERSION:    1.0
# DATE:       2007/08/25
#

include $(HOME)/etc/makefile.xip

KLIBS = -lkmaplib -lkpublib -lkcfglib -lkinitlib -lkdblib -lktablib -lkdbuslib -lkflowlib -lktcplib -lkloglib

APLIBS = -ldb2

OBJ = vtmbank.o

all :  vtmbank clean

palnrcv: $(OBJ) 
	$(CC) $(EXEFLAGS) $@ $(OBJ) -I$(DBINCLPATH) -L$(APLIBPATH) -L$(DBLIBPATH) $(KLIBS) $(APLIBS)
#$(MV) $@ $(BINPATH)/$@

palnrcv.o : vtmbank.c
	$(CC) $(CCFLAGS) vtmbank.c

clean:
	$(RM) -f *.o
