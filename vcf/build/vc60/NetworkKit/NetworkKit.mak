# Microsoft Developer Studio Generated NMAKE File, Based on NetworkKit.dsp
!IF "$(CFG)" == ""
CFG=NetworkKit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NetworkKit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NetworkKit - Win32 Release" && "$(CFG)" != "NetworkKit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKit.mak" CFG="NetworkKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NetworkKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "NetworkKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NetworkKit - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\ReleaseS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NetworkKit_s.lib"

!ELSE 

ALL : "FoundationKit - Win32 Release" "$(OUTDIR)\NetworkKit_s.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NetToolkit.obj"
	-@erase "$(INTDIR)\ServerSocketEvent.obj"
	-@erase "$(INTDIR)\Socket.obj"
	-@erase "$(INTDIR)\SocketEvent.obj"
	-@erase "$(INTDIR)\SocketListeningLoop.obj"
	-@erase "$(INTDIR)\URL.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Win32SocketPeer.obj"
	-@erase "$(OUTDIR)\NetworkKit_s.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\NetworkKit.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NetworkKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\NetworkKit_s.lib" 
LIB32_OBJS= \
	"$(INTDIR)\NetToolkit.obj" \
	"$(INTDIR)\ServerSocketEvent.obj" \
	"$(INTDIR)\Socket.obj" \
	"$(INTDIR)\SocketEvent.obj" \
	"$(INTDIR)\SocketListeningLoop.obj" \
	"$(INTDIR)\URL.obj" \
	"$(INTDIR)\Win32SocketPeer.obj" \
	"$(OUTDIR)\FoundationKit_s.lib"

"$(OUTDIR)\NetworkKit_s.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NetworkKit - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NetworkKit_sd.lib"

!ELSE 

ALL : "FoundationKit - Win32 Debug" "$(OUTDIR)\NetworkKit_sd.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NetToolkit.obj"
	-@erase "$(INTDIR)\ServerSocketEvent.obj"
	-@erase "$(INTDIR)\Socket.obj"
	-@erase "$(INTDIR)\SocketEvent.obj"
	-@erase "$(INTDIR)\SocketListeningLoop.obj"
	-@erase "$(INTDIR)\URL.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Win32SocketPeer.obj"
	-@erase "$(OUTDIR)\NetworkKit_sd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\NetworkKit.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NetworkKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\NetworkKit_sd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\NetToolkit.obj" \
	"$(INTDIR)\ServerSocketEvent.obj" \
	"$(INTDIR)\Socket.obj" \
	"$(INTDIR)\SocketEvent.obj" \
	"$(INTDIR)\SocketListeningLoop.obj" \
	"$(INTDIR)\URL.obj" \
	"$(INTDIR)\Win32SocketPeer.obj" \
	"$(OUTDIR)\FoundationKit_sd.lib"

"$(OUTDIR)\NetworkKit_sd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NetworkKit.dep")
!INCLUDE "NetworkKit.dep"
!ELSE 
!MESSAGE Warning: cannot find "NetworkKit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NetworkKit - Win32 Release" || "$(CFG)" == "NetworkKit - Win32 Debug"
SOURCE=..\..\..\src\net\NetToolkit.cpp

"$(INTDIR)\NetToolkit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\net\ServerSocketEvent.cpp

"$(INTDIR)\ServerSocketEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\net\Socket.cpp

"$(INTDIR)\Socket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\net\SocketEvent.cpp

"$(INTDIR)\SocketEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\net\SocketListeningLoop.cpp

"$(INTDIR)\SocketListeningLoop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\net\URL.cpp

"$(INTDIR)\URL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32SocketPeer.cpp

"$(INTDIR)\Win32SocketPeer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "NetworkKit - Win32 Release"

"FoundationKit - Win32 Release" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" 
   cd "..\NetworkKit"

"FoundationKit - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NetworkKit"

!ELSEIF  "$(CFG)" == "NetworkKit - Win32 Debug"

"FoundationKit - Win32 Debug" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" 
   cd "..\NetworkKit"

"FoundationKit - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NetworkKit"

!ENDIF 


!ENDIF 

