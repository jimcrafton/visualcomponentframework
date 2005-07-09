#ifndef _VCF_SYSTEMTOOLKIT_H__
#define _VCF_SYSTEMTOOLKIT_H__
//SystemToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class ProcessPeer;
class ProcessIORedirectionPeer;
class ProcessWithRedirectedIO;
class ThreadPeer;
class Process;
class Thread;
class Mutex;
class Condition;
class System;
class SystemPeer;
class LocalePeer;
class ResourceBundlePeer;
class RunLoop;
class RunLoopPeer;
class ThreadManagerPeer;

/**
\par
The SystemToolkit is and abstract class used to create or 
get access to basic system peer instances, like threads, processes, etc. 
It is a singleton factory for the various platform specific 
peers that are required for the FoundationKit. 
\par
The SystemToolkit is a singleton and is not intended to be created
or deleted directly. It is created as part of the FoundationKit::init()
and deleted as part of the FoundationKit::terminate() call. 
\par
If you are porting to a new platform you will need to derive a new 
class from this one and provide implementations of the various
internal_createXXXPeer methods. 
*/
class FOUNDATIONKIT_API SystemToolkit : public Object{

public:

	static SystemToolkit* create();

	static void terminate();

	

	/**
	*creates a new ProcessPeer instance
	*/
	static ProcessPeer* createProcessPeer( Process* process );

	static ProcessIORedirectionPeer* createProcessIORedirectionPeer( ProcessWithRedirectedIO* process );

	/**
	*creates a new ThreadPeer instance
	*/
	static ThreadPeer* createThreadPeer( Thread* thread, bool mainThread );

	static RunLoopPeer* createRunLoopPeer( RunLoop* runLoop );

	static ThreadManagerPeer* createThreadManagerPeer();

	

	/**
	*creates a new system peer
	*/
	static SystemPeer* createSystemPeer();

	static SemaphorePeer* createSemaphorePeer( long initialCount = 1, long maxCount = 1 );

	static RegistryPeer* createRegistryPeer( Registry* registry );

	static MutexPeer* createMutexPeer( Mutex* mutex );

    static ConditionPeer* createConditionPeer( Condition* condition );

	static LibraryPeer* createLibraryPeer( Library* library );

	static FilePeer* createFilePeer( File* file );

	static FileStreamPeer* createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType );

	static FileStreamPeer* createFileStreamPeer( File* file );

	static LocalePeer* createLocalePeer();

	static ResourceBundlePeer* createResourceBundlePeer();
protected:
	SystemToolkit();

	virtual ~SystemToolkit();

	/**
	creates a new ProcessPeer instance. 
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.
	*/
	virtual ProcessPeer* internal_createProcessPeer( Process* process ) = 0;

	/**	
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.
	*/
	virtual ProcessIORedirectionPeer* internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process ) = 0;

	/**
	creates a new ThreadPeer instance.
	
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual ThreadPeer* internal_createThreadPeer( Thread* thread, bool mainThread ) = 0;

	virtual RunLoopPeer* internal_createRunLoopPeer( RunLoop* runLoop ) = 0;

	virtual ThreadManagerPeer* internal_createThreadManagerPeer() = 0;

	
	/**
	*creates a new system peer
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual SystemPeer* internal_createSystemPeer() = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual SemaphorePeer* internal_createSemaphorePeer( long initialCount = 1, long maxCount = 1 ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual RegistryPeer* internal_createRegistryPeer( Registry* registry ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual MutexPeer* internal_createMutexPeer( Mutex* mutex ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
    virtual ConditionPeer* internal_createConditionPeer( Condition* condition ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual LibraryPeer* internal_createLibraryPeer( Library* library ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual FilePeer* internal_createFilePeer( File* file ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual FileStreamPeer* internal_createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual FileStreamPeer* internal_createFileStreamPeer( File* file ) = 0;

	/**
	A port of the FoundationKit to a new platform requires a new class that derives from the 
	SystemToolkit and implements this method.	
	*/
	virtual LocalePeer* internal_createLocalePeer() = 0;

	virtual ResourceBundlePeer* internal_createResourceBundlePeer() = 0;

	/**
	*returns the one and only instance of the system toolkit
	*/
	static SystemToolkit* getSystemToolkit() {
		return systemToolkitInstance;
	}
	static SystemToolkit* systemToolkitInstance;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.1  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.4  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.1  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.4  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
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
*Revision 1.15.2.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.14.2.2  2004/03/11 22:19:59  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.14.2.1  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.14  2003/12/18 05:15:59  ddiego
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
*Revision 1.13.2.1  2003/08/13 21:43:01  ddiego
*thread stuff - fixed bug in auto deleting
*
*Revision 1.13  2003/08/09 02:56:44  ddiego
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
*Revision 1.12.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.12  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:11:52  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.2.3  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.10.2.2  2003/02/18 20:04:40  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.10.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.9.10.1  2002/09/17 18:48:35  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*Revision 1.9  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.8  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SYSTEMTOOLKIT_H__


