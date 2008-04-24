#ifndef _VCF_GRAPHICSKITPRIVATE_H__
#define _VCF_GRAPHICSKITPRIVATE_H__
//GraphicsKitPrivate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#if defined (VCF_MSC) && (_MSC_VER >= 1020)
#endif

#include "vcf/FoundationKit/FoundationKitPrivate.h"

#if defined(VCF_WIN) && !defined(VCF_AGG)
#	include "vcf/GraphicsKit/Win32GraphicsToolkit.h"
#	include "vcf/GraphicsKit/Win32Context.h"
#	include "vcf/GraphicsKit/Win32Image.h"
#	include "vcf/GraphicsKit/Win32Font.h"
#	include "vcf/GraphicsKit/Win32FontManager.h"
#endif

#ifdef VCF_X11
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>

	//include the imlib2 headers
	#include "Imlib2.h"

#	include "vcf/ApplicationKit/X11VCFUtils.h"
#	include "vcf/ApplicationKit/X11GraphicsToolkit.h"
#	include "vcf/ApplicationKit/X11Context.h"
#	include "vcf/ApplicationKit/X11Image.h"
#	include "vcf/ApplicationKit/X11Font.h"
#endif

#ifdef VCF_XCB
#	include <xcb/xcb.h>
#	include <xcb/xcb_atom.h>
extern "C"
{
	#include <xcb/xcb_image.h>
	#include <xcb/xcb_aux.h>
}

#	include <fontconfig/fontconfig.h>
#	include "vcf/GraphicsKit/XCBGraphicsToolkit.h"
#endif

#ifdef VCF_AGG
#include "AggGraphicsToolkit.h"
#endif

#ifdef VCF_GTK
	#include <gtk/gtk.h>
	#include <pango/pango.h>
#	include "vcf/ApplicationKit/GTKPeer.h"
#	include "vcf/GraphicsKit/GTKGraphicsToolkit.h"
#	include "vcf/GraphicsKit/GTKContext.h"
#	include "vcf/GraphicsKit/GTKImage.h"
#	include "vcf/GraphicsKit/GTKFont.h"
#endif

#ifdef VCF_OSX
	#include <Carbon/Carbon.h>
#	include "vcf/GraphicsKit/OSXGraphicsToolkit.h"
#	include "vcf/GraphicsKit/OSXContext.h"
#	include "vcf/GraphicsKit/OSXImage.h"
#	include "vcf/GraphicsKit/OSXFont.h"
#endif


#endif // _VCF_GRAPHICSKITPRIVATE_H__

/**
$Id$
*/
