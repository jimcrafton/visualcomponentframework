//OSXButton.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXButton.h"
#include "vcf/ApplicationKit/CommandButton.h"


using namespace VCF;


OSXButton::OSXButton( CommandButton* control ):
	OSXControl( control ),
	commandButton_(control)
{

}

OSXButton::~OSXButton()
{

}
	
Image* OSXButton::getImage()
{
	return NULL;
}
		
void OSXButton::setImage( Image* image )
{

}
		
ButtonState OSXButton::getState()
{
	state_.setEnabled( IsControlEnabled( hiView_ ) ? true : false );
	state_.setActive( IsControlActive( hiView_ ) ? true : false );
	state_.setFocused( isFocused() ? true : false );
	
	return state_;
}
	
void OSXButton::create( Control* owningControl )
{
	::Rect bounds = {0,0,0,0};
	
		
	if ( noErr == CreatePushButtonControl( NULL, &bounds, CFSTR(""), &hiView_ ) ) {
		
		control_ = owningControl;
		OSXControl* thisPtr = this;
		SetControlProperty( hiView_, 
							VCF_PROPERTY_CREATOR, 
							VCF_PROPERTY_CONTROL_VAL, 
							sizeof(thisPtr), 
							&thisPtr );
							
		SetControlCommandID( hiView_, 'OKBN' );
		OSStatus err = OSXControl::installStdControlHandler();
							
		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("InstallEventHandler failed for OSXButton!") );
		}
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("OSXButton failed to be created!") );
	}
}
	
String OSXButton::getText()
{
	String result;
	//Str255 title;
	//GetControlTitle( hiView_, title );
	
	
	CFStringRef tmp;
	OSStatus err = CopyControlTitleAsCFString( hiView_, &tmp );	
	if ( err != noErr ) {
		printf( "CopyControlTitleAsCFString() failed, err: %d\n", err );
	}
	CFTextString title(tmp);
	CFRelease( tmp );
	result = title;
	return result;
}

void OSXButton::setText( const String& text )
{	
	CFTextString tmp(text);
	
	OSStatus err = SetControlTitleWithCFString( hiView_, tmp );
	if ( err != noErr ) {
		printf( "SetControlTitleWithCFString() failed, err: %d\n", err );
	}
}
	
OSStatus OSXButton::handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	OSStatus result = eventNotHandledErr;
	
    UInt32 whatHappened = GetEventKind (theEvent);
	TCarbonEvent event( theEvent );
	
	switch ( GetEventClass( theEvent ) )  {
		case kEventClassCommand : {
			switch( whatHappened ) {
				case kEventCommandProcess : {
					printf( "kEventCommandProcess\n" );
				}
				break;
			}
		}
		break;
		 
		case kEventClassControl : {
			switch( whatHappened ) {
				
			
				case kEventControlHitTest : {
				
					result = ::CallNextEventHandler( nextHandler, theEvent );
					handleWrappedControlHitTest( theEvent );
				
					ControlPartCode part;				   
					GetEventParameter( theEvent, kEventParamControlPart, typeControlPartCode, NULL,
										sizeof (part), NULL, &part);	
					if ( OSXControl::msDown == mouseState_ ) {					
						state_.setPressed( (part != kControlNoPart) ? true : false );
					}
				}
				break;
				
				
				case kEventControlTrack : {					
					//handle mouse down event here
					
					if ( !control_->isDestroying() ) {					
						handleWrappedControlTrack( theEvent );												
					}
					
					result = ::CallNextEventHandler( nextHandler, theEvent );
					
					if ( !control_->isDestroying() ) {					
						handleWrappedControlTrackDone( theEvent );
						
						VCF::Rect bounds = control_->getClientBounds();
						VCF::Point pt( lastMousePt_.h , lastMousePt_.v );
						if ( bounds.containsPt( &pt ) ) {
							commandButton_->click();
						}
						
						state_.setPressed( false );
					}
				}
				

				case kEventControlDraw : {
					result = noErr;//::CallNextEventHandler( nextHandler, theEvent );
					//break;
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
					}
				}
				break;
				
				default : {
                    result = OSXControl::handleOSXEvent( nextHandler, theEvent );
                }
                break;
			}
		}
		break;
		
		default : {
            result = OSXControl::handleOSXEvent( nextHandler, theEvent );
        }
        break; 
	}	
	
	return result;
	//return OSXControl::handleOSXEvent( nextHandler, theEvent );
}
