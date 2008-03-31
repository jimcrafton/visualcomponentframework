//Win32Context.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/GraphicsKit/AggCommon.h"




#include "thirdparty/common/agg/include/agg_renderer_scanline.h"
#include "thirdparty/common/agg/include/agg_span_allocator.h"
#include "thirdparty/common/agg/include/agg_span_interpolator_linear.h"
#include "thirdparty/common/agg/include/agg_span_image_filter_rgba.h"
#include "thirdparty/common/agg/include/agg_scanline_u.h"


#include "vcf/GraphicsKit/Win32VisualStylesWrapper.h"







using namespace VCF;



Win32Context::Win32Context()
{
	init();
}

Win32Context::Win32Context( const uint32& width, const uint32& height )
{
	init();

	HDC desktopDC = ::GetDC( ::GetDesktopWindow() );

	dc_ = ::CreateCompatibleDC( desktopDC );
	if ( NULL == dc_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Unable to create compatible Device Context for win32 context") );
	}
	memBitmap_ = ::CreateCompatibleBitmap( desktopDC, width, height );
	originalBitmap_ = (HBITMAP)::SelectObject( dc_, memBitmap_ );
	ReleaseDC( ::GetDesktopWindow(), desktopDC );
	isMemoryCtx_ = true;
	if ( NULL == memBitmap_ ){
		//throw exception
		throw RuntimeException( MAKE_ERROR_MSG_2("Unable to create memory bitmap for win32 context") );
	}
}

Win32Context::Win32Context( OSHandleID contextID )
{
	init();
	dc_ = (HDC)contextID;
}

Win32Context::~Win32Context()
{
	if ( NULL != clipRGN_ ) {
		::DeleteObject( clipRGN_ );
	}

	if ( NULL != memBitmap_ ){
		::SelectObject( dc_, originalBitmap_ );
		::DeleteObject( memBitmap_ );
	}

	if ( true == isMemoryCtx_ ) {
		if ( NULL != dc_ ) {
			::DeleteDC( dc_ );
		}
	}
	dc_ = NULL;

	//clearBuffer();
}

void Win32Context::init()
{
	dc_ = NULL;
	clipRGN_ = NULL;
	context_ = NULL;
	memBitmap_ = NULL;
	originalBitmap_ = NULL;

	pathStarted_ = false;
	isMemoryCtx_ = false;
	oldOrigin_.x_ = 0.0;
	oldOrigin_.y_ = 0.0;
	origin_.x_ = 0.0;
	origin_.y_ = 0.0;
	
	alignToBaseline_ = false;

	currentDCState_ = 0;
	currentHBrush_ = NULL;
	currentHPen_ = NULL;
	currentHFont_ = NULL;
}

void Win32Context::releaseHandle()
{
	//clearBuffer();
}



class ColorAlpha {
public:
	ColorAlpha():alphaValue_(255){}
	int alphaValue_;

	int calculate(int alpha, int c, int, int, int) const {
		return alphaValue_;
	}
};

typedef agg::renderer_base<pixfmt> RendererBase;
typedef agg::renderer_scanline_aa_solid<RendererBase> SolidRenderer;
typedef agg::span_allocator<agg::rgba8> SpanAllocator;
typedef agg::span_interpolator_linear<> SpanInterpolator;
typedef agg::span_image_filter_rgba_bilinear_clip<pixfmt,SpanInterpolator> SpanGenerator;
typedef agg::renderer_scanline_aa_solid<RendererBase> RendererType;


void Win32Context::drawGrayScaleImage( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	Matrix2D& currentXFrm = *context_->getCurrentTransform();

	agg::path_storage imagePath;
	imagePath.move_to( imageBounds->left_, imageBounds->top_ );
	imagePath.line_to( imageBounds->right_, imageBounds->top_ );
	imagePath.line_to( imageBounds->right_, imageBounds->bottom_ );
	imagePath.line_to( imageBounds->left_, imageBounds->bottom_ );
	imagePath.close_polygon();

	bool safeToRender = true;

	BITMAPINFO bmpInfo;
	memset( &bmpInfo, 0, sizeof(BITMAPINFO) );
	bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	int destLeft = 0;
	int destTop = 0;

	agg::rasterizer_scanline_aa<> rasterizer;
	agg::scanline_u8 scanLine;

	SysPixelType* bmpBuf = NULL;
	HDC memDC = ::CreateCompatibleDC( NULL );
	HBITMAP hbmp = NULL;
	HBITMAP oldBMP = NULL;
	agg::rendering_buffer imgRenderBuf;

	Rect xfrmedImageRect = *imageBounds;


	bool defaultXFrm = context_->isDefaultTransform();
	if ( !defaultXFrm ) {


		double xx = x * (currentXFrm[Matrix2D::mei00]) +
							y * (currentXFrm[Matrix2D::mei10]) +
								(currentXFrm[Matrix2D::mei20]);

		double yy = x * (currentXFrm[Matrix2D::mei01]) +
							y * (currentXFrm[Matrix2D::mei11]) +
								(currentXFrm[Matrix2D::mei21]);


		agg::trans_affine pathMat;



		pathMat *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
		pathMat *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
		pathMat *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
										Math::degreesToRadians(context_->getShearY()) );

		agg::conv_transform< agg::path_storage > xfrmedImgPath(imagePath,pathMat);

		double vert_x, vert_y;
		xfrmedImgPath.vertex( &vert_x, &vert_y );

		Point p1(vert_x, vert_y );


		xfrmedImgPath.vertex( &vert_x, &vert_y );

		Point p2( vert_x, vert_y );

		if ( p2.x_ > p1.x_ ) {
			xfrmedImageRect.left_ = p1.x_;
		}
		else {
			xfrmedImageRect.left_ = p2.x_;
		}

		if ( p1.x_ < p2.x_ ) {
			xfrmedImageRect.right_ = p2.x_;
		}
		else {
			xfrmedImageRect.right_ = p1.x_;
		}

		if ( p2.y_ > p1.y_ ) {
			xfrmedImageRect.top_ = p1.y_;
		}
		else {
			xfrmedImageRect.top_ = p2.y_;
		}

		if ( p1.y_ < p2.y_ ) {
			xfrmedImageRect.bottom_ = p2.y_;
		}
		else {
			xfrmedImageRect.bottom_ = p1.y_;
		}

		unsigned cmd = xfrmedImgPath.vertex(&vert_x, &vert_y);
		while(!agg::is_stop(cmd)) {
			if ( xfrmedImageRect.left_ > vert_x ) {
				xfrmedImageRect.left_ = vert_x;
			}

			if ( xfrmedImageRect.right_ < vert_x ) {
				xfrmedImageRect.right_ = vert_x;
			}

			if ( xfrmedImageRect.top_ > vert_y ) {
				xfrmedImageRect.top_ = vert_y;
			}

			if ( xfrmedImageRect.bottom_ < vert_y ) {
				xfrmedImageRect.bottom_ = vert_y;
			}

			cmd = xfrmedImgPath.vertex(&vert_x, &vert_y);
		}

		xfrmedImageRect.offset( xx, yy );
		xfrmedImageRect.inflate( 2, 2 );


		double imageTX = imageBounds->getWidth()/2.0;

		double imageTY = imageBounds->getHeight()/2.0;


		double xfrmImageTX = xfrmedImageRect.getWidth()/2.0;
		double xfrmImageTY = xfrmedImageRect.getHeight()/2.0;

		agg::trans_affine pathMat2;


		pathMat2 *= agg::trans_affine_translation( -imageTX, -imageTY );
		pathMat2 *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
		pathMat2 *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
		pathMat2 *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
										Math::degreesToRadians(context_->getShearY()) );
		pathMat2 *= agg::trans_affine_translation( xfrmImageTX, xfrmImageTY );


		agg::conv_transform< agg::path_storage > xfrmedImgPath2(imagePath,pathMat2);


		bmpInfo.bmiHeader.biWidth = (int32)xfrmedImageRect.getWidth();
		bmpInfo.bmiHeader.biHeight = (int32)-xfrmedImageRect.getHeight(); // Win32 DIB are upside down - do this to filp it over
		bmpInfo.bmiHeader.biSizeImage = (-bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;

		hbmp = CreateDIBSection ( memDC, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );


		safeToRender = (NULL != hbmp) ? true : false;

		if ( safeToRender ) {

			HBITMAP oldBMP = (HBITMAP)SelectObject( memDC, hbmp );

			BitBlt( memDC, 0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight,
					dc_, xfrmedImageRect.left_, xfrmedImageRect.top_, SRCCOPY );



			imgRenderBuf.attach( (unsigned char*)bmpBuf, bmpInfo.bmiHeader.biWidth,
										-bmpInfo.bmiHeader.biHeight,
										bmpInfo.bmiHeader.biWidth * 4 );



			pixfmt pixf(imgRenderBuf);
			RendererBase rb(pixf);


			agg::trans_affine imageMat;
			imageMat *= agg::trans_affine_translation( -imageTX, -imageTY );
			imageMat *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
			imageMat *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
			imageMat *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
											Math::degreesToRadians(context_->getShearY()) );

			imageMat *= agg::trans_affine_translation( xfrmImageTX, xfrmImageTY );
			imageMat.invert();


			SpanAllocator spanAllocator;

			SpanInterpolator interpolator(imageMat);


			agg::rendering_buffer tmpImgRenderBuf;
			tmpImgRenderBuf.attach( (unsigned char*)image->getData(),
									image->getWidth(),
									image->getHeight(),
									image->getWidth() * image->getType() );

			pixfmt tmpPixf(tmpImgRenderBuf);

			SpanGenerator spanGen(//spanAllocator,
							 tmpPixf,
							 agg::rgba(0, 0, 0, 0.0),
							 interpolator);


			RendererType imageRenderer(rb);



			rasterizer.add_path(xfrmedImgPath2);
			agg::render_scanlines_aa(rasterizer, scanLine, rb, spanAllocator, spanGen );
		}
	}
	else {

		xfrmedImageRect.offset( x, y );

		bmpInfo.bmiHeader.biWidth = (int32)xfrmedImageRect.getWidth();
		bmpInfo.bmiHeader.biHeight = (int32)-xfrmedImageRect.getHeight(); // Win32 DIB are upside down - do this to filp it over
		bmpInfo.bmiHeader.biSizeImage = (-bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;

		hbmp = CreateDIBSection ( memDC, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );


		safeToRender = (NULL != hbmp) ? true : false;

		if ( safeToRender ) {

			HBITMAP oldBMP = (HBITMAP)SelectObject( memDC, hbmp );

			//copy what ever is in the current DC image
			BitBlt( memDC, 0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight,
					dc_, xfrmedImageRect.left_, xfrmedImageRect.top_, SRCCOPY );


			SysPixelType* pixels = (SysPixelType*)bmpBuf;
			int incr = (int32)((imageBounds->top_ * xfrmedImageRect.getWidth()) + imageBounds->left_);
			pixels += incr;

			int s = (int)imageBounds->top_;
			int e = (int)imageBounds->bottom_;
			int boundsWidth = (int32)imageBounds->getWidth();
			int imgWidth = (int32)image->getWidth();
			int xIndex = 0;

			unsigned char* grayPix = (unsigned char*)image->getData();

			for (int y1=s;y1<e;y1++) {
				for ( xIndex=0;xIndex<boundsWidth;xIndex++ ) {
					pixels[xIndex].r = grayPix[xIndex];
					pixels[xIndex].g = grayPix[xIndex];
					pixels[xIndex].b = grayPix[xIndex];
				}

				pixels += boundsWidth;
				grayPix += imgWidth;
			}

/*
			//this is the renderer that agg is going to work with and 
			//will ultimately be dumped to the DC
			imgRenderBuf.attach( (unsigned char*)bmpBuf, bmpInfo.bmiHeader.biWidth,
										-bmpInfo.bmiHeader.biHeight,
										bmpInfo.bmiHeader.biWidth * 4 );


			agg::trans_affine imageMat;
			pixfmt pixf(imgRenderBuf);
			RendererBase rb(pixf);
			SpanAllocator spanAllocator;
			SpanInterpolator interpolator(imageMat);

			agg::rendering_buffer tmpImgRenderBuf;
			tmpImgRenderBuf.attach( (unsigned char*)image->getData(),
									image->getWidth(),
									image->getHeight(),
									image->getWidth() * image->getType() );

			pixfmt tmpPixf(tmpImgRenderBuf);


			//image->getImageBits()->attachRenderBuffer( image->getWidth(), image->getHeight() );

			SpanGenerator spanGen(//spanAllocator,
							 tmpPixf,
							 agg::rgba(0, 0, 0, 0.0),
							 interpolator);
			RendererType imageRenderer(rb);



			//rasterizer.add_path(imagePath);
			//rasterizer.render(scanLine, imageRenderer);*/
		}
	}


	if ( safeToRender ) {
		SetDIBitsToDevice( dc_,
								(int32)xfrmedImageRect.left_,
								(int32)xfrmedImageRect.top_,
								(int32)xfrmedImageRect.getWidth(),
								(int32)xfrmedImageRect.getHeight(),
								0,
								0,
								0,
								(int32)xfrmedImageRect.getHeight(),
								bmpBuf,
								&bmpInfo,
								DIB_RGB_COLORS );

		SelectObject( memDC, oldBMP );
		DeleteObject( hbmp );
		DeleteDC( memDC );
	}
}

void Win32Context::bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image )
{

	HPALETTE pal = NULL;
	HPALETTE oldPalette = NULL;
	BITMAPINFO* bmpInfo = NULL;
	void* imageBuf = image->getData();
	
	HDC srcDC = NULL;

	HPALETTE p = (HPALETTE) GetCurrentObject( dc_, OBJ_PAL );

	if ( image->getType() == Image::itColor ) {
		Win32Image* win32image = (Win32Image*)(image);

		pal = win32image->palette_;
		bmpInfo = &win32image->getBMPInfo();
		srcDC = win32image->getDC();
	}
	else if ( image->getType() == Image::itGrayscale ) { 
		Win32GrayScaleImage* win32image = (Win32GrayScaleImage*)(image);
		pal = win32image->palette_;
		bmpInfo = &win32image->getBMPInfo();
		srcDC = win32image->getDC();
	}	


	if ( NULL != pal ){
		oldPalette = ::SelectPalette( dc_, pal, FALSE );
		::RealizePalette( dc_ );
	}

	int res = ::BitBlt( dc_, (int32)x,
							(int32)y,
							(int32)imageBounds->getWidth(),
							(int32)imageBounds->getHeight(),
							srcDC,
							imageBounds->left_,
							imageBounds->top_,
							SRCCOPY );

	//int res = SetDIBitsToDevice( dc_,
	//						(int32)x,
	//						(int32)y,
	//						(int32)imageBounds->getWidth(),
	//						(int32)imageBounds->getHeight(),
	//						imageBounds->left_,
	//						imageBounds->top_,
	//						0,
	//						(int32)image->getHeight(),
	//						imageBuf,
	//						bmpInfo,
	//						DIB_RGB_COLORS );

	

	if ( NULL != oldPalette ){
		::SelectPalette( dc_, oldPalette, FALSE );
	}
}

