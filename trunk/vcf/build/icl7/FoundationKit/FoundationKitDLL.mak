# Microsoft Developer Studio Generated NMAKE File, Based on FoundationKitDLL.dsp
!IF "$(CFG)" == ""
CFG=FOUNDATIONKITDLL - WIN32 DEBUG
!MESSAGE No configuration specified. Defaulting to FOUNDATIONKITDLL - WIN32 DEBUG.
!ENDIF 

!IF "$(CFG)" != "FoundationKitDLL - Win32 Release" && "$(CFG)" != "FoundationKitDLL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FoundationKitDLL.mak" CFG="FOUNDATIONKITDLL - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FoundationKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FoundationKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FoundationKitDLL - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\ReleaseDLL\obj

ALL : "..\..\..\bin\FoundationKit.dll"


CLEAN :
	-@erase "$(INTDIR)\BasicException.obj"
	-@erase "$(INTDIR)\BasicInputStream.obj"
	-@erase "$(INTDIR)\BasicOutputStream.obj"
	-@erase "$(INTDIR)\Class.obj"
	-@erase "$(INTDIR)\ClassRegistry.obj"
	-@erase "$(INTDIR)\Directory.obj"
	-@erase "$(INTDIR)\ErrorLog.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\EventHandler.obj"
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\FileStream.obj"
	-@erase "$(INTDIR)\FileUtils.obj"
	-@erase "$(INTDIR)\FoundationKit.obj"
	-@erase "$(INTDIR)\FoundationKitDLL.pch"
	-@erase "$(INTDIR)\InterfaceClass.obj"
	-@erase "$(INTDIR)\Library.obj"
	-@erase "$(INTDIR)\Locales.obj"
	-@erase "$(INTDIR)\MemoryStream.obj"
	-@erase "$(INTDIR)\Mutex.obj"
	-@erase "$(INTDIR)\Object.obj"
	-@erase "$(INTDIR)\ObjectWithEvents.obj"
	-@erase "$(INTDIR)\Parser.obj"
	-@erase "$(INTDIR)\Point.obj"
	-@erase "$(INTDIR)\PropertyChangeEvent.obj"
	-@erase "$(INTDIR)\Rect.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Stream.obj"
	-@erase "$(INTDIR)\StringUtils.obj"
	-@erase "$(INTDIR)\System.obj"
	-@erase "$(INTDIR)\SystemToolkit.obj"
	-@erase "$(INTDIR)\TextInputStream.obj"
	-@erase "$(INTDIR)\TextOutputStream.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ThreadEvent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VCFMath.obj"
	-@erase "$(INTDIR)\VCFProcess.obj"
	-@erase "$(INTDIR)\Win32FilePeer.obj"
	-@erase "$(INTDIR)\Win32FileStream.obj"
	-@erase "$(INTDIR)\Win32LibraryPeer.obj"
	-@erase "$(INTDIR)\Win32Mutex.obj"
	-@erase "$(INTDIR)\Win32Peer.obj"
	-@erase "$(INTDIR)\Win32ProcessPeer.obj"
	-@erase "$(INTDIR)\Win32Registry.obj"
	-@erase "$(INTDIR)\Win32SystemPeer.obj"
	-@erase "$(INTDIR)\Win32Thread.obj"
	-@erase "$(INTDIR)\XMLParser.obj"
	-@erase "$(OUTDIR)\FoundationKit.exp"
	-@erase "$(OUTDIR)\FoundationKit.lib"
	-@erase "..\..\..\bin\FoundationKit.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\Implementer" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "FRAMEWORK_EXPORTS" /Fp"$(INTDIR)\FoundationKitDLL.pch" /Yu"FoundationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FoundationKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\FoundationKit.pdb" /machine:I386 /out:"..\..\..\bin/FoundationKit.dll" /implib:"$(OUTDIR)\FoundationKit.lib" 
