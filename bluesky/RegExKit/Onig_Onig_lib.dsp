# Microsoft Developer Studio Project File - Name="Onig_Onig_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Onig_lib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Onig_Onig_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Onig_Onig_lib.mak" CFG="Onig_lib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Onig_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Onig_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Onig_lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_d"
# PROP BASE Intermediate_Dir "msvc6prj_d\Onig_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_d"
# PROP Intermediate_Dir "msvc6prj_d\Onig_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "." /Zi /Gm /GZ /Fdmsvc6prj_d\Onig_lib.pdb /Od /GR /EHsc /W1 /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D ONIG_EXTERN=extern /c
# ADD CPP /nologo /FD /MDd /I "." /Zi /Gm /GZ /Fdmsvc6prj_d\Onig_lib.pdb /Od /GR /EHsc /W1 /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D ONIG_EXTERN=extern /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_d\Onig_lib.lib"
# ADD LIB32 /nologo /out:"msvc6prj_d\Onig_lib.lib"

!ELSEIF  "$(CFG)" == "Onig_lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj"
# PROP BASE Intermediate_Dir "msvc6prj\Onig_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj"
# PROP Intermediate_Dir "msvc6prj\Onig_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "." /Fdmsvc6prj\Onig_lib.pdb /O2 /GR /EHsc /W1 /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D ONIG_EXTERN=extern /c
# ADD CPP /nologo /FD /MD /I "." /Fdmsvc6prj\Onig_lib.pdb /O2 /GR /EHsc /W1 /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D ONIG_EXTERN=extern /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj\Onig_lib.lib"
# ADD LIB32 /nologo /out:"msvc6prj\Onig_lib.lib"

!ENDIF

# Begin Target

# Name "Onig_lib - Win32 Debug"
# Name "Onig_lib - Win32 Release"
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

