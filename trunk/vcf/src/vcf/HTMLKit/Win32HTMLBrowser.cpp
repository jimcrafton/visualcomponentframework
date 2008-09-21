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
COM_PTR(IOleWindow)
COM_PTR(IHTMLElement2)
COM_PTR(IHTMLWindow2)
COM_PTR(IHTMLEventObj)
 



using namespace VCF;


STDMETHODIMP HTMLEventHandler::Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, 
										WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, 
										EXCEPINFO* pExcepInfo, UINT* puArgErr ) 
{
	if ( 0 == dispIdMember ) {
		HTMLElementEvent e(eventSource,HTMLBrowserControl::heElementClicked);
		e.elementID = elementID;	
		
		HTMLElement srcElement;
		HTMLElement fromElement;
		HTMLElement toElement;
		VCF::HTMLElementPeer peer;


		IHTMLElementPtr htmlElement;
		IHTMLEventObjPtr eventObj;

		if ( element ) {
			com_ptr<IDispatch> disp;
			IHTMLDocument2Ptr doc;
			element->get_document( disp.out() );
			doc = com_cast( disp );
			if ( doc ) {
				IHTMLWindow2Ptr window;
				doc->get_parentWindow( window.out() );
				if ( window ) {
					
					window->get_event( eventObj.out() );
					if ( eventObj ) {
						eventObj->get_srcElement( htmlElement.out() );
						if ( htmlElement ) {
							peer = com_cast( htmlElement );
							srcElement.setPeer( &peer );

							e.srcElement = &srcElement;
						}

						eventObj->get_fromElement( htmlElement.out() );
						if ( htmlElement ) {
							peer = com_cast( htmlElement );
							fromElement.setPeer( &peer );

							e.fromElement = &fromElement;
						}

						eventObj->get_toElement( htmlElement.out() );
						if ( htmlElement ) {
							peer = com_cast( htmlElement );
							toElement.setPeer( &peer );

							e.toElement = &toElement;
						}


						VARIANT_BOOL val = FALSE;
						eventObj->get_altKey( &val );
						e.altKey = val ? true : false;

						eventObj->get_cancelBubble( &val );
						e.cancelBubble = val ? true : false;

						eventObj->get_ctrlKey( &val );
						e.ctrlKey = val ? true : false;

						eventObj->get_shiftKey( &val );
						e.shiftKey = val ? true : false;

						variant_t varVal;
						eventObj->get_returnValue( varVal.out() );
						e.returnValue = varVal ? true : false;


						long lval = 0;
						eventObj->get_button( &lval );
						switch ( lval ) {
							case 0 : {
								//no button
							}
							break;

							case 1 : {
								e.button = mbmLeftButton;
							}
							break;

							case 2 : {
								e.button = mbmRightButton;
							}
							break;

							case 3 : {
								e.button = mbmLeftButton | mbmRightButton;
							}
							break;

							case 4 : {
								e.button = mbmMiddleButton;
							}
							break;

							case 5 : {
								e.button = mbmLeftButton | mbmMiddleButton;
							}
							break;

							case 6 : {
								e.button = mbmRightButton | mbmMiddleButton;
							}
							break;

							case 7 : {
								e.button = mbmRightButton | mbmMiddleButton | mbmLeftButton;
							}
							break;
						}



						eventObj->get_clientX( &lval );
						e.clientX = lval;

						eventObj->get_clientY( &lval );
						e.clientY = lval;

						eventObj->get_offsetX( &lval );
						e.offsetX = lval;

						eventObj->get_offsetY( &lval );
						e.offsetY = lval;

						eventObj->get_screenX( &lval );
						e.screenX = lval;

						eventObj->get_screenY( &lval );
						e.screenY = lval;

						eventObj->get_x( &lval );
						e.x = lval;

						eventObj->get_y( &lval );
						e.y = lval;


						eventObj->get_keyCode( &lval );
						e.keyCode = lval;

						bstr_t bstrVal;
						eventObj->get_qualifier( bstrVal.out() );

						e.qualifier = bstrVal;

						eventObj->get_type( bstrVal.out() );

						e.type = bstrVal;
					}
				}
			}			
		}
		

		if ( this->eventType != -1 ) {
			e.setType( eventType );
			
			switch ( eventType ) {
				case HTMLBrowserControl::heElementClicked : {
					domComponent->Click( &e );
				}
				break;

				case HTMLBrowserControl::heElementDblClicked : {
					domComponent->DblClick( &e );
				}
				break;

				case HTMLBrowserControl::heElementDragStart : {
					domComponent->DragStart( &e );
				}
				break;

				case HTMLBrowserControl::heElementDragEnd : {
					domComponent->DragEnd( &e );
				}
				break;

				case HTMLBrowserControl::heElementKeyDown : {
					domComponent->KeyDown( &e );
				}
				break;

				case HTMLBrowserControl::heElementKeyPress : {
					domComponent->KeyPress( &e );
				}
				break;

				case HTMLBrowserControl::heElementKeyUp : {
					domComponent->KeyUp( &e );
				}
				break;

				case HTMLBrowserControl::heElementMouseDown : {
					domComponent->MouseDown( &e );
				}
				break;

				case HTMLBrowserControl::heElementMouseMove : {
					domComponent->MouseMove( &e );
				}
				break;

				case HTMLBrowserControl::heElementMouseOver : {
					domComponent->MouseOver( &e );
				}
				break;

				case HTMLBrowserControl::heElementMouseOut : {
					domComponent->MouseOut( &e );
				}
				break;

				case HTMLBrowserControl::heElementMouseUp : {
					domComponent->MouseUp( &e );
				}
				break;
			}
		}
		else if ( NULL != handler ) {
			handler->invoke( &e );
		}
		

		if ( eventObj ) {
			VARIANT_BOOL val = e.cancelBubble ? TRUE : FALSE;
			eventObj->put_cancelBubble( val );

			long lval = e.keyCode;
			eventObj->put_keyCode( lval );

			variant_t var;
			var = e.returnValue;
			eventObj->put_returnValue( var.in() );

		}

		return S_OK;
	}
	
	return E_NOTIMPL;
}



