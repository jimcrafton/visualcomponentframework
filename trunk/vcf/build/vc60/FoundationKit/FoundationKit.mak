# Microsoft Developer Studio Generated NMAKE File, Based on FoundationKit.dsp
!IF "$(CFG)" == ""
CFG=FoundationKit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FoundationKit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FoundationKit - Win32 Release" && "$(CFG)" != "FoundationKit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FoundationKit.mak" CFG="FoundationKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FoundationKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FoundationKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FoundationKit - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release\obj

ALL : "..\..\..\lib\FoundationKit.lib"


CLEAN :
	-@erase "$(INTDIR)\BasicException.obj"
	-@erase "$(INTDIR)\BasicInputStream.obj"
	-@erase "$(INTDIR)\BasicOutputStream.obj"
	-@erase "$(INTDIR)\Class.obj"
	-@erase "$(INTDIR)\ClassRegistry.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\FileStream.obj"
	-@erase "$(INTDIR)\FileUtils.obj"
	-@erase "$(INTDIR)\FoundationKit.obj"
	-@erase "$(INTDIR)\MemoryStream.obj"
	-@erase "$(INTDIR)\Object.obj"
	-@erase "$(INTDIR)\Point.obj"
	-@erase "$(INTDIR)\PropertyChangeEvent.obj"
	-@erase "$(INTDIR)\Rect.obj"
	-@erase "$(INTDIR)\Stream.obj"
	-@erase "$(INTDIR)\StringUtils.obj"
	-@erase "$(INTDIR)\TextInputStream.obj"
	-@erase "$(INTDIR)\TextOutputStream.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ThreadEvent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Win32FileStream.obj"
	-@erase "$(INTDIR)\Win32Peer.obj"
	-@erase "..\..\..\lib\FoundationKit.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /WX /GR /GX /O2 /I "..\..\..\include\COM" /I "..\..\..\include\Graphics" /I "..\..\..\include\Implementer" /I "..\..\..\include\DragDrop" /I "..\..\..\xml\include" /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\FoundationKit.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FoundationKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\lib\FoundationKit.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BasicException.obj" \
	"$(INTDIR)\BasicInputStream.obj" \
	"$(INTDIR)\BasicOutputStream.obj" \
	"$(INTDIR)\Class.obj" \
	"$(INTDIR)\ClassRegistry.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\FileStream.obj" \
	"$(INTDIR)\FileUtils.obj" \
	"$(INTDIR)\FoundationKit.obj" \
	"$(INTDIR)\MemoryStream.obj" \
	"$(INTDIR)\Object.obj" \
	"$(INTDIR)\Point.obj" \
	"$(INTDIR)\PropertyChangeEvent.obj" \
	"$(INTDIR)\Rect.obj" \
	"$(INTDIR)\Stream.obj" \
	"$(INTDIR)\StringUtils.obj" \
	"$(INTDIR)\TextInputStream.obj" \
	"$(INTDIR)\TextOutputStream.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\ThreadEvent.obj" \
	"$(INTDIR)\Win32FileStream.obj" \
	"$(INTDIR)\Win32Peer.obj"

"..\..\..\lib\FoundationKit.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FoundationKit - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug\obj

ALL : "..\..\..\lib\FoundationKit_d.lib"


CLEAN :
	-@erase "$(INTDIR)\BasicException.obj"
	-@erase "$(INTDIR)\BasicInputStream.obj"
	-@erase "$(INTDIR)\BasicOutputStream.obj"
	-@erase "$(INTDIR)\Class.obj"
	-@erase "$(INTDIR)\ClassRegistry.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\FileStream.obj"
	-@erase "$(INTDIR)\FileUtils.obj"
	-@erase "$(INTDIR)\FoundationKit.obj"
	-@erase "$(INTDIR)\MemoryStream.obj"
	-@erase "$(INTDIR)\Object.obj"
	-@erase "$(INTDIR)\Point.obj"
	-@erase "$(INTDIR)\PropertyChangeEvent.obj"
	-@erase "$(INTDIR)\Rect.obj"
	-@erase "$(INTDIR)\Stream.obj"
	-@erase "$(INTDIR)\StringUtils.obj"
	-@erase "$(INTDIR)\TextInputStream.obj"
	-@erase "$(INTDIR)\TextOutputStream.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ThreadEvent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Win32FileStream.obj"
	-@erase "$(INTDIR)\Win32Peer.obj"
	-@erase "..\..\..\lib\FoundationKit_d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GR /GX /ZI /Od /I "..\..\..\include\Core" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\Implementer" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FoundationKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\lib\FoundationKit_d.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BasicException.obj" \
	"$(INTDIR)\BasicInputStream.obj" \
	"$(INTDIR)\BasicOutputStream.obj" \
	"$(INTDIR)\Class.obj" \
	"$(INTDIR)\ClassRegistry.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\FileStream.obj" \
	"$(INTDIR)\FileUtils.obj" \
	"$(INTDIR)\FoundationKit.obj" \
	"$(INTDIR)\MemoryStream.obj" \
	"$(INTDIR)\Object.obj" \
	"$(INTDIR)\Point.obj" \
	"$(INTDIR)\PropertyChangeEvent.obj" \
	"$(INTDIR)\Rect.obj" \
	"$(INTDIR)\Stream.obj" \
	"$(INTDIR)\StringUtils.obj" \
	"$(INTDIR)\TextInputStream.obj" \
	"$(INTDIR)\TextOutputStream.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\ThreadEvent.obj" \
	"$(INTDIR)\Win32FileStream.obj" \
	"$(INTDIR)\Win32Peer.obj"

"..\..\..\lib\FoundationKit_d.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FoundationKit.dep")
!INCLUDE "FoundationKit.dep"
!ELSE 
!MESSAGE Warning: cannot find "FoundationKit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FoundationKit - Win32 Release" || "$(CFG)" == "FoundationKit - Win32 Debug"
SOURCE=..\..\..\src\Exceptions\BasicException.cpp

"$(INTDIR)\BasicException.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\BasicInputStream.cpp

"$(INTDIR)\BasicInputStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\BasicOutputStream.cpp

"$(INTDIR)\BasicOutputStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Core\Class.cpp

"$(INTDIR)\Class.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Core\ClassRegistry.cpp

"$(INTDIR)\ClassRegistry.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\Event.cpp

"$(INTDIR)\Event.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\FileStream.cpp

"$(INTDIR)\FileStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\io\FileUtils.cpp

"$(INTDIR)\FileUtils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\FoundationKit.cpp

"$(INTDIR)\FoundationKit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\MemoryStream.cpp

"$(INTDIR)\MemoryStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Core\Object.cpp

"$(INTDIR)\Object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Core\Point.cpp

"$(INTDIR)\Point.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\PropertyChangeEvent.cpp

"$(INTDIR)\PropertyChangeEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Core\Rect.cpp

"$(INTDIR)\Rect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\Stream.cpp

"$(INTDIR)\Stream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\StringUtils.cpp

"$(INTDIR)\StringUtils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\TextInputStream.cpp

"$(INTDIR)\TextInputStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\TextOutputStream.cpp

"$(INTDIR)\TextOutputStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\Thread.cpp

"$(INTDIR)\Thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\events\ThreadEvent.cpp

"$(INTDIR)\ThreadEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FileStream.cpp

"$(INTDIR)\Win32FileStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Peer.cpp

"$(INTDIR)\Win32Peer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

