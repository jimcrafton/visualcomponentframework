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

// Common definitions
#include "vcf/FoundationKit/FrameworkConfig.h"

#ifdef VCF_MSC
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

#ifdef VCF_BCC
  #include <string.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef VCF_CW
	#include <memory.h>
#else
	#include <wchar.h>
	#include <wctype.h>
	#ifdef VCF_CW_W32
		#include <memory>
	#elif defined(VCF_CW_OSX)
		#include <memory.h>
	#endif
#endif //VCF_CW
//#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <bitset>
#include <exception>
#include <list>


#ifdef VCF_WIN
	#include <process.h>
	//include std windoze headers for peers....
	#include <windows.h>
	//#include "Rpcdce.h" //make sure to link with Rpcrt4.lib
	#include <commctrl.h> //make sure to link with comctl32.lib
	#include <shlobj.h>
	#include <shobjidl.h> // some interfaces were moved from shlobj.h in Vista
#endif //VCF_WIN


#include "vcf/FoundationKit/FoundationKitSelectLib.h"

#include "vcf/FoundationKit/SmartPtr.h"
#include "vcf/FoundationKit/VCFChar.h"
#include "vcf/FoundationKit/VCFString.h"
#include "vcf/FoundationKit/CommonDefines.h"
#include "vcf/FoundationKit/VCFMath.h"
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
Components...
*/

#include "vcf/FoundationKit/BadComponentStateException.h"
#include "vcf/FoundationKit/ComponentEvent.h"
#include "vcf/FoundationKit/Component.h"
#include "vcf/FoundationKit/ComponentInfo.h"


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



#endif // _VCF_FOUNDATIONKIT_H__

/**
$Id$
*/