bool Win32HTMLBrowser::msgFilter( MSG* msg, void* data )
{
	Win32HTMLBrowser* thisPtr = (Win32HTMLBrowser*)data;

	if ( NULL != thisPtr ) {
		return thisPtr->processMessageFilter( msg );
	}

	return false;
}



Win32HTMLBrowser::Win32HTMLBrowser():
	browserHwnd_(NULL)	,
		msgFilterID_(0),
		oldBrowserWndProc_(NULL)
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

			IOleWindowPtr wnd = com_cast(browser_); 
			if ( wnd ) {
				wnd->GetWindow( &browserHwnd_ );
			}

			//Win32HTMLBrowser::browserWndProc
			if ( NULL != browserHwnd_ ) {
				//::SetWindowLongPtr( browserHwnd_, GWLP_USERDATA, (LONG_PTR)this );
				//oldBrowserWndProc_ = (WNDPROC)(LONG_PTR) ::SetWindowLongPtr( treeWnd_, GWLP_WNDPROC, (LONG_PTR)Win32Tree::TreeWndProc );
			}

			inPlaceObj_ = com_cast( browser_ );

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

LRESULT CALLBACK Win32HTMLBrowser::browserWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
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
		IHTMLInputElementPtr input = com_cast( item );

		if ( input ) {
			input->get_value( val.out() );
		}
		else {
			if ( textIsHTML ) {
				item->get_innerHTML( val.out() );
			}
			else {
				item->get_innerText( val.out() );
			}
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

		IHTMLInputElementPtr input = com_cast( item );

		bstr_t val = text.c_str();						

		if ( input ) {
			input->put_value( val.in() );
		}
		else {
			if ( textIsHTML ) {
				item->put_innerHTML( val.in() );
			}
			else {
				item->put_innerText( val.in() );
			}
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
		
		HTMLNewWindowEvent e(peerControl_,HTMLBrowserControl::heNewWindowDisplayed);
		HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;
		
		browserCtrl->NewWindowDisplayed( &e );
		if ( !e.allowNewWindow ) {
			*Cancel = TRUE;
		}
	}
}

void Win32HTMLBrowser::urlLoaded( Component* component )
{
	Enumerator<Component*>* comps = component->getComponents();
	while ( comps->hasMoreElements() ) {
		Component* c = comps->nextElement();
		urlLoaded( c );
	}

	HTMLEvent e(peerControl_,HTMLBrowserControl::heURLLoaded);
	component->handleEvent( &e );
}


