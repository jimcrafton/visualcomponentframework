#ifndef _VCF_PIXELBUFFER_H__
#define _VCF_PIXELBUFFER_H__
//PixelBuffer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

enum PixelFormat{
	PF_RGB = 0
};


class Rect;

class SortedVectorPath;

class Color;

class AlphaGamma;


class GRAPHICSKIT_API PixelBuffer {

public:
	PixelBuffer( const int32& width, const int32& height,
		         const int32& rowstride, uchar* pixels=NULL, const bool hasAlpha=true );

	PixelBuffer( const PixelBuffer& pixBufferToCopy );

	virtual ~PixelBuffer();

	virtual void destroyNotify( void* funcData, void* data );

	void affineTransform( PixelBuffer* dest, Rect* destRect, const double affine[6] );

	void render( SortedVectorPath* svp, Rect* clipRect, Color* lineColor, Color* fillColor, Color* backColor, AlphaGamma* gamma=NULL );
protected:

	void affineTransformRGB( PixelBuffer* dest, Rect* destRect, const double affine[6] );

	void affineTransformRGBA( PixelBuffer* dest, Rect* destRect, const double affine[6] );

private:

	void affineInvert (double dst[6], const double src[6]){
		double r_det = 0.0;

		r_det = 1.0 / (src[0] * src[3] - src[1] * src[2]);
		dst[0] = src[3] * r_det;
		dst[1] = -src[1] * r_det;
		dst[2] = -src[2] * r_det;
		dst[3] = src[0] * r_det;
		dst[4] = -src[4] * dst[0] - src[5] * dst[2];
		dst[5] = -src[4] * dst[1] - src[5] * dst[3];
	}

	PixelFormat format_;
	int32 numChannels_;
	bool hasAlpha_;
	int32 bitsPerSample_;

	uchar* pixels_;

	int32 width_;
	int32 height_;
	int32 rowStride_;
	void* destroyData_;

};

}; //end of namespace VCF


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
*Revision 1.8.8.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/12 03:10:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:44  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PIXELBUFFER_H__


