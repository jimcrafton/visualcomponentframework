//AbstractWin32Component.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"
#include "vcf/GraphicsKit/ContextPeer.h"
#include "vcf/ApplicationKit/Win32Object.h"
#include "vcf/ApplicationKit/AbstractWin32Component.h"
#include "vcf/ApplicationKit/Win32ToolKit.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"
#include "vcf/GraphicsKit/Win32FontManager.h"
#include "vcf/ApplicationKit/Scrollable.h"
#include "vcf/ApplicationKit/ScrollPeer.h"
#include "vcf/ApplicationKit/Win32ScrollPeer.h"
#include "vcf/FoundationKit/Win32Peer.h"
#include "vcf/GraphicsKit/Win32Font.h"
#include "vcf/ApplicationKit/CursorPeer.h"

#include "thirdparty/win32/Microsoft/htmlhelp.h"


#ifdef VCF_WIN32CE
#else
#include "vcf/GraphicsKit/Win32VisualStylesWrapper.h"
#endif



#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/GraphicsKit/Win32Image.h"


using namespace VCF;

using namespace VCFWin32;



AbstractWin32Component::AbstractWin32Component():
	memCtx_(NULL),
	mouseEnteredControl_(false),	
	memDCState_(0),
	destroyed_(false),
	canProcessMessages_(false),
	cachedMessages_(NULL)
{
	init();
	setPeerControl( NULL );
}

AbstractWin32Component::AbstractWin32Component( Control* component ):
	memCtx_(NULL),
	mouseEnteredControl_(false),	
	memDCState_(0),
	destroyed_(false),
	canProcessMessages_(false),
	cachedMessages_(NULL)
{
	init();
	setPeerControl( component );
}

void AbstractWin32Component::create( Control* owningControl )
{
	setPeerControl( owningControl );
}

void AbstractWin32Component::destroyControl()
{
	if ( !destroyed_ ) {		
		if ( NULL != hwnd_ ){		
			if ( IsWindow( hwnd_ ) ) {
				BOOL err = ::DestroyWindow( hwnd_ );
				if ( !err )  {
					//throw RuntimeException( MAKE_ERROR_MSG_2("DestroyWindow failed") );
					err = GetLastError();
				}
			}
			else {
				destroyWindowHandle();
			}
		}
	}
	
	if ( !destroyed_ ) {
		destroyWindowHandle();
		destroyed_ = true;
	}
	
	hwnd_ = NULL;
	wndProc_ = NULL;
	defaultWndProc_ = NULL;
	peerControl_ = NULL;


	if ( NULL != memCtx_ ) {
		delete memCtx_;
	}

	memCtx_ = NULL;
}

AbstractWin32Component::~AbstractWin32Component()
{

}

void AbstractWin32Component::init()
{
//	memDC_ = NULL;
	mouseEnteredControl_ = false;

	cachedMessages_ = new std::vector<MSG>();	
}

OSHandleID AbstractWin32Component::getHandleID()
{
	OSHandleID result = 0;
	result = (OSHandleID)hwnd_;
	return result;
}

VCF::String AbstractWin32Component::getText()
{
	VCF::String result;

	if ( System::isUnicodeEnabled() ) {
		int size = ::GetWindowTextLengthW( hwnd_ )+1;
		if ( size > 1 ) {
			VCFChar* tmpText = new VCFChar[size];
			memset( tmpText, 0, size*sizeof(VCFChar) );
			::GetWindowTextW( hwnd_, tmpText, size );
			result = tmpText;
			delete [] tmpText;
		}
	}
	else {
		int size = ::GetWindowTextLengthA( hwnd_ )+1;
		if ( size > 1 ) {
			char* tmpText = new char[size];
			memset( tmpText, 0, size*sizeof(char) );
			::GetWindowTextA( hwnd_, tmpText, size );
			result = tmpText;
			delete [] tmpText;
		}
	}

	return result;
}

void AbstractWin32Component::setText( const VCF::String& text )
{
	if ( System::isUnicodeEnabled() ) {
		const VCFChar* chars = text.c_str();
		::SetWindowTextW( hwnd_, chars );
	}
	else {
		::SetWindowTextA( hwnd_, text.ansi_c_str() );
	}

}

void AbstractWin32Component::setBounds( VCF::Rect* rect )
{	
	if ( !peerControl_->hasChildren() ) {
		::MoveWindow( hwnd_, (int)rect->left_, (int)rect->top_, rect->getWidth(), (int)rect->getHeight(), TRUE );
	}
	else {
		::SetWindowPos( hwnd_, NULL, (int)rect->left_, (int)rect->top_,
			          (int)rect->getWidth(), (int)rect->getHeight(), SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER );
	}	
}



bool AbstractWin32Component::beginSetBounds( const uint32& numberOfChildren )
{
	
	//JEC - I commented this out to simplify/speed up some resize/repaint issues
	bool result = true;

	
	return result;
}

void AbstractWin32Component::endSetBounds()
{
	
}

VCF::Rect AbstractWin32Component::getBounds()
{
	VCF::Rect result;
	RECT r;
 	::GetWindowRect( hwnd_, &r );
#ifdef VCF_WIN32CE
	LONG_PTR style = ::GetWindowLong( hwnd_, GWL_STYLE );
#else
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
#endif
	HWND parent = ::GetParent( hwnd_ );

	if ( style & WS_CHILD ){
		POINT pt = {0,0};
		pt.x = r.left;
		pt.y = r.top;
		::ScreenToClient( parent, &pt );
		r.left = pt.x;
		r.top = pt.y;

		pt.x = r.right;
		pt.y = r.bottom;
		::ScreenToClient( parent, &pt );

		r.right = pt.x;
		r.bottom = pt.y;

		result.setRect( r.left, r.top, r.right, r.bottom );

	}
	else{
		result.setRect( r.left, r.top, r.right, r.bottom );
	}
	return result;
}

void AbstractWin32Component::setVisible( const bool& visible )
{
	if ( (peerControl_->isDesigning()) && (NULL == GetParent(hwnd_)) ) {
		return; //do nothing! can't show the control till it's parented
	}

	if ( true == visible ){
		::ShowWindow( hwnd_, SW_SHOW );
	}
	else{
		::ShowWindow( hwnd_, SW_HIDE );
	}
}

