# Microsoft Developer Studio Project File - Name="RemoteObjectKitStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RemoteObjectKitStatic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RemoteObjectKitStatic.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_NETKIT_LIB" /Yu"vcf/RemoteObjectKit/RemoteObjectKit.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/RemoteObjectKit_vc71_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/RemoteObjectKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKitStatic - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_NETKIT_LIB" /Fd"..\..\..\lib\RemoteObjectKit_vc71_sd.pdb" /Yu"vcf/RemoteObjectKit/RemoteObjectKit.h" /FD /GZ /c
# SUBTRACT CPP /FR
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/RemoteObjectKit_vc71_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/RemoteObjectKit_vc71_sd.lib"

!ENDIF 

# Begin Target

# Name "RemoteObjectKitStatic - Win32 Release"
# Name "RemoteObjectKitStatic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\AbstractDistributedApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassRegistryEntry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassServerInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedClassRegistry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\InstanceID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\Proxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteObjectKit.cpp
# ADD CPP /Yc"vcf/RemoteObjectKit/RemoteObjectKit.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\AbstractDistributedApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassRegistryEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassServerInstance.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedClassRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\InstanceID.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\Proxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteObjectKit.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