void Win32Context::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode )
{
	//checkHandle();


	if ( (imageBounds->getWidth() > image->getWidth()) || (imageBounds->getHeight() > image->getHeight()) ) {
		throw BasicException( MAKE_ERROR_MSG("Invalid image bounds requested"), __LINE__);
	}


	if ( image->getType() == Image::itGrayscale ) {
		drawGrayScaleImage( x, y, imageBounds, image );
		return;
	}


	//drawImageAGG( x, y, imageBounds, image );
	//return;


	Matrix2D& currentXFrm = *context_->getCurrentTransform();

	if ( !context_->isDefaultTransform() ) {

		bool safeToRender = true;

		double xx = x * (currentXFrm[Matrix2D::mei00]) +
							y * (currentXFrm[Matrix2D::mei10]) +
								(currentXFrm[Matrix2D::mei20]);

		double yy = x * (currentXFrm[Matrix2D::mei01]) +
							y * (currentXFrm[Matrix2D::mei11]) +
								(currentXFrm[Matrix2D::mei21]);


		agg::trans_affine pathMat;



		pathMat *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
		pathMat *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
		pathMat *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
										Math::degreesToRadians(context_->getShearY()) );



		agg::path_storage imagePath;
		imagePath.move_to( imageBounds->left_, imageBounds->top_ );
		imagePath.line_to( imageBounds->right_, imageBounds->top_ );
		imagePath.line_to( imageBounds->right_, imageBounds->bottom_ );
		imagePath.line_to( imageBounds->left_, imageBounds->bottom_ );
		imagePath.close_polygon();




		agg::conv_transform< agg::path_storage > xfrmedImgPath(imagePath,pathMat);

		double vert_x, vert_y;
		xfrmedImgPath.vertex( &vert_x, &vert_y );

		Rect xfrmedImageRect;
		Point p1(vert_x, vert_y);

		xfrmedImgPath.vertex( &vert_x, &vert_y );

		Point p2(vert_x, vert_y );

		if ( p2.x_ > p1.x_ ) {
			xfrmedImageRect.left_ = p1.x_;
		}
		else {
			xfrmedImageRect.left_ = p2.x_;
		}

		if ( p1.x_ < p2.x_ ) {
			xfrmedImageRect.right_ = p2.x_;
		}
		else {
			xfrmedImageRect.right_ = p1.x_;
		}

		if ( p2.y_ > p1.y_ ) {
			xfrmedImageRect.top_ = p1.y_;
		}
		else {
			xfrmedImageRect.top_ = p2.y_;
		}

		if ( p1.y_ < p2.y_ ) {
			xfrmedImageRect.bottom_ = p2.y_;
		}
		else {
			xfrmedImageRect.bottom_ = p1.y_;
		}



		unsigned cmd = xfrmedImgPath.vertex(&vert_x, &vert_y);
		while(!agg::is_stop(cmd)) {

			if ( xfrmedImageRect.left_ > vert_x ) {
				xfrmedImageRect.left_ = vert_x;
			}

			if ( xfrmedImageRect.right_ < vert_x ) {
				xfrmedImageRect.right_ = vert_x;
			}

			if ( xfrmedImageRect.top_ > vert_y ) {
				xfrmedImageRect.top_ = vert_y;
			}

			if ( xfrmedImageRect.bottom_ < vert_y ) {
				xfrmedImageRect.bottom_ = vert_y;
			}

			cmd = xfrmedImgPath.vertex(&vert_x, &vert_y);
		}

		xfrmedImageRect.offset( xx, yy );
		xfrmedImageRect.inflate( 2, 2 );


		double imageTX = imageBounds->getWidth()/2.0;

		double imageTY = imageBounds->getHeight()/2.0;


		double xfrmImageTX = xfrmedImageRect.getWidth()/2.0;
		double xfrmImageTY = xfrmedImageRect.getHeight()/2.0;

		agg::trans_affine pathMat2;


		pathMat2 *= agg::trans_affine_translation( -imageTX, -imageTY );
		pathMat2 *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
		pathMat2 *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
		pathMat2 *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
										Math::degreesToRadians(context_->getShearY()) );
		pathMat2 *= agg::trans_affine_translation( xfrmImageTX, xfrmImageTY );




		agg::conv_transform< agg::path_storage > xfrmedImgPath2(imagePath,pathMat2);

		HBitmap32Bit hbmp;
		size_t hbmpWidth = xfrmedImageRect.getWidth();
		size_t hbmpHeight = xfrmedImageRect.getHeight();

		SysPixelType* bmpBuf = NULL;

		hbmp.setSize( hbmpWidth, hbmpHeight );


		bmpBuf = (SysPixelType*) hbmp.data();



		safeToRender = (hbmp != NULL) ? true : false;

		if ( safeToRender ) {
			BitBlt( hbmp.dc(), 0, 0, hbmpWidth, hbmpHeight,
					dc_, xfrmedImageRect.left_, xfrmedImageRect.top_, SRCCOPY );


			agg::rendering_buffer xfrmImgRenderBuf;
			xfrmImgRenderBuf.attach( (unsigned char*)bmpBuf, hbmpWidth,
										hbmpHeight,	hbmpWidth * 4 );



			pixfmt pixf(xfrmImgRenderBuf);
			RendererBase rb(pixf);

			agg::trans_affine imageMat;
			imageMat *= agg::trans_affine_translation( -imageTX, -imageTY );
			imageMat *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
			imageMat *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
			imageMat *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
											Math::degreesToRadians(context_->getShearY()) );

			imageMat *= agg::trans_affine_translation( xfrmImageTX, xfrmImageTY );
			imageMat.invert();


			SpanAllocator spanAllocator;

			SpanInterpolator interpolator(imageMat);



			ColorPixels pix(image);			

			pixfmt imgPixf(pix);
			SpanGenerator spanGen( imgPixf,
							 agg::rgba(0, 0, 0, 0.0),
							 interpolator);

			agg::rasterizer_scanline_aa<> rasterizer;
			agg::scanline_u8 scanLine;

			rasterizer.add_path(xfrmedImgPath2);
			agg::render_scanlines_aa(rasterizer, scanLine, rb, spanAllocator, spanGen );


			SetDIBitsToDevice( dc_,
								(int32)xfrmedImageRect.left_,
								(int32)xfrmedImageRect.top_,
								(int32)xfrmedImageRect.getWidth(),
								(int32)xfrmedImageRect.getHeight(),
								0,
								0,
								0,
								(int32)xfrmedImageRect.getHeight(),
								bmpBuf,
								hbmp.bmpInfo(),
								DIB_RGB_COLORS );
		}
	}
	else {

		Win32Image* win32image = (Win32Image*)(image);
		if ( NULL != win32image ){
			//HDC bmpDC = win32image->getDC();
			
			HPALETTE oldPalette = NULL;
			if ( NULL != win32image->palette_ ){
				oldPalette = ::SelectPalette( dc_, win32image->palette_, FALSE );
				::RealizePalette( dc_ );
			}

			BITMAPINFO bmpInfo;
			memset( &bmpInfo, 0, sizeof(BITMAPINFO) );
			//memset( &bmpInfo.bmiHeader, 0, sizeof (BITMAPINFOHEADER) );
			bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
			bmpInfo.bmiHeader.biWidth = (int32)imageBounds->getWidth();
			bmpInfo.bmiHeader.biHeight = (int32)-imageBounds->getHeight(); // Win32 DIB are upside down - do this to filp it over
			bmpInfo.bmiHeader.biPlanes = 1;
			bmpInfo.bmiHeader.biBitCount = 32;
			bmpInfo.bmiHeader.biCompression = BI_RGB;

			bmpInfo.bmiHeader.biSizeImage = (bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;



			SysPixelType* bmpBuf = NULL;
			SysPixelType* tmpBmpBuf = NULL;


			HBITMAP hbmp = CreateDIBSection ( dc_, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );


			ColorPixels pix(image);
			SysPixelType* imageBuf = pix;

			if ( NULL != hbmp ) {

				int incr = (int32)((imageBounds->top_ * image->getWidth()) + imageBounds->left_);
				imageBuf += incr;
				tmpBmpBuf = bmpBuf;
				int imgWidth = image->getWidth();
				int wIncr = (int32)imageBounds->getWidth();
				int s = (int)imageBounds->top_;
				int e = (int)imageBounds->bottom_;

				for (int y1=s;y1<e;y1++) {
					int xIndex = 0;

					for ( xIndex=0;xIndex<wIncr;xIndex++ ) {
						tmpBmpBuf[xIndex].r = imageBuf[xIndex].r;
						tmpBmpBuf[xIndex].g = imageBuf[xIndex].g;
						tmpBmpBuf[xIndex].b = imageBuf[xIndex].b;
						tmpBmpBuf[xIndex].a = 0; //JC don't use the alpha val here it mucks
												//up the transparent drawing code.
												//we can replace this once we add in real transparency
					}

					tmpBmpBuf += wIncr;
					imageBuf += imgWidth;
				}

				if ( true == image->isTransparent() )  {
					Color* imageTransColor = image->getTransparencyColor();
					COLORREF transColor = RGB( imageTransColor->getRed()*255,
						imageTransColor->getGreen()*255,
						imageTransColor->getBlue()*255 );




					Win32Context::drawTransparentBitmap( dc_, hbmp, (short)x, (short)y, transColor );


				}
				else {
					HDC tdc = CreateCompatibleDC(NULL);
					SelectObject( tdc, hbmp );

					//SetDIBitsToDevice( dc_,
					//					(int32)x,
					//					(int32)y,
					//					(int32)imageBounds->getWidth(),
					//					(int32)imageBounds->getHeight(),
					//					0,
					//					0,
					//					0,
					//					(int32)imageBounds->getHeight(),
					//					bmpBuf,
					//					&bmpInfo,
					//					DIB_RGB_COLORS );

					BitBlt( dc_, (int32)x, (int32)y, imageBounds->getWidth(),
							imageBounds->getHeight(),tdc,0,0, SRCCOPY );
					DeleteDC(tdc);
				}

				DeleteObject( hbmp );
			}

			if ( NULL != oldPalette ){
				::SelectPalette( dc_, oldPalette, FALSE );
			}

		}
		else {
			throw InvalidImage( "Image Peer is not usable under MS Windows" );
		}
	}

	//releaseHandle();
}

void Win32Context::drawImageAGG(  const double& x, const double& y, Rect* imageBounds, Image* image )
{
	Matrix2D& currentXFrm = *context_->getCurrentTransform();

	agg::path_storage imagePath;
	imagePath.move_to( imageBounds->left_, imageBounds->top_ );
	imagePath.line_to( imageBounds->right_, imageBounds->top_ );
	imagePath.line_to( imageBounds->right_, imageBounds->bottom_ );
	imagePath.line_to( imageBounds->left_, imageBounds->bottom_ );
	imagePath.close_polygon();

	bool safeToRender = true;

	BITMAPINFO bmpInfo;
	memset( &bmpInfo, 0, sizeof(BITMAPINFO) );
	bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	int destLeft = 0;
	int destTop = 0;

	agg::rasterizer_scanline_aa<> rasterizer;
	agg::scanline_u8 scanLine;

	SysPixelType* bmpBuf = NULL;
	//HDC memDC = ::CreateCompatibleDC( NULL );
	HBitmap32Bit hbmp;
	HBITMAP oldBMP = NULL;
	agg::rendering_buffer imgRenderBuf;

	Rect xfrmedImageRect = *imageBounds;


	bool defaultXFrm = false;//context_->isDefaultTransform();
	if ( !defaultXFrm ) {


		double xx = x * (currentXFrm[Matrix2D::mei00]) +
							y * (currentXFrm[Matrix2D::mei10]) +
								(currentXFrm[Matrix2D::mei20]);

		double yy = x * (currentXFrm[Matrix2D::mei01]) +
							y * (currentXFrm[Matrix2D::mei11]) +
								(currentXFrm[Matrix2D::mei21]);


		agg::trans_affine pathMat;



		pathMat *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
		pathMat *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
		pathMat *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
										Math::degreesToRadians(context_->getShearY()) );

		agg::conv_transform< agg::path_storage > xfrmedImgPath(imagePath,pathMat);


		double vert_x, vert_y;
		xfrmedImgPath.vertex( &vert_x, &vert_y );

		Point p1(vert_x, vert_y );

		xfrmedImgPath.vertex( &vert_x, &vert_y );

		Point p2(vert_x, vert_y );

		if ( p2.x_ > p1.x_ ) {
			xfrmedImageRect.left_ = p1.x_;
		}
		else {
			xfrmedImageRect.left_ = p2.x_;
		}

		if ( p1.x_ < p2.x_ ) {
			xfrmedImageRect.right_ = p2.x_;
		}
		else {
			xfrmedImageRect.right_ = p1.x_;
		}

		if ( p2.y_ > p1.y_ ) {
			xfrmedImageRect.top_ = p1.y_;
		}
		else {
			xfrmedImageRect.top_ = p2.y_;
		}

		if ( p1.y_ < p2.y_ ) {
			xfrmedImageRect.bottom_ = p2.y_;
		}
		else {
			xfrmedImageRect.bottom_ = p1.y_;
		}



		unsigned cmd = xfrmedImgPath.vertex(&vert_x, &vert_y);
		while(!agg::is_stop(cmd)) {

			if ( xfrmedImageRect.left_ > vert_x ) {
				xfrmedImageRect.left_ = vert_x;
			}

			if ( xfrmedImageRect.right_ < vert_x ) {
				xfrmedImageRect.right_ = vert_x;
			}

			if ( xfrmedImageRect.top_ > vert_y ) {
				xfrmedImageRect.top_ = vert_y;
			}

			if ( xfrmedImageRect.bottom_ < vert_y ) {
				xfrmedImageRect.bottom_ = vert_y;
			}

			cmd = xfrmedImgPath.vertex(&vert_x, &vert_y);
		}

		xfrmedImageRect.offset( xx, yy );
		//xfrmedImageRect.inflate( 2, 2 );


		double imageTX = imageBounds->getWidth()/2.0;

		double imageTY = imageBounds->getHeight()/2.0;


		double xfrmImageTX = xfrmedImageRect.getWidth()/2.0;
		double xfrmImageTY = xfrmedImageRect.getHeight()/2.0;

		agg::trans_affine pathMat2;


		pathMat2 *= agg::trans_affine_translation( -imageTX, -imageTY );
		pathMat2 *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
		pathMat2 *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
		pathMat2 *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
										Math::degreesToRadians(context_->getShearY()) );
		pathMat2 *= agg::trans_affine_translation( xfrmImageTX, xfrmImageTY );


		agg::conv_transform< agg::path_storage > xfrmedImgPath2(imagePath,pathMat2);


		bmpInfo.bmiHeader.biWidth = (int32)xfrmedImageRect.getWidth();
		bmpInfo.bmiHeader.biHeight = (int32)-xfrmedImageRect.getHeight(); // Win32 DIB are upside down - do this to filp it over
		bmpInfo.bmiHeader.biSizeImage = (-bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;

		hbmp.setSize( bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight );
		bmpBuf = (SysPixelType*) hbmp.data();

		//hbmp = CreateDIBSection ( memDC, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );


		safeToRender = (hbmp != NULL) ? true : false;

		if ( safeToRender ) {

			//HBITMAP oldBMP = (HBITMAP)SelectObject( memDC, hbmp );

			BitBlt( hbmp.dc(), 0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight,
					dc_, xfrmedImageRect.left_, xfrmedImageRect.top_, SRCCOPY );



			imgRenderBuf.attach( (unsigned char*)bmpBuf, bmpInfo.bmiHeader.biWidth,
										-bmpInfo.bmiHeader.biHeight,
										bmpInfo.bmiHeader.biWidth * 4 );



			pixfmt pixf(imgRenderBuf);
			RendererBase rb(pixf);


			agg::trans_affine imageMat;
			imageMat *= agg::trans_affine_translation( -imageTX, -imageTY );
			imageMat *= agg::trans_affine_rotation( Math::degreesToRadians( context_->getRotation() ) );
			imageMat *= agg::trans_affine_scaling( context_->getScaleX(), context_->getScaleY() );
			imageMat *= agg::trans_affine_skewing( Math::degreesToRadians(context_->getShearX()),
											Math::degreesToRadians(context_->getShearY()) );

			imageMat *= agg::trans_affine_translation( xfrmImageTX, xfrmImageTY );
			imageMat.invert();


			SpanAllocator spanAllocator;

			SpanInterpolator interpolator(imageMat);


			agg::rendering_buffer tmpImgRenderBuf;
			tmpImgRenderBuf.attach( (unsigned char*)image->getData(),
									image->getWidth(),
									image->getHeight(),
									image->getWidth() * image->getType() );

			pixfmt tmpPixf(tmpImgRenderBuf);
			SpanGenerator spanGen(//spanAllocator,
							 tmpPixf,
							 agg::rgba(0, 0, 0, 0.0),
							 interpolator);


			RendererType imageRenderer(rb);



			rasterizer.add_path(xfrmedImgPath2);
			agg::render_scanlines_aa(rasterizer, scanLine, rb, spanAllocator, spanGen );
		}
	}
	else {
		bmpInfo.bmiHeader.biWidth = (int32)xfrmedImageRect.getWidth();
		bmpInfo.bmiHeader.biHeight = (int32)-xfrmedImageRect.getHeight(); // Win32 DIB are upside down - do this to filp it over
		bmpInfo.bmiHeader.biSizeImage = (-bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;

		hbmp.setSize( bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight ); // = CreateDIBSection ( memDC, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );

		bmpBuf = (SysPixelType*)hbmp.data();

		safeToRender = (hbmp != NULL) ? true : false;

		if ( safeToRender ) {

			//HBITMAP oldBMP = (HBITMAP)SelectObject( memDC, hbmp );

			//BitBlt( hbmp.dc(), 0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight,
			//		dc_, xfrmedImageRect.left_, xfrmedImageRect.top_, SRCCOPY );



			imgRenderBuf.attach( (unsigned char*)bmpBuf, bmpInfo.bmiHeader.biWidth,
										-bmpInfo.bmiHeader.biHeight,
										bmpInfo.bmiHeader.biWidth * 4 );


			agg::trans_affine imageMat = agg::trans_affine_translation(x, y);
			imageMat.invert();

			pixfmt pixf(imgRenderBuf);
			RendererBase rb(pixf);
			SpanAllocator spanAllocator;
			SpanInterpolator interpolator(imageMat);

			agg::rendering_buffer tmpImgRenderBuf;
			tmpImgRenderBuf.attach( (unsigned char*)image->getData(),
									image->getWidth(),
									image->getHeight(),
									image->getWidth() * image->getType() );

			pixfmt tmpPixf(tmpImgRenderBuf);

			//image->getImageBits()->attachRenderBuffer( image->getWidth(), image->getHeight() );

			SpanGenerator spanGen(//spanAllocator,
							 tmpPixf,
							 agg::rgba(0, 234, 0, 0.0),
							 interpolator);
			RendererType imageRenderer(rb);



			rasterizer.add_path(imagePath);
			agg::render_scanlines_aa(rasterizer, scanLine, rb, spanAllocator, spanGen );
		}
	}


	if ( safeToRender ) {
		SetDIBitsToDevice( dc_,
								(int32)xfrmedImageRect.left_,
								(int32)xfrmedImageRect.top_,
								(int32)xfrmedImageRect.getWidth(),
								(int32)xfrmedImageRect.getHeight(),
								0,
								0,
								0,
								(int32)xfrmedImageRect.getHeight(),
								bmpBuf,
								&bmpInfo,
								DIB_RGB_COLORS );
		//SelectObject( memDC, oldBMP );
		//DeleteObject( hbmp );
		//DeleteDC( memDC );
	}
}

