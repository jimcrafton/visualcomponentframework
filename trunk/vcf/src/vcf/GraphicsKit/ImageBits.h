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
#if defined(VCF_VC71) || defined(VCF_BCC)
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

#if defined(VCF_VC71) || defined(VCF_BCC)
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

#if defined(VCF_VC71) || defined(VCF_BCC)
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

#if defined(VCF_VC71) || defined(VCF_BCC)
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

#if defined(VCF_VC71) || defined(VCF_BCC)
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
	/*
	defines a default pixel format of BGR which is what win32 uses
	*/
	#define AGG_BGRA32
#elif defined(VCF_X11) || defined(VCF_GTK) || defined(VCF_OSX)
	/*
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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/08/01 18:52:27  kiklop74
*A bit ugly workaround around BCB5 bugs during compilation
*
*Revision 1.1.2.3  2004/07/30 17:30:05  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.14.2.1  2004/04/26 21:58:39  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2004/02/15 21:55:36  ddiego
*Added changes for vc7.1 compiler, many thanks to Raghavendra Chandrashekara for helping with this.
*
*Revision 1.13  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.2.2  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.12.2.1  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.12  2003/08/09 02:56:43  ddiego
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
*Revision 1.11.2.4  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.11.2.3  2003/07/07 03:52:08  ddiego
*added further osx porting code, primarily to the GraphicsKit - hey we can
*draw lines ! Woot!
*
*Revision 1.11.2.2  2003/06/23 23:16:54  ddiego
*added some furtther implementation for the osx port
*
*Revision 1.11.2.1  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.11  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.10.4  2003/04/19 22:22:55  ddiego
*tested the code developed in windows using gtk in linux. Seems to work ok except for a
*few minor compiler glitches. Had to comment out the partial specialization for
*floating point image bits in include/graphics/ImageBits.h. Also made some
*adjustments in the makefiles for building the GraphicsKit and ApplicationKit
*from the build/make/Makefile.
*
*Revision 1.10.10.3  2003/04/17 04:29:47  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.10.10.2  2003/04/07 03:39:30  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.10.10.1  2003/03/12 03:10:25  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.12.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.9  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_IMAGEBITS_H__


