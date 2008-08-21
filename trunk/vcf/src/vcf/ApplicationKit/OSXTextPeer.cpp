//OSXTextPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXTextPeer.h"
#include "vcf/FoundationKit/Dictionary.h"

namespace VCF {


OSXTextPeer::OSXTextPeer( const bool& autoWordWrap, const bool& multiLined ):
	textStorage_(nil),
	layoutMgr_(nil),
	container_(nil)
{
	textStorage_ = [[NSTextStorage alloc] initWithString:@""];
	
	layoutMgr_ = [[NSLayoutManager alloc] init];
	container_ = [[NSTextContainer alloc] init];
	[layoutMgr_ addTextContainer:container_];
	[container_ release];
	[textStorage_ addLayoutManager:layoutMgr_];
	[layoutMgr_ release];
	
}

OSXTextPeer::OSXTextPeer():
	textStorage_(nil),
	layoutMgr_(nil),
	container_(nil)
{
	textStorage_ = [[NSTextStorage alloc] initWithString:@""];
	
	layoutMgr_ = [[NSLayoutManager alloc] init];
	container_ = [[NSTextContainer alloc] init];
	[layoutMgr_ addTextContainer:container_];
	[container_ release];
	[textStorage_ addLayoutManager:layoutMgr_];
	[layoutMgr_ release];
}

OSXTextPeer::~OSXTextPeer()
{
	[textStorage_ release];
}


OSHandleID OSXTextPeer::getTextObjectHandle()
{
	return (OSHandleID)textStorage_;
}

//storage
void OSXTextPeer::insertText( unsigned int start, const String& text )
{
	NSMutableString* str = [textStorage_ mutableString];
	[str insertString: [NSString stringWithCharacters:text.c_str() length:text.size()]  atIndex:start];
}

void OSXTextPeer::deleteText( unsigned int start, unsigned int length )
{
	NSMutableString* str = [textStorage_ mutableString];
	NSRange range;
	range.location = start;
	range.length = length;
	[str deleteCharactersInRange:range];	
}

unsigned int OSXTextPeer::getTextLength()
{
	unsigned int result = 0;

	NSMutableString* str = [textStorage_ mutableString];
	result = [str length];
	
	return result;
}

String OSXTextPeer::getText( unsigned int start, unsigned int length )
{
	String result;
	
	VCFChar* buffer = new VCFChar[length];
	
	NSRange range;
	range.location = start;
	range.length = length;
	
	NSMutableString* str = [textStorage_ mutableString];
	[str getCharacters:buffer range:range];
	
	result.append( buffer, length );
	
	delete [] buffer;
	
	return result;
}

void OSXTextPeer::paint( GraphicsContext* context, const Rect& paintRect )
{	
	//[self lockFocus]; this needs to be called before we get here!!!
	
	NSRange glyphRange = [layoutMgr_ glyphRangeForTextContainer:container_];
	
	NSSize sz;
	sz.width = paintRect.getWidth();
	sz.height = paintRect.getHeight();
	[container_  setContainerSize:sz];
	NSPoint pt;
	pt.x = paintRect.left_;
	pt.y = paintRect.top_;
	[layoutMgr_ drawGlyphsForGlyphRange: glyphRange atPoint: pt];
}

void OSXTextPeer::setRightMargin( const double & rightMargin )
{
	margins_.right_ = rightMargin;
}

void OSXTextPeer::setLeftMargin( const double & leftMargin )
{
	margins_.left_ = leftMargin;
}

void OSXTextPeer::setTopMargin( const double & topMargin )
{
	margins_.top_ = topMargin;
}

void OSXTextPeer::setBottomMargin( const double & bottomMargin )
{
	margins_.bottom_ = bottomMargin;
}

double OSXTextPeer::getLeftMargin()
{
	return margins_.left_;
}

double OSXTextPeer::getRightMargin()
{
	return margins_.right_;
}

double OSXTextPeer::getTopMargin()
{
	return margins_.top_;
}

double OSXTextPeer::getBottomMargin()
{
	return margins_.bottom_;
}

uint32 OSXTextPeer::getLineCount()
{
	uint32 result = 0;	
	
	return result;
}

VCF::Rect OSXTextPeer::getContentBoundsForWidth(const double& width)
{
	VCF::Rect result;

	
	return result;
}

void OSXTextPeer::getStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	NSRange range;
	range.length = length;
	range.location = start;
	NSDictionary* dict = [textStorage_ attributesAtIndex:start 
							longestEffectiveRange:nil
												 inRange:range];
	
	NSFont* font = [dict objectForKey: NSFontAttributeName];
	
	
	CFTextString tmp;
	if ( nil != font ) {
		tmp = [font fontName];
		styles [Text::fsFontName] = (String)tmp;
		
		styles [Text::fsPointSize] = [font pointSize];
		
		
		NSFontManager *fontManager = [NSFontManager sharedFontManager];
		
		NSFontTraitMask traits = [fontManager traitsOfFont:font];
		
		
		styles [Text::fsBold] =   NSBoldFontMask & traits ? true : false;
		styles [Text::fsItalic] = NSItalicFontMask & traits ? true : false;
	}
	
	styles [Text::fsUnderlined] = false;
	
