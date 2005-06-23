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
#include "thirdparty/common/agg/include/agg_span_image_filter_rgba32.h"
#include "thirdparty/common/agg/include/agg_scanline_u.h"


using namespace VCF;

#ifdef WINTHEMES
	std::auto_ptr<Win32ThemeDLLWrapper> Win32Context::pThemeDLL_;
#endif

Win32Context::Win32Context()
{
	init();
}

Win32Context::Win32Context( const unsigned long& width, const unsigned long& height )
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
	strokeWidth_ = 1.0;
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
	isXORModeOn_ = false;
	alignToBaseline_ = false;

	currentDCState_ = 0;
	currentHBrush_ = NULL;
	currentHPen_ = NULL;
	currentHFont_ = NULL;

#ifdef WINTHEMES
	if (pThemeDLL_.get()==0) pThemeDLL_.reset(new Win32ThemeDLLWrapper());
#endif

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

void Win32Context::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	//checkHandle();
	

	if ( (imageBounds->getWidth() > image->getWidth()) || (imageBounds->getHeight() > image->getHeight()) ) {
		throw BasicException( MAKE_ERROR_MSG("Invalid image bounds requested"), __LINE__);
	}


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

		agg::conv_transform< agg::path_storage >::iterator it = xfrmedImgPath.begin(0);
		
		
		agg::vertex_type vert = *it;	

		Rect xfrmedImageRect;
		Point p1(vert.x, vert.y );
		
		++it;
		vert = *it;	

		Point p2(vert.x, vert.y );
		
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



		while ( it != xfrmedImgPath.end() ) {			

			if ( xfrmedImageRect.left_ > (*it).x ) {
				xfrmedImageRect.left_ = (*it).x;
			}

			if ( xfrmedImageRect.right_ < (*it).x ) {
				xfrmedImageRect.right_ = (*it).x;
			}

			if ( xfrmedImageRect.top_ > (*it).y ) {
				xfrmedImageRect.top_ = (*it).y;
			}

			if ( xfrmedImageRect.bottom_ < (*it).y ) {
				xfrmedImageRect.bottom_ = (*it).y;
			}

			++it;
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

		
		
		typedef agg::renderer_base<pixfmt> RendererBase;
        typedef agg::renderer_scanline_u_solid<RendererBase> SolidRenderer;
		typedef agg::span_allocator<agg::rgba8> SpanAllocator;
		typedef agg::span_interpolator_linear<> SpanInterpolator;
		typedef agg::span_image_filter_rgba32_bilinear<agg::order_bgra32, 
                                                      SpanInterpolator> SpanGenerator;
        typedef agg::renderer_scanline_u<RendererBase, SpanGenerator> RendererType;

		

		BITMAPINFO bmpInfo;
		memset( &bmpInfo, 0, sizeof(BITMAPINFO) );
		bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biWidth = (long)xfrmedImageRect.getWidth();
		bmpInfo.bmiHeader.biHeight = (long)-xfrmedImageRect.getHeight(); // Win32 DIB are upside down - do this to filp it over
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 32;
		bmpInfo.bmiHeader.biCompression = BI_RGB;

		bmpInfo.bmiHeader.biSizeImage = (-bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;

		SysPixelType* bmpBuf = NULL;
		HDC xfrmDC = ::CreateCompatibleDC( NULL );
		HBITMAP hbmp = CreateDIBSection ( xfrmDC, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );
			

		safeToRender = (NULL != hbmp) ? true : false;

		if ( safeToRender ) {			

			HBITMAP oldBMP = (HBITMAP)SelectObject( xfrmDC, hbmp );

			BitBlt( xfrmDC, 0, 0, bmpInfo.bmiHeader.biWidth, -bmpInfo.bmiHeader.biHeight, 
					dc_, xfrmedImageRect.left_, xfrmedImageRect.top_, SRCCOPY );


			agg::rendering_buffer xfrmImgRenderBuf;
			xfrmImgRenderBuf.attach( (unsigned char*)bmpBuf, bmpInfo.bmiHeader.biWidth, 
										-bmpInfo.bmiHeader.biHeight,
										bmpInfo.bmiHeader.biWidth * 4 );


			
			pixfmt pixf(xfrmImgRenderBuf);
			RendererBase rb(pixf);
			SolidRenderer srcImageRenderer(rb);


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


			

			image->getImageBits()->attachRenderBuffer( image->getWidth(), image->getHeight() );

			SpanGenerator spanGen(spanAllocator, 
							 *image->getImageBits()->renderBuffer_, 
							 agg::rgba(0, 0, 0, 1.0),
							 interpolator);

			
			RendererType imageRenderer(rb, spanGen);

			agg::rasterizer_scanline_aa<> rasterizer;
			agg::scanline_u8 scanLine;

			rasterizer.add_path(xfrmedImgPath2);
			rasterizer.render(scanLine, imageRenderer);
			
			//rasterizer.render(scanLine, srcImageRenderer);



			SetDIBitsToDevice( dc_,
								(long)xfrmedImageRect.left_,
								(long)xfrmedImageRect.top_,
								(long)xfrmedImageRect.getWidth(),
								(long)xfrmedImageRect.getHeight(),
								0,
								0,
								0,
								(long)xfrmedImageRect.getHeight(),
								bmpBuf,
								&bmpInfo,
								DIB_RGB_COLORS );

			SelectObject( xfrmDC, oldBMP );
			DeleteObject( hbmp );
		}
		DeleteDC( xfrmDC );

	}
	else {

		Win32Image* win32image = (Win32Image*)(image);
		if ( NULL != win32image ){
			//HDC bmpDC = win32image->getDC();
			ImageBits* bits = win32image->getImageBits();
			HPALETTE oldPalette = NULL;
			if ( NULL != win32image->palette_ ){
				oldPalette = ::SelectPalette( dc_, win32image->palette_, FALSE );
				::RealizePalette( dc_ );
			}

			BITMAPINFO bmpInfo;
			memset( &bmpInfo, 0, sizeof(BITMAPINFO) );
			//memset( &bmpInfo.bmiHeader, 0, sizeof (BITMAPINFOHEADER) );
			bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
			bmpInfo.bmiHeader.biWidth = (long)imageBounds->getWidth();
			bmpInfo.bmiHeader.biHeight = (long)-imageBounds->getHeight(); // Win32 DIB are upside down - do this to filp it over
			bmpInfo.bmiHeader.biPlanes = 1;
			bmpInfo.bmiHeader.biBitCount = 32;
			bmpInfo.bmiHeader.biCompression = BI_RGB;

			bmpInfo.bmiHeader.biSizeImage = (bmpInfo.bmiHeader.biHeight) * bmpInfo.bmiHeader.biWidth * 4;



			SysPixelType* bmpBuf = NULL;
			SysPixelType* tmpBmpBuf = NULL;

			
			HBITMAP hbmp = CreateDIBSection ( dc_, &bmpInfo, DIB_RGB_COLORS, (void**)&bmpBuf, NULL, NULL );


			SysPixelType* imageBuf = image->getImageBits()->pixels_;

			if ( NULL != hbmp ) {

				int incr = (long)((imageBounds->top_ * image->getWidth()) + imageBounds->left_);
				imageBuf += incr;
				tmpBmpBuf = bmpBuf;
				int imgWidth = image->getWidth();
				int wIncr = (long)imageBounds->getWidth();
				int s = (int)imageBounds->top_;
				int e = (int)imageBounds->bottom_;
				unsigned char * scanLine = new unsigned char[wIncr];

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
					SetDIBitsToDevice( dc_,
										(long)x,
										(long)y,
										(long)imageBounds->getWidth(),
										(long)imageBounds->getHeight(),
										0,
										0,
										0,
										(long)imageBounds->getHeight(),
										bmpBuf,
										&bmpInfo,
										DIB_RGB_COLORS );
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


void Win32Context::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	int fixVal = 0;
	if ( true == inFillPath_ ){
		fixVal = 1;
	}
	::Rectangle( dc_, (long)x1, (long)y1, (long)(x2 + fixVal), (long)(y2 + fixVal) );
}

void Win32Context::roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
							 const double & xc, const double & yc)
{
	int fixVal = 0;
	if ( true == inFillPath_ ){
		fixVal = 1;
	}

	::RoundRect( dc_, (long)x1, (long)y1, (long)x2 + fixVal, (long)y2 + fixVal, (long)xc, (long)yc );
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

	::Ellipse( dc_, (long)ax1, (long)ay1, (long)(ax2 + fixVal), (long)(ay2 + fixVal) );
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

	::Arc( dc_, (long)ax1, (long)ay1, (long)ax2 + fixVal, (long)ay2 + fixVal,
				(long)x3, (long)y3, (long)x4, (long)y4 );
}


void Win32Context::polyline( const std::vector<Point>& pts)
{
	POINT* polyPts = new POINT[pts.size()];
	std::vector<Point>::const_iterator it = pts.begin();
	int i =0;
	while ( it != pts.end() ) {
		const Point& pt = *it;

		polyPts[i].x = (long)pt.x_;
		polyPts[i].y = (long)pt.y_;
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

	bezPts[0].x = (long)x1;
	bezPts[0].y = (long)y1;

	bezPts[1].x = (long)x2;
	bezPts[1].y = (long)y2;

	bezPts[2].x = (long)x3;
	bezPts[2].y = (long)y3;

	bezPts[3].x = (long)x4;
	bezPts[3].y = (long)y4;

	if ( inFillPath_ ){
		::BeginPath( dc_ );
		::PolyBezier( dc_, bezPts, 4 );
		::EndPath( dc_ );
		::FillPath( dc_ );
	}
	else {
		::PolyBezier( dc_, bezPts, 4 );
	}
}

void Win32Context::lineTo(const double & x, const double & y)
{
	::LineTo( dc_, (long)x, (long)y );
}

void Win32Context::moveTo(const double & x, const double & y)
{
	::MoveToEx( dc_, (long)x, (long)y, NULL );
}



OSHandleID Win32Context::getContextID()
{
	return (OSHandleID)dc_;
}

void Win32Context::setOrigin( const double& x, const double& y )
{
	checkHandle();

	POINT pt = {0,0};
	int err = ::SetViewportOrgEx( dc_, (long)x, (long)y, &pt );
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



		::BitBlt( dc_, (long)destRect.left_, (long)destRect.top_,
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


void Win32Context::textAt( const Rect& bounds, const String& text, const long& drawOptions )
{
	//checkHandle();
	if ( NULL == context_ ){
		//throw exception !
	}


	UINT textAlignment = (alignToBaseline_) ? TA_BASELINE | TA_LEFT : TA_TOP | TA_LEFT ;
	UINT oldTextAlignment = ::SetTextAlign( dc_, textAlignment );



	RECT r = {0,0,0,0};
	r.left = (long)bounds.left_;
	r.right = (long)bounds.right_;
	r.top = (long)bounds.top_;
	r.bottom = (long)bounds.bottom_;
	UINT formatOptions = 0;

	formatOptions = DT_NOCLIP; //this was put here to make rotated text look better JC



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

	formatOptions |= DT_EXPANDTABS;
	if ( System::isUnicodeEnabled() ) {
		VCFChar* textToDraw = new VCFChar[text.size()+1];
		memset( textToDraw, 0, (text.size()+1)*sizeof(VCFChar) );
		text.copy( textToDraw, text.size() );
		DrawTextExW( dc_, textToDraw, text.size(), &r, formatOptions, NULL );

		//clean up after ourselves
		delete[] textToDraw;
	}
	else {
		AnsiString tmpText = text;
		char* textToDraw = new char[tmpText.size()+1];
		memset( textToDraw, 0, tmpText.size()+1 );
		text.copy( textToDraw, tmpText.size() );
		DrawTextExA( dc_, textToDraw, tmpText.size(), &r, formatOptions, NULL );

		//clean up after ourselves
		delete[] textToDraw;
	}





	//releaseHandle();
}

bool Win32Context::isXORModeOn()
{
	return isXORModeOn_;
}

void Win32Context::setXORModeOn( const bool& XORModeOn )
{
	isXORModeOn_ = XORModeOn;
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
void Win32Context::drawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor)
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
			StringUtils::traceWithArgs( "Error in DeleteObject( %p )\n", clipRGN_, GetLastError() );
		}
	}

	clipRGN_ = NULL;

	if ( NULL != clipRect ) {
		if ( !clipRect->isNull() ) {
			clipRGN_ = CreateRectRgn( (long)clipRect->left_ + origin_.x_, 
										(long)clipRect->top_ + origin_.y_, 
										(long)clipRect->right_ + origin_.x_, 
										(long)clipRect->bottom_  + origin_.y_);			
		}
		else {
			clipRGN_ = NULL;
		}
	}


	if ( ERROR == ::SelectClipRgn( dc_, clipRGN_ ) ){
		StringUtils::traceWithArgs( "Error in SelectClipRgn( %p, %p )\n", dc_, clipRGN_, GetLastError() );
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
					MoveToEx( dc_, (long)pt.point_.x_ + origin_.x_, (long)pt.point_.y_ + origin_.y_, NULL );
				}
				break;

				case PathPoint::ptLineTo: {
					LineTo( dc_, (long)pt.point_.x_ + origin_.x_, (long)pt.point_.y_ + origin_.y_ );
				}
				break;

				case PathPoint::ptQuadTo: {

				}
				break;

				case PathPoint::ptCubicTo: {

				}
				break;

				case PathPoint::ptClose: {
					LineTo( dc_, (long)pt.point_.x_ + origin_.x_, (long)pt.point_.y_ + origin_.y_ );
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
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)rect->right_;
	r.bottom = (long)rect->bottom_;

	int err = ::DrawFocusRect( dc_, &r );

	releaseHandle();
}

void Win32Context::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)rect->right_;
	r.bottom = (long)rect->bottom_;

	int err = ::DrawFocusRect( dc_, &r );

	releaseHandle();
}

