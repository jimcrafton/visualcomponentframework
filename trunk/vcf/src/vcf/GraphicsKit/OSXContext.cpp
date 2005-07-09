//OSXContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/FoundationKit/VCFMath.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;




OSXContext::OSXContext():
	contextID_(nil),
    grafPort_(0),
	inMemoryImage_(nil),
    imgWidth_(0),
    imgHeight_(0),
	context_(NULL),
	currentDrawingOperation_(0),
	textLayout_(nil),
    xorModeOn_(false),
	lastPrimitive_(OSXContext::lpNone),
	antialiasingOn_(true)
{
	init();
}

OSXContext::OSXContext( const unsigned long& width, const unsigned long& height ):
	contextID_(nil),
    grafPort_(0),
	inMemoryImage_(nil),
    imgWidth_(width),
    imgHeight_(height),
	context_(NULL),
	currentDrawingOperation_(0),
	textLayout_(nil),
    xorModeOn_(false),
	lastPrimitive_(OSXContext::lpNone),
	antialiasingOn_(true)
{
	//allocate a RGBA buffer for use
    inMemoryImage_ = new unsigned char[imgWidth_ * imgHeight_ * 4];
	init();
}

OSXContext::OSXContext( OSHandleID contextID ):
	contextID_(0),
    grafPort_((GrafPtr)contextID),
	inMemoryImage_(nil),
    imgWidth_(0),
    imgHeight_(0),
	context_(NULL),
	currentDrawingOperation_(0),
	textLayout_(nil),
    xorModeOn_(false),
	lastPrimitive_(OSXContext::lpNone),
	antialiasingOn_(true)
{
	init();
}

OSXContext::~OSXContext()
{

	if ( nil != textLayout_ ) {
		ATSUDisposeTextLayout( textLayout_ );
	}

    CGContextRelease( contextID_);

    if ( NULL != inMemoryImage_ ) {
        delete [] inMemoryImage_;
        inMemoryImage_ = NULL;
        DisposeGWorld( grafPort_ );
    }


	contextID_ = nil;
}

void OSXContext::setContext( GraphicsContext* context )
{
	context_ = context;
}

GraphicsContext* OSXContext::getContext()
{
	return context_;
}

OSHandleID OSXContext::getContextID()
{
	return (OSHandleID)grafPort_;
}

void OSXContext::setContextID( OSHandleID handle )
{
    if ( NULL != inMemoryImage_ ) {
        delete [] inMemoryImage_;
        inMemoryImage_ = 0;
        imgWidth_ = 0;
        imgHeight_ = 0;
        DisposeGWorld( grafPort_ );
		
    }

	if ( NULL != grafPort_ ) {
		CGContextRelease( contextID_);
		contextID_ = NULL;
    }

	grafPort_ = (GrafPtr)handle;
    init();
}

void OSXContext::setPortFromImage( GrafPtr port, uint32 width, uint32 height )
{
	
	
	
	grafPort_ = port;
	ownerRect_.setRect( 0, 0, width, height );
	
	if ( NULL != contextID_ ) {
		CGContextRelease( contextID_);
	}
	
	
	CreateCGContextForPort( grafPort_, &contextID_);		
	
	//Note the absence of a transform! apparently we don't need to for 
	//image based CG's
	
	if ( nil == textLayout_ ) {
		ATSUCreateTextLayout( &textLayout_ );
	}
	
	ATSUAttributeTag        cgTags[] = {kATSUCGContextTag};
	ByteCount               cgSize[] = {sizeof (contextID_)};
	ATSUAttributeValuePtr   cgValue[] = {&contextID_};

	OSStatus err = ATSUSetLayoutControls (textLayout_,
										  1,
										  cgTags,
										  cgSize,
										  cgValue);
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUSetLayoutControls failed.") );
	}
	
}

void OSXContext::setCGContext( CGContextRef cgRef, GrafPtr port, const Rect& ownerRect  )
{
	if ( NULL != inMemoryImage_ ) {
        delete [] inMemoryImage_;
        inMemoryImage_ = 0;
        imgWidth_ = 0;
        imgHeight_ = 0;
        DisposeGWorld( grafPort_ );
    }



	ownerRect_ = ownerRect;
	contextID_ = cgRef;
	grafPort_ = NULL;

	if ( NULL != inMemoryImage_ ) {
        //allocate a new gworld
        GWorldPtr newGworld = 0;

        int bitsPerPix = 32;
        int componentCount = 4;
        int bytesPerRow = (imgWidth_ * (bitsPerPix/componentCount) * componentCount) / 8;
        ::Rect imgRect;
        imgRect.left = 0;
        imgRect.top = 0;
        imgRect.right = imgWidth_;
        imgRect.bottom = imgHeight_;

        OSStatus err = 0;
        err = NewGWorldFromPtr( &newGworld,
                            k32RGBAPixelFormat,
                            &imgRect,
                            NULL,
                            NULL,
                            0,
                            (char*)inMemoryImage_,
                            bytesPerRow );
        if ( noErr == err ) {
            grafPort_ = newGworld;
//            printf( "NewGWorldFromPtr() succeeded, grafPort_: %p\n", grafPort_ );
        }
        else {
            throw RuntimeException( MAKE_ERROR_MSG_2("NewGWorldFromPtr() failed to allocate GWorld") );
        }
    }

	grafPort_ = port;


	if ( nil == textLayout_ ) {
		ATSUCreateTextLayout( &textLayout_ );
	}

	if ( NULL != contextID_ ) {
		ATSUAttributeTag        cgTags[] = {kATSUCGContextTag};
		ByteCount               cgSize[] = {sizeof (contextID_)};
		ATSUAttributeValuePtr   cgValue[] = {&contextID_};

		OSStatus err = ATSUSetLayoutControls (textLayout_,
											  1,
											  cgTags,
											  cgSize,
											  cgValue);
		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("ATSUSetLayoutControls failed.") );
		}
	}
}

void OSXContext::init()
{
    origin_.x_ = 0;
	origin_.y_ = 0;
	
	if ( NULL != inMemoryImage_ ) {
        //allocate a new gworld
        GWorldPtr newGworld = 0;

        int bitsPerPix = 32;
        int componentCount = 4;
        int bytesPerRow = (imgWidth_ * (bitsPerPix/componentCount) * componentCount) / 8;
        ::Rect imgRect;
        imgRect.left = 0;
        imgRect.top = 0;
        imgRect.right = imgWidth_;
        imgRect.bottom = imgHeight_;

        OSStatus err = 0;
        err = NewGWorldFromPtr( &newGworld,
                            k32RGBAPixelFormat,
                            &imgRect,
                            NULL,
                            NULL,
                            0,
                            (char*)inMemoryImage_,
                            bytesPerRow );
        if ( noErr == err ) {
            grafPort_ = newGworld;
//            printf( "NewGWorldFromPtr() succeeded, grafPort_: %p\n", grafPort_ );
        }
        else {
            throw RuntimeException( MAKE_ERROR_MSG_2("NewGWorldFromPtr() failed to allocate GWorld") );
        }
    }

    if ( NULL != grafPort_ ) {
        CreateCGContextForPort( grafPort_, &contextID_);

		//CGContextSaveGState( contextID_ );
		::Rect portBounds;
        GetPortBounds( grafPort_, &portBounds );


        CGContextTranslateCTM(contextID_, 0,
                                        (float)(portBounds.bottom - portBounds.top));
        CGContextScaleCTM(contextID_, 1, -1);

		if( nil == textLayout_ ) { //only do this once
			ATSUCreateTextLayout( &textLayout_ );
		}

		ATSUAttributeTag        cgTags[] = {kATSUCGContextTag};
		ByteCount               cgSize[] = {sizeof (contextID_)};
		ATSUAttributeValuePtr   cgValue[] = {&contextID_};

		OSStatus err = ATSUSetLayoutControls (textLayout_,
											  1,
											  cgTags,
											  cgSize,
											  cgValue);
		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("ATSUSetLayoutControls failed.") );
		}
	}


}

