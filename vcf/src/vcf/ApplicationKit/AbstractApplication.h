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

class AcceleratorKey;

/**
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
	*returns the application's resource bundle, which
	*contains all the application's resources, such as
	*images, strings, or form files, or other custom
	*data.
	*@return ResourceBundle* the app's resource bundle
	*@see ResourceBundle
	*/
	ResourceBundle* getResourceBundle();

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
	Frame* createFrame( const String& frameClassName );

	/**
	*Loads an already existing Frame from a frame derived class name
	*@param Frame a pointer to new instance of the type specified
	*in the frameClassName argument.
	*/
	void loadFrame( Frame** frame );

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
	function here is allow event posting to be bale to happen through
	*an application where appropriate.
	*@see UIToolkit::postEvent()
	*/
	virtual void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true );


	AcceleratorKey* getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	void addAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask, EventHandler* eventHandler );

	void addAcceleratorKey( AcceleratorKey* accelerator );

protected:
	ApplicationPeer* applicationPeer_;
	String applicationName_;
private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.15.2.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.14.2.1  2004/03/08 04:41:07  ddiego
*minor changes to DocumentManager - allow the use of
*Actions so that other UI elements can be added besides menu
*items (like Toolbar items)
*
*Revision 1.14  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.13.2.1  2003/09/12 00:09:31  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.13  2003/08/09 02:56:42  ddiego
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
*Revision 1.12.2.1  2003/05/30 04:13:10  ddiego
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
*Revision 1.12  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.10.2  2003/03/23 03:23:43  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.10.1  2003/03/12 03:09:11  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.10.12.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.10  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.9  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTAPPLICATION_H__