void Win32Context::drawThemeButtonRect( Rect* rect, ButtonState& state )
{
#ifdef WINTHEMES
	if (drawThemeButtonRectDLL( rect, state )) return;
#endif

	checkHandle();

	RECT btnRect;
	btnRect.left = rect->left_;
	btnRect.top = rect->top_;
	btnRect.right = rect->right_;
	btnRect.bottom = rect->bottom_;


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

	RECT captionRect = btnRect;

		
	if ( state.isDefaultButton() ) {
		InflateRect( &tmpRect, -1, -1 );
	}

	if ( true == isPressed ) {
		HBRUSH shadowBrush = CreateSolidBrush( ::GetSysColor( COLOR_3DSHADOW ) );
		::FrameRect( dc_, &tmpRect, shadowBrush );
		DeleteObject( shadowBrush );
		::OffsetRect( &captionRect, 1, 1 );
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

	VCF::Font btnFont;

	Rect centerRect( captionRect.left, captionRect.top, captionRect.right, captionRect.bottom );
	if ( System::isUnicodeEnabled() ) {
		LOGFONTW* lf = (LOGFONTW*) btnFont.getFontPeer()->getFontHandleID();
		font = ::CreateFontIndirectW( lf );
		oldFont = (HFONT) ::SelectObject( dc_, font );

		::DrawTextW( dc_, state.buttonCaption_.c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	}
	else {
		LOGFONTA* lf = (LOGFONTA*) btnFont.getFontPeer()->getFontHandleID();
		font = ::CreateFontIndirectA( lf );
		oldFont = (HFONT) ::SelectObject( dc_, font );

		::DrawTextA( dc_, state.buttonCaption_.ansi_c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	}


	::OffsetRect( &captionRect,
		(centerRect.getWidth() - (captionRect.right - captionRect.left))/2,
		(centerRect.getHeight() - (captionRect.bottom - captionRect.top))/2 );

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

		OffsetRect( &captionRect, 1, 1 );

		if ( System::isUnicodeEnabled() ) {
			::DrawTextW( dc_, state.buttonCaption_.c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
		}
		else {
			::DrawTextA( dc_, state.buttonCaption_.ansi_c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
		}

		OffsetRect( &captionRect, -1, -1 );

		SetTextColor( dc_, textColor );
	}

	if ( System::isUnicodeEnabled() ) {
		::DrawTextW( dc_, state.buttonCaption_.c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
	}
	else {
		::DrawTextA( dc_, state.buttonCaption_.ansi_c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
	}



	SetTextColor( dc_, oldTextColor );
	SetBkMode( dc_, oldBkMode );

	::SelectObject( dc_, oldFont );
	::DeleteObject( font );



	if ( state.isFocused() ) {
		RECT focusRect = btnRect;
		InflateRect( &focusRect, -4, -4 );		

		::DrawFocusRect( dc_, &focusRect );
	}


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



	releaseHandle();
}

#ifdef WINTHEMES
bool Win32Context::drawThemeButtonRectDLL( Rect* rect, ButtonState& state )
{
	if (!pThemeDLL_->IsAppThemed()) return false;
    
	HWND hWin=::WindowFromDC(dc_);
    HTHEME hTheme = pThemeDLL_->OpenThemeData(hWin, L"BUTTON");

	if (hTheme==0) return false;

	int BtnState=	state.isPressed()		? PBS_PRESSED	: PBS_NORMAL;
	BtnState|=		state.isEnabled()		? PBS_NORMAL	: PBS_DISABLED;
	BtnState|=		state.isHighlighted()	? PBS_HOT		: PBS_NORMAL;
	BtnState|=		state.isFocused()		? PBS_DEFAULTED : PBS_NORMAL;

	RECT btnRect;
	btnRect.left = rect->left_;
	btnRect.top = rect->top_;
	btnRect.right = rect->right_;
	btnRect.bottom = rect->bottom_;

    HRESULT res=pThemeDLL_->DrawThemeBackground(hTheme, dc_, BP_PUSHBUTTON, BtnState, &btnRect, 0);
	if (res!=S_OK) return false;

	res=pThemeDLL_->DrawThemeText(hTheme, dc_, BP_PUSHBUTTON, BtnState,
		state.buttonCaption_.c_str(),
		state.buttonCaption_.length(),
		DT_SINGLELINE | DT_CENTER | DT_VCENTER, NULL, &btnRect);
	if (res!=S_OK) return false;

    pThemeDLL_->CloseThemeData(hTheme);

	return true;
}
#endif

void Win32Context::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)(rect->left_ + rect->getHeight());
	r.bottom = (long)rect->bottom_;
	UINT chkState =  state.isToggled() ?  DFCS_BUTTONCHECK | DFCS_CHECKED : DFCS_BUTTONCHECK;

	int err = ::DrawFrameControl( dc_, &r, DFC_BUTTON, chkState );

	Rect tmp = *rect;
	tmp.left_ = r.right + 3;
	tmp.inflate( -1.0, -1.0 );

	if ( state.isFocused() ) {
		drawThemeFocusRect( &tmp, state );
	}
	
	releaseHandle();


	context_->textBoundedBy( &tmp, state.buttonCaption_, false );
}

void Win32Context::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)(rect->left_ + rect->getHeight());
	r.bottom = (long)rect->bottom_;
	UINT btnState =  state.isToggled() ?  DFCS_BUTTONRADIO | DFCS_CHECKED : DFCS_BUTTONRADIO;

	::DrawFrameControl( dc_, &r, DFC_BUTTON, btnState );

	Rect tmp = *rect;
	tmp.left_ = r.right + 3;
	tmp.inflate( -1.0, -1.0 );

	if ( state.isFocused() ) {
		drawThemeFocusRect( &tmp, state );
	}
	
	releaseHandle();


	context_->textBoundedBy( &tmp, state.buttonCaption_, false );	
}

void Win32Context::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	int dcState = ::SaveDC( dc_ );
	RECT r = {0};
	r.left = rect->left_;
	r.top = rect->top_;
	r.right = rect->right_;
	r.bottom = rect->bottom_;

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

void Win32Context::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)rect->right_;
	r.bottom = (long)rect->bottom_;
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

	releaseHandle();
}

