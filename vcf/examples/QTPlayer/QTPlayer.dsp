# Microsoft Developer Studio Project File - Name="QTPlayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=QTPlayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QTPlayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QTPlayer.mak" CFG="QTPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QTPlayer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "QTPlayer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QTPlayer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc6\Release\"
# PROP Intermediate_Dir "vc6\Release\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /I "$(QTDevWin_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "NO_MFC" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"vc6/Release/QTPlayer_vc6.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib qtmlclient.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /out:"QTPlayer_vc6.exe" /libpath:"$(VCF_LIB)" /libpath:"$(QTDevWin_LIB)"
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "QTPlayer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc6\Debug\"
# PROP Intermediate_Dir "vc6\Debug\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "NO_MFC" /D "USE_FOUNDATIONKIT_DLL" /D "USE_GRAPHICSKIT_DLL" /D "USE_APPLICATIONKIT_DLL" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"vc6/Debug/QTPlayer_vc6.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib qtmlclient.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"QTPlayer_vc6.exe" /pdbtype:sept /libpath:"$(VCF_LIB)"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "QTPlayer - Win32 Release"
# Name "QTPlayer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=MainWindow.cpp
# End Source File
# Begin Source File

SOURCE=QTPlayer.cpp
# End Source File
# Begin Source File

SOURCE=QTPlayerAbout.cpp
# End Source File
# Begin Source File

SOURCE=QTPlayerApplication.cpp
# End Source File
# Begin Source File

SOURCE=QTResFile.rc
# End Source File
# Begin Source File

SOURCE=QuickTimeControl.cpp
# End Source File
# Begin Source File

SOURCE=QuickTimeMovie.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=MainWindow.h
# End Source File
# Begin Source File

SOURCE=QTPlayerAbout.h
# End Source File
# Begin Source File

SOURCE=QTPlayerApplication.h
# End Source File
# Begin Source File

SOURCE=QuickTimeControl.h
# End Source File
# Begin Source File

SOURCE=QuickTimeMovie.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=fullvol.bmp
# End Source File
# Begin Source File

SOURCE=mute.bmp
# End Source File
# Begin Source File

SOURCE=open.bmp
# End Source File
# Begin Source File

SOURCE=pause.bmp
# End Source File
# Begin Source File

SOURCE=play.bmp
# End Source File
# Begin Source File

SOURCE=QTLogo.bmp
# End Source File
# Begin Source File

SOURCE=reset.bmp
# End Source File
# Begin Source File

SOURCE=search.bmp
# End Source File
# Begin Source File

SOURCE=stop.bmp
# End Source File
# Begin Source File

SOURCE=view-half.bmp
# End Source File
# Begin Source File

SOURCE=view-normal.bmp
# End Source File
# Begin Source File

SOURCE=view200.bmp
# End Source File
# End Group
# End Target
# End Project
