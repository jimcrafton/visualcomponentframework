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


//#include <iostream>

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

#ifdef __BORLANDC__
  #include <string.h>
#endif

#ifdef WIN32
  #include <process.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef __MWERKS__
	#include <memory.h>
#else
	#include <wchar.h>
	#include <wctype.h>
	#ifdef VCF_CW_W32
		#include <memory>
	#elif defined(VCF_CW_OSX)
		#include <memory.h>
	#endif
#endif //__MWERKS__
//#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <bitset>
#include <exception>
#include <list>

//

#include "vcf/FoundationKit/VCF.h"

#include "vcf/FoundationKit/FoundationKitSelectLib.h"

#include "vcf/FoundationKit/SmartPtr.h"
#include "vcf/FoundationKit/VCFChar.h"
#include "vcf/FoundationKit/VCFString.h"
#include "vcf/FoundationKit/CommonDefines.h"
#include "vcf/FoundationKit/VCFMath.h"
#include "vcf/FoundationKit/VCFulong64.h"
#include "vcf/FoundationKit/Enumerator.h"
#include "vcf/FoundationKit/Interface.h"
#include "vcf/FoundationKit/Object.h"
#include "vcf/FoundationKit/CommandLine.h"








namespace VCF{
	/**
	\class FoundationKit FoundationKit.h "vcf/FoundationKit/FoundationKit.h"
	The FoundationKit class is used to initialize the Foundation Kit runtime.
	This includes registering the basic classes in the runtime system, such as the 
	correct SystemToolkit implementation, and the ClassRegistry.
	
	FoundationKit::init() MUST be called at start up before anything else in the
	VCF is used.
	FoundationKit::terminate() MUST be called to free up any resources used by the
	FoundationKit.
	
	An example of proper usage looks like this:
	\code
	int main( int argc, char** argv ) 
	{
		VCF::FoundationKit::init(argc, argv);

		//your code here

		VCF::FoundationKit::terminate();

		return 0;
	}
	\endcode

	
	The FoundationKit is cannot be instantiated nor can it be derived from.
	@see SystemToolkit
	@see ClassRegistry
	*/
	class FOUNDATIONKIT_API FoundationKit {
	public:
		/**
		This is a special case exception used \em only for the
		triggering of an asertion, through the call to 
		FoundationKit::assertCondition(). By having this as a 
		special case and \em not deriving from BasicException,
		an assertion is prevented from being caught in a BasicException
		try/catch block.
		*/
		class Assertion : public std::exception {
		public:
			Assertion( const String& msg ) :msg_(msg){}
			
			virtual ~Assertion() throw() {} //make GCC happy :)
			
			virtual const char *what() const throw() {
				return msg_.ansi_c_str();
			}
			
		private:
			String msg_;
		};

		/**
		Initialization takes place here, plus creating the various
		system resources and peer instances.
		*/
		static void init( int argc, char** argv );

		/**
		Frees up any resources allocated in the FoundationKit::init() function.
		*/
		static void terminate();

		/**
		returns the CommandLine contents as passed into
		the FoundationKit::init() function. The CommandLine allows you
		easy access to any command like arguments passed into your application.
		See the CommandLine class for examples of how to use this class. 
		@see CommandLine
		*/
		static const CommandLine& getCommandLine();

		/**
		
		Use this to cause an assert to be fired. Currently an assert is implemented 
		by throwing an exception. An assert is triggered if the condition is false.
		
		As a general rule you don't need to call this directly, instead use the VCF_ASSERT 
		macro's because in addition to a message the macro will be able to also include
		the file and line number where the assertion was triggered, which is more useful.
		@param bool the condition - if this value is false, then an assert is triggered
		and an excpetion is thrown.
		@param failureMessage a string message indicating what failed.
		@see VCF_ASSERT
		*/
		static void assertCondition( bool condition, const String& failureMessage );


	private :
		FoundationKit();
		FoundationKit( const FoundationKit& );
		~FoundationKit();

	};
}; // end of namespace









#include "vcf/FoundationKit/ErrorStrings.h"
#include "vcf/FoundationKit/StringUtils.h"