bool AbstractWin32Component::getVisible()
{
	bool result = false;
	
#ifdef VCF_WIN32CE
	LONG_PTR style = ::GetWindowLong( hwnd_, GWL_STYLE );
#else
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
#endif

	result =  (style & WS_VISIBLE ) != 0;
	return result;
}

VCF::Control* AbstractWin32Component::getControl()
{
	return peerControl_;
}

void AbstractWin32Component::setControl( VCF::Control* component )
{
	setPeerControl( component );
}

void AbstractWin32Component::setParent( VCF::Control* parent )
{
	VCF_ASSERT(NULL != hwnd_);
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND dummyParent = toolkit->getDummyParent();

	if ( NULL == parent ) {
		::ShowWindow( hwnd_, SW_HIDE );
		::SetParent( hwnd_, dummyParent );
	}
	else {
		VCF::ControlPeer* parentPeer = parent->getPeer();
		
		if ( NULL == dynamic_cast<Frame*>(peerControl_) ){
			HWND wndParent = (HWND)parentPeer->getHandleID();			
			
			if ( NULL == wndParent ){
				//throw exception !!!
			}
			
			HWND currentParent = ::GetParent( hwnd_ );

			::SetParent( hwnd_, wndParent );

			if ( currentParent == dummyParent ) {
#ifdef VCF_WIN32CE
				::ShowWindow( hwnd_, SW_SHOWNORMAL );
#else				
				::ShowWindow( hwnd_, SW_NORMAL );
#endif
			}		
		}
	}
}

VCF::Control* AbstractWin32Component::getParent()
{
	return NULL;
}

bool AbstractWin32Component::isFocused()
{
	VCF_ASSERT(NULL != hwnd_);
	HWND focusedHandle = ::GetFocus();
	bool result = (NULL != focusedHandle) && (focusedHandle == hwnd_);
	return result;
}

void AbstractWin32Component::setFocused()
{
	VCF_ASSERT(NULL != hwnd_);
	::SetFocus( hwnd_ );
}

bool AbstractWin32Component::isEnabled()
{
	VCF_ASSERT(NULL != hwnd_);
	return (::IsWindowEnabled( hwnd_ ) != 0);
}

void AbstractWin32Component::setEnabled( const bool& enabled )
{
	VCF_ASSERT(NULL != hwnd_);
	::EnableWindow( hwnd_, enabled );
}

void AbstractWin32Component::setFont( Font* font )
{
	VCF_ASSERT(NULL != hwnd_);
	if ( NULL != font ){
		Win32Font* win32FontPeer = NULL;
		FontPeer* fontPeer = font->getFontPeer();
		win32FontPeer = dynamic_cast<Win32Font*>(fontPeer );
		if ( NULL != win32FontPeer ){
			HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( win32FontPeer );
			if ( NULL != fontHandle ){
				::SendMessage( hwnd_, WM_SETFONT, (WPARAM)fontHandle, MAKELPARAM(TRUE, 0) );
				
			}
		}
		else {
			//what the hell is a non Win32Font doing here !!!! throw exception !!!!!
		}
	}
}

void AbstractWin32Component::prepForDoubleBufferPaint( HDC wmPaintDC, const Rect& paintRect )
{
	if ( peerControl_->isDoubleBuffered() && 
				!paintRect.isNull() && 
				!paintRect.isEmpty() ) {


		if ( NULL != memCtx_ ) {
			delete memCtx_;
		}
		memCtx_ = new GraphicsContext( paintRect.getWidth(), paintRect.getHeight() );

		memCtx_->setViewableBounds( paintRect );

		if ( peerControl_->isUsingRenderBuffer() ) {
			memCtx_->setAntiAliasingOn( true );
		}
	}
}

HDC AbstractWin32Component::doControlPaint( HDC paintDC, RECT paintRect, RECT* exclusionRect, int whatToPaint  )
{
	HDC result = NULL;

	if ( !peerControl_->isDestroying() ) {	
		Rect viewableRect(paintRect.left, paintRect.top,
			paintRect.right, paintRect.bottom );

		if ( peerControl_->isDoubleBuffered() && 
				!viewableRect.isNull() && 
				!viewableRect.isEmpty() ) {

			prepForDoubleBufferPaint( paintDC, viewableRect );
			GraphicsContext* ctx = memCtx_;

			Rect dirtyRect( paintRect.left,paintRect.top,paintRect.right,paintRect.bottom);
			
			// changes the origin of the paint coordinates, by specifying which
			// point of the device context points to the origin of the window.

			ctx->setOrigin( -paintRect.left, -paintRect.top );
			
			ctx->setCurrentFont( peerControl_->getFont() );
			//Font* font = ctx->getCurrentFont();
			//font->setPointSize( font->getPointSize() );

			// save the state of Graphics control so to be fully restored after the paint.
			int gcs = ctx->saveState();

			switch( whatToPaint ) {
				case cpBorderOnly : {
					peerControl_->paintBorder( ctx );
				}
				break;

				case cpControlOnly : {

					peerControl_->internal_beforePaint( ctx );

					peerControl_->paint( ctx );

					peerControl_->internal_afterPaint( ctx );
				}
				break;

				case cpBorderAndControl : {
					peerControl_->paintBorder( ctx );
					
					peerControl_->internal_beforePaint( ctx );

					peerControl_->paint( ctx );

					peerControl_->internal_afterPaint( ctx );
				}
				break;
			}

			ctx->restoreState( gcs );

			//reset back to original origin

			ctx->setOrigin( -paintRect.left, -paintRect.top );

			//::SetViewportOrgEx( memDC_, -paintRect.left, -paintRect.top, &oldOrg );
			result = (HDC)ctx->getPeer()->getContextID();
			ctx->setViewableBounds( Rect( 0,0,0,0 ) );
		
		}
		else if ( !viewableRect.isNull() && !viewableRect.isEmpty() ) {
			GraphicsContext gc((OSHandleID)paintDC);
			GraphicsContext* ctx = &gc;
			ctx->setViewableBounds( viewableRect );

			/**
			* we prevents the owning control of the context to alter
			* the HDC and the viewport, as this is done here using 
			* the DC given by the system with the message itself.
			*/

			if ( NULL != exclusionRect ) {
				ExcludeClipRect( paintDC, exclusionRect->left, exclusionRect->top,
								exclusionRect->right, exclusionRect->bottom );
			}
			
			int gcs = ctx->saveState();

			switch( whatToPaint ) {
				case cpBorderOnly : {
					peerControl_->paintBorder( ctx );
				}
				break;

				case cpControlOnly : {
					peerControl_->internal_beforePaint( ctx );

					peerControl_->paint( ctx );

					peerControl_->internal_afterPaint( ctx );
				}
				break;

				case cpBorderAndControl : {
					peerControl_->paintBorder( ctx );
					
					peerControl_->internal_beforePaint( ctx );

					peerControl_->paint( ctx );

					peerControl_->internal_afterPaint( ctx );
				}
				break;
			}

			ctx->restoreState( gcs );
			
			result = paintDC;

			ctx->setViewableBounds( Rect( 0,0,0,0 ) );
		}
	}

	return result;
}