void OSXContext::textAt( const VCF::Rect& bounds, const String & text, const long& drawOptions )
{
    VCF::Rect offsetBounds = bounds;
    offsetBounds.offset( origin_ );


	//tdoWordWrap=1,
	//tdoLeftAlign=2,
	//tdoCenterHorzAlign=4,
	//tdoRightAlign=8,
	//tdoBottomAlign=16,
	//tdoCenterVertAlign=32,
	//tdoTopAlign=64

	
	ATSUSetTextPointerLocation( textLayout_,
								text.c_str(),
								kATSUFromTextBeginning,
								kATSUToTextEnd,
								text.length() );

	//CFTextString cfStr;
	//cfStr = text;

    Font* ctxFont = context_->getCurrentFont();
	FontPeer* fontImpl = ctxFont->getFontPeer();
	
	ATSUStyle fontStyle = (ATSUStyle)fontImpl->getFontHandleID();
	
	ATSUSetRunStyle( textLayout_, fontStyle, 0, text.length() );
	
	OSStatus err = 0;
	
	ATSUAttributeTag tag[] = {kATSULineFlushFactorTag};
	ByteCount tagSize = sizeof(Fract);
	Fract orginalVal = 0;
	Fract val = 0;
	ByteCount actualSz[] = {sizeof(Fract)};
		
	if ( drawOptions & GraphicsContext::tdoLeftAlign ) {
		val = kATSUStartAlignment;
	}
	else if ( drawOptions & GraphicsContext::tdoRightAlign ) {
		val = kATSUEndAlignment;
	}
	else if ( drawOptions & GraphicsContext::tdoCenterHorzAlign ) {
		val = kATSUCenterAlignment;
	}
	
	ATSUAttributeValuePtr attrVals[] = {&val};
	
	
	err = ATSUGetLayoutControl( textLayout_, tag[0], tagSize, 
										(ATSUAttributeValuePtr)&orginalVal, &actualSz[0] );
	
	if ( err != noErr ) {
		StringUtils::trace( "ATSUGetLayoutControl(kATSULineFlushFactorTag) failed" );
	}
	
	err = ATSUSetLayoutControls( textLayout_, 1, tag, actualSz, attrVals );
	if ( err != noErr ) {
		StringUtils::trace( "ATSUSetLayoutControls(kATSULineFlushFactorTag) failed" );
	}
	
	
	

	
	if ( GraphicsContext::tdoWordWrap & drawOptions ) {
		//do word wrap
		VCF::Rect r = offsetBounds;

		atsuDrawTextInBox( r, drawOptions );
	}
	else {
		double textHeight = getTextHeight("EM");
		
		setLayoutWidth( textLayout_, 0 );
		FixedPointNumber x =  offsetBounds.left_;
		FixedPointNumber lineWidth =  offsetBounds.getWidth();
		FixedPointNumber y = ((offsetBounds.top_ + textHeight)*-1.0);
		
		if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
			y = ((offsetBounds.bottom_/* + textHeight*/) *-1.0);
		}
		else if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
			y = ((offsetBounds.top_ + offsetBounds.getHeight()/2.0 + textHeight/2.0 ) *-1.0 );
		}
		
		
		UniCharArrayOffset lineEndOffset;
		err = ATSUBreakLine(textLayout_, kATSUFromTextBeginning, lineWidth, true, &lineEndOffset);
		
		if ( noErr != err ) {
			StringUtils::trace( "ATSUBreakLine() failed" );
		}
		
		err = ATSUDrawText( textLayout_,
							kATSUFromTextBeginning,
							lineEndOffset,
							x,  y );
		if ( noErr != err ) {
			StringUtils::trace( "ATSUDrawText() failed" );
		}

	}

	attrVals[0] = &orginalVal;
	//reset original tag vals
	ATSUSetLayoutControls( textLayout_, 1, tag, actualSz, attrVals );
}

void OSXContext::setLayoutWidth( ATSUTextLayout layout, double width )
{
	FixedPointNumber fwidth = width;
	ATSUTextMeasurement textWidth = fwidth;
	ATSUAttributeTag tag = kATSULineWidthTag;
	ByteCount count = sizeof(ATSUTextMeasurement);
	ATSUAttributeValuePtr ptr = &textWidth;
	ATSUSetLayoutControls( layout, 1, &tag, &count, &ptr );

}

VCF::Size OSXContext::getLayoutDimensions( const String& text )
{
	int length = text.length();

	if ( NULL == textLayout_ ) {
		return Size();
	}
	
	ATSUTextLayout tmpTextLayout = NULL;
	OSStatus err = ATSUCreateAndCopyTextLayout( textLayout_, &tmpTextLayout );
	if ( err != noErr ) {
		String msg = StringUtils::format( Format("ATSUCreateAndCopyTextLayout failed, err: %d, textLayout_: %p, tmpTextLayout: %p") % err % textLayout_ % tmpTextLayout );
		throw RuntimeException( MAKE_ERROR_MSG_2(msg) );
	}	
	
	ATSUSetTextPointerLocation( tmpTextLayout, text.c_str(), 
                                kATSUFromTextBeginning, 
								kATSUToTextEnd, 
								length );												
	
	setLayoutWidth( tmpTextLayout, 0 );
		
	Font* ctxFont = context_->getCurrentFont();
	FontPeer* fontImpl = ctxFont->getFontPeer();
	ATSUStyle fontStyle = (ATSUStyle)fontImpl->getFontHandleID();
	
											
	ATSUSetRunStyle( tmpTextLayout, fontStyle, 0, length );
	
	
	ItemCount actualBoundsReturned  = 1;
	ATSTrapezoid bounds;
																
	ATSUGetGlyphBounds( tmpTextLayout, 0, 0, 0, length, kATSUseDeviceOrigins, 1, &bounds, &actualBoundsReturned );
					
	
	VCF::Size result;
	FixedPointNumber w = (Fixed)abs(bounds.upperLeft.x - bounds.upperRight.x);

	result.width_ = w.asDouble();

	FixedPointNumber h = (Fixed)(-bounds.upperLeft.y) + bounds.lowerLeft.y;
	result.height_ = h.asDouble();
	
	ATSUDisposeTextLayout( tmpTextLayout );
	
	return  result;
}

double OSXContext::getTextWidth( const String& text )
{
	return getLayoutDimensions(text).width_;
}

double OSXContext::getTextHeight( const String& text )
{
	return getLayoutDimensions(text).height_;
}

void OSXContext::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	endLastPrimitive();

	CGRect rect;
	rect.origin.x = x1 + origin_.x_;
	rect.origin.y = y1 + origin_.y_;

	rect.size.width = x2 - x1;
	rect.size.height = y2 - y1;
	//CGContextBeginPath( contextID_ );
	CGContextAddRect( contextID_, rect );
	//CGContextClosePath( contextID_ );
	if ( GraphicsContext::doStroke == currentDrawingOperation_ ) {
		//CGContextStrokePath ( contextID_ );
	}
	else if ( GraphicsContext::doFill == currentDrawingOperation_ ) {
		//CGContextFillPath ( contextID_ );
	}
}

void OSXContext::roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
							 const double & xc, const double & yc)
{

}


void OSXContext::ellipse(const double & x1, const double & y1, const double & x2, const double & y2 )
{
	endLastPrimitive();
	
	float a, b;
    CGPoint center;

    center.x = x1 + (x2-x1)/2.0;
	center.y = y1 + (y2-y1)/2.0;

    a = (x2-x1)/2.0;
    b = (y2-y1)/2.0;
    CGContextBeginPath ( contextID_ );
	CGContextSaveGState(contextID_);
    CGContextTranslateCTM(contextID_, center.x, center.y);
    CGContextScaleCTM(contextID_, a, b);
    CGContextMoveToPoint(contextID_, 1, 0);
    CGContextAddArc(contextID_, 0, 0, 1, Math::degreesToRadians(0), Math::degreesToRadians(360), 0);
    CGContextClosePath(contextID_);
    CGContextRestoreGState(contextID_);

	if ( GraphicsContext::doStroke == currentDrawingOperation_ ) {
		CGContextStrokePath(contextID_);
	}
	else if ( GraphicsContext::doFill == currentDrawingOperation_ ) {
		CGContextFillPath ( contextID_ );
	}
}

void OSXContext::arc(const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
						 const double & y3, const double & x4, const double & y4)
{
	//CGContextAddArc
}


void OSXContext::polyline(const std::vector<Point>& pts )
{
	endLastPrimitive();

	std::vector<Point>::const_iterator it = pts.begin();
	CGPoint* cgPts = new CGPoint[pts.size()];
	int i = 0;
	while ( it != pts.end() ) {
		const Point& pt = *it;
		cgPts[i].x = pt.x_ + origin_.x_;
		cgPts[i].y = pt.y_ + origin_.y_;
		it ++;
		i++;
	}

	CGContextAddLines( contextID_, cgPts, pts.size() );

	if ( GraphicsContext::doStroke == currentDrawingOperation_ ) {
		//CGContextStrokePath ( contextID_ );
	}
	else if ( GraphicsContext::doFill == currentDrawingOperation_ ) {
		//CGContextFillPath ( contextID_ );
	}

	delete [] cgPts;
}

