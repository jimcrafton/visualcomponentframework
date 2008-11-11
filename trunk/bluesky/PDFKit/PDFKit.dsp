# Microsoft Developer Studio Project File - Name="PDFKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PDFKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PDFKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PDFKit.mak" CFG="PDFKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PDFKit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PDFKit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PDFKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_CONSOLE" /D "USE_FOUNDATIONKIT_DLL" /FD /I$(VCF_ROOT)/src /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /subsystem:console /machine:I386 /libpath:$(VCF_ROOT)/lib

!ELSEIF  "$(CFG)" == "PDFKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\libharu\include" /I "$(VCF_ROOT)/thirdparty/common/ZLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_CONSOLE" /D "USE_FOUNDATIONKIT_DLL" /D "HPDF_NOZLIB" /D "HPDF_NOPNGLIB" /FD /GZ /I$(VCF_ROOT)/src /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:$(VCF_ROOT)/lib

!ENDIF 

# Begin Target

# Name "PDFKit - Win32 Release"
# Name "PDFKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\PDFKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "haru"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\libharu\src\hpdf_annotation.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_array.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_binary.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_boolean.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_catalog.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_destination.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_dict.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_doc.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_doc_png.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encoder.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encoder_cns.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encoder_cnt.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encoder_jp.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encoder_kr.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encrypt.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_encryptdict.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_error.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_ext_gstate.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_font.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_font_cid.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_font_tt.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_font_type1.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_base14.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_cid.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_cns.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_cnt.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_jp.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_kr.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_tt.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_fontdef_type1.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_gstate.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_image.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_image_png.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_info.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_list.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_mmgr.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_name.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_null.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_number.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_objects.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_outline.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_page_label.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_page_operator.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_pages.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_real.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_streams.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_string.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_utils.c"
# End Source File
# Begin Source File

SOURCE=".\libharu\src\hpdf_xref.c"
# End Source File
# End Group
# End Target
# End Project
