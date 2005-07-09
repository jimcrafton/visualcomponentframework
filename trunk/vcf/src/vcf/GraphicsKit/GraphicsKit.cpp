//GraphicsKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"

#include "vcf/FoundationKit/RTTIMacros.h"

#include "vcf/GraphicsKit/GraphicsKitRTTI.inl"

using namespace VCF;


//put global C++ objects here

GraphicsToolkit* GraphicsToolkit::graphicsToolkitInstance = NULL;




void GraphicsKit::init( int argc, char** argv )
{
	FoundationKit::init( argc, argv );

	REGISTER_CLASSINFO_EXTERNAL( Rect );
	REGISTER_CLASSINFO_EXTERNAL( ImageBits );
	REGISTER_CLASSINFO_EXTERNAL( Color );
	REGISTER_CLASSINFO_EXTERNAL( Font );

	GraphicsToolkit::initGraphicsToolkit();
}


void GraphicsKit::terminate()
{
	GraphicsToolkit::terminate();

	FoundationKit::terminate();
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:05:59  ddiego
*added missing gtk files
*
*Revision 1.2.4.1  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.17  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*

*Revision 1.14.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.14  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.2.2  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.13.2.1  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.13  2003/08/09 02:56:45  ddiego
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
*Revision 1.12.2.3  2003/08/02 00:41:12  marcelloptr
*fixes for vc6;  improved dependencies
*
*Revision 1.12.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.12.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.12  2003/05/17 20:37:22  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:12:02  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.8.1  2002/12/27 23:04:47  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.6.3  2002/09/03 05:05:13  ddiego
*fixed some more bugs in getting form building to work again. It now works
*but of course there are new issues, namely reading in nested properties
*in a form file where the properties are objects like:
*font.color.red, so this needs to be fixed in hte VFFInputStream file
*also need to have hte form saved properly
*still miscellaneous crashes but getting closer to an alpha tes state
*
*Revision 1.9.6.2  2002/08/08 05:02:59  ddiego
*added a test for X11 GraphicsKit testing
*fixed bug in initializing the graphicsKit, actually I just
*realized this will cause another but - take out automatice initialization of
*FoundationKit from GraphicsKit
*
*Revision 1.9.6.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.9  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