void Win32Context::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	int fixVal = 0;
	if ( true == inFillPath_ ){
		fixVal = 1;
	}
	::Rectangle( dc_, (int32)x1, (int32)y1, (int32)(x2 + fixVal), (int32)(y2 + fixVal) );
}

void Win32Context::roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
							 const double & xc, const double & yc)
{
	int fixVal = 0;
	if ( true == inFillPath_ ){
		fixVal = 1;
	}

	::RoundRect( dc_, (int32)x1, (int32)y1, (int32)x2 + fixVal, (int32)y2 + fixVal, (int32)xc, (int32)yc );
}

void Win32Context::ellipse(const double & x1, const double & y1, const double & x2, const double & y2)
{

	pathStarted_ = true;
	//swap out the values to ensure they are normalized since windows is brain dead about this
	double ax1 = x1;
	double ay1 = y1;
	double ax2 = x2;
	double ay2 = y2;

	double tmp = x2;
	if ( ax1 > ax2 ) {
		ax2 = ax1;
		ax1 = tmp;
	}
	tmp = ay2;
	if ( ay1 > ay2 ) {
		ay2 = ay1;
		ay1 = tmp;
	}

	int fixVal = 0;
	if ( true == inFillPath_ ){
		fixVal = 1;
	}

	::Ellipse( dc_, (int32)ax1, (int32)ay1, (int32)(ax2 + fixVal), (int32)(ay2 + fixVal) );
}

void Win32Context::arc(const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
					   const double & y3, const double & x4, const double & y4)
{

	pathStarted_ = true;
	//swap out the values to ensure they are normalized since windows is brain dead about this
	double ax1 = x1;
	double ay1 = y1;
	double ax2 = x2;
	double ay2 = y2;

	double tmp = x2;
	if ( ax1 > ax2 ) {
		ax2 = ax1;
		ax1 = tmp;
	}
	tmp = ay2;
	if ( ay1 > ay2 ) {
		ay2 = ay1;
		ay1 = tmp;
	}

	int fixVal = 0;
	if ( true == inFillPath_ ){
		fixVal = 1;
	}

	::Arc( dc_, (int32)ax1, (int32)ay1, (int32)ax2 + fixVal, (int32)ay2 + fixVal,
				(int32)x3, (int32)y3, (int32)x4, (int32)y4 );
}


void Win32Context::polyline( const std::vector<Point>& pts)
{
	POINT* polyPts = new POINT[pts.size()];
	std::vector<Point>::const_iterator it = pts.begin();
	int i =0;
	while ( it != pts.end() ) {
		const Point& pt = *it;

		polyPts[i].x = (int32)pt.x_;
		polyPts[i].y = (int32)pt.y_;
		it++;
		i++;
	}
	if ( inFillPath_ ){
		::Polygon( dc_, polyPts, pts.size() );
	}
	else{
		::Polyline( dc_, polyPts, pts.size() );
	}

	delete[] polyPts;
}

void Win32Context::curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4 )
{
	POINT bezPts[4];
	memset( &bezPts[0], 0, sizeof(bezPts[0]) * 4 );

	bezPts[0].x = (int32)x1;
	bezPts[0].y = (int32)y1;

	bezPts[1].x = (int32)x2;
	bezPts[1].y = (int32)y2;

	bezPts[2].x = (int32)x3;
	bezPts[2].y = (int32)y3;

	bezPts[3].x = (int32)x4;
	bezPts[3].y = (int32)y4;

	if ( inFillPath_ ){
		//::BeginPath( dc_ );
		::MoveToEx( dc_, bezPts[0].x, bezPts[0].y, NULL );
		::PolyBezierTo( dc_, &bezPts[1], 3 );
		//::EndPath( dc_ );
		//::FillPath( dc_ );
	}
	else {
		::PolyBezier( dc_, bezPts, 4 );
	}
}

void Win32Context::lineTo(const double & x, const double & y)
{
	int32 xx = x;
	int32 yy = y;
	::LineTo( dc_, xx, yy );
}

void Win32Context::moveTo(const double & x, const double & y)
{
	int32 xx = x;
	int32 yy = y;
	::MoveToEx( dc_, /*(int32)*/xx, /*(int32)*/yy, NULL );
}

void Win32Context::closePath()
{
	::CloseFigure(dc_);
}


OSHandleID Win32Context::getContextID()
{
	return (OSHandleID)dc_;
}

void Win32Context::setOrigin( const double& x, const double& y )
{
	checkHandle();

	POINT pt = {0,0};
	int err = ::SetViewportOrgEx( dc_, (int32)x, (int32)y, &pt );
	if ( !err ) {
		err = GetLastError();
	}

	origin_.x_ = x;
	origin_.y_ = y;

	oldOrigin_.x_ = pt.x;
	oldOrigin_.y_ = pt.y;

	releaseHandle();
}

Point Win32Context::getOrigin()
{
	checkHandle();
	POINT pt = {0,0};
	::GetViewportOrgEx( dc_, &pt );
	origin_.x_ = pt.x;
	origin_.y_ = pt.y;

	releaseHandle();

	return origin_;
}

void Win32Context::copyContext( const Rect& sourceRect,
								const Rect& destRect,
								ContextPeer* sourceContext )
{
	if ( NULL != sourceContext ){
		checkHandle();

		HDC dc = (HDC)sourceContext->getContextID();



		::BitBlt( dc_, (int32)destRect.left_, (int32)destRect.top_,
					destRect.getWidth(), destRect.getHeight(),
					dc, sourceRect.left_, sourceRect.top_, SRCCOPY );


		releaseHandle();

	}
	//else throw exception ???
}

bool Win32Context::isMemoryContext()
{
	return isMemoryCtx_;
}

void Win32Context::copyToImage( Win32Image* image )
{

}

HDC Win32Context::getDC()
{
	return dc_;
}

void Win32Context::setContext( GraphicsContext* context )
{
	context_ = context;
}

GraphicsContext* Win32Context::getContext()
{
	return context_;
}

void Win32Context::setContextID( OSHandleID handle )
{
	dc_ = (HDC)handle;
}


void Win32Context::textAt( const Rect& bounds, const String& text, const int32& drawOptions )
{
	//checkHandle();
	if ( NULL == context_ ){
		//throw exception !
	}


	UINT textAlignment = (alignToBaseline_) ? TA_BASELINE | TA_LEFT : TA_TOP | TA_LEFT ;
	UINT oldTextAlignment = ::SetTextAlign( dc_, textAlignment );



	RECT r = {0,0,0,0};
	r.left = (int32)bounds.left_;
	r.right = (int32)bounds.right_;
	r.top = (int32)bounds.top_;
	r.bottom = (int32)bounds.bottom_;


	if ( r.left > r.right ) {
		r.left = r.right;
	}

	if ( (r.right == r.left) || (r.bottom == r.top) ) {
		//no-op! no height or no width
		return;
	}




	UINT formatOptions = 0;

	Matrix2D& currentXFrm = *context_->getCurrentTransform();

	if ( !context_->isDefaultTransform() ) {
		formatOptions = DT_NOCLIP; //this was put here to make rotated text look better JC
	}



	if ( drawOptions & GraphicsContext::tdoLeftAlign ) {
		formatOptions |= DT_LEFT;
	}
	else if ( drawOptions & GraphicsContext::tdoCenterHorzAlign ) {
		formatOptions |= DT_CENTER;
	}
	else if ( drawOptions & GraphicsContext::tdoRightAlign ) {
		formatOptions |= DT_RIGHT;
	}

	if ( drawOptions & GraphicsContext::tdoTopAlign ) {
		formatOptions |= DT_TOP;
	}
	else if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
		formatOptions |= DT_VCENTER;
	}
	else if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
		formatOptions |= DT_BOTTOM;
	}

	if ( drawOptions & GraphicsContext::tdoWordWrap ) {
		formatOptions |= DT_WORDBREAK;
	}
	else {
		formatOptions |= DT_WORD_ELLIPSIS | DT_SINGLELINE;
	}

	formatOptions |= DT_EXPANDTABS;


	


	/* Not using for now
	DRAWTEXTPARAMS extraParams = {0};
	extraParams.cbSize = sizeof(DRAWTEXTPARAMS);
	*/

	/*
	*determine the size of the text and adjust the rect accordingly.
	*can't use DrawText to figure out the rect because it doesn't
	*calc the bounds correctly.
	*/
	//SIZE textSize = {0};
	//GetTextExtentPoint32( dc_, text.c_str(), text.size(), &textSize );
	//r.right = r.left + textSize.cx;
	//r.bottom = r.top + textSize.cy;

	
	if ( System::isUnicodeEnabled() ) {
		VCFChar* textToDraw = new VCFChar[text.size()+1];
		memset( textToDraw, 0, (text.size()+1)*sizeof(VCFChar) );
		text.copy( textToDraw, text.size() );

		if ( drawOptions & GraphicsContext::tdoWordWrap ) {
			if ( (drawOptions & GraphicsContext::tdoCenterVertAlign) || 
				(drawOptions & GraphicsContext::tdoBottomAlign) ) {
				RECT r2 = r;

				int h = DrawTextExW( dc_, textToDraw, text.size(), &r, formatOptions | DT_CALCRECT, NULL );
				
				if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
					r.left = r2.left;	
					r.right = r2.right;
					r.top = r2.top + ((r2.bottom - r2.top)/2) - (h/2);
					r.bottom = r.top + h;
				}
				else if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
					r.left = r2.left;	
					r.right = r2.right;
					r.top = r2.bottom  - h;
					r.bottom = r.top + h;
				}
			}
		}


		DrawTextExW( dc_, textToDraw, text.size(), &r, formatOptions, NULL );

		//clean up after ourselves
		delete[] textToDraw;
	}
	else {
		AnsiString tmpText = text;
		char* textToDraw = new char[tmpText.size()+1];
		memset( textToDraw, 0, (tmpText.size()+1)*sizeof(char) );
		text.copy( textToDraw, tmpText.size() );
		
		if ( drawOptions & GraphicsContext::tdoWordWrap ) {
			if ( (drawOptions & GraphicsContext::tdoCenterVertAlign) || 
				(drawOptions & GraphicsContext::tdoBottomAlign) ) {
				RECT r2 = r;

				int h = DrawTextExA( dc_, textToDraw, tmpText.size(), &r, formatOptions | DT_CALCRECT, NULL );
				
				if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
					r.left = r2.left;	
					r.right = r2.right;
					r.top = r2.top + ((r2.bottom - r2.top)/2) - (h/2);
					r.bottom = r.top + h;
				}
				else if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
					r.left = r2.left;	
					r.right = r2.right;
					r.top = r2.bottom  - h;
					r.bottom = r.top + h;
				}
			}
		}

		DrawTextExA( dc_, textToDraw, tmpText.size(), &r, formatOptions, NULL );

		//clean up after ourselves
		delete[] textToDraw;
	}





	//releaseHandle();
}


double Win32Context::getTextWidth( const String& text )
{
	double result = 0.0;
	checkHandle();
	if ( NULL == context_ ){
		//throw exception !
	}
	Font* ctxFont = context_->getCurrentFont();
	if ( NULL == ctxFont ){
		//throw exception
	}
	FontPeer* fontImpl = ctxFont->getFontPeer();

	if ( NULL == fontImpl ){
		//throw exception
	}





	HFONT font = NULL;

	prepareDCWithContextFont( font );

	HFONT oldFont = (HFONT)::SelectObject( dc_, font );

	SIZE textSize = {0,0};

	if ( String::npos != text.find( "\t" ) ) {
		RECT r = {0,0,0,0};

		if ( System::isUnicodeEnabled() ) {
			DrawTextW( dc_, text.c_str(), text.size(), &r, DT_CALCRECT | DT_EXPANDTABS | DT_SINGLELINE | DT_LEFT );
		}
		else {
			AnsiString tmpText = text;

			DrawTextA( dc_, tmpText.c_str(), tmpText.size(), &r, DT_CALCRECT | DT_EXPANDTABS | DT_SINGLELINE | DT_LEFT );
		}

		result = r.right - r.left;
	}
	else {
		if ( System::isUnicodeEnabled() ) {
			GetTextExtentPoint32W( dc_, text.c_str(), text.size(), &textSize );
		}
		else {
			GetTextExtentPoint32A( dc_, text.ansi_c_str(), text.size(), &textSize );
		}

		result = textSize.cx;
	}

	::SelectObject( dc_, oldFont );
	::DeleteObject( font );
	releaseHandle();
	return result;
}

double Win32Context::getTextHeight( const String& text )
{
	checkHandle();
	if ( NULL == context_ ){
		//throw exception !
	}
	Font* ctxFont = context_->getCurrentFont();
	if ( NULL == ctxFont ){
		//throw exception
	}
	FontPeer* fontImpl = ctxFont->getFontPeer();

	if ( NULL == fontImpl ){
		//throw exception
	}

	HFONT font = NULL;

	/*
	if ( System::isUnicodeEnabled() ) {
		LOGFONTW* logFont = (LOGFONTW*)fontImpl->getFontHandleID();

		font = CreateFontIndirectW( logFont );
	}
	else {
		LOGFONTA* logFont = (LOGFONTA*)fontImpl->getFontHandleID();

		font = CreateFontIndirectA( logFont );
	}
	*/
	prepareDCWithContextFont( font );


	HFONT oldFont = (HFONT)::SelectObject( dc_, font );

	SIZE textSize = {0,0};

	if ( System::isUnicodeEnabled() ) {
		GetTextExtentPoint32W( dc_, text.c_str(), text.size(), &textSize );
	}
	else {
		GetTextExtentPoint32A( dc_, text.ansi_c_str(), text.size(), &textSize );
	}


	::SelectObject( dc_, oldFont );
	::DeleteObject( font );

	releaseHandle();
	return textSize.cy;
}

void Win32Context::setTextAlignment( const bool& alignTobaseline )
{
	alignToBaseline_ = alignTobaseline;
}

bool Win32Context::isTextAlignedToBaseline()
{
	return alignToBaseline_;
}

/**
*Utility function to draw a transparent bitmap from MSDN
*HOWTO: Drawing Transparent Bitmaps
*Article ID: Q79212
*JC: This is an awfult lot of shit to just draw a transparent bmp.
*Maybe this will be revisited ???
*/
void Win32Context::drawTransparentBitmap(HDC hdc, HBITMAP hBitmap, int32 xStart,
                           int32 yStart, COLORREF cTransparentColor)
{

	BITMAP     bm;
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT      ptSize;

	hdcTemp = CreateCompatibleDC( NULL );//hdc);
	SelectObject(hdcTemp, hBitmap);   // Select the bitmap

	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;            // Get width of bitmap
	ptSize.y = bm.bmHeight;           // Get height of bitmap
	DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
	// to logical points

	// Create some DCs to hold temporary data.
	hdcBack   = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem    = CreateCompatibleDC(hdc);
	hdcSave   = CreateCompatibleDC(hdc);

	// Create a bitmap for each DC. DCs are required for a number of
	// GDI functions.

	// Monochrome DC
	bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	// Monochrome DC
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	// Each DC must select a bitmap object to store pixel data.
	bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

	// Set proper mapping mode.
	SetMapMode(hdcTemp, GetMapMode(hdc));

	// Save the bitmap sent here, because it will be overwritten.
	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	cColor = SetBkColor(hdcTemp, cTransparentColor);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
		SRCCOPY);

	// Set the background color of the source DC back to the original
	// color.
	SetBkColor(hdcTemp, cColor);

	// Create the inverse of the object mask.
	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
		NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
		SRCCOPY);

	// Mask out the places where the bitmap will be placed.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	// Copy the destination to the screen.
	BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
		SRCCOPY);

	// Place the original bitmap back into the bitmap sent here.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	// Delete the memory bitmaps.
	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	// Delete the memory DCs.
	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

