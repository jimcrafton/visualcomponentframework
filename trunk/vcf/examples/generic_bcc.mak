#######################################################
# MAKEFILE for building VCF samples                   #
#                                                     #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

#tools
ILINK32=ilink32
CC=bcc32
RC=brcc32

!ifndef BMODE
BMODE=RELEASE
!endif

!ifndef TARG
TARG=CONSOLE
!endif

!if $(BMODE) != RELEASE && $(BMODE) != DEBUG
!  error Illegal value for BMODE option
!endif

!if $(TARG) != CONSOLE && $(TARG) != GUI
!  error Illegal value for TARG option
!endif

INCDIR=..\..\src
!include <filedefs.inc>


################################
# Target
################################
!if $(TARG) == CONSOLE
TFLAGS=-tWCR
LFLAGS=-ap
!else
TFLAGS=-tW -tWR
LFLAGS=-aa -Tpe
!endif

SYSDEFINES=WIN32;_MBCS
BCC32STARTUP=c0x32.obj
BCC32RTLIB=cw32mti.lib
ALLOBJS=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS=$(LIBFILES) import32.lib $(BCC32RTLIB)
LIBDIR=..\..\lib

CPPFLAGS=$(TFLAGS) $(CUSTOMCPP) -q -6 -tWM -VF -RT -x -a8 -b -X- -D$(SYSDEFINES);$(USERDEFINES)
CFLAGS=$(TFLAGS)  $(CUSTOMC) -q -6 -tWM -VF -w-aus -w-sus -w-pia -w-rch -w-ccc -w-eff -D$(SYSDEFINES);$(USERDEFINES)
SLINKFLAGS=-q $(LFLAGS) $(CUSTOMLFLAGS) -Gn -c -Af:0x1000 -Ao:0x1000 -L$(LIBDIR)

!if $(BMODE) == RELEASE
CPPFLAGS=-v- -O2 -k- $(CPPFLAGS)
CFLAGS=-v- -O2 -k- $(CFLAGS)
SLINKFLAGS=-v- -x $(SLINKFLAGS)
SYSDEFINES=WIN32;_MBCS;NODEBUG
!else
CPPFLAGS=-v -vi- -Od -k -R -Q -M -y -r- $(CPPFLAGS)
CFLAGS=-v -vi- -Od -k -Q -R -M -y -r- $(CFLAGS)
SLINKFLAGS=-v -m -M $(SLINKFLAGS)
SYSDEFINES=WIN32;_MBCS;_DEBUG
!endif

all: $(PROJECT) 

clean: cleanobj cleantgt

cleanobj:: 
	-@echo Deleting intermediate files for $(PROJECT)
	-@if exist *.obj del *.obj
	-@if exist *.res del *.res
	-@if exist *.tds del *.tds
	-@if exist *.map del *.map

cleantgt::
	-@echo Deleting $(PROJECT)
	-@if exist $(PROJECT) del $(PROJECT)


  
$(PROJECT): $(OBJFILES) $(RESFILE)
    -@$(ILINK32) $(SLINKFLAGS) $(ALLOBJS),$(PROJECT),,$(ALLLIBS),$(DEFFILE),$(RESFILE)


.cpp.obj:
      @$(CC) $(CPPFLAGS) -I$(INCDIR) /c -o$@ $<

.c.obj:
      @$(CC) $(CFLAGS) -I$(INCDIR) /c -o$@ $<

#This include sequence is added because of some visual studio
#generated rc scripts
#This will only work on CBuilder with installed support for MFC
.rc.res:
      @$(RC) -r -i$(MAKEDIR)\..\Include;$(MAKEDIR)\..\Include\Mfc $<
