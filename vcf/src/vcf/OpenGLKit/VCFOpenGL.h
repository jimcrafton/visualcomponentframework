#ifndef _VCF_VCFOPENGL_H__
#define _VCF_VCFOPENGL_H__
//VCFOpenGL.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*config file for OpenGL headers
*make sure to link to the following:
	opengl32.lib
	glu32.lib
	glaux.lib
*/


#ifdef WIN32
	#ifndef _WINDOWS_
		#include <windows.h>
	#endif
#endif

#if defined(__APPLE__)
#	include <OpenGL/gl.h>
#	include	<OpenGL/glu.h>
#else
#	include <GL/gl.h>
#	include <GL/glu.h>
#endif


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/06 06:22:24  pallindo
*Fixed up paths to include files
*
*Revision 1.1.2.4  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/06/04 15:39:51  thrysoee
*Rollback accidental commit of Linux/freeglut changes
*
*Revision 1.1.2.1  2004/04/29 15:38:12  pallindo
*Initial attempt at an OpenGLKit
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.6.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.5  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.20.1  2003/01/08 00:19:44  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VCFOPENGL_H__


