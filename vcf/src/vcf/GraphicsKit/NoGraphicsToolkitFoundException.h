#ifndef _VCF_NOGRAPHICSTOOLKITFOUNDEXCEPTION_H__
#define _VCF_NOGRAPHICSTOOLKITFOUNDEXCEPTION_H__
//NoGraphicsToolkitFoundException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class NoGraphicsToolkitFoundException : public VCF::BasicException {
public:
	NoGraphicsToolkitFoundException( const VCF::String & message ):
	  VCF::BasicException( message ){};

	NoGraphicsToolkitFoundException():
		VCF::BasicException( NO_GFX_TOOLKIT_ERROR ){};

	NoGraphicsToolkitFoundException( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};


};

};


#endif // _VCF_NOGRAPHICSTOOLKITFOUNDEXCEPTION_H__

/**
$Id$
*/
