#ifndef _VCF_GRAPHICSKIT_H__
#define _VCF_GRAPHICSKIT_H__
//GraphicsKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/FoundationKit.h"

#include "vcf/GraphicsKit/GraphicsKitSelectLib.h"

#include "vcf/GraphicsKit/Point.h"
#include "vcf/GraphicsKit/Size.h"
#include "vcf/GraphicsKit/Rect.h"

#include "vcf/GraphicsKit/Color.h"

#include "vcf/GraphicsKit/Image.h"
#include "vcf/GraphicsKit/ImageBits.h"

#include "vcf/GraphicsKit/GraphicsToolKit.h"
#include "vcf/GraphicsKit/NoGraphicsToolkitFoundException.h"

#include "vcf/GraphicsKit/Stroke.h"
#include "vcf/GraphicsKit/Fill.h"
#include "vcf/GraphicsKit/Matrix2D.h"
#include "vcf/GraphicsKit/ContextPeer.h"
#include "vcf/GraphicsKit/GraphicsContext.h"

#include "vcf/GraphicsKit/ImageLoader.h"
#include "vcf/GraphicsKit/Path.h"
#include "vcf/GraphicsKit/BezierCurve.h"
#include "vcf/GraphicsKit/Ellipse.h"
#include "vcf/GraphicsKit/Circle.h"
#include "vcf/GraphicsKit/Font.h"
#include "vcf/GraphicsKit/FontPeer.h"

#include "vcf/GraphicsKit/ImageEvent.h"
#include "vcf/GraphicsKit/PrintContext.h"
#include "vcf/GraphicsKit/Printable.h"
#include "vcf/GraphicsKit/InvalidImage.h"
#include "vcf/GraphicsKit/ImageLoaderException.h"
#include "vcf/GraphicsKit/AbstractImage.h"

#include "vcf/GraphicsKit/BasicFill.h"
#include "vcf/GraphicsKit/BasicStroke.h"
#include "vcf/GraphicsKit/ContextPeer.h"

//graphics resources
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"

//printing
#include "vcf/GraphicsKit/PrintSession.h"
#include "vcf/GraphicsKit/PrintEvent.h"


/**
\class GraphicsKit GraphicsKit.h "vcf/GraphicsKit/GraphicsKit.h"
*initializes the graphics Kit runtime.
*This includes registering the basic classes in the runtime system
*This MUST be called first off, after the initFoundationKit, in the main() function of the app
*/
namespace VCF
{
	class GRAPHICSKIT_API GraphicsKit
	{
	public:
		/**
		*Initialization takes place here, plus creating the various
		*system resources and peer instances
		*/
		static void init( int argc, char** argv );

		/**
		*Frees up any resource allocated in init();
		*/
		static void terminate();
	};
}; // end of namespace


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/03/12 22:42:08  ddiego
*more doc updates - specific to graphicskit.
*
*Revision 1.5.2.1  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.5  2005/07/09 23:05:59  ddiego
*added missing gtk files
*
*Revision 1.4.2.2  2005/06/09 06:13:10  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.4.2.1  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.4  2004/12/02 04:11:10  ddiego
*removed some old, extraneous files from graphics kit dir.
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/08/25 04:43:33  ddiego
*migrated the core printing changes into the graphics kit
*
*Revision 1.2.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/25 19:52:48  marcelloptr
*adjusted macros and other changes for better performance
*
*Revision 1.1.2.4  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.3  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.2.1  2003/10/28 04:06:10  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
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
*Revision 1.5.2.4  2003/08/08 03:21:35  ddiego
*got rid of some miscellaneous graphics files
*
*Revision 1.5.2.3  2003/07/03 03:14:17  ddiego
*made some changes to the Path interface, and got rid of the PathEnumerator
*class
*
*Revision 1.5.2.2  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.5.2.1  2003/05/30 04:13:10  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.5  2003/05/17 20:36:58  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.4  2003/05/13 03:57:12  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.4.2.3  2003/04/17 04:29:45  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.4.2.2  2003/04/07 03:39:28  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
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
*Revision 1.3.8.3  2003/01/08 00:19:41  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.3.8.2  2002/12/30 00:24:12  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.3.8.1  2002/12/27 23:04:28  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.3  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.6.4  2002/08/12 02:56:25  ddiego
*changes to code parsing for C++
*
*Revision 1.2.6.3  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.2.6.2  2002/07/03 07:13:00  marcelloptr
*minor fixes
*
*Revision 1.2.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.4  2002/04/27 15:52:15  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.1.2.3  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.1.2.2  2002/04/03 20:52:36  zzack
*fixed init bug
*
*Revision 1.1.2.1  2002/04/02 20:36:37  zzack
*changed include
*
*Revision 1.10.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.10  2002/02/17 01:07:14  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.9  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_GRAPHICSKIT_H__


