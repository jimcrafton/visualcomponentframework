//Win32Application.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Application.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/Win32GraphicsResourceBundle.h"


using namespace VCFWin32;
using namespace VCF;


/*
class Win32ApplicationResBundle : public Win32GraphicsResourceBundle {
public:
	Win32ApplicationResBundle( ApplicationPeer* peer ): Win32GraphicsResourceBundle(), appPeer_(peer){
		
	}
protected:
	virtual HINSTANCE getResourceInstance() {

		HINSTANCE result = NULL;

		if ( NULL != this->appPeer_ ) {
			result = (HINSTANCE)appPeer_->getHandleID();
		}
		else {
			//throw exception !!
		}
		return result;
	}

	ApplicationPeer* appPeer_;
};


class AppKitGraphicsResourceBundle : public GraphicsResourceBundle {
public:
	AppKitGraphicsResourceBundle(Win32Application* peer) : GraphicsResourceBundle(){
		delete graphicsResPeer_;

		graphicsResPeer_ = new Win32ApplicationResBundle(peer);
		peer_ = dynamic_cast<ResourceBundlePeer*>( graphicsResPeer_ );
	}
};
*/



Win32Application::Win32Application()
{
	//System::internal_replaceResourceBundleInstance( new AppKitGraphicsResourceBundle(this) );


	instanceHandle_ = NULL;
}

Win32Application::~Win32Application()
{
	
}

bool Win32Application::initApp()
{
	/**
	*set the HandleID if it is still NULL
	*Dy default it should be set in the DLLMain()
	*function if this is a LibraryApplication
	*/
	if ( NULL == instanceHandle_ ) {
		instanceHandle_ = ::GetModuleHandle( NULL );
	}
#ifdef __GNUWIN32__
	InitCommonControls();
#else
	INITCOMMONCONTROLSEX controlsToInit = {0};
	controlsToInit.dwSize = sizeof(controlsToInit);
	controlsToInit.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx( &controlsToInit );
#endif
	HRESULT hr = OleInitialize(NULL);
	if ( !(SUCCEEDED(hr)) ){
		throw BasicException("OleInitialize failed");
	}

	return true;
}

void Win32Application::terminateApp()
{
	OleFlushClipboard();
	OleUninitialize();
}

VCF::AbstractApplication* Win32Application::getApplication()
{
	return this->app_;
}

void Win32Application::setApplication( VCF::AbstractApplication* application )
{
	this->app_ = application;
}


String Win32Application::getFileName()
{
	String result;
	if ( System::isUnicodeEnabled() ) {
		VCFChar fileName[MAX_PATH];
		memset( fileName, 0, MAX_PATH*sizeof(VCFChar) );
		::GetModuleFileNameW( instanceHandle_, fileName, MAX_PATH );

		result = fileName;
	}
	else {
		char fileName[MAX_PATH];
		memset( fileName, 0, MAX_PATH*sizeof(char) );
		::GetModuleFileNameA( instanceHandle_, fileName, MAX_PATH );

		result = fileName;
	}


	return result;
}


OSHandleID Win32Application::getHandleID()
{
	return (OSHandleID)instanceHandle_;
}

void Win32Application::setHandleID( OSHandleID handleID )
{
	instanceHandle_ = (HINSTANCE)handleID;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.2  2004/12/19 07:09:18  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.2.2.1  2004/08/21 21:06:52  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.24.6.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.24  2003/08/09 02:56:46  ddiego
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
*Revision 1.23.2.2  2003/06/09 03:57:15  ddiego
*fixed an issue with tooltip not showing up, and while fixing that found it
*accidentally caused another problem with application focus for the main
*window not being handled correctly. This is now working OK! Now just
*have to get rid of the dialog flicker...
*Also fixed the QTPlayer example. It had some syntax errors from using the older
*event macros (not using Delegates)
*
*Revision 1.23.2.1  2003/06/05 03:48:54  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.23  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.22.2.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.22  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.21.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.21.14.2  2002/12/27 23:04:51  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.21  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.20.4.2  2002/04/27 15:52:24  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.20.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.20  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.19  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


