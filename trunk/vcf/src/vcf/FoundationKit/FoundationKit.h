#ifndef _VCF_FOUNDATIONKIT_H__
#define _VCF_FOUNDATIONKIT_H__
//FoundationKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifdef _MSC_VER
//disable warnings on 255 char debug symbols
	#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
	#pragma warning (disable : 4231)

	#pragma warning (disable : 4251)

	#pragma warning (disable : 4275)

#endif


#include <iostream>

#include <typeinfo>



#include <algorithm>
#include <math.h>
#ifdef VCF_GCC
//#include <varargs.h>
#include <stdarg.h>
#endif //VCF_GCC


#ifdef macintosh
	#include <string.h>
	#include <extras.h>
#endif

#ifdef WIN32
  #include <process.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
//#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <bitset>
#include <exception>
#include <list>

//

#include "vcf/FoundationKit/FoundationKitSelectLib.h"
#include "vcf/FoundationKit/VCF.h"
#include "vcf/FoundationKit/VCFChar.h"
#include "vcf/FoundationKit/VCFString.h"
#include "vcf/FoundationKit/CommonDefines.h"
#include "vcf/FoundationKit/VCFMath.h"
#include "vcf/FoundationKit/VCFulong64.h"
#include "vcf/FoundationKit/Enumerator.h"
#include "vcf/FoundationKit/Interface.h"
#include "vcf/FoundationKit/Object.h"

#include "vcf/FoundationKit/BasicException.h"
#include "vcf/FoundationKit/CantCreateObjectException.h"
#include "vcf/FoundationKit/ErrorStrings.h"
#include "vcf/FoundationKit/InvalidPeer.h"
#include "vcf/FoundationKit/InvalidPointerException.h"
#include "vcf/FoundationKit/NoFreeMemException.h"
#include "vcf/FoundationKit/NoPeerFoundException.h"
#include "vcf/FoundationKit/NoSuchElementException.h"
#include "vcf/FoundationKit/OutOfBoundsException.h"
#include "vcf/FoundationKit/PropertyChangeException.h"
#include "vcf/FoundationKit/RuntimeException.h"
#include "vcf/FoundationKit/TypeCastException.h"
#include "vcf/FoundationKit/ClassNotFound.h"
#include "vcf/FoundationKit/BasicFileError.h"
#include "vcf/FoundationKit/FileNotFound.h"
#include "vcf/FoundationKit/ClassNotFound.h"
#include "vcf/FoundationKit/ProcessException.h"

#include "vcf/FoundationKit/PackageInfo.h"

#include "vcf/FoundationKit/Persistable.h"
#include "vcf/FoundationKit/DateTime.h"

#include "vcf/FoundationKit/FilePath.h"

#include "vcf/FoundationKit/Event.h"
#include "vcf/FoundationKit/EventHandler.h"
#include "vcf/FoundationKit/Delegate.h"

#include "vcf/FoundationKit/NotifyEvent.h"

#include "vcf/FoundationKit/StringUtils.h"

#include "vcf/FoundationKit/Class.h"
#include "vcf/FoundationKit/InterfaceClass.h"
#include "vcf/FoundationKit/Enum.h"
#include "vcf/FoundationKit/PropertyChangeException.h"

#include "vcf/FoundationKit/BasicFileError.h"
#include "vcf/FoundationKit/FileIOError.h"
#include "vcf/FoundationKit/MemStreamUtils.h"
#include "vcf/FoundationKit/Stream.h"
#include "vcf/FoundationKit/TextInputStream.h"
#include "vcf/FoundationKit/TextOutputStream.h"
#include "vcf/FoundationKit/BasicInputStream.h"
#include "vcf/FoundationKit/BasicOutputStream.h"
#include "vcf/FoundationKit/PropertyChangeEvent.h"
#include "vcf/FoundationKit/VariantData.h"
#include "vcf/FoundationKit/Property.h"
#include "vcf/FoundationKit/Method.h"
#include "vcf/FoundationKit/Field.h"
#include "vcf/FoundationKit/ClassRegistry.h"
#include "vcf/FoundationKit/ObjectWithEvents.h"

#include "vcf/FoundationKit/VCFRTTIImpl.h"
#include "vcf/FoundationKit/ClassInfo.h"


#include "vcf/FoundationKit/Runnable.h"
#include "vcf/FoundationKit/Waitable.h"