LINK32_OBJS= \
	"$(INTDIR)\BasicException.obj" \
	"$(INTDIR)\BasicInputStream.obj" \
	"$(INTDIR)\BasicOutputStream.obj" \
	"$(INTDIR)\Class.obj" \
	"$(INTDIR)\ClassRegistry.obj" \
	"$(INTDIR)\Directory.obj" \
	"$(INTDIR)\ErrorLog.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\EventHandler.obj" \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\FileStream.obj" \
	"$(INTDIR)\FileUtils.obj" \
	"$(INTDIR)\FoundationKit.obj" \
	"$(INTDIR)\InterfaceClass.obj" \
	"$(INTDIR)\Library.obj" \
	"$(INTDIR)\Locales.obj" \
	"$(INTDIR)\MemoryStream.obj" \
	"$(INTDIR)\Mutex.obj" \
	"$(INTDIR)\Object.obj" \
	"$(INTDIR)\ObjectWithEvents.obj" \
	"$(INTDIR)\Parser.obj" \
	"$(INTDIR)\Point.obj" \
	"$(INTDIR)\PropertyChangeEvent.obj" \
	"$(INTDIR)\Rect.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Stream.obj" \
	"$(INTDIR)\StringUtils.obj" \
	"$(INTDIR)\System.obj" \
	"$(INTDIR)\SystemToolkit.obj" \
	"$(INTDIR)\TextInputStream.obj" \
	"$(INTDIR)\TextOutputStream.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\ThreadEvent.obj" \
	"$(INTDIR)\VCFMath.obj" \
	"$(INTDIR)\VCFProcess.obj" \
	"$(INTDIR)\Win32FilePeer.obj" \
	"$(INTDIR)\Win32FileStream.obj" \
	"$(INTDIR)\Win32LibraryPeer.obj" \
	"$(INTDIR)\Win32Mutex.obj" \
	"$(INTDIR)\Win32Peer.obj" \
	"$(INTDIR)\Win32ProcessPeer.obj" \
	"$(INTDIR)\Win32Registry.obj" \
	"$(INTDIR)\Win32SystemPeer.obj" \
	"$(INTDIR)\Win32Thread.obj" \
	"$(INTDIR)\XMLParser.obj"

"..\..\..\bin\FoundationKit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FoundationKitDLL - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugDLL\obj

ALL : "..\..\..\bin\FoundationKit_d.dll"


CLEAN :
	-@erase "$(INTDIR)\BasicException.obj"
	-@erase "$(INTDIR)\BasicInputStream.obj"
	-@erase "$(INTDIR)\BasicOutputStream.obj"
	-@erase "$(INTDIR)\Class.obj"
	-@erase "$(INTDIR)\ClassRegistry.obj"
	-@erase "$(INTDIR)\Directory.obj"
	-@erase "$(INTDIR)\ErrorLog.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\EventHandler.obj"
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\FileStream.obj"
	-@erase "$(INTDIR)\FileUtils.obj"
	-@erase "$(INTDIR)\FoundationKit.obj"
	-@erase "$(INTDIR)\FoundationKitDLL.pch"
	-@erase "$(INTDIR)\InterfaceClass.obj"
	-@erase "$(INTDIR)\Library.obj"
	-@erase "$(INTDIR)\Locales.obj"
	-@erase "$(INTDIR)\MemoryStream.obj"
	-@erase "$(INTDIR)\Mutex.obj"
	-@erase "$(INTDIR)\Object.obj"
	-@erase "$(INTDIR)\ObjectWithEvents.obj"
	-@erase "$(INTDIR)\Parser.obj"
	-@erase "$(INTDIR)\Point.obj"
	-@erase "$(INTDIR)\PropertyChangeEvent.obj"
	-@erase "$(INTDIR)\Rect.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Stream.obj"
	-@erase "$(INTDIR)\StringUtils.obj"
	-@erase "$(INTDIR)\System.obj"
	-@erase "$(INTDIR)\SystemToolkit.obj"
	-@erase "$(INTDIR)\TextInputStream.obj"
	-@erase "$(INTDIR)\TextOutputStream.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ThreadEvent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VCFMath.obj"
	-@erase "$(INTDIR)\VCFProcess.obj"
	-@erase "$(INTDIR)\Win32FilePeer.obj"
	-@erase "$(INTDIR)\Win32FileStream.obj"
	-@erase "$(INTDIR)\Win32LibraryPeer.obj"
	-@erase "$(INTDIR)\Win32Mutex.obj"
	-@erase "$(INTDIR)\Win32Peer.obj"
	-@erase "$(INTDIR)\Win32ProcessPeer.obj"
	-@erase "$(INTDIR)\Win32Registry.obj"
	-@erase "$(INTDIR)\Win32SystemPeer.obj"
	-@erase "$(INTDIR)\Win32Thread.obj"
	-@erase "$(INTDIR)\XMLParser.obj"
	-@erase "$(OUTDIR)\FoundationKit_d.exp"
	-@erase "$(OUTDIR)\FoundationKit_d.lib"
	-@erase "..\..\..\bin\FoundationKit_d.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\Implementer" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "FRAMEWORK_EXPORTS" /Fp"$(INTDIR)\FoundationKitDLL.pch" /Yu"FoundationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FoundationKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /debug /machine:I386 /out:"..\..\..\bin/FoundationKit_d.dll" /implib:"$(OUTDIR)\FoundationKit_d.lib" 