void AbstractWin32Component::updatePaintDC( HDC paintDC, RECT paintRect, RECT* exclusionRect )
{	

	if ( !peerControl_->isDestroying() ) {
		if ( peerControl_->isDoubleBuffered() 
			 &&  ((paintRect.right-paintRect.left) != 0)
			 &&  ((paintRect.bottom-paintRect.top) != 0) ) {
			VCF_ASSERT( memCtx_ != NULL );
			//VCF_ASSERT( originalMemBMP_ != 0 );
			//VCF_ASSERT( memBMP_ != 0 );

			if ( NULL != exclusionRect ) {
				ExcludeClipRect( paintDC, exclusionRect->left, exclusionRect->top,
									exclusionRect->right, exclusionRect->bottom );
			}

			HDC memDC = (HDC) memCtx_->getPeer()->getContextID();
			/**
			* does the final part of the double buffering mechanism
			* copies the memory context into the device context
			* given by the system with the paint message itself.
			*/
			int err = ::BitBlt( paintDC, paintRect.left, paintRect.top,
					  paintRect.right - paintRect.left,
					  paintRect.bottom - paintRect.top,
					  memDC, paintRect.left, paintRect.top, SRCCOPY );
			
			if ( !err ) {
				err = GetLastError();
				StringUtils::trace( Format("error in BitBlt during drawing of double buffered Comp: error code=%d\n") %	
											err );
			}

		}
	}
}


Control* getActualHelpControl( Control* control, Point* pt ) 
{
	Control* result = NULL;
	
	Container* container = control->getContainer();
	if ( NULL != container ) {
		Enumerator<Control*>* children = container->getChildren();
		bool found = false;
		while ( children->hasMoreElements() && !found ) {
			Control* child = children->nextElement();
			if ( child->isLightWeight() ) {
				Rect bounds = child->getBounds();
				if ( bounds.containsPt( pt ) ) {
					Point tmpPt = *pt;
					child->translateToLocal( &tmpPt );
					result = getActualHelpControl( child, &tmpPt );
					if ( NULL != result  ) {
						found = true;//quit the loop
					}
				}
			}
		}
		if ( !found && (NULL == result) ) {
			result = control;
		}
	}
	else {
		result = control;
	}
	
	return result;
}


