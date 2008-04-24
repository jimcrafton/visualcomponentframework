//Win32HTMLBrowser.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32HTMLBrowser.h
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"
#include "vcf/ApplicationKit/Win32Object.h"
#include "vcf/ApplicationKit/AbstractWin32Component.h"
#include "vcf/HTMLKit/Win32HTMLBrowser.h"
#include "vcf/ApplicationKit/Win32Toolkit.h"
#include <Wininet.h>

#pragma comment (lib,"Wininet.lib")

COM_PTR(IOleInPlaceActiveObject)





using namespace VCF;


STDMETHODIMP HTMLEventHandler::Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, 
										WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, 
										EXCEPINFO* pExcepInfo, UINT* puArgErr ) 
{
	if ( 0 == dispIdMember && NULL != handler ) {
		HTMLElementEvent e(eventSource,HTMLBrowserControl::heElementClicked);
		e.elementID = elementID;
		
		handler->invoke( &e );
		
		return S_OK;
	}
	
	return E_NOTIMPL;
}



bool Win32HTMLBrowser::msgFilter( MSG* msg, void* data )
{
	Win32HTMLBrowser* thisPtr = (Win32HTMLBrowser*)data;

	if ( NULL != thisPtr ) {
		if ( msg->message == WM_KEYFIRST && msg->message < WM_KEYLAST ) {
			if ( IsChild( thisPtr->hwnd_, msg->hwnd ) ) {
				//OK lets try and process this
				com_ptr<IOleInPlaceActiveObject> ipao = com_cast( thisPtr->browser_ );
				
				if ( IsDialogMessage(msg->hwnd, msg) ) {
					
					return true;
				}

				if ( ipao ) {
					hresult hr = ipao->TranslateAccelerator( msg );
					if ( S_OK == (HRESULT)hr ) {
						return true;
					}
				}
			}
		}
	}

	return false;
}



Win32HTMLBrowser::Win32HTMLBrowser():
	browserHwnd_(NULL)	,
		msgFilterID_(0)
{
	uiStyle_ = DOCHOSTUIFLAG_NO3DBORDER;
}

Win32HTMLBrowser::~Win32HTMLBrowser()
{
	clearHTMLHandlers();

	if ( msgFilterID_ != 0 ) {
		Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();

		toolkit->removeFilter( msgFilterID_ );
	}
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
		
		msgFilterID_ = toolkit->addFilter( Win32HTMLBrowser::msgFilter, this );


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

			//embed the browser 
			embed( hwnd_ );
		}
		else {
			throw RuntimeException( MAKE_ERROR_MSG_2("Unable to create hwnd") );
		}


	}


	setCreated( true );
}

void Win32HTMLBrowser::setFocused()
{
	AbstractWin32Component::setFocused();
	//::SetFocus( browserHwnd_ );
}

void Win32HTMLBrowser::setVisible( const bool& val )
{
	AbstractWin32Component::setVisible( val );

	if ( val ) {
		//::ShowWindow( browserHwnd_, SW_SHOW );
	}
	else {
		//::ShowWindow( browserHwnd_, SW_HIDE );
	}
}

