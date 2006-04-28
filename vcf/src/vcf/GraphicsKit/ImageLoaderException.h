#ifndef _VCF_IMAGELOADEREXCEPTION_H__
#define _VCF_IMAGELOADEREXCEPTION_H__
//ImageLoaderException.h

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
\class ImageLoaderException ImageLoaderException.h "vcf/GraphicsKit/ImageLoaderException.h"
*/
	class GRAPHICSKIT_API ImageLoaderException : public BasicException {
	public:

		ImageLoaderException(const String & message ):
		  BasicException( message ){

		  };

		  ImageLoaderException():
		  BasicException( "Image file unreadable - this may be due to an incorrect file name" ){

		  };

		  ImageLoaderException( const String & message, const int lineNumber ):
		  BasicException(message, lineNumber){};

	};

};


#endif // _VCF_IMAGELOADEREXCEPTION_H__

/**
$Id$
*/