bool AbstractWin32Component::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	
	bool result = false;	

	/**
	JC
	This check is here to prevent us from processing ANY messages before we are ready to.
	We aren't erady until we have recv'd a VCF_CONTROL_CREATE message. This prevents
	exceptions thrown in a control constructor from going awry. What happens is that an
	exception thrown in the contructor will immediately exit the constructor and then
	the classes destructor is then called. This causes problems with the pointer
	and just general ugliness, so we put this check in here to prevent weird things from
	happening.
	*/
	if ( !canProcessMessages_ && (VCF_CONTROL_CREATE != message) ) {
		
		if ( (message == WM_SIZE)
			|| (message == WM_MOVE)
			|| (message == WM_ERASEBKGND)
			|| (message == WM_SETFOCUS)
			|| (message == WM_KILLFOCUS) 
			)  {
			
			MSG m;
			memset(&m,0,sizeof(m));
			m.hwnd = hwnd_;
			m.lParam = lParam;
			m.message = message;
			m.wParam = wParam;
			cachedMessages_->push_back( m );
		}

		/**
		We don't want WM_ERASEBKGND to go to ::DefWindowProc if we are not
		processing messages or registered yet. If it does, Windows will do an erase 
		where this control will be, (but before this control is to be painted), and 
		we will get a flicker effect.
		*/
		if( message == WM_ERASEBKGND || message == WM_SETFOCUS || message == WM_KILLFOCUS )
		{
			wndProcResult = 0;			
			return true;
		}
		else{
			return result;
		}
	}

	Win32MSG msg( hwnd_, message, wParam, lParam, peerControl_ );

	Event* event = UIToolkit::createEventFromNativeOSEventData( &msg );

	switch ( message ) {
		case VCF_CONTROL_CREATE : {
			canProcessMessages_ = true;

			peerControl_->handleEvent( event );


			if ( !cachedMessages_->empty() ) {
				std::vector<MSG>::iterator it = cachedMessages_->begin();
				while ( it != cachedMessages_->end() ) {
					MSG& m = *it;
					::SendMessage( m.hwnd, m.message, m.wParam, m.lParam );
					it++;
				}
			}

			delete cachedMessages_;

			/*
			Rect r = peerControl_->getBounds();

			peerControl_->setBounds( &r );
			Container* c = peerControl_->getContainer();
			if ( NULL != c ) {
				c->resizeChildren(NULL);
			}
			*/
		}
		break;

		case WM_ERASEBKGND :{
			wndProcResult = 0;
			result = true;
		}
		break;

		case WM_CTLCOLOREDIT : case WM_CTLCOLORBTN: case WM_CTLCOLORLISTBOX: {
			if ( !peerControl_->isDestroying() ) {
				HWND hwndCtl = (HWND) lParam; // handle to static control
				if ( hwndCtl != hwnd_ ) {
					Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
					if ( NULL != win32Obj ){
						win32Obj->handleEventMessages( message, wParam, lParam, wndProcResult );
						result = true;
					}
				}
			}
		}
		break;

		case  WM_SETFOCUS : {
/*			
			HWND hwndLoseFocus = (HWND) wParam;
			Win32Object* obj = Win32Object::getWin32ObjectFromHWND( hwndLoseFocus );
			if ( NULL != obj ){

				StringUtils::trace( Format( "lost focus: %s @ %p\n" ) % obj->getPeerControl()->getClassName() % obj->getPeerControl() );

			}
*/			
			if ( NULL != event && (!peerControl_->isDestroying()) ) {
				peerControl_->handleEvent( event );
			}
		}
		break;

		case  WM_KILLFOCUS : {
/*			
			HWND hwndGetFocus = (HWND) wParam;
			Win32Object* obj = Win32Object::getWin32ObjectFromHWND( hwndGetFocus );
			if ( NULL != obj ){

				StringUtils::trace( Format( "gained focus: %s @ %p\n" ) % obj->getPeerControl()->getClassName() % obj->getPeerControl() );

			}
*/			
			
			if ( NULL != event && (!peerControl_->isDestroying()) ) {
				peerControl_->handleEvent( event );
			}
		}
		break;

		case WM_COPYDATA: {
			Application* app = Application::getRunningInstance();
			if ( NULL != app ){
				Win32MSG msg( hwnd_, message, wParam, lParam, peerControl_ );
				Event e(peerControl_) ;
				e.setUserData( &msg );
				app->onOSNativeEvent( &e );
			}
		}
		break;
#ifndef VCF_WIN32CE
		case WM_HELP : {
			HELPINFO* helpInfo = (HELPINFO*) lParam;

			
			StringUtils::trace( Format("hwnd: %p, ctx: %d, type %d, handle %p, id: %d, x %d, y %d\n") % 
						hwnd_ %
						helpInfo->dwContextId % helpInfo->iContextType %
						helpInfo->hItemHandle % helpInfo->iCtrlId %
						helpInfo->MousePos.x % helpInfo->MousePos.y );


			POINT pt = helpInfo->MousePos;
			::ScreenToClient( hwnd_, &pt );
			Point tmp(pt.x,pt.y);

			

			Control* control = getActualHelpControl( peerControl_, &tmp );
			UIToolkit::displayContextHelpForControl( control );

			Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();
			toolkit->setWhatsThisHelpActive( false );

			wndProcResult = 1;
			result = true;
		}
		break;
#endif

		case WM_PAINT:{
			if ( true == isCreated() ){
				//StringUtils::trace( "AbstractWin32Component::WM_PAINT\n" );
				if ( !peerControl_->isDestroying() ) {					
					if( !GetUpdateRect( hwnd_, NULL, FALSE ) ){
						wndProcResult = 0;
						result = true;
						return result;
					}

					PAINTSTRUCT ps;
					HDC contextID = 0;
					contextID = ::BeginPaint( hwnd_, &ps);

					doControlPaint( contextID, ps.rcPaint, NULL, cpBorderAndControl );
					updatePaintDC( contextID, ps.rcPaint, NULL );

					::EndPaint( hwnd_, &ps);
				}
			}

			wndProcResult = 1;
			result = true;
		}
		break;

		case WM_DESTROY: {
			VCF_ASSERT( !destroyed_ );
			
			if ( isCreated() && (NULL != event) && (NULL != peerControl_) ) {
				if ( peerControl_->isNormal() || peerControl_->isDestroying() ) {
					peerControl_->handleEvent( event );
				}
				else {
					StringUtils::trace( "Trying to destroy component in weird state!\n" );
				}
			}			

			destroyWindowHandle();

			wndProcResult = 0;
			result = false;
		}
		break;

		case WM_MOUSEMOVE: {
			if ( peerControl_->isNormal() ) {
				//result = defaultWndProcedure( message, wParam, lParam );
			}

			if ( false == mouseEnteredControl_ ) {
#ifdef VCF_WIN32CE
#else
				TRACKMOUSEEVENT trackmouseEvent = {0,0,0,0};
				trackmouseEvent.cbSize = sizeof(trackmouseEvent);
				trackmouseEvent.dwFlags = TME_LEAVE;
				trackmouseEvent.hwndTrack = hwnd_;
				trackmouseEvent.dwHoverTime = HOVER_DEFAULT;

				if ( _TrackMouseEvent( &trackmouseEvent ) ) {
					event->setType( Control::MOUSE_ENTERED );
					peerControl_->handleEvent( event );

					event->setType( Control::MOUSE_MOVE );
				}
#endif
			}

			mouseEnteredControl_ = true;

			peerControl_->handleEvent( event );

		}
		break;

#ifdef VCF_WIN32CE
#else
		case WM_MOUSELEAVE: {
			if ( peerControl_->isNormal() ) {
				//result = defaultWndProcedure( message, wParam, lParam );
			}

			mouseEnteredControl_ = false;

			if ( NULL != event ) {
				peerControl_->handleEvent( event );
			}

		}
		break;
#endif


		case WM_DRAWITEM : {
			
			UINT idCtl = (UINT) wParam;
			DRAWITEMSTRUCT* drawItemStruct = (DRAWITEMSTRUCT*) lParam;

			if ( (!peerControl_->isDestroying()) && (0 == idCtl)
					&& (ODT_MENU == drawItemStruct->CtlType) ) {
				// we have received a draw item for a menu item
				MenuItem* foundItem = Win32MenuItem::getMenuItemFromID( drawItemStruct->itemID );
				if ( NULL != foundItem ) {
					foundItem->setSelected( (drawItemStruct->itemState & ODS_SELECTED) != 0 );

					//foundItem->setChecked( (drawItemStruct->itemState & ODS_CHECKED) != 0 );

					//foundItem->setEnabled( (drawItemStruct->itemState & ODS_CHECKED) != 0 );

					foundItem->setHighlighted( (drawItemStruct->itemState & ODS_SELECTED) != 0 );

					if ( foundItem->canPaint() ) {

						Win32MenuItem* itemPeer = (Win32MenuItem*)foundItem->getPeer();

						GraphicsContext gc( (OSHandleID)drawItemStruct->hDC );

						//itemPeer->drawDefaultMenuItem( &gc, idCtl, *drawItemStruct );						
						
						Rect menuRect(drawItemStruct->rcItem.left, drawItemStruct->rcItem.top,
										drawItemStruct->rcItem.right, drawItemStruct->rcItem.bottom);						

						foundItem->paint( &gc, &menuRect );

						gc.getPeer()->setContextID(0);
						
						wndProcResult = TRUE;
						result = true;
					}
				}
			}
			else {
				if ( (!peerControl_->isDestroying()) && (ODT_BUTTON == drawItemStruct->CtlType) ) {
					HWND hwndCtl = drawItemStruct->hwndItem;
					Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
					if ( NULL != win32Obj ){						
						win32Obj->handleEventMessages( WM_DRAWITEM, wParam, lParam, wndProcResult );
						result = true;
					}
				}
				else {
					//result = defaultWndProcedure( message, wParam, lParam );
				}
			}
		}
		break;

		case WM_MEASUREITEM : {

			UINT idCtl = (UINT) wParam;
			MEASUREITEMSTRUCT* measureInfo = (MEASUREITEMSTRUCT*) lParam;
			if ( (!peerControl_->isDestroying()) && (0 == idCtl)
					&& (ODT_MENU == measureInfo->CtlType) ) {

				// we have received a draw item for a menu item
				MenuItem* foundItem = Win32MenuItem::getMenuItemFromID( measureInfo->itemID );
				if ( NULL != foundItem ) {

					if ( foundItem->canPaint() ) {
						result = TRUE;
						Rect bounds = foundItem->getBounds();
						bool needsBounds = false;
						if ( !bounds.isNull() ) {
							needsBounds = ((bounds.getHeight() <= 0.0) && (bounds.getWidth() <= 0.0));
						}
						else {
							needsBounds = true;
						}
						if ( needsBounds ) {
							Win32MenuItem* peer = (Win32MenuItem*)foundItem->getPeer();
							peer->fillInMeasureItemInfo( *measureInfo );
							//

						}
						else {
							measureInfo->itemHeight = (int32)bounds.getHeight();
							measureInfo->itemWidth = (int32)bounds.getWidth();
						}
					}
				}
			}
			else {
				//result = defaultWndProcedure( message, wParam, lParam );
			}
		}
		break;

#ifdef VCF_WIN32CE
#else
		case WM_MENUSELECT : {
			if ( !peerControl_->isDestroying() ) {
				UINT uItem = (UINT) LOWORD(wParam);
				UINT fuFlags = (UINT) HIWORD(wParam);
				HMENU hmenuPopup = (HMENU) lParam;
				if ( (MF_MOUSESELECT & fuFlags) != 0 ) {
					MenuItem* foundItem = Win32MenuItem::getMenuItemFromID( uItem );
					if ( NULL != foundItem ) {
						//StringUtils::trace( "MF_MOUSESELECT over item \"" + foundItem->getCaption() + "\"\n" );
						foundItem->setSelected( true );
						result = 0;
					}
				}
				else {
					//result = defaultWndProcedure( message, wParam, lParam );
				}
			}
		}
		break;
#endif
		case WM_INITMENUPOPUP : {
			if ( !peerControl_->isDestroying() ) {
				HMENU hmenuPopup = (HMENU) wParam;//thisis the menu handle of the menu popuping up or dropping down
				if ( GetMenuItemCount( hmenuPopup ) > 0 ) {
					//UINT Pos = (UINT) LOWORD(lParam);
					UINT uPos = (UINT) LOWORD(lParam);
					//get the first item
					MENUITEMINFO info;
					memset(&info,0,sizeof(info));
					info.cbSize = sizeof(MENUITEMINFO);
					info.fMask = MIIM_ID;


					uint32 id = GetMenuItemID( hmenuPopup, uPos );
					if ( id == 0xFFFFFFFF ) {
						//hmmm try again with 0 - cause that also works
						//this makes no friggin sense whatsoever....
						GetMenuItemInfo( hmenuPopup, uPos, TRUE, &info );

						id = GetMenuItemID( hmenuPopup, 0 );
					}
					MenuItem* parent = NULL;
					MenuItem* foundItem = NULL;
					if ( id != 0xFFFFFFFF ) {
						foundItem = Win32MenuItem::getMenuItemFromID( id );
						if ( NULL != foundItem ) {
							parent = foundItem->getParent();
						}
					}
					else {
						parent = Win32MenuItem::getMenuItemFromHandle( hmenuPopup );
					}
					if ( NULL != parent ) {
						parent->update();
						Enumerator<MenuItem*>* menuItems = parent->getChildren();
						while ( menuItems->hasMoreElements() ) {
							MenuItem* child = menuItems->nextElement();
							child->update();
						}
						result = 0;
					}
				}
			}
		}
		break;

		case WM_NOTIFY : {
			result = true;
			wndProcResult = defaultWndProcedure( message, wParam, lParam );
			if ( !peerControl_->isDestroying() ) {
				NMHDR* notificationHdr = (LPNMHDR)lParam;
				Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( notificationHdr->hwndFrom );
				if ( NULL != win32Obj ){
					win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, wndProcResult );
				}
			}
		}
		break;

