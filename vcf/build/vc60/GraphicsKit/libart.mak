# Microsoft Developer Studio Generated NMAKE File, Based on libart.dsp
!IF "$(CFG)" == ""
CFG=libart - Win32 Debug
!MESSAGE No configuration specified. Defaulting to libart - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "libart - Win32 Release" && "$(CFG)" != "libart - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libart.mak" CFG="libart - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libart - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libart - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "libart - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

ALL : "$(OUTDIR)\libart.lib"


CLEAN :
	-@erase "$(INTDIR)\art_affine.obj"
	-@erase "$(INTDIR)\art_alphagamma.obj"
	-@erase "$(INTDIR)\art_bpath.obj"
	-@erase "$(INTDIR)\art_gray_svp.obj"
	-@erase "$(INTDIR)\art_misc.obj"
	-@erase "$(INTDIR)\art_pixbuf.obj"
	-@erase "$(INTDIR)\art_rect.obj"
	-@erase "$(INTDIR)\art_rect_svp.obj"
	-@erase "$(INTDIR)\art_rect_uta.obj"
	-@erase "$(INTDIR)\art_render.obj"
	-@erase "$(INTDIR)\art_render_gradient.obj"
	-@erase "$(INTDIR)\art_render_svp.obj"
	-@erase "$(INTDIR)\art_rgb.obj"
	-@erase "$(INTDIR)\art_rgb_affine.obj"
	-@erase "$(INTDIR)\art_rgb_affine_private.obj"
	-@erase "$(INTDIR)\art_rgb_bitmap_affine.obj"
	-@erase "$(INTDIR)\art_rgb_pixbuf_affine.obj"
	-@erase "$(INTDIR)\art_rgb_rgba_affine.obj"
	-@erase "$(INTDIR)\art_rgb_svp.obj"
	-@erase "$(INTDIR)\art_rgba.obj"
	-@erase "$(INTDIR)\art_svp.obj"
	-@erase "$(INTDIR)\art_svp_ops.obj"
	-@erase "$(INTDIR)\art_svp_point.obj"
	-@erase "$(INTDIR)\art_svp_render_aa.obj"
	-@erase "$(INTDIR)\art_svp_vpath.obj"
	-@erase "$(INTDIR)\art_svp_vpath_stroke.obj"
	-@erase "$(INTDIR)\art_svp_wind.obj"
	-@erase "$(INTDIR)\art_uta.obj"
	-@erase "$(INTDIR)\art_uta_ops.obj"
	-@erase "$(INTDIR)\art_uta_rect.obj"
	-@erase "$(INTDIR)\art_uta_svp.obj"
	-@erase "$(INTDIR)\art_uta_vpath.obj"
	-@erase "$(INTDIR)\art_vpath.obj"
	-@erase "$(INTDIR)\art_vpath_bpath.obj"
	-@erase "$(INTDIR)\art_vpath_dash.obj"
	-@erase "$(INTDIR)\art_vpath_svp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\libart.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\include\Graphics" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\libart.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libart.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libart.lib" 
LIB32_OBJS= \
	"$(INTDIR)\art_affine.obj" \
	"$(INTDIR)\art_alphagamma.obj" \
	"$(INTDIR)\art_bpath.obj" \
	"$(INTDIR)\art_gray_svp.obj" \
	"$(INTDIR)\art_misc.obj" \
	"$(INTDIR)\art_pixbuf.obj" \
	"$(INTDIR)\art_rect.obj" \
	"$(INTDIR)\art_rect_svp.obj" \
	"$(INTDIR)\art_rect_uta.obj" \
	"$(INTDIR)\art_render.obj" \
	"$(INTDIR)\art_render_gradient.obj" \
	"$(INTDIR)\art_render_svp.obj" \
	"$(INTDIR)\art_rgb.obj" \
	"$(INTDIR)\art_rgb_affine.obj" \
	"$(INTDIR)\art_rgb_affine_private.obj" \
	"$(INTDIR)\art_rgb_bitmap_affine.obj" \
	"$(INTDIR)\art_rgb_pixbuf_affine.obj" \
	"$(INTDIR)\art_rgb_rgba_affine.obj" \
	"$(INTDIR)\art_rgb_svp.obj" \
	"$(INTDIR)\art_rgba.obj" \
	"$(INTDIR)\art_svp.obj" \
	"$(INTDIR)\art_svp_ops.obj" \
	"$(INTDIR)\art_svp_point.obj" \
	"$(INTDIR)\art_svp_render_aa.obj" \
	"$(INTDIR)\art_svp_vpath.obj" \
	"$(INTDIR)\art_svp_vpath_stroke.obj" \
	"$(INTDIR)\art_svp_wind.obj" \
	"$(INTDIR)\art_uta.obj" \
	"$(INTDIR)\art_uta_ops.obj" \
	"$(INTDIR)\art_uta_rect.obj" \
	"$(INTDIR)\art_uta_svp.obj" \
	"$(INTDIR)\art_uta_vpath.obj" \
	"$(INTDIR)\art_vpath.obj" \
	"$(INTDIR)\art_vpath_bpath.obj" \
	"$(INTDIR)\art_vpath_dash.obj" \
	"$(INTDIR)\art_vpath_svp.obj"

