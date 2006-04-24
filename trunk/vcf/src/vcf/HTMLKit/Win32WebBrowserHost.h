#ifndef _VCF_WIN32WEBBROWSERHOST_H__
#define _VCF_WIN32WEBBROWSERHOST_H__



#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/HTMLKit/Win32HTMLDOMElements.h"

#ifndef _VCF_WIN32HTMLDOMELEMENTS_H__ 
//we need to pull all this stuff in
#include <exdisp.h>		// Defines of stuff like IWebBrowser2. This is an include file with Visual C 6 and above
#include <mshtml.h>		// Defines of stuff like IHTMLDocument2. This is an include file with Visual C 6 and above
#include <mshtmhst.h>	// Defines of stuff like IDocHostUIHandler. This is an include file with Visual C 6 and above

#include "thirdparty/win32/comet/threading.h"
#include "thirdparty/win32/comet/uuid.h"
#include "thirdparty/win32/comet/bstr.h"
#include "thirdparty/win32/comet/safearray.h"
#include "vcf/ApplicationKit/Win32HResult.h"

#include <vector>


#define COM_PTR(ifc) \
namespace comet { \
template<> struct comtype<ifc> { \
	static const IID& uuid() { \
        static const IID iid = IID_##ifc; \
        return iid; \
	} \
    typedef nil base;\
};\
};\
typedef comet::com_ptr<ifc> ifc##Ptr;\
\


COM_PTR(IHTMLDocument2)
COM_PTR(IHTMLElement)
COM_PTR(IHTMLElementCollection)
COM_PTR(IWebBrowser2)

#endif //_VCF_WIN32HTMLDOMELEMENTS_H__




using namespace comet;
typedef VCF::hresult hresult;

class IOleInPlaceFrameImpl : public IOleInPlaceFrame {
public:

	IOleInPlaceFrameImpl():wnd_(NULL){}

	STDMETHOD(QueryInterface)( REFIID iid, void ** ppvObject ) {
		if ( iid == IID_IOleInPlaceFrame ) {
			*ppvObject = (void*)(IOleInPlaceFrame*)this;
			return S_OK;
		}		
		else if ( iid == IID_IOleInPlaceUIWindow ) {
			*ppvObject = (void*)(IOleInPlaceUIWindow*)this;
			return S_OK;
		}
		else if ( iid == IID_IOleWindow ) {
			*ppvObject = (void*)(IOleWindow*)this;
			return S_OK;
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*)(IUnknown*)this;
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}

//IOleWindow
	STDMETHOD(GetWindow) ( HWND *phwnd ) {
		*phwnd = wnd_;
		return S_OK;
	}
	
	STDMETHOD(ContextSensitiveHelp)( BOOL fEnterMode ) {
		return E_NOTIMPL;
	}

//IOleInPlaceUIWindow 
	STDMETHOD(GetBorder)( LPRECT lprectBorder) {
		return E_NOTIMPL;
	}
        
    STDMETHOD(RequestBorderSpace)( LPCBORDERWIDTHS pborderwidths ) {
		return E_NOTIMPL;
	}
	
	STDMETHOD(SetBorderSpace)( LPCBORDERWIDTHS pborderwidths ) {
		return E_NOTIMPL;
	}
	
	STDMETHOD(SetActiveObject)( IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName) {
		return E_NOTIMPL;
	}

//IOleInPlaceFrame 
	STDMETHOD(InsertMenus)( HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths ) {
		return E_NOTIMPL;
	}
        
	STDMETHOD(SetMenu)( HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject) {
		return E_NOTIMPL;
	}
	
	STDMETHOD(RemoveMenus)( HMENU hmenuShared ) {
		return E_NOTIMPL;
	}	
	
	STDMETHOD(SetStatusText)( LPCOLESTR pszStatusText ) {
		return E_NOTIMPL;
	}
	
	STDMETHOD(EnableModeless)( BOOL fEnable ) {
		return E_NOTIMPL;
	}
        
	STDMETHOD(TranslateAccelerator)( LPMSG lpmsg, WORD wID ) {
		return E_NOTIMPL;
	}

	HWND wnd_;

};



class IOleInPlaceSiteImpl : public IOleInPlaceSite {
public:
	IOleInPlaceSiteImpl(): frameImpl_(NULL){}

	STDMETHOD(QueryInterface)( REFIID iid, void ** ppvObject ) {
		if ( iid == IID_IOleInPlaceSite ) {
			*ppvObject = (void*)(IOleInPlaceSite*)this;
			return S_OK;
		}
		else if ( iid == IID_IOleWindow ) {
			*ppvObject = (void*)(IOleWindow*)this;
			return S_OK;
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*)(IUnknown*)this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}

	//IOleWindow
	STDMETHOD(GetWindow) ( HWND *phwnd ) {
		*phwnd = frameImpl_->wnd_;
		return S_OK;
	}
	
	STDMETHOD(ContextSensitiveHelp)( BOOL fEnterMode ) {
		return E_NOTIMPL;
	}

	//IOleInPlaceSite

	STDMETHOD(CanInPlaceActivate)() {
		return S_OK;
	}
        
	STDMETHOD(OnInPlaceActivate)() {
		return S_OK;
	}
        
	STDMETHOD(OnUIActivate)() {
		return S_OK;
	}
        
    STDMETHOD(GetWindowContext)( IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
		LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)  {

		*ppFrame = frameImpl_;
		
		// We have no OLEINPLACEUIWINDOW
		*ppDoc = NULL;
		
		// Fill in some other info for the browser
		lpFrameInfo->fMDIApp = FALSE;
		lpFrameInfo->hwndFrame = frameImpl_->wnd_;
		lpFrameInfo->haccel = 0;
		lpFrameInfo->cAccelEntries = 0;

		return S_OK;
	}
        
	STDMETHOD(Scroll)( SIZE scrollExtant ) {
		return E_NOTIMPL;
	}
        
	STDMETHOD(OnUIDeactivate)( BOOL fUndoable ) {
		return S_OK;
	}
        
	STDMETHOD(OnInPlaceDeactivate)() {
		return S_OK;
	}
        
	STDMETHOD(DiscardUndoState)() {
		return E_NOTIMPL;
	}
        
	STDMETHOD(DeactivateAndUndo)()  {
		return E_NOTIMPL;
	}
        
	STDMETHOD(OnPosRectChange)( LPCRECT lprcPosRect ) {
		com_ptr<IOleInPlaceObject> inplace;
		IOleInPlaceObject* tmp;

		HRESULT res = browserObject_->QueryInterface( IID_IOleInPlaceObject, (void**)&tmp );
		if ( SUCCEEDED(res) ) {
			inplace = tmp;
			inplace->SetObjectRects( lprcPosRect, lprcPosRect );
		}

		return S_OK;
	}


