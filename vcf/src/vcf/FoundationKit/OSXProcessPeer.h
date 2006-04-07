#ifndef _VCF_OSXPROCESSPEER_H__
#define _VCF_OSXPROCESSPEER_H__
//OSXProcessPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

/**
This is the handle class that OSXProcessPeer::getHandleID() returns.
You should check isUnixProcess to determine how to access the information in this struct.
If isUnixProcess is true, then launchBlock is just zero'ed out and is meaningless and
pid will be set to the process id. If isUnixProcess is false then launchBlock
will have valid information in it, and pid will be set to the unix process id 
of the launchBlock.launchProcessSN
*/
class OSXProcessHandle {
public:
	bool isUnixProcess;
	LaunchParamBlockRec launchBlock;
	int pid;	
};

class OSXProcessPeer : public ProcessPeer {

public:
	OSXProcessPeer();

	virtual ~OSXProcessPeer();

	virtual int getProcessID() {
		return processHandle_.pid;
	}

	virtual int getProcessThreadID();

	virtual bool createProcess( const String& processName, const String& arguments );

	virtual String getProcessFileName();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)&processHandle_;
	}

    virtual ulong32 terminate();
	
	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();
protected:
	OSXProcessHandle processHandle_;
	VCF::String processFileName_;
	bool processTerminated_;
	static OSStatus osxProcessTerminated( EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void * inUserData );
};

}; //end of namespace VCF


/**
*CVS Log info
 *$Log$
 *Revision 1.6  2006/04/07 02:35:34  ddiego
 *initial checkin of merge from 0.6.9 dev branch.
 *
 *Revision 1.5.2.1  2006/01/14 21:49:22  ddiego
 *general osx checkin
 *
 *Revision 1.5  2005/07/09 23:15:04  ddiego
 *merging in changes from devmain-0-6-7 branch.
 *
 *Revision 1.4  2005/01/08 20:52:47  ddiego
 *fixed some glitches in osx impl.
 *
 *Revision 1.3.2.1  2005/05/08 19:55:32  ddiego
 *osx updates, not yet functional.
 *
 *Revision 1.3  2004/12/01 04:31:41  ddiego
 *merged over devmain-0-6-6 code. Marcello did a kick ass job
 *of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
 *that he found. Many, many thanks for this Marcello.
 *
 *Revision 1.2.2.1  2004/10/10 20:42:08  ddiego
 *osx updates
 *
 *Revision 1.2  2004/08/07 02:49:14  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.5  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.4.2.1  2004/04/26 21:58:43  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.4  2004/04/03 15:48:42  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.3.4.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.3  2003/08/09 02:56:44  ddiego
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
 *Revision 1.2.2.1  2003/06/23 23:16:55  ddiego
 *added some furtther implementation for the osx port
 *
 *Revision 1.2  2003/05/17 20:37:12  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:01  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


#endif // _VCF_OSXPROCESSPEER_H__


