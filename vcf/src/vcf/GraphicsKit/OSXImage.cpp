//OSXImage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

OSXImage::OSXImage():
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    grafPort_(0),
    imageRef_(0)
{
    init();
}

OSXImage::OSXImage( const unsigned long& width, const unsigned long& height ):
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    grafPort_(0),
    imageRef_(0)
{
    init();
    setSize( width, height );
}

OSXImage::OSXImage( GraphicsContext* context, Rect* rect ):
    AbstractImage(true),//note: we allocate the memory for the ImageBits pixels
    grafPort_(0),
    imageRef_(0)
{
    init();
    setSize( rect->getWidth(), rect->getHeight() );
    context_->copyContext( Rect(0,0,getWidth(),getHeight()), *rect, context );
}

OSXImage::~OSXImage()
{
    if ( NULL != grafPort_ ) {
        DisposeGWorld( grafPort_ );
        grafPort_ = NULL;
    }

    if ( NULL != imageRef_ ) {
        CGImageRelease( imageRef_ );

        imageRef_ = NULL;
    }
}

void OSXImage::init()
{
    ImageBits::Traits::setChannelType( flags_, ImageBits::Traits::getTraitsChannelType() );
	ImageBits::Traits::setChannelSize( flags_, ImageBits::Traits::getTraitsChannelSize() );
	ImageBits::Traits::setImageType( flags_, ImageBits::Traits::getTraitsImageType() );
	ImageBits::Traits::setPixelLayoutOrder( flags_, Image::ploRGBA );

    context_ = new GraphicsContext(0);
}

void OSXImage::setAlpha( float val )
{
	uchar alphaVal = (uchar) val * 255.0;
	
	SysPixelType* bits = imageBits_->pixels_;
	
	uint32 size = getWidth() * getHeight();
	while ( size > 0 ) {
		bits[size-1].a = alphaVal;
		
		size --;
	}
	
	
}

void OSXImage::createBMP()
{
    if ( NULL != grafPort_ ) {
        DisposeGWorld( grafPort_ );
        grafPort_ = NULL;
    }

    if ( NULL != imageRef_ ) {
        CGImageRelease( imageRef_ );
        imageRef_ = NULL;
    }

    GWorldPtr newGWorld = 0;

    int componentCount = getType();
    int bitsPerPix = getChannelSize() * componentCount;

    int bytesPerRow = (getWidth() * (bitsPerPix/componentCount) * componentCount) / 8;
    ulong32 width = getWidth();
    ulong32 height = getHeight();

    ::Rect boundsRect;
    boundsRect.left = boundsRect.top = 0;
    boundsRect.right = width;
    boundsRect.bottom = height;

	

    OSStatus err = 0;
    err = NewGWorldFromPtr( &newGWorld,
                            k32RGBAPixelFormat,
                            &boundsRect,
                            NULL,
                            NULL,
                            0,
                            (char*)imageBits_->pixels_,
                            bytesPerRow );
							
	//setAlpha( 0.67 );

    if ( noErr == err ) {


        grafPort_ = newGWorld;
        ulong32 imgSize = width * height * componentCount;
        CGDataProviderRef provider = CGDataProviderCreateWithData( NULL,
                                                                    imageBits_->pixels_,
                                                                    imgSize,
                                                                    NULL );

        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

        imageRef_ = CGImageCreate( width,
                                   height,
                                   getChannelSize(),
                                   bitsPerPix,
                                   bytesPerRow,
                                   colorSpace,
                                   kCGImageAlphaNoneSkipFirst,
                                   provider,
                                   NULL,
                                   FALSE,
                                   kCGRenderingIntentDefault );
								   
								   
								   
								   



        CGColorSpaceRelease(colorSpace);
        CGDataProviderRelease(provider);		
		
        //context_->getPeer()->setContextID( (ulong32)grafPort_ );
		OSXContext* peerCtx = (OSXContext*)context_->getPeer();
		peerCtx->setPortFromImage( grafPort_, width, height );
		//CGContextScaleCTM(contextID_, 1, -1);
		
    }
    else {
        throw RuntimeException( MAKE_ERROR_MSG_2("OSXImage failed to create a new GWorld!") );
    }
}

void OSXImage::setSize( const unsigned long & width, const unsigned long & height )
{
    AbstractImage::setSize( width, height );
	createBMP();
}

void OSXImage::beginDrawing()
{
	
	
}

void OSXImage::finishedDrawing()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/27 04:26:05  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.5.2.1  2004/06/20 00:36:11  ddiego
*finished the new theme API updates
*
*Revision 1.1.2.5  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/31 13:20:59  ddiego
*more osx updates
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/23 05:51:31  ddiego
*basic GraphicsKit implementation done for OSX
*
*Revision 1.1.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*/