void Win32Context::setClippingRect( Rect* clipRect )
{
	checkHandle();

	if ( NULL != clipRGN_ ) {
		if ( !::DeleteObject( clipRGN_ ) ) {
			StringUtils::trace( Format("Error in DeleteObject( %p )\n") % clipRGN_ % GetLastError() );
		}
	}

	clipRGN_ = NULL;

	if ( NULL != clipRect ) {
		if ( !clipRect->isNull() ) {
			clipRGN_ = CreateRectRgn( (int32)clipRect->left_ + origin_.x_,
										(int32)clipRect->top_ + origin_.y_,
										(int32)clipRect->right_ + origin_.x_,
										(int32)clipRect->bottom_  + origin_.y_);
		}
		else {
			clipRGN_ = NULL;
		}
	}


	if ( ERROR == ::SelectClipRgn( dc_, clipRGN_ ) ){
		StringUtils::trace( Format( "Error in SelectClipRgn( %p, %p )\n" ) % dc_ % clipRGN_ % GetLastError() );
	}

	releaseHandle();
}

void Win32Context::setClippingPath( Path* clippingPath )
{
	checkHandle();

	if ( NULL != clipRGN_ ) {
		::DeleteObject( clipRGN_ );
	}

	clipRGN_ = NULL;

	if ( NULL != clippingPath ) {
		::BeginPath( dc_ );

		std::vector<PathPoint> points;
		Matrix2D* currentXFrm = context_->getCurrentTransform();
		clippingPath->getPoints( points, currentXFrm );


		std::vector<PathPoint>::iterator it = points.begin();

		while ( it != points.end() ) {
			const PathPoint& pt = *it;

			switch ( pt.type_ ){
				case PathPoint::ptMoveTo: {
					MoveToEx( dc_, (int32)pt.point_.x_ + origin_.x_, (int32)pt.point_.y_ + origin_.y_, NULL );
				}
				break;

				case PathPoint::ptLineTo: {
					LineTo( dc_, (int32)pt.point_.x_ + origin_.x_, (int32)pt.point_.y_ + origin_.y_ );
				}
				break;

				case PathPoint::ptQuadTo: {

				}
				break;

				case PathPoint::ptCubicTo: {

				}
				break;

				case PathPoint::ptClose: {
					LineTo( dc_, (int32)pt.point_.x_ + origin_.x_, (int32)pt.point_.y_ + origin_.y_ );
				}
				break;
			}

			it++;

		}

		::EndPath( dc_ );

		clipRGN_ = ::PathToRegion( dc_ );
	}


	::SelectClipRgn( dc_, clipRGN_ );

	releaseHandle();
}


void Win32Context::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;

	int err = ::DrawFocusRect( dc_, &r );

	releaseHandle();
}

void Win32Context::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;

	int err = ::DrawFocusRect( dc_, &r );

	releaseHandle();
}

void Win32Context::drawThemeButtonFocusRect( Rect* rect )
{
	Rect focusRect = *rect;
	focusRect.inflate( -4, -4 );

	DrawUIState state;
	drawThemeFocusRect( &focusRect, state );
}

void Win32Context::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect )
{
	checkHandle();

	RECT btnRect;
	btnRect.left = rect->left_;
	btnRect.top = rect->top_;
	btnRect.right = rect->right_;
	btnRect.bottom = rect->bottom_;


	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
	}

	if ( theme ) {
		int dcs = SaveDC( dc_ );

		int btnState = 0;

		if ( !state.isEnabled() ) {
			btnState =	PBS_DISABLED;
		}
		else {
			btnState |= state.isHighlighted() ? PBS_HOT	: PBS_NORMAL;
			btnState |=	state.isDefaultButton()	? PBS_DEFAULTED : PBS_NORMAL;

			btnState = state.isPressed() ? PBS_PRESSED	: btnState;
		}

		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, BP_PUSHBUTTON, btnState, &btnRect, 0);

		SetBkMode(dc_, TRANSPARENT);
		VCF::Font btnFont = *context_->getCurrentFont();

		HFONT font = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}

		btnRect.left += 5;
		btnRect.right -= 5;

		Win32VisualStylesWrapper::DrawThemeText(theme, dc_, BP_PUSHBUTTON, btnState,
			state.buttonCaption_.c_str(),
			state.buttonCaption_.length(),
			DT_SINGLELINE | DT_CENTER | DT_VCENTER, NULL,
			&btnRect);


		Win32VisualStylesWrapper::CloseThemeData( theme );

		RestoreDC(dc_, dcs );

		DeleteObject( font );

	}
	else {
		COLORREF backColor = ::GetSysColor( COLOR_3DFACE );

		HBRUSH backBrush = CreateSolidBrush( backColor );
		HPEN hilightPen = CreatePen( PS_SOLID, 0, ::GetSysColor( COLOR_3DHIGHLIGHT ) );
		HPEN shadowPen = CreatePen( PS_SOLID, 0, ::GetSysColor( COLOR_3DSHADOW ) );
		HPEN blackPen = CreatePen( PS_SOLID, 0, 0 );

		HBRUSH oldBrush = (HBRUSH)::SelectObject( dc_, backBrush );
		::FillRect( dc_, &btnRect, backBrush );

		bool isPressed = state.isPressed();

		HPEN oldPen = NULL;

		RECT tmpRect = btnRect;
		//InflateRect( &tmpRect, -1, -1 );
		if ( state.isDefaultButton() ) {
			InflateRect( &tmpRect, -1, -1 );
		}

		RECT capRect = btnRect;
		if ( NULL != captionRect ) {
			capRect.left = captionRect->left_;
			capRect.top = captionRect->top_;
			capRect.right = captionRect->right_;
			capRect.bottom = captionRect->bottom_;
		}


		if ( true == isPressed ) {
			HBRUSH shadowBrush = CreateSolidBrush( ::GetSysColor( COLOR_3DSHADOW ) );
			::FrameRect( dc_, &tmpRect, shadowBrush );
			DeleteObject( shadowBrush );
			::OffsetRect( &capRect, 1, 1 );
		}
		else {

			oldPen = (HPEN) ::SelectObject( dc_, hilightPen );


			::MoveToEx( dc_, tmpRect.right, tmpRect.top, NULL );
			::LineTo( dc_, tmpRect.left, tmpRect.top );
			::LineTo( dc_, tmpRect.left, tmpRect.bottom-1 );

			::SelectObject( dc_, shadowPen );
			::MoveToEx( dc_, tmpRect.right-2, tmpRect.top+1, NULL );
			::LineTo( dc_, tmpRect.right-2, tmpRect.bottom-2 );
			::LineTo( dc_, tmpRect.left, tmpRect.bottom-2 );

			::SelectObject( dc_, blackPen );
			::MoveToEx( dc_, tmpRect.right-1, tmpRect.top, NULL );
			::LineTo( dc_, tmpRect.right-1, tmpRect.bottom-1 );
			::LineTo( dc_, tmpRect.left-1, tmpRect.bottom-1 );

			/*
			::MoveToEx( dc_, tmpRect.right, tmpRect.top, NULL );
			::LineTo( dc_, tmpRect.left, tmpRect.top );
			::LineTo( dc_, tmpRect.left, tmpRect.bottom );

			  ::SelectObject( dc_, shadowPen );
			  ::MoveToEx( dc_, tmpRect.right-1, tmpRect.top+1, NULL );
			  ::LineTo( dc_, tmpRect.right-1, tmpRect.bottom-1 );
			  ::LineTo( dc_, tmpRect.left, tmpRect.bottom-1 );

				::SelectObject( dc_, blackPen );
				::MoveToEx( dc_, tmpRect.right-1, tmpRect.top, NULL );
				::LineTo( dc_, tmpRect.right, tmpRect.bottom );
				::LineTo( dc_, tmpRect.left, tmpRect.bottom );
			*/

		}

		bool enabled = state.isEnabled();




		HFONT font = NULL;
		HFONT oldFont = NULL;

		VCF::Font btnFont = *context_->getCurrentFont();

		Rect centerRect( capRect.left, capRect.top, capRect.right, capRect.bottom );
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			oldFont = (HFONT) ::SelectObject( dc_, font );

			::DrawTextW( dc_, state.buttonCaption_.c_str(), -1, &capRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			oldFont = (HFONT) ::SelectObject( dc_, font );

			::DrawTextA( dc_, state.buttonCaption_.ansi_c_str(), -1, &capRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
		}


		::OffsetRect( &capRect,
			(centerRect.getWidth() - (capRect.right - capRect.left))/2,
			(centerRect.getHeight() - (capRect.bottom - capRect.top))/2 );

		int oldBkMode = SetBkMode( dc_, TRANSPARENT );


		COLORREF textColor = 0;
		if ( true == enabled ) {
			textColor = ::GetSysColor( COLOR_BTNTEXT );
		}
		else {
			textColor = ::GetSysColor( COLOR_GRAYTEXT );
		}



		COLORREF oldTextColor = SetTextColor( dc_, textColor );

		if ( false == enabled ) {
			SetTextColor( dc_, ::GetSysColor( COLOR_BTNHIGHLIGHT ) );

			OffsetRect( &capRect, 1, 1 );

			if ( System::isUnicodeEnabled() ) {
				::DrawTextW( dc_, state.buttonCaption_.c_str(), -1, &capRect, DT_WORDBREAK | DT_CENTER);
			}
			else {
				::DrawTextA( dc_, state.buttonCaption_.ansi_c_str(), -1, &capRect, DT_WORDBREAK | DT_CENTER);
			}

			OffsetRect( &capRect, -1, -1 );

			SetTextColor( dc_, textColor );
		}

		if ( System::isUnicodeEnabled() ) {
			::DrawTextW( dc_, state.buttonCaption_.c_str(), -1, &capRect, DT_WORDBREAK | DT_CENTER);
		}
		else {
			::DrawTextA( dc_, state.buttonCaption_.ansi_c_str(), -1, &capRect, DT_WORDBREAK | DT_CENTER);
		}



		SetTextColor( dc_, oldTextColor );
		SetBkMode( dc_, oldBkMode );

		::SelectObject( dc_, oldFont );
		::DeleteObject( font );



		/*if ( state.isFocused() ) {
		RECT focusRect = btnRect;
		InflateRect( &focusRect, -4, -4 );

		  ::DrawFocusRect( dc_, &focusRect );
	}*/


		if ( state.isDefaultButton() ) {
			RECT defRect = btnRect;

			//defRect.right -= 1;
			//defRect.bottom -= 1;


			FrameRect( dc_, &defRect, (HBRUSH)GetStockObject(BLACK_BRUSH) );
		}

		if ( NULL != oldBrush ) {
			::SelectObject( dc_, oldBrush );
		}
		if ( NULL != oldPen ) {
			::SelectObject( dc_, oldPen );
		}

		::DeleteObject( hilightPen );
		::DeleteObject( shadowPen );
		::DeleteObject( blackPen );
		::DeleteObject( backBrush );
	}


	releaseHandle();
}


void Win32Context::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	checkHandle();

	Rect tmp = *rect;

	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
	}

	if ( theme ) {
		RECT btnRect;
		btnRect.left = rect->left_;
		btnRect.top = rect->top_;
		btnRect.right = rect->right_;
		btnRect.bottom = rect->bottom_;
		btnRect.right = btnRect.left + (btnRect.bottom - btnRect.top);



		int dcs = SaveDC( dc_ );

		int btnState = 0;
		bool normal = true;
		if ( state.isPressed() ) {
			btnState |= state.isToggled() ? CBS_CHECKEDPRESSED : CBS_UNCHECKEDPRESSED;
			normal = false;
		}

		if ( !state.isEnabled() ) {
			btnState |= state.isToggled() ? CBS_CHECKEDDISABLED : CBS_UNCHECKEDDISABLED;
			normal = false;
		}

		if ( state.isFocused() || state.isHighlighted() ) {
			btnState |= state.isToggled() ? CBS_CHECKEDHOT : CBS_UNCHECKEDHOT;
			normal = false;
		}

		if ( normal ) {
			btnState |= state.isToggled() ? CBS_CHECKEDNORMAL : CBS_UNCHECKEDNORMAL;

		}

		SIZE val;
		memset(&val,0,sizeof(val));
		Win32VisualStylesWrapper::GetThemePartSize (theme, dc_, BP_CHECKBOX, 0, NULL, TS_DRAW, &val );

		btnRect.right = btnRect.left + val.cx;

		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, BP_CHECKBOX, btnState, &btnRect, 0);

		btnRect.left = btnRect.right;
		btnRect.right = rect->right_;


		SetBkMode(dc_, TRANSPARENT);
		VCF::Font btnFont = *context_->getCurrentFont();

		HFONT font = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}

		btnRect.left += 5; //this is totally made up! Where would I get this from????

		Win32VisualStylesWrapper::DrawThemeText(theme, dc_, BP_CHECKBOX, btnState,
			state.buttonCaption_.c_str(),
			state.buttonCaption_.length(),
			DT_SINGLELINE | DT_VCENTER, NULL,
			&btnRect);


		Win32VisualStylesWrapper::CloseThemeData( theme );

		RestoreDC(dc_, dcs );

		DeleteObject( font );

	}
	else {


	/**
	JC
	it turns out that the height/width is ALWAYS 13 pixels - no matter what
	the DPI is
	GetSystemMetrics( SM_CXMENUCHECK ) returns a value that changes based on the DPI
	13 at 96 DPI and 17 at 120 DPI
		*/
		int checkBoxHeight = 13;

		tmp.top_ = (int)(rect->top_ + rect->getHeight() /2.0 + 0.5);
		tmp.top_ -= checkBoxHeight/2;
		tmp.bottom_ = tmp.top_ + checkBoxHeight;
		tmp.right_ = tmp.left_ + checkBoxHeight;




		RECT r = {0,0,0,0};
		r.left = (int32)tmp.left_;
		r.top = (int32)tmp.top_;
		r.right = (int32)tmp.right_;
		r.bottom = (int32)tmp.bottom_;
		UINT chkState =  (state.isToggled() || state.isPressed()) ?  DFCS_BUTTONCHECK | DFCS_CHECKED : DFCS_BUTTONCHECK;

		int err = ::DrawFrameControl( dc_, &r, DFC_BUTTON, chkState );


		tmp = *rect;
		tmp.left_ = r.right + 3;
		tmp.inflate( -1.0, -1.0 );

		/*
		JC - commented this out - it looked dorky???
		if ( state.isFocused() ) {
		drawThemeFocusRect( &tmp, state );
		}
		*/


		releaseHandle();

		int32 flags = GraphicsContext::tdoCenterVertAlign;
		context_->textBoundedBy( &tmp, state.buttonCaption_, flags );
	}
}

void Win32Context::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	checkHandle();

	Rect tmp = *rect;

	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
	}

	if ( theme ) {
		RECT btnRect;
		btnRect.left = rect->left_;
		btnRect.top = rect->top_;
		btnRect.right = rect->right_;
		btnRect.bottom = rect->bottom_;
		btnRect.right = btnRect.left + (btnRect.bottom - btnRect.top);



		int dcs = SaveDC( dc_ );

		int btnState = 0;
		bool normal = true;
		if ( state.isPressed() ) {
			btnState |= state.isToggled() ? RBS_CHECKEDPRESSED : RBS_UNCHECKEDPRESSED;
			normal = false;
		}

		if ( !state.isEnabled() ) {
			btnState |= state.isToggled() ? RBS_CHECKEDDISABLED : RBS_UNCHECKEDDISABLED;
			normal = false;
		}

		if ( state.isFocused() || state.isHighlighted() ) {
			btnState |= state.isToggled() ? RBS_CHECKEDHOT : RBS_UNCHECKEDHOT;
			normal = false;
		}

		if ( normal ) {
			btnState |= state.isToggled() ? RBS_CHECKEDNORMAL : RBS_UNCHECKEDNORMAL;

		}

		SIZE val;
		memset(&val,0,sizeof(val));
		Win32VisualStylesWrapper::GetThemePartSize (theme, dc_, BP_RADIOBUTTON, 0, NULL, TS_DRAW, &val );

		btnRect.right = btnRect.left + val.cx;

		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, BP_RADIOBUTTON, btnState, &btnRect, 0);

		btnRect.left = btnRect.right;
		btnRect.right = rect->right_;


		SetBkMode(dc_, TRANSPARENT);
		VCF::Font btnFont = *context_->getCurrentFont();

		HFONT font = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}

		btnRect.left += 5; //this is totally made up! Where would I get this from????

		Win32VisualStylesWrapper::DrawThemeText(theme, dc_, BP_RADIOBUTTON, btnState,
			state.buttonCaption_.c_str(),
			state.buttonCaption_.length(),
			DT_SINGLELINE | DT_VCENTER, NULL,
			&btnRect);


		Win32VisualStylesWrapper::CloseThemeData( theme );

		RestoreDC(dc_, dcs );

		DeleteObject( font );

	}
	else {
	/**
	JC
	it turns out that the height/width is ALWAYS 13 pixels - no matter what
	the DPI is
	GetSystemMetrics( SM_CXMENUCHECK ) returns a value that changes based on the DPI
	13 at 96 DPI and 17 at 120 DPI
		*/
		int radioBoxHeight = 13;

		tmp.top_ = (int)(rect->top_ + rect->getHeight() /2.0 + 0.5);
		tmp.top_ -= radioBoxHeight/2;
		tmp.bottom_ = tmp.top_ + radioBoxHeight;
		tmp.right_ = tmp.left_ + radioBoxHeight;




		RECT r = {0,0,0,0};
		r.left = (int32)tmp.left_;
		r.top = (int32)tmp.top_;
		r.right = (int32)tmp.right_;
		r.bottom = (int32)tmp.bottom_;

		UINT btnState =  state.isToggled() ?  DFCS_BUTTONRADIO | DFCS_CHECKED : DFCS_BUTTONRADIO;

		::DrawFrameControl( dc_, &r, DFC_BUTTON, btnState );


		tmp = *rect;
		tmp.left_ = r.right + 3;
		tmp.inflate( -1.0, -1.0 );

		/*
		JC - commented this out - it looked dorky???
		if ( state.isFocused() ) {
		drawThemeFocusRect( &tmp, state );
		}
		*/

		releaseHandle();


		int32 flags = GraphicsContext::tdoCenterVertAlign;
		context_->textBoundedBy( &tmp, state.buttonCaption_, flags );
	}
}