LINK32_OBJS= \
	"$(INTDIR)\BasicException.obj" \
	"$(INTDIR)\BasicInputStream.obj" \
	"$(INTDIR)\BasicOutputStream.obj" \
	"$(INTDIR)\Class.obj" \
	"$(INTDIR)\ClassRegistry.obj" \
	"$(INTDIR)\Directory.obj" \
	"$(INTDIR)\ErrorLog.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\EventHandler.obj" \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\FileStream.obj" \
	"$(INTDIR)\FileUtils.obj" \
	"$(INTDIR)\FoundationKit.obj" \
	"$(INTDIR)\InterfaceClass.obj" \
	"$(INTDIR)\Library.obj" \
	"$(INTDIR)\Locales.obj" \
	"$(INTDIR)\MemoryStream.obj" \
	"$(INTDIR)\Mutex.obj" \
	"$(INTDIR)\Object.obj" \
	"$(INTDIR)\ObjectWithEvents.obj" \
	"$(INTDIR)\Parser.obj" \
	"$(INTDIR)\Point.obj" \
	"$(INTDIR)\PropertyChangeEvent.obj" \
	"$(INTDIR)\Rect.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Stream.obj" \
	"$(INTDIR)\StringUtils.obj" \
	"$(INTDIR)\System.obj" \
	"$(INTDIR)\SystemToolkit.obj" \
	"$(INTDIR)\TextInputStream.obj" \
	"$(INTDIR)\TextOutputStream.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\ThreadEvent.obj" \
	"$(INTDIR)\VCFMath.obj" \
	"$(INTDIR)\VCFProcess.obj" \
	"$(INTDIR)\Win32FilePeer.obj" \
	"$(INTDIR)\Win32FileStream.obj" \
	"$(INTDIR)\Win32LibraryPeer.obj" \
	"$(INTDIR)\Win32Mutex.obj" \
	"$(INTDIR)\Win32Peer.obj" \
	"$(INTDIR)\Win32ProcessPeer.obj" \
	"$(INTDIR)\Win32Registry.obj" \
	"$(INTDIR)\Win32SystemPeer.obj" \
	"$(INTDIR)\Win32Thread.obj" \
	"$(INTDIR)\XMLParser.obj"

