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


class OSXControlView : public TView {
public:

	OSXControlView( HIViewRef inControl ):
		TView(inControl), osxControl_(NULL){
		
		VCF::OSXControl::setCurrentCreateHIView( this );
	}
	
	virtual ~OSXControlView() {
	
	}

	virtual UInt32 GetBehaviors() {
		return TView::GetBehaviors() | 
            kControlSupportsEmbedding | kControlSupportsFocus |
            kControlWantsActivate | kControlHandlesTracking |
            kControlGetsFocusOnClick | kControlSupportsClickActivation;
	}

	void setOSXControl( VCF::OSXControl* val ) {
		osxControl_ = val ;
	}
									
	virtual ControlKind GetKind() {
		const ControlKind result = { 'OSXv', 'OSXv' };	
		return result;
	}
	
	virtual OSStatus GetRegion( ControlPartCode inPart, RgnHandle outRgn ) {
		OSStatus			err = noErr;
		TRect				bounds;
		Rect				qdBounds;
		
		if ( inPart == kControlContentMetaPart
				|| inPart == kControlStructureMetaPart
				/* || inPart == kControlOpaqueRegionMetaPart */ )
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
	VCF::OSXControl* osxControl_;
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
	
	{ kEventClassMouse, kEventMouseDown },
	{ kEventClassMouse, kEventMouseUp },
	{ kEventClassMouse, kEventMouseMoved },
	{ kEventClassMouse, kEventMouseDragged },
	{ kEventClassMouse, kEventMouseEntered },
	{ kEventClassMouse, kEventMouseExited },
	{ kEventClassMouse, kEventMouseWheelMoved },
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



TView* OSXControl::currentCreatedView = NULL;




OSXControl::OSXControl( Control* control ):
	hiView_(NULL),
	control_(control),
	handlerRef_(NULL),
	mouseState_(OSXControl::msNoState)
{

}

OSXControl::~OSXControl()
{

}

void OSXControl::setCurrentCreateHIView( TView* view )
{
	static Mutex* currentCreateMtx = NULL;
	
	if ( NULL == currentCreateMtx ) {
		currentCreateMtx = new Mutex();
	}
	
	Lock l(*currentCreateMtx);
	OSXControl::currentCreatedView = view;
}

long OSXControl::getHandleID()
{
	return (long) hiView_->GetViewRef();
}

EventHandlerUPP OSXControl::getEventHandlerUPP()
{
    static EventHandlerUPP result = NULL;
    if ( NULL == result ) {
        result = NewEventHandlerUPP( OSXControl::handleOSXEvents );
    }
    return result;
}

void OSXControl::create( Control* owningControl )
{
	HIViewRef view = NULL;
	TRect bounds(0,0,0,0);
	
	if ( noErr == ViewCreator<OSXControlView>::create( &view, bounds, NULL ) ) {
		hiView_ = OSXControl::getCurrentCreateHIView();
 		OSXControlView* osxView = (OSXControlView*)hiView_;
		osxView->setOSXControl( this );
		control_ = owningControl;
		
		SetControlProperty( hiView_->GetViewRef(), 'vcfa', 'vcfc', sizeof(void*), (void*)control_ );
		
		
		OSStatus err = InstallEventHandler( GetControlEventTarget( hiView_->GetViewRef() ), 
							OSXControl::getEventHandlerUPP(),
							sizeof(osxHIViewEvents) / sizeof(EventTypeSpec), 
							osxHIViewEvents, 
							this, 
							&handlerRef_ );
							
		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("InstallEventHandler failed for OSXControlView!") );
		}
		
		
        
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("OSXControlView failed to be created!") );
	}	
}

void OSXControl::destroyControl()
{

}


void OSXControl::setBounds( Rect* rect )
{
	TRect r( rect->left_, rect->top_, rect->getWidth(), rect->getHeight() );	
	HIViewSetFrame( hiView_->GetViewRef(), r );
}

bool OSXControl::beginSetBounds( const ulong32& numberOfChildren )
{
	return true;
}

void OSXControl::endSetBounds()
{

}

Rect OSXControl::getBounds()
{
	Rect result;
	
	TRect r = hiView_->Frame();
	
	result.setRect( r.origin.x, r.origin.y, r.origin.x + r.size.width, r.origin.y + r.size.height ); 
	
	return result;
}

void OSXControl::setVisible( const bool& visible )
{
	if ( visible ) {
		hiView_->Show();
	}
	else {
		hiView_->Hide();
	}
}

bool OSXControl::getVisible()
{
	return hiView_->IsVisible() ? true : false;
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

}