"$(OUTDIR)\libart.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libart - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

ALL : "$(OUTDIR)\libart_d.lib"


CLEAN :
	-@erase "$(INTDIR)\art_affine.obj"
	-@erase "$(INTDIR)\art_alphagamma.obj"
	-@erase "$(INTDIR)\art_bpath.obj"
	-@erase "$(INTDIR)\art_gray_svp.obj"
	-@erase "$(INTDIR)\art_misc.obj"
	-@erase "$(INTDIR)\art_pixbuf.obj"
	-@erase "$(INTDIR)\art_rect.obj"
	-@erase "$(INTDIR)\art_rect_svp.obj"
	-@erase "$(INTDIR)\art_rect_uta.obj"
	-@erase "$(INTDIR)\art_render.obj"
	-@erase "$(INTDIR)\art_render_gradient.obj"
	-@erase "$(INTDIR)\art_render_svp.obj"
	-@erase "$(INTDIR)\art_rgb.obj"
	-@erase "$(INTDIR)\art_rgb_affine.obj"
	-@erase "$(INTDIR)\art_rgb_affine_private.obj"
	-@erase "$(INTDIR)\art_rgb_bitmap_affine.obj"
	-@erase "$(INTDIR)\art_rgb_pixbuf_affine.obj"
	-@erase "$(INTDIR)\art_rgb_rgba_affine.obj"
	-@erase "$(INTDIR)\art_rgb_svp.obj"
	-@erase "$(INTDIR)\art_rgba.obj"
	-@erase "$(INTDIR)\art_svp.obj"
	-@erase "$(INTDIR)\art_svp_ops.obj"
	-@erase "$(INTDIR)\art_svp_point.obj"
	-@erase "$(INTDIR)\art_svp_render_aa.obj"
	-@erase "$(INTDIR)\art_svp_vpath.obj"
	-@erase "$(INTDIR)\art_svp_vpath_stroke.obj"
	-@erase "$(INTDIR)\art_svp_wind.obj"
	-@erase "$(INTDIR)\art_uta.obj"
	-@erase "$(INTDIR)\art_uta_ops.obj"
	-@erase "$(INTDIR)\art_uta_rect.obj"
	-@erase "$(INTDIR)\art_uta_svp.obj"
	-@erase "$(INTDIR)\art_uta_vpath.obj"
	-@erase "$(INTDIR)\art_vpath.obj"
	-@erase "$(INTDIR)\art_vpath_bpath.obj"
	-@erase "$(INTDIR)\art_vpath_dash.obj"
	-@erase "$(INTDIR)\art_vpath_svp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\libart_d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include\Graphics" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libart.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libart_d.lib" 
