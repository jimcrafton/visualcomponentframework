# Microsoft Developer Studio Project File - Name="libAGG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libAGG - Win32 GTK Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libAGG.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libAGG.mak" CFG="libAGG - Win32 GTK Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libAGG - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libAGG - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libAGG - Win32 GTK Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libAGG - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "icl7/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(VCF_INCLUDE)/../thirdparty/common/agg/include/" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fo"icl7/Release/" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\lib\libAGG_icl7_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\libAGG_icl7_s.lib"

!ELSEIF  "$(CFG)" == "libAGG - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "icl7/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)/../thirdparty/common/agg/include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"icl7/Debug/" /Fo"icl7/Debug/" /Fd"..\..\..\lib/libAGG_icl7_sd.pdb" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\lib\libAGG_icl7_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\libAGG_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "libAGG - Win32 GTK Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libAGG___Win32_GTK_Debug"
# PROP BASE Intermediate_Dir "libAGG___Win32_GTK_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "icl7/libAGG___Win32_GTK_Debug"
# PROP Intermediate_Dir "icl7/libAGG___Win32_GTK_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)/../thirdparty/common/agg/include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)/../thirdparty/common/agg/include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"icl7/libAGG___Win32_GTK_Debug/" /Fo"icl7/libAGG___Win32_GTK_Debug/" /Fd"..\..\..\lib/libAGG_icl7_sd.pdb" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\lib\libAGG_icl7_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libAGG_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libAGG_icl7_sd.lib"

!ENDIF 

# Begin Target

# Name "libAGG - Win32 Release"
# Name "libAGG - Win32 Debug"
# Name "libAGG - Win32 GTK Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_affine_matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_bspline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_curves.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_gen_stroke.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_gsv_text.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_path_storage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_rasterizer_scanline_aa.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\src\agg_scanline_u8.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_affine_matrix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_affine_span.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_alpha_mask_u8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_array.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_basics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_color_rgba.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_color_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_conv_generator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_conv_stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_conv_transform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_dda_line.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gen_stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gouraud_attr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gouraud_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gouraud_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gradient_attr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gradient_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gradient_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_gsv_text.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_math.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_path_storage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_rasterizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_renderer_bgr24_basic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_renderer_bgra32_basic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_renderer_gray8_basic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_renderer_u8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_renderer_util.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_rendering_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_scanline_u8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_solid_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_solid_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_span_bgr24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_span_bgra32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_span_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_util_bgr24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_util_bgra32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_util_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_vertex_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\thirdparty\common\agg\include\agg_vertex_sequence.h
# End Source File
# End Group
# End Target
# End Project