#include "vcf/FoundationKit/BasicException.h"
#include "vcf/FoundationKit/BasicFileError.h"
#include "vcf/FoundationKit/ClassNotFound.h"
#include "vcf/FoundationKit/CantCreateObjectException.h"
#include "vcf/FoundationKit/FileNotFound.h"
#include "vcf/FoundationKit/InvalidPeer.h"
#include "vcf/FoundationKit/InvalidPointerException.h"
#include "vcf/FoundationKit/NoFreeMemException.h"
#include "vcf/FoundationKit/NoPeerFoundException.h"
#include "vcf/FoundationKit/NoSuchElementException.h"
#include "vcf/FoundationKit/NotImplementedException.h"
#include "vcf/FoundationKit/OutOfBoundsException.h"
#include "vcf/FoundationKit/PropertyChangeException.h"
#include "vcf/FoundationKit/RuntimeException.h"
#include "vcf/FoundationKit/TypeCastException.h"

#include "vcf/FoundationKit/ProcessException.h"


#include "vcf/FoundationKit/Format.h"


#include "vcf/FoundationKit/ProgramInfo.h"
#include "vcf/FoundationKit/PackageInfo.h"


#include "vcf/FoundationKit/Persistable.h"
#include "vcf/FoundationKit/DateTime.h"

#include "vcf/FoundationKit/FilePath.h"

#include "vcf/FoundationKit/Event.h"
#include "vcf/FoundationKit/EventHandler.h"
#include "vcf/FoundationKit/Delegate.h"

#include "vcf/FoundationKit/NotifyEvent.h"



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

//#include "vcf/FoundationKit/VCFRTTIImpl.h"
//#include "vcf/FoundationKit/ClassInfo.h"


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




/**
*resources handling/management
*/
#include "vcf/FoundationKit/Resource.h"
#include "vcf/FoundationKit/ResourceBundle.h"
#include "vcf/FoundationKit/ResourceException.h"






/**
What follows is documentation for the main VCF source documentaion page.

\mainpage

This document is meant, first of all, as a general introduction to the VCF. It 
intends to orient you to the basic concepts of how the VCF is designed and how 
to begin using the features. Here’s what it won’t do: It won’t teach you how 
to program; nor will it show you details about features of the framework (see 
the Reference Manual for this information); nor will it present you with 
step-by-step information about how to build a program. No, this document will 
paint a “big picture” of what’s going on in the VCF. Enough rambling… now onto 
the details.

\par Understanding the kits of the VCF
The VCF is organized into a series of kits. Each one is built into a separate 
library. Here are the main ones:

\li ApplicationKit: This kit contains the items directly used in building an 
application, items like combo boxes, radio buttons, and panels. These are 
generally GUI-oriented items. If you are developing a standard application, you 
will use this kit most often.

\li FoundationKit: This kit contains items foundational to the features in any 
application, items like threads, strings, and XML parsers. Without a doubt, this 
kit will make your application more powerful.

\li GraphicsKit: This kit contains items pertaining to the graphics features in 
any application, items like fonts, lines, and Bezier curves. If you want to add 
pizzazz to your application, this kit is your best bet.


The VCF also has additional secondary kits that perform specific functions. At 
the moment, we have three:
\li OpenGLKit: This kit facilitates the display of OpenGL code within an application. If you wish to use three-dimensional graphics, an OpenGLControl will be a good friend.

\li NetworkKit: This kit contains items pertaining to network interactions in any 
application, containing items like sockets. If your application demands 
multi-party interaction, use this kit.

\li RemoteObjectKit: This is kit was started as an experiment to determine if the 
  RTTI functions could be used to create a small library suitable for distributed 
  objects, something akin to COM/DCOM but much more practical and easy to use. At 
  this point it is more of a proof of concept - it works, but needs to be revamped 
  before using it for anything more than experiments.

Since components’ interactions with the operating system vary from system to 
system, each kit contains implementations of the generalized components. Classes 
prefaced with Win32 pertain to 32-bit Windows environments; those prefaced with 
Linux, to Linux; with OSX, to Mac OS X. Generally, you need not access the 
specific implementation; you can keep to the generalized classes. (In other 
words, use class VCF::Thread, not class VCF::Win32Thread.). These classes also 
represent the concrete implementations of the various peer interfaces that are 
used to describe the various OS services. Peer classes are used by the internals 
of the framework.

\par Using examples to start your application
A standard download of the VCF will contain an examples directory, replete with 
basic demonstrations of features of the VCF. If you are completely unaware of how 
to use a feature, it is best first to consult one of these examples.

For example, if you want to use a slider control (like one Windows uses to control 
the volume), use VisualStudio to open up the project in examples/Sliders. If you 
build this project, it will appear in the examples/Sliders/vcXX/Debug directory. 
Here, you will see horizontal and vertical sliders, sliders with different begin 
and end values, sliders which send update events upon moving, etc. You can read 
the code and use these ideas to begin your application.


If you aren’t sure which example contains a certain item, perform a recursive 
search through the examples directory with your item’s name. Then open up one of 
the projects that contains the item.

\par Fine-tuning your application via the source manual
Of course, examples can’t exhaustively demonstrate all of the features of an 
application. Thus the API is available to facilitate your creative use of the 
features. To view this, see the Source Manual. The Class List will show a list 
of the classes.

When you click on a class, you will see its inheritance diagram. If you wish to 
view the class’s inherited members, click the “List of all members” link.

\par Sifting through the functions
The purpose of each function is designed to be easily understandable and not 
cryptic. If the class is a control, a paint method will paint the control; you 
should not call this method as it is called automatically.


Sometimes methods have models which represent a collection of multiple items. For 
example, a ListBoxControl (a vertical list of items) uses a ListModel (available 
via the getListModel command) to manage a group of ListItems. To build a list, 
create a DefaultListItem (an implementation of ListItem), add it to the ListModel 
via addItem, and it will be added to the ListBoxControl.

Other methods use events. There may be various event-handler methods present in 
a class. Again, you will usually not access these directly.


A control can be positioned and sized via the setBounds method, or via setLeft, 
setRight, setTop, setBottom, setWidth, and setHeight methods. These are 
universally inherited from the base Control class.

Some items use enumerations to specify particular functionalities. You can click 
on the class name to view a full description of the enumeration. An example from 
the directory should help you flesh this out.


\par Understanding accessories
If you wish to add event handlers to a control, various delegates are accessible 
in a class. The delegate names should adequately describe their functionality as 
distinguished from each other. An EventHandler can be added to each delegate to 
handle an event occurring at a certain point in the code. There are several types 
of EventHandlers; you can use the \c GenericEventHandler or fetch the specific type 
of EventHandler for your specific need.

In the following example, an EventHandler is added to a ListBoxControl, calling 
the function onChange every time the selection is changed in the ListBox.

\code
VCF::ListBoxControl *lbc = new VCF::ListBoxControl();
lbc->SelectionChanged += new
   ListModelEventHandler<ThisClassName>(this,
   &ThisClassName::onChange,
   “ThisClassName::onChange”);
\endcode

Sometimes, a method is available to add events, in lieu of a Delegate.

\par Going back to the original source
If you need to know the exact details of how a function acts, you may access the 
original source code. Sometimes, you may need to access the specific 
implementation for your operating system. It will be available in the 
src/vcf/[KitName]/ directory. Be sure to read the class – header and cxx file – 
thoroughly so that you understand everything that is going on.

\par Suggesting new functionality
Suppose you wish to change how a function operates, or that you wish to add new 
functionality to a class. You can change the source code directly to make this 
happen. You may want to suggest the change in the forums or talk over the change 
to ensure that you don’t unnecessarily break something.

Or suppose that you wish to create your own custom classes. You can inherit from 
a base class much as the already existing classes do. For example, you can 
inherit from class VCF::CustomControl to make your own control. You may need to 
write the paint method, much as the other controls do, to be sure that it is 
painted correctly.

If you run into trouble, be sure to pose a question in the forums. Chances are 
that someone will be able to relate to your concern.

*/