void OSXContext::curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4)
{
	endLastPrimitive();
	
	//CGContextBeginPath( contextID_ );

	CGContextMoveToPoint( contextID_, x1 + origin_.x_, y1 + origin_.y_ );
	CGContextAddCurveToPoint( contextID_, x2 + origin_.x_, y2 + origin_.y_,
                                x3 + origin_.x_, y3 + origin_.y_,
                                x4 + origin_.x_, y4 + origin_.y_ );

	//CGContextClosePath( contextID_ );
	if ( GraphicsContext::doStroke == currentDrawingOperation_ ) {
		//CGContextStrokePath ( contextID_ );
	}
	else if ( GraphicsContext::doFill == currentDrawingOperation_ ) {
		//CGContextFillPath ( contextID_ );
	}
}

void OSXContext::lineTo(const double & x, const double & y)
{
	//CGContextAddLineToPoint( contextID_, x + origin_.x_, y + origin_.y_ );
	//CGContextStrokePath ( contextID_ );
	finishLastPrimitive(x,y);
	
	CGPoint pt = CGContextGetPathCurrentPoint ( contextID_ );
	double dx = static_cast<double>(pt.x)-(x+.5);
	double dy = static_cast<double>(pt.y)-(y+.5);
	
	double len = sqrt(dx*dx + dy*dy);
	if ( len < 1.0 ){
		return;
	}
	
	double ndx = dx/len;
	double ndy = dy/len;
	
	lastPrimitiveV1_.x_ = ndx;
	lastPrimitiveV1_.y_ = ndy;
	
	lastPrimitive_ = OSXContext::lpLine;
	
	lastPrimitiveP1_.x_ = x;
	lastPrimitiveP1_.y_ = y;
	
	CGContextAddLineToPoint( contextID_, x + origin_.x_ + ndx + .5, y + origin_.y_ +ndy + .5);	
}

void OSXContext::moveTo(const double & x, const double & y)
{

	//CGContextMoveToPoint( contextID_, x + origin_.x_, y + origin_.y_ );
	endLastPrimitive();
	lastPrimitive_ = OSXContext::lpMove;
	lastPrimitiveP1_.x_ = x;
	lastPrimitiveP1_.y_ = y;
	CGContextMoveToPoint( contextID_, x + origin_.x_ + .5, y + origin_.y_ + .5);
}


void OSXContext::setOrigin( const double& x, const double& y )
{

	if ( lastPrimitive_ != OSXContext::lpNone ) {
		lastPrimitiveP1_.x_ += origin_.x_ - x;
		lastPrimitiveP1_.y_ += origin_.y_ - y;
	}
	
	origin_.x_ = x;
	origin_.y_ = y;
}

VCF::Point OSXContext::getOrigin()
{
	return origin_;
}

void OSXContext::copyContext( const Rect& sourceRect,
								const Rect& destRect,
								ContextPeer* sourceContext )
{
    ::Rect srcRect;
    srcRect.left = (int)sourceRect.left_;
    srcRect.right = (int)sourceRect.right_;
    srcRect.top = (int)sourceRect.top_;
    srcRect.bottom = (int)sourceRect.bottom_;

    ::Rect dstRect;
    dstRect.left = (int)(destRect.left_ + origin_.x_);
    dstRect.right = (int)(destRect.right_  + origin_.x_);
    dstRect.top = (int)(destRect.top_ + origin_.y_);
    dstRect.bottom = (int)(destRect.bottom_ + origin_.y_);



    GrafPtr srcPort = (GrafPtr)sourceContext->getContextID();
    GrafPtr destPort = grafPort_;

	CopyBits( GetPortBitMapForCopyBits (srcPort),
                    GetPortBitMapForCopyBits (destPort),
                    &srcRect,
                    &dstRect,
                    srcCopy, 0 );
}

bool OSXContext::isMemoryContext()
{
	return (NULL != inMemoryImage_) ? true : false;
}

bool OSXContext::prepareForDrawing( long drawingOperation )
{
	currentDrawingOperation_ = drawingOperation;

    checkHandle();

	Color* currentColor = context_->getColor();
	GrafPtr oldPort;
    GetPort( &oldPort );
    if ( oldPort != grafPort_ ) {
        //SetPort( grafPort_ );
    }

	if ( xorModeOn_ ) {
        PenMode( srcXor );
    }
    else {
        PenMode( srcCopy );
    }

    if ( oldPort != grafPort_ ) {
        //SetPort( oldPort );
    }

	CGContextSetShouldAntialias(contextID_, antialiasingOn_);


	float colorComponents[4] =
			{currentColor->getRed(),
			currentColor->getGreen(),
			currentColor->getBlue(), 1.0};

	switch ( drawingOperation ) {
		case GraphicsContext::doStroke : {
			CGContextSetLineWidth( contextID_, context_->getStrokeWidth() );
			CGContextSetRGBStrokeColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath ( contextID_ );
		}
		break;

		case GraphicsContext::doFill : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath ( contextID_ );
		}
		break;

		case GraphicsContext::doText : {
			//save state
			CGContextSaveGState( contextID_ );

			//change the scaling back to normal otherwise we will have vertically
			//flipped glyphs - and no one wants that!!
			CGAffineTransform xfrm = CGAffineTransformMakeScale( 1, -1 );
			CGContextConcatCTM( contextID_, xfrm );

			//xfrm = CGAffineTransformMakeTranslation( 0, -(ownerRect_.top_) );
			//CGContextConcatCTM( contextID_, xfrm );

            Font* ctxFont = context_->getCurrentFont();
            OSXFont* fontImpl = (OSXFont*)ctxFont->getFontPeer();
            Color* fontColor = ctxFont->getColor();
            fontImpl->setColor( fontColor );

			colorComponents[0] = fontColor->getRed();
			colorComponents[1] = fontColor->getGreen();
			colorComponents[2] = fontColor->getBlue();

            CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextSetRGBStrokeColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
		}
		break;

		case GraphicsContext::doImage : {

		}
		break;
	}

	return true;
}

void OSXContext::finishedDrawing( long drawingOperation )
{
	endLastPrimitive();

	switch ( drawingOperation ) {
		case GraphicsContext::doStroke : {
			//CGContextClosePath( contextID_ );
			CGContextStrokePath ( contextID_ );
		}
		break;

		case GraphicsContext::doFill : {
			//CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;

		case GraphicsContext::doText : {
			CGContextRestoreGState( contextID_ );
		}
		break;

		case GraphicsContext::doImage : {
		}
		break;
	}

	currentDrawingOperation_ = -1;

	releaseHandle();


}

void OSXContext::setAntiAliasingOn( bool antiAliasingOn )
{
	endLastPrimitive();

	antialiasingOn_ = antiAliasingOn;
}

void OSXContext::endLastPrimitive()
{
	if (!isAntiAliasingOn()) return;
	
	if ( lastPrimitive_ == OSXContext::lpLine )  {
		CGContextAddLineToPoint( contextID_, origin_.x_ + lastPrimitiveP1_.x_ + .5 + lastPrimitiveV1_.x_/2.0, origin_.y_ + lastPrimitiveP1_.y_ + .5 + lastPrimitiveV1_.y_/2.0);
	}
	lastPrimitive_ = OSXContext::lpNone;
}

void OSXContext::finishLastPrimitive(const double & x, const double & y)
{
	if ( lastPrimitive_ == OSXContext::lpNone ){
		return;
	}
	if ( lastPrimitive_ == OSXContext::lpMove ) {
		if (!isAntiAliasingOn()) return;
		
		CGPoint pt=CGContextGetPathCurrentPoint ( contextID_ );
		double dx=x-lastPrimitiveP1_.x_;
		double dy=y-lastPrimitiveP1_.y_;

		double len=sqrt(dx*dx+dy*dy);
		
		if (len<1.0) return;

		double ndx=dx/len;
		double ndy=dy/len;
		
		CGContextMoveToPoint(contextID_, origin_.x_ + lastPrimitiveP1_.x_ + .5 - ndx/2.0,
								origin_.y_ + lastPrimitiveP1_.y_ + .5 - ndy/2.0);
	}
	else if ( lastPrimitive_ == OSXContext::lpLine ){
		CGContextAddLineToPoint(contextID_, origin_.x_ + lastPrimitiveP1_.x_ + .5,
								origin_.y_ + lastPrimitiveP1_.y_ + .5);
	}
}



void OSXContext::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image )
{
    if ( (imageBounds->getWidth() > image->getWidth()) || (imageBounds->getHeight() > image->getHeight()) ) {
		throw BasicException( MAKE_ERROR_MSG("Invalid image bounds requested"), __LINE__);
	}

    OSXImage* osXimage = (OSXImage*)(image);
    ulong32 imgBoundsWidth = imageBounds->getWidth();
    ulong32 imgBoundsHeight = imageBounds->getHeight();

    if ( (imgBoundsWidth == image->getWidth()) && (imgBoundsHeight == image->getHeight()) ) {
        CGImageRef imgRef = osXimage->getCGImage();
        CGRect imgBounds;
        imgBounds.origin.x = x + origin_.x_;
        imgBounds.origin.y = y + origin_.y_;
        imgBounds.size.width = imgBoundsWidth;
        imgBounds.size.height = imgBoundsHeight;

        CGContextDrawImage( contextID_, imgBounds, imgRef );
    }
    else {
        //create a smaller portion of the image
        int componentCount = image->getType();
        int bitsPerPix = image->getChannelSize() * componentCount;
        int bitsPerComponent = image->getChannelSize();
        int rowStride = ((imgBoundsWidth * bitsPerComponent * componentCount)  + 7)/ 8;

        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        SysPixelType* data = new SysPixelType[imgBoundsWidth*imgBoundsHeight];

        ulong32 imgSize = imgBoundsWidth * imgBoundsHeight * componentCount;
        CGDataProviderRef provider = CGDataProviderCreateWithData( NULL,
                                                                    (char*)data,
                                                                    imgSize,
                                                                    NULL );


        CGImageRef imgRef = CGImageCreate( imgBoundsWidth,
                                   imgBoundsHeight,
                                   image->getChannelSize(),
                                   bitsPerPix,
                                   rowStride,
                                   colorSpace,
                                   kCGImageAlphaNone,
                                   provider,
                                   NULL,
                                   FALSE,
                                   kCGRenderingIntentDefault );

        //copy over bits
        SysPixelType* imageBuf = image->getImageBits()->pixels_;
        SysPixelType* tmpBmpBuf = data;

        ulong32 incr = (ulong32)((imageBounds->top_ * image->getWidth()) + imageBounds->left_);
        imageBuf += incr;
        ulong32 imgWidth = image->getWidth();

        int s = (int)imageBounds->top_;
        int e = (int)imageBounds->bottom_;
        for (int y1=s;y1<e;y1++) {

            memcpy( tmpBmpBuf, imageBuf, imgBoundsWidth*componentCount );

            tmpBmpBuf += imgBoundsWidth;
            imageBuf += imgWidth;
        }

        CGRect imgBounds;
        imgBounds.origin.x = x + origin_.x_;
        imgBounds.origin.y = y + origin_.y_;
        imgBounds.size.width = imgBoundsWidth;
        imgBounds.size.height = imgBoundsHeight;

        CGContextDrawImage( contextID_, imgBounds, imgRef );

        CGColorSpaceRelease(colorSpace);
        CGDataProviderRelease(provider);
        CGImageRelease( imgRef );
        delete [] data;
    }

}

