# Microsoft Developer Studio Project File - Name="RegExKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RegExKitDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RegExKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RegExKitDLL.mak" CFG="RegExKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegExKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RegExKitDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RegExKitDLL___Win32_Release"
# PROP BASE Intermediate_Dir "RegExKitDLL___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RegExKitDLL___Win32_Release"
# PROP Intermediate_Dir "RegExKitDLL___Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "REGEXKIT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RegExKitDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "RegExKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RegExKitDLL___Win32_Debug"
# PROP BASE Intermediate_Dir "RegExKitDLL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../vcf/bin"
# PROP Intermediate_Dir "RegExKitDLL___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RegExKitDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "./" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FOUNDATIONKIT_DLL" /D "REGEXKIT_EXPORTS" /D "REGEXKIT_DLL" /D "NOT_RUBY" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../vcf/bin/RegExKit_vc6_d.dll" /implib:"../../vcf/lib/RegExKit_vc6_d.lib" /pdbtype:sept /libpath:"$(VCF_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "RegExKitDLL - Win32 Release"
# Name "RegExKitDLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\RegExKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\RegExKit.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Onig Reg Ex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\enc\ascii.c
# End Source File
# Begin Source File

SOURCE=.\enc\big5.c
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\enc\euc_jp.c
# End Source File
# Begin Source File

SOURCE=.\enc\euc_kr.c
# End Source File
# Begin Source File

SOURCE=.\enc\euc_tw.c
# End Source File
# Begin Source File

SOURCE=.\enc\gb18030.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_1.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_10.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_11.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_13.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_14.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_15.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_16.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_2.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_3.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_4.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_5.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_6.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_7.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_8.c
# End Source File
# Begin Source File

SOURCE=.\enc\iso8859_9.c
# End Source File
# Begin Source File

SOURCE=.\enc\koi8.c
# End Source File
# Begin Source File

SOURCE=.\enc\koi8_r.c
# End Source File
# Begin Source File

SOURCE=.\oniggnu.h
# End Source File
# Begin Source File

SOURCE=.\onigposix.h
# End Source File
# Begin Source File

SOURCE=.\oniguruma.h
# End Source File
# Begin Source File

SOURCE=.\regcomp.c
# End Source File
# Begin Source File

SOURCE=.\regenc.c
# End Source File
# Begin Source File

SOURCE=.\regenc.h
# End Source File
# Begin Source File

SOURCE=.\regerror.c
# End Source File
# Begin Source File

SOURCE=.\regexec.c
# End Source File
# Begin Source File

SOURCE=.\regext.c
# End Source File
# Begin Source File

SOURCE=.\reggnu.c
# End Source File
# Begin Source File

SOURCE=.\regint.h
# End Source File
# Begin Source File

SOURCE=.\regparse.c
# End Source File
# Begin Source File

SOURCE=.\regparse.h
# End Source File
# Begin Source File

SOURCE=.\regposerr.c
# End Source File
# Begin Source File

SOURCE=.\regposix.c
# End Source File
# Begin Source File

SOURCE=.\regsyntax.c
# End Source File
# Begin Source File

SOURCE=.\regtrav.c
# End Source File
# Begin Source File

SOURCE=.\regversion.c
# End Source File
# Begin Source File

SOURCE=.\enc\sjis.c
# End Source File
# Begin Source File

SOURCE=.\st.c
# End Source File
# Begin Source File

SOURCE=.\st.h
# End Source File
# Begin Source File

SOURCE=.\enc\unicode.c
# End Source File
# Begin Source File

SOURCE=.\enc\utf16_be.c
# End Source File
# Begin Source File

SOURCE=.\enc\utf16_le.c
# End Source File
# Begin Source File

SOURCE=.\enc\utf32_be.c
# End Source File
# Begin Source File

SOURCE=.\enc\utf32_le.c
# End Source File
# Begin Source File

SOURCE=.\enc\utf8.c
# End Source File
# End Group
# End Target
# End Project