#include "vcf/FoundationKit/File.h"
#include "vcf/FoundationKit/Directory.h"
#include "vcf/FoundationKit/Library.h"
#include "vcf/FoundationKit/Locales.h"
#include "vcf/FoundationKit/FileStream.h"
#include "vcf/FoundationKit/Registry.h"
#include "vcf/FoundationKit/System.h"
#include "vcf/FoundationKit/SynchObject.h"
#include "vcf/FoundationKit/Mutex.h"
#include "vcf/FoundationKit/Condition.h"
#include "vcf/FoundationKit/SemaphorePeer.h"
#include "vcf/FoundationKit/Semaphore.h"
#include "vcf/FoundationKit/Lock.h"
#include "vcf/FoundationKit/Parser.h"
#include "vcf/FoundationKit/SystemToolkit.h"
#include "vcf/FoundationKit/FilePeer.h"
#include "vcf/FoundationKit/ErrorLog.h"
#include "vcf/FoundationKit/FileStreamPeer.h"
#include "vcf/FoundationKit/LibraryPeer.h"
#include "vcf/FoundationKit/MemoryStream.h"
#include "vcf/FoundationKit/MutexPeer.h"
#include "vcf/FoundationKit/RegistryPeer.h"
#include "vcf/FoundationKit/ConditionPeer.h"
#include "vcf/FoundationKit/SystemPeer.h"
#include "vcf/FoundationKit/StringUtils.h"
#include "vcf/FoundationKit/Thread.h"
#include "vcf/FoundationKit/ThreadPeer.h"
#include "vcf/FoundationKit/ThreadEvent.h"
#include "vcf/FoundationKit/VCFProcess.h"
#include "vcf/FoundationKit/ProcessPeer.h"
#include "vcf/FoundationKit/XMLParser.h"
#include "vcf/FoundationKit/VariantDataStream.h"
#include "vcf/FoundationKit/CommandLine.h"

namespace VCF{
	/**
	*initializes the Foundation Kit runtime.
	*This includes registering the basic classes in the runtime system
	*this declared this way for consistencies sake
	*FoundationKit::init() MUST be called at start up before anything else in the
	*VCF is used.
	*FoundationKit::terminate() MUST be called to free up any resources used by the
	*FoundationKit
	*/
	class FOUNDATIONKIT_API FoundationKit {
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

		/**
		returns the CommandLine contents as passed into
		the FoundationKit::init() function
		*/
		static CommandLine getCommandLine();

		static void assertCondition( bool condition, const String& failureMessage );
	};
}; // end of namespace


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.13.2.1  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12  2004/01/20 01:54:54  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.8.2.3  2004/01/17 06:09:49  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.8.2.2  2004/01/11 19:57:53  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.8.2.6  2004/03/11 22:19:58  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.8.2.5  2004/02/21 03:26:28  ddiego
*updates for OSX porting
*
*Revision 1.8.2.4  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.8.2.3  2004/01/17 06:09:49  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.8.2.2  2004/01/11 19:57:53  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*Revision 1.8  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.2  2003/10/24 04:03:20  ddiego
*More header musical chairs
*
*Revision 1.7.2.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.7  2003/08/09 02:56:42  ddiego
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
*Revision 1.6.2.2  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.6.2.1  2003/05/30 04:13:10  ddiego
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
*Revision 1.6  2003/05/17 20:36:58  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/23 03:23:42  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.8.3  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.4.8.2  2003/02/18 20:01:02  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.4.8.1  2002/12/27 23:04:28  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.4  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.3.4.4  2002/07/21 05:02:50  ddiego
*added more stuff for configuration management, fixed the FilePath bug
*add a removeAllHandlers() to VCF::Delegate class
*
*Revision 1.3.4.3  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.3.4.2  2002/07/03 07:13:00  marcelloptr
*minor fixes
*
*Revision 1.3.4.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.3  2002/06/18 21:18:32  ddiego
*added FilePath
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.8  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.1.2.7  2002/04/03 19:37:16  zzack
*include style changed
*
*Revision 1.1.2.6  2002/03/27 04:24:55  cesarmello
*Linux bugfixes
*
*Revision 1.1.2.5  2002/03/26 02:35:32  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.1.2.4  2002/03/25 04:25:42  ddiego
*added some of the BSD license header plus the cvs log stamp to the
*new foundation kit and network global headers
*
*
*/


#endif // _VCF_FOUNDATIONKIT_H__


