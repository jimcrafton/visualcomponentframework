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


VCF::uint32 translateButtonMask( NSEvent* event )
{
	VCF::uint32 result = 0;
	
	NSUInteger flags = [event modifierFlags];
	
	if ( flags && kEventMouseButtonPrimary ) {
		result |= VCF::mbmLeftButton;
	}
	
	if ( flags && kEventMouseButtonSecondary ) {
		result |= VCF::mbmRightButton;
	}
	
	if ( flags && kEventMouseButtonTertiary ) {
		result |= VCF::mbmMiddleButton;
	}
	
	return result;
}

VCF::uint32 translateKeyMask( NSEvent* event )
{
    VCF::uint32 result = 0;
	
	NSUInteger flags = [event modifierFlags];
	
    if ( flags & NSShiftKeyMask  ) {
        result |= VCF::kmShift;
    }
	
    if ( flags & NSAlternateKeyMask ) {
        result |= VCF::kmAlt;
    }
	
	if ( flags & NSCommandKeyMask ) {
        result |= VCF::kmCtrl;
    }
	
    if ( flags &  NSControlKeyMask  ) {
        result |= VCF::kmCtrl;
    }
    return result;
}





@implementation VCFControlView

- (BOOL)isFlipped
{
	return YES;
}

- (id)initWithFrame:(NSRect)frameRect
{
	if ((self = [super initWithFrame:frameRect]) != nil) {
		// Add initialization code here		
	}
	return self;
}

- (void)drawRect:(NSRect)rect
{
	VCF::OSXControl* peer = VCF::OSXControl::getPeerForView( self );
	
	if ( NULL != peer ) {		
		peer->internal_paint( rect );
	}	
}
 
- (void)setFrame:(NSRect)rect
{
	[super setFrame:rect];
	
	VCF::OSXControl::handleSetFrame( self, rect );
}

