#
# NAME:       makefile
# AUTHOR:     yangwanchun
# VERSION:    1.0
# DATE:       2007/08/25
#

include $(HOME)/etc/makefile.xip

CMP = $(CC) $(SOFLAGS)

LIBS = -lkxml2lib.2.2 -lkpublib -liconv -lkencodelib -lkfmtconv -lEpcctab
#LIBS = -lkxml2lib.1.6 -lkpublib -liconv -lkencodelib -lkfmtconv -lEpcctab
#LIBS = -lkxml2lib.1.5 -lkpublib -liconv -lkencodelib -lkfmtconv -lEpcctab

include OBJS

all : $(TARGET) clean

$(TARGET) : $(OBJ)
	$(CMP) $@ $(OBJ) -L$(APLIBPATH) $(LIBS)
	$(MV) $@ $(APLIBPATH)/

.SUFFIXES:.ec 

.ec.o :	
	$(RM) -f $*.c
	$(EC) -I$(INCLPATH) $(ECFLAGS) -L$(APLIBPATH) $<
	$(RM) -f $*.c
	
.c.o:
	$(CC) -I$(INCLPATH) $(CCFLAGS) -L$(APLIBPATH) $<

clean:
	rm -f *.o
