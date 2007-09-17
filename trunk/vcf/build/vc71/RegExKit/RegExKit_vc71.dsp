# Microsoft Developer Studio Project File - Name="RegExKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RegExKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RegExKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RegExKit.mak" CFG="RegExKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegExKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RegExKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "ReleaseLib\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/oniguruma" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "REGEXKIT_LIB" /D "NOT_RUBY" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D ONIG_EXTERN=extern /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\RegExKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "DebugLib\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/oniguruma" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "REGEXKIT_LIB" /D "NOT_RUBY" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D ONIG_EXTERN=extern /YX /FD /D /Fd"..\..\..\lib\RegExKit_vc71_sd.pdb" /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\RegExKit_vc71_sd.lib"

!ENDIF 

# Begin Target

# Name "RegExKit - Win32 Release"
# Name "RegExKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\RegExKit\RegExKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\RegExKit\RegExKit.h
# End Source File
# End Group
# Begin Group "Onig Reg Ex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\ascii.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\big5.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\euc_jp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\euc_kr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\euc_tw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\gb18030.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_10.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_11.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_13.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_14.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_15.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_16.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_3.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_4.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_5.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_6.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_7.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_8.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\iso8859_9.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\koi8.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\koi8_r.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\onig_cpp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\oniggnu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\onigposix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\oniguruma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regcomp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regenc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regenc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regerror.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regexec.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regext.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\reggnu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regparse.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regparse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regposerr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regposix.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regsyntax.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regtrav.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\regversion.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\sjis.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\st.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\st.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\unicode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\utf16_be.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\utf16_le.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\utf32_be.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\utf32_le.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\oniguruma\enc\utf8.c
# End Source File
# End Group
# End Target
# End Project
