//Win32HTMLBrowser.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32HTMLBrowser.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"



#include "vcf/ApplicationKit/Win32HTMLBrowser.h"


#include <atlhost.h>

#ifdef _ATL_STATIC_REGISTRY

#include <statreg.h>

#if  (_MSC_VER < 1300) //less than VC7
  #include <statreg.cpp>
#endif

#endif

#include <ExDispID.h>


static CLSID const clsid = { 0x8856f961, 0x340a, 0x11d0, { 0xa9, 0x6b, 0x0, 0xc0, 0x4f, 0xd7, 0x5, 0xa2 } };


// {CBD123C7-4389-4a24-95B3-F971065B6CD5}
static const GUID LIB_Win32HTMLBrowserGUID =
{ 0xcbd123c7, 0x4389, 0x4a24, { 0x95, 0xb3, 0xf9, 0x71, 0x6, 0x5b, 0x6c, 0xd5 } };



HRESULT DoAdvise(IUnknown* unknownConnectionPt, IUnknown* unknown, const IID& iid, DWORD* cookie)
{
	IConnectionPointContainerPtr connectionPtContainer;
	IConnectionPointPtr connectionPt;
	HRESULT hr = unknownConnectionPt->QueryInterface(IID_IConnectionPointContainer, (void**)&connectionPtContainer);

	if (SUCCEEDED(hr)) {
		hr = connectionPtContainer->FindConnectionPoint(iid, &connectionPt);
	}

	if (SUCCEEDED(hr)) {
		hr = connectionPt->Advise(unknown, cookie);
	}
	return hr;
}


HRESULT DoUnadvise(IUnknown* unknownConnectionPt, const IID& iid, DWORD cookie )
{
	IConnectionPointContainerPtr connectionPtContainer;
	IConnectionPointPtr connectionPt;

	HRESULT hr = unknownConnectionPt->QueryInterface(IID_IConnectionPointContainer, (void**)&connectionPtContainer);

	if (SUCCEEDED(hr)) {
		hr = connectionPtContainer->FindConnectionPoint(iid, &connectionPt);
	}

	if (SUCCEEDED(hr)) {
		hr = connectionPt->Unadvise(cookie);
	}
	return hr;
}






using namespace VCF;



STDMETHODIMP OLEClientSiteImpl::peerQueryInterface( REFIID riid, void** obj )
{
	return peer_->webInterfaces_.QueryInterface( riid, obj );
}


STDMETHODIMP WebBrowserEvents2Impl::peerQueryInterface( REFIID riid, void** obj )
{
	return peer_->webInterfaces_.QueryInterface( riid, obj );
}

//[id(0x00000066)
void STDMETHODCALLTYPE WebBrowserEvents2Impl::OnStatusTextChange( LPCSTR val )
{

}

//[id(0x00000068)
void STDMETHODCALLTYPE WebBrowserEvents2Impl::OnDownloadComplete()
{

}

//[id(0x00000069)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnCommandStateChange( long Command, BOOL Enable)
{

}

//[id(0x0000006a)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnDownloadBegin()
{

}

//[id(0x0000006c)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnProgressChange( long x, long y )
{

}

//[id(0x00000070)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnPropertyChange( LPCSTR szProperty )
{

}

//[id(0x00000071)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnTitleChange( LPCSTR Text)
{

}

//[id(0x000000e1)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnPrintTemplateInstantiation( IDispatch* pDisp)
{

}

//[id(0x000000e2)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnPrintTemplateTeardown( IDispatch* pDisp )
{

}

//[id(0x000000e3)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnUpdatePageStatus(
												   IDispatch* pDisp,
												   VARIANT* nPage,
												   VARIANT* fDone)
{

}

//[id(0x000000fa)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnBeforeNavigate2(
												  IDispatch* pDisp,
												  VARIANT* URL,
												  VARIANT* Flags,
												  VARIANT* TargetFrameName,
												  VARIANT* PostData,
												  VARIANT* Headers,
												  BOOL* Cancel )
{

}

//[id(0x000000fb)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnNewWindow2(
											 IDispatch** ppDisp,
											 BOOL* Cancel)
{

}