void Win32Context::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state )
{

}

/**
Draws a tab, the part of the TabbedPages control that acts like a
little button to activate a page, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeTab( Rect* rect, TabState& state )
{

}

/**
Draws a tab page - the page on which other controls for the page are
parented to, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeTabPage( Rect* rect, DrawUIState& state )
{

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

	for (long i=0;i<=state.tickMarkFrequency_;i++ ) {
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

/**
Draws a slider control, like that used for a slider control, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeSlider( Rect* rect, SliderState& state )
{
	Rect tmp = *rect;


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

		thumbRect.offset( 0, (int)(thumbSize.width_/2)-(int)(((state.position_-state.min_)/(state.max_-state.min_))*rect->getHeight()) );
	}
	else {
		thumbRect.right_ = thumbRect.left_ + thumbSize.width_;

		thumbRect.offset( (int)(((state.position_-state.min_)/(state.max_-state.min_))*rect->getWidth()) - (int)(thumbSize.width_/2), 0 );
	}


	Color* highlite = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color* shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color faceTmp = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color* black = Color::getColor("black");

	//

	if ( (!state.isEnabled()) || state.isPressed() ) {
		double h,l,s;
		faceTmp.getHLS( h,l,s );
		faceTmp.setHLS( h,0.85,s );
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

/**
Draws a progress bar control, that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeProgress( Rect* rect, ProgressState& state )
{
	Rect tmp = *rect;
	
	drawThemeEdge( &tmp, state, GraphicsContext::etAllSides, GraphicsContext::etSunken );

	tmp.inflate( -1, -1 );

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

	context_->setColor( progressBarColor );
	context_->rectangle( progressRect );
	context_->fillPath();
}

void Win32Context::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	drawImage( rect->left_, rect->top_, rect, image );
}

/**
Draws a header control that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeHeader( Rect* rect, ButtonState& state )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)rect->right_;
	r.bottom = (long)rect->bottom_;
	UINT hdrState =  DFCS_BUTTONPUSH;

	int err = ::DrawFrameControl( dc_, &r, DFC_BUTTON, hdrState );

	releaseHandle();
}

/**
draws edges, useful for separators, that is compliant
with the native windowing systems default look and feel.
use a mask or 1 or more values of type ContextPeer::EdgeType
to indicate which sides of the rect to draw an edge on
*/
void Win32Context::drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle )
{
	checkHandle();

	RECT r = {0,0,0,0};
	r.left = (long)rect->left_;
	r.top = (long)rect->top_;
	r.right = (long)rect->right_;
	r.bottom = (long)rect->bottom_;

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

	releaseHandle();
}

