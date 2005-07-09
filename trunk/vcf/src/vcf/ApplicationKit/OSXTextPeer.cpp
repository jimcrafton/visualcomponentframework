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

using namespace VCF;

static int MLTERefCount = 0;

void initMLTE()
{
	if ( 0 == MLTERefCount ) {
		TXNInitOptions options;
		TXNMacOSPreferredFontDescription  defaults;
		memset( &defaults, 0, sizeof(TXNMacOSPreferredFontDescription) );

		defaults.pointSize = kTXNDefaultFontSize;
		defaults.fontStyle = kTXNDefaultFontStyle;
		options = kTXNWantMoviesMask | kTXNWantSoundMask |
                                         kTXNWantGraphicsMask;

		if ( noErr != TXNInitTextension ( NULL, 0, options) ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("MLTE TXNInitTextension failed!") );
		}
	}

	MLTERefCount ++;
}

OSXTextPeer::OSXTextPeer( const bool& autoWordWrap, const bool& multiLined ):
	txnObject_(NULL)
{
	initMLTE();
}

OSXTextPeer::OSXTextPeer():
	txnObject_(NULL)
{
	initMLTE();

	TXNFrameOptions frameOptions;
    frameOptions = kTXNDoFontSubstitutionMask;

	//we may want these in the future
	//kTXNShowWindowMask | kTXNWantVScrollBarMask |
	//kTXNWantHScrollBarMask |kTXNDrawGrowIconMask;
	::HIRect r;
	r.origin.x = 0;
	r.origin.y = 0;
	r.size.width = 0;
	r.size.height = 0;
	if ( noErr != TXNCreateObject( &r, frameOptions, &txnObject_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("MLTE TXNCreateObject failed!") );
	}
	
	TXNCarbonEventInfo      carbonEventInfo;
	TXNControlTag           iControlTags[] = { kTXNUseCarbonEvents };  
	TXNControlData          iControlData[1];
	carbonEventInfo.useCarbonEvents = false;  
	carbonEventInfo.filler = 0;
	carbonEventInfo.flags = 0;   
	carbonEventInfo.fDictionary = NULL;
	iControlData[0].uValue = (UInt32) &carbonEventInfo;
	TXNSetTXNObjectControls( txnObject_, false, 1, iControlTags, iControlData ); 
}

OSXTextPeer::~OSXTextPeer()
{

	TXNDeleteObject(txnObject_);
	
	if ( MLTERefCount > 0 ) {
		MLTERefCount --;
	}

	if ( MLTERefCount <= 0 ) {
		TXNTerminateTextension();
	}
}


OSHandleID OSXTextPeer::getTextObjectHandle()
{
	OSHandleID result ;

	result = (OSHandleID)txnObject_;

	return result;
}

//storage
void OSXTextPeer::insertText( unsigned int start, const String& text )
{
	TXNSetData( txnObject_, kTXNUnicodeTextData, text.c_str(), text.size_in_bytes(), start, start );
}

void OSXTextPeer::deleteText( unsigned int start, unsigned int length )
{
	TXNSetData( txnObject_, kTXNUnicodeTextData, NULL, 0, start, start+length );
}

unsigned int OSXTextPeer::getTextLength()
{
	unsigned int result = 0;

	result = TXNDataSize(txnObject_) / sizeof(UniChar);

	return result;
}

String OSXTextPeer::getText( unsigned int start, unsigned int length )
{
	String result;

	Handle data = NULL;
	if ( noErr == TXNGetData( txnObject_, start, start+length, &data ) ) {
		HLock(data);
		CFRefObject<CFDataRef>  stringData = CFDataCreate(kCFAllocatorDefault, (UInt8*)*data, GetHandleSize(data));
		HUnlock(data);	


		CFRefObject<CFStringRef> stringRef = CFStringCreateFromExternalRepresentation(kCFAllocatorDefault, stringData, kCFStringEncodingUnicode);
		CFTextString tmp(stringRef);
		result = tmp;
		
		DisposeHandle( data );
	}

	return result;
}

