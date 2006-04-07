#ifndef _VCF_WIN32PROCESSIOREDIRECTOR_H__
#define _VCF_WIN32PROCESSIOREDIRECTOR_H__
//Win32ProcessIORedirector.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//Win32ProcessIORedirector


namespace VCF {



/**
Win32 (NT or better) implementation of ProcessIORedirectionPeer
original code swiped from:  (c) 2002 Andreas Saurwein - saurwein@uniwares.com
Any mistakes are mine due to the "port" over into the VCF.
*/
class Win32ProcessIORedirector  : public Object, public ProcessIORedirectionPeer {
public:
	Win32ProcessIORedirector();

	virtual ~Win32ProcessIORedirector();	

	virtual int getProcessID() {
		return processID_;
	}

	/**
	*returns the process's main thread ID
	*/
	virtual int getProcessThreadID() {
		return processThreadID_;
	}

	/**
	*creates a new process specified by the fully
	*qualified file name in the processName argument.
	*@param String the fully qualified file name of
	*process to start. This must represent an actual
	*executable file
	*@return bool returns true if the process was successfully started
	*otherwise false.
	*/
	virtual bool createProcess( const String& processName, const String& arguments );

	/**
	*returns the fully qualified file name of the process the
	*object represents.
	*/
	virtual String getProcessFileName() {
		return commandLine_;
	}

	virtual OSHandleID getHandleID() {
		return (OSHandleID)childProcess_;
	}

	virtual void setProcess( ProcessWithRedirectedIO* process ) {
		process_ = process;
	}

	virtual ulong32 terminate();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();
protected:
	//this is the handle to the child process that gets started
	HANDLE childProcess_;
	ProcessWithRedirectedIO* process_;
	int processID_;
	int processThreadID_;
	UINT readThreadID_;
	String commandLine_;
	HANDLE readThread_;

	HANDLE	childStdinRdHandle_;
	HANDLE	childStdinWrHandle_;
	HANDLE	childStdoutRdHandle_;
	HANDLE	childStdoutWrHandle_;
	HANDLE	savedStdinHandle_;
	HANDLE	savedStdoutHandle_;
	PROCESS_INFORMATION processInfo_;

	void*	startInfoPtr_;

	bool canContinueReading_;

	void readPipe();

	static UINT __stdcall ReadPipeThreadProc(LPVOID pParam);
	bool testProcess();
};


};


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/03/12 22:01:44  ddiego
*doc updates.
*
*Revision 1.4.2.1  2005/11/28 21:01:06  ddiego
*added wait function to process class. added stubs for linux.
*
*Revision 1.4  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:24  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2.4.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.2  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7.2.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.7  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.6.2.1  2004/01/20 19:19:01  ddiego
*mod to Process class to allow it to be terminated
*
*Revision 1.6  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.2  2003/10/30 20:13:03  ddiego
*fixed some bugs in the xml parser, added support for cdata and basic
*enities, also fiddled with the redirected IO for processes.
*
*Revision 1.5.2.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.5  2003/08/09 02:56:44  ddiego
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
*Revision 1.4.2.1  2003/06/24 02:45:24  ddiego
*mods to the Process class and the Win32 peers
*
*Revision 1.4  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:11:26  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.1  2002/12/27 23:04:41  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.2  2002/09/20 21:28:44  ddiego
*added mods to support building from the VCF Builder and display the
*console build process. Also allows for double clicking in the output
*area and being able to read the output in a generic manner
*
*Revision 1.1.2.1  2002/09/17 18:48:35  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*/


#endif // _VCF_WIN32PROCESSIOREDIRECTOR_H__


