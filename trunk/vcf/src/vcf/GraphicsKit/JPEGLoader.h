
#ifndef _VCF_JPEGLOADER_H__
#define _VCF_JPEGLOADER_H__

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
\class JPEGLoader JPEGLoader.h "vcf/GraphicsKit/JPEGLoader.h"
A class for built in support for reading and writing JPEG images.
*/
class GRAPHICSKIT_API JPEGLoader : public Object, public ImageLoader {
public:
	JPEGLoader();

	virtual ~JPEGLoader();

	virtual Image* loadImageFromFile( const String& fileName );

	virtual void saveImageToFile( const String& fileName, Image* image );

	virtual bool canSaveImage(){
		return true;
	}

};

};

#endif //_VCF_JPEGLOADER_H__

