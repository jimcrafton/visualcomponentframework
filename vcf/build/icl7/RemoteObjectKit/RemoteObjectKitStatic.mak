# Microsoft Developer Studio Generated NMAKE File, Based on RemoteObjectKitStatic.dsp
!IF "$(CFG)" == ""
CFG=RemoteObjectKitStatic - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RemoteObjectKitStatic - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RemoteObjectKitStatic - Win32 Release" && "$(CFG)" != "RemoteObjectKitStatic - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RemoteObjectKitStatic.mak" CFG="RemoteObjectKitStatic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RemoteObjectKitStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKitStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\ReleaseS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RemoteObjectKit_s.lib"

!ELSE 

ALL : "NetworkKit - Win32 Release" "FoundationKit - Win32 Release" "$(OUTDIR)\RemoteObjectKit_s.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 ReleaseCLEAN" "NetworkKit - Win32 ReleaseCLEAN" 
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
	-@erase "$(OUTDIR)\RemoteObjectKit_s.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /I "..\..\..\include\remote" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\RemoteObjectKitStatic.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RemoteObjectKitStatic.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\RemoteObjectKit_s.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractDistributedApplication.obj" \
	"$(INTDIR)\ClassRegistryEntry.obj" \
	"$(INTDIR)\ClassServerInstance.obj" \
	"$(INTDIR)\DistributedClassRegistry.obj" \
	"$(INTDIR)\DistributedException.obj" \
	"$(INTDIR)\InstanceID.obj" \
	"$(INTDIR)\Proxy.obj" \
	"$(INTDIR)\RemoteObjectKit.obj" \
	"$(OUTDIR)\FoundationKit_s.lib" \
	"$(OUTDIR)\NetworkKit_s.lib"

"$(OUTDIR)\RemoteObjectKit_s.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RemoteObjectKit_sd.lib"

!ELSE 

ALL : "NetworkKit - Win32 Debug" "FoundationKit - Win32 Debug" "$(OUTDIR)\RemoteObjectKit_sd.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 DebugCLEAN" "NetworkKit - Win32 DebugCLEAN" 
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
	-@erase "$(OUTDIR)\RemoteObjectKit_sd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\net" /I "..\..\..\include\remote" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RemoteObjectKitStatic.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\RemoteObjectKit_sd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractDistributedApplication.obj" \
	"$(INTDIR)\ClassRegistryEntry.obj" \
	"$(INTDIR)\ClassServerInstance.obj" \
	"$(INTDIR)\DistributedClassRegistry.obj" \
	"$(INTDIR)\DistributedException.obj" \
	"$(INTDIR)\InstanceID.obj" \
	"$(INTDIR)\Proxy.obj" \
	"$(INTDIR)\RemoteObjectKit.obj" \
	"$(OUTDIR)\FoundationKit_sd.lib" \
	"$(OUTDIR)\NetworkKit_sd.lib"

"$(OUTDIR)\RemoteObjectKit_sd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("RemoteObjectKitStatic.dep")
!INCLUDE "RemoteObjectKitStatic.dep"
!ELSE 
!MESSAGE Warning: cannot find "RemoteObjectKitStatic.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "RemoteObjectKitStatic - Win32 Release" || "$(CFG)" == "RemoteObjectKitStatic - Win32 Debug"
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


!IF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Release"

"FoundationKit - Win32 Release" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" 
   cd "..\REMOTEOBJECTKIT"

"FoundationKit - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\REMOTEOBJECTKIT"

!ELSEIF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Debug"

"FoundationKit - Win32 Debug" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" 
   cd "..\REMOTEOBJECTKIT"

"FoundationKit - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\REMOTEOBJECTKIT"

!ENDIF 

!IF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Release"

"NetworkKit - Win32 Release" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Release" 
   cd "..\REMOTEOBJECTKIT"

"NetworkKit - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\REMOTEOBJECTKIT"

!ELSEIF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Debug"

"NetworkKit - Win32 Debug" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Debug" 
   cd "..\REMOTEOBJECTKIT"

"NetworkKit - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\REMOTEOBJECTKIT"

!ENDIF 


!ENDIF 

