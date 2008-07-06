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
	//state_.setEnabled( IsControlEnabled( hiView_ ) ? true : false );
	//state_.setActive( IsControlActive( hiView_ ) ? true : false );
	//state_.setFocused( isFocused() ? true : false );
	
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
