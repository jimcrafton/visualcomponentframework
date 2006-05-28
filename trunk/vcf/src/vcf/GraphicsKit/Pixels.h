#ifndef _VCF_PIXELS_H__
#define _VCF_PIXELS_H__

//Pixels.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF {

/**
\class PixelTraits Pixels.h "vcf/GraphicsKit/Pixels.h"
*/
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

/**
\class PixelAllocater Pixels.h "vcf/GraphicsKit/Pixels.h"
*/
template < typename PixTraits >
class PixelAllocater {
public:
	typedef PixTraits Traits;


	static typename Traits::ChannelType* allocate( unsigned long width, unsigned long height ) {

		return new typename Traits::ChannelType[ (height * width) * Traits::getTraitsImageType() ];
	}
};





/**
\class BGRAPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class BGRAPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class RGBAPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class RGBAPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class ARGBPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class ARGBPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class ABGRPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class ABGRPixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class GrayscalePixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
\class GrayscalePixel Pixels.h "vcf/GraphicsKit/Pixels.h"
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
#  define SysPixelTypeTraits SysPixelType::Traits
#  define GrayPixelTypeTraits SysGrayscalePixelType::Traits
#else
#  define IMTRAITS ImageBits::Traits
#  define SysPixelTypeTraits SysPixelType::Traits
#  define GrayPixelTypeTraits SysGrayscalePixelType::Traits
#endif

/**
\class PixelException Pixels.h "vcf/GraphicsKit/Pixels.h"
*/
	class PixelException : public BasicException {
	public:

		PixelException( const String & message ): BasicException( message ){};

		virtual ~PixelException() throw() {};
	};


	/**
	\class Pixels Pixels.h "vcf/GraphicsKit/Pixels.h"
	*/
	template <typename PixelType>
	class Pixels {
	public:
		typedef PixelType Type;

		Pixels( Image* img ):buffer_(NULL),currentImage_(NULL),width_(0),height_(0) {
			assign( img );
		}

		~Pixels() {
			unLockImageBuffer( currentImage_ );
		}

		Pixels& operator=( Image* img ) {
			assign( img );
			return *this;
		}


		operator Type* () {
			return (Type*)buffer_;
		}

		operator agg::rendering_buffer& () {
			return renderBuffer_;
		}

		Type& at( uint32 x, uint32 y ) {

			return ((Type*)buffer_)[(y*width_)+x];
		}

		Type at( uint32 x, uint32 y ) const {

			return ((Type*)buffer_)[(y*width_)+x];
		}


		Type* buffer() {
			return (Type*)buffer_;
		}

		uint32 width() {
			if ( width_ != currentImage_->getWidth() ) {
				throw PixelException( "You've modified an image's width, potentially while it's locked! Any pixel access may be bogus!" );
			}
			return currentImage_->getWidth();
		}

		uint32 height() {
			if ( height_ != currentImage_->getHeight() ) {
				throw PixelException( "You've modified an image's width, potentially while it's locked! Any pixel access may be bogus!" );
			}
			return currentImage_->getHeight();
		}
	protected:

		void assign( Image* img ) {

			if ( NULL != currentImage_ ) {
				unLockImageBuffer( currentImage_ );
			}

			if ( (Type::Traits::getTraitsImageType() != img->getType()) ||
					(Type::ChannelSize != img->getChannelSize()) ) {
				throw PixelException( "Incompatible pixel type for this image. The image channel size doesn't match the pixel's expected size." );
			}


			currentImage_ = img;

			lockImageBuffer( currentImage_ );

			width_ = currentImage_->getWidth();
			height_ = currentImage_->getHeight();

			buffer_ = currentImage_->getData();

			renderBuffer_.attach( (unsigned char*)buffer_, width_, height_,
								width_ * (Type::Traits::getTraitsImageType()) );
		}

		void lockImageBuffer( Image* img ) {

		}

		void unLockImageBuffer( Image* img ) {
			if ( NULL != currentImage_ ) {

				width_ = 0;
				height_ = 0;
				renderBuffer_.attach( NULL, 0, 0, 0 );

				buffer_ = NULL;
				currentImage_ = NULL;
			}
		}

		void* buffer_;
		Image* currentImage_;
		uint32 width_;
		uint32 height_;
		agg::rendering_buffer renderBuffer_;
	private:
		Pixels();
		Pixels(const Pixels&);
		Pixels& operator=(const Pixels&);

	};



	typedef Pixels<SysPixelType> ColorPixels;
	typedef Pixels<SysGrayscalePixelType> GrayPixels;

};