void OSXContext::checkHandle()
{

}

void OSXContext::releaseHandle()
{

}

bool OSXContext::isXORModeOn()
{
    return xorModeOn_;
}

void OSXContext::setXORModeOn( const bool& XORModeOn )
{
	endLastPrimitive();
    xorModeOn_ = XORModeOn;
}

void OSXContext::setTextAlignment( const bool& alignTobaseline )
{

}

bool OSXContext::isTextAlignedToBaseline()
{
	return false;
}

double OSXContext::getLayoutWidth( ATSUTextLayout layout )
{
	ATSUTextMeasurement width = 0;
	OSStatus status = ATSUGetLayoutControl( layout,
											kATSULineWidthTag,
											sizeof(ATSUTextMeasurement),
											&width, NULL );

	if ( status == noErr ) {
		return (double)width;
	}
	else {
		//throw exception ??
	}

	return -1.0;
}

void OSXContext::atsuDrawTextInBox(	const VCF::Rect& rect, const long& drawOptions )
{
	OSStatus 			err = noErr;
	UniCharArrayOffset	textOffset = 0;
	UniCharCount		textLength = 0;
	UniCharArrayOffset*	lineEndOffsets = NULL;

	bool failed = false;

	// the the range of text to be drawn
	err = ATSUGetTextLocation (textLayout_, NULL, NULL, &textOffset, &textLength, NULL);
	if (err == noErr) {
		UniCharArrayOffset lineStartOffset = textOffset;
		UniCharArrayOffset lineEndOffset = 0;

		FixedPointNumber xPos = rect.left_;
		double EMTextHeight = getTextHeight("EM");
		ATSUTextMeasurement	yPos = vcf_IntToFixed((int) ( rect.top_ + EMTextHeight ));

		ATSUTextMeasurement	lineStart = xPos;
		ATSUTextMeasurement	lineEnd = vcf_IntToFixed((int)rect.right_);
		ATSUTextMeasurement	lineWidth = 0;

		//at the moment we are not taking text angle into account
		Fixed textAngle = 0;

		ItemCount lineCount = 0;
		ItemCount softBreakCount = 0;
		ATSUTextMeasurement	maxAscent = 0, maxDescent = 0;
		ulong32 ln = 0;


		// check for linewidth set as a layout control
		//lineWidth = getLayoutWidth( textLayout_ );

		//	if there is no layout control set for width
		//	then set it using the box bounds
		if (lineWidth == 0) {
			lineWidth = lineEnd - lineStart;
		}

		//	Break and measure each line to determine the max ascent and descent;
		//	This is needed because things that end up on different lines
		//	could interact to affect the line height when they're on the same line.
		//	To get the best value we break the lines first, then measure each
		//	line and find the max ascent and descent.
		while (lineStartOffset < textOffset + textLength) {
			ATSUTextMeasurement		ascent = 0, descent = 0;

			// set the soft breaks, we will use them later
			err = ATSUBreakLine(textLayout_, lineStartOffset, lineWidth, true, &lineEndOffset);
			if ( err != noErr ) {
				failed = true;
				printf ( "err: %d, ATSUBreakLine()\n", (int)err );
				goto EXIT;
			}

			// @@@ If you want leave lines that are terminated with a hard break unjustified, this is a
			// good place to set the individual line control to do that.

#if (ATSU_TARG_VERSION >= ATSU_1_1)
			// ATSUGetGlyphBounds is better than ATSUMeasureText if you've got any interesting feature
			// such as justification turned on. The former will do the layout exactly as it will be drawn and cache
			// the result, so things will be faster overall. ATSUMeasureText will turn off justification and end up doing
			// an "extra" layout operation.
			{
				ATSTrapezoid	glyphBounds;	// one should be enough when we're asking for the whole line.

				err = ATSUGetGlyphBounds( textLayout_, 0, 0, lineStartOffset, lineEndOffset - lineStartOffset, kATSUseFractionalOrigins,
												1, &glyphBounds, NULL );
				if ( err != noErr ) {
					failed = true;
					printf ( "err: %d, ATSUGetGlyphBounds()\n", (int)err );
					goto EXIT;
				}

				// The top and bottom of the bounds should be parallel to the baseline. You might want to check that.
				if (textAngle == 0) {
					ascent = -glyphBounds.upperLeft.y;
					descent = glyphBounds.lowerLeft.y;
				} else {
					// This looks strange, but the box you get is rotated, so "upper left" relative to the line is "upper right" in absolute terms.
					ascent = glyphBounds.upperLeft.x;
					descent = -glyphBounds.lowerLeft.x;
				}
			}
#else
			err = ATSUMeasureText(textLayout_, lineStartOffset, lineEndOffset - lineStartOffset, NULL, NULL, &ascent, &descent);
			if ( err != noErr ) {
				failed = true;
				printf ( "err: %d, ATSUMeasureText()\n", err );
				goto EXIT;
			}
#endif

			if (ascent > maxAscent)
				maxAscent = ascent;
			if (descent > maxDescent)
				maxDescent = descent;

			lineStartOffset = lineEndOffset;
			lineCount++;
		}

		lineEndOffsets = (UniCharArrayOffset*) NewPtr(lineCount * sizeof(UniCharArrayOffset));

		err = MemError();
		if ( err != noErr ) {
			failed = true;
			printf ( "err: %d, MemError()\n", (int)err );
			goto EXIT;
		}

		err = ATSUGetSoftLineBreaks(	textLayout_,
											textOffset,
											textLength,
											lineCount,
											lineEndOffsets,
											&softBreakCount);

		//	assert that the number of soft breaks is always one less than the number of lines
		//	since ATSUBreakLine does not insert a softbreak at the end of the text.

		if ( (err != noErr) || (softBreakCount != (lineCount - 1)) ) {
			failed = true;
			printf ( "err: %d, ATSUGetSoftLineBreaks()\n", (int)err );
			goto EXIT;
		}

		lineEndOffsets[softBreakCount] = textOffset + textLength;
		lineStartOffset = textOffset;

		// @@@ If maxAscent or maxDescent are not integers, this code may produce uneven line spacing. It will also
		// not necessarily match the line height used by ATSUI when highlighting. ATSUI highlighting uses
		// vcf_FixedToInt( baseline - ascent ) for the top of the box and vcf_FixedToInt( baseline + descent ) for the bottom.
		// Any other combination of reflection and rounding can result in one-pixel gaps and overlaps.

		// If you're using ATSUGetGlyphBounds above, you could ask for kATSUseDeviceOrigins to have ATSUI do this transformation for you.

		//	draw each line

		if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
			yPos = vcf_IntToFixed( rect.bottom_ + EMTextHeight );
			yPos -=	(lineCount * (maxAscent+maxDescent));
		}
		else if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
			yPos = vcf_IntToFixed( rect.top_ + rect.getHeight()/2.0 + EMTextHeight );
			yPos -=	((lineCount * (maxAscent+maxDescent))/2);
		}

		for (ln = 0; ln < lineCount; ln++) {
			lineEndOffset = lineEndOffsets[ln];

			err = ATSUDrawText( textLayout_,
										lineStartOffset,
										lineEndOffset - lineStartOffset,
										xPos,
										yPos*-1);

			if ( err != noErr ) {
				failed = true;
				printf ( "err: %d, ATSUDrawText() failed in OSXContect::atsuDrawTextInBox()\n", (int)err );
				goto EXIT;
			}

			lineStartOffset = lineEndOffset;

			yPos += maxAscent;
			yPos += maxDescent;
		}
	}