//[id(0x000000fc)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnNavigateComplete( IDispatch* dispatchPtr, VARIANT* URL )
{

}


//[id(0x000000fd)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnQuit()
{

}

//[id(0x00000103)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnDocumentComplete(
												   IDispatch* pDisp,
												   VARIANT* URL)
{

}

//[id(0x00000107)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnWindowClosing( BOOL IsChildWindow, BOOL* Cancel )
{

}

//[id(0x0000010c)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnClientToHostWindow( long* CX, long* CY )
{

}

//[id(0x0000010d)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnSetSecureLockIcon( long SecureLockIcon )
{

}

//[id(0x0000010e)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnFileDownload( VARIANT_BOOL* Cancel )
{

}

//[id(0x0000010f)
void STDMETHODCALLTYPE  WebBrowserEvents2Impl::OnNavigateError(
												IDispatch* pDisp,
												VARIANT* URL,
												VARIANT* Frame,
												VARIANT* StatusCode,
												BOOL* Cancel)
{

}

//[id(0x00000110)
void STDMETHODCALLTYPE WebBrowserEvents2Impl::OnPrivacyImpactedStateChange( BOOL bImpacted )
{

}

HRESULT STDMETHODCALLTYPE WebBrowserEvents2Impl::Invoke( DISPID  dispIdMember, REFIID  riid, LCID  lcid, WORD  wFlags,
					DISPPARAMS FAR*  pDispParams, VARIANT FAR*  pVarResult,
					EXCEPINFO FAR*  pExcepInfo, unsigned int FAR* puArgErr )
{

	switch (dispIdMember) {
		case DISPID_DOCUMENTCOMPLETE : {
			int i = 0;
			i++;
		}
		break;
	}

	return S_OK;
}


STDMETHODIMP OLEInPlaceSite::GetWindow( HWND * phwnd )
{
	*phwnd = peer_->hwnd_;

	return S_OK;
}


STDMETHODIMP OLEInPlaceSite::peerQueryInterface( REFIID riid, void** obj )
{
	return peer_->webInterfaces_.QueryInterface( riid, obj );
}

STDMETHODIMP OLEInPlaceSite::GetWindowContext( IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
		LPRECT lprcPosRect, LPRECT lprcClipRect,
		LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
	Rect r = peer_->getBounds();

	lprcPosRect->left = r.left_;
	lprcPosRect->right = r.right_;
	lprcPosRect->top = r.top_;
	lprcPosRect->bottom = r.bottom_;

	lprcClipRect->left = r.left_;
	lprcClipRect->right = r.right_;
	lprcClipRect->top = r.top_;
	lprcClipRect->bottom = r.bottom_;

	return S_OK;
}


STDMETHODIMP DocHostUIHandler::peerQueryInterface( REFIID riid, void** obj )
{
	return peer_->webInterfaces_.QueryInterface( riid, obj );
}


STDMETHODIMP DocHostUIHandler::ShowContextMenu(DWORD dwID, POINT FAR* ppt, IUnknown FAR* pcmdtReserved,
		IDispatch FAR* pdispReserved)
{
	return peer_->showContextMenu( dwID, ppt, pcmdtReserved, pdispReserved );
}

STDMETHODIMP DocHostUIHandler::GetHostInfo(DOCHOSTUIINFO FAR *pInfo)
{
	peer_->getHostInfo( pInfo );
	return S_OK;
}






Win32HTMLBrowser::Win32HTMLBrowser():
	browserHwnd_(NULL),
	clientSite_(this),
	browserEvents_(this),
	inPlaceSite_(this),
	docHostHandler_(this),
	connectionPtCookie_(0),
	docHostUIFlags_(0)
{
	webInterfaces_.addInterface( IID_IOleClientSite, &clientSite_ );
	webInterfaces_.addInterface( DIID_DWebBrowserEvents2, &browserEvents_ );
	webInterfaces_.addInterface( IID_IOleInPlaceSite, &inPlaceSite_ );
	webInterfaces_.addInterface( IID_IDocHostUIHandler, &docHostHandler_ );

	docHostUIFlags_ = docHostUIFlags_ | DOCHOSTUIFLAG_NO3DBORDER;
	docHostUIFlags_ = docHostUIFlags_ ^ DOCHOSTUIFLAG_SCROLL_NO;
}