namespace VCF {


	template<typename PixelType, int ColorChannelVal>
	class ChannelIterator;

	template<typename PixelType, int ColorChannelVal>
	class Channel;

	enum ColorChannel {
		ccRed,
		ccGreen,
		ccBlue,
		ccAlpha
	};



	template <typename PixelType, int ColorChannelVal>
	class Channel  {
	public:
		typedef _typename_ PixelType::Traits::ChannelType Type;
		typedef PixelType PixType;
		typedef ChannelIterator<PixelType,ColorChannelVal> Iterator;

		enum ChannelField {
			Field = ColorChannelVal
		};


		Channel( ColorPixels& colorPixels ): ptr_(NULL), endPtr_(NULL), pixels_(colorPixels),width_(0),height_(0){
			width_ = pixels_.width();
			height_ = pixels_.height();

			ptr_ = pixels_;
			endPtr_ = ptr_ + (width_ * height_) + 1;			
		}

		~Channel() {}

		Iterator begin();
		Iterator end();


		uint32 copyTo( Type* channelData, const uint32& dataLength ) const {
			uint32 result = 0;

			VCF_ASSERT( dataLength <= width_ * height_ );


			Type* tmp = channelData;
			while ( result < dataLength ) {
				switch ( Field ) {
					case ccRed : {
						*tmp = ptr_[result].r;
					}
					break;

					case ccGreen : {
						*tmp = ptr_[result].g;
					}
					break;

					case ccBlue : {
						*tmp = ptr_[result].b;
					}
					break;

					case ccAlpha : {
						*tmp = ptr_[result].a;
					}
					break;
				}

				tmp++;
				result ++;
			}
			return result;
		}

		uint32 copyFrom( const Type* channelData, const uint32& dataLength ) {
			uint32 result = 0;

			VCF_ASSERT( dataLength <= width_ * height_ );


			const Type* tmp = channelData;
			while ( result < dataLength ) {
				switch ( Field ) {
					case ccRed : {
						ptr_[result].r = *tmp;
					}
					break;

					case ccGreen : {
						ptr_[result].g = *tmp;
					}
					break;

					case ccBlue : {
						ptr_[result].b = *tmp;
					}
					break;

					case ccAlpha : {
						ptr_[result].a = *tmp;
					}
					break;
				}

				tmp++;
				result ++;
			}
			return result;
		}

		void fill( const Type& val ) {
			PixType* tmp = ptr_;
			while ( tmp != endPtr_ ) {

				switch ( Field ) {
					case ccRed : {
						tmp->r = val;
					}
					break;

					case ccGreen : {
						tmp->g = val;
					}
					break;

					case ccBlue : {
						tmp->b = val;
					}
					break;

					case ccAlpha : {
						tmp->a = val;
					}
					break;
				}
				tmp ++;
			}
		}

		Type& at( uint32 x, uint32 y ) {

			switch ( Field ) {
				case ccRed : {
					return ptr_[(y*width_)+x].r;
				}
				break;

				case ccGreen : {
					return ptr_[(y*width_)+x].g;
				}
				break;

				case ccBlue : {
					return ptr_[(y*width_)+x].b;
				}
				break;

				case ccAlpha : {
					return ptr_[(y*width_)+x].a;
				}
				break;
			}

			return ptr_[(y*width_)+x].b;
		}

		Type at( uint32 x, uint32 y ) const {

			switch ( Field ) {
				case ccRed : {
					return ptr_[(y*width_)+x].r;
				}
				break;

				case ccGreen : {
					return ptr_[(y*width_)+x].g;
				}
				break;

				case ccBlue : {
					return ptr_[(y*width_)+x].b;
				}
				break;

				case ccAlpha : {
					return ptr_[(y*width_)+x].a;
				}
				break;
			}

			return ptr_[(y*width_)+x].b;
		}

		Image* createImage() {
			Image* result = this->GraphicsToolkit::createImage( width_, height_, Image::itGrayscale );

			Type* data = (Type*)result->getData();

			copyTo( data, height_ * width_ );

			return result;
		}

