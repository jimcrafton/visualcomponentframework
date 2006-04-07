//ProcessWithRedirectedIO.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ProcessWithRedirectedIO.h"


using namespace VCF;


ProcessWithRedirectedIO::ProcessWithRedirectedIO():
	processPeer_(NULL)
{
	processPeer_ = SystemToolkit::createProcessIORedirectionPeer( this );
	if ( NULL == processPeer_ ) {
		throw NoPeerFoundException(MAKE_ERROR_MSG_2(NO_PEER));
	}
}

ProcessWithRedirectedIO::ProcessWithRedirectedIO( const String& processName, const String& arguments ):
	processPeer_(NULL)
{
	processPeer_ = SystemToolkit::createProcessIORedirectionPeer( this );
	if ( NULL == processPeer_ ) {
		throw NoPeerFoundException(MAKE_ERROR_MSG_2(NO_PEER));
	}

	if ( !createProcess( processName, arguments ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "" ) );
	}
}

ProcessWithRedirectedIO::~ProcessWithRedirectedIO()
{
	delete processPeer_;
}

int ProcessWithRedirectedIO::getID()
{
	return processPeer_->getProcessID();
}

int ProcessWithRedirectedIO::getThreadID()
{
	return processPeer_->getProcessThreadID();
}

bool ProcessWithRedirectedIO::createProcess( const String& processName, const String& arguments )
{
	return processPeer_->createProcess( processName, arguments );
}

String ProcessWithRedirectedIO::getName()
{
	return processPeer_->getProcessFileName();
}

ulong32 ProcessWithRedirectedIO::terminate()
{
	return processPeer_->terminate();
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.6  2004/04/03 15:48:49  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.5.4.1  2004/01/20 19:19:01  ddiego
*mod to Process class to allow it to be terminated
*
*Revision 1.5  2003/08/09 02:56:46  ddiego
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
*Revision 1.4.2.2  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.4.2.1  2003/06/24 02:45:26  ddiego
*mods to the Process class and the Win32 peers
*
*Revision 1.4  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/12 03:12:49  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2.2.1  2002/12/27 23:04:57  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.1  2002/09/17 18:48:38  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*/


