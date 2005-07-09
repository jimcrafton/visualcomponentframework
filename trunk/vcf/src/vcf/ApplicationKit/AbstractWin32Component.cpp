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

using namespace VCF;

using namespace VCFWin32;



AbstractWin32Component::AbstractWin32Component():
	memDC_(NULL),
	originalMemBMP_(NULL),
	memBMP_(NULL),
	mouseEnteredControl_(false),	
	memDCState_(0),
	destroyed_(false),
	canProcessMessages_(false),
	currentFont_(NULL),
	cachedMessages_(NULL)
{
	init();
	setPeerControl( NULL );
}

AbstractWin32Component::AbstractWin32Component( Control* component ):
	memDC_(NULL),
	originalMemBMP_(NULL),
	memBMP_(NULL),
	mouseEnteredControl_(false),	
	memDCState_(0),
	destroyed_(false),
	canProcessMessages_(false),
	currentFont_(NULL),
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


	if ( NULL != memDC_ ) {
		DeleteDC( memDC_ );
	}

	memDC_ = NULL;
}

AbstractWin32Component::~AbstractWin32Component()
{

}

void AbstractWin32Component::init()
{
	memDC_ = NULL;
	mouseEnteredControl_ = false;

	cachedMessages_ = new std::vector<MSG>();

	/*
	JC I remove this cause we don't really need them
	*/
	//parent_ = NULL;
	//winPosInfo_ = NULL;
	
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
	/*
	JEC - I commented this out to simplify/speed up some resize/repaint issues
	HDWP winPosInfo = NULL;
	if ( NULL != parent_ ) {
		winPosInfo = parent_->getWindPosInfo();
	}


	if ( NULL != winPosInfo ) {
		parent_->winPosInfo_ = ::DeferWindowPos( winPosInfo, hwnd_, NULL, (int)rect->left_, (int)rect->top_,
													(int)rect->getWidth(), (int)rect->getHeight(), SWP_NOACTIVATE | SWP_NOOWNERZORDER| SWP_NOZORDER );
	}
	else{
		::SetWindowPos( hwnd_, NULL, (int)rect->left_, (int)rect->top_,
                    (int)rect->getWidth(), (int)rect->getHeight(), SWP_NOACTIVATE | SWP_NOOWNERZORDER| SWP_NOZORDER );
	}
	*/

	bool repaint = peerControl_->getRepaintOnSize();
	//StringUtils::trace( Format( "AbstractWin32Component::MoveWindow: [%d] %s\n" ) % repaint  % peerControl_->getToolTipText());

	::MoveWindow( hwnd_, (int)rect->left_, (int)rect->top_, rect->getWidth(), (int)rect->getHeight(), repaint );
	//UINT rep = ( repaint ) ? 0 : SWP_NOREDRAW;
	//::SetWindowPos( hwnd_, NULL, (int)rect->left_, (int)rect->top_,
	//                (int)rect->getWidth(), (int)rect->getHeight(), SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | rep );
}



bool AbstractWin32Component::beginSetBounds( const ulong32& numberOfChildren )
{
	/*
	JEC - I commented this out to simplify/speed up some resize/repaint issues
	bool result = false;

	winPosInfo_ = NULL;
	winPosInfo_ = ::BeginDeferWindowPos( numberOfChildren );

	result = (NULL != winPosInfo_);
	*/

	return true;//result;
}

void AbstractWin32Component::endSetBounds()
{
	/*
	JEC - I commented this out to simplify/speed up some resize/repaint issues
	::EndDeferWindowPos( winPosInfo_ );

	winPosInfo_ = NULL;
	*/
}