void OSXTextPeer::paint( GraphicsContext* context, const Rect& paintRect )
{

	OSXContext* ctxPeer = (OSXContext*) context->getPeer();
	
	HIRect txBounds;
	txBounds.origin.x = paintRect.left_;
	txBounds.origin.y = paintRect.top_;
	txBounds.size.width = paintRect.getWidth();
	txBounds.size.height = paintRect.getHeight();
	
	TXNControlTag  controlTags[] = { kATSUCGContextTag };
	TXNControlData  controlData[1];
	controlData[0].uValue = (UInt32) ctxPeer->getCGContext();
	
	//set the txnObject_ to use the CGContext associated with the GraphicsContext!
 	TXNSetTXNObjectControls( txnObject_, false, sizeof( controlTags ) / sizeof( TXNControlTag ),
								controlTags, controlData );
 
	//resize it
	TXNSetHIRectBounds( txnObject_, &txBounds, &txBounds, false );
	//recalc the layout
	TXNRecalcTextLayout( txnObject_ );
	
	//draw it!!!
	TXNDrawObject( txnObject_, NULL, kTXNDrawItemTextMask );	
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

unsigned long OSXTextPeer::getLineCount()
{
	unsigned long result = 0;

	
	TXNGetLineCount( txnObject_, (ItemCount*)&result );
	
	return result;
}

VCF::Rect OSXTextPeer::getContentBoundsForWidth(const double& width)
{
	VCF::Rect result;

	
	HIRect originalBounds;
	TXNGetHIRect( txnObject_, kTXNViewRectKey, &originalBounds );
	
	//set the tmp bounds that we want to recalc the 
	//text for
	HIRect tmpBounds;
	tmpBounds.origin.x = 0;
	tmpBounds.origin.y = 0;
	tmpBounds.size.width = width;
	tmpBounds.size.height = 10; //doesn't really matter?
	
	//recalc the layout
	TXNSetHIRectBounds( txnObject_, &tmpBounds, &tmpBounds, false );
	TXNRecalcTextLayout( txnObject_ );
	
	ItemCount lines = 0;
	TXNGetLineCount( txnObject_, &lines );
	
	FixedPointNumber lineWidth;
	FixedPointNumber lineHeight;
	for ( ItemCount line=0;line<lines;line++ ) {
		TXNGetLineMetrics( txnObject_, line, &lineWidth, &lineHeight );
		result.right_ = maxVal<double>( result.right_, lineWidth );
		result.bottom_ += lineHeight.asDouble();
	}
	
	//reset the old bounds! 
	TXNSetHIRectBounds( txnObject_, &originalBounds, &originalBounds, false );
	TXNRecalcTextLayout( txnObject_ );
	
	return result;
}

void OSXTextPeer::getStyle( unsigned int start, unsigned int length, Dictionary& styles, Color& color )
{
	ItemCount count = 0;
	if ( noErr != TXNCountRunsInRange( txnObject_, start, start+length,&count ) ) {
		return;
	}
	TXNOffset s, e;
	s = e = 0;
	TXNDataType dataType = 0;
	ItemCount attrCount = 7;
	std::vector<TXNTypeAttributes> attrs(attrCount);
	Str255 fontName;
	RGBColor  fontColor;
	FixedPointNumber size;

	attrs[0].tag = kTXNQDFontNameAttribute;
	attrs[0].size = kTXNQDFontNameAttributeSize;
	attrs[0].data.dataPtr = fontName;

	attrs[1].tag = kTXNQDFontColorAttribute;
	attrs[1].size = kTXNQDFontColorAttributeSize;
	attrs[1].data.dataPtr = &fontColor;

	attrs[2].tag = kTXNQDFontSizeAttribute;
	attrs[2].size = kTXNQDFontSizeAttributeSize;
	attrs[2].data.dataValue = size.asInt();

	attrs[3].tag = kATSUQDBoldfaceTag;
	attrs[3].size = sizeof(Boolean);

	attrs[4].tag = kATSUQDItalicTag;
	attrs[4].size = sizeof(Boolean);

	attrs[5].tag = kATSUStyleStrikeThroughTag;
	attrs[5].size = sizeof(Boolean);

	attrs[6].tag = kATSUQDUnderlineTag;
	attrs[6].size = sizeof(Boolean);

	for (int index=0;index<count;index ++ ) {

		TXNGetIndexedRunInfoFromRange( txnObject_, index, start, start+length, &s, &e, &dataType, attrCount, &attrs[0] );
	}

	CFTextString tmp;
	tmp = fontName;

	styles [Text::fsFontName] = (String)tmp;

	styles [Text::fsColor] = &color;
	color.setRed( (double)fontColor.red / 65535.0 );
	color.setGreen( (double)fontColor.green / 65535.0 );
	color.setBlue( (double)fontColor.blue / 65535.0 );

	styles [Text::fsPointSize] = (double)size;

	styles [Text::fsBold] = (bool)attrs[3].data.dataValue;
	styles [Text::fsItalic] = (bool)attrs[4].data.dataValue;
	styles [Text::fsStrikeout] = (bool)attrs[5].data.dataValue;
	styles [Text::fsUnderlined] = (bool)attrs[6].data.dataValue;

}

void OSXTextPeer::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	Dictionary::Enumerator* items = styles.getEnumerator();
	std::vector<TXNTypeAttributes> attrs;
	Str255 pStr;
	while ( items->hasMoreElements() ) {
		Dictionary::pair style = items->nextElement();
		if ( style.first == Text::fsFontName ) {
			String s = style.second;

			CFTextString tmp(s);

			TXNTypeAttributes tag;
			tag.tag = kTXNQDFontNameAttribute;
			tag.size = kTXNQDFontNameAttributeSize;

			CopyCStringToPascal( s.ansi_c_str(), pStr );
			tag.data.dataPtr = pStr;
			attrs.push_back( tag );
		}
		else if ( style.first == Text::fsColor ) {
			Color* color = (Color*)(Object*)style.second;
			VCF_ASSERT( NULL != color );

			RGBColor  fontColor = { (int)(color->getRed()*65535.0), (int)(color->getGreen()*65535.0), (int)(color->getBlue()*65535.0) };
			TXNTypeAttributes tag;
			tag.tag = kTXNQDFontColorAttribute;
			tag.size = kTXNQDFontColorAttributeSize;
			tag.data.dataPtr = &fontColor;
			attrs.push_back( tag );
		}
		else if ( style.first == Text::fsPointSize ) {
			FixedPointNumber val = (double)style.second;
			TXNTypeAttributes tag;
			tag.tag = kTXNQDFontSizeAttribute;
			tag.size = kTXNQDFontSizeAttributeSize;
			tag.data.dataValue = val.asInt();
			attrs.push_back( tag );
		}
		else if ( style.first == Text::fsBold ) {
			bool val = style.second;

			TXNTypeAttributes tag;
			tag.tag = kATSUQDBoldfaceTag;
			tag.size = sizeof(Boolean);
			tag.data.dataValue = val;
			attrs.push_back( tag );
		}
		else if ( style.first == Text::fsItalic ) {
			bool val = style.second;
			TXNTypeAttributes tag;
			tag.tag = kATSUQDItalicTag;
			tag.size = sizeof(Boolean);
			tag.data.dataValue = val;
			attrs.push_back( tag );
		}
		else if ( style.first == Text::fsStrikeout ) {
			bool val = style.second;

			TXNTypeAttributes tag;
			tag.tag = kATSUStyleStrikeThroughTag;
			tag.size = sizeof(Boolean);
			tag.data.dataValue = val;
			attrs.push_back( tag );
		}
		else if ( style.first == Text::fsUnderlined ) {
			TXNTypeAttributes tag;
			tag.tag = kATSUQDUnderlineTag;
			tag.size = sizeof(Boolean);


			switch ( (int)style.second ) {
				case Text::utNone : {
					tag.data.dataValue = false;
				}
				break;

				case Text::utSingle : {
					tag.data.dataValue = true;
				}
				break;

				case Text::utDouble : {
					tag.data.dataValue = true;
				}
				break;

				case Text::utDotted : {
					tag.data.dataValue = true;
				}
				break;
			}

			attrs.push_back( tag );
		}
		else if ( style.first == Text::psAlignment ) {
			int alignment = style.second;
			
			TXNControlTag tag = kTXNJustificationTag;
			TXNControlData data;
			
			switch ( alignment ) {
				case Text::paLeft : {
					data.uValue = kTXNFlushLeft;
				}
				break;

				case Text::paCenter : {
					data.uValue = kTXNCenter;
				}
				break;

				case Text::paRight : {
					data.uValue = kTXNFlushRight;
				}
				break;

				case Text::paJustified : {
					data.uValue = kTXNForceFullJust;
				}
				break;
			}				
			
			TXNSetTXNObjectControls( txnObject_, false, 1, &tag, &data );
		}
	}

	if ( !attrs.empty() ) {
		TXNSetTypeAttributes( txnObject_, attrs.size(), &attrs[0], start, start+length );
	}
}

