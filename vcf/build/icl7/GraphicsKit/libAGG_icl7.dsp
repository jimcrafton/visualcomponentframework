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
# PROP Output_Dir "icl7\Release\"
# PROP Intermediate_Dir "icl7\Release\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/libAGG_icl7_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/libAGG_icl7_s.lib"

!ELSEIF  "$(CFG)" == "libAGG - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "icl7\Debug\"
# PROP Intermediate_Dir "icl7\Debug\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fd"..\..\..\lib\libAGG_icl7_sd.pdb" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/libAGG_icl7_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/libAGG_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "libAGG - Win32 GTK Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libAGG___Win32_GTK_Debug"
# PROP BASE Intermediate_Dir "libAGG___Win32_GTK_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "icl7\libAGG___Win32_GTK_Debug\"
# PROP Intermediate_Dir "icl7\libAGG___Win32_GTK_Debug\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fd"..\..\..\lib\libAGG_icl7_sd.pdb" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/libAGG_icl7_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../../lib/libAGG_icl7_sd.lib"
# ADD LIB32 /nologo /out:"../../../lib/libAGG_icl7_sd.lib"

!ENDIF 

# Begin Target

# Name "libAGG - Win32 Release"
# Name "libAGG - Win32 Debug"
# Name "libAGG - Win32 GTK Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_arc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bezier_arc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bspline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_curves.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_path_storage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_scanline_aa.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_affine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_bspline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_dash.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_stroke.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_alpha_mask_u8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_arc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_array.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_arrowhead.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_basics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_bezier_arc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_bitset_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_bounding_rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_clip_liang_barsky.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_color_rgba.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_color_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_color_rgba8_pre.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_adaptor_vcgen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_adaptor_vpgen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_clip_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_close_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_concat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_contour.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_curve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_dash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_gpc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_marker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_marker_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_segmentator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_shorten_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_smooth_poly1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_transform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_conv_unclose_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_curves.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_dda_line.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_ellipse_bresenham.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_embedded_raster_fonts.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_font_cache_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_gamma_functions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_gamma_lut.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_glyph_raster_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_gsv_text.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_image_filters.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_line_aa_basics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_math.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_path_storage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_path_storage_integer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pattern_filters_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_amask_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgb24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgb24_gamma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgb24_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgb555.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgb565.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgba32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgba32_plain.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_pixfmt_rgba32_pre.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_rasterizer_outline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_rasterizer_outline_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_rasterizer_scanline_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_markers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_mclip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_outline_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_outline_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_primitives.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_raster_text.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_renderer_scanline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_rendering_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_rounded_rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_scanline_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_scanline_boolean_algebra.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_scanline_p.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_scanline_storage_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_scanline_storage_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_scanline_u.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_shorten_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_simul_eq.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_converter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_generator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_gouraud.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_gouraud_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_gouraud_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_gouraud_rgba8_gamma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_gradient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_image_filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_image_filter_rgb24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_image_filter_rgb24_gamma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_image_filter_rgba32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_interpolator_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_interpolator_linear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_interpolator_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_pattern.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_pattern_rgb24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_pattern_rgba32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_span_solid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_affine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_bilinear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_double_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_perspective.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_single_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_viewport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_trans_warp_magnifier.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_contour.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_dash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_markers_term.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_smooth_poly1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vcgen_vertex_sequence.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vertex_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vertex_sequence.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vpgen_clip_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\include\agg_vpgen_segmentator.h
# End Source File
# End Group
# End Target
# End Project