Win32HTMLBrowser::~Win32HTMLBrowser()
{

}

void Win32HTMLBrowser::create( VCF::Control* owningControl )
{
	{
		String className = "VCF::Win32HTMLBrowser";
		if ( true != isRegistered() ){
			registerWin32Class( className, wndProc_  );
		}

		CreateParams params = createParams();

		Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
		HWND parent = toolkit->getDummyParent();

		if ( System::isUnicodeEnabled() ) {

			hwnd_ = ::CreateWindowExW( params.second, className.c_str(),
										L"",	params.first,
										0, 0,
										1,
										1,
										parent,
										NULL, ::GetModuleHandleW(NULL), NULL );
		}
		else {
			hwnd_ = ::CreateWindowExA( params.second, className.ansi_c_str(),
										"",	params.first,
										0, 0,
										1,
										1,
										parent,
										NULL, ::GetModuleHandleA(NULL), NULL );
		}


		if ( NULL != hwnd_ ){
			Win32Object::registerWin32Object( this );
		}
		else {
			throw RuntimeException( MAKE_ERROR_MSG_2("Unable to create hwnd") );
		}


	}


	AtlAxWinInit();
	RECT r = {0};
	r.left = 0;
	r.top = 0;
	r.right = 1;
	r.bottom = 1;
	String webBrowserCLSID = "{8856F961-340A-11D0-A96B-00C04FD705A2}";

	browserHwnd_ = browser_.Create( hwnd_, r, webBrowserCLSID.ansi_c_str(), WS_CHILD|WS_VISIBLE, 0, (UINT)-1);
	if ( NULL == browserHwnd_ ){
		throw RuntimeException( MAKE_ERROR_MSG_2("Unable to create Browser hwnd") );
	}

	HRESULT hr = browser_.QueryControl( IID_IWebBrowser2, (void**)&spBrowser_ );
	if ( !SUCCEEDED(hr) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Unable to get IID_IWebBrowser2 interface") );
	}

	IOleObjectPtr oleObj;
	spBrowser_.QueryInterface( &oleObj );
	oleObj->SetClientSite( &clientSite_ );

	connectionPtCookie_ = 0;

	DoAdvise( spBrowser_, &webInterfaces_, DIID_DWebBrowserEvents2, &connectionPtCookie_ );

	//webInterfaces_

	setCreated( true );
}

void Win32HTMLBrowser::setFocused()
{
	AbstractWin32Component::setFocused();
	::SetFocus( browserHwnd_ );
}

void Win32HTMLBrowser::setVisible( const bool& val )
{
	AbstractWin32Component::setVisible( val );

	if ( val ) {
		::ShowWindow( browserHwnd_, SW_SHOW );
	}
	else {
		::ShowWindow( browserHwnd_, SW_HIDE );
	}
}

bool Win32HTMLBrowser::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndResult, WNDPROC defaultWndProc )
{
	bool result = false;
	switch ( message ) {

		case WM_DESTROY : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );

			HRESULT hr = DoUnadvise(spBrowser_, DIID_DWebBrowserEvents2, connectionPtCookie_ );

			spBrowser_ = NULL;
		}
		break;

		case WM_PAINT : {
			if ( System::isUnicodeEnabled() ) {
				wndResult = DefWindowProcW(hwnd_, message, wParam, lParam);
				result = true;
			}
			else {
				wndResult = DefWindowProcA(hwnd_, message, wParam, lParam);
				result = true;
			}
		}
		break;

		case WM_ERASEBKGND : {
			wndResult = 0;
			result = true;
		}
		break;


		case WM_SIZE : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );

			DWORD w = LOWORD(lParam);
			DWORD h = HIWORD(lParam);
			MoveWindow( browserHwnd_, 0, 0, w, h, TRUE );
		}
		break;

		default : {
			result = AbstractWin32Component::handleEventMessages( message, wParam,lParam, wndResult, defaultWndProc );

		}
		break;
	}

	return  result;
}

Win32Object::CreateParams Win32HTMLBrowser::createParams()
{
	Win32Object::CreateParams result;
	result.second = 0;
	result.first = BORDERED_VIEW;

	return result;
}