	com_ptr<IOleObject> browserObject_;
	IOleInPlaceFrameImpl* frameImpl_;
};




class IDocHostUIHandlerImpl : public IDocHostUIHandler {
public:

	IDocHostUIHandlerImpl(): realImpl_(NULL) {}

	STDMETHOD(QueryInterface)( REFIID iid, void ** ppvObject ) {
		if ( iid == IID_IDocHostUIHandler ) {
			*ppvObject = (void*)(IDocHostUIHandler*)this;
			return S_OK;
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*)(IUnknown*)this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}

	STDMETHOD(ShowContextMenu)( DWORD hWndID, POINT *ppt, 
								IUnknown *pcmdtReserved, IDispatch *pdispReserved) {
		if ( NULL != realImpl_ ) {
			return realImpl_->ShowContextMenu(hWndID,ppt,pcmdtReserved,pdispReserved);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(GetHostInfo)( DOCHOSTUIINFO *pInfo ) {
		if ( NULL != realImpl_ ) {
			return realImpl_->GetHostInfo(pInfo);
		}

		pInfo->cbSize = sizeof(DOCHOSTUIINFO);

		pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER;

		pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

		return S_OK;
	}
	
	STDMETHOD(ShowUI)( DWORD dwID, IOleInPlaceActiveObject *pActiveObject,
						IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame,
						IOleInPlaceUIWindow *pDoc) {

		if ( NULL != realImpl_ ) {
			return realImpl_->ShowUI(dwID,pActiveObject,pCommandTarget,pFrame,pDoc);
		}

		return S_OK;
	}


	STDMETHOD(HideUI)(void) {
		if ( NULL != realImpl_ ) {
			return realImpl_->HideUI();
		}
		return E_NOTIMPL;
	}

	STDMETHOD(UpdateUI)(void) {
		if ( NULL != realImpl_ ) {
			return realImpl_->UpdateUI();
		}
		return S_OK;
	}

	STDMETHOD(EnableModeless)( BOOL fEnable) {
		if ( NULL != realImpl_ ) {
			return realImpl_->EnableModeless(fEnable);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(OnDocWindowActivate)( BOOL fEnable ) {
		if ( NULL != realImpl_ ) {
			return realImpl_->OnDocWindowActivate(fEnable);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(OnFrameWindowActivate)( BOOL fEnable ) {
		if ( NULL != realImpl_ ) {
			return realImpl_->OnFrameWindowActivate(fEnable);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(ResizeBorder)( LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow ) {
		if ( NULL != realImpl_ ) {
			return realImpl_->ResizeBorder(prcBorder,pUIWindow,fRameWindow);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(TranslateAccelerator)( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID ) {
		if ( NULL != realImpl_ ) {
			return realImpl_->TranslateAccelerator(lpMsg,pguidCmdGroup,nCmdID);
		}
		return S_OK;
	}

	STDMETHOD(GetOptionKeyPath)( LPOLESTR *pchKey, DWORD dw) {
		if ( NULL != realImpl_ ) {
			return realImpl_->GetOptionKeyPath(pchKey,dw);
		}
		return S_FALSE;
	}

	STDMETHOD(GetDropTarget)( IDropTarget *pDropTarget, IDropTarget **ppDropTarget) {
		if ( NULL != realImpl_ ) {
			return realImpl_->GetDropTarget(pDropTarget,ppDropTarget);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(GetExternal)( IDispatch **ppDispatch) {
		if ( NULL != realImpl_ ) {
			return realImpl_->GetExternal(ppDispatch);
		}
		return E_NOTIMPL;
	}
	
	STDMETHOD(TranslateUrl)( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut) {
		if ( NULL != realImpl_ ) {
			return realImpl_->TranslateUrl(dwTranslate,pchURLIn,ppchURLOut);
		}
		return E_NOTIMPL;
	}

	STDMETHOD(FilterDataObject)( IDataObject *pDO, IDataObject **ppDORet) {
		if ( NULL != realImpl_ ) {
			return realImpl_->FilterDataObject(pDO,ppDORet);
		}
		return E_NOTIMPL;
	}
	

	IDocHostUIHandlerImpl* realImpl_;
};



class IDispatchImpl : public IDispatch {
public:

	
	STDMETHOD(QueryInterface)( REFIID iid, void ** ppvObject ) {
		if ( iid == IID_IDispatch ) {
			*ppvObject = (void*)(IDispatch*)this;
			return S_OK;
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*)(IUnknown*)this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}

	STDMETHOD(GetTypeInfoCount)( UINT *iTInfo ) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetTypeInfo) ( UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo ) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetIDsOfNames)( REFIID riid, LPOLESTR* rgszNames, UINT cNames, 
								LCID lcid, DISPID* rgDispId )	{
		return E_NOTIMPL;
	}

	STDMETHOD(Invoke)( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, 
					DISPPARAMS* pDispParams, VARIANT* pVarResult, 
					EXCEPINFO* pExcepInfo, UINT* puArgErr ) {
		return E_NOTIMPL;
	}

};


class IServiceProviderImpl : public IServiceProvider {
public:
	IServiceProviderImpl(){}

	STDMETHOD(QueryInterface)( REFIID iid, void ** ppvObject ) {
		if ( iid == IID_IServiceProvider ) {
			*ppvObject = (void*)(IServiceProvider*)this;
			return S_OK;
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*)(IUnknown*)this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}
	
	STDMETHOD (QueryService)( REFGUID guidService, REFIID riid, void **ppv ) {
		return E_NOINTERFACE;
	}
};


class IAuthenticateImpl : public IAuthenticate {
public:
	IAuthenticateImpl(){};

	STDMETHOD (QueryInterface) (REFIID  riid, void** ppObj ) {
		if ( riid == IID_IAuthenticate ) {
			*ppObj = (void*) (IAuthenticate*)this;
			return S_OK;
		}
		else if ( riid == IID_IUnknown ) {
			*ppObj = (void*) (IUnknown*)this;
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}

	STDMETHOD(Authenticate)( HWND* phwnd, LPWSTR* pszUsername, 
							LPWSTR* pszPassword) {
		return E_NOTIMPL;
	}
};


class IOleClientSiteImpl : public IOleClientSite {
public:
	IOleClientSiteImpl() : inPlaceSite_(NULL), docUI_(NULL), serviceProvider_(NULL) {}


	STDMETHOD(QueryInterface)( REFIID iid, void ** ppvObject ) {
		
		if ( iid == IID_IOleClientSite ) {
			*ppvObject = (void*)(IOleClientSite*)this;
			return S_OK;
		}
		else if ( iid == IID_IOleInPlaceSite ) {			
			return inPlaceSite_->QueryInterface(iid,ppvObject);
		}
		else if ( iid == IID_IDocHostUIHandler ) {			
			return docUI_->QueryInterface(iid,ppvObject);
		}
		else if ( iid == IID_IServiceProvider ) {
			return serviceProvider_->QueryInterface(iid,ppvObject);
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*)(IUnknown*)this;
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG)AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG)Release() {
		return 0;
	}

	

	STDMETHOD(SaveObject)() {
		return E_NOTIMPL;
	}
        
	STDMETHOD(GetMoniker)( DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) {
		return E_NOTIMPL;
	}
        
	STDMETHOD(GetContainer)( IOleContainer **ppContainer ) {
		return E_NOTIMPL;
	}
        
	STDMETHOD(ShowObject)() {
		return E_NOTIMPL;
	}
        
	STDMETHOD(OnShowWindow)( BOOL fShow ) {
		return E_NOTIMPL;
	}
        
	STDMETHOD(RequestNewObjectLayout)() {
		return E_NOTIMPL;
	}


	IOleInPlaceSiteImpl* inPlaceSite_;
	IDocHostUIHandlerImpl* docUI_;
	IServiceProviderImpl* serviceProvider_;
};






class HTMLElementEventHandlerBase : public IDispatchImpl {
public:

	typedef void (*EventCallBack)(void);

	std::vector<EventCallBack> staticCallbacks;

	void add( EventCallBack cb ) {
		std::vector<EventCallBack>::iterator found =
			std::find( staticCallbacks.begin(), staticCallbacks.end(), cb );
		if ( found == staticCallbacks.end() ) {
			staticCallbacks.push_back( cb );
		}
	}

	void remove( EventCallBack cb ) {
		std::vector<EventCallBack>::iterator found =
			std::find( staticCallbacks.begin(), staticCallbacks.end(), cb );
		if ( found != staticCallbacks.end() ) {
			staticCallbacks.erase( found );
		}
	}

	virtual void fire() {
		std::vector<EventCallBack> tmp = staticCallbacks;
		std::vector<EventCallBack>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			EventCallBack cb = *it;
			(*cb)();
			it ++;
		}		
	}

	
	STDMETHOD(Invoke)( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, 
					DISPPARAMS* pDispParams, VARIANT* pVarResult, 
					EXCEPINFO* pExcepInfo, UINT* puArgErr ) {
		if ( 0 == dispIdMember ) {
			fire();
			return S_OK;
		}

		return E_NOTIMPL;
	}

};

template <typename ClassType>
class HTMLElementEventHandlerMethods : public HTMLElementEventHandlerBase {
public:
	typedef void (ClassType::*MethodEventCallBack)(void);


	std::vector< std::pair<ClassType*,MethodEventCallBack> > methodCallbacks;

	void add( ClassType* src, MethodEventCallBack cb ) {
		std::vector< std::pair<ClassType*,MethodEventCallBack> >::iterator found =
			std::find( methodCallbacks.begin(), methodCallbacks.end(), std::pair<ClassType*,MethodEventCallBack>(src,cb) );
		if ( found == methodCallbacks.end() ) {
			methodCallbacks.push_back( std::pair<ClassType*,MethodEventCallBack>(src,cb) );
		}
	}

	void remove( ClassType* src, MethodEventCallBack cb ) {		
		std::vector< std::pair<ClassType*,MethodEventCallBack> >::iterator found =
			std::find( methodCallbacks.begin(), methodCallbacks.end(), std::pair<ClassType*,MethodEventCallBack>(src,cb) );
		if ( found != methodCallbacks.end() ) {
			methodCallbacks.erase( found );
		}
	}

	virtual void fire() {
		std::vector< std::pair<ClassType*,MethodEventCallBack> > tmp = methodCallbacks;
		std::vector< std::pair<ClassType*,MethodEventCallBack> >::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			MethodEventCallBack cb = (*it).second;
			ClassType* src = (*it).first;
			(src->*cb)();
			it ++;
		}		
	}	
};


#ifdef USE_SIMPLE_HTMLDOM_WRAPPER

class HTMLElement;
class HTMLDocument;

class HTMLElementCollection {
public:

	friend class HTMLElement;
	friend class HTMLDocument;

	inline HTMLElementCollection():currentItem_(NULL){}

	inline HTMLElementCollection( IHTMLElementCollection* rhs ):currentItem_(NULL) {
		collectionImpl_ = rhs;
	}

	inline ~HTMLElementCollection();


	bool null() const {
		return collectionImpl_.is_null();
	}

	inline HTMLElementCollection& operator= ( IHTMLElementCollection* rhs ) {
		collectionImpl_ = rhs;
		return *this;
	}

	inline HTMLElementCollection& operator= ( const HTMLElementCollection& rhs ) {
		collectionImpl_ = rhs.collectionImpl_;
		return *this;
	}

	inline IHTMLElementCollection* in() const {
		return collectionImpl_.in();
	}
	
	inline IHTMLElementCollection** out() {
		return collectionImpl_.out();
	}
	

	inline std::string toString() const {
		bstr_t res;

		if ( collectionImpl_ ) {
			collectionImpl_->toString( res.out() );
		}

		return res;
	}

	inline void setLength( long len ) {
		if ( collectionImpl_ ) {
			collectionImpl_->put_length( (long)len );
		}
	}

	inline long getLength() const {
		long result = 0;
		if ( collectionImpl_ ) {
			collectionImpl_->get_length( &result );
		}
		return result;
	}


	inline HTMLElement* item( const std::string& name, long index );

	inline HTMLElement* item( const std::string& name );
	inline HTMLElement* item( long index );

	inline HTMLElement* operator[](long index);
	inline HTMLElement* operator[](const std::string& name);


	HTMLElementCollection tags( const std::string& tag ) {
		HTMLElementCollection result;
		

		variant_t tmpTag = tag;

		com_ptr<IDispatch> collection;

		collectionImpl_->tags( tmpTag.in(), collection.out() );

		if (collection) {
			result.collectionImpl_ = com_cast(collection);
		}

		return result;
	}
private:
	IHTMLElementCollectionPtr collectionImpl_;
	HTMLElement* currentItem_;
};


class HTMLElement {
public:

	inline HTMLElement(){}

	inline HTMLElement( IHTMLElement* rhs ) {
		elementImpl_ = rhs;
	}	

	inline HTMLElement& operator= ( IHTMLElement* rhs ) {
		elementImpl_ = rhs;
		return *this;
	}

	inline HTMLElement& operator= ( const HTMLElement& rhs ) {
		elementImpl_ = rhs.elementImpl_;
		return *this;
	}

	inline operator IHTMLElement* () const {
		return elementImpl_.in();
	}
	

	bool null() const {
		return elementImpl_.is_null();
	}

	void setAttribute( const std::string& attributeName,
						const std::string& attributeValue,
						bool caseSensitive ) {

		bstr_t name = attributeName;
		variant_t val = attributeValue;
		elementImpl_->setAttribute( name.in(), val.in(), caseSensitive ? TRUE:FALSE );
	}

	std::string getAttribute(const std::string& attributeName, bool caseSensitive=true) const {
		std::string result;

		variant_t tmp;
		bstr_t name = attributeName;

		elementImpl_->getAttribute(name.in(), caseSensitive ? TRUE:FALSE, tmp.out() );

		result = tmp;

		return result;
	}

	bool removeAttribute( const std::string& attributeName, bool caseSensitive=true ) {
		VARIANT_BOOL result = FALSE;
		bstr_t name = attributeName;
		elementImpl_->removeAttribute( name.in(), caseSensitive ? TRUE:FALSE, &result );
		return result ? true : false;
	}

	void setClassName( const std::string& className ) {

		elementImpl_->put_className( bstr_t(className).in() );
	}

	std::string getClassName() const {
		bstr_t tmp;
		elementImpl_->get_className( tmp.out() );
		return std::string(tmp);
	}

	void setID( const std::string& id ) {

		elementImpl_->put_id( bstr_t(id).in() );
	}

	std::string getID() const {
		bstr_t tmp;
		elementImpl_->get_id( tmp.out() );
		return std::string(tmp);
	}

	std::string getTagName() const {
		bstr_t tmp;
		elementImpl_->get_tagName( tmp.out() );
		return std::string(tmp);
	}

	HTMLElement getParent() const {
		IHTMLElementPtr parent;
		elementImpl_->get_parentElement( parent.out() );

		return HTMLElement(parent.in());
	}

	void setTitle( const std::string& title ) {
		elementImpl_->put_title( bstr_t(title).in() );		
	}

	std::string getTitle() const {
		bstr_t tmp;
		elementImpl_->get_title( tmp.out() );
		return std::string(tmp);
	}

	void setLanguage( const std::string& language ) {
		elementImpl_->put_language( bstr_t(language).in() );		
	}

	std::string getLanguage() const {
		bstr_t tmp;
		elementImpl_->get_language( tmp.out() );
		return std::string(tmp);
	}

	void scrollIntoView( bool atTop ) {
		elementImpl_->scrollIntoView( variant_t(atTop).in() );
	}

	bool contains( const HTMLElement& child ) const {
		VARIANT_BOOL result = FALSE;

		elementImpl_->contains( child.elementImpl_.in(), &result );

		return result ? true : false;
	}

	long getSourceIndex() const {
		long result = 0;

		elementImpl_->get_sourceIndex( &result );
		
		return result;
	}

	void setLang( const std::string& language ) {
		elementImpl_->put_lang( bstr_t(language).in() );		
	}

	std::string getLang() const {
		bstr_t tmp;
		elementImpl_->get_lang( tmp.out() );
		return std::string(tmp);
	}
	
	long getOffsetLeft() const {
		long result = 0;

		elementImpl_->get_offsetLeft( &result );
		
		return result;
	}

	long getOffsetTop() const {
		long result = 0;

		elementImpl_->get_offsetTop( &result );
		
		return result;
	}

	long getOffsetWidth() const {
		long result = 0;

		elementImpl_->get_offsetWidth( &result );
		
		return result;
	}

	long getOffsetHeight() const {
		long result = 0;

		elementImpl_->get_offsetHeight( &result );
		
		return result;
	}

	HTMLElement getOffsetParent() const {
		IHTMLElementPtr parent;
		elementImpl_->get_offsetParent( parent.out() );

		return HTMLElement(parent.in());
	}

	void setInnerHTML( const std::string& html ) {
		elementImpl_->put_innerHTML( bstr_t(html).in() );		
	}

	std::string getInnerHTML() const {
		bstr_t tmp;
		elementImpl_->get_innerHTML( tmp.out() );
		return std::string(tmp);
	}

	void setInnerText( const std::string& text ) {
		elementImpl_->put_innerText( bstr_t(text).in() );		
	}

	std::string getInnerText() const {
		bstr_t tmp;
		elementImpl_->get_innerText( tmp.out() );
		return std::string(tmp);
	}

	void setOuterHTML( const std::string& html ) {
		elementImpl_->put_outerHTML( bstr_t(html).in() );		
	}

	std::string getOuterHTML() const {
		bstr_t tmp;
		elementImpl_->get_outerHTML( tmp.out() );
		return std::string(tmp);
	}

	void setOuterText( const std::string& text ) {
		elementImpl_->put_outerText( bstr_t(text).in() );		
	}

	std::string getOuterText() const {
		bstr_t tmp;
		elementImpl_->get_outerText( tmp.out() );
		return std::string(tmp);
	}


	void insertAdjacentHTML( const std::string& where, const std::string& html ) {
		elementImpl_->insertAdjacentHTML( bstr_t(where).in(), bstr_t(html).in() );		
	}

	void insertAdjacentText( const std::string& where, const std::string& text ) {
		elementImpl_->insertAdjacentText( bstr_t(where).in(), bstr_t(text).in() );		
	}

	HTMLElement getParentTextEdit() const {
		IHTMLElementPtr parent;
		elementImpl_->get_parentTextEdit( parent.out() );

		return HTMLElement(parent.in());
	}

	bool getIsTextEdit() const {
		VARIANT_BOOL result = FALSE;
		elementImpl_->get_isTextEdit( &result );
		return result ? true : false;
	}

	void click() {
		elementImpl_->click();
	}

	std::string toString() const {
		bstr_t tmp;
		elementImpl_->toString( tmp.out() );
		return std::string(tmp);
	}

	HTMLElementCollection getChildren() {
		HTMLElementCollection result;
		com_ptr<IDispatch> collection;
		elementImpl_->get_children( collection.out() );
		if (collection) {
			result.collectionImpl_ = com_cast(collection);
		}

		return result;
	}

	HTMLElementCollection getAll() {
		HTMLElementCollection result;
		com_ptr<IDispatch> collection;
		elementImpl_->get_all( collection.out() );
		if (collection) {
			result.collectionImpl_ = com_cast(collection);
		}

		return result;
	}

	
	 
	/*	
            
get_style    put_onhelp    get_onhelp    
put_onclick    get_onclick    put_ondblclick    
get_ondblclick    put_onkeydown    get_onkeydown    
put_onkeyup    get_onkeyup    put_onkeypress    
get_onkeypress    put_onmouseout    get_onmouseout    
put_onmouseover    get_onmouseover    put_onmousemove    
get_onmousemove    put_onmousedown    get_onmousedown    
put_onmouseup    get_onmouseup    get_document    
            
    put_onselectstart    get_onselectstart    
           
get_recordNumber

get_filters    put_ondragstart    get_ondragstart    
toString    put_onbeforeupdate    get_onbeforeupdate    
put_onafterupdate    get_onafterupdate    put_onerrorupdate    
get_onerrorupdate    put_onrowexit    get_onrowexit    
put_onrowenter    get_onrowenter    put_ondatasetchanged    
get_ondatasetchanged    put_ondataavailable    get_ondataavailable    
put_ondatasetcomplete    get_ondatasetcomplete    put_onfilterchange    
get_onfilterchange           

	*/
private:
	IHTMLElementPtr elementImpl_;
};






class HTMLDocument {
public:

	inline HTMLDocument(){}

	inline HTMLDocument( IHTMLDocument2* rhs ) {
		docImpl_ = rhs;
	}	

	inline HTMLDocument& operator= ( IHTMLDocument2* rhs ) {
		docImpl_ = rhs;
		return *this;
	}

	inline HTMLDocument& operator= ( const HTMLDocument& rhs ) {
		docImpl_ = rhs.docImpl_;
		return *this;
	}

	inline operator IHTMLDocument2* () const {
		return docImpl_.in();
	}
	

	bool null() const {
		return docImpl_.is_null();
	}

	HTMLElementCollection getAll() {
		HTMLElementCollection result;		
		docImpl_->get_all( result.collectionImpl_.out() );		
		return result;
	}

	HTMLElement getBody() const {
		IHTMLElementPtr element;
		docImpl_->get_body( element.out() );

		return HTMLElement(element.in());
	}

	HTMLElement getActiveElement() const {
		IHTMLElementPtr element;
		docImpl_->get_activeElement( element.out() );

		return HTMLElement(element.in());
	}


	HTMLElementCollection getImages() {
		HTMLElementCollection result;		
		docImpl_->get_images( result.collectionImpl_.out() );		
		return result;
	}

	HTMLElementCollection getApplets() {
		HTMLElementCollection result;		
		docImpl_->get_applets( result.collectionImpl_.out() );		
		return result;
	}

	HTMLElementCollection getLinks() {
		HTMLElementCollection result;		
		docImpl_->get_links( result.collectionImpl_.out() );		
		return result;
	}

	HTMLElementCollection getForms() {
		HTMLElementCollection result;		
		docImpl_->get_forms( result.collectionImpl_.out() );		
		return result;
	}

	HTMLElementCollection getAnchors() {
		HTMLElementCollection result;		
		docImpl_->get_anchors( result.collectionImpl_.out() );		
		return result;
	}
	
	void setTitle( const std::string& title ) {
		docImpl_->put_title( bstr_t(title).in() );		
	}

	std::string getTitle() const {
		bstr_t tmp;
		docImpl_->get_title( tmp.out() );
		return std::string(tmp);
	}

	HTMLElementCollection getScripts() {
		HTMLElementCollection result;		
		docImpl_->get_scripts( result.collectionImpl_.out() );		
		return result;
	}


	std::string getReadyState() const {
		bstr_t tmp;
		docImpl_->get_readyState( tmp.out() );
		return std::string(tmp);
	}

	HTMLElementCollection getEmbeds() {
		HTMLElementCollection result;		
		docImpl_->get_embeds( result.collectionImpl_.out() );		
		return result;
	}

	HTMLElementCollection getPlugins() {
		HTMLElementCollection result;		
		docImpl_->get_plugins( result.collectionImpl_.out() );		
		return result;
	}

	std::string getReferrer() const {
		bstr_t tmp;
		docImpl_->get_referrer( tmp.out() );
		return std::string(tmp);
	}
	
	std::string getLastModified() const {
		bstr_t tmp;
		docImpl_->get_lastModified( tmp.out() );
		return std::string(tmp);
	}
	
	void setURL( const std::string& url ) {
		docImpl_->put_URL( bstr_t(url).in() );		
	}

	std::string getURL() const {
		bstr_t tmp;
		docImpl_->get_URL( tmp.out() );
		return std::string(tmp);
	}

	void setDomain( const std::string& domain ) {
		docImpl_->put_domain( bstr_t(domain).in() );		
	}

	std::string getDomain() const {
		bstr_t tmp;
		docImpl_->get_domain( tmp.out() );
		return std::string(tmp);
	}

	void setCookie( const std::string& cookie ) {
		docImpl_->put_cookie( bstr_t(cookie).in() );		
	}

	std::string getCookie() const {
		bstr_t tmp;
		docImpl_->get_cookie( tmp.out() );
		return std::string(tmp);
	}

	bool getExpando() const {
		VARIANT_BOOL result = FALSE;
		docImpl_->get_expando( &result );
		return result ? true : false;
	}

	void setExpando( bool expando ) {
		docImpl_->put_expando( expando ? TRUE : FALSE );
	}

	void setCharset( const std::string& val ) {
		docImpl_->put_charset( bstr_t(val).in() );		
	}

	std::string getCharset() const {
		bstr_t tmp;
		docImpl_->get_charset( tmp.out() );
		return std::string(tmp);
	}

	void setDefaultCharset( const std::string& val ) {
		docImpl_->put_defaultCharset( bstr_t(val).in() );		
	}

	std::string getDefaultCharset() const {
		bstr_t tmp;
		docImpl_->get_defaultCharset( tmp.out() );
		return std::string(tmp);
	}

	std::string getMimeType() const {
		bstr_t tmp;
		docImpl_->get_mimeType( tmp.out() );
		return std::string(tmp);
	}

	std::string getFileSize() const {
		bstr_t tmp;
		docImpl_->get_fileSize( tmp.out() );
		return std::string(tmp);
	}

	int getIntFileSize() const {
		bstr_t tmp;
		docImpl_->get_fileSize( tmp.out() );
		return atoi(tmp.s_str().c_str());
	}

	std::string getFileCreatedDate() const {
		bstr_t tmp;
		docImpl_->get_fileCreatedDate( tmp.out() );
		return std::string(tmp);
	}

	std::string getFileModifiedDate() const {
		bstr_t tmp;
		docImpl_->get_fileModifiedDate( tmp.out() );
		return std::string(tmp);
	}

	std::string getFileUpdatedDate() const {
		bstr_t tmp;
		docImpl_->get_fileUpdatedDate( tmp.out() );
		return std::string(tmp);
	}

	std::string getSecurity() const {
		bstr_t tmp;
		docImpl_->get_security( tmp.out() );
		return std::string(tmp);
	}

	std::string getProtocol() const {
		bstr_t tmp;
		docImpl_->get_protocol( tmp.out() );
		return std::string(tmp);
	}

	std::string getNameProp() const {
		bstr_t tmp;
		docImpl_->get_nameProp( tmp.out() );
		return std::string(tmp);
	} 

	std::string toString() const {
		bstr_t tmp;
		docImpl_->toString( tmp.out() );
		return std::string(tmp);
	} 
	   
	void write( const std::string& text ) {

		safearray_t<variant_t> sarr;
		
		variant_t v = text;
		sarr.push_back(v);

		docImpl_->write( sarr.in() );
	}

	void writeln( const std::string& text ) {

		safearray_t<variant_t> sarr;
		
		variant_t v = text;
		sarr.push_back(v);

		docImpl_->writeln( sarr.in() );
	}

	HTMLElement createElement( const std::string& elementTag ) const {
		IHTMLElementPtr element;
		docImpl_->createElement( bstr_t(elementTag).in(), element.out() );

		return HTMLElement(element.in());
	}

	void setDesignMode( bool val ) {
		bstr_t mode = val ? "on" : "off";
		docImpl_->put_designMode( mode.in() );
	}

	bool getDesignMode() const {
		bool result = false;
		bstr_t mode;
		docImpl_->get_designMode( mode.out() );

		if ( mode.s_str() == "off" ) {
			result = false;
		}
		else if ( mode.s_str() == "on" ) {
			result = true;
		}

		return result;
	}

	
	void copy() {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Copy";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void cut() {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Cut";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void paste() {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Paste";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void selectAll() {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "SelectAll";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void underline() {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Underline";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void bold() {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Bold";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void italic () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Italic";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void justifyLeft () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "JustifyLeft";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void justifyRight () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "JustifyRight";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void justifyCenter () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "JustifyCenter";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void justifyFull () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "JustifyFull";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void outdent () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Outdent ";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void indent () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Indent";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}

	void clearSelection () {
		variant_t v;
		VARIANT_BOOL res;
		bstr_t cmd = "Unselect";
		docImpl_->execCommand( cmd.in(), TRUE, v.in(), &res );
	}
	
	 
/*get_selection    
    get_frames      
    put_alinkColor    get_alinkColor  
put_bgColor    get_bgColor    put_fgColor    
get_fgColor  put_linkColor    get_linkColor    
put_vlinkColor    get_vlinkColor      
get_location          
            
                 
open    close    clear    
queryCommandSupported    queryCommandEnabled    queryCommandState    
queryCommandIndeterm    queryCommandText    queryCommandValue    
execCommand    execCommandShowHelp
*/

private:
	IHTMLDocument2Ptr docImpl_;
};



HTMLElementCollection::~HTMLElementCollection()
{
	delete currentItem_;
}

HTMLElement* HTMLElementCollection::item( const std::string& name, long index )
{
	HTMLElement* result = NULL;
	
	variant_t tmpName = index;
	variant_t tmpIndex = index;
	
	com_ptr<IDispatch> disp;
	collectionImpl_->item( tmpName.in(), tmpIndex.in(), disp.out() );
	if ( NULL != disp ) {
		IHTMLElementPtr item = com_cast( disp );
		if ( item ) {
			if ( NULL == currentItem_ ) {
				currentItem_ = new HTMLElement();
			}
			
			*currentItem_ = item.in();
			result = currentItem_;
		}
	}

	return result;
}


HTMLElement* HTMLElementCollection::item( const std::string& name )
{
	HTMLElement* result = NULL;
	variant_t tmpName = name;
	variant_t tmpIndex = name;
	
	com_ptr<IDispatch> disp;
	collectionImpl_->item( tmpName.in(), tmpIndex.in(), disp.out() );
	if ( NULL != disp ) {
		IHTMLElementPtr item = com_cast( disp );
		if ( item ) {
			if ( NULL == currentItem_ ) {
				currentItem_ = new HTMLElement();
			}
			
			*currentItem_ = item.in();
			result = currentItem_;
		}
	}

	return result;
}

HTMLElement* HTMLElementCollection::item( long index )
{
	HTMLElement* result = NULL;

	variant_t tmpName = index;
	variant_t tmpIndex = index;
	
	com_ptr<IDispatch> disp;
	collectionImpl_->item( tmpName.in(), tmpIndex.in(), disp.out() );
	if ( NULL != disp ) {
		IHTMLElementPtr item = com_cast( disp );
		if ( item ) {
			if ( NULL == currentItem_ ) {
				currentItem_ = new HTMLElement();
			}
			
			*currentItem_ = item.in();
			result = currentItem_;
		}
	}

	return result;
}


HTMLElement* HTMLElementCollection::operator[](long index)
{
	return item(index);
}

HTMLElement*HTMLElementCollection::operator[](const std::string& name)
{
	return item(name);
}

#endif //USE_SIMPLE_HTMLDOM_WRAPPER




class WebBrowserCtrl : public IDispatchImpl, protected IDocHostUIHandlerImpl, 
						protected IServiceProviderImpl,
						protected IAuthenticateImpl {
public:
	WebBrowserCtrl():connectionPointCookie_(0),uiStyle_(0) {
		OleInitialize(NULL);
		
		uiStyle_ |= DOCHOSTUIFLAG_NO3DBORDER;
	}

	virtual ~WebBrowserCtrl() {

		unembed();

		::OleUninitialize();
	}

	void unembed() {
		if ( connectionPointCookie_ != 0 ) {
			
			//remove connection point support
			IDispatch* thisDisp = this;
			com_ptr<IConnectionPointContainer> cpContainer = com_cast(oleObject_);
			if ( cpContainer ) {
				com_ptr<IConnectionPoint> cp;
				hresult res = cpContainer->FindConnectionPoint( DIID_DWebBrowserEvents2, cp.out() ); 
				if ( res.ok() && !cp.is_null() ) {
					res = cp->Unadvise( connectionPointCookie_ );
				}
			}
		}

		if ( oleObject_ ) {
			oleObject_->Close( OLECLOSE_NOSAVE );
		}

		storagePtr_ = NULL;
		oleObject_ = NULL;
		browser_ = NULL;

		if ( NULL != site_ ) {
			delete site_->docUI_;
			site_->docUI_ = NULL;
			delete site_->inPlaceSite_->frameImpl_;
			site_->inPlaceSite_->frameImpl_ = NULL;
			delete site_->inPlaceSite_;
			site_->inPlaceSite_ = NULL;
			delete site_;
			site_ = NULL;
		}

		connectionPointCookie_ = 0;
	}

	void embed( HWND hwnd ) {
		StgCreateDocfile( NULL, STGM_DIRECT | STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 
			0, storagePtr_.out() );

		site_ = new IOleClientSiteImpl();
		site_->docUI_ = new IDocHostUIHandlerImpl();
		
		site_->docUI_->realImpl_ = this;

		site_->inPlaceSite_ = new IOleInPlaceSiteImpl();
		
		site_->inPlaceSite_->frameImpl_ = new IOleInPlaceFrameImpl();
		
		site_->inPlaceSite_->frameImpl_->wnd_ = hwnd;
		
		site_->serviceProvider_ = this;

		IOleObject* oleObject;
		
		hresult res = ::OleCreate( CLSID_WebBrowser, 
									IID_IOleObject, 
									OLERENDER_DRAW, 
									0, 
									site_,
									storagePtr_.in(), 
									(void**)&oleObject );

		if ( res ) {
			oleObject_ = oleObject;

			site_->inPlaceSite_->browserObject_ = oleObject;
			
			oleObject_->SetHostNames( L"WebBrowser", NULL );
			
			RECT rect = {0,0,100,100};
			//::GetClientRect(hwnd, &rect);
			res = ::OleSetContainedObject( oleObject_.in(), TRUE );
			if ( res ) {
				
				res = oleObject_->DoVerb( OLEIVERB_SHOW, NULL, site_, 0, hwnd, &rect );
				
				if ( res ) {
					browser_ = com_cast(oleObject_);
					
					browser_->put_Left( 0 );
					browser_->put_Top( 0 );
					browser_->put_Width( rect.right - rect.left );
					browser_->put_Height( rect.bottom - rect.top );
					



					//add connection point support
					connectionPointCookie_ = 0;
					IDispatch* thisDisp = this;
					com_ptr<IConnectionPointContainer> cpContainer = com_cast(oleObject_);
					if ( cpContainer ) {
						com_ptr<IConnectionPoint> cp;
						res = cpContainer->FindConnectionPoint( DIID_DWebBrowserEvents2, cp.out() ); 
						if ( res.ok() && !cp.is_null() ) {
							res = cp->Advise( thisDisp, &connectionPointCookie_ );
						}
					}
				}
			}
		}
	}

	void openURL( const std::string& urlStr ) {
		variant_t url;
		url = urlStr.c_str();
		browser_->Navigate2( url.inout(), NULL, NULL, NULL, NULL );	
	}

	static std::string resourceToURL( const std::string& resourceStr ) {
		char tmp[_MAX_PATH * 2];
		char module[_MAX_PATH];
		if ( GetModuleFileName(NULL, module, _MAX_PATH) )	{
			sprintf( tmp, "res://%s/%s", module, resourceStr.c_str());
			return std::string(tmp);
		}

		return std::string("");
	}

	void openResource( const std::string& resourceStr ) {

		variant_t url;
		url = WebBrowserCtrl::resourceToURL(resourceStr).c_str();
		browser_->Navigate2( url.inout(), NULL, NULL, NULL, NULL );	
	}

	std::string getCurrentURL() const {
		
		IHTMLDocument2Ptr doc;
		com_ptr<IDispatch> disp;
		browser_->get_Document( disp.out() );
		if ( disp ) {
			doc = com_cast(disp);
			bstr_t tmp;
			doc->get_URL( tmp.out() );
			return std::string(tmp);
		}
		
		return "";
	}

	void resize( int w, int h ) {
		if ( browser_ ) {
			browser_->put_Width( w );
			browser_->put_Height( h );
		}
	}

#ifdef USE_SIMPLE_HTMLDOM_WRAPPER
	HTMLDocument getDocument() {
		IHTMLDocument2Ptr doc;
		com_ptr<IDispatch> disp;
		browser_->get_Document( disp.out() );

		if ( disp ) {
			doc = com_cast(disp);
			return HTMLDocument( doc.in() );
		}

		return HTMLDocument();
	}
#endif //USE_SIMPLE_HTMLDOM_WRAPPER

	void home() {
		browser_->GoHome();
	}

	void back() {
		browser_->GoBack();
	}

	void forward() {
		browser_->GoForward();
	}

	void refresh() {
		browser_->Refresh();
	}

	void stop() {
		browser_->Stop();
	}


	bool busy() const {
		VARIANT_BOOL b = FALSE;
		browser_->get_Busy( &b );
		return b ? true : false;
	}
	

/*
	void test() {
		com_ptr<IHTMLElementCollection> collection;
		IHTMLElementPtr item;
		com_ptr<IDispatch> disp;
		IHTMLDocument2Ptr doc;
		browser_->get_Document( disp.out() );
		
		doc = com_cast( disp );
		if ( doc ) {
			doc->get_all( collection.out() );
			if ( collection ) {

				HTMLElementCollection coll2 = collection.in();

				long len = coll2.getLength();
				//collection->get_length( &len );
				for (int i=0;i<len;i++ ) {
					HTMLElement* f = coll2[i];
					
					if ( f ) {
						if ( "IndicativePrices" == f->getID() ) {
							HTMLElementEventHandlerMethods<WebBrowserCtrl>* eventHandler = 
								new HTMLElementEventHandlerMethods<WebBrowserCtrl>();
							
							eventHandler->add( this, &WebBrowserCtrl::onDoIt );
							
							com_ptr<IDispatch> idisp = eventHandler;
							
					
							item = *f;

							variant_t e;
							e = idisp;
							
							item->put_onclick( e.in() );
							
						}
					}
				}
			}
		}
	}
*/




	//IDispatch impl
	//this should get called back by the connection point container...
	STDMETHOD(Invoke)( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, 
					DISPPARAMS* pDispParams, VARIANT* pVarResult, 
					EXCEPINFO* pExcepInfo, UINT* puArgErr ) {
		
		hresult res = S_OK;

		//note that pDispParams arguments are in order from LAST to FIRST!!!		
		switch ( dispIdMember ) {
			case 0x00000068 : {				
				onDownloadComplete();
			}
			break;

			case 0x000000fc : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == VT_DISPATCH );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_VARIANT|VT_BYREF) );

				onNavigateComplete( pDispParams->rgvarg[1].pdispVal,  pDispParams->rgvarg[0].pvarVal );
			}
			break;

			case 0x0000006c : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( (pDispParams->rgvarg[1].vt & VT_I4) != 0 );
				VCF_ASSERT( (pDispParams->rgvarg[0].vt & VT_I4) != 0 );

				onProgressChange( pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal );
			}
			break;

			case 0x00000066 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == VT_BSTR );

				onStatusTextChange( pDispParams->rgvarg[0].bstrVal );
			}
			break;

			case 0x00000069 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == VT_I4 );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == VT_BOOL );
				onCommandStateChange( pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].boolVal );
			}
			break;

			case 0x0000006a : {
				
				onDownloadBegin();
			}
			break;

			case 0x00000071 : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == VT_BSTR );

