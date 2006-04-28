#ifndef _VCF_IMAGEBITS_H__
#define _VCF_IMAGEBITS_H__
//ImageBits.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

template < typename SizeType, bool FloatingPoint=false, bool GrayScale=false >
struct PixelTraits {
	enum {
		ChannelSize = sizeof(SizeType)*8
	};

	typedef SizeType ChannelType;

	static SizeType minVal()  {
		return FloatingPoint ? 0.0 : 0 ;
	}

	static SizeType maxVal()  {
		return FloatingPoint ? 1.0 : ChannelSize * 8 ;
	}

	static Image::ImageChannelSize getTraitsChannelSize() {
		return (Image::ImageChannelSize)ChannelSize;
	}

	static Image::ImageChannelType getTraitsChannelType() {
		return FloatingPoint ? Image::ictFloatingPoint : Image::ictInteger;
	}

	static Image::ImageType getTraitsImageType() {
		return GrayScale ? Image::itGrayscale : Image::itColor;
	}


	static Image::ImageChannelSize getChannelSize( Image::ImageDescriptor val ) {

		return (Image::ImageChannelSize)(((val & 0xFFFF) ^ (val & 0xFF)) >> 8);
	}

	static Image::ImageDescriptor setChannelSize( Image::ImageDescriptor& val, Image::ImageChannelSize size ) {
		Image::ImageDescriptor tmp =  (((val & 0xFFFF) ^ val) | (val & 0xFF));

		val = (size << 8);

		val |= tmp;

		return val;
	}

	static Image::ImageDescriptor setImageType( Image::ImageDescriptor& val, Image::ImageType type ) {
		val = ((val & 0xF) ^ val) | type;
		return val;
	}

	static Image::ImageType getImageType( Image::ImageDescriptor val ) {

		return (Image::ImageType)(val & 0xF);
	}

	static Image::ImageDescriptor setChannelType( Image::ImageDescriptor& val, Image::ImageChannelType type ) {
		Image::ImageDescriptor tmp =  (((val & 0xFFFFF) ^ val) | (val & 0xFFFF));
		val = (type << 16);
		val |= tmp;

		return val;
	}

	static Image::ImageChannelType getChannelType( Image::ImageDescriptor val ) {

		return (Image::ImageChannelType)(((val & 0xFFFFF) ^ (val & 0xFFFF)) >> 16);
	}

	static Image::ImageDescriptor setPixelLayoutOrder( Image::ImageDescriptor& val, Image::PixelLayoutOrder order ) {
		Image::ImageDescriptor tmp =  (((val & 0xFFFFFF) ^ val) | (val & 0xFFFFF));
		val = (order << 20);
		val |= tmp;

		return val;
	}

	static Image::PixelLayoutOrder getPixelLayoutOrder( Image::ImageDescriptor val ) {

		return (Image::PixelLayoutOrder)(((val & 0xFFFFFF) ^ (val & 0xFFFFF)) >> 20);
	}
};


template < typename PixTraits >
class PixelAllocater {
public:
	typedef PixTraits Traits;


	static typename Traits::ChannelType* allocate( unsigned long width, unsigned long height ) {

		return new typename Traits::ChannelType[ (height * width) * Traits::getTraitsImageType() ];
	}
};





/**
Defines a channel layout order of b,g,r,a with
BitSizeType bits per channel
*/
template < typename BitSizeType,
			bool FloatingPoint=false,
			typename PixTraitsType=PixelTraits<BitSizeType,FloatingPoint>,
			typename PixAllocaterType=PixelAllocater<PixTraitsType>	>
struct BGRAPixel {
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;
	enum {
		ChannelSize = Traits::ChannelSize
	};

	BitSizeType b;
	BitSizeType g;
	BitSizeType r;
	BitSizeType a;
};

