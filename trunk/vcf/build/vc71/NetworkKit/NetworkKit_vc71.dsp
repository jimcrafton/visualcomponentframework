# Microsoft Developer Studio Project File - Name="NetworkKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=NetworkKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NetworkKit.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NetworkKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc71\ReleaseS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "BUILD_NETWORKKIT_LIB" /Yu"vcf/NetworkKit/NetworkKit.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/NetworkKit_vc71_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/NetworkKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "NetworkKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc71\DebugS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "BUILD_NETWORKKIT_LIB" /Fd"..\..\..\lib\NetworkKit_vc71_sd.pdb" /Yu"vcf/NetworkKit/NetworkKit.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/NetworkKit_vc71_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/NetworkKit_vc71_sd.lib"

!ENDIF 

# Begin Target

# Name "NetworkKit - Win32 Release"
# Name "NetworkKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\DatagramSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetToolkit.cpp
# ADD CPP /Yc"vcf/NetworkKit/NetworkKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\ServerSocketEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Socket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketListeningLoop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\URL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32DatagramSocketPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32SocketPeer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\DatagramSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\NetworkKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\ServerSocketEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Socket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketListeningLoop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\SocketPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\URL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32DatagramSocketPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\NetworkKit\Win32SocketPeer.h
# End Source File
# End Group
# End Target
# End Project
