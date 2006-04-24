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
protected:
	String loadingURL_;
	HWND browserHwnd_;	
	std::map<String,HTMLEventHandler*> eventHandlers_;

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
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2006/04/07 02:35:42  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.1.2.1  2006/03/06 03:48:31  ddiego
*more docs, plus update add-ins, plus migrated HTML browser code to a new kit called HTMLKit.
*
*Revision 1.4.2.5  2006/02/15 05:14:33  ddiego
*more browser code.
*
*Revision 1.4.2.4  2006/02/14 05:13:09  ddiego
*more browser updates.
*
*Revision 1.4.2.3  2006/02/13 22:11:59  ddiego
*added further html support and better browser example code.
*
*Revision 1.4.2.2  2006/02/13 05:10:32  ddiego
*added better html browser support.
*
*Revision 1.4.2.1  2006/02/09 04:54:02  ddiego
*added missing lib tiff project for vc80. Also removed
*ATL dependency and comdef.h dependency. We are now using comet for
*basic COM types, and I have a new chunk of code that implements the
*basics for hosting the browser.
*
*Revision 1.4  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.3.2.1  2005/02/21 19:07:11  ddiego
*fixed missing code from createParam changes in win32 html browser kit
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/10 19:07:37  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2.2.2  2004/09/08 01:16:50  ddiego
*fixed incorrect win32htmlbrowser function due to changes from weekend.
*
*Revision 1.2.2.1  2004/08/17 05:01:29  marcelloptr
*improved macros for library selection
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.2  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7.4.1  2004/04/07 03:25:57  ddiego
*fixed Win32HTMLBrowser ATL assert bug. The problem was a minor
*to teh ATL CComModule.Init() function. In VC6 version it just needed
*an HINSTANCE and and object map, in VC7 it also needs a GUID for the lib.
*Of course this is helpfully set to an INVALID default parameter, which is
*nice, I suppose.
*
*Revision 1.7  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.2.2  2003/12/17 05:11:56  ddiego
*minors mods, mostly to support chnages to the installer and some
*problems with the html help docs abnd MSDN integration
*
*Revision 1.6.2.1  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.6  2003/08/09 02:56:44  ddiego
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
*Revision 1.5.2.1  2003/08/06 21:26:27  ddiego
*minor changes to doc stuff
*
*Revision 1.5  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.10.2  2003/04/17 04:29:49  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.4.10.1  2003/03/12 03:11:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.3.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.3  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.2  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32HTMLBROWSER_H__


