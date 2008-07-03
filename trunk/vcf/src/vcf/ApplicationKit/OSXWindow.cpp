//OSXWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXWindow.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXCursorPeer.h"

@interface VCFWindowDelegate : NSObject
{
@public
	VCF::Window* vcfWnd;	
}
- (void)windowWillClose:(NSNotification *)notification;
- (BOOL)windowShouldClose:(id)window;
- (void)windowDidMiniaturize:(NSNotification *)notification;
- (void)windowDidDeminiaturize:(NSNotification *)notification;
- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)proposedFrame;
- (NSSize)windowWillResize:(NSWindow *)window toSize:(NSSize)proposedFrameSize;
@end


@implementation VCFWindowDelegate

- (NSSize)windowWillResize:(NSWindow *)window toSize:(NSSize)proposedFrameSize
{
	NSSize result = proposedFrameSize;
	
	VCF::Size minSize = vcfWnd->getMinSize();
	VCF::Size maxSize = vcfWnd->getMaxSize();
			
	if ( minSize.width_ > VCF::Control::mmIgnoreMinWidth ) {
		if ( proposedFrameSize.width < minSize.width_ ) {
			result.width = minSize.width_;
		}		
	}
	
	if ( minSize.height_ > VCF::Control::mmIgnoreMinHeight ) {
		if ( proposedFrameSize.height < minSize.height_ ) {
			result.height = minSize.height_;
		}		
	}
	
	if ( maxSize.width_ > VCF::Control::mmIgnoreMaxWidth ) {
		if ( proposedFrameSize.width > maxSize.width_ ) {
			result.width = minSize.width_;
		}		
	}
	
	if ( maxSize.height_ > VCF::Control::mmIgnoreMaxHeight ) {
		if ( proposedFrameSize.height > maxSize.height_ ) {
			result.height = minSize.height_;
		}		
	}
				
	return result;
}


- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)proposedFrame
{
	VCF::WindowEvent e(vcfWnd,WINDOW_EVENT_MAXIMIZE);
	vcfWnd->WindowRestore( &e );
	return YES;
}

- (void)windowDidDeminiaturize:(NSNotification *)notification
{
	VCF::WindowEvent e(vcfWnd,WINDOW_EVENT_RESTORE);
	vcfWnd->WindowRestore( &e );
}

- (void)windowDidMiniaturize:(NSNotification *)notification
{	
	VCF::WindowEvent e(vcfWnd,WINDOW_EVENT_MINIMIZE);
	vcfWnd->WindowMinimize( &e );	
}

- (void)windowWillClose:(NSNotification *)notification
{
	//printf( "windowWillClose called \n" );
	VCF::Application* app = VCF::Application::getRunningInstance();
	if ( app->getMainWindow() == vcfWnd ) {
		
		NSApplication* app = [NSApplication sharedApplication];
		[app stop: app];
	}
}



- (BOOL)windowShouldClose:(id)window
{
	BOOL result = YES;
	
	//printf( "windowShouldClose called \n" );
	
	if ( vcfWnd->isDesigning() ) {
	}
	else {
		if ( vcfWnd->allowClose() ) {
					
			VCF::FrameEvent event( vcfWnd, VCF::Frame::CLOSE_EVENT );
			
			
			vcfWnd->FrameClose( &event );		
		}
		else {
			result = NO;
		}
	}
	
	return result;
}
@end




@interface VCFWindowContentView : VCFControlView
{
	VCF::OSXWindow* wnd;
}
@end

@implementation VCFWindowContentView

- (id)initWithFrame:(NSRect)frameRect
{
	if ((self = [super initWithFrame:frameRect]) != nil) {
		// Add initialization code here
	}
	return self;
}

- (void)drawRect:(NSRect)rect
{
	//printf( "VCFWindowContentView drawRect rect: %d,%d,%d,%d\n", (int)rect.origin.x, (int)rect.origin.y, (int)rect.size.width, (int)rect.size.height );
	if ( NULL != wnd ) {
		wnd->internal_paint(rect);
	}
}

- (void) setVCFWindow: (VCF::OSXWindow*) aWnd
{
	wnd = aWnd;
}
 
- (void)setFrame:(NSRect)rect
{
	[super setFrame:rect];	
}

@end