LIB32_OBJS= \
	"$(INTDIR)\art_affine.obj" \
	"$(INTDIR)\art_alphagamma.obj" \
	"$(INTDIR)\art_bpath.obj" \
	"$(INTDIR)\art_gray_svp.obj" \
	"$(INTDIR)\art_misc.obj" \
	"$(INTDIR)\art_pixbuf.obj" \
	"$(INTDIR)\art_rect.obj" \
	"$(INTDIR)\art_rect_svp.obj" \
	"$(INTDIR)\art_rect_uta.obj" \
	"$(INTDIR)\art_render.obj" \
	"$(INTDIR)\art_render_gradient.obj" \
	"$(INTDIR)\art_render_svp.obj" \
	"$(INTDIR)\art_rgb.obj" \
	"$(INTDIR)\art_rgb_affine.obj" \
	"$(INTDIR)\art_rgb_affine_private.obj" \
	"$(INTDIR)\art_rgb_bitmap_affine.obj" \
	"$(INTDIR)\art_rgb_pixbuf_affine.obj" \
	"$(INTDIR)\art_rgb_rgba_affine.obj" \
	"$(INTDIR)\art_rgb_svp.obj" \
	"$(INTDIR)\art_rgba.obj" \
	"$(INTDIR)\art_svp.obj" \
	"$(INTDIR)\art_svp_ops.obj" \
	"$(INTDIR)\art_svp_point.obj" \
	"$(INTDIR)\art_svp_render_aa.obj" \
	"$(INTDIR)\art_svp_vpath.obj" \
	"$(INTDIR)\art_svp_vpath_stroke.obj" \
	"$(INTDIR)\art_svp_wind.obj" \
	"$(INTDIR)\art_uta.obj" \
	"$(INTDIR)\art_uta_ops.obj" \
	"$(INTDIR)\art_uta_rect.obj" \
	"$(INTDIR)\art_uta_svp.obj" \
	"$(INTDIR)\art_uta_vpath.obj" \
	"$(INTDIR)\art_vpath.obj" \
	"$(INTDIR)\art_vpath_bpath.obj" \
	"$(INTDIR)\art_vpath_dash.obj" \
	"$(INTDIR)\art_vpath_svp.obj"

"$(OUTDIR)\libart_d.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("libart.dep")
!INCLUDE "libart.dep"
!ELSE 
!MESSAGE Warning: cannot find "libart.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "libart - Win32 Release" || "$(CFG)" == "libart - Win32 Debug"
SOURCE=..\..\..\src\Graphics\art_affine.c

"$(INTDIR)\art_affine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_alphagamma.c

"$(INTDIR)\art_alphagamma.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_bpath.c

"$(INTDIR)\art_bpath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_gray_svp.c

"$(INTDIR)\art_gray_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_misc.c

"$(INTDIR)\art_misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_pixbuf.c

"$(INTDIR)\art_pixbuf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rect.c

"$(INTDIR)\art_rect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rect_svp.c

"$(INTDIR)\art_rect_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rect_uta.c

"$(INTDIR)\art_rect_uta.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_render.c

"$(INTDIR)\art_render.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_render_gradient.c

"$(INTDIR)\art_render_gradient.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_render_svp.c

"$(INTDIR)\art_render_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb.c

"$(INTDIR)\art_rgb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb_affine.c

"$(INTDIR)\art_rgb_affine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb_affine_private.c

"$(INTDIR)\art_rgb_affine_private.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb_bitmap_affine.c

"$(INTDIR)\art_rgb_bitmap_affine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb_pixbuf_affine.c

"$(INTDIR)\art_rgb_pixbuf_affine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb_rgba_affine.c

"$(INTDIR)\art_rgb_rgba_affine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgb_svp.c

"$(INTDIR)\art_rgb_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_rgba.c

"$(INTDIR)\art_rgba.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp.c

"$(INTDIR)\art_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp_ops.c

"$(INTDIR)\art_svp_ops.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp_point.c

"$(INTDIR)\art_svp_point.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp_render_aa.c

"$(INTDIR)\art_svp_render_aa.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp_vpath.c

"$(INTDIR)\art_svp_vpath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp_vpath_stroke.c

"$(INTDIR)\art_svp_vpath_stroke.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_svp_wind.c

"$(INTDIR)\art_svp_wind.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_uta.c

"$(INTDIR)\art_uta.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_uta_ops.c

"$(INTDIR)\art_uta_ops.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_uta_rect.c

"$(INTDIR)\art_uta_rect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_uta_svp.c

"$(INTDIR)\art_uta_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_uta_vpath.c

"$(INTDIR)\art_uta_vpath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_vpath.c

"$(INTDIR)\art_vpath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_vpath_bpath.c

"$(INTDIR)\art_vpath_bpath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_vpath_dash.c

"$(INTDIR)\art_vpath_dash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\art_vpath_svp.c

"$(INTDIR)\art_vpath_svp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

