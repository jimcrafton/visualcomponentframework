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


#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#endif

#include "vcf/FoundationKit/FoundationKitPrivate.h"

#ifdef WIN32
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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.3  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.6.4.2  2004/02/24 01:42:19  ddiego
*initial OSX ApplicationKit port checkin
*
*Revision 1.6.4.1  2004/02/21 03:26:28  ddiego
*updates for OSX porting
*
*Revision 1.6  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.5.2.1  2003/07/07 03:52:08  ddiego
*added further osx porting code, primarily to the GraphicsKit - hey we can
*draw lines ! Woot!
*
*Revision 1.5  2003/05/17 20:36:58  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.2  2003/04/17 04:29:45  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.4.2.1  2003/03/23 03:23:42  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.8.6  2003/02/20 02:46:00  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Revision 1.3.8.5  2003/01/08 00:19:41  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.3.8.4  2002/12/27 23:04:28  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.3.8.3  2002/12/20 03:29:02  ddiego
*continued more work in integrating imlib2 into the X11Image class. getting
*a little better hand of how to debug with CLI gdb ! Close to having this
*work, and tehn we can work on Fonts !
*
*Revision 1.3.8.2  2002/12/19 05:32:30  ddiego
*initial integration of imlib2 into the GraphicsKit.
*
*Revision 1.3.8.1  2002/12/14 01:50:24  ddiego
*more code in X11Image
*
*Revision 1.3  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.6.2  2002/08/10 05:48:06  ddiego
*added basic support to the X11COntext for drawing lines, rectangles, and ellipses
*Bezier curves are more complex and will have to be done by hand as X has no
*convenient way to do this
*
*Revision 1.2.6.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.3  2002/04/27 15:52:15  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*/


#endif // _VCF_GRAPHICSKITPRIVATE_H__


