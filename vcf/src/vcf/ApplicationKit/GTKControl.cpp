//GTKControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKControl.h"
#include "vcf/ApplicationKit/GTKUIToolkit.h"

using namespace VCF;


GTKControl::GTKControl( Control* control )
{
	control_ = control;


}

GTKControl::~GTKControl()
{

}



void GTKControl::create( Control* owningControl )
{
	GTKGraphicsToolkit* grafToolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	GTKUIToolkit* toolkit = (GTKUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();

	wndHandle_ = AbstractGTKControl::Container::create(NULL, this);	//gtk_layout_new( NULL, NULL );

		//

	if ( NULL == wndHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("gtk_layout_new() failed") );
	}

	gtk_container_add( GTK_CONTAINER( toolkit->getDefaultParent() ), wndHandle_ );

	AbstractGTKControl::registerGTKControl( this );


}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.11  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.10  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.8.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*

*Revision 1.8  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.7  2003/08/09 02:56:46  ddiego
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
*Revision 1.6.2.6  2003/07/14 22:52:53  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.6.2.5  2003/07/13 03:45:11  ddiego
*Added further fixes for the GTK port. Now have the event handling working
*correctly, and fixed an issue with too many repaint messages being sent
*which caused 100% CPU utilization.
*
*Revision 1.6.2.4  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*Revision 1.6.2.3  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.6.2.2  2003/06/01 16:44:00  ddiego
*further GTK support added
*
*Revision 1.6.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.6  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.3  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.5.2.2  2003/04/23 03:42:54  ddiego
*further gtk dev got basic eventing code in place
*
*Revision 1.5.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


