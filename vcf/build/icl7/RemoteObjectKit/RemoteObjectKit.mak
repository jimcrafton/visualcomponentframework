# Microsoft Developer Studio Generated NMAKE File, Based on RemoteObjectKit.dsp
!IF "$(CFG)" == ""
CFG=RemoteObjectKit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RemoteObjectKit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RemoteObjectKit - Win32 Release" && "$(CFG)" != "RemoteObjectKit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RemoteObjectKit.mak" CFG="RemoteObjectKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RemoteObjectKit - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RemoteObjectKit - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\bin\RemoteObjectKitDLL.dll"

!ELSE 

ALL : "NetworkKitDLL - Win32 Release" "FoundationKitDLL - Win32 Release" "..\..\..\bin\RemoteObjectKitDLL.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKitDLL - Win32 ReleaseCLEAN" "NetworkKitDLL - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractDistributedApplication.obj"
	-@erase "$(INTDIR)\ClassRegistryEntry.obj"
	-@erase "$(INTDIR)\ClassServerInstance.obj"
	-@erase "$(INTDIR)\DistributedClassRegistry.obj"
	-@erase "$(INTDIR)\DistributedException.obj"
	-@erase "$(INTDIR)\InstanceID.obj"
	-@erase "$(INTDIR)\Proxy.obj"
	-@erase "$(INTDIR)\RemoteObjectKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RemoteObjectKitDLL.exp"
	-@erase "$(OUTDIR)\RemoteObjectKitDLL.lib"
	-@erase "..\..\..\bin\RemoteObjectKitDLL.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /I "..\..\..\include\remote" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "REMOTEOBJECTKIT_EXPORTS" /Fp"$(INTDIR)\RemoteObjectKit.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RemoteObjectKit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\RemoteObjectKitDLL.pdb" /machine:I386 /out:"..\..\..\bin/RemoteObjectKitDLL.dll" /implib:"$(OUTDIR)\RemoteObjectKitDLL.lib" 
LINK32_OBJS= \
	"$(INTDIR)\AbstractDistributedApplication.obj" \
	"$(INTDIR)\ClassRegistryEntry.obj" \
	"$(INTDIR)\ClassServerInstance.obj" \
	"$(INTDIR)\DistributedClassRegistry.obj" \
	"$(INTDIR)\DistributedException.obj" \
	"$(INTDIR)\InstanceID.obj" \
	"$(INTDIR)\Proxy.obj" \
	"$(INTDIR)\RemoteObjectKit.obj" \
	"..\..\..\lib\FoundationKitDLL.lib" \
	"..\NetworkKit\Release\NetworkKitDLL.lib"

"..\..\..\bin\RemoteObjectKitDLL.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\bin\RemoteObjectKitDLL_d.dll"

!ELSE 

ALL : "NetworkKitDLL - Win32 Debug" "FoundationKitDLL - Win32 Debug" "..\..\..\bin\RemoteObjectKitDLL_d.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKitDLL - Win32 DebugCLEAN" "NetworkKitDLL - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractDistributedApplication.obj"
	-@erase "$(INTDIR)\ClassRegistryEntry.obj"
	-@erase "$(INTDIR)\ClassServerInstance.obj"
	-@erase "$(INTDIR)\DistributedClassRegistry.obj"
	-@erase "$(INTDIR)\DistributedException.obj"
	-@erase "$(INTDIR)\InstanceID.obj"
	-@erase "$(INTDIR)\Proxy.obj"
	-@erase "$(INTDIR)\RemoteObjectKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\RemoteObjectKitDLL_d.exp"
	-@erase "$(OUTDIR)\RemoteObjectKitDLL_d.lib"
	-@erase "$(OUTDIR)\RemoteObjectKitDLL_d.pdb"
	-@erase "..\..\..\bin\RemoteObjectKitDLL_d.dll"
	-@erase "..\..\..\bin\RemoteObjectKitDLL_d.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /I "..\..\..\include\remote" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FOUNDATIONKIT_DLL" /D "NETKIT_DLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RemoteObjectKit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=FoundationKitDLL_d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\RemoteObjectKitDLL_d.pdb" /debug /machine:I386 /out:"..\..\..\bin/RemoteObjectKitDLL_d.dll" /implib:"$(OUTDIR)\RemoteObjectKitDLL_d.lib" /pdbtype:sept /libpath:"..\..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\AbstractDistributedApplication.obj" \
	"$(INTDIR)\ClassRegistryEntry.obj" \
	"$(INTDIR)\ClassServerInstance.obj" \
	"$(INTDIR)\DistributedClassRegistry.obj" \
	"$(INTDIR)\DistributedException.obj" \
	"$(INTDIR)\InstanceID.obj" \
	"$(INTDIR)\Proxy.obj" \
	"$(INTDIR)\RemoteObjectKit.obj" \
	"$(OUTDIR)\FoundationKitDLL_d.lib" \
	"$(OUTDIR)\NetworkKitDLL_d.lib"

"..\..\..\bin\RemoteObjectKitDLL_d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("RemoteObjectKit.dep")
!INCLUDE "RemoteObjectKit.dep"
!ELSE 
!MESSAGE Warning: cannot find "RemoteObjectKit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "RemoteObjectKit - Win32 Release" || "$(CFG)" == "RemoteObjectKit - Win32 Debug"
SOURCE=..\..\..\src\remote\AbstractDistributedApplication.cpp

"$(INTDIR)\AbstractDistributedApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\ClassRegistryEntry.cpp

"$(INTDIR)\ClassRegistryEntry.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\ClassServerInstance.cpp

"$(INTDIR)\ClassServerInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\DistributedClassRegistry.cpp

"$(INTDIR)\DistributedClassRegistry.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\DistributedException.cpp

"$(INTDIR)\DistributedException.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\InstanceID.cpp

"$(INTDIR)\InstanceID.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\Proxy.cpp

"$(INTDIR)\Proxy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\remote\RemoteObjectKit.cpp

"$(INTDIR)\RemoteObjectKit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "RemoteObjectKit - Win32 Release"

"FoundationKitDLL - Win32 Release" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Release" 
   cd "..\RemoteObjectKit"

"FoundationKitDLL - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd "..\RemoteObjectKit"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 Debug"

"FoundationKitDLL - Win32 Debug" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Debug" 
   cd "..\RemoteObjectKit"

"FoundationKitDLL - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\RemoteObjectKit"

!ENDIF 

!IF  "$(CFG)" == "RemoteObjectKit - Win32 Release"

"NetworkKitDLL - Win32 Release" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Release" 
   cd "..\RemoteObjectKit"

"NetworkKitDLL - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd "..\RemoteObjectKit"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 Debug"

"NetworkKitDLL - Win32 Debug" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Debug" 
   cd "..\RemoteObjectKit"

"NetworkKitDLL - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\RemoteObjectKit"

!ENDIF 


!ENDIF 

