# Microsoft Developer Studio Project File - Name="Onig_Onig_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Onig_dll - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Onig_Onig_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Onig_Onig_dll.mak" CFG="Onig_dll - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Onig_dll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Onig_dll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Onig_dll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_d"
# PROP BASE Intermediate_Dir "msvc6prj_d\Onig_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_d"
# PROP Intermediate_Dir "msvc6prj_d\Onig_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "." /Zi /Gm /GZ /Fdmsvc6prj_d\Onig_dll.pdb /Od /GR /EHsc /W1 /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /c
# ADD CPP /nologo /FD /MDd /I "." /Zi /Gm /GZ /Fdmsvc6prj_d\Onig_dll.pdb /Od /GR /EHsc /W1 /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "." /d "NOT_RUBY" /d "_DEBUG" /d "_DEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d EXPORT
# ADD RSC /l 0x409 /i "." /d "NOT_RUBY" /d "_DEBUG" /d "_DEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d EXPORT
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"msvc6prj_d\Onig_dll.dll" /implib:"msvc6prj_d\Onig_dll.lib" /debug
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"msvc6prj_d\Onig_dll.dll" /implib:"msvc6prj_d\Onig_dll.lib" /debug

!ELSEIF  "$(CFG)" == "Onig_dll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj"
# PROP BASE Intermediate_Dir "msvc6prj\Onig_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj"
# PROP Intermediate_Dir "msvc6prj\Onig_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "." /Fdmsvc6prj\Onig_dll.pdb /O2 /GR /EHsc /W1 /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /c
# ADD CPP /nologo /FD /MD /I "." /Fdmsvc6prj\Onig_dll.pdb /O2 /GR /EHsc /W1 /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NOT_RUBY" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "EXPORT" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "." /d "NOT_RUBY" /d "NDEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d EXPORT
# ADD RSC /l 0x409 /i "." /d "NOT_RUBY" /d "NDEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d EXPORT
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"msvc6prj\Onig_dll.dll" /implib:"msvc6prj\Onig_dll.lib"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"msvc6prj\Onig_dll.dll" /implib:"msvc6prj\Onig_dll.lib"

!ENDIF

# Begin Target

# Name "Onig_dll - Win32 Debug"
# Name "Onig_dll - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\enc\ascii.c
# End Source File
# Begin Source File

SOURCE=.\enc\big5.c
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

SOURCE=.\regcomp.c
# End Source File
# Begin Source File

SOURCE=.\regenc.c
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

SOURCE=.\regparse.c
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
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\config.h
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

SOURCE=.\regenc.h
# End Source File
# Begin Source File

SOURCE=.\regint.h
# End Source File
# Begin Source File

SOURCE=.\regparse.h
# End Source File
# Begin Source File

SOURCE=.\st.h
# End Source File
# End Group
# End Target
# End Project