String Win32HTMLBrowser::getCurrentURL()
{
	String result ;
	CComBSTR bstr;
	spBrowser_->get_LocationURL(&bstr);
	_bstr_t tmp = bstr.Detach();
	result = (VCFChar*)tmp;

	return result;
}

void Win32HTMLBrowser::setCurrentURL( const String& url )
{
	CComVariant ve;
	CComVariant vurl( url.c_str() );
	spBrowser_->put_Visible(VARIANT_TRUE);
	spBrowser_->Navigate2(&vurl, &ve, &ve, &ve, &ve);
}

void Win32HTMLBrowser::goBack()
{
	HRESULT hr = spBrowser_->GoBack();
}

void Win32HTMLBrowser::goForward()
{
	HRESULT hr = spBrowser_->GoForward();
}

void Win32HTMLBrowser::goHome()
{
	HRESULT hr = spBrowser_->GoHome();
}

void Win32HTMLBrowser::refresh()
{
	HRESULT hr = spBrowser_->Refresh();
}

bool Win32HTMLBrowser::isLoadingURL()
{
	bool result = false;
	VARIANT_BOOL busy;
	HRESULT hr = spBrowser_->get_Busy( &busy );
	if ( VARIANT_TRUE == busy ) {
		result = true;
	}
	else if ( VARIANT_FALSE == busy ) {
		result = false;
	}
	return result;
}

void Win32HTMLBrowser::stopLoadingURL()
{

}

void Win32HTMLBrowser::setFromHTML( const String& html )
{

}

void Win32HTMLBrowser::getHostInfo(DOCHOSTUIINFO FAR *pInfo)
{
	pInfo->cbSize  = sizeof(DOCHOSTUIINFO);
    pInfo->dwFlags = docHostUIFlags_;
}

HRESULT Win32HTMLBrowser::showContextMenu( DWORD dwID, POINT FAR* ppt, IUnknown FAR* pcmdtReserved,
		IDispatch FAR* pdispReserved)
{

	return S_OK;
}











CComModule _Module;


using namespace VCF;


BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


void initWin32HTMLBrowserLib( HMODULE module )
{
	if ( module == NULL ) {
		module = GetModuleHandle(NULL);
	}

#if  (_MSC_VER < 1300) //VC6
	_Module.Init(ObjectMap, (HINSTANCE)module );
#else //do this for VC7/7.1
	_Module.Init(ObjectMap, (HINSTANCE)module, &LIB_Win32HTMLBrowserGUID );
#endif
	REGISTER_CLASSINFO( Win32HTMLBrowser );
}

void terminateWin32HTMLBrowserLib()
{
	_Module.Term();
}



#ifdef _USRDLL

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {
			initWin32HTMLBrowserLib((HINSTANCE) hModule);
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {
			terminateWin32HTMLBrowserLib();
		}
		break;
    }
    return TRUE;
}

#endif


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/02/21 19:07:10  ddiego
*fixed missing code from createParam changes in win32 html browser kit
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/08 01:16:49  ddiego
*fixed incorrect win32htmlbrowser function due to changes from weekend.
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:27:14  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.3  2004/04/26 16:43:34  ddiego
*checked in some minor fixes to some of the other
*libraries due to switch over to unicode
*
*Revision 1.10.4.2  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.10.4.1  2004/04/07 03:25:57  ddiego
*fixed Win32HTMLBrowser ATL assert bug. The problem was a minor
*to teh ATL CComModule.Init() function. In VC6 version it just needed
*an HINSTANCE and and object map, in VC7 it also needs a GUID for the lib.
*Of course this is helpfully set to an INVALID default parameter, which is
*nice, I suppose.
*
*Revision 1.10  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.2.1  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.9  2003/08/09 02:56:46  ddiego
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
*Revision 1.8.2.1  2003/08/06 21:28:02  ddiego
*minor changes
*
*Revision 1.8  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:12:38  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6.2.1  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.5.10.1  2002/11/06 01:03:02  ddiego
*bug fixes, made the Win32HTMLBrowser get rid of the ATL.dll dependencies
*also made changes to the VCF Builder installer
*
*Revision 1.5  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.4  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


