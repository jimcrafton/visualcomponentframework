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
#ifdef VCF_CYGWIN
	InitCommonControls();
#else
	INITCOMMONCONTROLSEX controlsToInit;
	memset(&controlsToInit,0,sizeof(controlsToInit));
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
$Id$
*/
