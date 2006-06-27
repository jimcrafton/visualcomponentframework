#ifndef _VCF_ABSTRACTAPPLICATION_H__
#define _VCF_ABSTRACTAPPLICATION_H__
//AbstractApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ApplicationPeer;

class ResourceBundle;

class Frame;
class Window;
class Dialog;

class AcceleratorKey;

/**
\class AbstractApplication AbstractApplication.h "vcf/ApplicationKit/AbstractApplication.h"
*An AbstractApplication is a base class for deriving new application types
*Currently there are two main types, standard Application classes, which
*represent the current process the application is associated with and of which there
*should only be one, and LibraryApplication classes which are tied to
*shared librarys or DLL's.
*An application can act as a grouping place for a set of logically connect
*group of behaviours. For example, you might consider writing an HTML editor
*and thus want to create an <code>HTMLEditorApplication</code> class. Later
*you might expand things and break out the text editing functionality into a
*separate library, thus create a <code>TextEditorLibraryApplication</code>
*class. You would still have a primary application class ( the HTMLEditorApplication )
*of which there could be only one per process.
*However, unlike other frameworks, an AbstractApplication instance is <b><i>NOT</i></b>
a requirement in the VCF. It is entirely possible to use the VCF <b>without</b> an application
*object. For example, you may have an existing MFC or raw Win32 application that
*you wish to enhance using controls or other classes from the VCF. To allow this
*certain functions are declared again in the AbstractApplication class that were
*previously declared in the UIToolkit to allow for a central place to call them
*when using an application object, but still allowing the framework to operate
*correctly without the application instance when appropriate. Please note
*that while these functions may be declared again, they are not reimplmented. All
*the AbstractApplication functions like postEvent() or getAccelerator() do is to
*call the approriate UIToolkit functions, so no implmentation code is duplicated.
*/
class APPLICATIONKIT_API AbstractApplication : public ObjectWithEvents {
public:
	AbstractApplication();

	virtual ~AbstractApplication();

	/**
	*allows for the use of programmable, user friendly names for Applications
	*/
	String getName() {
		return applicationName_;
	}

	virtual void setName( const String& name );
	/**
	*This happens after the Application object is constructed, after the initialize() method,
	*and just before the app's run() method is called
	*successful. if false, it calls terminate() and then kills the app process.
	*this method also builds the accellerator table used for keyboard shortcuts
	*@return bool this tells whether or not the initialization of the application was
	*/
	virtual bool initRunningApplication() = 0;

	/**
	*terminates the running application. This is called during normal shutdown of an
	*application object. You should override this function if your application created
	*resources and release those resources here.
	*/
	virtual void terminateRunningApplication() = 0;

	/**
	*retreives the system specific Peer for this application
	*@return ApplicationPeer - the application Peer
	*@see ApplicationPeer
	*/
	ApplicationPeer* getPeer();
	

	/**
	This returns the application's resource bundle. If the application in question
	is the application instance that represents the running process/program (
	in other words, the instance returned by Application::getRunningInstance() )
	then the resource bundle returned is the same that you would get by calling
	System::getResourceBundle(). However, if the application instance is
	a LibraryApplication, then the resource bundle is unique to that library, and
	independant from that of the main application's resource bundle.
	
	This is re-implemented in LibraryApplication class.
	*/
	virtual GraphicsResourceBundle* getResourceBundle();

	/**
	*returns the full path for the application executable
	*@return String the fully qualified path to the executable
	*that the Application represents.
	*<p>
	*for example:
	*<pre>
		String appFileName = Application::getRunningInstance()->getFileName();
		Sting msg = StringUtils::formatString( "The app file name is: %s", appFileName.c_str() );
		Dialog::showMessage( msg );
	*</pre>
	*/
	String getFileName();

	/**
	*Creates a Frame from a frame derived class name
	*@param String the name of the frame derived class name
	*this is also the name of the VFF (Visual Form File) resource
	*which is loaded. If this can't be found or the class name
	*doesn't exist in the ClassRegistry then the return is NULL.
	*@return Frame a pointer to new instance of the type specified
	*in the frameClassName argument. NULL if the form resource doesn't exist
	*or the class doesn't exist. Otherwise it represent a full loaded
	*instance, using the data from the resource VFF.
	*/
	Window* createWindow( Class* windowClass );

	Dialog* createDialog( Class* dialogClass );

	/**
	*Loads an already existing Frame from a frame derived class name
	*@param Frame a pointer to new instance of the type specified
	*in the frameClassName argument.
	*/
	void loadWindow( Window* window );

	void loadDialog( Dialog* dialog );

	/**
	*This virtual function is called during the event loops idle phase.
	*Ovveride this fucntion for application specific processing that can be done during
	*idle time.
	*/
	virtual void idleTime();

	/**
	*call this method to post an event. You can override it ot provide
	*extra behaviour. The default behaviour is to simply pass the event
	*along to the UIToolkit::postEvent() method. The idea in placing this
	function here is allow event posting to be able to happen through
	*an application where appropriate.
	*@see UIToolkit::postEvent()
	*/
	virtual void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true );


	AcceleratorKey* getAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src );

	void addAcceleratorKey( const VirtualKeyCode& keyCode, const uint32& modifierMask, EventHandler* eventHandler );

	void addAcceleratorKey( AcceleratorKey* accelerator );

protected:
	ApplicationPeer* applicationPeer_;
	String applicationName_;
private:
};


}; //end of namespace VCF


#endif // _VCF_ABSTRACTAPPLICATION_H__

/**
$Id$
*/