		void updateFromImage( Image* image ) {
			VCF_ASSERT( image->getWidth() == width_ );
			VCF_ASSERT( image->getHeight() == height_ );
			VCF_ASSERT( image->getType() == Image::itGrayscale );

			Type* data = (Type*)image->getData();

			copyFrom( data, width_ * height_ );
		}

		friend class ChannelIterator<PixelType,ColorChannelVal>;
	protected:
		PixType* ptr_;
		PixType* endPtr_;
		ColorPixels& pixels_;
		uint32 width_;
		uint32 height_;
	};

	

	template <typename PixelType, int ColorChannelVal>
	class ChannelIterator {
	public:
		typedef _typename_ PixelType::Traits::ChannelType Type;
		typedef Channel<PixelType,ColorChannelVal> ChannelType;
		typedef _typename_ ChannelType::PixType PixType;

		ChannelIterator(): ptr_(NULL){}

		~ChannelIterator(){}


		bool operator == ( const ChannelIterator& rhs ) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator != ( const ChannelIterator& rhs ) const {
			return ptr_ != rhs.ptr_;
		}

		Type& operator*() {

			switch ( ChannelType::Field ) {
				case ccRed : {
					return ptr_->r;
				}
				break;

				case ccGreen : {
					return ptr_->g;
				}
				break;

				case ccBlue : {
					return ptr_->g;
				}
				break;

				case ccAlpha : {
					return ptr_->a;
				}
				break;
			}

			return ptr_->b; 
		}
		
		
		ChannelIterator& operator++() {		// prefix
			ptr_++;
			return *this;
		}

		ChannelIterator operator++(int) {  // postfix
			ChannelIterator before = *this;
			
			ptr_++;

			return before;
		}

		ChannelIterator& operator+=( const uint32& incrBy ) {		// prefix
			ptr_+= incrBy;
			return *this;
		}

		friend class Channel<PixelType,ColorChannelVal>;
	protected:
		void setToBegin( ChannelType& channel );

		void setToEnd( ChannelType& channel );

		PixType* ptr_;
	};


	template <typename PixelType, int ColorChannelVal>
	inline _typename_ Channel<PixelType, ColorChannelVal>::Iterator Channel<PixelType, ColorChannelVal>::begin()
	{
		Iterator res;
		res.setToBegin( *this );
		return res;
	}

	template <typename PixelType, int ColorChannelVal> 
	inline _typename_ Channel<PixelType, ColorChannelVal>::Iterator Channel<PixelType,ColorChannelVal>::end()
	{
		Iterator res;
		res.setToEnd( *this );
		return res;
	}

	template <typename PixelType, int ColorChannelVal> 
	inline void ChannelIterator<PixelType, ColorChannelVal>::setToBegin( ChannelType& channel )
	{
		ptr_ = channel.ptr_;
	}

	template <typename PixelType, int ColorChannelVal> 
	inline void ChannelIterator<PixelType, ColorChannelVal>::setToEnd( ChannelType& channel )
	{
		ptr_ = channel.endPtr_;
	}














	/**
	Red color channel iterator specilization
	*/
	template <>
	class ChannelIterator<ColorPixels::Type,ccRed> {
	public:
		typedef ColorPixels::Type::Traits::ChannelType Type;
		typedef Channel<ColorPixels::Type,ccRed> ChannelType;
		typedef ChannelType::PixType PixType;

		ChannelIterator(): ptr_(NULL){}

		~ChannelIterator(){}


		bool operator == ( const ChannelIterator& rhs ) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator != ( const ChannelIterator& rhs ) const {
			return ptr_ != rhs.ptr_;
		}

		Type& operator*() {
			return ptr_->r; 
		}
		
		
		ChannelIterator& operator++() {		// prefix
			ptr_++;
			return *this;
		}

		ChannelIterator operator++(int) {  // postfix
			ChannelIterator before = *this;
			
			ptr_++;

			return before;
		}

		ChannelIterator& operator+=( const uint32& incrBy ) {		// prefix
			ptr_+= incrBy;
			return *this;
		}

		friend class Channel<ColorPixels::Type,ccRed>;
	protected:
		void setToBegin( ChannelType& channel ) {
			ptr_ = channel.ptr_;
		}

		void setToEnd( ChannelType& channel ) {
			ptr_ = channel.endPtr_;
		}

		PixType* ptr_;
	};