EXIT:
	if ( failed ) {
		//throw exception ??
		printf( "\n\nWe Blewit !\n\n" );
	}


	if (lineEndOffsets != NULL)  {
		DisposePtr((char*)lineEndOffsets);
	}
}

void OSXContext::setClippingPath( Path* clippingPath )
{
	if ( NULL != clippingPath ) {
		std::vector<PathPoint> points;
		
		if ( clippingPath->getPoints( points, NULL ) ) {	

			CGMutablePathRef  pathRef = CGPathCreateMutable();
	
			PathPoint p2, c1, c2;			
			
			std::vector<PathPoint>::iterator it = points.begin();
			while ( it != points.end() ) {
				PathPoint& pt = *it;
				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						CGPathMoveToPoint( pathRef, NULL, pt.point_.x_ + origin_.x_, pt.point_.y_ + origin_.y_);
					}
					break;

					case PathPoint::ptLineTo: {
						CGPathAddLineToPoint( pathRef, NULL, pt.point_.x_+origin_.x_, pt.point_.y_ + origin_.y_);
					}
					break;

					case PathPoint::ptQuadTo: {
					
						it++;
						c1 = *it;

						it++;
						c2 = *it;

						it++;
						p2 = *it;						
						
						if ( it == points.begin() ) {
							CGPathMoveToPoint( pathRef, NULL, pt.point_.x_, pt.point_.y_);
							CGPathAddCurveToPoint( pathRef, NULL, 
													c1.point_.x_ + origin_.x_,
													c1.point_.y_ + origin_.y_,
													c2.point_.x_ + origin_.x_,
													c2.point_.y_ + origin_.y_,
													p2.point_.x_ + origin_.x_,
													p2.point_.y_ + origin_.y_ );
						}
						else {
							CGPathAddCurveToPoint( pathRef, NULL, 
													c1.point_.x_ + origin_.x_,
													c1.point_.y_ + origin_.y_,
													c2.point_.x_ + origin_.x_,
													c2.point_.y_ + origin_.y_,
													p2.point_.x_ + origin_.x_,
													p2.point_.y_ + origin_.y_ );
						}
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						CGPathCloseSubpath( pathRef );						
					}
					break;
				}
				
				it ++;
			}
			
			CGContextSaveGState( contextID_ );
			
			CGContextBeginPath ( contextID_ );
			
			CGContextAddPath( contextID_, pathRef );
			
			CGContextClosePath(contextID_);
			
			CGContextClip( contextID_ );
			
			CGPathRelease( pathRef );			
		}
	}
	else {
		CGContextRestoreGState( contextID_ );
	}
}

void OSXContext::setClippingRect( Rect* clipRect )
{	
	if ( clipRect->isNull() || clipRect->isEmpty() ) {
		CGContextRestoreGState( contextID_ );	
	}
	else {
		Rect tmpClipRect = *clipRect;
		tmpClipRect.offset( origin_.x_, origin_.y_ );
		
		OSXRect r = &tmpClipRect;
		
		CGContextSaveGState( contextID_ );
		CGContextClipToRect( contextID_, r );
	}
}


void OSXContext::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	CGContextSaveGState( contextID_ );
	
	Color* stroke = Color::getColor("gray100");
	Color* fill = Color::getColor("gray128");
	
	CGContextSetAlpha( contextID_, 0.2 );
	
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
	CGContextSetLineWidth( contextID_, 1.0 );
	CGContextSetRGBStrokeColor( contextID_, stroke->getRed(), stroke->getGreen(),
										stroke->getBlue(), 1.0 );
										
	CGContextSetRGBFillColor( contextID_, fill->getRed(), fill->getGreen(),
										fill->getBlue(), 1.0 );
										
    CGContextBeginPath( contextID_ );
	CGContextAddRect( contextID_, r );
	CGContextClosePath( contextID_ );
	CGContextDrawPath ( contextID_, kCGPathFillStroke );	
	//CGContextFillPath ( contextID_ );
	
	CGContextRestoreGState( contextID_ );	
}

void OSXContext::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;

    DrawThemeFocusRect( r, state.isFocused() );
}

void OSXContext_drawThemeButtonText( const ::Rect * bounds, ThemeButtonKind kind, 
										const ThemeButtonDrawInfo * info, UInt32 userData,
										SInt16 depth, Boolean isColorDev )
{
	
	ButtonState* state = (ButtonState*)userData;
	CFTextString cfStr;
	cfStr = state->buttonCaption_;
	::Point textSize;
	SInt16 baseLine;
	GetThemeTextDimensions( cfStr, kThemePushButtonFont, info->state, FALSE, &textSize, &baseLine );
	::Rect adjustedBounds = *bounds;
	adjustedBounds.top += ((bounds->bottom-bounds->top)/2) - (textSize.v/2);
	DrawThemeTextBox( cfStr, kThemePushButtonFont, info->state, FALSE, &adjustedBounds, teCenter, NULL );
}


void OSXContext::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
    ThemeButtonDrawInfo btnInfo;
	btnInfo.state = kThemeStateInactive ;
	
	if ( state.isPressed() && (state.isActive() && state.isEnabled()) ) {
		btnInfo.state |= kThemeStatePressed;
	}
	
	if ( state.isActive() && state.isEnabled() ) {
		btnInfo.state |= kThemeStateActive;
	}
	
	btnInfo.value = kThemeButtonOff;
	btnInfo.adornment = kThemeAdornmentNone;
	
	if ( state.isFocused() ) {
		btnInfo.adornment |= kThemeAdornmentFocus;
	}
	
	if ( state.isDefaultButton() && (state.isActive() && state.isEnabled()) ) {
		btnInfo.state |= kThemeStatePressed;
	}
   /*
	printf( "state.isPressed() : %s\n", state.isPressed() ? "true" : "false"  );
	printf( "state.isActive() : %s\n", state.isActive() ? "true" : "false"  );
	printf( "state.isEnabled() : %s\n", state.isEnabled() ? "true" : "false"  );
	printf( "state.isFocused() : %s\n", state.isFocused() ? "true" : "false"  );
	printf( "state.isDefaultButton() : %s\n", state.isDefaultButton() ? "true" : "false"  );
	printf( "button text : %s\n", state.buttonCaption_.ansi_c_str() );
	printf( "--------------------------------------------------------\n\n");
*/
	ThemeButtonDrawUPP btnDrawUPP = NewThemeButtonDrawUPP(OSXContext_drawThemeButtonText);
	
    DrawThemeButton( r, kThemePushButton, &btnInfo, NULL, NULL, btnDrawUPP, (UInt32)&state );
	
	DisposeThemeButtonDrawUPP(btnDrawUPP);
}

void OSXContext::drawThemeButtonFocusRect( Rect* rect )
{

}

void OSXContext::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
    ThemeButtonDrawInfo btnInfo;
	btnInfo.state = kThemeStateInactive ;
	
	btnInfo.value = kThemeButtonOff;
	
	if ( state.isPressed() ) {
		btnInfo.state |= kThemeStatePressed;
	}
	
	if ( state.isToggled() ) {
		btnInfo.value = kThemeButtonOn;
	}
	
	if ( state.isActive() && state.isEnabled() ) {
		btnInfo.state |= kThemeStateActive;
	}
	
	
	btnInfo.adornment = kThemeAdornmentNone;
	
	if ( state.isFocused() ) {
		btnInfo.adornment |= kThemeAdornmentFocus;
	}	
    
    

	ThemeButtonDrawUPP btnDrawUPP = NewThemeButtonDrawUPP(OSXContext_drawThemeButtonText);
	
    DrawThemeButton( r, kThemeCheckBox, &btnInfo, NULL, NULL, btnDrawUPP, (UInt32)&state );
	
	DisposeThemeButtonDrawUPP(btnDrawUPP);
}

