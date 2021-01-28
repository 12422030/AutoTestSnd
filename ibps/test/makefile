#
# NAME:       makefile
# AUTHOR:     yangwanchun
# VERSION:    1.0
# DATE:       2007/08/25
#

include $(HOME)/etc/makefile.xip

KLIBS = 

APLIBS = 

OBJ = cli.o

all :  cli clean

cli: $(OBJ) 
	$(CC) $(EXEFLAGS) $@ $(OBJ) -I$(INCLPATH) -I$(DBINCLPATH) -L$(APLIBPATH) -L$(DBLIBPATH) $(KLIBS) $(APLIBS)
	#$(MV) $@ $(BINPATH)/$@

cli.o : cli.c
	$(CC) $(CCFLAGS) -I$(INCLPATH) cli.c

clean:
	$(RM) -f *.o