void OSXControl::setParent( Control* parent )
{
	Window* windowParent = NULL;
	
	if ( parent->isLightWeight() ) {
		OSXLightweightControl* lwPeer = (OSXLightweightControl*) parent->getPeer();
		
		windowParent = dynamic_cast<Window*>(lwPeer->getHeavyWeightParent());
	}
	else {
		windowParent = dynamic_cast<Window*>(parent);
	}
	
	
	if ( NULL != windowParent ) {
 		WindowRef wndRef = (WindowRef)parent->getPeer()->getHandleID();
		ControlRef root = NULL;
		GetRootControl( wndRef, &root );
		HIViewAddSubview( root, hiView_->GetViewRef() );		
	}
	else {
		ControlRef parentControlRef = (ControlRef)parent->getPeer()->getHandleID();
		OSStatus err = HIViewAddSubview( parentControlRef, hiView_->GetViewRef() );
		if ( err != noErr ) {
			StringUtils::traceWithArgs( "HIViewAddSubview failed, err: %d\n", err );
		}
	}
}

Control* OSXControl::getParent()
{
	Control* result = NULL;
	HIViewRef parentRef = HIViewGetSuperview( hiView_->GetViewRef() );	
	
	void* ptr = NULL;
	OSStatus err = GetControlProperty( parentRef, 'vcfa', 'vcfc', sizeof(void*), NULL, &ptr );
	if ( err == noErr ) {
		result = (VCF::Control*)ptr;
	}	
	return result;
}

bool OSXControl::isFocused()
{
	WindowRef wnd = hiView_->GetOwner();
	ControlRef focusedControl = NULL;
	GetKeyboardFocus( wnd, &focusedControl );	
	
	return ( hiView_->GetViewRef() == focusedControl ) ? true : false;
}

void OSXControl::setFocused()
{
    EventModifiers mods = 0;
	HIViewAdvanceFocus( hiView_->GetViewRef(), mods );    
}

bool OSXControl::isEnabled()
{
	return hiView_->IsEnabled() ? true : false;
}

void OSXControl::setEnabled( const bool& enabled )
{
	if ( enabled ) {
		EnableControl( hiView_->GetViewRef() );
	}
	else {
		DisableControl( hiView_->GetViewRef() );
	}
}

void OSXControl::setFont( Font* font )
{

}