void OSXContext::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
    ThemeButtonDrawInfo btnInfo;
	btnInfo.state = kThemeStateInactive ;
	
	btnInfo.value = kThemeButtonOff;
	
	if ( state.isPressed() ) {
		btnInfo.state |= kThemeStatePressed;
	}
	
	if ( state.isToggled() ) {
		btnInfo.value = kThemeButtonOn;
	}
	
	if ( state.isActive() && state.isEnabled() ) {
		btnInfo.state |= kThemeStateActive;
	}
	
	
	btnInfo.adornment = kThemeAdornmentNone;
	
	if ( state.isFocused() ) {
		btnInfo.adornment |= kThemeAdornmentFocus;
	}	
    
    

	ThemeButtonDrawUPP btnDrawUPP = NewThemeButtonDrawUPP(OSXContext_drawThemeButtonText);
	
    DrawThemeButton( r, kThemeRadioButton, &btnInfo, NULL, NULL, btnDrawUPP, (UInt32)&state );
	
	DisposeThemeButtonDrawUPP(btnDrawUPP);
}

void OSXContext::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
    ThemeButtonDrawInfo btnInfo;
	btnInfo.state = kThemeStateInactive ;
	
	btnInfo.value = kThemeButtonOff;
	
	if ( state.isPressed() ) {
		btnInfo.state |= kThemeStatePressed;
		btnInfo.value = kThemeButtonOn;
	}
	
	if ( state.isActive() && state.isEnabled() ) {
		btnInfo.state |= kThemeStateActive;
	}
	
	
	btnInfo.adornment = kThemeAdornmentNone;
	
	if ( state.isFocused() ) {
		btnInfo.adornment |= kThemeAdornmentFocus;
	}	
    
    

	ThemeButtonDrawUPP btnDrawUPP = NewThemeButtonDrawUPP(OSXContext_drawThemeButtonText);
	
    DrawThemeButton( r, kThemePopupButton, &btnInfo, NULL, NULL, btnDrawUPP, (UInt32)&state );
	
	DisposeThemeButtonDrawUPP(btnDrawUPP);
}

void OSXContext::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{
	/*
	OSXRect r = rect;
	ThemeTrackEnableState enableState = 0;
	
	if ( !state.isEnabled() ) {
        enableState = kThemeTrackDisabled;
    }
    else {
		if ( state.isActive() ) {
			enableState = kThemeTrackActive;
		}
		else {
			enableState = kThemeTrackInactive;
		}
    }
	
	DrawThemeScrollBarArrows
	*/
}

void OSXContext::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
    ThemeButtonDrawInfo btnInfo;
	btnInfo.state = kThemeStateInactive ;
	
	btnInfo.value = kThemeButtonOff;
	
	if ( state.isClosed() ) {		
		btnInfo.value = kThemeDisclosureRight;
	}
	else if ( state.isOpened() ) {		
		btnInfo.value = kThemeDisclosureDown;
	}
	
	if ( state.isActive() && state.isEnabled() ) {
		btnInfo.state |= kThemeStateActive;
	}
	
	
	btnInfo.adornment = kThemeAdornmentNone;		    

    DrawThemeButton( r, kThemeDisclosureButton, &btnInfo, NULL, NULL, NULL, 0 );
	
}

void OSXContext::drawThemeTab( Rect* rect, TabState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
	TabState* ts = (TabState*)&state;
	
	ThemeTabStyle tabStyle = kThemeTabNonFront;
	if ( ts->isPressed() ) {
		tabStyle |= kThemeTabFront;
	}
	
	if ( !ts->isActive() ) {		
		if ( ts->isPressed() ) {
			tabStyle |= kThemeTabFrontInactive;
		}
		else {
			tabStyle |= kThemeTabNonFrontInactive;
		}
	}
	
	ThemeTabDirection dir = 0;
	
	if ( ts->isTabOnTop() ) {
		dir = kThemeTabNorth;
	}
	else if ( ts->isTabOnBottom() ) {
		dir = kThemeTabSouth;
	}
	else if ( ts->isTabOnLeft() ) {
		dir = kThemeTabWest;
	}
	else if ( ts->isTabOnRight() ) {
		dir = kThemeTabEast;
	}	
	
	
	DrawThemeTab( r, tabStyle, dir, NULL, 0 );
}

void OSXContext::drawThemeTabPage( Rect* rect, DrawUIState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	DrawThemeTabPane( r, state.isActive() ? kThemeStateActive : kThemeStateInactive );
}

void OSXContext::drawThemeTickMarks( Rect* rect, SliderState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;

    ThemeTrackDrawInfo info;
    info.kind = kThemeSlider;//kThemeMediumSlider;
    info.bounds = r;			
								
    info.min = (int)state.min_;
    info.max = (int)state.max_;
    info.value = (int)state.position_;
    info.attributes = state.isVertical() ? 0 :  kThemeTrackHorizontal;
    info.attributes |= kThemeTrackShowThumb;

    info.trackInfo.slider.thumbDir = 0;
    info.trackInfo.slider.pressState = 0;

	if ( state.isFocused() ) {
		info.attributes |= kThemeTrackHasFocus;
	}

	
    if ( !state.isEnabled() ) {
        info.enableState = kThemeTrackDisabled;
    }
    else {
		if ( state.isActive() ) {
			info.enableState = kThemeTrackActive;
		}
		else {
			info.enableState = kThemeTrackInactive;
		}
    }
	
	if ( state.isPressed() ) {
		info.trackInfo.slider.pressState = kThemeThumbPressed;
	}

	bool drawBothSides = false;
	info.trackInfo.slider.thumbDir = 0;
	
    if ( state.isTickMarkingOnBottomRight() && state.isTickMarkingOnTopLeft() ) {
		
		drawBothSides = true;
	}
    else if ( state.isTickMarkingOnBottomRight() ) {
		info.trackInfo.slider.thumbDir = kThemeThumbDownward;	
    }
    else if( state.isTickMarkingOnTopLeft() ) {
		info.trackInfo.slider.thumbDir = kThemeThumbUpward;        
    }

	
	//GetThemeTrackBounds( &info, r );
	//info.bounds = r;

	if ( drawBothSides ) {
		info.trackInfo.slider.thumbDir = kThemeThumbUpward;
		
		if ( noErr != DrawThemeTrackTickMarks( &info, state.tickMarkFrequency_, NULL, 0 ) ) {
			StringUtils::trace( "DrawThemeTrackTickMarks failed\n" );
		}
		
		info.trackInfo.slider.thumbDir = kThemeThumbDownward;
		
		if ( noErr != DrawThemeTrackTickMarks( &info, state.tickMarkFrequency_, NULL, 0 ) ) {
			StringUtils::trace( "DrawThemeTrackTickMarks failed\n" );
		}
	}
	else if ( info.trackInfo.slider.thumbDir != 0 ) {//if info.trackInfo.slider.thumbDir == 0 then no track marks
		if ( noErr != DrawThemeTrackTickMarks( &info, state.tickMarkFrequency_, NULL, 0 ) ) {
			StringUtils::trace( "DrawThemeTrackTickMarks failed\n" );
		}
	}
    
	
	//DrawThemeTrack( &info, NULL, NULL, 0 );
	
}

void OSXContext::drawThemeSlider( Rect* rect, SliderState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;

    ThemeTrackDrawInfo info;
    info.kind = kThemeSlider;//kThemeMediumSlider;
    info.bounds = r;			
								
    info.min = (int)state.min_;
    info.max = (int)state.max_;
    info.value = (int)state.position_;
    info.attributes = state.isVertical() ? 0 :  kThemeTrackHorizontal;
    info.attributes |= /*kThemeTrackRightToLeft |*/ kThemeTrackShowThumb;

    info.trackInfo.slider.thumbDir = 0;
    info.trackInfo.slider.pressState = 0;

	if ( state.isFocused() ) {
		info.attributes |= kThemeTrackHasFocus;
	}

	
    if ( !state.isEnabled() ) {
        info.enableState = kThemeTrackDisabled;
    }
    else {
		if ( state.isActive() ) {
			info.enableState = kThemeTrackActive;
		}
		else {
			info.enableState = kThemeTrackInactive;
		}
    }
	
	if ( state.isPressed() ) {
		info.trackInfo.slider.pressState = kThemeThumbPressed;
	}

	if ( state.isTickMarkingOnBottomRight() && state.isTickMarkingOnTopLeft() ) {
		info.trackInfo.slider.thumbDir = kThemeThumbPlain;
	}
    else if ( state.isTickMarkingOnBottomRight() ) {
		info.trackInfo.slider.thumbDir = kThemeThumbDownward;	
    }
    else if( state.isTickMarkingOnTopLeft() ) {
		info.trackInfo.slider.thumbDir = kThemeThumbUpward;        
    }

	
	GetThemeTrackBounds( &info, r );
	info.bounds = r;
		
	DrawThemeTrack( &info, NULL, NULL, 0 );
}