				onTitleChange( pDispParams->rgvarg[0].bstrVal );
			}
			break;

			case 0x00000070 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == VT_BSTR );

				onPropertyChange( pDispParams->rgvarg[0].bstrVal );
			}
			break;

			case 0x000000fa : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 7 );
				VCF_ASSERT( (pDispParams->rgvarg[6].vt & VT_DISPATCH) != 0 );
				VCF_ASSERT( pDispParams->rgvarg[5].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[4].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[3].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[4].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[2].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_BOOL) );

				onBeforeNavigate2( pDispParams->rgvarg[6].pdispVal, 
									pDispParams->rgvarg[5].pvarVal,
									pDispParams->rgvarg[4].pvarVal,
									pDispParams->rgvarg[3].pvarVal,
									pDispParams->rgvarg[2].pvarVal,
									pDispParams->rgvarg[1].pvarVal,
									pDispParams->rgvarg[0].pboolVal );

			}
			break;

			case 0x000000fb : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_BYREF|VT_DISPATCH) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_BOOL) );


				onNewWindow2( pDispParams->rgvarg[1].ppdispVal, pDispParams->rgvarg[0].pboolVal );
				
			}
			break;

			case 0x00000103 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_DISPATCH) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_VARIANT) );

				onDocumentComplete( pDispParams->rgvarg[1].pdispVal, 
									pDispParams->rgvarg[0].pvarVal );
			}
			break;

			case 0x000000fd : {
				

				onQuit();
			}
			break;

			case 0x00000107 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_BOOL) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_BOOL) );


				onWindowClosing( pDispParams->rgvarg[1].boolVal, pDispParams->rgvarg[0].pboolVal );
			}
			break;

			case 0x0000010c : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 2 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_BYREF|VT_I4) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_I4) );


				onClientToHostWindow( pDispParams->rgvarg[1].plVal, pDispParams->rgvarg[0].plVal );
			}
			break;

			case 0x0000010d : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_I4) );


				onSetSecureLockIcon( pDispParams->rgvarg[0].lVal );
			}
			break;

			case 0x0000010e : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs >= 1 ); // should be just 1???
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_BOOL) );


				onFileDownload( pDispParams->rgvarg[0].pboolVal );
			}
			break;

			case 0x0000010f : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 5 );
				VCF_ASSERT( (pDispParams->rgvarg[4].vt & VT_DISPATCH) != 0 );
				VCF_ASSERT( pDispParams->rgvarg[3].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[2].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_BOOL) );

				onNavigateError( pDispParams->rgvarg[4].pdispVal, 
									pDispParams->rgvarg[3].pvarVal,
									pDispParams->rgvarg[2].pvarVal,
									pDispParams->rgvarg[1].pvarVal,
									pDispParams->rgvarg[0].pboolVal );
			}
			break;

			case 0x000000e1 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( (pDispParams->rgvarg[0].vt & VT_DISPATCH) != 0 );

				onPrintTemplateInstantiation( pDispParams->rgvarg[0].pdispVal );
			}
			break;

			case 0x000000e2 : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( (pDispParams->rgvarg[0].vt & VT_DISPATCH) != 0 );

				onPrintTemplateTeardown( pDispParams->rgvarg[0].pdispVal );
			}
			break;

			case 0x000000e3 : {
				

				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 3 );
				VCF_ASSERT( (pDispParams->rgvarg[2].vt & VT_DISPATCH) != 0 );
				VCF_ASSERT( pDispParams->rgvarg[1].vt == (VT_BYREF|VT_VARIANT) );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BYREF|VT_VARIANT) );

				onUpdatePageStatus( pDispParams->rgvarg[2].pdispVal, 
									pDispParams->rgvarg[1].pvarVal,
									pDispParams->rgvarg[0].pvarVal );
			}
			break;

			case 0x00000110 : {
				
				VCF_ASSERT( pDispParams != NULL );
				VCF_ASSERT( pDispParams->cArgs == 1 );
				VCF_ASSERT( pDispParams->rgvarg[0].vt == (VT_BOOL) );

				onPrivacyImpactedStateChange( pDispParams->rgvarg[0].boolVal );
			}
			break;

			default : {
				res = E_NOTIMPL;
			}
			break;
		}

		return res;
	}