	/**
	Green color channel iterator specilization
	*/
	template <>
	class ChannelIterator<ColorPixels::Type,ccGreen> {
	public:
		typedef ColorPixels::Type::Traits::ChannelType Type;
		typedef Channel<ColorPixels::Type,ccGreen> ChannelType;
		typedef ChannelType::PixType PixType;

		ChannelIterator(): ptr_(NULL){}

		~ChannelIterator(){}


		bool operator == ( const ChannelIterator& rhs ) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator != ( const ChannelIterator& rhs ) const {
			return ptr_ != rhs.ptr_;
		}

		Type& operator*() {
			return ptr_->g; 
		}
		
		
		ChannelIterator& operator++() {		// prefix
			ptr_++;
			return *this;
		}

		ChannelIterator operator++(int) {  // postfix
			ChannelIterator before = *this;
			
			ptr_++;

			return before;
		}

		ChannelIterator& operator+=( const uint32& incrBy ) {		// prefix
			ptr_+= incrBy;
			return *this;
		}

		friend class Channel<ColorPixels::Type,ccGreen>;
	protected:
		void setToBegin( ChannelType& channel ) {
			ptr_ = channel.ptr_;
		}

		void setToEnd( ChannelType& channel ) {
			ptr_ = channel.endPtr_;
		}

		PixType* ptr_;
	};


	/**
	Blue color channel iterator specilization
	*/
	template <>
	class ChannelIterator<ColorPixels::Type,ccBlue> {
	public:
		typedef ColorPixels::Type::Traits::ChannelType Type;
		typedef Channel<ColorPixels::Type,ccBlue> ChannelType;
		typedef ChannelType::PixType PixType;

		ChannelIterator(): ptr_(NULL){}

		~ChannelIterator(){}


		bool operator == ( const ChannelIterator& rhs ) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator != ( const ChannelIterator& rhs ) const {
			return ptr_ != rhs.ptr_;
		}

		Type& operator*() {
			return ptr_->b; 
		}
		
		
		ChannelIterator& operator++() {		// prefix
			ptr_++;
			return *this;
		}

		ChannelIterator operator++(int) {  // postfix
			ChannelIterator before = *this;
			
			ptr_++;

			return before;
		}

		ChannelIterator& operator+=( const uint32& incrBy ) {		// prefix
			ptr_+= incrBy;
			return *this;
		}

		friend class Channel<ColorPixels::Type,ccBlue>;
	protected:
		void setToBegin( ChannelType& channel ) {
			ptr_ = channel.ptr_;
		}

		void setToEnd( ChannelType& channel ) {
			ptr_ = channel.endPtr_;
		}

		PixType* ptr_;
	};



	/**
	Alpha color channel iterator specilization
	*/
	template <>
	class ChannelIterator<ColorPixels::Type,ccAlpha> {
	public:
		typedef ColorPixels::Type::Traits::ChannelType Type;
		typedef Channel<ColorPixels::Type,ccAlpha> ChannelType;
		typedef ChannelType::PixType PixType;

		ChannelIterator(): ptr_(NULL){}

		~ChannelIterator(){}


		bool operator == ( const ChannelIterator& rhs ) const {
			return ptr_ == rhs.ptr_;
		}

		bool operator != ( const ChannelIterator& rhs ) const {
			return ptr_ != rhs.ptr_;
		}

		Type& operator*() {
			return ptr_->a; 
		}
		
		
		ChannelIterator& operator++() {		// prefix
			ptr_++;
			return *this;
		}

		ChannelIterator operator++(int) {  // postfix
			ChannelIterator before = *this;
			
			ptr_++;

			return before;
		}

		ChannelIterator& operator+=( const uint32& incrBy ) {		// prefix
			ptr_+= incrBy;
			return *this;
		}

		friend class Channel<ColorPixels::Type,ccAlpha>;
	protected:
		void setToBegin( ChannelType& channel ) {
			ptr_ = channel.ptr_;
		}

		void setToEnd( ChannelType& channel ) {
			ptr_ = channel.endPtr_;
		}

		PixType* ptr_;
	};

	typedef Channel<ColorPixels::Type,ccRed> RedChannel;
	typedef Channel<ColorPixels::Type,ccGreen> GreenChannel;
	typedef Channel<ColorPixels::Type,ccBlue> BlueChannel;
	typedef Channel<ColorPixels::Type,ccAlpha> AlphaChannel;
};


#endif //_VCF_PIXELS_H__

/**
$Id$
*/
