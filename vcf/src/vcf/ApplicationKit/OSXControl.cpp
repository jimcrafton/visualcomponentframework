//OSXControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/OSXLightweightControl.h"
#include "vcf/ApplicationKit/OSXWindow.h"
#include "vcf/ApplicationKit/OSXCursorPeer.h"

/*

class OSXControlView : public TView {
public:
	

	OSXControlView( HIViewRef inControl ):
		TView(inControl){
		
	}
	
	virtual ~OSXControlView() {
	
	}

	virtual OSStatus Initialize( TCarbonEvent& inEvent ) {
		OSStatus res = TView::Initialize( inEvent );
		
		return res;
	}
	
	
	virtual UInt32 GetBehaviors() {
		return TView::GetBehaviors() | kHIViewAllowsSubviews | kHIViewDoesNotUseSpecialParts;
            //kControlSupportsEmbedding | kControlSupportsFocus |
            //kControlWantsActivate | kControlHandlesTracking |
            //kControlGetsFocusOnClick | kControlSupportsClickActivation;
	}
	
	
	virtual ControlPartCode HitTest( const HIPoint& inWhere ) {
		ControlPartCode		part;
		
		// Is the mouse in the view?
		if ( CGRectContainsPoint( Bounds(), inWhere ) )
			part = 1;
		else
			part = kControlNoPart;
		
		return part;
	}

									
	virtual ControlKind GetKind() {
		const ControlKind result = { 'OSXv', 'OSXc' };	
		return result;
	}
	
	virtual OSStatus GetRegion( ControlPartCode inPart, RgnHandle outRgn ) {
		OSStatus			err = noErr;
		TRect				bounds;
		Rect				qdBounds;
		
		if ( inPart == kControlContentMetaPart
				|| inPart == kControlStructureMetaPart
				) // || inPart == kControlOpaqueRegionMetaPart  )
		{
			bounds = Bounds();
			qdBounds = bounds;
		
			RectRgn( outRgn, &qdBounds );
		}
		
		return err;
	}

	virtual void Draw( RgnHandle inLimitRgn, CGContextRef inContext, GrafPtr port ) {
	
	}	
protected:

};


namespace VCF {

static const EventTypeSpec osxHIViewEvents[] =
{	{ kEventClassCommand, kEventCommandProcess },
	{ kEventClassCommand, kEventCommandUpdateStatus },
	
	{ kEventClassControl, kEventControlInitialize },
	{ kEventClassControl, kEventControlDraw },
	{ kEventClassControl, kEventControlHitTest },
	{ kEventClassControl, kEventControlGetPartRegion },
	{ kEventClassControl, kEventControlGetData },
	{ kEventClassControl, kEventControlSetData },
	{ kEventClassControl, kEventControlGetOptimalBounds },
	{ kEventClassControl, kEventControlBoundsChanged },
	{ kEventClassControl, kEventControlTrack },
	{ kEventClassControl, kEventControlGetSizeConstraints },
	{ kEventClassControl, kEventControlHit },
	{ kEventClassControl, kEventControlOwningWindowChanged },

	
	{ kEventClassKeyboard, kEventRawKeyDown },
	{ kEventClassKeyboard, kEventRawKeyUp },

	{ kEventClassControl, kEventControlHiliteChanged },
	{ kEventClassControl, kEventControlActivate },
	{ kEventClassControl, kEventControlDeactivate },
	{ kEventClassControl, kEventControlValueFieldChanged },
	{ kEventClassControl, kEventControlTitleChanged },
	{ kEventClassControl, kEventControlEnabledStateChanged },
	{ kEventClassControl, kEventControlOwningWindowChanged },
    { kEventClassControl, kEventControlSetFocusPart }
    
};





OSXControl::OSXControl( Control* control ):
	hiView_(NULL),
	control_(control),
	handlerRef_(NULL),
	mouseState_(OSXControl::msNoState)
{
	lastMousePt_.h = 0;
	lastMousePt_.v = 0;
}

OSXControl::~OSXControl()
{

}

OSHandleID OSXControl::getHandleID()
{
	return (OSHandleID) hiView_;
}

EventHandlerUPP OSXControl::getEventHandlerUPP()
{
    static EventHandlerUPP result = NULL;
    if ( NULL == result ) {
        result = NewEventHandlerUPP( OSXControl::handleOSXEvents );
    }
    return result;
}

OSXControl* OSXControl::getControlFromControlRef( ControlRef control )
{
	OSXControl* result = NULL;
	
	if ( noErr != GetControlProperty( control, VCF_PROPERTY_CREATOR, 
									  VCF_PROPERTY_CONTROL_VAL, 
									  sizeof(OSXControl*), NULL, &result ) ) {
		result = NULL;
	}
	return result;
}

OSStatus OSXControl::installStdControlHandler()
{
	VCF_ASSERT( hiView_ != NULL );
	
	return InstallEventHandler( GetControlEventTarget( hiView_ ), 
							OSXControl::getEventHandlerUPP(),
							sizeof(osxHIViewEvents) / sizeof(EventTypeSpec), 
							osxHIViewEvents, 
							this, 
							&handlerRef_ );
}

void OSXControl::create( Control* owningControl )
{
	TRect bounds(0,0,0,0);
	
	if ( noErr == ViewCreator<OSXControlView>::create( &hiView_, bounds, NULL ) ) {
		
		control_ = owningControl;
		OSXControl* thisPtr = this;
		SetControlProperty( hiView_, 
							VCF_PROPERTY_CREATOR, 
							VCF_PROPERTY_CONTROL_VAL, 
							sizeof(thisPtr), 
							&thisPtr );


		OSStatus err = installStdControlHandler();

		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("InstallEventHandler failed for OSXControl!") );
		}
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("OSXControl failed to be created!") );
	}
}

void OSXControl::destroyControl()
{

}


void OSXControl::setBounds( Rect* rect )
{
	TRect r( rect->left_, rect->top_, rect->getWidth(), rect->getHeight() );	
	HIViewSetFrame( hiView_, r );
}

bool OSXControl::beginSetBounds( const uint32& numberOfChildren )
{
	return true;
}

void OSXControl::endSetBounds()
{

}

Rect OSXControl::getBounds()
{
	Rect result;
	
	HIRect		frame;	
	HIViewGetFrame( hiView_, &frame );
	
	TRect r = frame;
	
	result.setRect( r.origin.x, r.origin.y, r.origin.x + r.size.width, r.origin.y + r.size.height ); 
	
	return result;
}

void OSXControl::setVisible( const bool& visible )
{
	HIViewSetVisible( hiView_, visible );
}

bool OSXControl::getVisible()
{
	return IsControlVisible(hiView_) ? true : false;
}

Control* OSXControl::getControl()
{
	return control_;
}

void OSXControl::setControl( Control* component )
{
	control_ = component;
}

void OSXControl::setCursor( Cursor* cursor )
{
	if (NULL == cursor) {
		return;
	}
	
	OSXCursorPeer *peer = (OSXCursorPeer*)cursor->getPeer();
	
	if (NULL == peer) {
		return;
	}
	
	if (peer->isSystemCursor()){
		SetThemeCursor(peer->getCursorID());
	}	
}

void OSXControl::setParent( Control* parent )
{
	Frame* windowParent = NULL;
	
	if ( NULL != parent && parent->isLightWeight() ) {
		OSXLightweightControl* lwPeer = dynamic_cast<OSXLightweightControl*>(parent->getPeer());
		if ( NULL != lwPeer ) {
			Control* lwParent = lwPeer->getHeavyWeightParent();
			if ( NULL != lwParent ) {
				windowParent = dynamic_cast<Frame*>(lwParent);
			}
		}
	}
	else {
		windowParent = dynamic_cast<Frame*>(parent);
	}
	
	
	if ( NULL != windowParent ) {
 		OSXWindow* osxWnd = dynamic_cast<OSXWindow*>(windowParent->getPeer());
		WindowRef wnd = (WindowRef) osxWnd->getHandleID();
		
		ControlRef contentView = osxWnd->getRootControl();		
					
		OSStatus err = HIViewAddSubview( contentView, hiView_ );		
	}
	else if ( parent != NULL ) {
		ControlRef parentControlRef = (ControlRef)parent->getPeer()->getHandleID();
		OSStatus err = HIViewAddSubview( parentControlRef, hiView_ );
		if ( err != noErr ) {
			StringUtils::trace( Format("HIViewAddSubview failed, err: %d\n") % err );
		}
	}
}

Control* OSXControl::getParent()
{
	Control* result = NULL;
	HIViewRef parentRef = HIViewGetSuperview( hiView_ );	
	
	OSXControl* parentPeer = OSXControl::getControlFromControlRef( parentRef );
	if ( NULL != parentPeer ) {
		result = parentPeer->getControl();
	}
	
	return result;
}

bool OSXControl::isFocused()
{
	WindowRef wnd = GetControlOwner( hiView_ );
	ControlRef focusedControl = NULL;
	GetKeyboardFocus( wnd, &focusedControl );	
	
	return ( hiView_ == focusedControl ) ? true : false;
}

void OSXControl::setFocused()
{
    EventModifiers mods = 0;
	HIViewAdvanceFocus( hiView_, mods );    
}

bool OSXControl::isEnabled()
{
	return IsControlEnabled( hiView_ ) ? true : false;
}

void OSXControl::setEnabled( const bool& enabled )
{
	if ( enabled ) {
		EnableControl( hiView_ );
	}
	else {
		DisableControl( hiView_ );
	}
}

void OSXControl::setFont( Font* font )
{
	String fontName = font->getName();
	
	SInt16 iFONDNumber = 0;
    Str255 pStr;
    CopyCStringToPascal( fontName.empty() ? "Arial" : fontName.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	
	ControlFontStyleRec fontRec = {0};
	fontRec.flags = kControlUseForeColorMask | kControlUseFontMask | kControlUseSizeMask | kControlUseFaceMask;
	fontRec.font = iFONDNumber;
	fontRec.size = font->getPointSize();
	if ( font->getBold() ) {
		fontRec.style |= 1;
	}
	
	if ( font->getItalic() ) {
		fontRec.style |= 2;
	}
	
	if ( font->getUnderlined() ) {
		fontRec.style |= 4;
	}
	
	Color* color = font->getColor();
	color->getRGB16( fontRec.foreColor.red, fontRec.foreColor.green, fontRec.foreColor.blue );
	SetControlFontStyle( hiView_, &fontRec );	
}

void OSXControl::repaint( Rect* repaintRect, const bool& immediately )
{
	HIViewSetNeedsDisplay( hiView_, true );
}

void OSXControl::keepMouseEvents()
{

}

void OSXControl::releaseMouseEvents()
{

}

void OSXControl::translateToScreenCoords( Point* pt )
{
	HIPoint tmpPt;
	tmpPt.x = pt->x_;
	tmpPt.y = pt->y_;
	
	HIViewConvertPoint( &tmpPt, hiView_, NULL );
	::Rect r;
	GetWindowBounds( GetControlOwner(hiView_), kWindowStructureRgn, &r );
	tmpPt.x += r.left;
	tmpPt.y += r.top;
	
	pt->x_ = tmpPt.x;
	pt->y_ = tmpPt.y;	
}

void OSXControl::translateFromScreenCoords( Point* pt )
{
	HIPoint tmpPt;
	tmpPt.x = pt->x_;
	tmpPt.y = pt->y_;
	::Rect r;
	GetWindowBounds( GetControlOwner(hiView_), kWindowStructureRgn, &r );
	tmpPt.x -= r.left;
	tmpPt.y -= r.top;
	
	HIViewConvertPoint( &tmpPt, NULL, hiView_ );	
	
	pt->x_ = tmpPt.x;
	pt->y_ = tmpPt.y;
}


OSStatus OSXControl::handleOSXEvents(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData)
{
	OSXControl* control = (OSXControl*)userData;
    
    return control->handleOSXEvent( nextHandler, theEvent );
}

void OSXControl::setBorder( Border* border )
{
	//cause the control to repaint itself!
	repaint(NULL,false);
}

OSStatus OSXControl::handleWrappedControlHitTest( EventRef theEvent )
{
	GetEventParameter( theEvent, kEventParamMouseLocation, typeQDPoint, NULL,
					   sizeof (lastMousePt_), NULL, &lastMousePt_);
	
	OSXEventMsg msg( theEvent, control_ );
	
	Event* mouseMove = UIToolkit::createEventFromNativeOSEventData( &msg );
	if ( NULL != mouseMove ) {
		control_->handleEvent( mouseMove );
		mouseMove->free();
	}
	
	return noErr;
}

OSStatus OSXControl::handleWrappedControlTrack( EventRef theEvent )
{
	//first fire off a mouse down event!
	mouseState_ = OSXControl::msDown;
	
	
	OSXEventMsg msg( theEvent, control_ );
	
	Event* mouseDown = UIToolkit::createEventFromNativeOSEventData( &msg );
	if ( NULL != mouseDown ) {
		control_->handleEvent( mouseDown );
		mouseDown->free();
	}
	
	return noErr;
}

OSStatus OSXControl::handleWrappedControlTrackDone( EventRef theEvent )
{
	WindowRef wnd = GetControlOwner(hiView_);
	OSXWindow* osxWnd = OSXWindow::getWindowFromWindowRef( wnd );
	
	
	uint32 buttonVal = osxWnd->getCurrentMouseBtn();
	
	//LocalToGlobal( &lastMousePt_ );
	VCF::Point pt( lastMousePt_.h , lastMousePt_.v );
	//localizes the coords
	//translateFromScreenCoords( &pt );
	
	Scrollable* scrollable = control_->getScrollable();
	if ( NULL != scrollable ) {
		pt.x_ += scrollable->getHorizontalPosition();
		pt.y_ += scrollable->getVerticalPosition();
	}	
	
	Event* mouseUp = new VCF::MouseEvent ( control_, Control::MOUSE_UP,
										   buttonVal,
										   OSXUIUtils::translateKeyMask( 0 ), //fix this - !!!!!
										   &pt );
	control_->handleEvent( mouseUp );
	mouseUp->free();
	
	mouseState_ = OSXControl::msUp;
	
	return noErr;
}

OSStatus OSXControl::handleControlTrack( EventRef theEvent )
{
	OSStatus result = noErr;
	
	uint32 buttonDown = VCF::mbmUndefined;
	
	WindowRef wnd = GetControlOwner(hiView_);
	OSXWindow* osxWnd = OSXWindow::getWindowFromWindowRef( wnd );
	
	
	uint32 buttonDownVal = osxWnd->getCurrentMouseBtn();
	
	//first fire off a mouse down event!
	OSXEventMsg msg( theEvent, control_ );
	
	Event* mouseDown = UIToolkit::createEventFromNativeOSEventData( &msg );
	if ( NULL != mouseDown ) {
		control_->handleEvent( mouseDown );
		mouseDown->free();
	}
	
	
	::Point lastPt;
	MouseTrackingResult trackMouseRes;
	bool quitTracking = false;
	OSStatus err = 0;
	UInt32 mods = 0;
	
	while ( !quitTracking ) {
		err = TrackMouseLocationWithOptions( NULL, 0, 0.5, &lastPt, &mods, & trackMouseRes );
		
		if ( noErr != err ) {
			quitTracking = true;
			break;
		}
		
		if ( trackMouseRes == kMouseTrackingMouseUp ) {									   
												
			quitTracking = true;
			break;
		}
		else if ( (trackMouseRes == kMouseTrackingMouseMoved) || (trackMouseRes == kMouseTrackingMouseDragged) ) {
			uint32 mouseBtnDown = 0;
			if ( trackMouseRes == kMouseTrackingMouseMoved ) {
				mouseBtnDown = buttonDown;
			}
			else if ( trackMouseRes == kMouseTrackingMouseDragged ) {
				mouseBtnDown = buttonDownVal;
			}
			LocalToGlobal( &lastPt );
			VCF::Point pt( lastPt.h , lastPt.v );
			//localizes the coords
			translateFromScreenCoords( &pt );	
			
			Scrollable* scrollable = control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}
			
			
			Event* mouseMove = new VCF::MouseEvent ( control_, Control::MOUSE_MOVE,
										   mouseBtnDown,
										   OSXUIUtils::translateKeyMask( mods ), &pt );
										   
			control_->handleEvent( mouseMove );
			mouseMove->free();
		}		
	}
	
	//fire mouse up!
	LocalToGlobal( &lastPt );
	VCF::Point pt( lastPt.h , lastPt.v );
	
	//localizes the coords
	translateFromScreenCoords( &pt );			
	
	Scrollable* scrollable = control_->getScrollable();
	if ( NULL != scrollable ) {
		pt.x_ += scrollable->getHorizontalPosition();
		pt.y_ += scrollable->getVerticalPosition();
	}
	
	Event* mouseUp = new VCF::MouseEvent ( control_, Control::MOUSE_UP,
										   mbmLeftButton,
										   OSXUIUtils::translateKeyMask( mods ), &pt );
	control_->handleEvent( mouseUp );
	mouseUp->free();
			
		
	return result;
}

void OSXControl::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	
}

void OSXControl::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	
}

OSStatus OSXControl::handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	OSStatus result = eventNotHandledErr;
    
	
    OSXEventMsg msg( theEvent, control_ );
    Event* vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );

//	{ kEventClassControl, kEventControlDeactivate },
	
    UInt32 whatHappened = GetEventKind (theEvent);
	TCarbonEvent event( theEvent );
	
	switch ( GetEventClass( theEvent ) )  {	
		case kEventClassControl : {
			switch( whatHappened ) {
				
				case kEventControlTrack : {					
					//do mouse tracking to catch the rest!
					handleControlTrack( theEvent );
					
					result = noErr;
				}
				
				case kEventControlHit: {
					result = ::CallNextEventHandler( nextHandler, theEvent );
				
			
			//		if ( !control_->isDestroying() && (NULL != vcfEvent) ) {
			//			
			//			if ( OSXControl::msNoState == mouseState_ ) {							
			//				control_->handleEvent( vcfEvent );
			//				mouseState_ = OSXControl::msDown;
			//				printf( "kEventControlHit, mouseState_ = OSXControl::msDown\n" );
			//			}
			//			else if ( OSXControl::msDown == mouseState_ ) {
			//				mouseState_ = OSXControl::msUp;
			//				
			//				MouseEvent* tmpEvent = (MouseEvent*)vcfEvent;
			//				
			//				MouseEvent mouseEvent( tmpEvent->getSource(), Control::MOUSE_UP,
			//										tmpEvent->getButtonMask(),
			//										tmpEvent->getKeyMask(),
			//										tmpEvent->getPoint() );
			//										
			//				control_->handleEvent( &mouseEvent );						
			//				
			//				mouseState_ = OSXControl::msNoState;
			//				printf( "kEventControlHit, mouseState_ = OSXControl::msNoState\n" );
			//			}						
			//		}
			//		
							
				}
				break;
				

				case kEventControlDraw : {
					//don't call next event handler here
					result = noErr;
				
					if ( !control_->isDestroying() ) {
												
						GrafPtr port = NULL;										
						CGContextRef context = NULL;
						RgnHandle region = NULL;
						
						event.GetParameter( kEventParamRgnHandle, &region );
						event.GetParameter<CGContextRef>( kEventParamCGContextRef, typeCGContextRef, &context );
						event.GetParameter<GrafPtr>( kEventParamGrafPort, typeGrafPtr, &port );						
						
						::Rect rgnBds;
						GetRegionBounds( region, &rgnBds );						
						
						
						VCF::Rect bounds = control_->getClientBounds();									
						
						VCF::GraphicsContext* ctx = control_->getContext();
						
						WindowRef wnd = GetControlOwner( hiView_ );
						::Rect wndR;
						GetWindowBounds( wnd, kWindowContentRgn, &wndR );
						
						
						HIRect bds;
						//bounds = control_->getBounds();
						
						bds.origin.x = bounds.left_;
						bds.origin.y = bounds.top_;
						bds.size.width = bounds.getWidth();
						bds.size.height = bounds.getHeight();
						HIViewConvertRect( &bds, hiView_, NULL );
						
						bounds.setRect( bds.origin.x,
										bds.origin.y, 
										bds.origin.x + bds.size.width,
										bds.origin.y + bds.size.height );
																						
						ctx->setViewableBounds( bounds );
						
						
						OSXContext* osxCtx =  (OSXContext*)ctx->getPeer();
						
						bounds.setRect( 0, 0, wndR.right-wndR.left, wndR.bottom-wndR.top );
						osxCtx->setCGContext( context, port, bounds );
		
						int gcs = ctx->saveState();
		
						control_->paintBorder( ctx );
		
						control_->paint( ctx );	
						
						ctx->restoreState( gcs );
						
						osxCtx->setCGContext( NULL, 0, bounds );		
	
						
						result = noErr;						
					}
				}
				break;
				
				default : {
                    result = CallNextEventHandler( nextHandler, theEvent );
					
                    if ( !control_->isDestroying() ) {
						if ( NULL != vcfEvent ) {
							control_->handleEvent( vcfEvent );
						}
					}
                }
                break;
			}
		}
		break;
		
		default : {
            result = CallNextEventHandler( nextHandler, theEvent );
        }
        break; 
	}
	
	if ( NULL != vcfEvent ) {
        delete vcfEvent;
    }
	
	return result;
}

	
};

*/

/**
$Id$
*/
