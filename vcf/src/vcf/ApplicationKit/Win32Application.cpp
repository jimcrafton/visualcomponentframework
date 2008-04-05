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




Win32Application::Win32Application():
	instanceHandle_(NULL),
	singleInstanceMutex_(NULL)
{

}

Win32Application::~Win32Application()
{
	if ( NULL != singleInstanceMutex_ ) {
		CloseHandle( singleInstanceMutex_ );
	}
}


BOOL CALLBACK SearchForAppWindows(HWND hWnd, LPARAM lParam)
{
	DWORD result;

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND toolkitWnd = toolkit->getDummyParent();

	if ( toolkitWnd != hWnd ) {
		LRESULT ok = ::SendMessageTimeout(hWnd,
											Win32ToolKit::AreUMeMessage,
											0, 0, 
											SMTO_BLOCK |
											SMTO_ABORTIFHUNG,
											200,
											&result );
		if(ok == 0)
			return TRUE; // ignore this and continue
		
		if(result == Win32ToolKit::AreUMeMessage)
		{ /* found it */
			HWND * target = (HWND *)lParam;
			*target = hWnd;
			return FALSE; // stop search
			
		} /* found it */
	}
    return TRUE; // continue search
}

bool Win32Application::initApp()
{

	Application* app = Application::getRunningInstance();
	if ( app->isSingleInstance() && app == app_ ) {

		bool alreadyRunning = false;

		uniqueAppName_ = app->getName();
		
		DWORD len;
		HDESK desktop = GetThreadDesktop(GetCurrentThreadId());
		BOOL result = GetUserObjectInformation(desktop, UOI_NAME, NULL, 0, &len);
		DWORD err = ::GetLastError();
		if(!result && err == ERROR_INSUFFICIENT_BUFFER)	{ 
			/* NT/2000 */
			LPBYTE data = new BYTE[len];
			result = GetUserObjectInformation(desktop, UOI_NAME, data, len, &len);
			uniqueAppName_ += "-";
			uniqueAppName_ += (const char*)data;
			delete [ ] data;
		} /* NT/2000 */
		else { 
			/* Win9x */
			uniqueAppName_ += "-Win9x";
		} /* Win9x */

		singleInstanceMutex_ = ::CreateMutexW( NULL, FALSE, uniqueAppName_.c_str() );
		
		Win32ToolKit::initAreUMeMessage( uniqueAppName_ );

		alreadyRunning = ( ::GetLastError() == ERROR_ALREADY_EXISTS || 
							::GetLastError() == ERROR_ACCESS_DENIED) ? true : false;

		if ( alreadyRunning ) {

			//Win32ToolKit::AreUMeMessage
			HWND otherToolkitWnd = NULL;
			EnumWindows( SearchForAppWindows, (LPARAM)&otherToolkitWnd );

			if ( otherToolkitWnd != NULL )
			{ /* pop up */
				const std::vector<String>& cmdLine = FoundationKit::getCommandLine().getOriginalCommandLine();
				std::vector<String>::const_iterator it = cmdLine.begin();
				String cmds;

				while ( it != cmdLine.end() ) {					
					
					const String& s = *it;
					cmds += s + "\n";
					++it;
				}

				Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
				HWND toolkitWnd = toolkit->getDummyParent();

				COPYDATASTRUCT cpd = {0};
				cpd.dwData = Win32ToolKit::RestoreSingleInstAppMessage;
				cpd.cbData = cmds.size_in_bytes();
				cpd.lpData = (void*)cmds.c_str();

				::SendMessage( otherToolkitWnd, WM_COPYDATA, (WPARAM)toolkitWnd, (LPARAM)&cpd );

				::SendMessage( otherToolkitWnd, Win32ToolKit::RestoreSingleInstAppMessage, 0, 0 );

			} /* pop up */



			return false;
		}
	}


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
