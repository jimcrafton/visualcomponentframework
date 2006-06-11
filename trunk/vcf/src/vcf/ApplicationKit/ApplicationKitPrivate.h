#ifndef _VCF_APPLICATIONKITPRIVATE_H__
#define _VCF_APPLICATIONKITPRIVATE_H__
//ApplicationKitPrivate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

/****************/
#ifdef VCF_WIN
//controls & GDI stuff
#include <Commdlg.h>
#	include "vcf/FoundationKit/Win32Peer.h"
#	include "vcf/ApplicationKit/Win32ToolKit.h"
#	include "vcf/ApplicationKit/Win32Object.h"
#	include "vcf/ApplicationKit/AbstractWin32Component.h"
#elif VCF_X11
	#include <unistd.h>
	#include <sys/time.h>

	//X11 stuff
#	include "vcf/ApplicationKit/X11Peer.h"
#	include "vcf/ApplicationKit/X11UIToolkit.h"
#elif VCF_GTK

#	include "vcf/ApplicationKit/GTKUIToolkit.h"
#elif VCF_OSX

#	include "vcf/ApplicationKit/OSXUIToolkit.h"
#endif


#endif // _VCF_APPLICATIONKITPRIVATE_H__

/**
$Id$
*/