#ifdef WM_MOUSEWHEEL
		case WM_MOUSEWHEEL : {
			if ( NULL != peerControl_ ) {
				Scrollable* scrollable = peerControl_->getScrollable();

				if ( (!peerControl_->isDestroying()) && (NULL != scrollable) ) {
					short fwKeys = LOWORD(wParam);    // key flags
					short zDelta = (short) HIWORD(wParam);    // wheel rotation
					short xPos = (short) LOWORD(lParam);    // horizontal position of pointer
					short yPos = (short) HIWORD(lParam);    // vertical position of pointer

                    Rect clientBoundsRect = peerControl_->getClientBounds();
                    if ( scrollable->hasVerticalScrollBar() && (scrollable->getVirtualViewHeight() > clientBoundsRect.getHeight() ) ) {
						int pos = 0;
						//StringUtils::trace( Format( "zDelta: %d\n" ) % zDelta );
						
						double actualViewHeight = clientBoundsRect.getHeight();
						if ( scrollable->isHorizontalScrollbarVisible() ) {
							actualViewHeight -= scrollable->getHorizontalScrollbarHeight();
						}
						
						if ( zDelta < 0 ) {
							pos = VCF::minVal<int32>((scrollable->getVerticalPosition() + 10 ),
												abs((int32)(scrollable->getVirtualViewHeight() - actualViewHeight )) );
						}
						else if ( zDelta > 0 ) {
							pos = VCF::maxVal<int32>((scrollable->getVerticalPosition() - 10 ), 0 );
						}

						scrollable->setVerticalPosition( pos );

					}
					else if ( scrollable->hasHorizontalScrollBar() && (scrollable->getVirtualViewWidth() > clientBoundsRect.getWidth() ) ) {
						int pos = 0;
						//StringUtils::trace( Format( "zDelta: %d\n" ) % zDelta );
						
						double actualViewWidth = clientBoundsRect.getWidth();
						if ( scrollable->isVerticalScrollbarVisible() ) {
							actualViewWidth -= scrollable->getVerticalScrollbarWidth();
						}
						
						if ( zDelta < 0 ) {
							pos = VCF::minVal<int32>((scrollable->getHorizontalPosition() + 10),
												abs((int32)(scrollable->getVirtualViewWidth() - actualViewWidth )) );
						}
						else if ( zDelta > 0 ) {
							pos = VCF::maxVal<int32>((scrollable->getHorizontalPosition() - 10), 0 );
						}

						scrollable->setHorizontalPosition( pos );
					}

				}

				if (!peerControl_->isDestroying())
				{
					event->setType( Control::MOUSE_WHEEL );
					peerControl_->handleEvent( event );
				}
			}
		}
		break;