#ifndef __GNUC__
/**
floating point specialization
*/
template <>
struct BGRAPixel<float, true > {
#if defined(VCF_VC71) || defined(VCF_VC80) || defined(VCF_BCC) || defined(VCF_CW)
	typedef PixelTraits<float, true> Traits;
	typedef PixelAllocater<Traits> Allocater;
#else
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;
#endif


	enum {
		ChannelSize = Traits::ChannelSize
	};

	float b;
	float g;
	float r;
	float a;
};
#endif





/**
Defines a channel layout order of r,g,b,a with
BitSizeType bits per channel
*/
template < typename BitSizeType,
			bool FloatingPoint=false,
			typename PixTraitsType=PixelTraits<BitSizeType,FloatingPoint>,
			typename PixAllocaterType=PixelAllocater<PixTraitsType> >
struct RGBAPixel {
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;

	enum {
		ChannelSize = Traits::ChannelSize
	};

	BitSizeType r;
	BitSizeType g;
	BitSizeType b;
	BitSizeType a;
};

#ifndef __GNUC__
/**
floating point specialization
*/
template <>
struct RGBAPixel<float, true > {

#if defined(VCF_VC71) || defined(VCF_VC80) || defined(VCF_BCC) || defined(VCF_CW)
	typedef PixelTraits<float, true> Traits;
	typedef PixelAllocater<Traits> Allocater;
#else
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;
#endif

	enum {
		ChannelSize = Traits::ChannelSize
	};

	float r;
	float g;
	float b;
	float a;
};
#endif

/**
Defines a channel layout order of a,r,g,b with
BitSizeType bits per channel
*/
template < typename BitSizeType,
			bool FloatingPoint=false,
			typename PixTraitsType=PixelTraits<BitSizeType,FloatingPoint>,
			typename PixAllocaterType=PixelAllocater<PixTraitsType> >
struct ARGBPixel {
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;

	enum {
		ChannelSize = Traits::ChannelSize
	};

	BitSizeType a;
	BitSizeType r;
	BitSizeType g;
	BitSizeType b;
};

#ifndef __GNUC__
/**
floating point specialization
*/
template <  >
struct ARGBPixel<float, true > {

#if defined(VCF_VC71) || defined(VCF_VC80) || defined(VCF_BCC) || defined(VCF_CW)
	typedef PixelTraits<float, true> Traits;
	typedef PixelAllocater<Traits> Allocater;
#else
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;
#endif

	enum {
		ChannelSize = Traits::ChannelSize
	};

	float a;
	float r;
	float g;
	float b;
};
#endif




/**
Defines a channel layout order of a,b,g,r with
BitSizeType bits per channel
*/
template < typename BitSizeType,
			bool FloatingPoint=false,
			typename PixTraitsType=PixelTraits<BitSizeType,FloatingPoint>,
			typename PixAllocaterType=PixelAllocater<PixTraitsType> >
struct ABGRPixel {
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;

	enum {
		ChannelSize = Traits::ChannelSize
	};

	BitSizeType a;
	BitSizeType b;
	BitSizeType g;
	BitSizeType r;
};

#ifndef __GNUC__
/**
floating point specialization
*/
template <  >
struct ABGRPixel<float,true> {

#if defined(VCF_VC71) || defined(VCF_VC80) || defined(VCF_BCC) || defined(VCF_CW)
	typedef PixelTraits<float, true> Traits;
	typedef PixelAllocater<Traits> Allocater;
#else
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;
#endif

	enum {
		ChannelSize = Traits::ChannelSize
	};

	float a;
	float b;
	float g;
	float r;
};
#endif




/**
Defines a channel layout order of a,b,g,r with
BitSizeType bits per channel
*/
template < typename BitSizeType,
			bool FloatingPoint=false,
			typename PixTraitsType=PixelTraits<BitSizeType,FloatingPoint,true>,
			typename PixAllocaterType=PixelAllocater<PixTraitsType> >
struct GrayscalePixel {

	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;

	enum {
		ChannelSize = Traits::ChannelSize
	};