	NSNumber* num = [dict objectForKey: NSUnderlineStyleAttributeName];
	if ( nil != num ) {
		int val = [num intValue];
		
		styles [Text::fsUnderlined] = val != 0 ? true : false;
	}
	
	num = [dict objectForKey: NSStrikethroughStyleAttributeName];
	if ( nil != num ) {
		int val = [num intValue];
		
		styles [Text::fsStrikeout] = val != 0 ? true : false;
	}
	
	
	NSColor* foreColor = [dict objectForKey: NSForegroundColorAttributeName];
	if ( nil != foreColor ) {
		Color* color = new Color();
		styles [Text::fsColor] = color;
		color->setRed( [foreColor redComponent] );
		color->setGreen( [foreColor greenComponent] );
		color->setBlue( [foreColor blueComponent] );
		color->setAlpha( [foreColor alphaComponent] );
	}	
}

void OSXTextPeer::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	NSRange range;
	range.length = length;
	range.location = start;
	
	
	NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithCapacity: styles.size()];
	
	CFTextString tmp;
	Dictionary::Enumerator* items = styles.getEnumerator();
	NSFontTraitMask traits = 0;
	NSInteger weight = 0;
	double size = 0;
	NSFontManager *fontManager = [NSFontManager sharedFontManager];
	
	NSFont* font = nil;//[fontManager fontWithFamily:tmp traits:traits weight:weight size:size];
	
	if ( styles.keyExists(Text::fsColor) ) {
		Color* color = (Color*)(Object*)styles[Text::fsColor];
		VCF_ASSERT( NULL != color );
		
		NSColor* foreColor = [NSColor colorWithCalibratedRed:color->getRed() 
								green:color->getGreen() 
								blue:color->getBlue() 
							   alpha:color->getAlpha()];
		
		[dict setObject:foreColor forKey:NSForegroundColorAttributeName];
	}
	
	if ( styles.keyExists(Text::fsStrikeout) ) {
		bool val = styles [Text::fsStrikeout];		
		
		NSNumber* num = [NSNumber numberWithInt: val ? 1 : 0];
		[dict setObject:num forKey:NSStrikethroughStyleAttributeName];
	}
	
	if ( styles.keyExists(Text::psAlignment) ) {
		int alignment = styles [Text::psAlignment];
		
		NSTextAlignment ta = 0;
		
		switch ( alignment ) {
			case Text::paLeft : {
				ta = NSLeftTextAlignment;
			}
			break;
				
			case Text::paCenter : {
				ta = NSCenterTextAlignment;
			}
			break;
				
			case Text::paRight : {
				ta = NSRightTextAlignment;
			}
			break;
				
			case Text::paJustified : {
				ta = NSJustifiedTextAlignment;
			}
			break;
		}
		NSMutableParagraphStyle* ps = [[NSMutableParagraphStyle alloc] init];
		[ps setParagraphStyle: [NSParagraphStyle defaultParagraphStyle]];
		[ps setAlignment:ta];
		
		[dict setObject:ps forKey:NSParagraphStyleAttributeName];
	}
	
	
	if ( styles.keyExists(Text::fsUnderlined) ) {
		int val = styles [Text::fsUnderlined];
		
		
		switch ( val ) {
			case Text::utNone : {
				
			}
			break;
				
			case Text::utSingle : {
				
			}
			break;
				
			case Text::utDouble : {
				
			}
			break;
				
			case Text::utDotted : {
				
			}
			break;
		}
		
		
		
		NSNumber* num = [NSNumber numberWithInt: val ? 1 : 0];
		[dict setObject:num forKey:NSUnderlineStyleAttributeName];
	}
	
	if ( styles.keyExists(Text::fsFontName) ) {
		tmp = (String)styles [Text::fsFontName];
		
		font = [NSFont fontWithName: tmp size: 0.0f];		
	}
	
	if ( styles.keyExists(Text::fsBold) ) {
		bool val = styles [Text::fsBold];
		if ( nil == font ) {
			font = [NSFont userFontOfSize: 0.0f];
		}
		
		if ( val ) {
			font = [fontManager convertFont: font  toHaveTrait:NSBoldFontMask];
		}
		else {
			font = [fontManager convertFont: font  toNotHaveTrait:NSBoldFontMask];
		}
	}
	
	if ( styles.keyExists(Text::fsItalic) ) {
		bool val = styles [Text::fsItalic];
		if ( nil == font ) {
			font = [NSFont userFontOfSize: 0.0f];
		}
		
		if ( val ) {
			font = [fontManager convertFont: font  toHaveTrait:NSItalicFontMask];
		}
		else {
			font = [fontManager convertFont: font  toNotHaveTrait:NSItalicFontMask];
		}
	}
	
	if ( styles.keyExists(Text::fsPointSize) ) {
		double val = styles [Text::fsPointSize];
		if ( nil == font ) {
			font = [NSFont userFontOfSize: val];
		}
		else {
			font = [fontManager convertFont: font  toSize:val];
		}
	}
	
	if ( nil != font ) {
		[dict setObject:font forKey:NSFontAttributeName];
	}
	
	[textStorage_ setAttributes:dict range:range ];
	
}

void OSXTextPeer::setDefaultStyle( Dictionary&  styles )
{
	
	//setStyle()
}

};


/**
$Id$
*/
