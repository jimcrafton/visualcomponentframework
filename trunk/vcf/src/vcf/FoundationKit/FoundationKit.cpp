//FoundationKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/MessageLoader.h"
#include "vcf/FoundationKit/TextCodec.h"
#include "vcf/FoundationKit/StringsMessageLoader.h"
#include "vcf/FoundationKit/ThreadManager.h"


#include "vcf/FoundationKit/RTTIMacros.h"

#include "vcf/FoundationKit/FoundationKitRTTI.inl"

//#include "utils/Dictionary.h"

using namespace VCF;



SystemToolkit* SystemToolkit::systemToolkitInstance = NULL;

System* System::systemInstance = NULL;

ClassRegistry* ClassRegistry::registryInstance_ = NULL;

static CommandLine foundationKitCommandLine;

void FoundationKit::init( int argc, char** argv )
{
	try {
		foundationKitCommandLine.splitLine( argc, argv );

		SystemToolkit::create();

#ifdef _VCF_DEBUG_NEW
		Object::accessMutex_ = NULL;
		Object::accessMutex_ = new Mutex();
		if ( NULL == Object::accessMutex_ ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("access mutex is NULL!") );
		}
#endif
		System::create();

		ClassRegistry::create();


		MessageLoader::registerMessageLoader( "text/strings", new StringsMessageLoader() );

		ThreadManager::create();

		PackageManager::init();

	}
	catch ( BasicException& e ) {
		StringUtils::trace( "unknown exception occurred during FoundationKit::init()\n\terror is: " +
												e.getMessage() + "\n" );
		throw e;
	}
	catch ( ... ) {
		StringUtils::trace( "unknown exception occurred during FoundationKit::init()\n" );
		throw BasicException("unknown exception occurred during FoundationKit::init()");
	}

	{
		try {
			REGISTER_CLASSINFO_EXTERNAL( ObjectWithEvents );
		}
		catch ( BasicException& e ) {
			StringUtils::trace( "exception attempting to register basic objects, error: " +
			e.getMessage() + "\n" );
			throw e;
		}

	}
}

void FoundationKit::terminate()
{
	TextCodec::internal_freeAllRegisteredCodecs();

	MessageLoader::internal_freeAllRegisteredMessageLoaders();

	System::terminate();

	ClassRegistry::terminate();

	SystemToolkit::terminate();

	ThreadManager::terminate();

	PackageManager::terminate();

#ifdef _VCF_DEBUG_NEW
	Mutex* mutex = Object::accessMutex_;
	Object::accessMutex_ = NULL;
	mutex->free();
#endif

#ifdef _DEBUG
	Object::dumpDebugInfo();
#endif


}



const CommandLine& FoundationKit::getCommandLine()
{
	return foundationKitCommandLine;
}

void FoundationKit::assertCondition( bool condition, const String& failureMessage )
{
	if ( !condition ) {

		throw FoundationKit::Assertion( L"Assertion failure: " + failureMessage );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/03/06 03:48:30  ddiego
*more docs, plus update add-ins, plus migrated HTML browser code to a new kit called HTMLKit.
*
*Revision 1.3.2.1  2005/09/03 14:03:53  ddiego
*added a package manager to support package info instances, and
*fixed feature request 1278069 - Background color of the TableControl cells.
*
*Revision 1.3  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2.4.2  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2.4.1  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/13 16:05:57  marcelloptr
*minor change for Unicode
*
*Revision 1.1.2.5  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/05/03 03:44:52  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.19  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.18  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.16.2.5  2004/02/21 03:27:08  ddiego
*updates for OSX porting
*
*Revision 1.16.2.4  2004/02/16 00:01:53  ddiego
*added some commetns to the Localization example
*
*Revision 1.16.2.3  2004/02/15 20:24:02  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.16.2.2  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.16.2.1  2004/01/05 05:45:17  ddiego
**** empty log message ***
*
*Revision 1.16.2.1  2004/01/05 05:45:17  ddiego
**** empty log message ***
*
*Revision 1.16  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.15.2.5  2003/10/24 04:03:36  ddiego
*More header musical chairs
*
*Revision 1.15.2.4  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.15.2.3  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.15.2.2  2003/09/16 02:41:40  ddiego
*added a small fix for adding a mutex to prevent multithreaded programs from
*crashing in debug mode.
*
*Revision 1.15.2.1  2003/09/12 16:46:33  ddiego
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
*Revision 1.15  2003/08/09 02:56:45  ddiego
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
*Revision 1.14.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.14.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.14  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.14.3  2003/05/15 03:01:03  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.13.14.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.14.1  2003/03/12 03:13:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.12  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.2  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.11.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.11  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


