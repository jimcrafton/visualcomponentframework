//ImageFormats.h

#ifndef _IMAGEFORMATS_H__
#define _IMAGEFORMATS_H__


#include "ImageFormats/ImageFormatsSelectLib.h"




class TIFFLoader : public VCF::Object, public VCF::ImageLoader {
public:
	TIFFLoader() {} ;
	
	virtual ~TIFFLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	
	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return true;
	}
	
};

class IFFLoader : public VCF::Object, public VCF::ImageLoader {
public:
	IFFLoader() {} ;
	
	virtual ~IFFLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	
	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class PCXLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PCXLoader() {} ;
	
	virtual ~PCXLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	
	virtual  VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );
	
	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class PSDLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PSDLoader() {} ;
	
	virtual ~PSDLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );

	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class TARGALoader : public VCF::Object, public VCF::ImageLoader {
public:
	TARGALoader() {} ;
	
	virtual ~TARGALoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	
	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class PGMLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PGMLoader() {} ;
	
	virtual ~PGMLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	
	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class PICTLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PICTLoader() {} ;
	
	virtual ~PICTLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	
	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class SGILoader : public VCF::Object, public VCF::ImageLoader {
public:
	SGILoader() {} ;
	
	virtual ~SGILoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );

	virtual VCF::Image* loadImageFromBytes( const unsigned char* imageData, const VCF::uint64& dataLength );

	virtual VCF::Image* loadImageFromStream( VCF::InputStream* stream );

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};




#endif //_IMAGEFORMATS_H__


