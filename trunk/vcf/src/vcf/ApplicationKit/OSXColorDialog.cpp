//OSXColorDialog.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXColorDialog.h"

@interface OSXColorDialogDelegate : NSObject 
{
	BOOL closed_;
	
}
- (id)init;
- (BOOL)windowShouldClose:(id)sender;
- (BOOL)isClosed;
@end

@implementation OSXColorDialogDelegate

- (id)init
{
    [super init];
    closed_ = NO;

    return self;
}

- (BOOL)windowShouldClose:(id)sender
{
    closed_ = YES;
    
    [NSApp abortModal];
    [NSApp stopModal];
    return YES;
}

- (BOOL)isClosed
{
    return closed_;
}

@end


namespace VCF {

	
OSXColorDialog::OSXColorDialog( Control* owner )
{

}

OSXColorDialog::~OSXColorDialog()
{

}

Color* OSXColorDialog::getSelectedColor()
{
	return &color_;
}

void OSXColorDialog::setSelectedColor( Color* selectedColor )
{
	color_ = *selectedColor;
}

void OSXColorDialog::setTitle( const String& title )
{
	title_ = title;
}

bool OSXColorDialog::execute()
{
	bool result = true;
	
	NSColorPanel* panel = [ NSColorPanel sharedColorPanel];
	OSXColorDialogDelegate* del = [[OSXColorDialogDelegate alloc] init];
	[panel setDelegate: del];
	NSColor* color = [NSColor colorWithCalibratedRed:color_.getRed() green: color_.getGreen()
						blue:color_.getBlue() alpha:color_.getAlpha() ];
	[panel setColor: color];
	
	
	NSModalSession session = [NSApp beginModalSessionForWindow:panel];
	while (true) {
		[NSApp runModalSession:session];
		
		//are done? Yes, if the color dialog was closed
		if ([del isClosed])
			break;
	}
	[NSApp endModalSession:session];
	
	[del release];
	
	NSColor* panelColor = [panel color];
	color_.setRed( [panelColor redComponent] );
	color_.setGreen( [panelColor greenComponent] );
	color_.setBlue( [panelColor blueComponent] );
	color_.setAlpha( [panelColor alphaComponent] );
	
	return result;
}



};


/**
$Id$
*/