	BitSizeType value;
};

#ifndef __GNUC__
/**
turned off for GCC until I figure out the right syntax!
floating point specialization
*/
template < >
struct GrayscalePixel<float,true> {

#if defined(VCF_VC71) || defined(VCF_VC80) || defined(VCF_BCC) || defined(VCF_CW)
	typedef PixelTraits<float, true> Traits;
	typedef PixelAllocater<Traits> Allocater;
#else
	typedef PixTraitsType Traits;
	typedef PixAllocaterType Allocater;
#endif

	enum {
		ChannelSize = Traits::ChannelSize
	};

	float value;
};
#endif


}; //VCF namespace



/**
determine platform type
which in turn defines the default pixel types and formats
*/

#if defined(WIN32)
	/**
	defines a default pixel format of BGR which is what win32 uses
	*/
	#define AGG_BGRA32
#elif defined(VCF_X11) || defined(VCF_GTK) || defined(VCF_OSX)
	/**
	defines a default pixel format of RGB which is what x/gtk uses
	*/
	#define AGG_RGBA32
#endif

#include "vcf/GraphicsKit/PixelFormats.h"
#include "vcf/GraphicsKit/AggCommon.h"

namespace VCF {


#if defined(WIN32)
	typedef BGRAPixel<unsigned char> SysPixelType;
	typedef GrayscalePixel<unsigned char> SysGrayscalePixelType;

	typedef GrayscalePixel<unsigned char> PixelFormatType;

#elif defined(VCF_X11) || defined(VCF_GTK) || defined(VCF_OSX)
	typedef RGBAPixel<unsigned char> SysPixelType;
	typedef GrayscalePixel<unsigned char> SysGrayscalePixelType;
#endif



#if (__BORLANDC__ < 0x0560)
#  define IMTRAITS SysPixelType::Traits
#else
#  define IMTRAITS ImageBits::Traits
#endif

/**
*Basic class for image bit twiddling
*default behaviour is to allow for RGBA channels
*/

#define IMAGEBITS_CLASSID		"ED88C098-26AB-11d4-B539-00C04F0196DA"

/**
\class ImageBits ImageBits.h "vcf/GraphicsKit/ImageBits.h"
@deprecated - Don't use this class anymore - it will be removed 
after the 0-7-0 release.
*/
class GRAPHICSKIT_API ImageBits : public Object {
//	typedef SysPixelType::Traits Traits;
public :

	typedef SysPixelType::Traits Traits;

	ImageBits():needsMemAlloc_(true),pixels_(NULL),renderBuffer_(NULL) {
		renderBuffer_ = new agg::rendering_buffer();
	};


	ImageBits( const unsigned long& width, const unsigned long& height, const bool& needsMemAlloc=true ):
		needsMemAlloc_(needsMemAlloc), pixels_(NULL), renderBuffer_(NULL) {

		allocatePixelMemory( width, height );


		renderBuffer_ = new agg::rendering_buffer();
	};

	virtual ~ImageBits(){
		if ( (NULL != pixels_) && (true == needsMemAlloc_) ) {
			delete [] pixels_;
		}

		delete renderBuffer_;
	};

	void allocatePixelMemory( unsigned long width, unsigned long height ) {
		if ( true == needsMemAlloc_ ) {
			if ( NULL != pixels_ ){
				delete [] pixels_;
			}

			pixels_ = (SysPixelType*)SysPixelType::Allocater::allocate( width, height );
		}
	}

	void attachRenderBuffer( unsigned long width, unsigned long height ) {
		renderBuffer_->attach( (unsigned char*)pixels_, width, height,
								width * (IMTRAITS::getTraitsImageType()) );
	}

	bool needsMemAlloc_;

	SysPixelType* pixels_;
	agg::rendering_buffer* renderBuffer_;
};

};


#endif // _VCF_IMAGEBITS_H__

/**
$Id$
*/