- (void)mouseDown:(NSEvent *)theEvent
{
	[super mouseDown:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
	
}

- (void)mouseUp:(NSEvent *)theEvent
{
	[super mouseUp:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );	
}


- (void)rightMouseDown:(NSEvent *)theEvent
{
	[super rightMouseDown:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
	[super rightMouseUp:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
}


- (void)mouseMoved:(NSEvent *)theEvent
{
	[super mouseMoved:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
}


@end


/*
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

	
};

*/



namespace VCF {

typedef std::map<NSView*,OSXControl*> ViewControlMap;
static ViewControlMap viewControlMap;

OSXControl* OSXControl::getPeerForView( NSView* view )
{
	OSXControl* result = NULL;
	ViewControlMap::iterator found = viewControlMap.find( view );
	if ( found != viewControlMap.end() ) {
		result = found->second;
	}
	return result;
}

void OSXControl::setViewForPeer( NSView* view, OSXControl* peer )
{
	viewControlMap[ view ] = peer;
}

OSXControl::OSXControl( Control* control ):
	control_(control),
	view_(NULL)
{

}

OSXControl::~OSXControl()
{

}

OSHandleID OSXControl::getHandleID()
{
	return (OSHandleID) view_;
}

void OSXControl::create( Control* owningControl )
{
	VCF_ASSERT( view_ != NULL );	
	OSXControl::setViewForPeer( view_, this );
}

void OSXControl::destroyControl()
{
	ViewControlMap::iterator found = viewControlMap.find( view_ );
	if ( found != viewControlMap.end() ) {
		viewControlMap.erase( found );
	}
}

void OSXControl::setBounds( Rect* rect )
{
	NSRect frame;
	frame.origin.x = rect->left_;
	frame.origin.y = rect->top_;
	frame.size.width = rect->getWidth();
	frame.size.height = rect->getHeight();
	[view_ setFrame:frame];
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
	NSRect frame = [view_ frame];
	return Rect( frame.origin.x, frame.origin.y, 
				frame.origin.x + frame.size.width,
				frame.origin.y + frame.size.height );
}

void OSXControl::setVisible( const bool& visible )
{
	[view_ setHidden: visible ? NO : YES ];
}

bool OSXControl::getVisible()
{
	return [view_ isHidden] ? false : true;
}

Control* OSXControl::getControl()
{
	return control_;
}

void OSXControl::setControl( Control* control )
{
	control_ = control;
}

void OSXControl::setCursor( Cursor* cursor )
{

}

void OSXControl::setParent( Control* parent )
{
	if ( NULL != parent ) {
		OSXControl* parentPeer = (OSXControl*) parent->getPeer();
		[parentPeer->view_ addSubview: view_ ];
	}
}

Control* OSXControl::getParent()
{
	Control* result = NULL;
	NSView* parentView = [view_ superview];
	
	OSXControl* osxCtrl = OSXControl::getPeerForView( parentView );
	if ( NULL != osxCtrl ) {
		result = osxCtrl->control_;
	}
	
	return result;
}

bool OSXControl::isFocused()
{
	NSWindow* wnd = [view_ window];
	return view_ == [wnd firstResponder];
}

void OSXControl::setFocused()
{
	NSWindow* wnd = [view_ window];
	[wnd makeFirstResponder:view_];
}

bool OSXControl::isEnabled()
{
	return true;
}

void OSXControl::setEnabled( const bool& enabled )
{

}

void OSXControl::setFont( Font* font )
{

}

void OSXControl::repaint( Rect* repaintRect, const bool& immediately )
{
	if ( repaintRect ) {
		NSRect r;
		r.origin.x = repaintRect->left_;
		r.origin.y = repaintRect->top_;
		r.size.width = repaintRect->getWidth();
		r.size.height = repaintRect->getHeight();
		[view_ displayRect:r];
	}
	else {
		[view_ display];
	}
}
	
void OSXControl::keepMouseEvents()
{

}

void OSXControl::releaseMouseEvents()
{

}

void OSXControl::translateToScreenCoords( Point* pt )
{
	NSPoint localPt;
	localPt.x = pt->x_;
	localPt.y = pt->y_;
	NSPoint screenPt = [view_ convertPoint: localPt toView:nil];
	pt->x_ = screenPt.x;
	pt->y_ = screenPt.y;
}

void OSXControl::translateFromScreenCoords( Point* pt )
{
	NSPoint screenPt;
	screenPt.x = pt->x_;
	screenPt.y = pt->y_;
	NSPoint localPt = [view_ convertPoint: screenPt fromView:nil];
	pt->x_ = localPt.x;
	pt->y_ = localPt.y;
}
	
void OSXControl::setBorder( Border* border )
{
	[view_ display];
}
	
void OSXControl::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{

}
	
void OSXControl::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{

}
	
void OSXControl::internal_paint( const NSRect& r )
{
	NSGraphicsContext* currentCtx = [NSGraphicsContext currentContext];
	CGContextRef cgCtx = (CGContextRef) [currentCtx graphicsPort];
	
	OSXGCRef cgr(cgCtx, r );
	GraphicsContext gc(&cgr);
	
	control_->paint( &gc );
}


void OSXControl::handleEventForView( NSView* view, NSEvent* event )
{
	VCF::OSXControl* peer = VCF::OSXControl::getPeerForView( view );
	peer->doEventForView( view, event );
}

void OSXControl::handleSetFrame( NSView* view, const NSRect& rect )
{
	VCF::OSXControl* peer = VCF::OSXControl::getPeerForView( view );
	peer->doSetFrame( view, rect );
}
	
void OSXControl::doEventForView( NSView* view, NSEvent* event )
{
	VCF::Control* control = getControl();
		
	switch ( [event type] ) {
		case NSRightMouseDown: case NSLeftMouseDown: { 
			VCF::uint32 mouseButton = translateButtonMask(event); 
			NSPoint location = [event locationInWindow];
			NSPoint local = [view convertPoint:location fromView:nil];
			VCF::Point pt(local.x, local.y);
			
			VCF::MouseEvent me( control, VCF::Control::MOUSE_DOWN,mouseButton,
														translateKeyMask( event ), &pt );
														
			control->handleEvent( &me );
		}
		break;
		
		case NSRightMouseUp: case NSLeftMouseUp: { 
			VCF::uint32 mouseButton = translateButtonMask(event); 
			NSPoint location = [event locationInWindow];
			NSPoint local = [view convertPoint:location fromView:nil];
			VCF::Point pt(local.x, local.y);
			
			VCF::MouseEvent me( control, VCF::Control::MOUSE_UP,mouseButton,
														translateKeyMask( event ), &pt );
														
			control->handleEvent( &me );
		}
		break;
		
		case NSMouseMoved:  { 
			
			VCF::Control* control = getControl();
	
			NSPoint location = [event locationInWindow];
			NSPoint local = [view convertPoint:location fromView:nil];
			VCF::Point pt(local.x, local.y);
			
			
			VCF::MouseEvent me( control, VCF::Control::MOUSE_MOVE,translateButtonMask(event),
											translateKeyMask(event), &pt );
											
			control->handleEvent( &me );
		}
		break;
		
	}
}

void OSXControl::doSetFrame( NSView* view, const NSRect& rect )
{
	VCF::Control* control = getControl();
	
	VCF::Size sz( rect.size.width, rect.size.height );
	VCF::ControlEvent e( control, sz );
	control->handleEvent( &e );
	
	
	VCF::ControlEvent e2( control, VCF::Point(rect.origin.x,rect.origin.y) );
	control->handleEvent( &e2 );
}
	


};


/**
$Id$
*/
