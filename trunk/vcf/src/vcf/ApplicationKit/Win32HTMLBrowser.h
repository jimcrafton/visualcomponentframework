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


#include "vcf/ApplicationKit/Win32HTMLBrowserSelectLib.h"

#ifndef _VCF_HTMLBROWSERPEER_H__
#	include "vcf/ApplicationKit/HTMLBrowserPeer.h"
#endif // _VCF_HTMLBROWSERPEER_H__


//this will automatilcally pull in the atl.lib
//#define _ATL_DLL

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif



#include <comdef.h>


#include <Exdisp.h>
#include <mshtmhst.h>
#include <Mshtml.h>


#include <atlbase.h>

extern CComModule _Module;

#include <atlcom.h>
#include <atlwin.h>





/*
This is a series of smart pointer declarations
so ICustomDoc, becomes ICustomDocPtr, used on the stack
*/
_COM_SMARTPTR_TYPEDEF(IOleObject, __uuidof(IOleObject));
_COM_SMARTPTR_TYPEDEF(IConnectionPointContainer, __uuidof(IConnectionPointContainer));
_COM_SMARTPTR_TYPEDEF(IConnectionPoint, __uuidof(IConnectionPoint));


_COM_SMARTPTR_TYPEDEF(ICustomDoc , __uuidof(ICustomDoc ));
_COM_SMARTPTR_TYPEDEF(IWebBrowser2, __uuidof(IWebBrowser2 ));
_COM_SMARTPTR_TYPEDEF(IHTMLElement, __uuidof(IHTMLElement ));
_COM_SMARTPTR_TYPEDEF(IHTMLTxtRange, __uuidof(IHTMLTxtRange ));
_COM_SMARTPTR_TYPEDEF(IHTMLDocument2, __uuidof(IHTMLDocument2 ));
_COM_SMARTPTR_TYPEDEF(IHTMLElementCollection, __uuidof(IHTMLElementCollection ));
_COM_SMARTPTR_TYPEDEF(IHTMLTable, __uuidof(IHTMLTable ));
_COM_SMARTPTR_TYPEDEF(IHTMLTableRow, __uuidof(IHTMLTableRow ));

_COM_SMARTPTR_TYPEDEF(IHTMLTableCell, __uuidof(IHTMLTableCell ));

//_COM_SMARTPTR_TYPEDEF(IHighlightRenderingServices, __uuidof(IHighlightRenderingServices ));
//_COM_SMARTPTR_TYPEDEF(IDisplayServices, __uuidof(IDisplayServices ));

//_COM_SMARTPTR_TYPEDEF(IDisplayPointer, __uuidof(IDisplayPointer ));
//_COM_SMARTPTR_TYPEDEF(IHTMLRenderStyle, __uuidof(IHTMLRenderStyle ));
//_COM_SMARTPTR_TYPEDEF(IHighlightSegment, __uuidof(IHighlightSegment ));
//_COM_SMARTPTR_TYPEDEF(ISegment, __uuidof(ISegment ));



void initWin32HTMLBrowserLib( HMODULE module=NULL );

void terminateWin32HTMLBrowserLib();


namespace VCF  {

#define WIN32HTMLBROWSER_CLASSID "75794831-B24F-4f83-91B4-611952567DE6"


#define IUNKNOWN_IMPL(DerivedClass,DerivedClass_IID) \
	STDMETHOD(QueryInterface)( REFIID riid, void** obj ) {\
		HRESULT hr = E_NOINTERFACE;\
		if ( riid == IID_IUnknown ) {\
			*obj = (IUnknown*)this;\
			hr = S_OK;\
		}\
		else if ( riid == DerivedClass_IID ) { \
			*obj = (DerivedClass*)this;\
		}\
		else {\
			hr = peerQueryInterface( riid, obj ); \
		}\
		return hr;\
	}\
  \
	virtual ULONG STDMETHODCALLTYPE AddRef( void){ \
		return 1;\
	}\
	\
	virtual ULONG STDMETHODCALLTYPE Release( void){\
		return 1; \
	} \
	\


#define IUNKNOWNREFCOUNT_IMPL() \
	virtual ULONG STDMETHODCALLTYPE AddRef( void){ \
		return 1;\
	}\
	\
	virtual ULONG STDMETHODCALLTYPE Release( void){\
		return 1; \
	} \
	\



class Win32HTMLBrowser;

struct CLSIDPred {
	bool operator() ( const CLSID& x, const CLSID& y ) const {
		return (memcmp( &x, &y, sizeof(CLSID) ) < 0) ? true : false;
	}
};

class IUnknownCollection;

class AggregateBaseClass {
public:

