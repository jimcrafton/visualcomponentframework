# Microsoft Developer Studio Generated NMAKE File, Based on vcfAllStaticLibs.dsp
!IF "$(CFG)" == ""
CFG=vcfAllStaticLibs - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vcfAllStaticLibs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vcfAllStaticLibs - Win32 Release" && "$(CFG)" != "vcfAllStaticLibs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vcfAllStaticLibs.mak" CFG="vcfAllStaticLibs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vcfAllStaticLibs - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "vcfAllStaticLibs - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : 

!ELSE 

ALL : "RemoteObjectKitStatic - Win32 Release" "NetworkKit - Win32 Release" "GraphicsKit - Win32 Release" "FoundationKit - Win32 Release" "ApplicationKit - Win32 Release" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ApplicationKit - Win32 ReleaseCLEAN" "FoundationKit - Win32 ReleaseCLEAN" "GraphicsKit - Win32 ReleaseCLEAN" "NetworkKit - Win32 ReleaseCLEAN" "RemoteObjectKitStatic - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!IF  "$(CFG)" == "vcfAllStaticLibs - Win32 Release"

MTL=midl.exe
MTL_PROJ=

!ELSEIF  "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

MTL=midl.exe
MTL_PROJ=

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("vcfAllStaticLibs.dep")
!INCLUDE "vcfAllStaticLibs.dep"
!ELSE 
!MESSAGE Warning: cannot find "vcfAllStaticLibs.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vcfAllStaticLibs - Win32 Release" || "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

!IF  "$(CFG)" == "vcfAllStaticLibs - Win32 Release"

"ApplicationKit - Win32 Release" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKit.mak CFG="ApplicationKit - Win32 Release" 
   cd ".."

"ApplicationKit - Win32 ReleaseCLEAN" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKit.mak CFG="ApplicationKit - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

"ApplicationKit - Win32 Debug" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKit.mak CFG="ApplicationKit - Win32 Debug" 
   cd ".."

"ApplicationKit - Win32 DebugCLEAN" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKit.mak CFG="ApplicationKit - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAllStaticLibs - Win32 Release"

"FoundationKit - Win32 Release" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" 
   cd ".."

"FoundationKit - Win32 ReleaseCLEAN" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

"FoundationKit - Win32 Debug" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" 
   cd ".."

"FoundationKit - Win32 DebugCLEAN" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAllStaticLibs - Win32 Release"

"GraphicsKit - Win32 Release" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Release" 
   cd ".."

"GraphicsKit - Win32 ReleaseCLEAN" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

"GraphicsKit - Win32 Debug" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Debug" 
   cd ".."

"GraphicsKit - Win32 DebugCLEAN" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAllStaticLibs - Win32 Release"

"NetworkKit - Win32 Release" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Release" 
   cd ".."

"NetworkKit - Win32 ReleaseCLEAN" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

"NetworkKit - Win32 Debug" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Debug" 
   cd ".."

"NetworkKit - Win32 DebugCLEAN" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKit.mak CFG="NetworkKit - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAllStaticLibs - Win32 Release"

"RemoteObjectKitStatic - Win32 Release" : 
   cd ".\REMOTEOBJECTKIT"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKitStatic.mak CFG="RemoteObjectKitStatic - Win32 Release" 
   cd ".."

"RemoteObjectKitStatic - Win32 ReleaseCLEAN" : 
   cd ".\REMOTEOBJECTKIT"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKitStatic.mak CFG="RemoteObjectKitStatic - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAllStaticLibs - Win32 Debug"

"RemoteObjectKitStatic - Win32 Debug" : 
   cd ".\REMOTEOBJECTKIT"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKitStatic.mak CFG="RemoteObjectKitStatic - Win32 Debug" 
   cd ".."

"RemoteObjectKitStatic - Win32 DebugCLEAN" : 
   cd ".\REMOTEOBJECTKIT"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKitStatic.mak CFG="RemoteObjectKitStatic - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

