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



@interface VCFWindowContentView : NSView
{
	VCF::OSXWindow* wnd;
}
@end

@implementation VCFWindowContentView

- (id)initWithFrame:(NSRect)frameRect
{
	if ((self = [super initWithFrame:frameRect]) != nil) {
		// Add initialization code here
		wnd = NULL;
	}
	return self;
}

- (void)drawRect:(NSRect)rect
{
	if ( NULL != wnd ) {
		wnd->internal_paint(rect);
	}	
}

- (void) setVCFWindow: (id) aWnd
{
	wnd = (VCF::OSXWindow*)aWnd;
}
 
@end

namespace VCF {


OSXWindow::OSXWindow():	
	control_(NULL),
	internalClose_(false),
	currentMouseBtn_(0)
{

}


OSXWindow::OSXWindow( Control* control, Control* owner ):
	control_(control),
	window_(NULL),
	internalClose_(false),
	currentMouseBtn_(0)
{

}

OSXWindow::~OSXWindow()
{

}

/*
EventHandlerUPP OSXWindow::getEventHandlerUPP()
{
	static EventHandlerUPP result = NULL;
	if ( NULL == result ) {
		result = NewEventHandlerUPP( OSXWindow::handleOSXEvents );
	}
	return result;
}

WindowAttributes OSXWindow::getCreationWinAttrs()
{
	return kWindowCloseBoxAttribute | kWindowFullZoomAttribute | kWindowCollapseBoxAttribute |
			  kWindowResizableAttribute | kWindowCloseBoxAttribute | kWindowCompositingAttribute |
			  kWindowStandardHandlerAttribute | kWindowLiveResizeAttribute | kWindowInWindowMenuAttribute;
}

WindowClass OSXWindow::getCreationWinClass()
{
	return kDocumentWindowClass;
}
*/
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
	
	r.size.width = 1;
	r.size.height = 1;
	r.origin.x = 0;
	r.origin.y = 0;
	[contentView initWithFrame:r];
	
	[contentView setVCFWindow: (id)this];
	
	[window_ setContentView: contentView ];
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
	
	[window_ release];
}

String OSXWindow::getText()
{
	VCF::String result;
	//CFStringRef wndTitle = 
		
	CFTextString text;
	text = (CFStringRef) [window_ title];
	//text = wndTitle;
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
	
/*
	OSXRect r = rect;

	SetWindowBounds( windowRef_, kWindowStructureRgn, r );
	
	if ( NULL != mouseTrackRef_ ) {
		ReleaseMouseTrackingRegion( mouseTrackRef_ );
	}
	
	GetWindowBounds( windowRef_, kWindowContentRgn, r );	
	
	::Rect rgnRect = r;
	RgnHandle rgn = NewRgn();
	SetRectRgn( rgn, rgnRect.left, rgnRect.top, rgnRect.right, rgnRect.bottom );
		
	MouseTrackingRegionID id;
	id.signature = VCF_WINDOW_MOUSE_RGN;
	id.id = (SInt32)this;
		
	OSStatus err = CreateMouseTrackingRegion( windowRef_, rgn, NULL, kMouseTrackingOptionsLocalClip,
												  id, this, NULL, &mouseTrackRef_ );
	if ( noErr == err ) {
		RetainMouseTrackingRegion( mouseTrackRef_ );
		err = SetMouseTrackingRegionEnabled( mouseTrackRef_, TRUE );
	}
	
		
	DisposeRgn( rgn );
*/		
	
	/*
	if ( !IsWindowVisible( windowRef_ ) ) {
		//send an artificial size event!
		if ( !control_->isDestroying() ) {
			StringUtils::trace( "Sending artificial size event!" );
			VCF::Size sz( rect->getWidth(), rect->getHeight() );
			ControlEvent event( control_, sz );
							
			control_->handleEvent( &event );
		}						
	}
	*/
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
	
	//GetWindowBounds( windowRef_, kWindowStructureRgn, r );

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
/*
	if ( !visible ) {
		HideWindow( windowRef_ );
	}
	else {
		bool doResize = false;
		if ( !IsWindowVisible( windowRef_ ) ) {
			doResize = true;
		}
		
		ShowWindow( windowRef_ );
	
		if ( doResize ) {
			control_->getContainer()->resizeChildren( NULL );
		}
		repaint( NULL,false );
	}
	*/
}

bool OSXWindow::getVisible()
{
	return  [window_ isVisible] ? true : false ; //IsWindowVisible( windowRef_ ) ? true : false;
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
	//WindowRef wndRef = GetUserFocusWindow();
	return false; //(wndRef == windowRef_) ? true : false;
}

void OSXWindow::setFocused()
{
//	SetUserFocusWindow( windowRef_ );
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

	//HIViewSetNeedsDisplay( getRootControl(), true );

	//InvalWindowRect( windowRef_, r );
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
	//HIViewSetNeedsDisplay( getRootControl(), true );
}

void OSXWindow::translateToScreenCoords( Point* pt )
{
	/*
	WndSwitchPort port(windowRef_);

	::Point point;
	point.h = pt->x_;
	point.v = pt->y_;

	LocalToGlobal( &point );

	pt->x_ = point.h;
	pt->y_ = point.v;
	*/
	
	NSPoint tmp;
	tmp.x = pt->x_;
	tmp.y = pt->y_;
	tmp = [window_ convertBaseToScreen: tmp];
	
	pt->x_ = tmp.x;
	pt->y_ = tmp.y;
}