	IUnknownCollection* collection;
};

class IUnknownCollection : public IUnknown {
public :
	IUnknownCollection(){}

	virtual ~IUnknownCollection() {

	}


	STDMETHOD(QueryInterface)( REFIID riid, void** obj ) {
		HRESULT hr = E_NOINTERFACE;

		if ( riid == IID_IUnknown ) {
			*obj = (IUnknown*)this;
			hr = S_OK;
		}
		else {
			std::map<CLSID,IUnknown*,CLSIDPred>::iterator found = interfaces_.find( riid );
			if ( found != interfaces_.end() ) {
				*obj = (IUnknown*) found->second;
				hr = S_OK;
			}
		}

		return hr;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef( void){
		return 1;
	}

	virtual ULONG STDMETHODCALLTYPE Release( void){
		return 1;
	}

	void addInterface( CLSID riid, IUnknown* unknown ) {
		//((AggregateBaseClass*)unknown)->collection = this;
		interfaces_[riid] = unknown;
	}

	std::map<CLSID,IUnknown*,CLSIDPred> interfaces_;
};


class OLEClientSiteImpl : public IOleClientSite {
public:
	OLEClientSiteImpl(Win32HTMLBrowser* peer) :peer_(peer) {

	}

	IUNKNOWN_IMPL( IOleClientSite, IID_IOleClientSite )


	STDMETHOD(SaveObject)(void)	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk){
		return E_NOTIMPL;
	}

	STDMETHOD(GetContainer)(IOleContainer **ppContainer){
		return E_NOTIMPL;
	}

	STDMETHOD(ShowObject)(void){
		return E_NOTIMPL;
	}

	STDMETHOD(OnShowWindow)(BOOL fShow){
		return E_NOTIMPL;
	}

	STDMETHOD(RequestNewObjectLayout)(void){
		return E_NOTIMPL;
	}
protected:
	STDMETHOD(peerQueryInterface)( REFIID riid, void** obj );

	Win32HTMLBrowser* peer_;
};



class WebBrowserEvents2Impl : public IDispatch {
public:
	WebBrowserEvents2Impl(Win32HTMLBrowser* peer) :peer_(peer) {

	}

	IUNKNOWNREFCOUNT_IMPL()

	STDMETHOD(QueryInterface)( REFIID riid, void** obj ) {
		HRESULT hr = E_NOINTERFACE;
		if ( riid == IID_IUnknown ) {
			*obj = (IUnknown*)this;
			hr = S_OK;
		}
		else if ( riid == IID_IDispatch ) {
			*obj = (IDispatch*)this;
			hr = S_OK;
		}
		else if ( riid == DIID_DWebBrowserEvents2 ) {
			*obj = (IDispatch*)this;
			hr = S_OK;
		}
		else {
			hr = peerQueryInterface( riid, obj );
		}
		return hr;
	}