void Win32Context::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	HTHEME theme = NULL;

	RECT r;
	memset(&r,0,sizeof(r));
	r.left = rect->left_;
	r.top = rect->top_;
	r.right = rect->right_;
	r.bottom = rect->bottom_;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"EDIT" );
	}

	if ( theme ) {
		int dcs = SaveDC( dc_ );

		int btnState = 0;

		btnState |= state.isPressed() ? CBXS_PRESSED : CBXS_NORMAL;

		if ( !state.isEnabled() ) {
			btnState |= CBXS_DISABLED;
		}

		if ( state.isFocused() || state.isHighlighted() ) {
			btnState |= CBXS_HOT;
		}

		int editState = state.isEnabled() ? ETS_NORMAL : ETS_DISABLED;

		if ( state.isEnabled() ) {
			if ( state.isFocused() ) {
				editState |= ETS_FOCUSED;
				editState |= ETS_SELECTED;
			}
			if ( state.isHighlighted() ) {
				editState |= ETS_HOT;
			}
		}




		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, EP_EDITTEXT, editState, &r, 0);

		SetBkMode(dc_, TRANSPARENT);
		VCF::Font btnFont = *context_->getCurrentFont();

		HFONT font = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}

		r.left += 2;
		r.top += 2;
		r.bottom -= 2;
		r.right -= 2;

		Win32VisualStylesWrapper::DrawThemeText(theme, dc_, EP_EDITTEXT, editState,
												state.buttonCaption_.c_str(),
												state.buttonCaption_.length(),
												DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_EXPANDTABS,
												NULL,
												&r);


		Win32VisualStylesWrapper::CloseThemeData( theme );

		r.left -= 1;
		r.top -= 1;
		r.bottom += 1;
		r.right += 1;

		//now do drop down button
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"COMBOBOX" );
		SIZE val;
		memset(&val,0,sizeof(val));
		HRESULT hr = Win32VisualStylesWrapper::GetThemePartSize (theme, dc_, CP_DROPDOWNBUTTON, 0, NULL, TS_DRAW, &val );
		if ( SUCCEEDED(hr) && val.cx != 0 ) {
			r.left = r.right - val.cx;
		}
		else {
			//do it the old way???
			NONCLIENTMETRICS ncm;
			memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
			ncm.cbSize = sizeof(NONCLIENTMETRICS);

			SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
			r.left = r.right - ncm.iScrollWidth;
		}


		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, CP_DROPDOWNBUTTON, btnState, &r, 0);



		Win32VisualStylesWrapper::CloseThemeData( theme );

		RestoreDC(dc_, dcs );

		DeleteObject( font );
	}
	else {

		int dcState = ::SaveDC( dc_ );


		::FillRect( dc_, &r, (HBRUSH)(COLOR_WINDOW+1) );

		RECT btnRect = r;

		NONCLIENTMETRICS ncm;
		memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
		ncm.cbSize = sizeof(NONCLIENTMETRICS);

		SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );

		btnRect.left = r.right - ncm.iScrollWidth;

		::FillRect( dc_, &btnRect, (HBRUSH)(COLOR_3DFACE+1) );

		UINT flags = 0;

		flags |= DFCS_SCROLLDOWN;

		if ( state.isPressed() ) {
			// Native win32 pressed combobox buttons are always flat, so
			// we're going to do our best to make it look flat in our
			// combobox emulation too
			flags |= DFCS_PUSHED | DFCS_FLAT;
		}

		if ( !state.isEnabled() ) {
			flags |= DFCS_INACTIVE;
		}

		DrawFrameControl( dc_, &btnRect, DFC_SCROLL, flags );

		RECT bkRect = r;
		bkRect.right = btnRect.left;


		SetBkMode( dc_, TRANSPARENT );
		COLORREF bkColor;
		COLORREF textColor;
		if ( !state.isEnabled() ) {
			bkColor = GetSysColor( COLOR_BTNFACE );
			textColor = GetSysColor( COLOR_WINDOWTEXT );
		}
		else {
			InflateRect( &bkRect, -2, -2 );

			if ( state.isFocused() ) {
				bkColor = GetSysColor( COLOR_HIGHLIGHT );
				textColor = GetSysColor( COLOR_HIGHLIGHTTEXT );

				InflateRect( &bkRect, +1, +1 );

				::DrawFocusRect( dc_, &bkRect );

				InflateRect( &bkRect, -1, -1 );
			}
			else {
				bkColor = GetSysColor( COLOR_WINDOW );
				textColor = GetSysColor( COLOR_WINDOWTEXT );
			}
		}

		HBRUSH bkBrush = CreateSolidBrush( bkColor );

		FillRect( dc_, &bkRect, bkBrush );
		SetTextColor( dc_, textColor );
		UINT fmt = DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_EXPANDTABS | DT_END_ELLIPSIS;

		HFONT font;
		prepareDCWithContextFont( font );

		::SelectObject( dc_, font );

		if ( System::isUnicodeEnabled() ) {
			DrawTextW( dc_, state.buttonCaption_.c_str(), state.buttonCaption_.size(), &bkRect, fmt );
		}
		else {
			AnsiString tmp = state.buttonCaption_;
			DrawTextA( dc_, tmp.c_str(), tmp.size(), &bkRect, fmt );
		}


		::RestoreDC( dc_, dcState );

		DeleteObject( font );
		DeleteObject( bkBrush );
	}
}

void Win32Context::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
	}

	if ( theme ) {

		int scrollState = 0;

		if ( state.isVertical() ) {
			if ( state.isUpOrLeftBtn() ) {
				scrollState |= state.isEnabled() ? ABS_UPNORMAL : ABS_UPDISABLED;
			}
			else if ( state.isDownOrRightBtn() ) {
				scrollState |= state.isEnabled() ? ABS_DOWNNORMAL : ABS_DOWNDISABLED;
			}

			if ( state.isEnabled() ) {
				if ( state.isScrollBarIncrArrowPressed() ) {
					scrollState |= ABS_UPPRESSED;
				}
				else if ( state.isScrollBarDecrArrowPressed() ) {
					scrollState |= ABS_DOWNPRESSED;
				}
			}
		}
		else if ( !state.isVertical() ) {
			if ( state.isDownOrRightBtn() ) {
				scrollState |= state.isEnabled() ? ABS_RIGHTNORMAL : ABS_RIGHTDISABLED;
			}
			else if ( state.isUpOrLeftBtn() ) {
				scrollState |= state.isEnabled() ? ABS_LEFTNORMAL : ABS_LEFTDISABLED;
			}

			if ( state.isEnabled() ) {
				if ( state.isScrollBarIncrArrowPressed() ) {
					scrollState |= ABS_LEFTPRESSED;
				}
				else if ( state.isScrollBarDecrArrowPressed() ) {
					scrollState |= ABS_RIGHTPRESSED;
				}
			}
		}



		if ( true == state.isScrollBarThumbPressed() ) {
			scrollState |= DFCS_PUSHED;
		}

		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, SBP_ARROWBTN, scrollState, &r, 0);

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {

		UINT scrollState =  0;

		if ( state.isVertical() ) {
			if ( state.isScrollBarIncrArrowPressed() ) {
				scrollState |= DFCS_SCROLLUP;
			}
			else if ( state.isScrollBarDecrArrowPressed() ) {
				scrollState |= DFCS_SCROLLDOWN;
			}
		}
		else if ( !state.isVertical() ) {
			if ( state.isScrollBarIncrArrowPressed() ) {
				scrollState |= DFCS_SCROLLRIGHT;
			}
			else if ( state.isScrollBarDecrArrowPressed() ) {
				scrollState |= DFCS_SCROLLLEFT;
			}
		}

		if ( true == state.isScrollBarThumbPressed() ) {
			scrollState |= DFCS_PUSHED;
		}

		int err = ::DrawFrameControl( dc_, &r, DFC_SCROLL, scrollState );
	}
	releaseHandle();
}

void Win32Context::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state )
{
	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TREEVIEW" );
	}

	if ( theme ) {
		SIZE val;
		memset(&val,0,sizeof(val));
		int partState = state.isOpened() ? GLPS_OPENED : GLPS_CLOSED;

		HRESULT hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, TVP_GLYPH, partState,
																&r, TS_TRUE, &val);

		RECT disclR = r;
		disclR.right = disclR.left + val.cx;

		Win32VisualStylesWrapper::DrawThemeParentBackground( ::WindowFromDC(dc_), dc_, &r );

		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TVP_GLYPH, partState, &r, 0 );

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		//old way????
	}
}

