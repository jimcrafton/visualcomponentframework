# Microsoft Developer Studio Generated NMAKE File, Based on NetworkKitDLL.dsp
!IF "$(CFG)" == ""
CFG=NetworkKitDLL - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NetworkKitDLL - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NetworkKitDLL - Win32 Release" && "$(CFG)" != "NetworkKitDLL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKitDLL.mak" CFG="NetworkKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NetworkKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NetworkKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NetworkKitDLL - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\bin\NetworkKitDLL.dll"

!ELSE 

ALL : "FoundationKitDLL - Win32 Release" "..\..\..\bin\NetworkKitDLL.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKitDLL - Win32 ReleaseCLEAN" 
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
	-@erase "$(OUTDIR)\NetworkKitDLL.exp"
	-@erase "$(OUTDIR)\NetworkKitDLL.lib"
	-@erase "..\..\..\bin\NetworkKitDLL.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NETWORKKITDLL_EXPORTS" /Fp"$(INTDIR)\NetworkKitDLL.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NetworkKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\NetworkKitDLL.pdb" /machine:I386 /out:"..\..\..\bin/NetworkKitDLL.dll" /implib:"$(OUTDIR)\NetworkKitDLL.lib" 
LINK32_OBJS= \
	"$(INTDIR)\NetToolkit.obj" \
	"$(INTDIR)\ServerSocketEvent.obj" \
	"$(INTDIR)\Socket.obj" \
	"$(INTDIR)\SocketEvent.obj" \
	"$(INTDIR)\SocketListeningLoop.obj" \
	"$(INTDIR)\URL.obj" \
	"$(INTDIR)\Win32SocketPeer.obj" \
	"..\..\..\lib\FoundationKitDLL.lib"

"..\..\..\bin\NetworkKitDLL.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NetworkKitDLL - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugDLL\obj

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\bin\NetworkKitDLL_d.dll"

!ELSE 

ALL : "FoundationKitDLL - Win32 Debug" "..\..\..\bin\NetworkKitDLL_d.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKitDLL - Win32 DebugCLEAN" 
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
	-@erase "$(OUTDIR)\NetworkKitDLL_d.exp"
	-@erase "$(OUTDIR)\NetworkKitDLL_d.lib"
	-@erase "$(OUTDIR)\NetworkKitDLL_d.pdb"
	-@erase "..\..\..\bin\NetworkKitDLL_d.dll"
	-@erase "..\..\..\bin\NetworkKitDLL_d.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NO_MFC" /D "FRAMEWORK_DLL" /D "NETKIT_DLL" /D "NETKIT_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NetworkKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=FoundationKitDLL_d.lib Ws2_32.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\NetworkKitDLL_d.pdb" /debug /machine:I386 /out:"..\..\..\bin/NetworkKitDLL_d.dll" /implib:"$(OUTDIR)\NetworkKitDLL_d.lib" /pdbtype:sept /libpath:"..\..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\NetToolkit.obj" \
	"$(INTDIR)\ServerSocketEvent.obj" \
	"$(INTDIR)\Socket.obj" \
	"$(INTDIR)\SocketEvent.obj" \
	"$(INTDIR)\SocketListeningLoop.obj" \
	"$(INTDIR)\URL.obj" \
	"$(INTDIR)\Win32SocketPeer.obj" \
	"$(OUTDIR)\FoundationKitDLL_d.lib"

"..\..\..\bin\NetworkKitDLL_d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NetworkKitDLL.dep")
!INCLUDE "NetworkKitDLL.dep"
!ELSE 
!MESSAGE Warning: cannot find "NetworkKitDLL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NetworkKitDLL - Win32 Release" || "$(CFG)" == "NetworkKitDLL - Win32 Debug"
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


!IF  "$(CFG)" == "NetworkKitDLL - Win32 Release"

"FoundationKitDLL - Win32 Release" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Release" 
   cd "..\NetworkKit"

"FoundationKitDLL - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd "..\NetworkKit"

!ELSEIF  "$(CFG)" == "NetworkKitDLL - Win32 Debug"

"FoundationKitDLL - Win32 Debug" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Debug" 
   cd "..\NetworkKit"

"FoundationKitDLL - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\NetworkKit"

!ENDIF 


!ENDIF 