void OSXControl::repaint( Rect* repaintRect=NULL )
{
	hiView_->Invalidate();
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
	
	HIViewConvertPoint( &tmpPt, hiView_->GetViewRef(), NULL );
	::Rect r;
	GetWindowBounds( hiView_->GetOwner(), kWindowStructureRgn, &r );
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
	GetWindowBounds( hiView_->GetOwner(), kWindowStructureRgn, &r );
	tmpPt.x -= r.left;
	tmpPt.y -= r.top;
	
	HIViewConvertPoint( &tmpPt, NULL, hiView_->GetViewRef() );	
	
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
				
				case kEventControlHitTest: {
					result = ::CallNextEventHandler( nextHandler, theEvent );
				/*
					HIPoint where;
					ControlPartCode part;
					
					result = noErr;//::CallNextEventHandler( nextHandler, theEvent );
					event.GetParameter<HIPoint>( kEventParamMouseLocation, typeHIPoint, &where );
					//part = HitTest( where );
					if ( CGRectContainsPoint( hiView_->Bounds(), where ) ) {
						part = 1;
					}
					else {
						part = kControlNoPart;
					}
					event.SetParameter<ControlPartCode>( kEventParamControlPart, typeControlPartCode, part );
					
					printf( "\n\nkEventControlHitTest where: %0.3f,%0.3f, part: %d, class: %s\n",
												where.x, where.y, part, control_->getClassName().ansi_c_str() );
												
					if ( !control_->isDestroying() ) {
					
							
						if ( NULL != vcfEvent ) {
							control_->handleEvent( vcfEvent );
						}
					}
					*/		
				}
				break;
				
				case kEventControlTrack : {
					printf( "kEventControlTrack\n" );
					result = ::CallNextEventHandler( nextHandler, theEvent );
				}
				
				case kEventControlHit: {
					result = ::CallNextEventHandler( nextHandler, theEvent );
				
					/*									
					if ( !control_->isDestroying() && (NULL != vcfEvent) ) {
						
						if ( OSXControl::msNoState == mouseState_ ) {							
							control_->handleEvent( vcfEvent );
							mouseState_ = OSXControl::msDown;
							printf( "kEventControlHit, mouseState_ = OSXControl::msDown\n" );
						}
						else if ( OSXControl::msDown == mouseState_ ) {
							mouseState_ = OSXControl::msUp;
							
							MouseEvent* tmpEvent = (MouseEvent*)vcfEvent;
							
							MouseEvent mouseEvent( tmpEvent->getSource(), Control::MOUSE_UP,
													tmpEvent->getButtonMask(),
													tmpEvent->getKeyMask(),
													tmpEvent->getPoint() );
													
							control_->handleEvent( &mouseEvent );						
							
							mouseState_ = OSXControl::msNoState;
							printf( "kEventControlHit, mouseState_ = OSXControl::msNoState\n" );
						}						
					}
					*/
							
				}
				break;
				/*
				case kEventMouseDown : {
					HIPoint where;
					result = ::CallNextEventHandler( nextHandler, theEvent );
					event.GetParameter<HIPoint>( kEventParamMouseLocation, typeHIPoint, &where );
					
					printf( "kEventMouseDown where: %0.3f,%0.3f, class: %s\n",
												where.x, where.y, control_->getClassName().ansi_c_str() );
												
				}
				break;
				
				case kEventMouseMoved : {
					HIPoint where;
					result = ::CallNextEventHandler( nextHandler, theEvent );
					event.GetParameter<HIPoint>( kEventParamMouseLocation, typeHIPoint, &where );
					
					printf( "kEventMouseMoved where: %0.3f,%0.3f, class: %s\n",
												where.x, where.y, control_->getClassName().ansi_c_str() );
												
				}
				break;
				
				case kEventMouseUp : {
					HIPoint where;
					result = ::CallNextEventHandler( nextHandler, theEvent );
					event.GetParameter<HIPoint>( kEventParamMouseLocation, typeHIPoint, &where );
					
					printf( "kEventMouseUp where: %0.3f,%0.3f, class: %s\n",
												where.x, where.y, control_->getClassName().ansi_c_str() );
												
				}
				break;
				*/
				
                case kEventControlSetFocusPart : {
                    result = ::CallNextEventHandler( nextHandler, theEvent );
                    
                    ControlPartCode		desiredFocus;
					Boolean				focusEverything;
					ControlPartCode		actualFocus;
						
                    event.GetParameter<ControlPartCode>( kEventParamControlPart, typeControlPartCode, &desiredFocus ); 
                    
                    if ( !control_->isDestroying() ) {
					
							
						if ( NULL != vcfEvent ) {
							control_->handleEvent( vcfEvent );
						}
					}
                    
                }
                break;
                
				case kEventControlActivate : {
					result = ::CallNextEventHandler( nextHandler, theEvent ); 
					
					hiView_->Invalidate();					
					
					if ( !control_->isDestroying() ) {
					
							
						if ( NULL != vcfEvent ) {
							control_->handleEvent( vcfEvent );
						}
					}
				}
				break;

				case kEventControlDraw : {
					result = noErr;//::CallNextEventHandler( nextHandler, theEvent ); 
				
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
						
						WindowRef wnd = hiView_->GetOwner();
						::Rect wndR;
						GetWindowBounds( wnd, kWindowContentRgn, &wndR );
						
						
						HIRect bds;
						//bounds = control_->getBounds();
						
						bds.origin.x = bounds.left_;
						bds.origin.y = bounds.top_;
						bds.size.width = bounds.getWidth();
						bds.size.height = bounds.getHeight();
						HIViewConvertRect( &bds, hiView_->GetViewRef(), NULL );
						
						bounds.setRect( bds.origin.x,
										bds.origin.y, 
										bds.origin.x + bds.size.width,
										bds.origin.y + bds.size.height );
																						
						ctx->setViewableBounds( bounds );
						
						OSXContext* osxCtx =  (OSXContext*)ctx->getPeer();
						
						bounds.setRect( 0, 0, wndR.right-wndR.left, wndR.bottom-wndR.top );
						osxCtx->setCGContext( context, port, bounds );
		
						control_->paint( ctx );	
						
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



/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.11.2.3  2004/07/09 02:01:28  ddiego
*more osx updates
*
*Revision 1.1.2.11.2.2  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.11.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.11  2004/06/07 03:07:07  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.1.2.9  2004/05/31 22:24:52  ddiego
*OSX code for handling focus events
*
*Revision 1.1.2.6  2004/05/23 14:11:59  ddiego
*osx updates
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.11.2.3  2004/07/09 02:01:28  ddiego
*more osx updates
*
*Revision 1.1.2.11.2.2  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.11.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.11  2004/06/07 03:07:07  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.1.2.9  2004/05/31 22:24:52  ddiego
*OSX code for handling focus events
*
*Revision 1.1.2.8  2004/05/31 19:42:52  ddiego
*more osx updates
*
*Revision 1.1.2.7  2004/05/31 13:20:57  ddiego
*more osx updates
*
*Revision 1.1.2.6  2004/05/23 14:11:59  ddiego
*osx updates
*
*Revision 1.1.2.5  2004/05/16 05:31:06  ddiego
*OSX code updates. Add basics for custom control peers.
*
*Revision 1.1.2.4  2004/05/16 02:39:01  ddiego
*OSX code updates
*
*
*/
