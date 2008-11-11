# Microsoft Developer Studio Project File - Name="GraphvizKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GraphvizKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GraphvizKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GraphvizKit.mak" CFG="GraphvizKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GraphvizKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GraphvizKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GraphvizKit - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GraphvizKit - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)\src" /I "lib/fdpgen" /I "lib/graph" /I "lib/cdt" /I "lib/gvc" /I "lib/common" /I "lib/pathplan" /I "./" /I "lib/circogen" /I "lib/neatogen" /I "lib/pack" /I "lib/twopigen" /I "lib/dotgen" /I "windows" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "MSWIN32" /D "HAVE_CONFIG_H" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"GraphvizKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "GraphvizKit - Win32 Release"
# Name "GraphvizKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GraphvizKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GraphvizKit.h
# End Source File
# End Group
# Begin Group "libgraphviz"

# PROP Default_Filter ""
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\common\args.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\arrows.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\colxlate.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\diagen.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\emit.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\fontmetrics.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\geom.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\globals.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\hpglgen.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\htmllex.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\htmlparse.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\htmltable.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\input.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\labels.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\memory.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\mifgen.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\mpgen.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\ns.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\output.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\picgen.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\pointset.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\postproc.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\psusershape.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\routespl.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\shapes.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\splines.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\timing.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\utils.c
# End Source File
# Begin Source File

SOURCE=.\lib\common\vtxgen.c
# End Source File
# End Group
# Begin Group "pathplan"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\pathplan\cvt.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\inpoly.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\route.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\shortest.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\shortestpth.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\solvers.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\triang.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\util.c
# End Source File
# Begin Source File

SOURCE=.\lib\pathplan\visibility.c
# End Source File
# End Group
# Begin Group "circogen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\circogen\block.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\blockpath.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\blocktree.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\circpos.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\circular.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\circularinit.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\deglist.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\edgelist.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\nodelist.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\nodeset.c
# End Source File
# Begin Source File

SOURCE=.\lib\circogen\stack.c
# End Source File
# End Group
# Begin Group "twopigen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\twopigen\circle.c
# End Source File
# Begin Source File

SOURCE=.\lib\twopigen\twopiinit.c
# End Source File
# End Group
# Begin Group "fdpgen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\fdpgen\clusteredges.c
# End Source File
# Begin Source File

SOURCE=.\lib\fdpgen\comp.c
# End Source File
# Begin Source File

SOURCE=.\lib\fdpgen\fdpinit.c
# End Source File
# Begin Source File

SOURCE=.\lib\fdpgen\grid.c
# End Source File
# Begin Source File

SOURCE=.\lib\fdpgen\layout.c
# End Source File
# Begin Source File

SOURCE=.\lib\fdpgen\tlayout.c
# End Source File
# Begin Source File

SOURCE=.\lib\fdpgen\xlayout.c
# End Source File
# End Group
# Begin Group "neatogen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\neatogen\adjust.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\bfs.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\circuit.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\closest.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\compute_hierarchy.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\conjgrad.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\constrained_majorization.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\constrained_majorization_ipsep.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\constraint.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\delaunay.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\dijkstra.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\edges.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\embed_graph.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\find_ints.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\geometry.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\heap.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\hedges.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\info.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\intersect.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\kkutils.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\legal.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\lu.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\matinv.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\matrix_ops.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\memory.c

!IF  "$(CFG)" == "GraphvizKit - Win32 Release"

!ELSEIF  "$(CFG)" == "GraphvizKit - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\mosek_quad_solve.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\neatoinit.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\neatosplines.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\ngmemory.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\opt_arrangement.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\pca.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\poly.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\printvis.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\quad_prog_solve.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\quad_prog_vpsc.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\site.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\smart_ini_x.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\solve.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\stress.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\stuff.c
# End Source File
# Begin Source File

SOURCE=.\lib\neatogen\voronoi.c
# End Source File
# End Group
# Begin Group "pack"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\pack\ccomps.c
# End Source File
# Begin Source File

SOURCE=.\lib\pack\pack.c
# End Source File
# Begin Source File

SOURCE=.\lib\pack\pack.h
# End Source File
# End Group
# Begin Group "dotgen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\dotgen\acyclic.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\class1.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\class2.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\cluster.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\compound.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\conc.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\decomp.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\dot.h
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\dotinit.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\dotprocs.h
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\dotsplines.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\fastgr.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\flat.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\mincross.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\position.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\rank.c
# End Source File
# Begin Source File

SOURCE=.\lib\dotgen\sameport.c
# End Source File
# End Group
# Begin Group "plugins"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\plugin\dot_layout\gvlayout_dot_layout.c
# End Source File
# Begin Source File

SOURCE=.\plugin\neato_layout\gvlayout_neato_layout.c
# End Source File
# Begin Source File

SOURCE=.\plugin\dot_layout\gvplugin_dot_layout.c
# End Source File
# Begin Source File

SOURCE=.\plugin\neato_layout\gvplugin_neato_layout.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\lib\graph\agxbuf.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\attribs.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\dot_builtins.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtclose.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtdisc.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtextract.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtflatten.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dthash.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtlist.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtmethod.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtopen.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtrenew.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtrestore.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtsize.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtstat.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtstrhash.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dttree.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtview.c
# End Source File
# Begin Source File

SOURCE=.\lib\cdt\dtwalk.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\edge.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\graph.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\graphio.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvc.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvconfig.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvcontext.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvdevice.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvevent.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvjobs.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvlayout.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvloadimage.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvloadimage_core.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvplugin.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvplugin_core.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvrender.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_dot.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_fig.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_map.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_ps.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_svg.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_tk.c
# End Source File
# Begin Source File

SOURCE=.\plugin\core\gvrender_core_vml.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvtextlayout.c
# End Source File
# Begin Source File

SOURCE=.\lib\gvc\gvusershape.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\lexer.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\node.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\parser.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\refstr.c
# End Source File
# Begin Source File

SOURCE=.\lib\graph\trie.c
# End Source File
# End Group
# End Target
# End Project