HTMLEventHandler* Win32HTMLBrowser::createHTMLEventHandler( const String& elementName, const String& name )
{
	HTMLEventHandler* result = NULL;
	result = getElementEventHandler(name);
	if ( NULL == result ) {
		result = new HTMLEventHandler();
		eventHandlers_[name] = result;
	}
	
	result->eventSource = peerControl_;
	result->handler = NULL;
	result->elementID = elementName;

	return result;
}

void Win32HTMLBrowser::updateCallbacks( DOMElementComponent* component )
{
	VCF::HTMLElementCollectionPeer collection;	
	com_ptr<IDispatch> disp;
	IHTMLDocument2Ptr doc;
	browser_->get_Document( disp.out() );
	doc = com_cast( disp );
	if ( doc ) {
		doc->get_all( collection.out() );
		if ( collection ) {

			String elementName = component->getName();

			VCF::HTMLElementCollection coll2;
			coll2.setPeer( &collection );

			long len = coll2.getLength();

			for (int i=0;i<len;i++ ) {
				VCF::HTMLElement* f = coll2[i];
				if ( NULL != f ) {				

					if ( elementName == f->getID() ) {

						variant_t e;
						com_ptr<IDispatch> idisp;
						HTMLEventHandler* htmlHandler;
						String name;

						if ( !component->Click.empty() ) {
							name = elementName + "_onclick";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementClicked;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;
							(*f->getPeer())->put_onclick( e.in() );
						}

						if ( !component->DblClick.empty() ) {
							name = elementName + "_ondblclick";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementDblClicked;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_ondblclick( e.in() );
						}

						if ( !component->DragStart.empty() ) {
							name = elementName + "_ondragstart";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementDragStart;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_ondragstart( e.in() );
						}

						IHTMLElement2Ptr element = com_cast( *f->getPeer() );
						if ( element ) {
							if ( !component->DragEnd.empty() ) {
								name = elementName + "_ondragend";
								
								htmlHandler = createHTMLEventHandler( elementName, name );
								htmlHandler->domComponent = component;
								htmlHandler->eventType = HTMLBrowserControl::heElementDragEnd;
								htmlHandler->element = *f->getPeer();

								
								idisp = htmlHandler;							
								e = idisp;							
								element->put_ondragend( e.in() );
							}
						}

						if ( !component->KeyDown.empty() ) {
							name = elementName + "_onkeydown";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementKeyDown;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onkeydown( e.in() );
						}

						if ( !component->KeyPress.empty() ) {
							name = elementName + "_onkeypress";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementKeyPress;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onkeypress( e.in() );
						}

						if ( !component->KeyUp.empty() ) {
							name = elementName + "_onkeyup";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementKeyUp;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onkeyup( e.in() );
						}

						if ( !component->MouseDown.empty() ) {
							name = elementName + "_onmousedown";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementMouseDown;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onmousedown( e.in() );
						}

						if ( !component->MouseMove.empty() ) {
							name = elementName + "_onmousemove";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementMouseMove;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onmousemove( e.in() );
						}

						if ( !component->MouseOver.empty() ) {
							name = elementName + "_onmouseover";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementMouseOver;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onmouseover( e.in() );
						}

						if ( !component->MouseOut.empty() ) {
							name = elementName + "_onmouseout";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementMouseOut;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onmouseout( e.in() );
						}

						if ( !component->MouseUp.empty() ) {
							name = elementName + "_onmouseup";
							
							htmlHandler = createHTMLEventHandler( elementName, name );
							htmlHandler->domComponent = component;
							htmlHandler->eventType = HTMLBrowserControl::heElementMouseUp;
							htmlHandler->element = *f->getPeer();
							
							idisp = htmlHandler;							
							e = idisp;							
							(*f->getPeer())->put_onmouseup( e.in() );
						}
						

						
						break;
					}
				}
			}			
		}
	}
}

