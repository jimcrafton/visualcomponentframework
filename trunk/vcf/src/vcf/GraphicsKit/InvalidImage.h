#ifndef _VCF_INVALIDIMAGE_H__
#define _VCF_INVALIDIMAGE_H__
//InvalidImage.h

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

class GRAPHICSKIT_API InvalidImage : public BasicException
{
public:

	InvalidImage(const VCF::String & message):
	  VCF::BasicException( message ){};

	InvalidImage():
		VCF::BasicException( INVALID_IMAGE ){};

	InvalidImage( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};



};

};


#endif // _VCF_INVALIDIMAGE_H__

/**
$Id$
*/
