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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_INVALIDIMAGE_H__