#endif
		case WM_VSCROLL : {
			result = false;
			if ( NULL != peerControl_ ) {
				if ( !peerControl_->isDestroying() ) {

					HWND hwndScrollBar = (HWND) lParam;

					Scrollable* scrollable = peerControl_->getScrollable();
					//if it's null then check for children
					if ( NULL == scrollable ) {
						Control* scrollControl = Win32ScrollPeer::getScrollableControlFromHWnd( hwndScrollBar );
						if ( NULL != scrollControl ) {
							scrollable = scrollControl->getScrollable();
						}
					}
					if ( NULL != scrollable ) {
						int nScrollCode = (int) LOWORD(wParam); // scroll bar value
						short int nPos = (short int) HIWORD(wParam);  // scroll box position
						// handle to scroll bar
						//use this for 32bit scroll positions
						SCROLLINFO si;
						memset( &si, 0, sizeof(si) );
						si.cbSize = sizeof(si);
						si.fMask = SIF_ALL;	// SIF_PAGE is not enough: si.nMax would be = 0
						GetScrollInfo( hwndScrollBar, SB_CTL, &si );
						double height = peerControl_->getClientBounds().getHeight();

						switch ( nScrollCode ) {

							case SB_THUMBPOSITION : case SB_THUMBTRACK : {

								int pos = si.nTrackPos;

								if ( scrollable->getDiscreteVertScroll() ) {
									double step = scrollable->getVirtualViewVertStep();
									if ( 0 != step ) {
										double n = pos / step;
										pos = (((int)ceil(n)) * step);
									}
								}

								scrollable->setVerticalPosition( pos );

							}
							break;

							case SB_LINEDOWN: {
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getVerticalPosition() == p );
								double step = scrollable->getVirtualViewVertStep();
								int pos = p + step;
								if ( scrollable->getDiscreteVertScroll() ) {
									if ( 0 != step ) {
										double n = p / step;
										pos = (((int)ceil(n)) * step) + step;
									}
								}

								//pos = min( pos, abs((int32)(scrollable->getVirtualViewHeight() - height)) );
								pos = VCF::minVal ( pos, si.nMax );
								//si.nPos += step;
								//si.nPos = min ( si.nPos, si.nMax );
								//pos = si.nPos;
								scrollable->setVerticalPosition( pos );

							}
							break;

							case SB_LINEUP: {
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getVerticalPosition() == p );
								double step = scrollable->getVirtualViewVertStep();
								int pos = p - step;
								if ( scrollable->getDiscreteVertScroll() ) {
									if ( 0 != step ) {
										double n = p / step;
										pos = (((int)ceil(n)) * step) - step;
									}
								}

								//pos = max( pos, 0 );
								pos = VCF::maxVal ( pos, si.nMin );
								//si.nPos -= step;
								//si.nPos = max ( si.nPos, si.nMin );
								//pos = si.nPos;
								scrollable->setVerticalPosition( pos );

							}
							break;

							case SB_PAGEDOWN: {
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getVerticalPosition() == p );
								int pos = p + si.nPage;
								if ( scrollable->getDiscreteVertScroll() ) {
									double step = scrollable->getVirtualViewVertStep();
									if ( 0 != step ) {
										double n = (p + si.nPage) / step;
										pos = ((int)ceil(n)) * step;
									}
								}

								//pos = min( pos, abs((int32)(scrollable->getVirtualViewHeight() - height)) );
								pos = VCF::minVal ( pos, si.nMax );
								scrollable->setVerticalPosition( pos );
							}
							break;

							case SB_PAGEUP: {
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getVerticalPosition() == p );
								int pos = p - si.nPage;
								if ( scrollable->getDiscreteVertScroll() ) {
									double step = scrollable->getVirtualViewVertStep();
									if ( 0 != step ) {
										double n = (p - si.nPage) / step;
										pos = ((int)ceil(n)) * step;
									}
								}

								//pos = max( pos, 0 );
								pos = VCF::maxVal( pos, si.nMin );
								scrollable->setVerticalPosition( pos );

							}
							break;
						}
					}
				}
			}
		}
		break;

		case WM_HSCROLL : {
			result = false;
			if ( NULL != peerControl_ ) {
				if ( !peerControl_->isDestroying() ) {

					HWND hwndScrollBar = (HWND) lParam;

					Scrollable* scrollable = peerControl_->getScrollable();
					//if it's null then check for children
					if ( NULL == scrollable ) {
						Control* scrollControl = Win32ScrollPeer::getScrollableControlFromHWnd( hwndScrollBar );
						if ( NULL != scrollControl ) {
							scrollable = scrollControl->getScrollable();
						}
					}
					if ( NULL != scrollable ) {
						int nScrollCode = (int) LOWORD(wParam); // scroll bar value
						short int nPos = (short int) HIWORD(wParam);  // scroll box position
						// handle to scroll bar
						//use this for 32bit scroll positions
						SCROLLINFO si;
						memset( &si, 0, sizeof(si) );
						si.cbSize = sizeof(si);
						si.fMask = SIF_ALL;	// SIF_POS | SIF_TRACKPOS | SIF_PAGE;	// SIF_PAGE is not enough: si.nMax would be = 0
						GetScrollInfo( hwndScrollBar, SB_CTL, &si );
						double width = peerControl_->getClientBounds().getWidth();

						switch ( nScrollCode ) {
							case SB_THUMBPOSITION : case SB_THUMBTRACK : {

								int pos = si.nTrackPos;

								if ( scrollable->getDiscreteHorzScroll() ) {
									double step = scrollable->getVirtualViewHorzStep();
									if ( 0 != step ) {
										double n = pos / step;
										pos = (((int)ceil(n)) * step);
									}
								}

								scrollable->setHorizontalPosition( pos );

							}
							break;

							case SB_LEFT : {

							}
							break;

							case SB_RIGHT : {

							}
							break;

							case SB_LINELEFT : {
								//copied from SB_LINEUP
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getHorizontalPosition() == p );
								double step = scrollable->getVirtualViewHorzStep();
								int pos = p - step;
								if ( scrollable->getDiscreteHorzScroll() ) {
									if ( 0 != step ) {
										double n = p / step;
										pos = (((int)ceil(n)) * step) - step;
									}
								}

								//pos = max( pos, 0 );
								pos = VCF::maxVal ( pos, si.nMin );
								//si.nPos -= step;
								//si.nPos = max ( si.nPos, si.nMin );
								//pos = si.nPos;
								scrollable->setHorizontalPosition( pos );

							}
							break;

							case SB_LINERIGHT : {
								//copied from SB_LINEDOWN
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getHorizontalPosition() == p );
								double step = scrollable->getVirtualViewHorzStep();
								int pos = p + step;
								if ( scrollable->getDiscreteHorzScroll() ) {
									if ( 0 != step ) {
										double n = p / step;
										pos = (((int)ceil(n)) * step) + step;
									}
								}

								//pos = min( pos, abs((int32)(scrollable->getVirtualViewWidth() - width)) );
								pos = VCF::minVal ( pos, si.nMax );
								//si.nPos += step;
								//si.nPos = min ( si.nPos, si.nMax );
								//pos = si.nPos;
								scrollable->setHorizontalPosition( pos );

							}
							break;

							case SB_PAGELEFT : {
								//copied from SB_PAGEUP
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getHorizontalPosition() == p );
								int pos = p - si.nPage;
								if ( scrollable->getDiscreteHorzScroll() ) {
									double step = scrollable->getVirtualViewHorzStep();
									if ( 0 != step ) {
										double n = (p - si.nPage) / step;
										pos = ((int)ceil(n)) * step;
									}
								}

								//pos = max( pos, 0 );
								pos = VCF::maxVal( pos, si.nMin );
								scrollable->setHorizontalPosition( pos );

							}
							break;

							case SB_PAGERIGHT : {
								//copied from SB_PAGEDOWN
								int p = si.nPos;
								//VCF_ASSERT( scrollable->getHorizontalPosition() == p );
								int pos = p + si.nPage;
								if ( scrollable->getDiscreteHorzScroll() ) {
									double step = scrollable->getVirtualViewHorzStep();
									if ( 0 != step ) {
										double n = (p + si.nPage) / step;
										pos = ((int)ceil(n)) * step;
									}
								}

								//pos = min( pos, abs((int32)(scrollable->getVirtualViewWidth() - width)) );
								pos = VCF::minVal ( pos, si.nMax );
								scrollable->setHorizontalPosition( pos );

							}
							break;

							case SB_ENDSCROLL : {

							}
							break;
						}
					}
				}
			}
		}
		break;

		case WM_COMMAND:{
			if ( !peerControl_->isDestroying() ) {
				UINT notifyCode = HIWORD(wParam);
				HWND hwndCtl = (HWND) lParam;
				Win32Object* win32Obj = NULL;
				if ( NULL != hwndCtl ){
					win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
				}
				if ( NULL != win32Obj ){
					if ( NULL != win32Obj ){
						win32Obj->handleEventMessages( notifyCode, wParam, lParam, wndProcResult );
					}
					else {
						StringUtils::trace( "win32Obj == NULL!\n" );
						UINT wID = LOWORD(wParam);
						char tmp2[256];
						memset( tmp2, 0, sizeof(tmp2) );
						sprintf( tmp2, "command ID: %d\n", wID );

						StringUtils::trace( String(tmp2) );

						//defaultWndProcedure( message, wParam, lParam );
					}
				}
				else {
					switch ( notifyCode ) {
						case 0 : { //menu item command
							UINT wID = LOWORD(wParam);

							MenuItem* item = Win32MenuItem::getMenuItemFromID( wID );
							if ( NULL != item ){
								item->click();
							}
						}
						break;

						case 1 : { //accellerator

						}
						break;
					}
				}
			}
		}
		break;

		default:{
			if ( NULL != event ) {
				peerControl_->handleEvent( event );
			}
		}
		break;
	}

	if ( NULL != event ) {
		delete event;
		event = NULL;
	}

	return result;
}