/**
Draws a tab, the part of the TabbedPages control that acts like a
little button to activate a page, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeTab( Rect* rect, TabState& state )
{
	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
	}

	if ( theme ) {
		int dcs = SaveDC( dc_ );

		SetBkMode(dc_, TRANSPARENT);
		VCF::Font tabFont = *context_->getCurrentFont();		
		
		HFONT font = NULL;			
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) tabFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) tabFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}

		int tabPart = 0;
		int tabState = 0;

		SIZE tabSz;
		memset(&tabSz,0,sizeof(tabSz));
		tabPart = (state.isHighlighted() || state.isPressed()) ? TABP_TABITEMLEFTEDGE : TABP_TABITEM;

		if ( state.isEnabled() ) {
			tabState = (state.isHighlighted() || state.isPressed()) ? TIS_SELECTED : TIS_NORMAL;
		}
		else {
			tabState = TIS_DISABLED;
		}

		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, tabPart, tabState, &r, 0 );

		RECT textRect = r;
		Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, TABP_TABITEM, TIS_NORMAL, 
																&r, TS_TRUE, &tabSz);

		textRect.left += tabSz.cx/2;
		textRect.right -= tabSz.cx/2;

		
		Win32VisualStylesWrapper::DrawThemeText( theme, dc_, tabPart, tabState, 
													state.tabCaption_.c_str(), state.tabCaption_.size(), 
													DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_EXPANDTABS,
													0, &textRect );

		RestoreDC( dc_, dcs );
		DeleteObject( font );

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		Color* hilite = GraphicsToolkit::getSystemColor(SYSCOLOR_HIGHLIGHT);
		Color* shadow = GraphicsToolkit::getSystemColor(SYSCOLOR_SHADOW);
		Color* face = GraphicsToolkit::getSystemColor(SYSCOLOR_FACE);
		Color* textColor = GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT );
		Color* selectedTextColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );

		context_->setColor( face );
		context_->rectangle( rect );
		context_->fillPath();
		Color oldFontColor;
		
		oldFontColor = *context_->getCurrentFont()->getColor();
		context_->getCurrentFont()->setColor( textColor );

		if ( state.isPressed() ) {
			context_->getCurrentFont()->setBold( true );
			context_->setColor( hilite );
			context_->moveTo(rect->left_ , rect->bottom_ -1 );
			context_->lineTo(rect->left_ , rect->top_ + 2 );
			context_->lineTo(rect->left_ + 2 , rect->top_ );
			context_->lineTo(rect->right_ - 2 , rect->top_);
			context_->strokePath();
			
			context_->setColor( Color::getColor( "black" ) );
			context_->moveTo( rect->right_ - 2 , rect->top_ + 1);
			context_->lineTo( rect->right_ - 1 , rect->top_ + 2);
			context_->lineTo( rect->right_ - 1 , rect->bottom_ );
			context_->strokePath();
			
			context_->setColor( shadow );
			context_->moveTo( rect->right_ - 2, rect->top_ + 2);
			context_->lineTo( rect->right_ - 2, rect->bottom_ );
			context_->strokePath();
		}
		else {
			context_->setColor( hilite );
			context_->moveTo(rect->left_ , rect->bottom_ );
			context_->lineTo(rect->left_ , rect->top_ + 2 );
			context_->lineTo(rect->left_ + 2 , rect->top_  );
			context_->lineTo(rect->right_ - 2 , rect->top_ );
			context_->strokePath();
			
			context_->setColor( Color::getColor( "black" ) );
			context_->moveTo( rect->right_ - 2 , rect->top_ + 1);
			context_->lineTo( rect->right_ - 1 , rect->top_ + 2);
			context_->lineTo( rect->right_ - 1 , rect->bottom_ );
			context_->strokePath();
			
			context_->setColor( shadow );
			context_->moveTo( rect->right_ - 2, rect->top_ + 2);
			context_->lineTo( rect->right_ - 2, rect->bottom_ );
			context_->strokePath();

		}

		Rect tmpR = *rect;
		
		tmpR.inflate( -4, 0 );
		tmpR.normalize();
		int32 flags = GraphicsContext::tdoCenterHorzAlign | GraphicsContext::tdoCenterVertAlign;
		context_->textBoundedBy( &tmpR, state.tabCaption_, flags );
		
		context_->getCurrentFont()->setColor( &oldFontColor );
	}
}

void Win32Context::drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState,
									TabState& otherTabs, const std::vector<String>& tabsNames,
									int selectedTabIndex )
{
	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
	}

	if ( theme ) {

		int dcs = SaveDC( dc_ );

		SetBkMode(dc_, TRANSPARENT);
		VCF::Font btnFont = *context_->getCurrentFont();

		HFONT font = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}

		SIZE bodySize;
		memset(&bodySize,0,sizeof(bodySize));
		
		SIZE paneSize;
		memset(&paneSize,0,sizeof(paneSize));
		
		RECT bodyContent = r;
		RECT paneContent = r;

		SIZE tabSz;
		memset(&tabSz,0,sizeof(tabSz));
		SIZE tabSelectedSz;
		memset(&tabSelectedSz,0,sizeof(tabSelectedSz));

		HRESULT hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, TABP_BODY, 1,
																&r, TS_TRUE, &bodySize);

		hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, TABP_PANE, 1,
																&r, TS_TRUE, &paneSize);

		hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, TABP_TABITEM, TIS_SELECTED,
																&r, TS_TRUE, &tabSelectedSz);

		hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, TABP_TABITEM, TIS_NORMAL,
																&r, TS_TRUE, &tabSz);


		hr = Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_,
			TABP_BODY, 1, &r, &bodyContent );

		hr = Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_,
			TABP_PANE, 1, &r, &paneContent );


		int dy = abs(bodyContent.top - paneContent.top);

		if ( !tabsNames.empty() ) {
			bodyContent.top += VCF::maxVal(tabSz.cy,tabSelectedSz.cy);
			paneContent.top += VCF::maxVal(tabSz.cy,tabSelectedSz.cy) + dy;
		}



		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TABP_PANE, 1, &bodyContent, 0 );

		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TABP_BODY, 1, &paneContent, 0 );

		if ( !tabsNames.empty() ) {

			RECT tabRect;

			int tabWidth = tabSz.cx;

			std::vector<String>::const_iterator it = tabsNames.begin();

			int totalTabWidth = 0;

			std::vector<int> textWidths;
			SIZE textSz;
			memset(&textSz,0,sizeof(textSz));
			//calculate total width
			if ( System::isUnicodeEnabled() ) {
				while ( it != tabsNames.end() ) {
					const String& s = *it;

					::GetTextExtentPoint32W( dc_, s.c_str(), s.size(), &textSz );

					totalTabWidth += textSz.cx + tabSz.cx;

					textWidths.push_back( textSz.cx );

					it ++;
				}
			}
			else {
				while ( it != tabsNames.end() ) {
					AnsiString s = *it;

					::GetTextExtentPoint32A( dc_, s.c_str(), s.size(), &textSz );

					totalTabWidth += textSz.cx + tabSz.cx;

					textWidths.push_back( textSz.cx );
						
					it ++;
				}				

			}

			bool scaleTabs = totalTabWidth > (bodyContent.right - bodyContent.left);

			if ( scaleTabs ) {
				tabWidth = (bodyContent.right - bodyContent.left) / tabsNames.size();
			}

			tabRect.left = bodyContent.left;
			tabRect.right = tabRect.left;

			//draw tabs
			it = tabsNames.begin();
			int idx = 0;
			RECT textRect;
			memset(&textRect,0,sizeof(textRect));

			int tabState = 0;
			int tabPart = 0;

			if ( !paneState.isEnabled() ) {
				tabState = TIS_DISABLED;
			}

			while ( it != tabsNames.end() ) {

				const String& s = *it;


				if ( !scaleTabs ) {
					tabWidth = textWidths[idx] + tabSz.cx;
				}

				tabRect.right += tabWidth;

				if ( ((idx == 0) && (selectedTabIndex == -1)) || (selectedTabIndex == idx) ) {
					tabRect.bottom = bodyContent.top+1;
					tabRect.top = tabRect.bottom - tabSz.cy;

					tabPart = TABP_TABITEMLEFTEDGE;
					tabState = paneState.isEnabled() ? TILES_SELECTED : TILES_DISABLED;
				}
				else if ( idx == tabsNames.size()-1 ) {
					//last tab

					tabRect.bottom = bodyContent.top;
					tabRect.top = tabRect.bottom - tabSz.cy + 2;

					tabPart = TABP_TABITEM;
					tabState = paneState.isEnabled() ? TIS_NORMAL : TIS_DISABLED;
				}
				else {
					tabRect.bottom = bodyContent.top;
					tabRect.top = tabRect.bottom - tabSz.cy + 2;

					tabPart = TABP_TABITEM;
					tabState = paneState.isEnabled() ? TIS_NORMAL : TIS_DISABLED;
				}

				Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, tabPart, tabState, &tabRect, 0 );

				textRect = tabRect;
				textRect.left += tabSz.cx/2;
				textRect.right -= tabSz.cx/2;

				Win32VisualStylesWrapper::DrawThemeText( theme, dc_, TABP_TABITEM, TIS_NORMAL,
													s.c_str(), s.size(), DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_EXPANDTABS,
													0, &textRect );

				tabRect.left += tabWidth;

				idx ++;
				it ++;
			}
		}

		RestoreDC( dc_, dcs );
		DeleteObject( font );

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {

	}
}

/**
Draws a tab page - the page on which other controls for the page are
parented to, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeTabPage( Rect* rect, DrawUIState& state )
{
	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
	}

	if ( theme ) {
		RECT bodyContent = r;
		RECT paneContent = r;

		Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_,
			TABP_BODY, 1, &r, &bodyContent );

		Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_,
			TABP_PANE, 1, &r, &paneContent );

		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TABP_PANE, 1, &bodyContent, 0 );

		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TABP_BODY, 1, &paneContent, 0 );

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		BackgroundState bkg;
		bkg.setEnabled( state.isEnabled() );
		bkg.setActive( state.isActive() );
		bkg.colorType_ = SYSCOLOR_FACE;	
		
		drawThemeBackground( rect, bkg );

		::DrawEdge( dc_, &r, BDR_RAISEDOUTER|BDR_RAISEDINNER, BF_RECT | BF_SOFT );

	}
}

void Win32Context::drawThemeTabContent( Rect* rect, DrawUIState& state )
{
	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
	}

	if ( theme ) {
		
		//Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TABP_PANE, 1, &bodyContent, 0 );

		Win32VisualStylesWrapper::DrawThemeBackground( theme, dc_, TABP_BODY, 1, &r, 0 );

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		BackgroundState bkg;
		bkg.setEnabled( state.isEnabled() );
		bkg.setActive( state.isActive() );
		bkg.colorType_ = SYSCOLOR_FACE;	
		
		drawThemeBackground( rect, bkg );
	}
}

/**
Draws a tick mark, like that used for a slider control, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeTickMarks( Rect* rect, SliderState& state )
{
	if ( state.tickMarkFrequency_ <= 0 ) {
		return;
	}


	double range = state.max_ - state.min_;

	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TRACKBAR" );
	}

	if ( theme ) {

		int tickPart = 0;
		int tickState = TSS_NORMAL;

		int thmbPart = 0;
		int thmbState = 0;

		double start = 0;

		RECT trackContent;
		memset(&trackContent,0,sizeof(trackContent));
		SIZE thmbSize;
		memset(&thmbSize,0,sizeof(thmbSize));

		if ( state.isVertical() ) {
			tickPart = TKP_TICSVERT;
			thmbPart = TKP_THUMBVERT;

			if ( state.isTickMarkingOnBottomRight() && !state.isTickMarkingOnTopLeft() ) {
				thmbPart = TKP_THUMBRIGHT;
			}
			else if ( state.isTickMarkingOnTopLeft() && !state.isTickMarkingOnBottomRight() ) {
				thmbPart = TKP_THUMBLEFT;
			}


			if ( state.isEnabled() ) {
				thmbState = TUVS_NORMAL;
				if ( state.isPressed() ) {
					thmbState = TUVS_PRESSED;
				}
				else if ( state.isFocused() ) {
					thmbState = TUVS_FOCUSED;
				}
			}
			else {
				thmbState = TUVS_DISABLED;
			}

			Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_, TKP_TRACKVERT, TRVS_NORMAL, &r, &trackContent );

			Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, thmbPart, thmbState, &r, TS_TRUE, &thmbSize );
		}
		else {
			tickPart = TKP_TICS;
			thmbPart = TKP_THUMB;

			if ( state.isTickMarkingOnBottomRight() && !state.isTickMarkingOnTopLeft() ) {
				thmbPart = TKP_THUMBBOTTOM;
			}
			else if ( state.isTickMarkingOnTopLeft() && !state.isTickMarkingOnBottomRight() ) {
				thmbPart = TKP_THUMBTOP;
			}

			if ( state.isEnabled() ) {
				thmbState = TUS_NORMAL;
				if ( state.isPressed() ) {
					thmbState = TUS_PRESSED;
				}
				else if ( state.isFocused() ) {
					thmbState = TUS_FOCUSED;
				}
			}
			else {
				thmbState = TUS_DISABLED;
			}
			Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_, TKP_TRACK, TKS_NORMAL, &r, &trackContent );

			Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, thmbPart, thmbState, &r, TS_TRUE, &thmbSize );
		}

		SIZE val;
		memset(&val,0,sizeof(val));

		Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, tickPart, tickState, &r, TS_TRUE, &val );

		double tickVal;
		double incr = 0;
		double length = 0;
		RECT tick1;
		RECT tick2;

		if ( state.isVertical() ) {
			tickVal = trackContent.top - val.cy/2;
			length = (trackContent.bottom - trackContent.top);// - thmbSize.cy;

			tick1.left = r.left + val.cx/2;
			tick1.right = tick1.left + val.cx;

			tick2.left = r.right - val.cx/2;
			tick2.right = tick2.left + val.cx;

		}
		else {
			tickVal = trackContent.left - val.cx/2;
			length = (trackContent.right - trackContent.left);

			tick1.top = r.top + val.cy/2;
			tick1.bottom = tick1.top + val.cy;

			tick2.top = r.bottom - val.cy/2;
			tick2.bottom = tick2.top + val.cy;
		}

		incr = length/state.tickMarkFrequency_;

		int count = state.tickMarkFrequency_;
		for (int32 i=0;i<=count;i++ ) {
			if ( state.isVertical() ) {
				tick2.top = tick1.top = tickVal;
				tick1.bottom = tick1.top + val.cy;
				tick2.bottom = tick1.bottom;
			}
			else{
				tick2.left = tick1.left = tickVal;
				tick1.right = tick1.left + val.cy;
				tick2.right = tick1.right;
			}

			if ( state.isTickMarkingOnBottomRight() ) {
				Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, tickPart, tickState, &tick2, 0);
			}

			if ( state.isTickMarkingOnTopLeft() ) {
				Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, tickPart, tickState, &tick1, 0);
			}

			tickVal += incr;
		}
		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {

		context_->setColor( Color::getColor( "black" ) );

		double incr = 0;
		if ( state.isVertical() ) {
			incr = (1.0/(double)(state.tickMarkFrequency_)) * rect->getHeight();
		}
		else {
			incr = (1.0/(double)(state.tickMarkFrequency_)) * rect->getWidth();
		}

		double y = rect->top_;
		double x = rect->left_;

		for (int32 i=0;i<=state.tickMarkFrequency_;i++ ) {
			if ( state.isVertical() ) {


				if ( state.isTickMarkingOnTopLeft() ) {
					x = rect->left_;
					double x2 = x - 5;

					context_->moveTo( x, y );
					context_->lineTo( x2, y );
					context_->strokePath();
				}

				if ( state.isTickMarkingOnBottomRight() ) {
					x = rect->right_;
					double x2 = x + 5;

					context_->moveTo( x, y );
					context_->lineTo( x2, y );
					context_->strokePath();
				}
				y += incr;
			}
			else {
				if ( state.isTickMarkingOnTopLeft() ) {
					y = rect->top_;
					double y2 = y - 5;

					context_->moveTo( x, y );
					context_->lineTo( x, y2 );
					context_->strokePath();
				}

				if ( state.isTickMarkingOnBottomRight() ) {
					y = rect->bottom_;
					double y2 = y + 5;

					context_->moveTo( x, y );
					context_->lineTo( x, y2 );
					context_->strokePath();
				}
				x += incr;
			}
		}
	}
}

/**
Draws a slider control, like that used for a slider control, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeSlider( Rect* rect, SliderState& state )
{
	Rect tmp = *rect;

	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TRACKBAR" );
	}

	if ( theme ) {
		int trackPart = 0;
		int trkState = 0;

		int thmbPart = 0;
		int thmbState = 0;
		RECT trackR = r;
		
		SIZE val;
		memset(&val,0,sizeof(val));
		
		RECT trackContent;
		memset(&trackContent,0,sizeof(trackContent));
		
		RECT thmbR;

		if ( state.isVertical() ) {

			trackPart = TKP_TRACKVERT;
			trkState = TRVS_NORMAL;

			Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, trackPart, trkState, &r, TS_TRUE, &val );

			trackR.left = r.left + ((r.right-r.left)/2 - (val.cx/2));
			trackR.right = trackR.left + val.cx;

			Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_, trackPart, trkState, &r, &trackContent );

			thmbPart = TKP_THUMBVERT;

			if ( state.isTickMarkingOnBottomRight() && !state.isTickMarkingOnTopLeft() ) {
				thmbPart = TKP_THUMBRIGHT;
			}
			else if ( state.isTickMarkingOnTopLeft() && !state.isTickMarkingOnBottomRight() ) {
				thmbPart = TKP_THUMBLEFT;
			}


			if ( state.isEnabled() ) {
				thmbState = TUVS_NORMAL;
				if ( state.isPressed() ) {
					thmbState = TUVS_PRESSED;
				}
				else if ( state.isFocused() ) {
					thmbState = TUVS_FOCUSED;
				}
			}
			else {
				thmbState = TUVS_DISABLED;
			}

			thmbR = trackContent;
			Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, thmbPart, thmbState, &r, TS_TRUE, &val );

			thmbR.left = trackContent.left + ((trackContent.right-trackContent.left)/2 - (val.cx/2));
			thmbR.right = thmbR.left + val.cx;
			thmbR.top =  (trackContent.bottom - val.cy/2) -
				((state.min_ + state.position_) / (state.max_ - state.min_)) * ((double)(r.bottom-r.top));
			thmbR.bottom = thmbR.top + val.cy;

		}
		else {
			trackPart = TKP_TRACK;
			trkState = TRS_NORMAL;

			Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, trackPart, trkState, &r, TS_TRUE, &val );

			trackR.top = r.top + ((r.bottom-r.top)/2 - (val.cy/2));
			trackR.bottom = trackR.top + val.cy;

			Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_, trackPart, trkState, &r, &trackContent );

			thmbPart = TKP_THUMB;

			if ( state.isTickMarkingOnBottomRight() && !state.isTickMarkingOnTopLeft() ) {
				thmbPart = TKP_THUMBBOTTOM;
			}
			else if ( state.isTickMarkingOnTopLeft() && !state.isTickMarkingOnBottomRight() ) {
				thmbPart = TKP_THUMBTOP;
			}


			if ( state.isEnabled() ) {
				thmbState = TUS_NORMAL;
				if ( state.isPressed() ) {
					thmbState = TUS_PRESSED;
				}
				else if ( state.isFocused() ) {
					thmbState = TUS_FOCUSED;
				}
			}
			else {
				thmbState = TUS_DISABLED;
			}

			thmbR = trackContent;
			Win32VisualStylesWrapper::GetThemePartSize(theme, dc_, thmbPart, thmbState, &r, TS_TRUE, &val );

			thmbR.top = trackContent.top + ((trackContent.bottom-trackContent.top)/2 - (val.cy/2));
			thmbR.bottom = thmbR.top + val.cy;
			thmbR.left =  (thmbR.left - val.cx/2) +
				((state.position_- state.min_) / (state.max_ - state.min_)) * ((double)(r.right-r.left));
			thmbR.right = thmbR.left + val.cx;
		}

		//draw slider "rail"
		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, trackPart, trkState, &trackR, 0);

		//draw thumb
		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, thmbPart, thmbState, &thmbR, 0);


		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		if ( state.isVertical() ) {
			tmp.left_ = tmp.left_ + rect->getWidth()/2.0;
			tmp.right_ = tmp.left_;
			tmp.inflate( 2, 0 );
		}
		else{
			tmp.top_ = tmp.top_ + rect->getHeight()/2.0;
			tmp.bottom_ = tmp.top_;
			tmp.inflate( 0, 2 );
		}

		drawThemeEdge( &tmp, state, GraphicsContext::etAllSides, GraphicsContext::etSunken );



		Size thumbSize;
		thumbSize.width_ = ::GetSystemMetrics( SM_CXHTHUMB )*0.85+1;
		thumbSize.height_ = ::GetSystemMetrics( SM_CYVTHUMB );

		Rect thumbRect = *rect;
		if ( state.isVertical() ) {
			thumbRect.top_ = thumbRect.bottom_ - thumbSize.width_;

			thumbRect.offset( 0, (int)(thumbSize.width_/2)-(int)(((state.position_+state.min_)/(state.max_-state.min_))*rect->getHeight()) );
		}
		else {
			thumbRect.right_ = thumbRect.left_ + thumbSize.width_;

			thumbRect.offset( (int)(((state.position_- state.min_)/(state.max_-state.min_))*rect->getWidth()) - (int)(thumbSize.width_/2), 0 );
		}


		Color* highlite = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
		Color* shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
		Color faceTmp = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		Color* black = Color::getColor("black");

		//

		if ( (!state.isEnabled()) || state.isPressed() ) {
			double h,l,s;
			faceTmp.getHSL( h,l,s );
			faceTmp.setHSL( h,0.85,s );
		}

		Color* face = &faceTmp;


		if ( state.isVertical() ) {

			int x1 = thumbRect.left_;
			int x2 = thumbRect.right_;
			int y1 = thumbRect.top_;
			int y2 = thumbRect.bottom_;


			if ( state.isTickMarkingOnBottomRight() && state.isTickMarkingOnTopLeft() ) {
				context_->setColor( face );
				context_->rectangle( &thumbRect );
				context_->fillPath();

				context_->setColor( highlite );

				context_->moveTo( x2, y1 );
				context_->lineTo( x1, y1 );
				context_->lineTo( x1, y2 );
				context_->strokePath();

				context_->setColor( black );
				context_->moveTo( x1, y2 );
				context_->lineTo( x2, y2 );
				context_->lineTo( x2, y1-1 );
				context_->strokePath();

				context_->setColor( shadow );
				context_->moveTo( x1+1, y2-1 );
				context_->lineTo( x2-1, y2-1 );
				context_->lineTo( x2-1, y1 );
				context_->strokePath();
			}
			else {
				if ( state.isTickMarkingOnTopLeft() ) {
					int xmid = x1 + ((y2-y1)/2);
					int ymid = y1 + ((y2-y1)/2);

					std::vector<Point> pts(6);
					pts[0] = Point(x2,y1);
					pts[1] = Point(xmid,y1);
					pts[2] = Point(x1,ymid);
					pts[3] = Point(xmid,y2);
					pts[4] = Point(x2,y2);
					pts[5] = Point(x2,y1);

					context_->setColor( face );
					context_->polyline( pts );
					context_->fillPath();

					context_->setColor( highlite );

					context_->moveTo( x2, y1 );
					context_->lineTo( xmid, y1 );
					context_->lineTo( x1, ymid );
					context_->strokePath();

					context_->setColor( black );

					context_->moveTo( x1, ymid );
					context_->lineTo( xmid, y2 );
					context_->lineTo( x2, y2 );
					context_->lineTo( x2, y1-1 );
					context_->strokePath();

					context_->setColor( shadow );

					context_->moveTo( x1+1, ymid );
					context_->lineTo( xmid, y2-1 );
					context_->lineTo( x2-1, y2-1 );
					context_->lineTo( x2-1, y1 );
					context_->strokePath();

				}
				else if (state.isTickMarkingOnBottomRight()) {
					int xmid = x2 - ((y2-y1)/2);
					int ymid = y1 + ((y2-y1)/2);

					std::vector<Point> pts(6);
					pts[0] = Point(x1,y1);
					pts[1] = Point(xmid,y1);
					pts[2] = Point(x2,ymid);
					pts[3] = Point(xmid,y2);
					pts[4] = Point(x1,y2);
					pts[5] = Point(x1,y1);

					context_->setColor( face );
					context_->polyline( pts );
					context_->fillPath();

					context_->setColor( highlite );

					context_->moveTo( x1, y2 );
					context_->lineTo( x1, y1 );
					context_->lineTo( xmid, y1 );
					context_->lineTo( x2, ymid );
					context_->strokePath();

					context_->setColor( black );

					context_->moveTo( x2, ymid );
					context_->lineTo( xmid, y2 );
					context_->lineTo( x1, y2 );
					context_->strokePath();

					context_->setColor( shadow );

					context_->moveTo( x2-1, ymid );
					context_->lineTo( xmid, y2-1 );
					context_->lineTo( x1-1, y2-1 );
					context_->strokePath();
				}
			}
	}
	else {


		int x1 = thumbRect.left_;
		int x2 = thumbRect.right_;
		int y1 = thumbRect.top_;
		int y2 = thumbRect.bottom_;


		if ( state.isTickMarkingOnBottomRight() && state.isTickMarkingOnTopLeft() ) {
			context_->setColor( face );
			context_->rectangle( &thumbRect );
			context_->fillPath();

			context_->setColor( highlite );

			context_->moveTo( x2, y1 );
			context_->lineTo( x1, y1 );
			context_->lineTo( x1, y2 );
			context_->strokePath();

			context_->setColor( black );
			context_->moveTo( x1, y2 );
			context_->lineTo( x2, y2 );
			context_->lineTo( x2, y1-1 );
			context_->strokePath();

			context_->setColor( shadow );
			context_->moveTo( x1+1, y2-1 );
			context_->lineTo( x2-1, y2-1 );
			context_->lineTo( x2-1, y1 );
			context_->strokePath();
		}
		else {
			if ( state.isTickMarkingOnTopLeft() ) {


				int xmid = x1 + ((x2-x1)/2);
				int ymid = y1 + ((x2-x1)/2);

				std::vector<Point> pts(6);
				pts[0] = Point(xmid,y1);
				pts[1] = Point(x1,ymid);
				pts[2] = Point(x1,y2);
				pts[3] = Point(x2,y2);
				pts[4] = Point(x2,ymid);
				pts[5] = Point(xmid,y1);

				context_->setColor( face );
				context_->polyline( pts );
				context_->fillPath();


				context_->setColor( highlite );

				context_->moveTo( xmid, y1 );
				context_->lineTo( x1, ymid );
				context_->lineTo( x1, y2 );
				context_->strokePath();

				context_->setColor( black );

				context_->moveTo( x1, y2 );
				context_->lineTo( x2, y2 );
				context_->lineTo( x2, ymid );
				context_->lineTo( xmid-1, y1-1 );

				context_->strokePath();

				context_->setColor( shadow );

				context_->moveTo( x1+1, y2-1 );
				context_->lineTo( x2-1, y2-1 );
				context_->lineTo( x2-1, ymid );
				context_->lineTo( xmid-1, y1 );

				context_->strokePath();
			}
			else if (state.isTickMarkingOnBottomRight()) {

				int xmid = x1 + ((x2-x1)/2);
				int ymid = y2 - ((x2-x1)/2);

				std::vector<Point> pts(6);
				pts[0] = Point(x1,y1);
				pts[1] = Point(x1,ymid);
				pts[2] = Point(xmid,y2);
				pts[3] = Point(x2,ymid);
				pts[4] = Point(x2,y1);
				pts[5] = Point(x1,y1);

				context_->setColor( face );
				context_->polyline( pts );
				context_->fillPath();


				context_->setColor( highlite );

				context_->moveTo( x2, y1 );
				context_->lineTo( x1, y1 );
				context_->lineTo( x1, ymid );
				context_->lineTo( xmid, y2 );
				context_->strokePath();

				context_->setColor( black );

				context_->moveTo( xmid, y2 );
				context_->lineTo( x2, ymid );
				context_->lineTo( x2, y1-1 );

				context_->strokePath();

				context_->setColor( shadow );

				context_->moveTo( xmid, y2-1 );
				context_->lineTo( x2-1, ymid );
				context_->lineTo( x2-1, y1 );

				context_->strokePath();
			}
		}
	}
	}
}

void Win32Context::drawThemeProgress( Rect* rect, ProgressState& state )
{
	Rect tmp = *rect;

	HTHEME theme = NULL;

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;


	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"PROGRESS" );
	}

	if ( theme ) {

		int dcs = ::SaveDC( dc_ );
		
		RECT progressContent;
		memset(&progressContent,0,sizeof(progressContent));
		
		RECT textRect;

		SetBkMode(dc_, TRANSPARENT);
		VCF::Font btnFont = *context_->getCurrentFont();
		HFONT font = NULL;

		::SetTextColor( dc_, btnFont.getColor()->getColorRef32() );

		if ( state.isVertical() ) {
			Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_, PP_CHUNKVERT, 0, &r, &progressContent );

			Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, PP_BARVERT, 0, &r, 0);

			textRect = progressContent;

			progressContent.top += (progressContent.left - r.left);
			progressContent.bottom -= (progressContent.left - r.left);


			progressContent.top = progressContent.bottom -
				((state.position_)/(state.max_-state.min_) * (progressContent.bottom-progressContent.top));

			Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, PP_CHUNKVERT, 0, &progressContent, 0);



			if ( System::isUnicodeEnabled() ) {
				LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
				font = ::CreateFontIndirectW( lf );
				::SelectObject( dc_, font );
			}
			else {
				LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
				font = ::CreateFontIndirectA( lf );
				::SelectObject( dc_, font );
			}

			textRect.left += 1;
			textRect.top += 1;
			textRect.right -= 1;
			textRect.bottom -= 1;

			Win32VisualStylesWrapper::DrawThemeText(theme, dc_, PP_CHUNKVERT, 0,
													state.progressCaption_.c_str(),
													state.progressCaption_.length(),
													DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_EXPANDTABS,
													NULL,
													&textRect);


		}
		else {
			Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc_, PP_CHUNK, 0, &r, &progressContent );

			Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, PP_BAR, 0, &r, 0);

			textRect = progressContent;

			progressContent.left += (progressContent.top - r.top);
			progressContent.right -= (progressContent.top - r.top);

			progressContent.right = progressContent.left +
				((state.position_)/(state.max_-state.min_) * (progressContent.right-progressContent.left));

			Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, PP_CHUNK, 0, &progressContent, 0);

			textRect.left += 1;
			textRect.top += 1;
			textRect.right -= 1;
			textRect.bottom -= 1;


			if ( System::isUnicodeEnabled() ) {
				LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
				font = ::CreateFontIndirectW( lf );
				::SelectObject( dc_, font );
			}
			else {
				LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
				font = ::CreateFontIndirectA( lf );
				::SelectObject( dc_, font );
			}

			Win32VisualStylesWrapper::DrawThemeText(theme, dc_, PP_CHUNK, 0,
													state.progressCaption_.c_str(),
													state.progressCaption_.length(),
													DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_EXPANDTABS,
													NULL,
													&textRect);
		}



		RestoreDC( dc_, dcs );

		DeleteObject( font );

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		::DrawEdge( dc_, &r, BDR_SUNKENINNER, BF_TOPLEFT|BF_SOFT );
		::DrawEdge( dc_, &r, BDR_SUNKENOUTER, BF_BOTTOMRIGHT|BF_SOFT );
		tmp.inflate( -2, -2 );

		Rect progressRect = tmp;

		double s = minVal<>( state.min_, state.max_ );
		double e = maxVal<>( state.min_, state.max_ );

		if ( state.isVertical() ) {
			progressRect.top_ = progressRect.bottom_ - ((state.position_/fabs(e-s)) * tmp.getHeight());
		}
		else {
			progressRect.right_ = progressRect.left_ + ((state.position_/(e-s)) * tmp.getWidth());
		}

		Color* progressBarColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION );

		if ( state.useCustomProgressColor() ) {
			progressBarColor = &state.customColor_;
		}

		context_->setColor( progressBarColor );
		context_->rectangle( progressRect );
		context_->fillPath();

		//draw text

		if ( !state.progressCaption_.empty() ) {
			Rect textBounds;


			if ( state.isVertical() ) {
				textBounds.left_ = progressRect.left_;
				textBounds.right_ = progressRect.right_;

				double h = minVal<>( context_->getTextHeight( "EM" ), tmp.getHeight()-2 );
				textBounds.top_ = tmp.top_ +
					(tmp.getHeight()/2.0 - h/2.0);

				textBounds.bottom_ = textBounds.top_ + h;

				textBounds.inflate( 0, 2 );
			}
			else {
				textBounds.top_ = progressRect.top_;
				textBounds.bottom_ = progressRect.bottom_;

				double w = minVal<>( context_->getTextWidth( state.progressCaption_ ), tmp.getWidth()-2 );

				textBounds.left_ = tmp.left_ +
					(tmp.getWidth()/2.0 - w/2.0);

				textBounds.right_ = textBounds.left_ + w;
			}

			int32 drawOptions = GraphicsContext::tdoNone;
			drawOptions |= GraphicsContext::tdoCenterHorzAlign;
			drawOptions |= GraphicsContext::tdoCenterVertAlign;

			Color oldColor = *context_->getCurrentFont()->getColor();

			Color* progressTextColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );
			if ( state.useCustomProgressTextColor() ) {
				progressTextColor = &state.customTextColor_;
			}
			context_->getCurrentFont()->setColor( progressTextColor );

			context_->textBoundedBy( &textBounds, state.progressCaption_, drawOptions );

			context_->getCurrentFont()->setColor(&oldColor);
		}
	}
}

void Win32Context::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	drawImage( rect->left_, rect->top_, rect, image, GraphicsContext::cmSource );
}

/**
Draws a header control that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeHeader( Rect* rect, ButtonState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;

	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"HEADER" );
	}

	if ( theme ) {
		int dcs = ::SaveDC( dc_ );
		SetBkMode(dc_, TRANSPARENT);
		VCF::Font hdrFont = *context_->getCurrentFont();
		HFONT font = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) hdrFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectW( lf );
			::SelectObject( dc_, font );
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) hdrFont.getFontPeer()->getFontHandleID();
			font = ::CreateFontIndirectA( lf );
			::SelectObject( dc_, font );
		}


		RECT textRect = r;

		textRect.left += 1;
		textRect.top += 1;
		textRect.right -= 5;
		textRect.bottom -= 1;

		int headerPart = HP_HEADERITEM;
		int headerState = 0;

		if ( state.isEnabled() ) {
			headerState = HIS_NORMAL;
			if ( state.isPressed() ) {
				headerState = HIS_PRESSED;
			}
		}


		Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, headerPart, headerState, &r, 0);
		Win32VisualStylesWrapper::DrawThemeText(theme, dc_, headerPart, 0,
													state.buttonCaption_.c_str(),
													state.buttonCaption_.length(),
													DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_EXPANDTABS,
													NULL,
													&textRect);

		RestoreDC( dc_, dcs );

		DeleteObject( font );

		Win32VisualStylesWrapper::CloseThemeData( theme );

	}
	else {
		UINT hdrState =  DFCS_BUTTONPUSH;
		
		int err = ::DrawFrameControl( dc_, &r, DFC_BUTTON, hdrState );
	}

	releaseHandle();
}

/**
draws edges, useful for separators, that is compliant
with the native windowing systems default look and feel.
use a mask or 1 or more values of type ContextPeer::EdgeType
to indicate which sides of the rect to draw an edge on
*/
void Win32Context::drawThemeEdge( Rect* rect, DrawUIState& state, const int32& edgeSides, const int32& edgeStyle )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;

	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"GLOBALS" );
	}

	if ( theme ) {
		int part = 0;

		UINT edge = 0;

		switch ( edgeStyle ) {
			case GraphicsContext::etRecessed : {
				edge = BDR_SUNKENOUTER;//EDGE_BUMP;
			}
			break;

			case GraphicsContext::etEtched : {
				edge = EDGE_ETCHED;
			}
			break;

			case GraphicsContext::etRaised : {
				edge = EDGE_RAISED;
			}
			break;

			case GraphicsContext::etSunken : {
				edge = EDGE_SUNKEN;
			}
			break;
		}
		UINT flags = 0;
		if ( edgeSides & GraphicsContext::etLeftSide ) {
			flags |= BF_LEFT;
		}

		if ( edgeSides & GraphicsContext::etRightSide ) {
			flags |= BF_RIGHT;
		}

		if ( edgeSides & GraphicsContext::etTopSide ) {
			flags |= BF_TOP;
		}

		if ( edgeSides & GraphicsContext::etBottomSide ) {
			flags |= BF_BOTTOM;
		}

		part = 1;//GP_BORDER;
		//ignore styles????

		int stateFlags = state.isEnabled() ? GBS_NORMAL : GBS_DISABLED;

		switch ( edgeStyle ) {
			case GraphicsContext::etRecessed : {
				stateFlags = 1;//BSS_FLAT;
			}
			break;

			case GraphicsContext::etEtched : {
				stateFlags = 1;//BSS_FLAT;
			}
			break;

			case GraphicsContext::etRaised : {
				stateFlags = 2;//BSS_RAISED;
			}
			break;

			case GraphicsContext::etSunken : {
				stateFlags = 3;//BSS_SUNKEN;
			}
			break;
		}



		Win32VisualStylesWrapper::DrawThemeEdge(theme, dc_, part, stateFlags, &r, edge, flags, 0);

		Win32VisualStylesWrapper::CloseThemeData( theme );
	}
	else {
		UINT edge = 0;
		switch ( edgeStyle ) {
			case GraphicsContext::etRecessed : {
				edge = BDR_SUNKENOUTER;//EDGE_BUMP;
			}
			break;

			case GraphicsContext::etEtched : {
				edge = EDGE_ETCHED;
			}
			break;

			case GraphicsContext::etRaised : {
				edge = EDGE_RAISED;
			}
			break;

			case GraphicsContext::etSunken : {
				edge = EDGE_SUNKEN;
			}
			break;
		}
		UINT flags = 0;
		if ( edgeSides & GraphicsContext::etLeftSide ) {
			flags |= BF_LEFT;
		}

		if ( edgeSides & GraphicsContext::etRightSide ) {
			flags |= BF_RIGHT;
		}

		if ( edgeSides & GraphicsContext::etTopSide ) {
			flags |= BF_TOP;
		}

		if ( edgeSides & GraphicsContext::etBottomSide ) {
			flags |= BF_BOTTOM;
		}

		//flags |= BF_SOFT;// | BF_ADJUST;
		::DrawEdge( dc_, &r, edge, flags );
	}
	releaseHandle();
}

