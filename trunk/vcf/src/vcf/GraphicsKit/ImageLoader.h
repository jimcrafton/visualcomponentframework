#ifndef _VCF_IMAGELOADER_H__
#define _VCF_IMAGELOADER_H__
//ImageLoader.h

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

/**
\class ImageLoader ImageLoader.h "vcf/GraphicsKit/ImageLoader.h"
*The ImageLoader interface provides a means to load up images into a generic Bitmap.
*Examples are JPEG ImageLoaders, GIF, BMP, etc ImageLoaders.
*
*@version 1.0
*@author Jim Crafton
*/
/*@interface*/
class GRAPHICSKIT_API ImageLoader {
public:
	virtual ~ImageLoader(){};

	/**
	*loads the image from a file
	*@param String the fully qualified file name that
	*specifies the image to load
	*/
	virtual Image* loadImageFromFile( const String& fileName )=0;

	/**
	*does this ImageLoader support saving the image
	*@return bool returns true if the ImageLoader supports
	*saving the image, otherwise returns false. If the this
	*function does return true, then it is safe to call
	*saveImageToFile()
	*/
	virtual bool canSaveImage() = 0;

	/**
	*Saves the image to file
	*@param String the fully qualified filename that specifies
	*the file to save.
	*@param Image the image object that will be saved
	*/
	virtual void saveImageToFile( const String& fileName, Image* image )=0;
};

};


#endif // _VCF_IMAGELOADER_H__

/**
$Id$
*/