void OSXWindow::translateFromScreenCoords( Point* pt )
{
	/*
	WndSwitchPort port(windowRef_);

	::Point point;
	point.h = pt->x_;
	point.v = pt->y_;

	GlobalToLocal( &point );

	pt->x_ = point.h;
	pt->y_ = point.v;
	*/
	
	NSPoint tmp;
	tmp.x = pt->x_;
	tmp.y = pt->y_;
	tmp = [window_ convertScreenToBase: tmp];
	
	pt->x_ = tmp.x;
	pt->y_ = tmp.y;
}


Rect OSXWindow::getClientBounds()
{
/*
	::Rect r;
	GetWindowBounds( windowRef_, kWindowContentRgn, &r );

	WndSwitchPort port(windowRef_);

	::Point pt;
	pt.h = r.left;
	pt.v = r.top;

	VCF::Rect result;

	GlobalToLocal(&pt);

	result.left_ = pt.h;
	result.top_ = pt.v;

	pt.h = r.right;
	pt.v = r.bottom;

	GlobalToLocal(&pt);

	result.right_ = pt.h;
	result.bottom_ = pt.v;

*/	
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
	if ( !internalClose_ ){
		internalClose_ = true;
		Application* app = Application::getRunningInstance();
		if ( NULL != app ){
			Window* mainWindow = app->getMainWindow();
			if ( mainWindow == getControl() ){
				//::PostMessage( hwnd_, WM_QUIT, 0, 0 );
			}
		}
	}
	/*
	EventRef closeWindowEvent = NULL;
	
	OSStatus err = CreateEvent( NULL,
	                          kEventClassWindow,
	                          kEventWindowClose,
	                          0,
	                          kEventAttributeUserEvent,
	                          &closeWindowEvent );
	
	err = SetEventParameter( closeWindowEvent, kEventParamDirectObject,
	                         typeWindowRef, sizeof(WindowRef), &windowRef_ );
	//SendEventToEventTarget( closeWindowEvent, GetWindowEventTarget(parent) );	
	//CFRelease( result );
	
	PostEventToQueue( GetCurrentEventQueue(), closeWindowEvent, kEventPriorityStandard );
	*/
}

void OSXWindow::setFrameStyle( const FrameStyleType& frameStyle )
{

}

void OSXWindow::setFrameTopmost( const bool& isTopmost )
{

}

bool OSXWindow::isMaximized()
{
	return false;//IsWindowInStandardState( windowRef_, NULL, NULL ) ? true : false;
}

void OSXWindow::setMaximized( const bool maximised )
{/*
	if ( maximised ) {
		ZoomWindow( windowRef_, inZoomOut, true );
	}
	else {
		ZoomWindow( windowRef_, inZoomIn, false );
	}
	*/
}

bool OSXWindow::isMinimized()
{
	return false; //IsWindowCollapsed( windowRef_ ) ? true : false;
}

void OSXWindow::setMinimized( const bool& minimized )
{
	//CollapseWindow( windowRef_, minimized );
}

void OSXWindow::restore()
{

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
	//Boolean active = IsWindowActive(windowRef_);
	
	return false;//active ? true : false;
}

void OSXWindow::setBorderPath( Path* path )
{
    
}
/*
OSStatus OSXWindow::wndContentViewHandler(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData)
{
	OSXWindow* thisPtr = (OSXWindow*)userData;
	return thisPtr->handleContentViewDraw( nextHandler, theEvent );
}

OSStatus OSXWindow::handleContentViewDraw( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	TCarbonEvent event( theEvent );
	return noErr;
}

void OSXWindow::copyControlsFromWndRef( WindowRef oldWndRef )
{
	ControlRef contentView = getRootControl();
	
	ControlRef oldContentView = NULL;
	HIViewFindByID(HIViewGetRoot(oldWndRef), kHIViewWindowContentID, &oldContentView);
	UInt16 count = 0;
	UInt16 i = 1;
	CountSubControls( oldContentView, &count );
	for (i=1;i<=count;i++ ) {
		ControlRef child;
		OSStatus err = GetIndexedSubControl( oldContentView, 1, &child );
		if ( noErr == err ) {			
			EmbedControl( child, contentView );
			ShowControl( child );
		}
		else {
			printf( "GetIndexedSubControl failed (err: %d) for child # %d (%p) of %d in new content view %p\n",
						err, i, child, count, contentView );
		}
	}						
}
*/

void OSXWindow::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	
}

void OSXWindow::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	
}

void OSXWindow::internal_paint( NSRect r )
{
	NSGraphicsContext* theContext = [NSGraphicsContext currentContext];

	Color* c = this->control_->getColor();
	
	NSColor* backColor = [NSColor colorWithCalibratedRed:c->getRed() 
									green:c->getGreen() 
									blue:c->getBlue() 
									alpha:c->getAlpha()];
									
	
	[backColor setFill];
	
	NSRectFill( r );
}

};//end of namespace VCF


/**
$Id$
*/
