#ifndef _VCF_PROCESSWITHREDIRECTEDIO_H__
#define _VCF_PROCESSWITHREDIRECTEDIO_H__
//ProcessWithRedirectedIO.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_OUTPUTREADYEVENT_H__
#	include "vcf/FoundationKit/OutputReadyEvent.h"
#endif // _VCF_OUTPUTREADYEVENT_H__

#ifndef _VCF_PROCESSIOREDIRECTIONPEER_H__
#	include "vcf/FoundationKit/ProcessIORedirectionPeer.h"
#endif // _VCF_PROCESSIOREDIRECTIONPEER_H__



namespace VCF {

	class ProcessIORedirectionPeer;

	/**
	\class ProcessWithRedirectedIO ProcessWithRedirectedIO.h "vcf/FoundationKit/ProcessWithRedirectedIO.h"
	This class represents a process that has it's IO redirected so that when
	there is new data available an event is fired to any registered event
	handlers. Currently only output is captured and redirected.
	You can register an event handler with the addOutputReadyHandler() method.
	To start the process either call createProcess() or construct the process
	and pass in a filename/commandline to the constructor.
	*/
	class FOUNDATIONKIT_API ProcessWithRedirectedIO : public Object {
	public:
		/**
		Constructs a ProcessWithRedirectedIO. Does NOT actually start the
		process.
		*/
		ProcessWithRedirectedIO();

		/**
		Constructs a ProcessWithRedirectedIO. It will then
		call the createProcess() with the processName passed in.
		if createProcess() returns false then an RuntimeException
		will be thrown
		*/
		ProcessWithRedirectedIO( const String& processName, const String& arguments );

		virtual ~ProcessWithRedirectedIO();


		/**
		@delegate OutputReady fires an OutputReadyEvent. This is 
		fired by the framework, specifically the ProcessIORedirectionPeer,
		whenever data has become available and read to read. The peer
		will allocate the data in the form of a string (it's assumed to
		be text format). 
		\note Please note that when data is a ready and the the new event 
		is fired, at least in the Win32 implementation, this event will
		be fired in the context of a different thread than the one in which 
		the ProcessWithRedirectedIO	was created in.
		@event OutputReadyEvent
		@eventtype 
		*/
		DELEGATE(OutputReady);

		/**
		Returns the ID of the process
		*/
		int getID();

		/**
		returns the processes's main thread ID
		*/
		int getThreadID();

		/**
		*creates/runs the process
		@param String the name of the process to run.
		createProcess() will block till the process is finished running.
		@param arguments the arguments, or command line, to pass to the process
		*@return bool indicates wether the process creation was successful. If the
		process was successful then it returns true. If not then it returns false.
		*/
		bool createProcess( const String& processName, const String& arguments );

		/**
		returns the name of the process including any commandline supplied.
		*/
		String getName();

		/**
		returns the current peer instance. Should NEVER be NULL as the constructors
		should throw exceptions if a NULL peer is returned from the SystemToolkit
		*/
		ProcessIORedirectionPeer* getPeer() {
			return processPeer_;
		}

		/**
		adds a new output ready handler. Please note (for at least Win32 implementations,
		when data is a ready and the the new event is fired, this will happen in the
		context of a different thread than the one in which the ProcessWithRedirectedIO
		was created in.
		@deprecated - use the OutputReady delegate directly.
		*/
		void addOutputReadyHandler( EventHandler* eventHandler ) {
			OutputReady += eventHandler;
		}

		/**
		@deprecated - use the OutputReady delegate directly.
		*/
		void removeOutputReadyHandler( EventHandler* eventHandler ) {
			OutputReady -= eventHandler;
		}

		ulong32 terminate();
	protected:
		ProcessIORedirectionPeer* processPeer_;
	};
};


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
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
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
*Revision 1.4.2.1  2003/06/23 23:16:55  ddiego
*added some furtther implementation for the osx port
*
*Revision 1.4  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:11:51  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.2  2002/12/28 01:56:21  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.2  2002/09/17 21:33:00  ddiego
*added the build menus for building files and projects
*
*Revision 1.1.2.1  2002/09/17 18:48:35  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*/


#endif // _VCF_PROCESSWITHREDIRECTEDIO_H__


