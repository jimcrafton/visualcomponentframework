//OSXButton.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXButton.h"
#include "vcf/ApplicationKit/CommandButton.h"


using namespace VCF;


@interface VCFButton : NSButton
{

}

@end



@implementation VCFButton
- (void)buttonAction: (id)sender
{
	VCF::OSXControl* peer = VCF::OSXControl::getPeerForView( self );
	
	VCF::CommandButton* btn = (VCF::CommandButton*)peer->getControl();
	if ( !btn->isDesigning() ) {
		btn->click();
		
		Frame* frame = btn->getParentFrame();
		Dialog* dlg = dynamic_cast<Dialog*> (frame);
		if ( NULL != dlg ) {
			if ( dlg->isSheetModal() ) {
				NSWindow* modalWnd = (NSWindow*) dlg->getPeer()->getHandleID();
				if ( nil != modalWnd ) {
					[NSApp endSheet:modalWnd];
				}
			}
			else {
				NSInteger code = NSRunStoppedResponse;
				
				if ( btn->getCommandType() != BC_NONE ) {
					switch ( btn->getCommandType() ) {
						case BC_OK : {
							code = UIToolkit::mrOK;
						}
						break;
							
						case BC_CANCEL : {
							code = UIToolkit::mrCancel;
						}
						break;
						
						case BC_YES : {
							code = UIToolkit::mrYes;
						}
						break;	
						
							
						case BC_NO : {
							code = UIToolkit::mrNo;
						}
							break;
							
						case BC_MAYBE : {
//							code = UIToolkit::mrOK;
						}
							break;
							
						case BC_HELP : {
							code = UIToolkit::mrOK;
						}
							break;
							
						case BC_IGNORE : {
							code = UIToolkit::mrIgnore;
						}
							break;
							
						case BC_RETRY : {
							code = UIToolkit::mrRetry;
						}
							break;
							
						case BC_ABORT : {
							code = UIToolkit::mrAbort;
						}
							break;							
					}
					
					code = (NSInteger) btn->getCommandType();
				}
				
				[NSApp stopModalWithCode:code ];
			}
		}
	}
}

- (BOOL)isFlipped
{
	return YES;
}


- (void)drawRect:(NSRect)rect
{
	[super drawRect:rect];
	
	VCF::OSXControl* peer = VCF::OSXControl::getPeerForView( self );
	
	if ( NULL != peer ) {		
		//peer->internal_paint( rect );
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
	state_.setFocused( isFocused() ? true : false );
	
	NSWindow* wnd = [view_ window];
	state_.setActive( [wnd isKeyWindow] ? true : false );
	NSControl* ctrl = (NSControl*)view_;
	state_.setEnabled( [ctrl isEnabled] ? true : false );
	
	return state_;
}
	
void OSXButton::create( Control* owningControl )
{
	NSRect r;
	r.origin.x = 0;
	r.origin.y = 0;
	r.size.width = 1;
	r.size.height = 1;	
	
	view_ = [[VCFButton alloc] initWithFrame:r];
	NSButton* btn = (NSButton*)view_;
	
	[btn setTarget: btn];
	[btn setAction: @selector(buttonAction:)];
		
		
	[btn setButtonType:NSMomentaryPushButton ];
	[btn setBezelStyle: NSRoundedBezelStyle];
	//[btn setBordered:YES];
	
	OSXControl::create( owningControl );		
}
	
String OSXButton::getText()
{
	String result;
	
	NSButton* btn = (NSButton*)view_;
		
	CFTextString text;
	text = (CFStringRef) [btn title];	
	result = text;
	
	return result;
}

void OSXButton::setText( const String& text )
{	
	CFTextString tmp(text);
	CFStringRef t = tmp;
	NSButton* btn = (NSButton*)view_;
	[btn setTitle: (NSString*) t ];
}
	

/**
$Id$
*/