VCF::Rect AbstractWin32Component::getBounds()
{
	VCF::Rect result;
	RECT r;
 	::GetWindowRect( hwnd_, &r );

	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );

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
	DWORD style = GetWindowLong( hwnd_, GWL_STYLE );
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
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND dummyParent = toolkit->getDummyParent();

	if ( NULL == parent ) {
		::ShowWindow( hwnd_, SW_HIDE );
		::SetParent( hwnd_, dummyParent );
	}
	else {
		VCF::ControlPeer* parentPeer = parent->getPeer();
		/*
		JC I remove this cause we don't really need them
		*/
		//parent_ = NULL;
		
		if ( NULL == dynamic_cast<Frame*>(peerControl_) ){
			HWND wndParent = (HWND)parentPeer->getHandleID();
			
			/*
			JC I remove this cause we don't really need them
			*/
			//parent_ = (AbstractWin32Component*)(parentPeer);
			
			if ( NULL == wndParent ){
				//throw exception !!!
			}
			
			HWND currentParent = ::GetParent( hwnd_ );

			::SetParent( hwnd_, wndParent );

			if ( currentParent == dummyParent ) {
				::ShowWindow( hwnd_, SW_NORMAL );
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
	HWND focusedHandle = ::GetFocus();
	bool result = (NULL != focusedHandle) && (focusedHandle == hwnd_);
	return result;
}

void AbstractWin32Component::setFocused()
{
	::SetFocus( hwnd_ );
}

bool AbstractWin32Component::isEnabled()
{
	return (::IsWindowEnabled( hwnd_ ) != 0);
}

void AbstractWin32Component::setEnabled( const bool& enabled )
{
	::EnableWindow( hwnd_, enabled );
}

void AbstractWin32Component::setFont( Font* font )
{
	if ( NULL != font ){
		Win32Font* win32FontPeer = NULL;
		FontPeer* fontPeer = font->getFontPeer();
		win32FontPeer = dynamic_cast<Win32Font*>(fontPeer );
		if ( NULL != win32FontPeer ){
			HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( win32FontPeer );
			if ( NULL != fontHandle ){
				::SendMessage( hwnd_, WM_SETFONT, (WPARAM)fontHandle, MAKELPARAM(TRUE, 0) );
				currentFont_ = fontHandle;
			}
		}
		else {
			//what the hell is a non Win32Font doing here !!!! throw exception !!!!!
		}
	}
}

HDC AbstractWin32Component::doControlPaint( HDC paintDC, RECT paintRect, RECT* exclusionRect, int whatToPaint  )
{
	HDC result = NULL;

	if ( !peerControl_->isDestroying() ) {
		
		if ( NULL == memDC_ ) {
			// we need a memory HDC, so we create it here one compatible 
			// with the HDC of the entire screen
			HDC dc = ::GetDC(0);
			memDC_ = ::CreateCompatibleDC( dc );
			::ReleaseDC( 0,	dc );
		}					
		
		
		VCF::GraphicsContext* ctx = peerControl_->getContext();
		
		Rect viewableRect(paintRect.left, paintRect.top,
			paintRect.right, paintRect.bottom );

		ctx->setViewableBounds( viewableRect );
		Image* drawingArea = ctx->getDrawingArea();
		
		if ( peerControl_->isUsingRenderBuffer() && 
				!viewableRect.isNull() && 
				!viewableRect.isEmpty() &&
				(NULL != drawingArea) ) {
			
			ctx->getPeer()->setContextID( (OSHandleID)paintDC );

			((ControlGraphicsContext*)ctx)->setOwningControl( NULL );
			
			drawingArea->getImageContext()->setViewableBounds(ctx->getViewableBounds());

			if ( ctx->isRenderAreaDirty() ) {

				if ( NULL != exclusionRect ) {
					ExcludeClipRect( paintDC, exclusionRect->left, exclusionRect->top,
								exclusionRect->right, exclusionRect->bottom );
				}

				GraphicsContext* paintCtx = ctx->getDrawingArea()->getImageContext();
				int gcs = paintCtx->saveState();

				switch( whatToPaint ) {
					case cpBorderOnly : {
						peerControl_->paintBorder( paintCtx );
					}
					break;

					case cpControlOnly : {
						peerControl_->paint( paintCtx );

					}
					break;

					case cpBorderAndControl : {
						peerControl_->paintBorder( paintCtx );
						peerControl_->paint( paintCtx );
					}
					break;
				}
				paintCtx->restoreState( gcs );
			}
			ctx->flushDrawingArea();

			ctx->getDrawingArea()->getImageContext()->setViewableBounds( Rect(0,0,0,0) );

			((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );
			

			result = paintDC;
		}
		else if ( true == peerControl_->isDoubleBuffered() ) {

			Rect dirtyRect( paintRect.left,paintRect.top,paintRect.right,paintRect.bottom);
			
			// implements double buffering by painting everything 
			//  in a memory device context first

			memBMP_ = ::CreateCompatibleBitmap( paintDC,
					paintRect.right - paintRect.left,
					paintRect.bottom - paintRect.top );

			memDCState_ = ::SaveDC( memDC_ );
			originalMemBMP_ = (HBITMAP)::SelectObject( memDC_, memBMP_ );



			// changes the origin of the paint coordinates, by specifying which
			// point of the device context points to the origin of the window.
			POINT oldOrg = {0};
			::SetViewportOrgEx( memDC_, -paintRect.left, -paintRect.top, &oldOrg );
			
			
			/**
			* we prevents the owning control of the context to alter
			* the HDC and the viewport, as this is done here using 
			* the DC given by the system with the message itself.
			* We temporarly use a memory context as teh current 
			* HDC for the Graphics context because we are 
			* doing double buffering.
			*/
			ctx->getPeer()->setContextID( (OSHandleID)memDC_ );
			((ControlGraphicsContext*)ctx)->setOwningControl( NULL );				
			
			// save the state of Graphics control so to be fully restored after the paint.
			int gcs = ctx->saveState();

			switch( whatToPaint ) {
				case cpBorderOnly : {
					peerControl_->paintBorder( ctx );
				}
				break;

				case cpControlOnly : {
					peerControl_->paint( ctx );

				}
				break;

				case cpBorderAndControl : {
					peerControl_->paintBorder( ctx );
					peerControl_->paint( ctx );
				}
				break;
			}

			ctx->restoreState( gcs );

			((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );


			//reset back to original origin

			::SetViewportOrgEx( memDC_, -paintRect.left, -paintRect.top, &oldOrg );

			
			result = memDC_;
		
		}
		else {
			
			/**
			* we prevents the owning control of the context to alter
			* the HDC and the viewport, as this is done here using 
			* the DC given by the system with the message itself.
			*/
			ctx->getPeer()->setContextID( (OSHandleID)paintDC );
			((ControlGraphicsContext*)ctx)->setOwningControl( NULL );

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
					peerControl_->paint( ctx );

				}
				break;

				case cpBorderAndControl : {
					peerControl_->paintBorder( ctx );
					peerControl_->paint( ctx );
				}
				break;
			}

			ctx->restoreState( gcs );

			((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );
			
			result = paintDC;
		}
		
		ctx->setViewableBounds( Rect( 0,0,0,0 ) );
		
	}

	return result;
}

void AbstractWin32Component::updatePaintDC( HDC paintDC, RECT paintRect, RECT* exclusionRect )
{	

	if ( !peerControl_->isDestroying() ) {
		if ( true == peerControl_->isDoubleBuffered() && !peerControl_->isUsingRenderBuffer() ) {
			VCF_ASSERT( memDCState_ != 0 );
			VCF_ASSERT( originalMemBMP_ != 0 );
			VCF_ASSERT( memBMP_ != 0 );

			if ( NULL != exclusionRect ) {
				ExcludeClipRect( paintDC, exclusionRect->left, exclusionRect->top,
									exclusionRect->right, exclusionRect->bottom );
			}

			/**
			* does the final part of the double buffering mechanism
			* copies the memory context into the device context
			* given by the system with the paint message itself.
			*/
			int err = /*::BitBlt( ps.hdc, 0, 0,
					  (int)clientBounds.getWidth(),
					  (int)clientBounds.getHeight(),
					  memDC_, 0, 0, SRCCOPY );*/			

					  ::BitBlt( paintDC, paintRect.left, paintRect.top,
					  paintRect.right - paintRect.left,
					  paintRect.bottom - paintRect.top,
					  memDC_, paintRect.left, paintRect.top, SRCCOPY );
			
			
			::RestoreDC ( memDC_, memDCState_ );
			
			::DeleteObject( memBMP_ );
			
			memBMP_ = NULL;
			originalMemBMP_ = NULL;
			memDCState_ = 0;
			
			if ( err == FALSE ) {
				err = GetLastError();
				StringUtils::traceWithArgs( Format("error in BitBlt during drawing of double buffered Comp: error code=%d\n") %	
											err );
			}

		}
	}
}

void AbstractWin32Component::checkForFontChange()
{	
	if ( NULL != currentFont_ ) {
		Font* font = peerControl_->getFont();

		void* lf1 = NULL;
		void* lf2 = NULL;
		int lfSize = 0;
		lf1 = font->getFontPeer()->getFontHandleID();

		LOGFONTW lf2w;
		LOGFONTA lf2a;

		if ( System::isUnicodeEnabled() ) {			
			memset( &lf2w, 0, sizeof(LOGFONTW) );
			GetObjectW( currentFont_, sizeof(LOGFONTW), &lf2w );

			//set lfWidth to 0 - essentially we want to 
			//ignore this in our compare, as we do
			//not bother to set it
			lf2w.lfWidth = 0;

			lf2 = &lf2w;
			lfSize = sizeof(LOGFONTW);
		}
		else {
			memset( &lf2a, 0, sizeof(LOGFONTW) );		
			GetObjectA( currentFont_, sizeof(LOGFONTA), &lf2a );

			//set lfWidth to 0 - essentially we want to 
			//ignore this in our compare, as we do
			//not bother to set it
			lf2a.lfWidth = 0;

			lf2 = &lf2a;
			lfSize = sizeof(LOGFONTA);
		}	
		
		
		
		int cmp = memcmp( &lf2, lf1, lfSize );
		if ( cmp != 0 ) {
			Win32Font* win32FontPeer = (Win32Font*)font->getFontPeer();
			
			HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( win32FontPeer );
			if ( NULL != fontHandle ){
				::SendMessage( hwnd_, WM_SETFONT, (WPARAM)fontHandle, MAKELPARAM(FALSE, 0) );
				currentFont_ = fontHandle;
			}
			

		}
	}
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
		
		if ( (message == WM_SIZE) || 
			(message == WM_MOVE) ||
			(message == WM_ERASEBKGND) ||
			(message == WM_SETFOCUS) ||
			(message == WM_KILLFOCUS) )  {
			
			MSG m = {0};
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
		if( message == WM_ERASEBKGND )
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


				StringUtils::traceWithArgs( "lost focus: %s @ %p\n",
											obj->getPeerControl()->getClassName().c_str(), obj->getPeerControl() );


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

				StringUtils::traceWithArgs( "gained focus: %s @ %p\n",
											obj->getPeerControl()->getClassName().c_str(), obj->getPeerControl() );

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
				/*
				PCOPYDATASTRUCT pcd = (PCOPYDATASTRUCT) lParam;
				VCF::ulong32 dwData = (VCF::ulong32) pcd->dwData;
				VCF::ulong32 cbData = (VCF::ulong32) pcd->cbData;
				*/
				Win32MSG msg( hwnd_, message, wParam, lParam, peerControl_ );
				Event e(peerControl_) ;
				e.setUserData( &msg );
				app->onOSNativeEvent( &e );
			}
		}
		break;

		case WM_PAINT:{
			if ( true == isCreated() ){
				//StringUtils::trace( Format( "AbstractWin32Component::WM_PAINT: [%d] %s\n" ) % peerControl_->getRepaintOnSize() % peerControl_->getToolTipText() );
				if ( !peerControl_->isDestroying() ) {
					if( !GetUpdateRect( hwnd_, NULL, FALSE ) ){
						wndProcResult = 0;
						result = true;
						return result;
					}


					//check to see if the font needs updating
					checkForFontChange();



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
/*


		case WM_HELP : {
			if ( !peerControl_->isDestroying() ) {
				HELPINFO* helpInfo = (HELPINFO*) lParam;
				if ( HELPINFO_WINDOW == helpInfo->iContextType ) {
					if ( helpInfo->hItemHandle == hwnd_ ) {
						peerControl_->processWhatsThisHelpEvent();
					}
				}
				else if ( HELPINFO_MENUITEM == helpInfo->iContextType ) {
					HelpEvent event(peerControl_);
					peerControl_->fireOnHelpRequested( &event );
				}
			}
		}
		break;

*/

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
			}

			mouseEnteredControl_ = true;

			peerControl_->handleEvent( event );

		}
		break;


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

					if ( true == foundItem->canPaint() ) {

						Win32MenuItem* itemPeer = (Win32MenuItem*)foundItem->getPeer();

						itemPeer->drawDefaultMenuItem( idCtl, *drawItemStruct );

						GraphicsContext gc( (OSHandleID)drawItemStruct->hDC );
						foundItem->paint( &gc, &Rect(drawItemStruct->rcItem.left, drawItemStruct->rcItem.top,
														drawItemStruct->rcItem.right, drawItemStruct->rcItem.bottom) );
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

					if ( true == foundItem->canPaint() ) {
						result = TRUE;
						Rect* bounds = foundItem->getBounds();
						bool needsBounds = false;
						if ( NULL != bounds ) {
							needsBounds = ((bounds->getHeight() <= 0.0) && (bounds->getWidth() <= 0.0));
						}
						else {
							needsBounds = true;
						}
						if ( true == needsBounds ) {
							Win32MenuItem* peer = (Win32MenuItem*)foundItem->getPeer();
							peer->fillInMeasureItemInfo( *measureInfo );
						}
						else {
							measureInfo->itemHeight = (long)bounds->getHeight();
							measureInfo->itemWidth = (long)bounds->getWidth();
						}
					}
				}
			}
			else {
				//result = defaultWndProcedure( message, wParam, lParam );
			}
		}
		break;

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

		case WM_INITMENUPOPUP : {
			if ( !peerControl_->isDestroying() ) {
				HMENU hmenuPopup = (HMENU) wParam;//thisis the menu handle of the menu popuping up or dropping down
				if ( GetMenuItemCount( hmenuPopup ) > 0 ) {
					//UINT Pos = (UINT) LOWORD(lParam);
					UINT uPos = (UINT) LOWORD(lParam);
					//get the first item
					MENUITEMINFO info = {0};
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

					if ( scrollable->hasVerticalScrollBar() && (scrollable->getVirtualViewHeight() > peerControl_->getHeight() ) ) {
						int pos = 0;
						//StringUtils::traceWithArgs( "zDelta: %d\n", zDelta );
						if ( zDelta < 0 ) {
							pos = VCF::minVal<long>((scrollable->getVerticalPosition() + 10),
												abs((long)(scrollable->getVirtualViewHeight() - peerControl_->getHeight())) );
						}
						else if ( zDelta > 0 ) {
							pos = VCF::maxVal<long>((scrollable->getVerticalPosition() - 10), 0 );
						}

						scrollable->setVerticalPosition( pos );

					}
					else if ( scrollable->hasHorizontalScrollBar() && (scrollable->getVirtualViewWidth() > peerControl_->getWidth() ) ) {
						int pos = 0;
						//StringUtils::traceWithArgs( "zDelta: %d\n", zDelta );
						if ( zDelta < 0 ) {
							pos = VCF::minVal<long>((scrollable->getHorizontalPosition() + 10),
												abs((long)(scrollable->getVirtualViewWidth() - peerControl_->getWidth())) );
						}
						else if ( zDelta > 0 ) {
							pos = VCF::maxVal<long>((scrollable->getHorizontalPosition() - 10), 0 );
						}

						scrollable->setHorizontalPosition( pos );
					}
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

								//pos = min( pos, abs((long)(scrollable->getVirtualViewHeight() - height)) );
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

								//pos = min( pos, abs((long)(scrollable->getVirtualViewHeight() - height)) );
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

								//pos = min( pos, abs((long)(scrollable->getVirtualViewWidth() - width)) );
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

								//pos = min( pos, abs((long)(scrollable->getVirtualViewWidth() - width)) );
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
			//result = defaultWndProcedure( message, wParam, lParam );			

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

void AbstractWin32Component::repaint( Rect* repaintRect )
{
	if ( NULL == repaintRect ){
		::InvalidateRect( hwnd_, NULL, TRUE );
	}
	else {
		RECT rect = {0,0,0,0};
		rect.left = (long)repaintRect->left_;
		rect.top = (long)repaintRect->top_;
		rect.right = (long)repaintRect->right_;
		rect.bottom = (long)repaintRect->bottom_;
		::InvalidateRect( hwnd_, &rect, TRUE );
	}
}

void AbstractWin32Component::keepMouseEvents()
{
	::SetCapture( hwnd_ );
}

void AbstractWin32Component::releaseMouseEvents()
{
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
	if ( NULL != cursor ) {
		::SetCursor( (HCURSOR)cursor->getPeer()->getCursorHandleID() );
	}
}

void AbstractWin32Component::translateToScreenCoords( Point* pt )
{
	POINT aPt = { (long)pt->x_, (long)pt->y_ };
	ClientToScreen( hwnd_, &aPt );
	pt->x_ = aPt.x;
	pt->y_ = aPt.y;
}

void AbstractWin32Component::translateFromScreenCoords( Point* pt )
{
	POINT aPt = { (long)pt->x_, (long)pt->y_ };
	ScreenToClient( hwnd_, &aPt );
	pt->x_ = aPt.x;
	pt->y_ = aPt.y;
}

void AbstractWin32Component::setBorder( Border* border )
{	
	SetWindowPos(hwnd_, NULL,0,0,0,0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE);
}

LRESULT AbstractWin32Component::handleNCPaint( WPARAM wParam, LPARAM lParam )
{
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

	int style = GetWindowLong( hwnd_, GWL_STYLE );
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

	
	return 0;
}

LRESULT AbstractWin32Component::handleNCCalcSize( WPARAM wParam, LPARAM lParam )
{
	RECT* rectToModify = NULL;

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

/**
*CVS Log info
*$Log$
*Revision 1.7  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.6  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.5.2.22  2005/06/29 20:33:35  marcelloptr
*second step to remove flickering when dragging a splitter
*
*Revision 1.5.2.20  2005/06/29 05:00:02  marcelloptr
*some white spaces
*
*Revision 1.5.2.19  2005/06/14 07:33:35  dougtinkham
*Fixed flicker effect with WM_ERASEBKGND in handleEventMessages
*
*Revision 1.5.2.18  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.5.2.17  2005/05/02 02:31:42  ddiego
*minor text updates.
*
*Revision 1.5.2.16  2005/04/27 02:05:38  marcelloptr
*somehow the first line of the cvs log section got deleted... restored
*
*Revision 1.3.2.3  2005/04/26 02:29:39  ddiego
*fixes font setting bug brought up by scott and glen_f
*
*Revision 1.5.2.7  2005/03/27 05:25:13  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.5.2.6  2005/03/15 01:51:49  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.5.2.5  2005/02/16 05:09:30  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.5.2.4  2005/01/28 02:49:01  ddiego
*fixed bug 1111096 where the text control was properly handlind
*input from the numbpad keys.
*
*Revision 1.5.2.3  2005/01/16 03:02:41  marcelloptr
*bugfix [ 1099910 ] plus other improvements on the scrolling behaviour
*
*Revision 1.5.2.1  2004/12/19 04:04:58  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.5  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.4  2004/08/20 23:59:16  ddiego
*minor fix to listboxcontrol
*
*Revision 1.3  2004/08/19 02:24:54  ddiego
*fixed bug [ 1007039 ] lightweight controls do not paint correctly.
*
*Revision 1.2.2.9  2004/11/07 19:32:18  marcelloptr
*more documentation
*
*Revision 1.2.2.8  2004/09/21 22:27:09  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.7  2004/09/21 05:37:36  dougtinkham
*minor mod to handleEventMessages, case WM_HSCROLL, for horiz. scrolling
*
*Revision 1.2.2.6  2004/09/12 22:34:20  ddiego
*fixed bug in handling window cleanup when exception thrown from constructor.
*
*Revision 1.2.2.5  2004/09/07 03:57:04  ddiego
*misc tree control update
*
*Revision 1.2.2.4  2004/09/06 21:30:19  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2.2.3  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2.2.2  2004/08/26 01:44:38  ddiego
*fixed font pix size bug that handled non true type fonts poorly.
*
*Revision 1.2.2.1  2004/08/19 03:22:53  ddiego
*updates so new system tray code compiles
*
*Revision 1.3  2004/08/19 02:24:54  ddiego
*fixed bug [ 1007039 ] lightweight controls do not paint correctly.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.17  2004/07/24 03:56:03  ddiego
*fixed a repaint bug that didn't take into account when a control
*is using the render buffer.
*
*Revision 1.1.2.16  2004/07/21 03:35:49  ddiego
*some minor updates to the QTPlayer example
*
*Revision 1.1.2.15  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.14  2004/07/17 17:56:24  ddiego
*minor mods to the TableControl and the TabbedPages control
*so that drawing updates get drawn better, and we don't have weird missing
*artifacts.
*
*Revision 1.1.2.13  2004/07/16 04:01:45  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.12  2004/07/15 18:53:00  ddiego
*more updates
*
*Revision 1.1.2.11  2004/07/15 14:55:11  ddiego
*borders fixed
*
*Revision 1.1.2.10  2004/07/15 04:27:14  ddiego
*more updates for edit nc client painting
*
*Revision 1.1.2.9  2004/07/14 21:54:40  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.8  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.7  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.6  2004/07/12 02:05:45  ddiego
*fixed a subtle bug (that only showed up when using a lightweight
*control) that happened with MouseClick events being handled twice.
*
*Revision 1.1.2.5  2004/07/11 22:08:06  ddiego
*fixed an accidental checkin that resulted in scrolled
*drawing not showing up correctly
*
*Revision 1.1.2.4  2004/07/01 04:02:13  ddiego
*minor stuff
*
*Revision 1.1.2.3  2004/06/05 01:55:20  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.50.2.1  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.50  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*

*Revision 1.49  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.48.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*

*Revision 1.48.2.6  2004/03/28 00:46:22  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.48.2.5  2004/03/26 18:37:59  marcelloptr
*very minor fixes
*
*Revision 1.48.2.4  2004/03/21 20:25:40  marcelloptr
*Scrollable automatically calculates the scroll given the line where to go
*
*Revision 1.48.2.3  2004/03/19 04:18:53  ddiego
*added more code to condition example, fixed some
*minor stuff in the table control
*
*Revision 1.48.2.2  2004/03/17 03:22:57  ddiego
*fixed a glitch in setting focus
*
*Revision 1.48.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.48  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.47.2.12  2003/11/24 05:05:24  ddiego
*added some more docs, and some minor changes to the Win32ScrollPeer
*
*Revision 1.47.2.11  2003/11/10 01:57:43  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.47.2.10  2003/11/04 04:19:38  ddiego
**** empty log message ***
*
*Revision 1.47.2.9  2003/11/01 15:53:04  ddiego
**** empty log message ***
*
*Revision 1.47.2.8  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.47.2.7  2003/10/10 04:33:22  ddiego
*made the treelist look a bit better
*
*Revision 1.47.2.6  2003/10/09 22:05:20  ddiego
*menu item fix
*
*Revision 1.47.2.5  2003/10/08 04:53:54  ddiego
*minor futzing around with menu updates
*
*Revision 1.47.2.4  2003/10/04 20:14:59  ddiego
*aaddec changes to support compiling on GCC 3.3.1, which is much more
*picky than some of the previous versions.
*
*Revision 1.47.2.3  2003/09/18 17:56:44  ddiego
*added a fix to menu items (in hte assignment of their Win32 menuid)
*and to foward update events correctly (this was occasionally not working
*right for menus that had been dynamically inserted later on, after
*the main menu had already been constructed)
*
*Revision 1.47.2.2  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.47.2.1  2003/08/23 02:01:29  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.47  2003/08/09 02:56:46  ddiego
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
*Revision 1.46.2.7  2003/07/28 23:49:59  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.46.2.6  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.46.2.5  2003/06/20 04:36:59  ddiego
*further AGG integration
*moved files over to renamed directories
*
*Revision 1.46.2.4  2003/06/17 03:54:25  ddiego
*further agg integration - took out the getImage/putImage from GraphicsContext -
*this was too slow. now have an alternate solution that seems to work OK
*
*Revision 1.46.2.3  2003/06/13 03:05:31  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.46.2.2  2003/06/13 00:02:10  ddiego
*more xmake fixes for the new version
*bug fixes for bugs
*509004	Opening a modal Dialog causes flicker
*also have tooltips working again
*
*Revision 1.46.2.1  2003/05/27 04:45:33  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.46  2003/05/17 20:37:28  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.45.2.4  2003/05/14 03:04:29  ddiego
*fixed some bugs caused by some of the changes in the graphics kit that I made
*yesterday. All is well now.
*
*Revision 1.45.2.3  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.45.2.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.45.2.1  2003/03/12 03:12:16  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.45  2003/02/26 04:30:47  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.44.2.4  2003/01/08 00:19:51  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.44.2.3  2002/12/30 00:24:13  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.44.2.2  2002/12/27 23:04:51  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.44.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.44  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.43.4.1  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.43  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.42.6.2  2002/09/10 04:07:48  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.42.6.1  2002/09/06 05:24:52  ddiego
*fixed bug in TableControl where it does not proeprly finished the ItemEditor
*correctly on loss of focus for the editor's control
*
*Revision 1.42  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.41.4.2  2002/04/27 15:52:23  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.41.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.41  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.40  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


