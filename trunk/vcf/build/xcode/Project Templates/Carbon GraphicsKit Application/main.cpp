#include <Carbon/Carbon.h>
#include "vcf/GraphicsKit/GraphicsKit.h"





void paint( WindowRef window )
{
	
	::Rect		r;
	
	SetPortWindowPort( window );
	
	GrafPtr wndPort = GetWindowPort(window);
	SetPort( wndPort );
	
	GetPortBounds(wndPort, &r);
	::SetThemeBackground(kThemeBrushWhite, 32, true);
	EraseRect( &r );
	
		
	VCF::Rect clientBounds( 0, 0, r.right-r.left, r.bottom-r.top );
	
	VCF::GraphicsContext gc(wndPort);
		
	clientBounds.inflate( -10, -10 );
	
	
	gc.rectangle( &clientBounds );
	gc.strokePath();
	
	gc.textBoundedBy( &clientBounds, "Hello World!", true );
}


pascal OSStatus MyWindowEventHandler(
	EventHandlerCallRef	inHandlerCallRef,
	EventRef			inEvent,
	void*				inUserData )
{
#pragma unused( inHandlerCallRef )
	OSStatus			err;
	UInt32				eventClass = GetEventClass( inEvent );
	UInt32				eventKind = GetEventKind( inEvent );
	WindowRef			window = (WindowRef) inUserData;
	UInt32		attributes;
	
	if ( eventClass == kEventClassWindow )	{	
		switch( eventKind ) {
			case kEventWindowDrawContent : {
				
				
				err = ::CallNextEventHandler( inHandlerCallRef, inEvent );
			
				paint( window );
			}
			break;
			
			case kEventWindowDeactivated : case kEventWindowActivated : {
				err = ::CallNextEventHandler( inHandlerCallRef, inEvent );
				paint( window );
			}
			break;
			
			case kEventWindowBoundsChanged : {
				err = GetEventParameter( inEvent, kEventParamAttributes,
										typeUInt32, NULL, sizeof( UInt32 ), NULL, &attributes );
				err = ::CallNextEventHandler( inHandlerCallRef, inEvent );
										
				if ( attributes & kWindowBoundsChangeSizeChanged ) {
					paint( window );
				}							
			}
			break;
		}
	}
	
	
	return err;
}




DEFINE_ONE_SHOT_HANDLER_GETTER( MyWindowEventHandler );







int main(int argc, char* argv[])
{
    WindowRef 		window;
    
	VCF::GraphicsKit::init( argc, argv );
	
	EventTypeSpec	windowEventList[] = {
							{ kEventClassWindow, kEventWindowDrawContent },
							{kEventClassWindow, kEventWindowDeactivated},
							{kEventClassWindow, kEventWindowActivated},
							{kEventClassWindow, kEventWindowBoundsChanged}
							};
		 


    OSStatus		err;

    

	WindowAttributes attrs = 0;
    attrs |=  kWindowCloseBoxAttribute | kWindowFullZoomAttribute | kWindowCollapseBoxAttribute |
                kWindowResizableAttribute | kWindowCloseBoxAttribute | kWindowCompositingAttribute |
                kWindowStandardHandlerAttribute | kWindowLiveResizeAttribute | kWindowInWindowMenuAttribute;


	::Rect bounds = {0,0,0,0};
	bounds.left = 100;
	bounds.top = 100;
	bounds.right = 600;
	bounds.bottom = 600;
	
	err = CreateNewWindow( kDocumentWindowClass, attrs, &bounds, &window );
	
	if ( err != noErr ) {
		return err;
	}
	
	err = InstallWindowEventHandler( window, GetMyWindowEventHandlerUPP(),
			GetEventTypeCount( windowEventList ), windowEventList, window, NULL );
	
	if ( err != noErr ) {
		return err;
	}		
			
    ShowWindow( window );
    
    // Call the event loop
    RunApplicationEventLoop();
	
	VCF::GraphicsKit::terminate();
	
	return err;
}

