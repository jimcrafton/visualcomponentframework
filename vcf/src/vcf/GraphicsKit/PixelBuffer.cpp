//PixelBuffer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"



using namespace VCF;

#define EPSILON 1e-6

void PixelBufferAffineRun( int *p_x0, int *p_x1, int y, int src_width, int src_height, const double affine[6] )
{
  int x0, x1;
  double z;
  double x_intercept;
  int xi;

  x0 = *p_x0;
  x1 = *p_x1;

  /* do left and right edges */
  if (affine[0] > EPSILON)
    {
      z = affine[2] * (y + 0.5) + affine[4];
      x_intercept = -z / affine[0];
      xi = ceil (x_intercept + EPSILON - 0.5);
      if (xi > x0)
	x0 = xi;
      x_intercept = (-z + src_width) / affine[0];
      xi = ceil (x_intercept - EPSILON - 0.5);
      if (xi < x1)
	x1 = xi;
    }
  else if (affine[0] < -EPSILON)
    {
      z = affine[2] * (y + 0.5) + affine[4];
      x_intercept = (-z + src_width) / affine[0];
      xi = ceil (x_intercept + EPSILON - 0.5);
      if (xi > x0)
	x0 = xi;
      x_intercept = -z / affine[0];
      xi = ceil (x_intercept - EPSILON - 0.5);
      if (xi < x1)
	x1 = xi;
    }
  else
    {
      z = affine[2] * (y + 0.5) + affine[4];
      if (z < 0 || z >= src_width)
	{
	  *p_x1 = *p_x0;
	  return;
	}
    }

  /* do top and bottom edges */
  if (affine[1] > EPSILON)
    {
      z = affine[3] * (y + 0.5) + affine[5];
      x_intercept = -z / affine[1];
      xi = ceil (x_intercept + EPSILON - 0.5);
      if (xi > x0)
	x0 = xi;
      x_intercept = (-z + src_height) / affine[1];
      xi = ceil (x_intercept - EPSILON - 0.5);
      if (xi < x1)
	x1 = xi;
    }
  else if (affine[1] < -EPSILON)
    {
      z = affine[3] * (y + 0.5) + affine[5];
      x_intercept = (-z + src_height) / affine[1];
      xi = ceil (x_intercept + EPSILON - 0.5);
      if (xi > x0)
	x0 = xi;
      x_intercept = -z / affine[1];
      xi = ceil (x_intercept - EPSILON - 0.5);
      if (xi < x1)
	x1 = xi;
    }
  else
    {
      z = affine[3] * (y + 0.5) + affine[5];
      if (z < 0 || z >= src_height)
	{
	  *p_x1 = *p_x0;
	  return;
	}
    }

  *p_x0 = x0;
  *p_x1 = x1;
}

PixelBuffer::PixelBuffer( const int32& width, const int32& height,
		                  const int32& rowstride, uchar* pixels, const bool hasAlpha )
{
	this->bitsPerSample_ = 8;
	this->format_ = PF_RGB;
	this->hasAlpha_ = hasAlpha;
	this->height_ = height;
	this->numChannels_ = (hasAlpha) ? 4 : 3;
	this->pixels_ = NULL;
	this->rowStride_ = rowstride;
	this->width_ = width;

	int size = (height_ - 1) * rowStride_ + width_ * ((numChannels_ * bitsPerSample_ + 7) >> 3);

	pixels_ = new uchar[ size ];
	if ( NULL != pixels ){
		memcpy( pixels_, pixels, size );
	}
	else {
		memset( pixels_, 0, size );
	}
}

PixelBuffer::PixelBuffer( const PixelBuffer& pixBufferToCopy )
{
	this->bitsPerSample_ = pixBufferToCopy.bitsPerSample_;
	this->format_ = pixBufferToCopy.format_;
	this->hasAlpha_ = pixBufferToCopy.hasAlpha_;
	this->height_ = pixBufferToCopy.height_;
	this->numChannels_ = pixBufferToCopy.numChannels_;
	this->pixels_ = NULL;
	this->rowStride_ = pixBufferToCopy.rowStride_;
	this->width_ = pixBufferToCopy.width_;

	int size = (height_ - 1) * rowStride_ + width_ * ((numChannels_ * bitsPerSample_ + 7) >> 3);

	pixels_ = new uchar[ size ];

	memcpy( pixels_, pixBufferToCopy.pixels_, size );
}

PixelBuffer::~PixelBuffer()
{
	delete [] pixels_;
}

void PixelBuffer::destroyNotify( void* funcData, void* data )
{

}

void PixelBuffer::affineTransform( PixelBuffer* dest, Rect* destRect, const double affine[6] )
{
	if ( true == this->hasAlpha_ ){
		this->affineTransformRGBA( dest, destRect, affine );
	}
	else {
		this->affineTransformRGB( dest, destRect, affine );
	}
}

