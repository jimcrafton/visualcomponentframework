# Microsoft Developer Studio Project File - Name="TeXLabel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TeXLabel - Win32 Generate YY and LL files
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TeXLabel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TeXLabel.mak" CFG="TeXLabel - Win32 Generate YY and LL files"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TeXLabel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TeXLabel - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "TeXLabel - Win32 Generate YY and LL files" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\"
# PROP Intermediate_Dir "Release\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /out:"Release\TeXLabel_vc71.exe" /libpath:"$(VCF_LIB)"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\"
# PROP Intermediate_Dir "Debug\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"Debug\TeXLabel_vc71.exe" /pdbtype:sept /libpath:"$(VCF_LIB)"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TeXLabel___Win32_Generate_YY_and_LL_files"
# PROP BASE Intermediate_Dir "TeXLabel___Win32_Generate_YY_and_LL_files"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TeXLabel___Win32_Generate_YY_and_LL_files\"
# PROP Intermediate_Dir "TeXLabel___Win32_Generate_YY_and_LL_files\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(VCF_LIB)"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /out:"TeXLabel___Win32_Generate_YY_and_LL_files\TeXLabel_vc71.exe" /pdbtype:sept /libpath:"$(VCF_LIB)"

!ENDIF 

# Begin Target

# Name "TeXLabel - Win32 Release"
# Name "TeXLabel - Win32 Debug"
# Name "TeXLabel - Win32 Generate YY and LL files"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=TeXLabel.cpp

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=TeXTypes.cpp

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=TeXLabel.hpp
# End Source File
# Begin Source File

SOURCE=TeXTypes.hpp
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=readme.txt
# End Source File
# Begin Source File

SOURCE=TeXLabel.ll

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

USERDEP__TEXLA="TeXLabel.tab.hpp"	
# Begin Custom Build
InputPath=.\TeXLabel.ll
InputName=TeXLabel

"$(InputName).scan.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -o$(InputName).scan.cpp  $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=TeXLabel.scan.cpp

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=TeXLabel.tab.cpp

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=TeXLabel.yy

!IF  "$(CFG)" == "TeXLabel - Win32 Release"

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TeXLabel - Win32 Generate YY and LL files"

# Begin Custom Build
InputPath=.\TeXLabel.yy
InputName=TeXLabel

BuildCmds= \
	bison -d $(InputPath) \
	move $(InputName).tab.cc $(InputName).tab.cpp \
	move $(InputName).tab.hh $(InputName).tab.hpp \
	

"TeXLabel.tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TeXLabel.tab.hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
