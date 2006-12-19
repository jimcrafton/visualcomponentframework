#######################################################
# MAKEFILE for building RegExKit_bcc_s(d).lib         #
#                   and RegExKit_bcc_(d).dll          #
#                                                     #
# (c) 2006 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

!ifndef BMODE
BMODE = RELEASE
!endif

!ifndef TARGET
TARGET = LIB
!endif

!if $(BMODE) != RELEASE && $(BMODE) != DEBUG
!  error Illegal value for BMODE option
!endif

!if $(TARGET) != LIB && $(TARGET) != DLL
!  error Illegal value for TARGET option
!endif

!include <..\defaultmake.inc>

!if $(TARGET) == LIB
PROJECT=$(PROJECT1)
SYSDEFINES=_LIB;REGEXKIT_LIB;NOT_RUBY;ONIG_EXTERN=extern
OUTDIR=..\..\..\lib
TDIR=S
!else
PROJECT=$(PROJECT2)
SYSDEFINES=_WINDOWS;_USRDLL;USE_FOUNDATIONKIT_DLL;REGEXKIT_EXPORTS;REGEXKIT_DLL;NOT_RUBY;EXPORT
OUTDIR=..\..\..\bin
TDIR=DLL
!endif

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	LPARAM=/P128
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif


LIBNAME=RegExKit_bcc_s$(DBG).lib
DLLNAME=RegExKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src;..\..\..\src\thirdparty\common\oniguruma
LIBDIR=..\..\..\lib
SRC=..\..\..\src\vcf\RegExKit
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;$(SYSDEFINES)
.path.cpp=$(SRC)
.path.c=..\..\..\src\thirdparty\common\oniguruma;..\..\..\src\thirdparty\common\oniguruma\enc
.path.obj=$(OBJ)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
CPPFILES=RegExKit.cpp
CFILES= ascii.c \
				big5.c \
				euc_jp.c \
				euc_kr.c \
				euc_tw.c \
				gb18030.c \
				iso8859_1.c \
				iso8859_10.c \
				iso8859_11.c \
				iso8859_13.c \
				iso8859_14.c \
				iso8859_15.c \
				iso8859_16.c \
				iso8859_2.c \
				iso8859_3.c \
				iso8859_4.c \
				iso8859_5.c \
				iso8859_6.c \
				iso8859_7.c \
				iso8859_8.c \
				iso8859_9.c \
				koi8.c \
				koi8_r.c \
				mktable.c \
				sjis.c \
				unicode.c \
				utf16_be.c \
				utf16_le.c \
				utf32_be.c \
				utf32_le.c \
				utf8.c  \
				regcomp.c \
				regenc.c \
				regerror.c \
				regexec.c \
				regext.c \
				reggnu.c \
				regparse.c \
				regposerr.c \
				regposix.c \
				regsyntax.c \
				regtrav.c \
				regversion.c \
				st.c				

OBJCFILES=$(CFILES:.c=.obj^ )         
OBJFILES=$(CPPFILES:.cpp=.obj^ )         
LIBFILES=UUID.LIB WS2_32.LIB
DEFFILE=
BCC32STARTUP=c0d32.obj
ALLOBJS=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS=$(LIBFILES) import32.lib $(BCC32RTLIB)

all: dirs $(RESFILE) $(PROJECT)

cleanobj:: 
	-@echo Deleting intermediate files for project
	-@if exist $(OBJ)\*.obj del $(OBJ)\*.obj
	-@if exist $(OBJ)\*.res del $(OBJ)\*.res
	-@if exist $(OBJ)\. rd $(OBJ)
!if $(BMODE) == RELEASE
	-@if exist $(BIN)\*.tds del $(BIN)\*.tds
	-@if exist $(BIN)\*.map del $(BIN)\*.map
!endif

cleantgt::
	-@echo Deleting output files for project
	-@if exist $(PROJECT) del $(PROJECT)
	-@if exist ..\..\..\lib\RegExKit_bcc$(DBGDLL).lib del ..\..\..\lib\RegExKit_bcc$(DBGDLL).lib

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@if not exist bcc md bcc
	-@if not exist $(OBJ) md $(OBJ)
	-@if not exist $(BIN) md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1): $(OBJCFILES) $(OBJFILES)
   @echo Linking $(<F) static library
   @$(LB) $< $(LPARAM) @&&|
   -+$(?: = &^
   -+)
   
| > NUL:

$(PROJECT2):: $(OBJCFILES) $(OBJFILES)
    @echo Linking $(<F) dynamic library
    @$(ILINK32) @&&|
    $(LINKFLAGS) $(BCC32STARTUP) $(?: = ^)
    $<,$*
    $(ALLLIBS)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\RegExKit_bcc$(DBGDLL).lib move $(BIN)\RegExKit_bcc$(DBGDLL).lib $(LIBDIR)
    