void Win32HTMLBrowser::onDocumentComplete( LPDISPATCH pDisp, VARIANT* URL)
{
	clearHTMLHandlers();

	HTMLEvent e(peerControl_,HTMLBrowserControl::heURLLoaded);
	HTMLBrowserControl* browserCtrl = (HTMLBrowserControl*)peerControl_;

	if ( NULL != URL && URL->vt == VT_BSTR ) {
		bstr_t tmp;
		tmp = URL->bstrVal;
		e.url = tmp.c_str();
	}

	std::vector<KeyedHTMLElement> keys;
	if ( browserCtrl->getKeyedElements( keys ) ) {
		std::vector<KeyedHTMLElement>::iterator it = keys.begin();
		while ( it != keys.end() ) {
			updateElementForKey( it->second, it->first );
			++it;
		}
	}


	if ( browserCtrl->shouldUpdateDOMOnDocumentCompleted() ) {
		browserCtrl->updateDOMFromModel();
	} 
	else if ( browserCtrl->shouldUpdateModelOnDocumentCompleted() ) {
		browserCtrl->updateModelFromDOM();
	}

	
	browserCtrl->URLLoaded( &e );
	urlLoaded( browserCtrl );
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
	HRESULT result = E_NOTIMPL;

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


	if ( InternetCrackUrlW( s.c_str(), s.size(), 0, &components ) ) {
		if ( components.nScheme == INTERNET_SCHEME_RES ) {
			//check out resources dir first to see if we have anything
			Application* app = Application::getRunningInstance();
			if ( NULL != app ) {
				FilePath fp;
				String resDir = app->getResourceBundle()->getResourcesDirectory();
				
				String file;
				if ( components.dwUrlPathLength == 1 && components.lpszUrlPath[0] == '/' ) {
					file += components.lpszHostName;
				}
				else {
					String binary = components.lpszHostName;
					
					FilePath ourExe = app->getFileName();
					file = components.lpszUrlPath;
					
					FilePath binFp = binary;
					if ( binFp.getPathName().empty() && binFp.getBaseName() == ourExe.getBaseName() ) {
						if ( System::getCurrentWorkingDirectory() == ourExe.getPathName() ) {
							binary = System::getCurrentWorkingDirectory() + components.lpszHostName;	
						}
					}
					else if ( binFp.getPathName().empty() ) {
						binary = "";
						file = "";
					}			
					
					
					if ( !binary.empty() ) {
						resDir = System::findResourceDirectoryForExecutable( FilePath( binary ) );
						
						resDir.erase( resDir.size()-1, 1 );
					}
				}
				
				fp = resDir + file;
				
				if ( File::exists( fp ) ) {
					String newResFile = "file://";
					newResFile += fp;
					
					*ppchURLOut = (OLECHAR*) CoTaskMemAlloc( newResFile.size_in_bytes() + 2 );
					
					newResFile.copy( *ppchURLOut, newResFile.size() );
					
					(*ppchURLOut)[ newResFile.size() ] = 0;
					result = S_OK;
				}
			}
		}
	}

	delete [] scheme;
	delete [] host;
	delete [] user;
	delete [] pwd;
	delete [] url;
	delete [] extra;




	return result;
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

STDMETHODIMP Win32HTMLBrowser::TranslateAccelerator( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID )
{
	if ( this->peerControl_->keepsTabKey() ) {
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

bool Win32HTMLBrowser::processMessageFilter( MSG* msg )
{
	if ( msg->message == WM_KEYFIRST && msg->message < WM_KEYLAST ) {
		if ( IsChild( hwnd_, msg->hwnd ) ) {

			if ( inPlaceObj_ ) {
				if ( S_OK == inPlaceObj_->TranslateAccelerator( msg ) ) {
					return true;
				}
			}

			if ( msg->hwnd == browserHwnd_ ) {
				handleBrowserMessages( msg );
			}
		}
	}
	return false;
}

void Win32HTMLBrowser::handleBrowserMessages( MSG* msg )
{

}

void Win32HTMLBrowser::updateElementForKey( const VariantData& key, const String& elementName )
{
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


						IHTMLInputElementPtr input = com_cast( *f->getPeer() );

						if ( input ) {
							String name = elementName + "_onchange";
							
							HTMLEventHandler* htmlHandler = getElementEventHandler(name);
							if ( NULL == htmlHandler ) {
								htmlHandler = new HTMLEventHandler();
								eventHandlers_[name] = htmlHandler;
							}
							
							htmlHandler->eventSource = peerControl_;
							htmlHandler->handler = (EventHandler*) peerControl_->getCallback( "HTMLBrowserControl::inputElementChanged" ) ;
							htmlHandler->elementID = elementName;
							
							variant_t e;
							com_ptr<IDispatch> idisp = htmlHandler;
							
							e = idisp;							
							input->put_onchange( e.in() );
							break;
						}						
					}
				}
			}			
		}
	}	
}

/**
$Id$
*/