void Win32Context::drawThemeBorder( Rect* rect, DrawUIState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (int32)rect->left_;
	r.top = (int32)rect->top_;
	r.right = (int32)rect->right_;
	r.bottom = (int32)rect->bottom_;

	HTHEME theme = NULL;

	switch ( state.getType() ) {
		case etTextbox : {
			if ( Win32VisualStylesWrapper::IsThemeActive() ) {
				theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"Edit" );
			}
			
			if ( theme ) {
				int part = EP_EDITTEXT;
				int partState = 0;
				
				if ( state.isEnabled() ) {
					partState = ETS_NORMAL;
				}
				else {
					partState = ETS_DISABLED;
				}


				Win32VisualStylesWrapper::DrawThemeBackground(theme, dc_, part, partState, &r, 0);
				Win32VisualStylesWrapper::CloseThemeData( theme );
			}
			else {
				
			}
		}
		break;
	}

	
	releaseHandle();
}

/**
Draws a size gripper for resizing a control/window that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{
	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"GLOBALS" );
	}

	if ( theme ) {
	}
}

/**
Draws a them compliant background
*/
void Win32Context::drawThemeBackground( Rect* rect, BackgroundState& state )
{
	Color* backColor = GraphicsToolkit::getSystemColor( state.colorType_ );
	
	if ( state.colorType_ == SYSCOLOR_WINDOW ) {
		backColor = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	}
		
	context_->setColor( backColor );
	context_->rectangle( rect );
	context_->fillPath();		
}