void OSXTextPeer::setDefaultStyle( Dictionary&  styles )
{

	TXNMacOSPreferredFontDescription defaults;
	defaults.encoding = CreateTextEncoding(kTextEncodingMacRoman, kTextEncodingDefaultVariant, kTextEncodingDefaultFormat);


	Dictionary::Enumerator* items = styles.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair style = items->nextElement();
		if ( style.first == Text::fsFontName ) {
			AnsiString tmp  = (String)style.second;

			ATSUFindFontFromName ( tmp.c_str(), tmp.length(),
						kFontFullName, kFontNoPlatform, kFontNoScript, kFontNoLanguage,
						&defaults.fontID );

		}
		else if ( style.first == Text::fsColor ) {
			//Color* color = (Color*)(Object*)style.second;
			//VCF_ASSERT( NULL != color );

			//RGBColor  fontColor = { (int)(color->getRed()*65535.0), (int)(color->getGreen()*65535.0), (int)(color->getBlue()*65535.0) };
		}
		else if ( style.first == Text::fsPointSize ) {
			FixedPointNumber val = (double)style.second;
			defaults.pointSize = val;
		}
		else if ( style.first == Text::fsBold ) {
			bool val = style.second;
		}
		else if ( style.first == Text::fsItalic ) {
			bool val = style.second;
		}
		else if ( style.first == Text::fsStrikeout ) {
			bool val = style.second;
		}
		else if ( style.first == Text::fsUnderlined ) {


			switch ( (int)style.second ) {
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
		}
		else if ( style.first == Text::psAlignment ) {
			int alignment = style.second;

			switch ( alignment ) {
				case Text::paLeft : {

				}
				break;

				case Text::paCenter : {

				}
				break;

				case Text::paRight : {

				}
				break;

				case Text::paJustified : {

				}
				break;
			}
		}
	}

	TXNSetFontDefaults( txnObject_, 1, &defaults );
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.4  2005/06/28 04:03:36  ddiego
*osx text edit mods and started on osx tree peer.
*
*Revision 1.1.2.3  2005/06/27 03:28:54  ddiego
*more osx work.
*
*Revision 1.1.2.2  2005/06/25 19:46:59  marcelloptr
*forgotten MP mark
*
*Revision 1.1.2.1  2005/06/23 01:26:55  ddiego
*build updates
*
*Revision 1.1.2.9  2005/06/09 07:18:25  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.1.2.6  2005/06/07 17:31:29  marcelloptr
*added missed getStyle() function. Fixed underline text that couldn't be removed once introduced.
*
*/


