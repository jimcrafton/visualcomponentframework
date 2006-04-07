//LibraryApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//LibraryApplication.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"
#include "vcf/ApplicationKit/ApplicationResourceBundle.h"

using namespace VCF;

LibraryApplication::LibraryApplication():
	resourceBundle_(NULL)
{
	ApplicationKit::init(0, NULL);



	applicationPeer_ = UIToolkit::createApplicationPeer();
	applicationPeer_->setApplication( this );

	applicationName_ = "";
/*
#if defined( WIN32 ) && defined ( _MSC_VER )
	//load the BlacBox error trapper
	try {
		Library lib( L"BlackBox.dll" );
	}
	catch (...) {
		StringUtils::trace( "Unable to load the BlackBox error detection library\n" );
	}
#endif
	*/
}

LibraryApplication::~LibraryApplication()
{
	if ( NULL != resourceBundle_ ) {
		resourceBundle_->free();
	}
	resourceBundle_ = NULL;

	delete applicationPeer_;
	applicationPeer_ = NULL;

	ApplicationKit::terminate();
}

void LibraryApplication::setName( const String& name )
{
	applicationName_ = name;

	std::map<String,LibraryApplication*>::iterator found = 	LibraryApplication::namedLibraryAppMap->find( applicationName_ );
	if ( found != LibraryApplication::namedLibraryAppMap->end() ) {
		(*LibraryApplication::namedLibraryAppMap)[ applicationName_ ] = this;
	}
}

GraphicsResourceBundle* LibraryApplication::getResourceBundle()
{
	if ( NULL == resourceBundle_ ) {
		//create it on demand
		resourceBundle_ = new ApplicationResourceBundle(this);
	}

	return resourceBundle_;
}

Enumerator<VCF::LibraryApplication*>* LibraryApplication::getRegisteredLibraries()
{
	return LibraryApplication::namedLibAppContainer->getEnumerator();
}

void LibraryApplication::registerLibrary( VCF::LibraryApplication* libraryApp )
{
	(*LibraryApplication::namedLibraryAppMap)[ libraryApp->getName() ] = libraryApp;
}


void LibraryApplication::unRegisterLibrary( VCF::LibraryApplication* libraryApp )
{
	std::map<String,LibraryApplication*>::iterator found = 	LibraryApplication::namedLibraryAppMap->find( libraryApp->getName() );
	if ( found != LibraryApplication::namedLibraryAppMap->end() ) {
		LibraryApplication::namedLibraryAppMap->erase( found );
	}
}

VCF::LibraryApplication* LibraryApplication::getRegisteredLibraryApplication( const String& libName )
{
	VCF::LibraryApplication* result = NULL;

	std::map<String,LibraryApplication*>::iterator found = 	LibraryApplication::namedLibraryAppMap->find( libName );
	if ( found != LibraryApplication::namedLibraryAppMap->end() ) {
		result = found->second;
	}

	return result;
}

void LibraryApplication::load( VCF::LibraryApplication* libraryApp )
{

}

void LibraryApplication::unload( VCF::LibraryApplication* libraryApp )
{

}

void LibraryApplication::initLibraryRegistrar()
{
	LibraryApplication::namedLibraryAppMap = new std::map<String,LibraryApplication*>();
	LibraryApplication::namedLibAppContainer = new EnumeratorMapContainer<std::map<String,LibraryApplication*>, LibraryApplication*>();

	LibraryApplication::namedLibAppContainer->initContainer( *LibraryApplication::namedLibraryAppMap );
}

void LibraryApplication::clearLibraryRegistrar()
{
	delete LibraryApplication::namedLibraryAppMap;
	LibraryApplication::namedLibraryAppMap = NULL;

	delete LibraryApplication::namedLibAppContainer;
	LibraryApplication::namedLibAppContainer = NULL;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/03/10 21:49:32  ddiego
*updates to color example and some documentation.
*
*Revision 1.5.2.1  2005/12/08 21:09:18  kiklop74
*fixes for borland compiler
*
*Revision 1.5  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 07:09:18  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3.2.1  2004/12/19 07:09:18  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/27 19:54:56  marcelloptr
*Color changes
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.10  2003/08/09 02:56:45  ddiego
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
*Revision 1.9.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.9.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.9  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:13:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.8.2  2003/02/05 01:26:13  notandor
*Fixed a compilation error on VC6SP5
*
*Revision 1.7.8.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.6.6.1  2002/09/10 04:07:51  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.6  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.2  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.5.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.5  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.4  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