#define CXGAP				1		// num pixels between button and text
#define CXTEXTMARGIN		2		// num pixels after hilite to start text
#define CXBUTTONMARGIN		2		// num pixels wider button is than bitmap
#define CYBUTTONMARGIN		2		// ditto for height


/**
Draws the background appropriate for a menu item that is compliant
with the native windowing systems default look and feel.
This is typically called first by a menu item to give it a standard
look and feel in it's background before drawing any thing else
*/
void Win32Context::drawThemeMenuItem( Rect* rect, MenuState& state )
{
	RECT menuRect;
	memset(&menuRect,0,sizeof(menuRect));

	menuRect.left = (int32)rect->left_;
	menuRect.top = (int32)rect->top_;
	menuRect.right = (int32)rect->right_;
	menuRect.bottom = (int32)rect->bottom_;


	HTHEME theme = NULL;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"MENU" );
	}

	if ( theme ) {

	}
	else {

		if ( state.isSeparator() ) {
			RECT tmp = menuRect;
			
			tmp.top += (tmp.bottom - tmp.top) >>1; 	// vertical center
			
			::DrawEdge( dc_, &tmp, EDGE_ETCHED, BF_TOP);// draw separator line
			
		}
		else {
			RECT tmpBtnRect;
			tmpBtnRect.left = menuRect.left + 2;
			tmpBtnRect.top = menuRect.top;
			tmpBtnRect.right = menuRect.left + 2 + (menuRect.right - menuRect.left);
			tmpBtnRect.bottom = menuRect.top + (menuRect.bottom - menuRect.top);

			int cxButn = tmpBtnRect.bottom - tmpBtnRect.top;				// width of button


			state.imageRect_.setRect( tmpBtnRect.left, tmpBtnRect.top, 
										tmpBtnRect.right, tmpBtnRect.bottom );

			state.imageRect_.right_ = state.imageRect_.left_ + cxButn;

			

			COLORREF colorBG = ::GetSysColor( state.isHighlighted() ? COLOR_HIGHLIGHT : COLOR_MENU );
		
			// selected or selection state changed: paint text background
			RECT rcBG = menuRect;	// whole rectangle
			
			//if ( true == menuHasButn) {	// if there's a button:
			//	rcBG.left += cxButn + CXGAP;			//  don't paint over it!
			//}

			{
				HBRUSH brush = ::CreateSolidBrush( colorBG );
				
				HBRUSH oldBrush = (HBRUSH)::SelectObject( dc_, brush );
				
				PatBlt( dc_, rcBG.left, rcBG.top, rcBG.right - rcBG.left, rcBG.bottom - rcBG.top, PATCOPY);
				
				::SelectObject( dc_, oldBrush );
				DeleteObject( brush );

			}			
		}
	}
}


String generateMenuItemCaption( MenuState& state )
{
	String acceleratorText;
	
	//generate accelerator text if we are not owner drawn
	
	if ( state.hasControlKey() ) {			
		acceleratorText += "Ctrl";
	}

	if ( state.hasShiftKey() ) {
		if ( !acceleratorText.empty() ) {
			acceleratorText += "+";
		}
		acceleratorText += "Shift";
	}

	if ( state.hasAltKey() ) {
		if ( !acceleratorText.empty() ) {
			acceleratorText += "+";
		}
		acceleratorText += "Alt";
	}

	if ( !acceleratorText.empty() ) {
		acceleratorText += "+";
	}

	acceleratorText += 
			StringUtils::translateVKCodeToString( (VirtualKeyCode)state.keyCode_ );		


	String result = state.menuCaption_;

	if ( !acceleratorText.empty() ) {
		result = result + "\t" + acceleratorText;
	}

	return result;
}


void Win32Context::drawThemeMenuItemText( Rect* rect, MenuState& state )
{
	HTHEME theme = NULL;

	RECT rcText;
	memset(&rcText,0,sizeof(rcText));

	rcText.left = (int32)rect->left_;
	rcText.top = (int32)rect->top_;
	rcText.right = (int32)rect->right_;
	rcText.bottom = (int32)rect->bottom_;

	if ( Win32VisualStylesWrapper::IsThemeActive() ) {
		theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"MENU" );
	}

	if ( theme ) {

	}
	else {
		
		COLORREF colorText =
			GetSysColor( !state.isEnabled() ?  COLOR_GRAYTEXT :
								(state.isHighlighted() ? COLOR_HIGHLIGHTTEXT : COLOR_MENUTEXT));
	
		String left = generateMenuItemCaption( state );
		
		String right;
		
		int tabPos = left.find('\t');
		if ( tabPos != String::npos ) {
			if ( tabPos >= 0 ) {
				right = left.substr( tabPos + 1, left.size() - tabPos );
				
				left  = left.substr( 0, tabPos );
			}
		}
		
		::SetBkMode( dc_, TRANSPARENT );	

		COLORREF colorBG = ::GetSysColor( state.isHighlighted() ? COLOR_HIGHLIGHT : COLOR_MENU );

		rcText.left += state.imageRect_.getWidth() + CXGAP + CXTEXTMARGIN; // left margin
		rcText.right -= state.imageRect_.getWidth() - 2;				 // right margin

		if ( (!state.isEnabled() && !state.isHighlighted()) || (colorText == colorBG) ) {
				// disabled: draw hilite text shifted southeast 1 pixel for embossed
				// look. Don't do it if item is selected, tho--unless text color same
				// as menu highlight color. Got it?
				//
			rcText.left += 1;
			rcText.top += 1;

			::SetTextColor( dc_, GetSysColor(COLOR_3DHILIGHT) );

			if ( System::isUnicodeEnabled() ) {
				DrawTextW( dc_, left.c_str(), left.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
			}
			else {
				AnsiString tmp = left;
				DrawTextA( dc_, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
			}
			
			if (tabPos > 0) {
				if ( System::isUnicodeEnabled() ) {
					DrawTextW( dc_, right.c_str(), right.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_RIGHT);
				}
				else {
					AnsiString tmp = right;
					DrawTextA( dc_, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_RIGHT);
				}
				
			}
			
			rcText.left -= 1;
			rcText.top -= 1;
		}


		::SetTextColor( dc_, colorText );
		
		if ( System::isUnicodeEnabled() ) {
			DrawTextW( dc_, left.c_str(), left.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		}
		else {
			AnsiString tmp = left;
			DrawTextA( dc_, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		}
		
		if (tabPos > 0) {
			if ( System::isUnicodeEnabled() ) {
				DrawTextW( dc_, right.c_str(), right.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_RIGHT);
			}
			else {
				AnsiString tmp = right;
				DrawTextA( dc_, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_RIGHT);
			}			
		}
	}
}

void Win32Context::drawThemeText( Rect* rect, TextState& state )
{

	Font font;

	switch ( state.themeFontType_ ) {
		case GraphicsContext::ttMenuItemFont : {

		}
		break;

		case GraphicsContext::ttSelectedMenuItemFont : {

		}
		break;

		case GraphicsContext::ttSystemFont : {

		}
		break;

		case GraphicsContext::ttSystemSmallFont : {

		}
		break;

		case GraphicsContext::ttControlFont : {

		}
		break;

		case GraphicsContext::ttMessageFont : {

		}
		break;

		case GraphicsContext::ttToolTipFont : {

		}
		break;
	}

	Font oldFont = *context_->getCurrentFont();

	context_->setCurrentFont( &font );

	context_->textBoundedBy( rect, state.text_, state.wrapText_ );

	context_->setCurrentFont( &oldFont );
}

void Win32Context::prepareDCWithContextFont( HFONT& fontHandle )
{
	Font* ctxFont = context_->getCurrentFont();
	if ( NULL == ctxFont ){
		//throw exception
	}
	FontPeer* fontImpl = ctxFont->getFontPeer();

	if ( NULL == fontImpl ){
		//throw exception
	}

	fontHandle = NULL;
/*
	DWORD charSet;

	Locale* fontLocale = ctxFont->getLocale();
	if ( NULL == fontLocale ) {
		fontLocale = System::getCurrentThreadLocale();
	}


	//fontLocale = NULL;

	if ( NULL == fontLocale ) {
		charSet = DEFAULT_CHARSET;
	}
	else if ( !ctxFont->isTrueType() ) {
		charSet = DEFAULT_CHARSET;
	}
	else {

		LCID lcid = (LCID)PtrToUlong( fontLocale->getPeer()->getHandleID() );
		WORD langID = LANGIDFROMLCID( lcid );

		WORD primaryLangID = PRIMARYLANGID(langID);
		WORD subLangID = SUBLANGID(langID);

		switch ( primaryLangID ) {
			case LANG_LITHUANIAN: case LANG_LATVIAN: case LANG_ESTONIAN: {
				charSet = BALTIC_CHARSET;
			}
			break;

			case LANG_CHINESE: {
				charSet = CHINESEBIG5_CHARSET;

				if ( SUBLANG_CHINESE_SIMPLIFIED == subLangID ) {
					charSet = GB2312_CHARSET;
				}
			}
			break;

			case LANG_SLOVENIAN: case LANG_ALBANIAN:
			case LANG_ROMANIAN: case LANG_BULGARIAN: case LANG_CROATIAN:
			case LANG_BELARUSIAN: case LANG_UKRAINIAN: case LANG_HUNGARIAN:
			case LANG_SLOVAK: case LANG_POLISH: case LANG_CZECH: {
				charSet = EASTEUROPE_CHARSET;
			}
			break;

			case LANG_GREEK: {
				charSet = GREEK_CHARSET;
			}
			break;

			case LANG_KOREAN: {
				charSet = HANGUL_CHARSET;//???JOHAB_CHARSET instead????
			}
			break;

			case LANG_RUSSIAN: {
				charSet = RUSSIAN_CHARSET;
			}
			break;

			case LANG_TURKISH: {
				charSet = TURKISH_CHARSET;
			}
			break;

			case LANG_JAPANESE: {
				charSet = SHIFTJIS_CHARSET;
			}
			break;

			case LANG_HEBREW: {
				charSet = HEBREW_CHARSET;
			}
			break;

			case LANG_ARABIC: {
				charSet = ARABIC_CHARSET;
			}
			break;

			case LANG_THAI: {
				charSet = THAI_CHARSET;
			}
			break;

			default : {
				charSet = DEFAULT_CHARSET;
			}
			break;
		}
	}
*/

	if ( System::isUnicodeEnabled() ) {
		LOGFONTW* logFont = (LOGFONTW*)fontImpl->getFontHandleID();

		LONG oldOrientation = logFont->lfOrientation;

		//DWORD oldCharSet = logFont->lfCharSet;

		//logFont->lfCharSet = charSet;

		logFont->lfOrientation = logFont->lfEscapement = (LONG)(-context_->getRotation() * 10.0);


		fontHandle = CreateFontIndirectW( logFont );

		//logFont->lfCharSet = oldCharSet;
		logFont->lfOrientation = logFont->lfEscapement = oldOrientation;
	}
	else {
		LOGFONTA* logFont = (LOGFONTA*)fontImpl->getFontHandleID();

		LONG oldOrientation = logFont->lfOrientation;

		//DWORD oldCharSet = logFont->lfCharSet;

		logFont->lfOrientation = logFont->lfEscapement = (LONG)(-context_->getRotation() * 10.0);

		//logFont->lfCharSet = charSet;

		fontHandle = CreateFontIndirectA( logFont );

		//logFont->lfCharSet = oldCharSet;
		logFont->lfOrientation = logFont->lfEscapement = oldOrientation;
	}
}

bool Win32Context::prepareForDrawing( int32 drawingOperation )
{
	bool result = false;

	checkHandle();

	inFillPath_ = false;
	//pathStarted_ = false;

	if ( NULL != dc_ ){

		currentDCState_ = SaveDC( dc_ );

		GraphicsContext::DrawingOperation op = (GraphicsContext::DrawingOperation)drawingOperation;

		Color* currentColor = context_->getColor();

		context_->cacheRenderAreaAlpha();

		LOGBRUSH logBrush;
		memset( &logBrush, 0, sizeof(logBrush) );

		switch ( op ) {
			case GraphicsContext::doStroke : {

				logBrush.lbColor = 0;
				logBrush.lbHatch = 0;
				logBrush.lbStyle = BS_HOLLOW;
				currentHBrush_ = ::CreateBrushIndirect( &logBrush );

				logBrush.lbColor = currentColor->getColorRef32();
				logBrush.lbHatch = 0;
				logBrush.lbStyle = BS_SOLID;

				DWORD penStyle = PS_GEOMETRIC;
				penStyle |= PS_SOLID;

				switch ( context_->getLineCapStyle() ) {
					case GraphicsContext::lcsButtCap : {
						penStyle |= PS_ENDCAP_FLAT;
					}
					break;

					case GraphicsContext::lcsRoundCap : {
						penStyle |= PS_ENDCAP_ROUND;
					}
					break;

					case GraphicsContext::lcsSquareCap : {
						penStyle |= PS_ENDCAP_SQUARE;
					}
					break;
				}

				switch ( context_->getLineJoinStyle() ) {
					case GraphicsContext::ljsMiterJoin : {
						penStyle |= PS_JOIN_MITER;
					}
					break;

					case GraphicsContext::ljsRoundJoin : {
						penStyle |= PS_JOIN_ROUND;
					}
					break;

					case GraphicsContext::ljsBevelJoin : {
						penStyle |= PS_JOIN_BEVEL;
					}
					break;
				}

				currentHPen_ = ExtCreatePen( penStyle, (DWORD)context_->getStrokeWidth(),
											&logBrush, 0, NULL );


				SetMiterLimit( dc_, (FLOAT)context_->getMiterLimit(), NULL );

				if ( context_->getCompositingMode() == GraphicsContext::cmXOR ) {
					SetROP2( dc_, R2_NOTXORPEN );
				}
			}
			break;

			case GraphicsContext::doFill : {
				logBrush.lbColor = currentColor->getColorRef32();

				logBrush.lbStyle = BS_SOLID;
				logBrush.lbHatch = BS_NULL;

				currentHBrush_ = ::CreateBrushIndirect( &logBrush );

				currentHPen_ = ::CreatePen( PS_NULL, 0, 0 );

				inFillPath_ = true;

				//JC: this is new (9/19/2006), I put this in as the default
				//winding rule for fills. Do we want to leave this as the default....?
				SetPolyFillMode( dc_, WINDING );

				::BeginPath( dc_ );
			}
			break;

			case GraphicsContext::doText : {

				::SetBkMode( dc_, TRANSPARENT );

				Font* ctxFont = context_->getCurrentFont();
				if ( NULL == ctxFont ){
					//throw exception
				}
				FontPeer* fontImpl = ctxFont->getFontPeer();

				if ( NULL == fontImpl ){
					//throw exception
				}

				prepareDCWithContextFont( currentHFont_ );

				Color* fontColor = ctxFont->getColor();

				if ( NULL != fontColor ){
					::SetTextColor( dc_, fontColor->getColorRef32() );
				}
				else {
					::SetTextColor( dc_, RGB(0,0,0) );
				}



				::SelectObject( dc_, currentHFont_ );

			}
			break;

			case GraphicsContext::doImage : {

			}
			break;
		}

		if ( NULL != currentHBrush_ ) {
			SelectObject( dc_, currentHBrush_ );
		}

		if ( NULL != currentHPen_ ) {
			SelectObject( dc_, currentHPen_ );
		}

		result = true;
	}

	return result;
}

void Win32Context::finishedDrawing( int32 drawingOperation )
{

	if ( NULL != dc_ ){

		switch ( drawingOperation ) {
			case GraphicsContext::doStroke : {
			}
			break;

			case GraphicsContext::doFill : {

				::EndPath( dc_ );

				FillPath( dc_ );
			}
			break;

			case GraphicsContext::doText : {

			}
			break;

			case GraphicsContext::doImage : {

			}
			break;
		}

		RestoreDC( dc_, currentDCState_ );

		if ( NULL != currentHPen_ ) {
			DeleteObject( currentHPen_ );
			currentHPen_ = NULL;
		}

		if ( NULL != currentHBrush_ ) {
			DeleteObject( currentHBrush_ );
			currentHBrush_ = NULL;
		}

		if ( NULL != currentHFont_ ) {
			DeleteObject( currentHFont_ );
			currentHFont_ = NULL;
		}

		context_->renderAreaAlphaOverwritten();
	}
	else {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("HDC handle is NULL!!!") );
	}

	releaseHandle();
}


/**
$Id$
*/
