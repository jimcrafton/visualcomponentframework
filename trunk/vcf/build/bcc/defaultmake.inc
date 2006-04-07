
#tools
BCROOT=c:\Borland\BCC55\bin
ILINK32=$(BCROOT)\ilink32
LB=$(BCROOT)\tlib
CC=$(BCROOT)\bcc32
RC=$(BCROOT)\brcc32

#C/C++ compile/link flags
CFLAGS=-q -6 -tWDR -tWM -Q -w-aus -w-sus -w-pia -w-rch -w-ccc -w-eff -w-sig -w-use -w-voi -w-def -w-pin -D$(USERDEFINES);$(SYSDEFINES)
CPPFLAGS=-q -6 -tWDR -tWM -RT -x -a8 -b -X- -Q -w-aus -w-sig -w-voi -w-use -w-def -w-pin -w-8084 -D$(USERDEFINES);$(SYSDEFINES)
LINKFLAGS=-q -aa -Tpd -Gn -Gi -c -Af:0x1000 -Ao:0x1000 -L$(LIBDIR) -j$(OBJ)
BCC32RTLIB=cw32mti.lib

!if $(BMODE) == RELEASE
CPPFLAGS=-v- -O2 -k- -Q -w-inl $(CPPFLAGS)
CFLAGS=-v- -O2 -k- -Q  -w-inl $(CFLAGS)
LINKFLAGS=-v- -x $(LINKFLAGS)
DBG=
DBGDLL=
!else
CPPFLAGS=-v -vi- -Od -k -R -M -y -r- $(CPPFLAGS)
CFLAGS=-v -vi- -Od -k -R -M -y -r- $(CFLAGS)
LINKFLAGS=-v -m -M $(LINKFLAGS)
DBG=d
DBGDLL=_d
!endif

.cpp.obj:
      @$(CC) $(CPPFLAGS) -I$(INCDIR) -n$(OBJ) /c $<

.c.obj:
      @$(CC) $(CFLAGS) -I$(INCDIR) -n$(OBJ) /c $<

#This include sequence is added because of some visual studio
#generated rc scripts
#This will only work on CBuilder with installed support for MFC
.rc.res:
      @echo Compiling $(<F)
      @$(RC) $(RFLAGS) -i$(BCROOT)\..\Include;$(BCROOT)\..\Include\Mfc -fo$@ $< > NUL:
