# Microsoft Developer Studio Generated NMAKE File, Based on vcfAll.dsp
!IF "$(CFG)" == ""
CFG=vcfAll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vcfAll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vcfAll - Win32 Release" && "$(CFG)" != "vcfAll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vcfAll.mak" CFG="vcfAll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vcfAll - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "vcfAll - Win32 Debug" (based on "Win32 (x86) Generic Project")
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

ALL : "RemoteObjectKit - Win32 Release" "NetworkKitDLL - Win32 Release" "GraphicsKitDLL - Win32 Release" "FoundationKitDLL - Win32 Release" "ApplicationKitDLL - Win32 Release" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ApplicationKitDLL - Win32 ReleaseCLEAN" "FoundationKitDLL - Win32 ReleaseCLEAN" "GraphicsKitDLL - Win32 ReleaseCLEAN" "NetworkKitDLL - Win32 ReleaseCLEAN" "RemoteObjectKit - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!IF  "$(CFG)" == "vcfAll - Win32 Release"

MTL=midl.exe
MTL_PROJ=

!ELSEIF  "$(CFG)" == "vcfAll - Win32 Debug"

MTL=midl.exe
MTL_PROJ=

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("vcfAll.dep")
!INCLUDE "vcfAll.dep"
!ELSE 
!MESSAGE Warning: cannot find "vcfAll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vcfAll - Win32 Release" || "$(CFG)" == "vcfAll - Win32 Debug"

!IF  "$(CFG)" == "vcfAll - Win32 Release"

"ApplicationKitDLL - Win32 Release" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKitDLL.mak CFG="ApplicationKitDLL - Win32 Release" 
   cd ".."

"ApplicationKitDLL - Win32 ReleaseCLEAN" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKitDLL.mak CFG="ApplicationKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAll - Win32 Debug"

"ApplicationKitDLL - Win32 Debug" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKitDLL.mak CFG="ApplicationKitDLL - Win32 Debug" 
   cd ".."

"ApplicationKitDLL - Win32 DebugCLEAN" : 
   cd ".\ApplicationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\ApplicationKitDLL.mak CFG="ApplicationKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAll - Win32 Release"

"FoundationKitDLL - Win32 Release" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Release" 
   cd ".."

"FoundationKitDLL - Win32 ReleaseCLEAN" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAll - Win32 Debug"

"FoundationKitDLL - Win32 Debug" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Debug" 
   cd ".."

"FoundationKitDLL - Win32 DebugCLEAN" : 
   cd ".\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKitDLL.mak CFG="FoundationKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAll - Win32 Release"

"GraphicsKitDLL - Win32 Release" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKitDLL.mak CFG="GraphicsKitDLL - Win32 Release" 
   cd ".."

"GraphicsKitDLL - Win32 ReleaseCLEAN" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKitDLL.mak CFG="GraphicsKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAll - Win32 Debug"

"GraphicsKitDLL - Win32 Debug" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKitDLL.mak CFG="GraphicsKitDLL - Win32 Debug" 
   cd ".."

"GraphicsKitDLL - Win32 DebugCLEAN" : 
   cd ".\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKitDLL.mak CFG="GraphicsKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAll - Win32 Release"

"NetworkKitDLL - Win32 Release" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Release" 
   cd ".."

"NetworkKitDLL - Win32 ReleaseCLEAN" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAll - Win32 Debug"

"NetworkKitDLL - Win32 Debug" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Debug" 
   cd ".."

"NetworkKitDLL - Win32 DebugCLEAN" : 
   cd ".\NetworkKit"
   $(MAKE) /$(MAKEFLAGS) /F .\NetworkKitDLL.mak CFG="NetworkKitDLL - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "vcfAll - Win32 Release"

"RemoteObjectKit - Win32 Release" : 
   cd ".\RemoteObjectKit"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKit.mak CFG="RemoteObjectKit - Win32 Release" 
   cd ".."

"RemoteObjectKit - Win32 ReleaseCLEAN" : 
   cd ".\RemoteObjectKit"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKit.mak CFG="RemoteObjectKit - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "vcfAll - Win32 Debug"

"RemoteObjectKit - Win32 Debug" : 
   cd ".\RemoteObjectKit"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKit.mak CFG="RemoteObjectKit - Win32 Debug" 
   cd ".."

"RemoteObjectKit - Win32 DebugCLEAN" : 
   cd ".\RemoteObjectKit"
   $(MAKE) /$(MAKEFLAGS) /F .\RemoteObjectKit.mak CFG="RemoteObjectKit - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

