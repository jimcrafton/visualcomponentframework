# Microsoft Developer Studio Project File - Name="JavaScriptKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=JavaScriptKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit.mak" CFG="JavaScriptKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JavaScriptKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "JavaScriptKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JavaScriptKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\ReleaseS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /I "./" /I "$(VCF_ROOT)/src/JavaScriptKit/js-impl" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "EXPORT_JS_API" /D "XP_WIN" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/JavaScriptKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\DebugS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "./" /I "$(VCF_ROOT)/src/JavaScriptKit/js-impl" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "EXPORT_JS_API" /D "XP_WIN" /Fd"..\..\..\lib\JavaScriptKit_vc6_sd.pdb" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/JavaScriptKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "JavaScriptKit - Win32 Release"
# Name "JavaScriptKit - Win32 Debug"
# Begin Group "js-impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_acos.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_acosh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_asin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_atan2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_atanh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_cosh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_exp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_fmod.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_gamma.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_gamma_r.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_hypot.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_j0.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_j1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_jn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_lgamma.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_lgamma_r.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_log.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_log10.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_pow.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_rem_pio2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_remainder.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_scalb.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_sinh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\e_sqrt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\fdlibm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\js.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarena.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarena.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarray.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsatom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsatom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsbit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsbool.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsbool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsclist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscntxt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscntxt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscompat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscpucfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdbgapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdbgapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdhash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdhash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdtoa.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdtoa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsemit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsemit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsexn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsexn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsgc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsgc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jshash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jshash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsinterp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsiter.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslibmath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslock.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslog2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslong.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslong.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsmath.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsmath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsnum.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsnum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsobj.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsobj.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsopcode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsosdep.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsotypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsparse.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsparse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsprf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsprf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsprvtd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jspubtd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsregexp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsregexp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscan.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscope.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscope.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscript.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscript.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsstddef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsstr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsstr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jstypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsutil.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsutil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxdrapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxdrapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxml.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\k_cos.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\k_rem_pio2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\k_sin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\k_standard.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\k_tan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\prmjtime.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\prmjtime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\resource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_asinh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_atan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_cbrt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_ceil.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_copysign.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_cos.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_erf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_expm1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_fabs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_finite.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_floor.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_frexp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_ilogb.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_isnan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_ldexp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_lib_version.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_log1p.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_logb.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_matherr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_modf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_nextafter.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_rint.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_scalbn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_signgam.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_significand.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_sin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_tan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\s_tanh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_acos.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_acosh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_asin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_atan2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_atanh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_cosh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_exp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_fmod.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_gamma.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_gamma_r.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_hypot.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_j0.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_j1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_jn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_lgamma.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_lgamma_r.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_log.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_log10.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_pow.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_remainder.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_scalb.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_sinh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm\w_sqrt.c
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\JavaScriptKit.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\JavaScriptKit.cpp
# End Source File
# End Group
# End Target
# End Project
