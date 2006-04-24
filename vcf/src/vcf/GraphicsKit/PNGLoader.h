
#ifndef _VCF_PNGLOADER_H__
#define _VCF_PNGLOADER_H__
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
\class PNGLoader PNGLoader.h "vcf/GraphicsKit/PNGLoader.h"
A class for built in support for reading and writing PNG images.
*/
class GRAPHICSKIT_API PNGLoader : public Object, public ImageLoader {
public:
	PNGLoader();

	virtual ~PNGLoader();

	virtual Image* loadImageFromFile( const String& fileName );

	virtual void saveImageToFile( const String& fileName, Image* image );

	virtual bool canSaveImage(){
		return true;
	}

};

};

#endif //_VCF_PNGLOADER_H__