void OSXContext::drawThemeProgress( Rect* rect, ProgressState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;

    ThemeTrackDrawInfo info;
    info.kind = kThemeProgressBar;
    info.bounds = r;			
								
    info.min = (int)state.min_;
    info.max = (int)state.max_;
    info.value = (int)state.position_;
    info.attributes = state.isVertical() ? 0 :  kThemeTrackHorizontal;
    //info.attributes |= kThemeTrackRightToLeft;

    info.trackInfo.progress.phase = 0;

	if ( state.isFocused() ) {
		info.attributes |= kThemeTrackHasFocus;
	}

	
    if ( !state.isEnabled() ) {
        info.enableState = kThemeTrackDisabled;
    }
    else {
		if ( state.isActive() ) {
			info.enableState = kThemeTrackActive;
		}
		else {
			info.enableState = kThemeTrackInactive;
		}
    }
		
	DrawThemeTrack( &info, NULL, NULL, 0 );
}

void OSXContext::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	CGContextSaveGState( contextID_ );
	
	if ( !state.isEnabled() ) {
		CGContextSetAlpha( contextID_, 0.2 );
	}
	
	
	if ( (rect->getWidth() > image->getWidth()) || (rect->getHeight() > image->getHeight()) ) {
		throw BasicException( MAKE_ERROR_MSG("Invalid image bounds requested"), __LINE__);
	}

    OSXImage* osXimage = (OSXImage*)(image);
    ulong32 imgBoundsWidth = rect->getWidth();
    ulong32 imgBoundsHeight = rect->getHeight();

    if ( (imgBoundsWidth == image->getWidth()) && (imgBoundsHeight == image->getHeight()) ) {
        CGImageRef imgRef = osXimage->getCGImage();
        CGRect imgBounds;
        imgBounds.origin.x = rect->left_;
        imgBounds.origin.y = rect->top_;
        imgBounds.size.width = imgBoundsWidth;
        imgBounds.size.height = imgBoundsHeight;

        CGContextDrawImage( contextID_, imgBounds, imgRef );
    }
    else {
        //create a smaller portion of the image
        int componentCount = image->getType();
        int bitsPerPix = image->getChannelSize() * componentCount;
        int bitsPerComponent = image->getChannelSize();
        int rowStride = ((imgBoundsWidth * bitsPerComponent * componentCount)  + 7)/ 8;

        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        SysPixelType* data = new SysPixelType[imgBoundsWidth*imgBoundsHeight];

        ulong32 imgSize = imgBoundsWidth * imgBoundsHeight * componentCount;
        CGDataProviderRef provider = CGDataProviderCreateWithData( NULL,
                                                                    (char*)data,
                                                                    imgSize,
                                                                    NULL );


        CGImageRef imgRef = CGImageCreate( imgBoundsWidth,
                                   imgBoundsHeight,
                                   image->getChannelSize(),
                                   bitsPerPix,
                                   rowStride,
                                   colorSpace,
                                   kCGImageAlphaNone,
                                   provider,
                                   NULL,
                                   FALSE,
                                   kCGRenderingIntentDefault );

        //copy over bits
        SysPixelType* imageBuf = image->getImageBits()->pixels_;
        SysPixelType* tmpBmpBuf = data;

        ulong32 incr = (ulong32)((rect->top_ * image->getWidth()) + rect->left_);
        imageBuf += incr;
        ulong32 imgWidth = image->getWidth();

        int s = (int)rect->top_;
        int e = (int)rect->bottom_;
        for (int y1=s;y1<e;y1++) {

            memcpy( tmpBmpBuf, imageBuf, imgBoundsWidth*componentCount );

            tmpBmpBuf += imgBoundsWidth;
            imageBuf += imgWidth;
        }

        CGRect imgBounds;
        imgBounds.origin.x = rect->left_;
        imgBounds.origin.y = rect->top_;
        imgBounds.size.width = imgBoundsWidth;
        imgBounds.size.height = imgBoundsHeight;

        CGContextDrawImage( contextID_, imgBounds, imgRef );

        CGColorSpaceRelease(colorSpace);
        CGDataProviderRelease(provider);
        CGImageRelease( imgRef );
        delete [] data;
    }
	
	CGContextRestoreGState( contextID_ );
}

void OSXContext::drawThemeHeader( Rect* rect, ButtonState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
    ThemeButtonDrawInfo btnInfo;
	btnInfo.state = kThemeStateInactive ;
	
	btnInfo.value = kThemeButtonOff;
	
	if ( state.isPressed() ) {
		btnInfo.state |= kThemeStatePressed;
		btnInfo.value = kThemeButtonOn;
	}
	
	if ( state.isActive() && state.isEnabled() ) {
		btnInfo.state |= kThemeStateActive;
	}
	
	
	btnInfo.adornment = kThemeAdornmentNone;		    

    DrawThemeButton( r, kThemeListHeaderButton, &btnInfo, NULL, NULL, NULL, 0 );
}

void OSXContext::drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle )
{
	Rect modRect = *rect;
	modRect.offset( origin_.x_, origin_.y_ );
		
	if ( GraphicsContext::etAllSides == edgeSides ) { 
		OSXRect r = &modRect;
        DrawThemePrimaryGroup( r, state.isActive() ? kThemeStateActive : kThemeStateInactive );
    }
    else {		
        if ( edgeSides & GraphicsContext::etLeftSide ) {			
			OSXRect tmp = &modRect;
			::Rect r = tmp;
            r.right = r.left;
            DrawThemeSeparator( &r, state.isActive() ? kThemeStateActive : kThemeStateInactive );
        }

        if ( edgeSides & GraphicsContext::etRightSide ) {
            OSXRect tmp = &modRect;
			::Rect r = tmp;
            r.left = r.right;
            DrawThemeSeparator( &r, state.isActive() ? kThemeStateActive : kThemeStateInactive );
        }

        if ( edgeSides & GraphicsContext::etTopSide ) {
            OSXRect tmp = &modRect;
			::Rect r = tmp;
            r.bottom = r.top;
            DrawThemeSeparator( &r, state.isActive() ? kThemeStateActive : kThemeStateInactive );
        }

        if ( edgeSides & GraphicsContext::etBottomSide ) {
            OSXRect tmp = &modRect;
			::Rect r = tmp;
            r.top = r.bottom;
            DrawThemeSeparator( &r, state.isActive() ? kThemeStateActive : kThemeStateInactive );
        }
    }
}

void OSXContext::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	
	::Rect bounds;
    ::Point gripperOrigin;
    gripperOrigin.h = (int)tmp.left_;
    gripperOrigin.v = (int)tmp.top_;

    GetThemeStandaloneGrowBoxBounds( gripperOrigin, 0, FALSE, &bounds );
    gripperOrigin.h = (int)(tmp.right_ - (bounds.right-bounds.left));
    gripperOrigin.v = (int)(tmp.bottom_ - (bounds.bottom-bounds.top));

    DrawThemeStandaloneGrowBox( gripperOrigin, 0, FALSE,  state.isActive() ? kThemeStateActive : kThemeStateInactive );
}

