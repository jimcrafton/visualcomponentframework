//ImageFormats.h

#ifndef _IMAGEFORMATS_H__
#define _IMAGEFORMATS_H__


#include "ImageFormats/ImageFormatsSelectLib.h"


class PNGLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PNGLoader();
	
	virtual ~PNGLoader();

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return true;
	}

	private:
	
};

class JPEGLoader : public VCF::Object, public VCF::ImageLoader {
public:
	JPEGLoader() {} ;
	
	virtual ~JPEGLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return true;
	}
	
};

class TIFFLoader : public VCF::Object, public VCF::ImageLoader {
public:
	TIFFLoader() {} ;
	
	virtual ~TIFFLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

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
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class KOALALoader : public VCF::Object, public VCF::ImageLoader {
public:
	KOALALoader() {} ;
	
	virtual ~KOALALoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};


class LBMLoader : public VCF::Object, public VCF::ImageLoader {
public:
	LBMLoader() {} ;
	
	virtual ~LBMLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};


class MNGLoader : public VCF::Object, public VCF::ImageLoader {
public:
	MNGLoader() {} ;
	
	virtual ~MNGLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class PCDLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PCDLoader() {} ;
	
	virtual ~PCDLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

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
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class PNMLoader : public VCF::Object, public VCF::ImageLoader {
public:
	PNMLoader() {} ;
	
	virtual ~PNMLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

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
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

class RASLoader : public VCF::Object, public VCF::ImageLoader {
public:
	RASLoader() {} ;
	
	virtual ~RASLoader() {};

	virtual VCF::Image* loadImageFromFile( const VCF::String& fileName );
	

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
	

	virtual void saveImageToFile( const VCF::String& fileName, VCF::Image* image );

	virtual bool canSaveImage(){
		return false;
	}
	
};

#endif //_IMAGEFORMATS_H__