void AbstractWin32Component::repaint( Rect* repaintRect, const bool& immediately )
{	
	VCF_ASSERT(NULL != hwnd_);

	if ( NULL == repaintRect ){
		::InvalidateRect( hwnd_, NULL, TRUE );
	}
	else {
		RECT rect = {0,0,0,0};
		rect.left = (int32)repaintRect->left_;
		rect.top = (int32)repaintRect->top_;
		rect.right = (int32)repaintRect->right_;
		rect.bottom = (int32)repaintRect->bottom_;
		::InvalidateRect( hwnd_, &rect, TRUE );
	}

	if ( immediately ) {
		UpdateWindow( hwnd_ );
	}	
}

void AbstractWin32Component::keepMouseEvents()
{
	VCF_ASSERT(NULL != hwnd_);
	::SetCapture( hwnd_ );
}

void AbstractWin32Component::releaseMouseEvents()
{
	VCF_ASSERT(NULL != hwnd_);
	::ReleaseCapture();
}


String AbstractWin32Component::toString()
{
	String result = Win32Object::toString();
	char tmp[256];
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp, "\n\tpeerControl_=%p\n\tHWND=%p\n", peerControl_, hwnd_ );
	result += tmp;
	return result;
}

void AbstractWin32Component::setCursor( Cursor* cursor )
{
	Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();

	//this is here to override the 
	//default cursor so that we can see the help cursor
	//if what's-up help is triggered, i.e. the user 
	//has pressed the little question mark button
	//on a dialog title bar.
	if ( toolkit->getWhatsThisHelpActive() ) {
		::SetCursor( ::LoadCursor(NULL,IDC_HELP) );
	}
	else if ( NULL != cursor ) {
		::SetCursor( (HCURSOR)cursor->getPeer()->getCursorHandleID() );
	}
}