protected:

	//[id(0x00000068) 
	virtual void onDownloadComplete(){};

	//[id(0x000000fc) 
	virtual void onNavigateComplete( LPDISPATCH dispatchPtr, VARIANT* URL ){};
	
	//[id(0x0000006c)
	virtual void onProgressChange( long x, long y ){};

	//[id(0x00000066)
	virtual void onStatusTextChange( BSTR val ){};
	
	
    //[id(0x00000069)
    virtual void onCommandStateChange( long Command, BOOL Enable){};

    //[id(0x0000006a)
    virtual void onDownloadBegin(){};
    
	//[id(0x00000071)
    virtual void onTitleChange( BSTR Text){};
    
	//[id(0x00000070)
    virtual void onPropertyChange( BSTR szProperty ){};
    
	//[id(0x000000fa)
    virtual void onBeforeNavigate2(
                    LPDISPATCH pDisp, 
                    VARIANT* URL, 
                    VARIANT* Flags, 
                    VARIANT* TargetFrameName, 
                    VARIANT* PostData, 
                    VARIANT* Headers, 
                    VARIANT_BOOL* Cancel ){};
    
	//[id(0x000000fb)
    virtual void onNewWindow2(
                    LPDISPATCH* ppDisp, 
                    VARIANT_BOOL* Cancel){};
    
	//[id(0x00000103)
    virtual void onDocumentComplete(
                    LPDISPATCH pDisp, 
                    VARIANT* URL){};
    
	//[id(0x000000fd)
    virtual void onQuit(){};
    
	//[id(0x00000107)
    virtual void onWindowClosing( VARIANT_BOOL IsChildWindow, VARIANT_BOOL* Cancel ){};
    
	//[id(0x0000010c)
    virtual void onClientToHostWindow( long* CX, long* CY ){};
    
	//[id(0x0000010d)
    virtual void onSetSecureLockIcon( long SecureLockIcon ){};
    
	//[id(0x0000010e)
    virtual void onFileDownload( VARIANT_BOOL* Cancel ){};
    
	//[id(0x0000010f)
    virtual void onNavigateError(
                    LPDISPATCH pDisp, 
                    VARIANT* URL, 
                    VARIANT* Frame, 
                    VARIANT* StatusCode, 
                    VARIANT_BOOL* Cancel){};
    
	//[id(0x000000e1)
    virtual void onPrintTemplateInstantiation( LPDISPATCH pDisp){};
    
	//[id(0x000000e2)
    virtual void onPrintTemplateTeardown( LPDISPATCH pDisp ){};
    
	//[id(0x000000e3)
    virtual void onUpdatePageStatus(
                    LPDISPATCH pDisp, 
                    VARIANT* nPage, 
                    VARIANT* fDone) {};
    
	//[id(0x00000110)
    virtual void onPrivacyImpactedStateChange( VARIANT_BOOL bImpacted ) {}



	IOleClientSiteImpl* site_;
	com_ptr<IStorage> storagePtr_;
	com_ptr<IOleObject> oleObject_;
	com_ptr<IWebBrowser2> browser_;
	DWORD connectionPointCookie_;
	DWORD uiStyle_;
};

#endif //_VCF_WIN32WEBBROWSERHOST_H__