	STDMETHOD(GetTypeInfoCount)( unsigned int *iTInfo	) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetTypeInfo)( unsigned int iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo ) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetIDsOfNames)( REFIID  riid, OLECHAR FAR* FAR*  rgszNames, unsigned int  cNames,
							LCID   lcid, DISPID FAR*  rgDispId ) {
		return E_NOTIMPL;
	}

	STDMETHOD(Invoke)( DISPID  dispIdMember, REFIID  riid, LCID  lcid, WORD  wFlags,
					DISPPARAMS FAR*  pDispParams, VARIANT FAR*  pVarResult,
					EXCEPINFO FAR*  pExcepInfo, unsigned int FAR* puArgErr );



	//[id(0x00000066)
	virtual void STDMETHODCALLTYPE OnStatusTextChange( LPCSTR val );

	//[id(0x00000068)
	virtual void STDMETHODCALLTYPE  OnDownloadComplete();

	//[id(0x00000069)
    virtual void STDMETHODCALLTYPE  OnCommandStateChange( long Command, BOOL Enable);

	//[id(0x0000006a)
    virtual void STDMETHODCALLTYPE  OnDownloadBegin();

	//[id(0x0000006c)
	virtual void STDMETHODCALLTYPE  OnProgressChange( long x, long y );

	//[id(0x00000070)
    virtual void STDMETHODCALLTYPE  OnPropertyChange( LPCSTR szProperty );

	//[id(0x00000071)
    virtual void STDMETHODCALLTYPE  OnTitleChange( LPCSTR Text);

	//[id(0x000000e1)
    virtual void STDMETHODCALLTYPE  OnPrintTemplateInstantiation( IDispatch* pDisp);

	//[id(0x000000e2)
    virtual void STDMETHODCALLTYPE  OnPrintTemplateTeardown( IDispatch* pDisp );

	//[id(0x000000e3)
    virtual void STDMETHODCALLTYPE  OnUpdatePageStatus(
                    IDispatch* pDisp,
                    VARIANT* nPage,
                    VARIANT* fDone) ;

	//[id(0x000000fa)
    virtual void STDMETHODCALLTYPE  OnBeforeNavigate2(
                    IDispatch* pDisp,
                    VARIANT* URL,
                    VARIANT* Flags,
                    VARIANT* TargetFrameName,
                    VARIANT* PostData,
                    VARIANT* Headers,
                    BOOL* Cancel );

	//[id(0x000000fb)
    virtual void STDMETHODCALLTYPE  OnNewWindow2(
                    IDispatch** ppDisp,
                    BOOL* Cancel);


	//[id(0x000000fc)
	virtual void STDMETHODCALLTYPE  OnNavigateComplete( IDispatch* dispatchPtr, VARIANT* URL );


	//[id(0x000000fd)
    virtual void STDMETHODCALLTYPE  OnQuit();

    //[id(0x00000103)
    virtual void STDMETHODCALLTYPE  OnDocumentComplete(
                    IDispatch* pDisp,
                    VARIANT* URL) ;

	//[id(0x00000107)
    virtual void STDMETHODCALLTYPE  OnWindowClosing( BOOL IsChildWindow, BOOL* Cancel );

	//[id(0x0000010c)
    virtual void STDMETHODCALLTYPE  OnClientToHostWindow( long* CX, long* CY );

	//[id(0x0000010d)
    virtual void STDMETHODCALLTYPE  OnSetSecureLockIcon( long SecureLockIcon );

	//[id(0x0000010e)
    virtual void STDMETHODCALLTYPE  OnFileDownload( VARIANT_BOOL* Cancel );

	//[id(0x0000010f)
    virtual void STDMETHODCALLTYPE  OnNavigateError(
                    IDispatch* pDisp,
                    VARIANT* URL,
                    VARIANT* Frame,
                    VARIANT* StatusCode,
                    BOOL* Cancel);

	//[id(0x00000110)
    virtual void STDMETHODCALLTYPE OnPrivacyImpactedStateChange( BOOL bImpacted ) ;

protected:
	STDMETHOD(peerQueryInterface)( REFIID riid, void** obj );

	Win32HTMLBrowser* peer_;
};


class DocHostUIHandler : public IDocHostUIHandler {
public:
	DocHostUIHandler(Win32HTMLBrowser* peer) : peer_(peer) {

	}

	IUNKNOWN_IMPL( IDocHostUIHandler, IID_IDocHostUIHandler )

	STDMETHOD(ShowContextMenu)(DWORD dwID, POINT FAR* ppt, IUnknown FAR* pcmdtReserved,
		IDispatch FAR* pdispReserved);

	STDMETHOD(GetHostInfo)(DOCHOSTUIINFO FAR *pInfo);

	STDMETHOD(ShowUI)(DWORD dwID, IOleInPlaceActiveObject FAR* pActiveObject,
		IOleCommandTarget FAR* pCommandTarget,
		IOleInPlaceFrame  FAR* pFrame,
		IOleInPlaceUIWindow FAR* pDoc)	{
		return E_NOTIMPL;
	}

	STDMETHOD(HideUI)(void)	{
		return E_NOTIMPL;
	}

	STDMETHOD(UpdateUI)(void)	{
		return E_NOTIMPL;
	}

