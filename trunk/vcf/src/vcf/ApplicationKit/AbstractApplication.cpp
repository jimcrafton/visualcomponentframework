//AbstractApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AbstractApplication.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"
#include "vcf/ApplicationKit/VFFInputStream.h"
#include "vcf/ApplicationKit/VFFOutputStream.h"


using namespace VCF;

AbstractApplication::AbstractApplication():
	applicationPeer_(NULL)
{

}

AbstractApplication::~AbstractApplication()
{

}

ApplicationPeer* AbstractApplication::getPeer()
{
	return applicationPeer_;
}

ResourceBundle* AbstractApplication::getResourceBundle()
{
	return applicationPeer_->getResourceBundle();
}

String AbstractApplication::getFileName()
{
	return applicationPeer_->getFileName();
}

Frame* AbstractApplication::createFrame( const String& frameClassName )
{
	Frame* result = NULL;

	ResourceBundle* resBundle = getResourceBundle();
	if ( NULL != resBundle ){
		String vffString = resBundle->getVFF( frameClassName );

		if ( false == vffString.empty() ){
			BasicInputStream bis( vffString );
			VFFInputStream vis( &bis );
			vis.readComponent( (Component**)&result );
		}
		else{
			String errMsg = "VFF Resource \"" + frameClassName + "\" has no data.";
			throw InvalidPointerException( MAKE_ERROR_MSG( errMsg ) );
		}
	}
	else{
		String errMsg = "Resource \"" + frameClassName + "\" not found.";
		throw InvalidPointerException( MAKE_ERROR_MSG( errMsg ) );
	}

	return result;
}

void AbstractApplication::loadFrame( Frame** frame )
{

	String frameClassName = (*frame)->getClassName();

	ResourceBundle* resBundle = getResourceBundle();
	if ( NULL != resBundle ){
		String vffString = resBundle->getVFF( frameClassName );

		if ( false == vffString.empty() ){
			BasicInputStream bis( vffString );
			VFFInputStream vis( &bis );
			vis.readComponentInstance( *frame );
		}
		else{
			String errMsg = "VFF Resource \"" + frameClassName + "\" has no data.";
			throw InvalidPointerException( MAKE_ERROR_MSG( errMsg ) );
		}
	}
	else{
		String errMsg = "Resource \"" + frameClassName + "\" not found.";
		throw InvalidPointerException( MAKE_ERROR_MSG( errMsg ) );
	}
}

void AbstractApplication::idleTime()
{

}

void AbstractApplication::postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	UIToolkit::postEvent( eventHandler, event, deleteHandler );
}

AcceleratorKey* AbstractApplication::getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask )
{
	return UIToolkit::getAccelerator( keyCode, modifierMask );
}

void AbstractApplication::addAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask, EventHandler* eventHandler )
{
	AcceleratorKey* accelerator = new AcceleratorKey( NULL, keyCode, modifierMask, eventHandler );
	addAcceleratorKey( accelerator );
}

void AbstractApplication::addAcceleratorKey( AcceleratorKey* accelerator )
{
	UIToolkit::registerAccelerator( accelerator );
}

void AbstractApplication::setName( const String& name )
{
	applicationName_ = name;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:04  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.17  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.4.2  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.13.4.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
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
*Revision 1.12.2.2  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.12.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.12  2003/05/17 20:37:43  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:12:51  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.8.1  2003/01/08 00:19:56  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.6.2  2002/09/10 04:07:49  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.9.6.1  2002/08/01 19:16:26  ddiego
*added support for create new files from the File | New... menu
*this displays a list of file templates which are read from the Object
*Repository. The FilePath had a bug with the FilePath::isRelative() function
*fixed a display bug with the CheckBoxControl and the fixed size of hte
*of the check box being too small
*
*Revision 1.9  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:52:36  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.8  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.7  2002/02/14 05:04:52  ddiego
*documentation...
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


