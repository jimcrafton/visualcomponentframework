
#tools
ILINK32=ilink32
LB=tlib
CC=bcc32

#C/C++ compile/link flags
CFLAGS=-q -6 -tWD -tWR -tWM -VF -w-aus -w-sus -w-pia -w-rch -w-ccc -w-eff -D$(USERDEFINES);$(SYSDEFINES)
CPPFLAGS=-q -6 -tWD  -tWR -tWM -VF -RT -x -a8 -b -X- -D$(USERDEFINES);$(SYSDEFINES)
LINKFLAGS=-q -aa -Tpd -Gn -Gi -c -Af:0x1000 -Ao:0x1000 -L$(LIBDIR)
BCC32RTLIB=cw32mti.lib

!if $(BMODE) == RELEASE
CPPFLAGS=-v- -O2 -k- $(CPPFLAGS)
CFLAGS=-v- -O2 -k- $(CFLAGS)
LINKFLAGS=-v- -x $(LINKFLAGS)
DBG=
DBGDLL=
!else
CPPFLAGS=-v -vi- -Od -k -R -Q -M -y -r- $(CPPFLAGS)
CFLAGS=-v -vi- -Od -k -Q -R -M -y -r- $(CFLAGS)
LINKFLAGS=-v -m -M $(LINKFLAGS)
DBG=d
DBGDLL=_d
!endif

.cpp.obj:
      @$(CC) $(CPPFLAGS) -I$(INCDIR) /c -o$@ $<

.c.obj:
      @$(CC) $(CFLAGS) -I$(INCDIR) /c -o$@ $<