namespace VCF {


OSXWindow::OSXWindow():	
	OSXControl(NULL),
	internalClose_(false),
	currentMouseBtn_(0)
{

}


OSXWindow::OSXWindow( Control* control, Control* owner ):
	OSXControl(control),
	window_(NULL),
	internalClose_(false),
	currentMouseBtn_(0)
{

}

OSXWindow::~OSXWindow()
{

}

void OSXWindow::create( Control* owningControl )
{
	/*
	WindowAttributes attrs=getCreationWinAttrs();// = kWindowCompositingAttribute | kWindowStandardHandlerAttribute;
	
	::Rect bounds = {0,0,0,0};

	OSStatus err = CreateNewWindow( getCreationWinClass(), attrs, &bounds, &windowRef_ );
	if ( noErr != err ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("CreateNewWindow() failed!") );
	}
	else {
		OSXWindow* thisPtr = this;
		err = SetWindowProperty( windowRef_, 
								VCF_PROPERTY_CREATOR, 
								VCF_PROPERTY_WINDOW_VAL, 
								sizeof(OSXWindow*), 
								&thisPtr );

		if ( noErr != err ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("SetWindowProperty() failed!") );
		}
		
		SetThemeWindowBackground( windowRef_, kThemeBrushSheetBackgroundTransparent, true );

		static EventTypeSpec eventsToHandle[] ={
		                    // { kEventClassWindow, kEventWindowGetIdealSize },
		                    { kEventClassCommand, kEventCommandProcess },
		                    //{ kEventClassCommand, kEventCommandUpdateStatus },
		                    { kEventClassWindow, kEventWindowClose },
		                    { kEventClassWindow, kEventWindowActivated },
		                    { kEventClassWindow, kEventWindowDeactivated },
		                    { kEventClassWindow, kEventWindowFocusAcquired },
		                    { kEventClassWindow, kEventWindowFocusRelinquish },

		                    { kEventClassWindow, kEventWindowDrawContent },
		                    { kEventClassMouse, kEventMouseDown },
		                    { kEventClassMouse, kEventMouseUp },
		                    { kEventClassMouse, kEventMouseMoved },
		                    { kEventClassMouse, kEventMouseDragged },
		                    { kEventClassMouse, kEventMouseEntered },
		                    { kEventClassMouse, kEventMouseExited },
		                    { kEventClassMouse, kEventMouseWheelMoved },
		                    { kEventClassKeyboard, kEventRawKeyDown },
		                    { kEventClassKeyboard, kEventRawKeyUp },
		                    { kEventClassWindow, kEventWindowBoundsChanged } };


		    InstallWindowEventHandler( windowRef_,
		                               OSXWindow::getEventHandlerUPP(),
		                               sizeof(eventsToHandle)/sizeof(eventsToHandle[0]),
		                               eventsToHandle,
		                               this,
		                               &handlerRef_ );
		
				
		static EventTypeSpec contentViewEvents[] ={ { kEventClassControl, kEventControlDraw } };
		
		ControlRef root = getRootControl();
		InstallEventHandler( GetControlEventTarget( root ), 
							OSXWindow::wndContentViewHandler,
							sizeof(contentViewEvents) / sizeof(EventTypeSpec), 
							contentViewEvents, 
							this, 
							&contentViewHandlerRef_ );
		EventHandler* ev = new ClassProcedure1<Event*,Control>( owningControl, &Control::handleEvent );
		UIToolkit::postEvent( ev, new VCF::ComponentEvent( owningControl, Component::COMPONENT_CREATED ), true );		
	}
	*/
	
	this->window_ = [NSWindow alloc];
	NSRect r;
	r.size.width = 1;
	r.size.height = 1;
	r.origin.x = 0;
	r.origin.y = 0;
	
	[window_ initWithContentRect: r 
				styleMask: NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
				backing: NSBackingStoreBuffered
				defer: YES ];
	
	
	VCFWindowContentView* contentView = [VCFWindowContentView alloc];	
	[contentView setAutoresizingMask: (NSViewWidthSizable | NSViewHeightSizable)];
	
	r.size.width = 1;
	r.size.height = 1;
	r.origin.x = 0;
	r.origin.y = 0;
	
	[contentView setVCFWindow: this];
	
	[contentView initWithFrame:r];
	
	OSXControl::setViewForPeer( contentView, this );
	
	view_ = contentView;

	VCFWindowDelegate* wndDelegate = [[VCFWindowDelegate alloc] init];
	wndDelegate->vcfWnd = (Window*)owningControl;
	[window_ setDelegate: wndDelegate ];
	
	
	[window_ setContentView: view_ ];
	[window_ setAcceptsMouseMovedEvents: YES];
}

void OSXWindow::destroyControl()
{
	//StringUtils::trace( "OSXWindow::destroyControl\n" );
	//VCF::ComponentEvent event( control_, Component::COMPONENT_DELETED );

	//control_->handleEvent( &event );

	//DisposeWindow( windowRef_ );
	//StringUtils::trace( Format("windowRef_: %p, destroyed\n") % windowRef_ );

	//DisposeRgn( mouseTrackRgn_ );
	//ReleaseMouseTrackingRegion( mouseTrackRef_ );
	
	//windowRef_ = NULL;
	
	//[window_ release];
}

String OSXWindow::getText()
{
	VCF::String result;
	
	CFTextString text;
	text = (CFStringRef) [window_ title];	
	result = text;
	
	return result;
}

void OSXWindow::setText( const String& text )
{
	CFTextString wndTitle;
	wndTitle = text;
	CFStringRef tmp = wndTitle;
	[window_ setTitle: (NSString*) tmp ];
}

void OSXWindow::setBounds( Rect* rect )
{
	NSRect r;
	r.origin.x = rect->left_;
	r.origin.y = rect->top_;
	r.size.width = rect->getWidth();
	r.size.height = rect->getHeight();
	[window_ setFrame:r display:YES];	
}

bool OSXWindow::beginSetBounds( const uint32& numberOfChildren )
{
	return true;
}

void OSXWindow::endSetBounds()
{

}

Rect OSXWindow::getBounds()
{
	NSRect r = [window_ frame];
	
	VCF::Rect result( r.origin.x, r.origin.y, 
						r.origin.x + r.size.width, 
						r.origin.y + r.size.height );

	return result;
}

void OSXWindow::setVisible( const bool& visible )
{
	if ( !visible ) {
		[window_ orderOut:nil];
	}
	else {
		[window_ makeKeyAndOrderFront:nil];
	}
}

bool OSXWindow::getVisible()
{
	return  [window_ isVisible] ? true : false ;
}

Control* OSXWindow::getControl()
{
	return control_;
}

void OSXWindow::setControl( Control* control )
{
	control_ = control;
}

void OSXWindow::setCursor( Cursor* cursor )
{	
	if (NULL == cursor) {
		return;
	}
	
	OSXCursorPeer *peer = (OSXCursorPeer*)cursor->getPeer();
	
	if (NULL == peer) {
		return;
	}
	
	if (peer->isSystemCursor()){
		//SetThemeCursor(peer->getCursorID());
	}
}

void OSXWindow::setParent( Control* parent )
{
	
}

Control* OSXWindow::getParent()
{
	return NULL;
}

bool OSXWindow::isFocused()
{
	return [window_ isKeyWindow] ? true : false;
}

void OSXWindow::setFocused()
{
//	SetUserFocusWindow( windowRef_ );
	[window_ makeKeyWindow];
}

bool OSXWindow::isEnabled()
{
	return true; //IsWindowActive( windowRef_ ) ? true : false;
}

void OSXWindow::setEnabled( const bool& enabled )
{
	//ActivateWindow( windowRef_, enabled ? TRUE : FALSE );
}

void OSXWindow::setFont( Font* font )
{

}

void OSXWindow::repaint( Rect* repaintRect, const bool& immediately )
{
	OSXRect r;
	if ( NULL == repaintRect ) {
		r = getClientBounds();
	}
	else {
		r = repaintRect;
	}
	
	[window_ display];
}

void OSXWindow::keepMouseEvents()
{

}

void OSXWindow::releaseMouseEvents()
{

}

void OSXWindow::setBorder( Border* border )
{
	//cause the window to repaint itself!!!	
	[window_ display];
}

void OSXWindow::translateToScreenCoords( Point* pt )
{	
	NSPoint tmp;
	tmp.x = pt->x_;
	tmp.y = pt->y_;
	tmp = [window_ convertBaseToScreen: tmp];
	
	pt->x_ = tmp.x;
	pt->y_ = tmp.y;
}

void OSXWindow::translateFromScreenCoords( Point* pt )
{		
	NSPoint tmp;
	tmp.x = pt->x_;
	tmp.y = pt->y_;
	tmp = [window_ convertScreenToBase: tmp];
	
	pt->x_ = tmp.x;
	pt->y_ = tmp.y;
}


Rect OSXWindow::getClientBounds()
{	
	NSView* v = [window_ contentView];
	NSRect r = [v bounds];	
	
	VCF::Rect result( r.origin.x, r.origin.y, 
						r.origin.x + r.size.width, 
						r.origin.y + r.size.height );

	return result;
}

void  OSXWindow::setClientBounds( Rect* bounds )
{
	//OSXRect r = bounds;
	//SetWindowBounds( windowRef_, kWindowContentRgn, r );
}

void OSXWindow::close()
{
	[window_ performClose: window_ ];
}

void OSXWindow::setFrameStyle( const FrameStyleType& frameStyle )
{

}

void OSXWindow::setFrameTopmost( const bool& isTopmost )
{

}

bool OSXWindow::isMaximized()
{
	return [window_ isZoomed] ? true : false;
}

void OSXWindow::setMaximized( const bool maximised )
{	
	[window_ zoom: window_];
}

bool OSXWindow::isMinimized()
{
	return [window_ isMiniaturized] ? true : false;
}

void OSXWindow::setMinimized( const bool& minimized )
{
	if ( minimized ) {
		[window_ miniaturize: window_];
	}
	else {
		[window_ deminiaturize: window_];
	}
}

void OSXWindow::restore()
{
	[window_ deminiaturize: window_];
}

void OSXWindow::setIconImage( Image* icon )
{

}
/*
OSStatus OSXWindow::handleOSXEvent(  EventHandlerCallRef nextHandler, EventRef theEvent )
{
	OSStatus result = eventNotHandledErr;
	
	Event* vcfEvent = NULL;
	

	OSXEventMsg msg( theEvent, control_ );
	//Event* vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );

	UInt32 whatHappened = GetEventKind (theEvent);
	UInt32 attributes = 0;   
	
	if ( GetEventClass( theEvent ) !=  kEventClassMouse ) {
		OSXEventMsg msg( theEvent, control_ );
		vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
	}


	switch ( GetEventClass( theEvent ) ) {
		case kEventClassMouse : {
			::Point mousePos;
			GetEventParameter( theEvent, kEventParamMouseLocation, typeQDPoint, NULL,
			                   sizeof (mousePos), NULL, &mousePos);
			VCF::Point pt( mousePos.h , 
						   mousePos.v );

			switch( whatHappened ) {
				case kEventMouseMoved : {
					
					result = CallNextEventHandler( nextHandler, theEvent );
					
					//try and discover the control this event is over. if 
					//getControlForMouseEvent() returns NULL then use the
					//event for ourselves
					Control* childControl = getControlForMouseEvent( theEvent );
					if ( NULL != childControl && !childControl->isDestroying() ) {
						OSXEventMsg msg( theEvent, childControl );
						vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
		
						childControl->handleEvent( vcfEvent );
					}
					else if ( !control_->isDestroying() ) {
						OSXEventMsg msg( theEvent, control_ );
						vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
						
						control_->handleEvent( vcfEvent );
					}
					
				}
				break;
				
				case kEventMouseDragged : {					
					result = CallNextEventHandler( nextHandler, theEvent );
					
					Control* childControl = getControlForMouseEvent( theEvent );
					if ( NULL != childControl && !childControl->isDestroying() ) {
						OSXEventMsg msg( theEvent, childControl );
						vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
						
						childControl->handleEvent( vcfEvent );
					}
					else if ( !control_->isDestroying() ) {
						OSXEventMsg msg( theEvent, control_ );
						vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
						
						//printf( "WindowRef found for mouse move!\n" );
						control_->handleEvent( vcfEvent );
					}
				}
				break;
				
				case kEventMouseDown : {
					
					EventMouseButton button = kEventMouseButtonPrimary;
					GetEventParameter( theEvent, kEventParamMouseButton, typeMouseButton, NULL,
										sizeof (EventMouseButton), NULL, &button);
								
					currentMouseBtn_ = OSXUIUtils::translateButtonMask( button );
					
					Control* childControl = getControlForMouseEvent( theEvent );
					if ( NULL == childControl && !control_->isDestroying() ) {
						OSXEventMsg msg( theEvent, control_ );
						vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
						
						control_->handleEvent( vcfEvent );
					}
					
					//this starts the mouse tracking if childControl is non-NULL
					result = CallNextEventHandler( nextHandler, theEvent );
				}
				break;
				
				case kEventMouseUp : {
					result = CallNextEventHandler( nextHandler, theEvent );
					
					Control* childControl = getControlForMouseEvent( theEvent );
					if ( NULL == childControl && !control_->isDestroying() ) {
						OSXEventMsg msg( theEvent, control_ );
						vcfEvent = UIToolkit::createEventFromNativeOSEventData( &msg );
						
						control_->handleEvent( vcfEvent );
					}
					currentMouseBtn_ = 0;
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
		

		case kEventClassWindow : {
			switch( whatHappened ) {
				case kEventWindowGetMinimumSize : {
					Control* ctrl = getControl();
					::Point minHeightAndWidth;
					minHeightAndWidth.h = ctrl->getMinWidth(); 
					minHeightAndWidth.v = ctrl->getMinHeight();
					
					SetEventParameter(theEvent,kEventParamDimensions,typeQDPoint,
										sizeof(minHeightAndWidth),&minHeightAndWidth);
				}
				break;
				
				case kEventWindowGetMaximumSize : {
					Control* ctrl = getControl();
					::Point maxHeightAndWidth;
					maxHeightAndWidth.h = ctrl->getMaxWidth(); 
					maxHeightAndWidth.v = ctrl->getMaxHeight();
					
					SetEventParameter(theEvent,kEventParamDimensions,typeQDPoint,
										sizeof(maxHeightAndWidth),&maxHeightAndWidth);
				}
				break;
				
				case kEventWindowClose : {

					result = noErr;//::CallNextEventHandler( nextHandler, theEvent );

					VCF::Window* window = (VCF::Window*)getControl();

					if ( window->allowClose() ) {

						VCF::FrameEvent event( getControl(), Frame::CLOSE_EVENT );


						window->FrameClose( &event );

						if ( false == internalClose_ ){
							//check if the main window is clossing - if it is
							//then close the app !

							Application* app = Application::getRunningInstance();
							if ( NULL != app ){
								Window* mainWindow = app->getMainWindow();
								if ( mainWindow == getControl() ){
									//::PostMessage( hwnd_, WM_QUIT, 0, 0 );
								}
							}
						}

						result = ::CallNextEventHandler( nextHandler, theEvent );

					}
					else {
						result = noErr;
					}
				}
				break;

				case kEventWindowDrawContent: {
					result = ::CallNextEventHandler( nextHandler, theEvent );

					//handleDraw( true, theEvent );
				}
				break;


				case kEventWindowDeactivated: case kEventWindowActivated: {
					result = CallNextEventHandler( nextHandler, theEvent );

					if ( !control_->isDestroying() ) {
						//handleDraw( false, theEvent );

						if ( NULL != vcfEvent ) {
							control_->handleEvent( vcfEvent );
						}
						if ( kEventWindowActivated == whatHappened ) {
							Frame* frame = (Frame*)control_;
							frame->activate();
						}
					}
				}
				break;

				case kEventWindowBoundsChanged: {

					if ( !control_->isDestroying() ) {

						OSStatus err = GetEventParameter( theEvent,
													kEventParamAttributes,
													typeUInt32,
													NULL,
													sizeof( UInt32 ),
													NULL, &attributes );

						if ( err == noErr ) 	{
							if ( attributes & kWindowBoundsChangeSizeChanged ) {
								//handleDraw( false, theEvent );
							}
						}

						result = ::CallNextEventHandler( nextHandler, theEvent );

						if ( NULL != vcfEvent ) {
							control_->handleEvent( vcfEvent );
						}
					}
					else {
						result = ::CallNextEventHandler( nextHandler, theEvent );
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
			if ( !control_->isDestroying() ) {
				if ( NULL != vcfEvent ) {
					control_->handleEvent( vcfEvent );
				}
			}
		}
		break;
	}

	if ( NULL != vcfEvent ) {
		delete vcfEvent;
	}

	return result;
}


OSStatus OSXWindow::handleOSXEvents( EventHandlerCallRef nextHandler, EventRef theEvent, void* userData)
{
	OSXWindow* window = (OSXWindow*)userData;

	return window->handleOSXEvent( nextHandler, theEvent );
}
*/

/*
void internal_handleChildRepaint( Control* control )
{
	Container* container = control->getContainer();
	if ( NULL != container ) {
		Enumerator<Control*>* children = container->getChildren();
		
		while ( children->hasMoreElements() ) {
			Control* child = children->nextElement();
			
			if ( !child->isLightWeight() && child->getVisible() ) {
				
				child->repaint();
			}
		
			internal_handleChildRepaint( child );			
		}
	}
}

OSXWindow* OSXWindow::getWindowFromWindowRef( WindowRef window )
{
	OSXWindow* result = NULL;
	
	if ( noErr != GetWindowProperty( window, VCF_PROPERTY_CREATOR, 
										VCF_PROPERTY_WINDOW_VAL,
										sizeof(result),
										NULL,
										&result ) ) {
		result = NULL;									
	}
	
	return result;
}

Control* OSXWindow::getControlForMouseEvent( EventRef event )
{	
	
				
	Control* result = NULL;
	ControlRef theControl = NULL;
	ControlRef root = getRootControl();
	ControlRef realRoot = HIViewGetRoot(windowRef_);
	
	
	if ( isComposited() ) {
		if ( noErr == HIViewGetViewForMouseEvent( root, event, &theControl ) ) {						
			if ( theControl != root ) {
				OSXControl* controlPeer =  OSXControl::getControlFromControlRef(theControl);
				if ( NULL != controlPeer ) {
					result = controlPeer->getControl();
				}
			}
			else {
				//????
			}
		}
	}
	else {
		//FindControlUnderMouse( 
	}
	
	return result;
}

ControlRef OSXWindow::getRootControl()
{
	ControlRef result = NULL;
	HIViewFindByID(HIViewGetRoot(windowRef_), kHIViewWindowContentID, &result);
	return result;				
}

RgnHandle OSXWindow::determineUnobscuredClientRgn()
{
	//StringUtils::trace( "determineUnobscuredClientRgn()\n" );

	//create a region
	RgnHandle result = NewRgn();

	VCF::Rect currentClientBounds = getClientBounds();


	//set the regions bounds to the entire client are of the window
	SetRectRgn( result, (int)currentClientBounds.left_,
					(int)currentClientBounds.top_,
					(int)currentClientBounds.right_,
					(int)currentClientBounds.bottom_ );




	VCF::Rect bounds;
	RgnHandle childRgn = NewRgn();

	//enumerate through all first level controls
	Container* container = control_->getContainer();
	if ( NULL != container ) {
		Enumerator<Control*>* children = container->getChildren();

		while ( children->hasMoreElements() ) {
			Control* child = children->nextElement();
			//for each child,
			//if child is NOT lightweight, then
			//get it's bounds, and subtract these bounds from the
			//client region r. 
			if ( !child->isLightWeight() ) {
				bounds = child->getBounds();
				control_->translateToScreenCoords( &bounds );
				control_->translateFromScreenCoords( &bounds ); 

				SetRectRgn( childRgn, (int)bounds.left_,
					(int)bounds.top_,
					(int)bounds.right_,
					(int)bounds.bottom_ );

				::Rect r;
				GetRegionBounds( childRgn, &r );
	//StringUtils::traceWithArgs( "childRgn bounds: left: %d, top: %d, right: %d, bottom: %d\n",
	//								r.left, r.top, r.right, r.bottom );

				DiffRgn( result, childRgn, result );
			}
			else {
				//check if the light weight child is a container
				Container* lwContainer = child->getContainer();
				if ( NULL != lwContainer ) {
					Enumerator<Control*>* lwChildren = lwContainer->getChildren();
					while ( lwChildren->hasMoreElements() ) {
						Control* lwChild = lwChildren->nextElement();
						bounds = lwChild->getBounds();
						child->translateToScreenCoords( &bounds );
						child->translateFromScreenCoords( &bounds ); 
						
						SetRectRgn( childRgn, (int)bounds.left_,
									(int)bounds.top_,
									(int)bounds.right_,
									(int)bounds.bottom_ );
						
						DiffRgn( result, childRgn, result );					
					}
				}
			}
		}
	}

	DisposeRgn( childRgn );

	return result;
}
*/

bool OSXWindow::isActiveWindow()
{
	return [window_ isKeyWindow] ? true : false;
}

void OSXWindow::setBorderPath( Path* path )
{
    
}

void OSXWindow::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	
}

void OSXWindow::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	
}

void OSXWindow::internal_paint( NSRect r )
{
	Color* c = this->control_->getColor();
	
	NSColor* backColor = [NSColor colorWithCalibratedRed:c->getRed() 
									green:c->getGreen() 
									blue:c->getBlue() 
									alpha:c->getAlpha()];
									
	
	[backColor setFill];
	
	NSRectFill( r );
	
	NSGraphicsContext* currentCtx = [NSGraphicsContext currentContext];
	CGContextRef cgCtx = (CGContextRef) [currentCtx graphicsPort];
	
	OSXGCRef cgr(cgCtx, r );
	GraphicsContext gc(&cgr);
	control_->paint(&gc);
}

};//end of namespace VCF


/**
$Id$
*/