void OSXContext::drawThemeBackground( Rect* rect, BackgroundState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	OSStatus err = 0;
	
	Color* color = GraphicsToolkit::getSystemColor( state.colorType_ );
	float colorComponents[4] =
			{color->getRed(),
			color->getGreen(),
			color->getBlue(), 1.0};
	
	switch ( state.colorType_ ) {
		case SYSCOLOR_SHADOW : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
										
		}
		break;
		
		case SYSCOLOR_FACE : {
			err = SetThemeBackground( state.isActive() ? kThemeBrushButtonFaceActive : kThemeBrushButtonFaceInactive,
									32, TRUE );
			if ( err != noErr ) {
				StringUtils::traceWithArgs( Format("SetThemeBackground() failed, err: %d\n") % err );
			}
			EraseRect( r );
		}
		break;
		
		case SYSCOLOR_HIGHLIGHT : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_ACTIVE_CAPTION : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_ACTIVE_BORDER : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_DESKTOP : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_CAPTION_TEXT : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_SELECTION_TEXT : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_INACTIVE_BORDER : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_INACTIVE_CAPTION : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}   
		break;
		
		case SYSCOLOR_TOOLTIP : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_TOOLTIP_TEXT : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_MENU : {		
			
			err = SetThemeBackground( state.isHighlighted() ? kThemeBrushMenuBackgroundSelected : kThemeBrushMenuBackground,
									32, TRUE );
			if ( err != noErr ) {
				StringUtils::traceWithArgs( Format("SetThemeBackground() failed, err: %d\n") % err );
			}
			
			EraseRect( r );
		}
		break;
		
		case SYSCOLOR_MENU_TEXT : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_WINDOW : {
			err = SetThemeBackground( state.isActive() ? kThemeBrushUtilityWindowBackgroundActive : kThemeBrushUtilityWindowBackgroundInactive,
									32, TRUE );
									
			if ( err != noErr ) {
				StringUtils::traceWithArgs( Format("SetThemeBackground() failed, err: %d\n") % err );
			}
			
			EraseRect( r );
		}
		break;
		
		case SYSCOLOR_WINDOW_TEXT : {
			CGContextSetRGBFillColor( contextID_, colorComponents[0], colorComponents[1],
										colorComponents[2], colorComponents[3] );
			CGContextBeginPath( contextID_ );
			CGContextAddRect( contextID_, r );
			CGContextClosePath( contextID_ );
			CGContextFillPath ( contextID_ );
		}
		break;
		
		case SYSCOLOR_WINDOW_FRAME : {
			SetThemeBackground( state.isActive() ? kThemeBrushDocumentWindowBackground : kThemeBrushDocumentWindowBackground,
									32, TRUE );
			EraseRect( r );			
		}
		break;
	}
}


void OSXContext_drawThemeMenuItemText ( const ::Rect * inBounds, SInt16 inDepth, 
										Boolean inIsColorDevice, SInt32 inUserData )
{
	MenuState* state = (MenuState*)inUserData;
	CFTextString cfStr;
	cfStr = state->menuCaption_;
	int menuState;
	if ( state->isActive() ) {
		menuState = kThemeStateActive;
	}
	else if ( state->isSelected() ) {
		menuState = kThemeStatePressed;
	}
	else if ( !state->isEnabled() ) {
		menuState = kThemeStateInactive;
	}
	
	::DrawThemeTextBox( cfStr, kThemeMenuItemFont, menuState, false, inBounds,
			teFlushDefault, NULL );
}
 
void OSXContext::drawThemeMenuItem( Rect* rect, MenuState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	::Point pt;
	::Rect menuRect = r;
	pt.h = menuRect.left;
	pt.v = menuRect.top;	
	
	//LocalToGlobal( &pt );
	
//	menuRect.left = pt.h;
//	menuRect.top = pt.v;
	
	
	pt.h = menuRect.right;
	pt.v = menuRect.bottom;
	LocalToGlobal( &pt );
	
//	menuRect.right = pt.h;
//	menuRect.bottom = pt.v;
	
	::Rect menuItemRect = menuRect;
	
	ThemeMenuState menuState = kThemeMenuActive;
	if ( state.isSelected() ) {
		menuState = kThemeMenuSelected;
	}
	else if ( !state.isEnabled() ) {
		menuState = kThemeMenuDisabled;
	}
	
	MenuItemDrawingUPP menuDrawUPP = NewMenuItemDrawingUPP(OSXContext_drawThemeMenuItemText);
	
    	
	DrawThemeMenuItem( &menuRect, &menuItemRect, menuRect.top, menuRect.bottom, 
						menuState, kThemeMenuItemPlain, menuDrawUPP, (UInt32)&state );
						
	DisposeMenuItemDrawingUPP(menuDrawUPP);
	
}

void OSXContext::drawThemeMenuItemText( Rect* rect, MenuState& state )
{

}

void OSXContext::drawThemeText( Rect* rect, TextState& state )
{
	Rect tmp = *rect;
	tmp.offset( origin_.x_, origin_.y_ );
	OSXRect r = &tmp;
	
	
	ThemeTextColor textColor = kThemeTextColorDialogActive;
	int menuState = kThemeStateActive;
	
	if ( state.isSelected() ) {
		menuState = kThemeStatePressed;
	}
	else if ( (!state.isEnabled()) || (!state.isActive()) ) {
		menuState = kThemeStateInactive;
		textColor = kThemeTextColorDialogInactive;
	}
	
	
	ThemeFontID fontID = 0;
	switch ( state.themeFontType_ ) {
		case GraphicsContext::ttMenuItemFont : {
			fontID = kThemeMenuItemFont;
		}
		break;
		
		case GraphicsContext::ttSelectedMenuItemFont : {
			fontID = kThemeMenuItemFont;
		}
		break;
		
		case GraphicsContext::ttSystemFont : {
			fontID = kThemeSystemFont;
		}
		break;
		
		case GraphicsContext::ttSystemSmallFont : {
			fontID = kThemeSmallSystemFont;
		}
		break;
		
		case GraphicsContext::ttControlFont : {
			fontID = kThemeApplicationFont;
		}
		break;
		
		case GraphicsContext::ttMessageFont : {
			fontID = kThemeAlertHeaderFont;
		}
		break;
		
		case GraphicsContext::ttToolTipFont : {
			fontID = kThemeLabelFont;
		}   
		break;		
	}
	
	/*
	teJustLeft
  teJustCenter
  teJustRight
  teForceLeft		// new names for the Justification (word alignment) styles 
  teFlushDefault	//flush according to the line direction 
  teCenter			//center justify (word alignment) 
  teFlushRight		//flush right for all scripts 
  teFlushLeft
  */
  
	CFTextString cfStr;
	cfStr = state.text_;
	
	::SetThemeTextColor( textColor, 32, true );
	
	::DrawThemeTextBox( cfStr, fontID, menuState, state.wrapText_, r,
						teFlushDefault, NULL );
}
	
	
	
/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:06:00  ddiego
*added missing gtk files
*
*Revision 1.4  2005/01/08 20:52:47  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3.2.3  2005/06/28 04:09:05  ddiego
*adjusted for marcellos change.
*
*Revision 1.3.2.2  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.3.2.1  2005/03/15 01:51:54  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3  2004/12/01 04:31:43  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.5  2004/11/15 05:41:28  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2.2.4  2004/11/06 18:21:51  chriskr
*small bugfixes and optimizations for line-drawing
*
*Revision 1.2.2.3  2004/10/27 03:12:18  ddiego
*integrated chrisk changes
*
*Revision 1.2.2.2  2004/10/23 18:10:46  ddiego
*mac osx updates, some more fixes for dialog code and for command button peer functionality
*
*Revision 1.2.2.1  2004/10/10 15:24:00  ddiego
*updated os x code in graphics stuff.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/08/01 23:40:17  ddiego
*fixed a few osx bugs
*
*Revision 1.1.2.11  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.10.2.7  2004/07/09 02:01:29  ddiego
*more osx updates
*
*Revision 1.1.2.10.2.6  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.10.2.5  2004/06/27 18:19:16  ddiego
*more osx updates
*
*Revision 1.1.2.10.2.4  2004/06/20 00:36:11  ddiego
*finished the new theme API updates
*
*Revision 1.1.2.10.2.3  2004/06/17 03:00:24  ddiego
*further updates to OSX theme compliant drawing code
*
*Revision 1.1.2.10.2.2  2004/06/16 05:18:56  ddiego
*further updates to OSX theme compliant drawing code
*
*Revision 1.1.2.10.2.1  2004/06/15 04:04:38  ddiego
*revamped osx theme drawing API
*
*Revision 1.1.2.10  2004/06/07 03:07:07  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.1.2.9  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.8  2004/05/31 19:42:53  ddiego
*more osx updates
*
*Revision 1.1.2.7  2004/05/31 13:20:58  ddiego
*more osx updates
*
*Revision 1.1.2.6  2004/05/23 14:12:18  ddiego
*osx updates
*
*Revision 1.1.2.5  2004/05/16 02:39:10  ddiego
*OSX code updates
*
*Revision 1.1.2.4  2004/05/07 23:23:33  ddiego
*more osx changes
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.4  2004/02/24 01:42:44  ddiego
*initial OSX ApplicationKit port checkin
*
*Revision 1.1.2.3  2004/02/23 05:51:31  ddiego
*basic GraphicsKit implementation done for OSX
*
*Revision 1.1.2.2  2004/02/22 06:50:22  ddiego
*more progress with the OSX GraphicsKit - almost done!
*
*Revision 1.1.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*/