void PixelBuffer::affineTransformRGB( PixelBuffer* dest, Rect* destRect, const double affine[6] )
{
	double inv[6];
	uchar* dst_p = NULL;
	uchar* dst_linestart = NULL;
	const uchar* src_p = NULL;
	Point pt;
	Point src_pt;
	int src_x = 0;
	int src_y = 0;
	int run_x0 = 0;
	int run_x1 = 0;

	dst_linestart = dest->pixels_;

	affineInvert(inv, affine);
	int x0 = destRect->left_;
	int x1 = destRect->right_;
	int w = destRect->getWidth();
	int h = destRect->getHeight();
	for (int y = destRect->top_; y < destRect->bottom_; y++) {
		pt.y_ = y + 0.5;
		run_x0 = x0;
		run_x1 = x1;

		PixelBufferAffineRun (&run_x0, &run_x1, y, this->width_, this->height_, inv);

		dst_p = dst_linestart + (run_x0 - x0) * 3;
		for (int x = run_x0; x < run_x1; x++){
			pt.x_ = x + 0.5;
			//art_affine_point (&src_pt, &pt, inv);
			src_x = floor (src_pt.x_);
			src_y = floor (src_pt.y_);
			src_p = this->pixels_ + (src_y * this->rowStride_) + src_x * 3;
			dst_p[0] = src_p[0];
			dst_p[1] = src_p[1];
			dst_p[2] = src_p[2];
			dst_p += 3;
		}
		dst_linestart += dest->rowStride_;
    }
}

void PixelBuffer::affineTransformRGBA( PixelBuffer* dest, Rect* destRect, const double affine[6] )
{

}

void PixelBuffer::render( SortedVectorPath* svp, Rect* clipRect, Color* lineColor, Color* fillColor, Color* backColor, AlphaGamma* gamma )
{
	if ( (NULL != svp) && (NULL != clipRect) && (NULL != lineColor) && (NULL != fillColor) && (NULL != backColor) ){
		int r_fg = 0;
		int g_fg = 0;
		int b_fg = 0;
		int r_bg = 0;
		int g_bg = 0;
		int b_bg = 0;
		int r = 0;
		int g = 0;
		int b = 0;
		int dr = 0;
		int dg = 0;
		int db = 0;

		uint32 rgbtab[256];

		uint32 fg_color = fillColor->getRGB();
		uint32 bg_color = backColor->getRGB();

		/**
		*set up the colors for the Gamma table
		*/
		if ( NULL == gamma ){
			r_fg = fg_color >> 16;
			g_fg = (fg_color >> 8) & 0xff;
			b_fg = fg_color & 0xff;

			r_bg = bg_color >> 16;
			g_bg = (bg_color >> 8) & 0xff;
			b_bg = bg_color & 0xff;

			r = (r_bg << 16) + 0x8000;
			g = (g_bg << 16) + 0x8000;
			b = (b_bg << 16) + 0x8000;
			dr = ((r_fg - r_bg) << 16) / 255;
			dg = ((g_fg - g_bg) << 16) / 255;
			db = ((b_fg - b_bg) << 16) / 255;

			for (int i = 0; i < 256; i++) {
				rgbtab[i] = (r & 0xff0000) | ((g & 0xff0000) >> 8) | (b >> 16);
				r += dr;
				g += dg;
				b += db;
			}
		}
		else {
			int32 *table = gamma->getTable();

			r_fg = table[fg_color >> 16];
			g_fg = table[(fg_color >> 8) & 0xff];
			b_fg = table[fg_color & 0xff];

			r_bg = table[bg_color >> 16];
			g_bg = table[(bg_color >> 8) & 0xff];
			b_bg = table[bg_color & 0xff];

			r = (r_bg << 16) + 0x8000;
			g = (g_bg << 16) + 0x8000;
			b = (b_bg << 16) + 0x8000;
			dr = ((r_fg - r_bg) << 16) / 255;
			dg = ((g_fg - g_bg) << 16) / 255;
			db = ((b_fg - b_bg) << 16) / 255;

			uchar *invtab = gamma->getInvTable();
			for (int i = 0; i < 256; i++) {
				rgbtab[i] = (invtab[r >> 16] << 16) |
					(invtab[g >> 16] << 8) |
					invtab[b >> 16];
				r += dr;
				g += dg;
				b += db;
			}
		}

		int x0 = clipRect->top_;
		int y0 = clipRect->left_;
		int x1 = clipRect->right_;
		int y1 = clipRect->bottom_;
		for (int y = y0;y<y1;y++) {

		}

	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/05/17 20:37:22  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/12 03:12:04  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:50  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