/**
*CVS Log info
*$Log$
*Revision 1.7  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.6.2.6  2006/03/26 22:37:35  ddiego
*minor update to source docs.
*
*Revision 1.6.2.5  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.6.2.4  2006/03/10 21:49:33  ddiego
*updates to color example and some documentation.
*
*Revision 1.6.2.3  2006/03/06 03:48:30  ddiego
*more docs, plus update add-ins, plus migrated HTML browser code to a new kit called HTMLKit.
*
*Revision 1.6.2.2  2005/12/28 20:43:40  kiklop74
*Fixed error - missing strcmp
*
*Revision 1.6.2.1  2005/12/16 02:01:09  obirsoy
*. added boost smart_ptr library.
*
*Revision 1.6  2005/07/13 01:55:43  ddiego
*doc updates.
*
*Revision 1.5  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.5  2005/04/17 16:11:31  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.4.2.4  2005/04/11 17:07:10  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.4.2.3  2005/03/14 05:44:51  ddiego
*added the Formatter class as part of the process of getting rid of the var arg methods in System and StringUtils.
*
*Revision 1.4.2.2  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.4.2.1  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.4  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.4  2004/09/15 21:14:28  ddiego
*added support for getting program info from resource bundle.
*
*Revision 1.3.2.3  2004/08/23 22:26:06  marcelloptr
*added NotImplementedException
*
*Revision 1.3.2.2  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.3.2.1  2004/08/17 05:01:32  marcelloptr
*improved macros for library selection
*
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
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