void AbstractWin32Component::translateToScreenCoords( Point* pt )
{
	VCF_ASSERT(NULL != hwnd_);
	POINT aPt = { (int32)pt->x_, (int32)pt->y_ };
	ClientToScreen( hwnd_, &aPt );
	pt->x_ = aPt.x;
	pt->y_ = aPt.y;
}

void AbstractWin32Component::translateFromScreenCoords( Point* pt )
{
	VCF_ASSERT(NULL != hwnd_);
	POINT aPt = { (int32)pt->x_, (int32)pt->y_ };
	ScreenToClient( hwnd_, &aPt );
	pt->x_ = aPt.x;
	pt->y_ = aPt.y;
}

void AbstractWin32Component::setBorder( Border* border )
{	
	VCF_ASSERT(NULL != hwnd_);
	SetWindowPos(hwnd_, NULL,0,0,0,0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE);
}

LRESULT AbstractWin32Component::handleNCPaint( WPARAM wParam, LPARAM lParam )
{
	VCF_ASSERT(NULL != hwnd_);
#ifdef VCF_WIN32CE
#else
	defaultWndProcedure( WM_NCPAINT, wParam, lParam );
	
	HDC hdc = GetWindowDC(hwnd_);

	int dcs = SaveDC( hdc );
	RECT rect;
	GetWindowRect(hwnd_, &rect);
	OffsetRect(&rect, -rect.left, -rect.top);

	
	Border* border = peerControl_->getBorder();

	RECT clipR = rect;
	RECT clientRect = rect;
	if ( NULL != border ) {		
		Rect clientBounds( rect.left, rect.top, rect.right, rect.bottom );
		clientBounds = border->getClientRect( &clientBounds, peerControl_ );
		
		clipR.left = clientBounds.left_;
		clipR.top = clientBounds.top_;
		clipR.right = clientBounds.right_;
		clipR.bottom = clientBounds.bottom_;
		clientRect = clipR;
	}

	LONG_PTR style = GetWindowLongPtr( hwnd_, GWL_STYLE );
	if ( style & WS_VSCROLL ) {
		NONCLIENTMETRICS ncm;
		memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
		ncm.cbSize = sizeof(NONCLIENTMETRICS);	
		
		SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
		
		//clipR.right -= ncm.iScrollWidth;
		//r.right -= ncm.iScrollWidth;
	}
	
	if ( style & WS_HSCROLL ) {
		NONCLIENTMETRICS ncm;
		memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
		ncm.cbSize = sizeof(NONCLIENTMETRICS);	
		
		SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
		
		//clipR.bottom -= ncm.iScrollHeight;
		//r.bottom -= ncm.iScrollHeight;
	}


	doControlPaint( hdc, rect, &clipR, cpBorderOnly );
	updatePaintDC( hdc, rect, &clipR );
	


	RestoreDC( hdc, dcs );
	ReleaseDC(hwnd_, hdc);
#endif
	
	return 0;
}

LRESULT AbstractWin32Component::handleNCCalcSize( WPARAM wParam, LPARAM lParam )
{
	VCF_ASSERT(NULL != hwnd_);
	RECT* rectToModify = NULL;

	RECT currentWndRect = {0};
	GetWindowRect(hwnd_, &currentWndRect);

	if ( !wParam ) {
		RECT* rect = (RECT*)lParam;
		GetWindowRect(hwnd_, rect);
		OffsetRect(rect, -rect->left, -rect->top);
		rectToModify = rect;
	}
	else {
		NCCALCSIZE_PARAMS *windowParams = (NCCALCSIZE_PARAMS*)lParam;
		windowParams->rgrc[0].left = windowParams->lppos->x; 
		windowParams->rgrc[0].top = windowParams->lppos->y;
		windowParams->rgrc[0].right = windowParams->lppos->x + windowParams->lppos->cx;
		windowParams->rgrc[0].bottom = windowParams->lppos->y + windowParams->lppos->cy;

		rectToModify = &windowParams->rgrc[0];
	}

	//RECT originalRectToMod = *rectToModify;

	

	//return res;

	if ( (NULL != rectToModify) && (!peerControl_->isDestroying()) ) {
		Border* border = peerControl_->getBorder();
		Rect clientBounds( rectToModify->left, rectToModify->top, rectToModify->right, rectToModify->bottom );

		if ( NULL != border ) {
			clientBounds = border->getClientRect( &clientBounds, peerControl_ );
		}

		rectToModify->left = clientBounds.left_;
		rectToModify->top = clientBounds.top_;
		rectToModify->right = clientBounds.right_;
		rectToModify->bottom = clientBounds.bottom_;
	}

	defaultWndProcedure( WM_NCCALCSIZE, wParam, lParam );

	return 0;
}

void AbstractWin32Component::registerForFontChanges()
{
	VCF_ASSERT( peerControl_ != NULL );

	setFont( peerControl_->getFont() );

	peerControl_->getFont()->FontChanged += 
			new ClassProcedure1<Event*,AbstractWin32Component>( this, &AbstractWin32Component::onControlFontChanged, "AbstractWin32Component::onControlFontChanged" );
}

void AbstractWin32Component::onControlFontChanged( Event* event )
{
	Font* font = (Font*) event->getSource();	

	setFont( font );
}


void AbstractWin32Component::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	graphicsContext->setClippingRect( childClipRect );
}

void AbstractWin32Component::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	graphicsContext->setClippingRect( oldClipRect );
}


/**
$Id$
*/
