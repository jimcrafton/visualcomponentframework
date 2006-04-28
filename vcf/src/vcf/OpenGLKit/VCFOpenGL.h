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


#endif // _VCF_VCFOPENGL_H__

/**
$Id$
*/
