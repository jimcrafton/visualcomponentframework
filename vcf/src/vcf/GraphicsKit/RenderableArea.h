#ifndef _VCF_RENDERABLEAREA_H__
#define _VCF_RENDERABLEAREA_H__
//RenderableArea.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*borrowed from
*art_render.h & Libart_LGPL - library of basic graphic primitives
* Copyright (C) 2000 Raph Levien
*/


#include "vcf/FoundationKit/VCF.h"

namespace VCF {


class AlphaGamma;


#if RENDERABLE_MAX_DEPTH == 16
	typedef ushort RenderPixelMaxDepthType;
	#define RENDER_PIX_MAX_FROM_8(x) ((x) | ((x) << 8))
	#define RENDER_PIX_8_FROM_MAX(x) (((x) + 0x80 - (((x) + 0x80) >> 8)) >> 8)
#else
	#if RENDERABLE_MAX_DEPTH == 8
		typedef uchar RenderPixelMaxDepthType;
		#define RENDER_PIX_MAX_FROM_8(x) (x)
		#define RENDER_PIX_8_FROM_MAX(x) (x)
	#else
		#error RENDERABLE_MAX_DEPTH must be either 8 or 16
	#endif //RENDERABLE_MAX_DEPTH == 8
#endif //RENDERABLE_MAX_DEPTH == 16


#define RENDERABLE_MAX_CHAN			16


enum RenderAlphaType{
	RA_NONE=0,
	RA_SEPERATE,
	RA_PRE_MULTIPLY
};

enum RenderCompositeMode{
	RCM_NONE=0,
	RCM_NORMAL,
	RCM_ADDITIVE,
	RCM_SUBBTRACTIVE,
	RCM_MULTIPLY,
	RCM_DIVIDE
	//more to come
};

class GRAPHICSKIT_API RenderMaskRun {
public:
	int32 x_;
	int32 alpha_;
};

class GRAPHICSKIT_API RenderableArea {

public:
	RenderableArea( const int32& x0, const int32& y0, const int32& x1, const int32& y1,
					const int32& rowstride, uchar *pixels=NULL,
					int n_chan=4, const int32& depth,
					const RenderAlphaType& alpha_type=RA_NONE,
					AlphaGamma *alphaGamma=NULL ){};

	virtual ~RenderableArea(){};

	virtual void invoke();

	virtual void clear();

	virtual void clearRGB( const uint32& rgb );

	virtual void maskSolid( const int32& opacity );


protected:
	int32 x0_;
	int32 y0_;
	int32 x1_;
	int32 y1_;
	uchar* pixels_;
	int32 rowstride_;
	int32	numberOfChannels_;
	int32	depth_;
	RenderAlphaType alphaType_;

	bool isClear_;

	long clearColors_[RENDERABLE_MAX_CHAN + 1];
	uint32 opacity_; /* [0..0x10000] */

	RenderCompositeMode compositing_mode;

	AlphaGamma* alphaGamma_;

	uchar* alphaBuffer;

	/* parameters of intermediate buffer */
	int bufferDepth_;
	RenderAlphaType bufferAlpha_;
	uchar* imageBuffer_;

	/* driving alpha scanline data */
	/* A "run" is a contiguous sequence of x values with the same alpha value. */
	int runNumber_;

	RenderMaskRun* run_;

	/* A "span" is a contiguous sequence of x values with non-zero alpha. */
	int spanNumber_;
	int* spanX_;

	bool needSpan_;

private:


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
*Revision 1.7.8.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:10:47  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2003/01/08 00:19:44  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_RENDERABLEAREA_H__