	STDMETHOD(EnableModeless)(BOOL fEnable)	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnDocWindowActivate)(BOOL fActivate)	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnFrameWindowActivate)(BOOL fActivate)	{
		return E_NOTIMPL;
	}

	STDMETHOD(ResizeBorder)(LPCRECT prcBorder, IOleInPlaceUIWindow FAR* pUIWindow,
		BOOL fRameWindow)	{
		return E_NOTIMPL;
	}

	STDMETHOD(TranslateAccelerator)(LPMSG lpMsg, const GUID FAR* pguidCmdGroup,
		DWORD nCmdID)	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetOptionKeyPath)(LPOLESTR FAR* pchKey, DWORD dw)	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetDropTarget)(IDropTarget* pDropTarget, IDropTarget** ppDropTarget)	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetExternal)(IDispatch** ppDispatch) {
		return E_NOTIMPL;
	}

	STDMETHOD(TranslateUrl)(DWORD dwTranslate, OLECHAR* pchURLIn,
		OLECHAR** ppchURLOut)	{
		return E_NOTIMPL;
	}

	STDMETHOD(FilterDataObject)(IDataObject* pDO, IDataObject** ppDORet) {
		return E_NOTIMPL;
	}

protected:
	STDMETHOD(peerQueryInterface)( REFIID riid, void** obj );

	Win32HTMLBrowser* peer_;
};

class OLEInPlaceSite : public  IOleInPlaceSite {
public :
	OLEInPlaceSite(Win32HTMLBrowser* peer) : inPlaceActive_(false), peer_(peer) {

	}

	IUNKNOWN_IMPL( IOleInPlaceSite, IID_IOleInPlaceSite )

	STDMETHOD(GetWindow)( HWND * phwnd );

	STDMETHOD(ContextSensitiveHelp)( BOOL fEnterMode ) {
		return E_NOTIMPL;
	}

	STDMETHOD(CanInPlaceActivate)(void)	{
		return S_OK;
	}

	STDMETHOD(OnInPlaceActivate)(void) {
		inPlaceActive_ = true;
		return S_OK;
	}

	STDMETHOD(OnUIActivate)(void) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetWindowContext)(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
		LPRECT lprcPosRect, LPRECT lprcClipRect,
		LPOLEINPLACEFRAMEINFO lpFrameInfo)	;

	STDMETHOD(Scroll)(SIZE scrollExtant)	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnUIDeactivate)(BOOL fUndoable) {
		return E_NOTIMPL;
	}

	STDMETHOD(OnInPlaceDeactivate)( void) {
		inPlaceActive_ = false;
		return S_OK;
	}

	STDMETHOD(DiscardUndoState)( void) {
		return E_NOTIMPL;
	}

	STDMETHOD(DeactivateAndUndo)( void)	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect)	{
		return E_NOTIMPL;
	}

	bool inPlaceActive_;
protected:
	STDMETHOD(peerQueryInterface)( REFIID riid, void** obj );

	Win32HTMLBrowser* peer_;
};

/**
*Class Win32HTMLBrowser documentation
*/
class WIN32HTMLBROWSERAPI Win32HTMLBrowser : public AbstractWin32Component, public HTMLBrowserPeer {
public:
	BEGIN_CLASSINFO(Win32HTMLBrowser, "VCF::Win32HTMLBrowser", "VCF::AbstractWin32Component", WIN32HTMLBROWSER_CLASSID )
	END_CLASSINFO(Win32HTMLBrowser)

	Win32HTMLBrowser();

	virtual ~Win32HTMLBrowser();

	virtual void create( VCF::Control* owningControl );

	virtual void setFocused();

	virtual void createParams();

	virtual void setVisible( const bool& val );

	virtual LRESULT handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc = NULL );


	virtual String getCurrentURL();

	virtual void setCurrentURL( const String& url );

	virtual void goBack();

	virtual void goForward();

	virtual void goHome();

	virtual void refresh();

	virtual bool isLoadingURL();

	virtual void stopLoadingURL();

	virtual void setFromHTML( const String& html );

	friend class OLEClientSiteImpl;
	friend class WebBrowserEvents2Impl;
	friend class OLEInPlaceSite;
	friend class DocHostUIHandler;
protected:

	HWND browserHwnd_;

	IUnknownCollection webInterfaces_;
	OLEClientSiteImpl clientSite_;
	WebBrowserEvents2Impl browserEvents_;
	OLEInPlaceSite inPlaceSite_;
	DocHostUIHandler docHostHandler_;

	CAxWindow browser_;
	CComPtr<IWebBrowser2> spBrowser_;

	DWORD connectionPtCookie_;
	DWORD docHostUIFlags_;

	void getHostInfo(DOCHOSTUIINFO FAR *pInfo);

	HRESULT showContextMenu( DWORD dwID, POINT FAR* ppt, IUnknown FAR* pcmdtReserved,
		IDispatch FAR* pdispReserved);
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
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