/**
Draws a size gripper for resizing a control/window that is compliant
with the native windowing systems default look and feel
*/
void Win32Context::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{

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

/**
Draws the background appropriate for a menu item that is compliant
with the native windowing systems default look and feel.
This is typically called first by a menu item to give it a standard
look and feel in it's background before drawing any thing else
*/
void Win32Context::drawThemeMenuItem( Rect* rect, MenuState& state )
{
			
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

		LCID lcid = (LCID)fontLocale->getPeer()->getHandleID();
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


	if ( System::isUnicodeEnabled() ) {
		LOGFONTW* logFont = (LOGFONTW*)fontImpl->getFontHandleID();

		LONG oldOrientation = logFont->lfOrientation;
		
		DWORD oldCharSet = logFont->lfCharSet;

		logFont->lfCharSet = charSet;
		
		logFont->lfOrientation = logFont->lfEscapement = (LONG)(-context_->getRotation() * 10.0);
		
		
		fontHandle = CreateFontIndirectW( logFont );

		logFont->lfCharSet = oldCharSet;
		logFont->lfOrientation = logFont->lfEscapement = oldOrientation;
	}
	else {
		LOGFONTA* logFont = (LOGFONTA*)fontImpl->getFontHandleID();

		LONG oldOrientation = logFont->lfOrientation;

		DWORD oldCharSet = logFont->lfCharSet;

		logFont->lfOrientation = logFont->lfEscapement = (LONG)(-context_->getRotation() * 10.0);

		logFont->lfCharSet = charSet;

		fontHandle = CreateFontIndirectA( logFont );

		logFont->lfCharSet = oldCharSet;
		logFont->lfOrientation = logFont->lfEscapement = oldOrientation;
	}	
}

bool Win32Context::prepareForDrawing( long drawingOperation )
{
	bool result = false;

	checkHandle();

	inFillPath_ = false;
	//pathStarted_ = false;

	if ( NULL != dc_ ){

		currentDCState_ = SaveDC( dc_ );

		GraphicsContext::DrawingOperation op = (GraphicsContext::DrawingOperation)drawingOperation;

		Color* currentColor = context_->getColor();

		LOGBRUSH logBrush;
		memset( &logBrush, 0, sizeof(logBrush) );

		switch ( op ) {
			case GraphicsContext::doStroke : {
				LOGPEN logPen;
				memset( &logPen, 0, sizeof(logPen) );

				logPen.lopnColor = currentColor->getRGB();

				logPen.lopnStyle = PS_SOLID;//translateStrokeStyle( currentStroke_.style_ );
				logPen.lopnWidth.x = (long)context_->getStrokeWidth();

				currentHPen_ = ::CreatePenIndirect( &logPen );

				logBrush.lbColor = 0;
				logBrush.lbHatch = 0;
				logBrush.lbStyle = BS_HOLLOW;
				currentHBrush_ = ::CreateBrushIndirect( &logBrush );

				if ( isXORModeOn_ ) {
					SetROP2( dc_, R2_NOTXORPEN );
				}
			}
			break;

			case GraphicsContext::doFill : {
				logBrush.lbColor = currentColor->getRGB();

				logBrush.lbStyle = BS_SOLID;
				logBrush.lbHatch = BS_NULL;

				currentHBrush_ = ::CreateBrushIndirect( &logBrush );

				currentHPen_ = ::CreatePen( PS_NULL, 0, 0 );

				inFillPath_ = true;
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
					::SetTextColor( dc_, fontColor->getRGB() );
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

void Win32Context::finishedDrawing( long drawingOperation )
{

	if ( NULL != dc_ ){
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
	}
	else {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("HDC handle is NULL!!!") );
	}

	releaseHandle();
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2005/06/23 18:23:45  scottpearson
*Fixed bug in position of vertical sliders; now, sliders are positioned
*correctly.
*
*Revision 1.5  2005/01/02 03:04:26  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.4.2.2  2004/12/20 21:59:09  ddiego
*committing cheeseheads patches for the combobox control.
*
*Revision 1.4.2.1  2004/12/19 04:05:04  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.4  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3  2004/08/19 02:24:54  ddiego
*fixed bug [ 1007039 ] lightweight controls do not paint correctly.
*
*Revision 1.2.2.13  2004/11/09 18:47:20  chriskr
*changed class name VisualStylesXP to Win32ThemeDLLWrapper
*
*Revision 1.2.2.12  2004/11/06 20:22:32  chriskr
*added dynamic linking to UxTheme.dll
*added example xp theme support for drawThemeButtonRect()
*
*Revision 1.2.2.11  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.10  2004/09/08 02:21:57  ddiego
*fixed bug due to not checking return value of HBITMAP in drawImage.
*
*Revision 1.2.2.9  2004/09/06 23:06:51  ddiego
*fixed border in button class
*
*Revision 1.2.2.8  2004/09/06 18:34:24  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2.2.7  2004/09/06 04:43:51  ddiego
*added font rotation back in, this time with support for matching
*the graphic contexts current transform.
*
*Revision 1.2.2.6  2004/09/06 04:40:43  ddiego
*added font rotation back in, this time with support for matching
*the graphic contexts current transform.
*
*Revision 1.2.2.5  2004/09/06 03:33:21  ddiego
*updated the graphic context code to support image transforms.
*
*Revision 1.2.2.4  2004/09/03 04:05:46  ddiego
*fixes to add matrix transform support for images.
*
*Revision 1.2.2.3  2004/08/31 21:12:07  ddiego
*graphice save and restore state
*
*Revision 1.2.2.2  2004/08/31 04:12:13  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2.2.1  2004/08/19 03:22:54  ddiego
*updates so new system tray code compiles
*
*Revision 1.3  2004/08/19 02:24:54  ddiego
*fixed bug [ 1007039 ] lightweight controls do not paint correctly.
*
>>>>>>> 1.2.2.13
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.9  2004/07/16 04:01:50  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.8  2004/07/15 01:52:54  ddiego
*added drawThemeComboboxRect implementation so a combobox
*control draws itself correctly.
*
*Revision 1.1.2.7  2004/07/11 22:08:45  ddiego
*fixed an accidental checkin that resulted in scrolled
*drawing not showing up correctly
*
*Revision 1.1.2.6  2004/07/11 18:45:55  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.5  2004/07/09 20:07:20  ddiego
*fixed bug in drawing of theme thumb slider
*
*Revision 1.1.2.4  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.3  2004/06/30 20:05:53  ddiego
*added Locale support to Font class, and added support in the
*Win32Context class to check for the locale and set and appropriate
*character set when creating an HFONT handle
*
*Revision 1.1.2.2  2004/04/29 04:10:28  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.38.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.38  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.37.2.1  2004/03/01 05:59:19  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.37  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.36.2.3  2003/10/29 22:28:45  ddiego
*minor little change in how text widht is calculated (takes into consider
*ation the width of tabs)
*
*Revision 1.36.2.2  2003/10/28 04:06:12  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.36.2.1  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.36  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.35.2.5  2003/07/03 03:14:51  ddiego
*made some changes to the Path interface, and got rid of the PathEnumerator
*class
*
*Revision 1.35.2.4  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.35.2.3  2003/06/13 03:05:31  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.35.2.2  2003/06/05 03:48:54  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.35.2.1  2003/05/30 04:13:11  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.35  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.34.2.5  2003/05/14 03:04:30  ddiego
*fixed some bugs caused by some of the changes in the graphics kit that I made
*yesterday. All is well now.
*
*Revision 1.34.2.4  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.34.2.3  2003/04/07 03:39:32  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.34.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.34.2.1  2003/03/12 03:12:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.34  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.33.2.6  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.33.2.5  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.33.2.4  2002/12/28 21:51:19  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.33.2.3  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.33.2.2  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.33.2.1  2002/11/28 05:12:05  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.33  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.32.10.5  2002/11/17 01:20:38  cesarmello
*Removed the LR_COPYRETURNORG flag from CopyImage due to inconsistent Win32 behavior under Windows NT 4
*
*Revision 1.32.10.4  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.32.10.3  2002/10/07 05:02:55  ddiego
*addeds some more gui work to teh TemplateNewClassDlg.
*
*Revision 1.32.10.2  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.32.10.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.32  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.31.4.2  2002/04/27 15:52:27  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.31.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.31  2002/01/31 05:46:17  ddiego
*fixed resource leak with GraphicsContexts used as memory GC's
*Works fine in 98 with no drop of GDI resources.
*
*Revision 1.30  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.29  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


