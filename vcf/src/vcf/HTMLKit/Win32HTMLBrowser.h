#ifndef _VCF_WIN32HTMLBROWSER_H__
#define _VCF_WIN32HTMLBROWSER_H__
//Win32HTMLBrowser.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_HTMLBROWSERPEER_H__
#	include "vcf/HTMLKit/HTMLBrowserPeer.h"
#endif // _VCF_HTMLBROWSERPEER_H__




#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif


#include "vcf/HTMLKit/Win32WebBrowserHost.h"


void initWin32HTMLBrowserLib( HMODULE module=NULL );

void terminateWin32HTMLBrowserLib();


namespace VCF  {


class Win32HTMLBrowser;

struct CLSIDPred {
	bool operator() ( const CLSID& x, const CLSID& y ) const {
		return (memcmp( &x, &y, sizeof(CLSID) ) < 0) ? true : false;
	}
};




class HTMLEventHandler : public IDispatchImpl {
public:

	HTMLEventHandler():eventSource(NULL), handler(NULL){}

	STDMETHOD(Invoke)( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, 
					DISPPARAMS* pDispParams, VARIANT* pVarResult, 
					EXCEPINFO* pExcepInfo, UINT* puArgErr );

	Object* eventSource;
	EventHandler* handler;
	String elementID;
};

/**
*Class Win32HTMLBrowser documentation
*/
class HTMLKIT_API Win32HTMLBrowser : 
		public AbstractWin32Component, public HTMLBrowserPeer,
		public WebBrowserCtrl {
public:	

	Win32HTMLBrowser();

	virtual ~Win32HTMLBrowser();

	virtual void create( VCF::Control* owningControl );

	virtual void setFocused();

	virtual CreateParams createParams();

	virtual void setVisible( const bool& val );

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndResult, WNDPROC defaultWndProc=NULL );
	


	virtual String getCurrentURL();

	virtual void setCurrentURL( const String& url );

	virtual void goBack();

	virtual void goForward();

	virtual void goHome();

	virtual void refresh();

	virtual bool isLoadingURL();

	virtual void stopLoadingURL();

	virtual void setFromHTML( const String& html );

	virtual String getTitle();

	virtual void edit( const bool& val );

	virtual void copy();

	virtual void selectAll();

	virtual void setAllowsPopupWindows( bool val );

	virtual void setAllowsScrollbars( bool val );

	virtual void setAllowsTextSelection( bool val );

	virtual String getElementHTMLText( const String& elementName );

	virtual void setElementHTMLText( const String& elementName, const String& html );

	virtual String getElementText( const String& elementName );

	virtual void setElementText( const String& elementName, const String& text );

	virtual String getActiveElementID();

	virtual String getElementIDFromPoint( Point* pt );

	virtual bool setElementClickedEventHandler( const String& elementName, EventHandler* handler );

	virtual HTMLDocument getDocument();
	
	//callbacks...
	virtual void onDownloadComplete();

	virtual void onProgressChange( long x, long y );

	virtual void onStatusTextChange( BSTR val );

    virtual void onDownloadBegin();
    
	virtual void onTitleChange( BSTR Text);
    
	virtual void onBeforeNavigate2( LPDISPATCH pDisp, 
									VARIANT* URL, 
									VARIANT* Flags, 
									VARIANT* TargetFrameName, 
									VARIANT* PostData, 
									VARIANT* Headers, 
									VARIANT_BOOL* Cancel );
    
	virtual void onNewWindow2( LPDISPATCH* ppDisp, VARIANT_BOOL* Cancel);
    
	virtual void onDocumentComplete( LPDISPATCH pDisp, VARIANT* URL);
    
	virtual void onWindowClosing( VARIANT_BOOL IsChildWindow, VARIANT_BOOL* Cancel );
    
	virtual void onFileDownload( VARIANT_BOOL* Cancel );
    
	virtual void onNavigateError( LPDISPATCH pDisp, 
									VARIANT* URL, 
									VARIANT* Frame, 
									VARIANT* StatusCode, 
									VARIANT_BOOL* Cancel);
    
	

	
	//IDocHostUIHandlerImpl impl
	STDMETHOD(ShowContextMenu)( DWORD hWndID, POINT *ppt, 
								IUnknown *pcmdtReserved, IDispatch *pdispReserved);

	STDMETHOD(TranslateUrl)( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut);

	STDMETHOD(GetHostInfo)( DOCHOSTUIINFO *pInfo ) ;
	
	STDMETHOD(OnDocWindowActivate)( BOOL fEnable );

	STDMETHOD(OnFrameWindowActivate)( BOOL fEnable );
    
	//IServiceProviderImpl impl
	STDMETHOD (QueryService)( REFGUID guidService, REFIID riid, void **ppv );

	//IAuthenticateImpl impl
	STDMETHOD(Authenticate)( HWND* phwnd, LPWSTR* pszUsername, 
							LPWSTR* pszPassword);


	HTMLEventHandler* getElementEventHandler( const String& name ) {
		HTMLEventHandler* result = NULL;
		std::map<String,HTMLEventHandler*>::iterator found = eventHandlers_.find(name);
		if ( found != eventHandlers_.end() ) {
			result = found->second;
		}

		return result;
	}

	STDMETHOD(TranslateAccelerator)( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID );
protected:

	

	String loadingURL_;
	HWND browserHwnd_;	
	std::map<String,HTMLEventHandler*> eventHandlers_;

	com_ptr<IOleInPlaceActiveObject> inPlaceObj_;

	int msgFilterID_;
	WNDPROC oldBrowserWndProc_;
	

	String getElementText( bool textIsHTML, const String& elementName );
	void setElementText( bool textIsHTML, const String& elementName, const String& text );

	void clearHTMLHandlers() {
		std::map<String,HTMLEventHandler*>::iterator it = eventHandlers_.begin();
		while ( it != eventHandlers_.end() ) {
			delete it->second;
			it ++;
		}

		eventHandlers_.clear();
	}

	static bool msgFilter( MSG* msg, void* data );

	bool processMessageFilter( MSG* msg );
	void handleBrowserMessages( MSG* msg );

	static LRESULT CALLBACK browserWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


}; //end of namespace VCF



#endif // _VCF_WIN32HTMLBROWSER_H__

/**
$Id$
*/
