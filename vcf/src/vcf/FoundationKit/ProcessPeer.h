#ifndef _VCF_PROCESSPEER_H__
#define _VCF_PROCESSPEER_H__
//ProcessPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_WAITABLE_H__
#include "vcf/FoundationKit/Waitable.h"
#endif


namespace VCF {

/**
\class ProcessPeer ProcessPeer.h "vcf/FoundationKit/ProcessPeer.h"
*a peer class that wraps working with processes
*on OS's
*/
class FOUNDATIONKIT_API ProcessPeer {

public:
	ProcessPeer() {} ;

	virtual ~ProcessPeer() {};

	/**
	*returns an int that uniquely identifies the process on a given machine
	*/
	virtual int getProcessID() = 0;

	/**
	*returns the process's main thread ID
	*/
	virtual int getProcessThreadID() = 0;

	/**
	*creates a new process specified by the fully
	*qualified file name in the processName argument.
	*@param String the fully qualified file name of
	*process to start. This must represent an actual
	*executable file
	*@return bool returns true if the process was successfully started
	*otherwise false.
	*/
	virtual bool createProcess( const String& processName, const String& arguments ) = 0;

	/**
	*returns the fully qualified file name of the process the
	*object represents.
	*/
	virtual String getProcessFileName() = 0;

	virtual OSHandleID getHandleID() = 0;

	virtual ulong32 terminate() = 0;

	virtual Waitable::WaitResult wait( uint32 milliseconds ) = 0;

	virtual Waitable::WaitResult wait() = 0;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.4.2.1  2005/11/28 21:01:06  ddiego
*added wait function to process class. added stubs for linux.
*
*Revision 1.4  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:05:01  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2.4.1  2004/12/19 04:05:01  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.10.2.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.9.2.1  2004/01/20 19:19:01  ddiego
*mod to Process class to allow it to be terminated
*
*Revision 1.9  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.8  2003/08/09 02:56:44  ddiego
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
*Revision 1.7.6.1  2003/06/23 23:16:55  ddiego
*added some furtther implementation for the osx port
*
*Revision 1.7  2002/11/17 18:09:41  ddiego
*removing hte old Contextpeer.h file - to make way for the "new"
*ContextPeer.h - gotta love case sensitive file systems :)
*
*Revision 1.6.16.1  2002/09/17 18:48:34  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PROCESSPEER_H__