bool Win32HTMLBrowser::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndResult, WNDPROC defaultWndProc )
{
	bool result = false;
	switch ( message ) {

		case WM_DESTROY : {

			unembed();

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );

			
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
			
			resize( LOWORD(lParam), HIWORD(lParam) );
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
	//WS_CLIPSIBLINGS and friends cause TONS of flicker
	//during repaints, so we get rid of them.
	result.first = WS_CHILD;//  | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return result;
}


String Win32HTMLBrowser::getCurrentURL()
{
	return WebBrowserCtrl::getCurrentURL();
}

void Win32HTMLBrowser::setCurrentURL( const String& url )
{
	loadingURL_ = url;
	openURL( url );
}

void Win32HTMLBrowser::goBack()
{
	back();
}

void Win32HTMLBrowser::goForward()
{
	forward();
}

void Win32HTMLBrowser::goHome()
{
	home();
}

void Win32HTMLBrowser::refresh()
{
	WebBrowserCtrl::refresh();
}

bool Win32HTMLBrowser::isLoadingURL()
{
	return busy();
}

void Win32HTMLBrowser::stopLoadingURL()
{
	WebBrowserCtrl::stop();
}

void Win32HTMLBrowser::setFromHTML( const String& html )
{
	if ( busy() ) {
		//barf!
		throw RuntimeException( "The browser is still loading it's document and you can't set the document's HTML while it's loading." );
	}

	HTMLDocument doc = getDocument();
	if ( !doc.null() ) {
		doc.write( html );
	}
}

String Win32HTMLBrowser::getTitle()
{
	String result;

	HTMLDocument doc = getDocument();
	if ( !doc.null() ) {
		result = doc.getTitle();
	}

	return result;
}

void Win32HTMLBrowser::edit( const bool& val )
{
	HTMLDocument doc = getDocument();
	if ( !doc.null() ) {
		doc.setDesignMode( val );
	}
	else {
		throw RuntimeException( "Can't edit a null document." );
	}
}

void Win32HTMLBrowser::copy()
{
	HTMLDocument doc = getDocument();
	if ( !doc.null() ) {
		doc.copy();
	}
	else {
		throw RuntimeException( "Can't copy from a null document." );
	}
}

void Win32HTMLBrowser::selectAll()
{
	HTMLDocument doc = getDocument();
	if ( !doc.null() ) {
		doc.selectAll();
	}
	else {
		throw RuntimeException( "Can't make a selection from a null document." );
	}
}

void Win32HTMLBrowser::setAllowsPopupWindows( bool val )
{
//no-op
}

void Win32HTMLBrowser::setAllowsScrollbars( bool val )
{
	uiStyle_ = val ? (uiStyle_ ^ DOCHOSTUIFLAG_SCROLL_NO)
                                      : (uiStyle_ | DOCHOSTUIFLAG_SCROLL_NO);	
}

void Win32HTMLBrowser::setAllowsTextSelection( bool val )
{
	uiStyle_ = val ? (uiStyle_ ^ DOCHOSTUIFLAG_DIALOG)
                                      : (uiStyle_ | DOCHOSTUIFLAG_DIALOG);
}

String Win32HTMLBrowser::getElementHTMLText( const String& elementName )
{
	return getElementText( true, elementName );
}

void Win32HTMLBrowser::setElementHTMLText( const String& elementName, const String& html )
{
	setElementText( true, elementName, html );
}

String Win32HTMLBrowser::getElementText( const String& elementName )
{
	return getElementText( false, elementName );
}

void Win32HTMLBrowser::setElementText( const String& elementName, const String& text )
{
	setElementText( false, elementName, text );
}

String Win32HTMLBrowser::getActiveElementID()
{
	String result;

	com_ptr<IDispatch> disp;
	IHTMLDocument2Ptr doc;
	browser_->get_Document( disp.out() );
	doc = com_cast( disp );
	if ( doc ) {
		IHTMLElementPtr item;
		doc->get_activeElement( item.out() );
		bstr_t tmp;
		item->get_id( tmp.out() );

		result = tmp.c_str();

		item->get_tagName( tmp.out() );
	}

	return result;
}

String Win32HTMLBrowser::getElementIDFromPoint( Point* pt )
{
	String result;

	com_ptr<IDispatch> disp;
	IHTMLDocument2Ptr doc;
	browser_->get_Document( disp.out() );
	doc = com_cast( disp );
	if ( doc ) {
		IHTMLElementPtr item;
		doc->elementFromPoint( (long)pt->x_, (long)pt->y_, item.out() );
		bstr_t tmp;
		item->get_id( tmp.out() );

		result = tmp.c_str();
	}

	return result;
}

String Win32HTMLBrowser::getElementText( bool textIsHTML, const String& elementName )
{
	String result;

	VCF::HTMLElementPeer item;

	VCF::HTMLElementCollectionPeer collection;	
	com_ptr<IDispatch> disp;
	IHTMLDocument2Ptr doc;
	browser_->get_Document( disp.out() );
	doc = com_cast( disp );
	if ( doc ) {
		doc->get_all( collection.out() );
		if ( collection ) {
			VCF::HTMLElementCollection coll2;
			coll2.setPeer( &collection );
			long len = coll2.getLength();
			
			for (int i=0;i<len;i++ ) {
				VCF::HTMLElement* f = coll2[i];
				if ( NULL != f ) {
					if ( elementName == f->getID() ) {							
						item = *f->getPeer();
						break;
					}
				}
			}			
		}
	}	

	if ( !item.is_null() ) {
		bstr_t val;
		if ( textIsHTML ) {
			item->get_innerHTML( val.out() );
		}
		else {
			item->get_innerText( val.out() );
		}

		result = val.c_str();
	}

	return result;
}

void Win32HTMLBrowser::setElementText( bool textIsHTML, const String& elementName, const String& text )
{
	VCF::HTMLElementPeer item;
	
	HTMLElementCollectionPeer collection;
	com_ptr<IDispatch> disp;
	IHTMLDocument2Ptr doc;
	browser_->get_Document( disp.out() );
	doc = com_cast( disp );
	if ( doc ) {
		doc->get_all( collection.out() );
		if ( collection ) {
			VCF::HTMLElementCollection coll2;
			coll2.setPeer( &collection );
			long len = coll2.getLength();
			
			for (int i=0;i<len;i++ ) {
				VCF::HTMLElement* f = coll2[i];
				if ( NULL != f ) {
					if ( elementName == f->getID() ) {							
						item = *f->getPeer();
						break;
					}
				}
			}			
		}
	}
	

	if ( !item.is_null() ) {
		bstr_t val = text.c_str();						

		if ( textIsHTML ) {
			item->put_innerHTML( val.in() );
		}
		else {
			item->put_innerText( val.in() );
		}
	}
}


bool Win32HTMLBrowser::setElementClickedEventHandler( const String& elementName, EventHandler* handler )
{
	bool result = false;

	VCF::HTMLElementCollectionPeer collection;	
	com_ptr<IDispatch> disp;
	IHTMLDocument2Ptr doc;
	browser_->get_Document( disp.out() );
	doc = com_cast( disp );
	if ( doc ) {
		doc->get_all( collection.out() );
		if ( collection ) {
			VCF::HTMLElementCollection coll2;
			coll2.setPeer( &collection );

			long len = coll2.getLength();

			for (int i=0;i<len;i++ ) {
				VCF::HTMLElement* f = coll2[i];
				if ( NULL != f ) {
					if ( elementName == f->getID() ) {
						String name = handler->getName();

						HTMLEventHandler* htmlHandler = getElementEventHandler(name);
						if ( NULL == htmlHandler ) {
							htmlHandler = new HTMLEventHandler();
							eventHandlers_[name] = htmlHandler;
						}

						htmlHandler->eventSource = peerControl_;
						htmlHandler->handler = handler;
						htmlHandler->elementID = elementName;

						variant_t e;
						com_ptr<IDispatch> idisp = htmlHandler;

						e = idisp;							
						(*f->getPeer())->put_onclick( e.in() );

						result = true;
						break;
					}
				}
			}			
		}
	}

	return result;
}

VCF::HTMLDocument Win32HTMLBrowser::getDocument()
{
	VCF::HTMLDocument result;

	VCF::HTMLDocumentPeer doc;
	com_ptr<IDispatch> disp;
	browser_->get_Document( disp.out() );
	
	if ( disp ) {
		doc = com_cast(disp);
		result.setPeer( &doc );
	}	

	return result;
}

void Win32HTMLBrowser::onDownloadComplete()
{

}

void Win32HTMLBrowser::onProgressChange( long x, long y )
{
	HTMLEvent e(peerControl_,HTMLBrowserControl::heURLLoading);
	e.maxValue = y;
	e.value = x;

	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
	browserCtrl->URLLoading( &e );
}

void Win32HTMLBrowser::onStatusTextChange( BSTR val )
{
	HTMLEvent e(peerControl_,HTMLBrowserControl::heStatusChanged);
	bstr_t tmp(val);
	e.status = tmp.c_str();

	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
	browserCtrl->StatusChanged( &e );
}

void Win32HTMLBrowser::onDownloadBegin()
{
	HTMLEvent e(peerControl_,HTMLBrowserControl::heURLLoadingBegun);
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
	browserCtrl->URLLoadingBegun( &e );
}

void Win32HTMLBrowser::onTitleChange( BSTR Text)
{
	HTMLEvent e(peerControl_,HTMLBrowserControl::heTitleChanged);
	bstr_t tmp(Text);
	e.status = tmp.c_str();
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
	browserCtrl->TitleChanged( &e );
}

void Win32HTMLBrowser::onBeforeNavigate2( LPDISPATCH pDisp, 
							   VARIANT* URL, 
							   VARIANT* Flags, 
							   VARIANT* TargetFrameName, 
							   VARIANT* PostData, 
							   VARIANT* Headers, 
							   VARIANT_BOOL* Cancel )
{

}

void Win32HTMLBrowser::onNewWindow2( LPDISPATCH* ppDisp, VARIANT_BOOL* Cancel)
{
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;

	if ( !browserCtrl->getAllowsPopupWindows() ) {
		*Cancel = TRUE;
	}
	else {
		
		HTMLEvent e(peerControl_,HTMLBrowserControl::heNewWindowDisplayed);
		HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
		
		browserCtrl->NewWindowDisplayed( &e );
	}
}

void Win32HTMLBrowser::onDocumentComplete( LPDISPATCH pDisp, VARIANT* URL)
{
	HTMLEvent e(peerControl_,HTMLBrowserControl::heURLLoaded);
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;

	if ( NULL != URL && URL->vt == VT_BSTR ) {
		bstr_t tmp;
		tmp = URL->bstrVal;
		e.url = tmp.c_str();
	}

	browserCtrl->URLLoaded( &e );
}

void Win32HTMLBrowser::onWindowClosing( VARIANT_BOOL IsChildWindow, VARIANT_BOOL* Cancel )
{

}

void Win32HTMLBrowser::onFileDownload( VARIANT_BOOL* Cancel )
{

}

void Win32HTMLBrowser::onNavigateError( LPDISPATCH pDisp, 
							 VARIANT* URL, 
							 VARIANT* Frame, 
							 VARIANT* StatusCode, 
							 VARIANT_BOOL* Cancel)
{
	HTMLEvent e(peerControl_,HTMLBrowserControl::heURLLoadingBegun);
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;

	if ( NULL != URL && URL->vt == VT_BSTR ) {
		bstr_t tmp;
		tmp = URL->bstrVal;
		e.url = tmp.c_str();
	}

	hresult hr = (HRESULT) StatusCode->lVal;
	e.status = hr.toString();

	browserCtrl->URLLoadError( &e );
}

STDMETHODIMP Win32HTMLBrowser::TranslateUrl( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
{
	String s(pchURLIn);

	URL_COMPONENTSW components;
	
	VCFChar* scheme = new VCFChar[s.size()];
	VCFChar* host = new VCFChar[s.size()];
	VCFChar* user = new VCFChar[s.size()];
	VCFChar* pwd = new VCFChar[s.size()];
	VCFChar* url = new VCFChar[s.size()];
	VCFChar* extra = new VCFChar[s.size()];

	components.dwStructSize = sizeof(components);
	components.dwExtraInfoLength = s.size();

	components.dwHostNameLength = components.dwPasswordLength = components.dwSchemeLength = 
		components.dwUrlPathLength = components.dwUserNameLength = s.size();

	components.lpszExtraInfo = extra;
	components.lpszHostName = host;
	components.lpszPassword = pwd;
	components.lpszScheme = scheme;
	components.lpszUrlPath = url;
	components.lpszUserName = user;


	InternetCrackUrlW( s.c_str(), s.size(), 0, &components );



	if ( components.nScheme == INTERNET_SCHEME_RES ) {
		//check out resources dir first to see if we have anything
		Application* app = Application::getRunningInstance();
		if ( NULL != app ) {
			String resDir = app->getResourceBundle()->getResourcesDirectory();
			FilePath fp = resDir + components.lpszUrlPath;
			if ( File::exists( fp ) ) {

			}
		}
	}


	delete [] scheme;
	delete [] host;
	delete [] user;
	delete [] pwd;
	delete [] url;
	delete [] extra;




	return E_NOTIMPL;
}

STDMETHODIMP Win32HTMLBrowser::ShowContextMenu( DWORD hWndID, POINT *ppt, 
								IUnknown *pcmdtReserved, IDispatch *pdispReserved)
{
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;

	ControlPopupMenuMenuEvent e(this,Control::BEFORE_POPUP_MENU);
	e.popupMenu = peerControl_->getPopupMenu();
	peerControl_->BeforePopupMenu( &e );
	if ( (NULL != e.popupMenu) && !e.cancelPopup ) {
		//point is in screen coords
		Point pt(ppt->x, ppt->y);
		//convert to client coords

		peerControl_->translateFromScreenCoords( &pt );
		e.popupMenu->popup( &pt );

		return S_OK; //we've handled this!
	}
	else if ( !browserCtrl->getAllowDefaultContextMenu() ) {
		//do nothing - we don't want the default context menu to show up!
		return S_OK;
	}

	return E_NOTIMPL;
}

STDMETHODIMP Win32HTMLBrowser::GetHostInfo( DOCHOSTUIINFO *pInfo ) 
{
	pInfo->cbSize = sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags = uiStyle_;

	pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

	return S_OK;
}

STDMETHODIMP Win32HTMLBrowser::OnDocWindowActivate( BOOL fEnable ) 
{
	return E_NOTIMPL;
}

STDMETHODIMP Win32HTMLBrowser::OnFrameWindowActivate( BOOL fEnable ) 
{
	return E_NOTIMPL;
}

STDMETHODIMP Win32HTMLBrowser::QueryService( REFGUID guidService, REFIID riid, void **ppv )
{
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
	if ( riid == IID_IAuthenticate && !browserCtrl->getUseDefaultAuthenticationUI() ) {		
		IAuthenticateImpl* authenticater = this;

		*ppv = (IAuthenticate*) authenticater;

		return S_OK;
	}
	return E_NOINTERFACE;
}

STDMETHODIMP Win32HTMLBrowser::Authenticate( HWND* phwnd, LPWSTR* pszUsername, 
							LPWSTR* pszPassword)
{	
	HTMLAuthenticationEvent e(peerControl_, loadingURL_ );

	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
	browserCtrl->AuthenticationRequested( &e );

	if ( e.authenticationCancelled ) {
		return E_ACCESSDENIED;
	}

	if ( e.userName.empty() && e.password.empty() ) {
		return E_ACCESSDENIED;
	}

	*phwnd = NULL;

	*pszUsername = (LPWSTR) CoTaskMemAlloc( e.userName.size_in_bytes() + sizeof(WCHAR) );
	memset( *pszUsername, 0, e.userName.size_in_bytes() + sizeof(WCHAR) );
	e.userName.copy( *pszUsername, e.userName.size() );

	*pszPassword = (LPWSTR) CoTaskMemAlloc( e.password.size_in_bytes() + sizeof(WCHAR) );
	memset( *pszPassword, 0, e.password.size_in_bytes() + sizeof(WCHAR) );
	e.password.copy( *pszPassword, e.password.size() );

	return S_OK;
}



using namespace VCF;



/**
$Id$
*/