"..\..\..\bin\FoundationKit_d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FoundationKitDLL.dep")
!INCLUDE "FoundationKitDLL.dep"
!ELSE 
!MESSAGE Warning: cannot find "FoundationKitDLL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FoundationKitDLL - Win32 Release" || "$(CFG)" == "FoundationKitDLL - Win32 Debug"
SOURCE=..\..\..\src\Exceptions\BasicException.cpp

"$(INTDIR)\BasicException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\BasicInputStream.cpp

"$(INTDIR)\BasicInputStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\BasicOutputStream.cpp

"$(INTDIR)\BasicOutputStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Class.cpp

"$(INTDIR)\Class.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ClassRegistry.cpp

"$(INTDIR)\ClassRegistry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\Directory.cpp

"$(INTDIR)\Directory.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\ErrorLog.cpp

"$(INTDIR)\ErrorLog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\Event.cpp

"$(INTDIR)\Event.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\EventHandler.cpp

"$(INTDIR)\EventHandler.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\io\File.cpp

"$(INTDIR)\File.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\FileStream.cpp

"$(INTDIR)\FileStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\FileUtils.cpp

"$(INTDIR)\FileUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\FoundationKit.cpp

!IF  "$(CFG)" == "FoundationKitDLL - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\Implementer" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "FRAMEWORK_EXPORTS" /Fp"$(INTDIR)\FoundationKitDLL.pch" /Yc"FoundationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\FoundationKit.obj"	"$(INTDIR)\FoundationKitDLL.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FoundationKitDLL - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\Implementer" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "FRAMEWORK_EXPORTS" /Fp"$(INTDIR)\FoundationKitDLL.pch" /Yc"FoundationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\FoundationKit.obj"	"$(INTDIR)\FoundationKitDLL.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\src\core\InterfaceClass.cpp

"$(INTDIR)\InterfaceClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\utils\Library.cpp

"$(INTDIR)\Library.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Locales.cpp

"$(INTDIR)\Locales.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\MemoryStream.cpp

"$(INTDIR)\MemoryStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\Mutex.cpp

"$(INTDIR)\Mutex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Object.cpp

"$(INTDIR)\Object.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ObjectWithEvents.cpp

"$(INTDIR)\ObjectWithEvents.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\Parser.cpp

"$(INTDIR)\Parser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Point.cpp

"$(INTDIR)\Point.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\PropertyChangeEvent.cpp

"$(INTDIR)\PropertyChangeEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Rect.cpp

"$(INTDIR)\Rect.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\Registry.cpp

"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\Stream.cpp

"$(INTDIR)\Stream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\StringUtils.cpp

"$(INTDIR)\StringUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\System.cpp

"$(INTDIR)\System.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\utils\SystemToolkit.cpp

"$(INTDIR)\SystemToolkit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\TextInputStream.cpp

"$(INTDIR)\TextInputStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\TextOutputStream.cpp

"$(INTDIR)\TextOutputStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\Thread.cpp

"$(INTDIR)\Thread.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ThreadEvent.cpp

"$(INTDIR)\ThreadEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\VCFMath.cpp

"$(INTDIR)\VCFMath.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\VCFProcess.cpp

"$(INTDIR)\VCFProcess.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FilePeer.cpp

"$(INTDIR)\Win32FilePeer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FileStream.cpp

"$(INTDIR)\Win32FileStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\implementerkit\Win32LibraryPeer.cpp

"$(INTDIR)\Win32LibraryPeer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Mutex.cpp

"$(INTDIR)\Win32Mutex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Peer.cpp

"$(INTDIR)\Win32Peer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\implementerkit\Win32ProcessPeer.cpp

"$(INTDIR)\Win32ProcessPeer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\implementerkit\Win32Registry.cpp

"$(INTDIR)\Win32Registry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32SystemPeer.cpp

"$(INTDIR)\Win32SystemPeer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Thread.cpp

"$(INTDIR)\Win32Thread.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\XMLParser.cpp

"$(INTDIR)\XMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FoundationKitDLL.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

