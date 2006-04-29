#ifndef _VCF_NOPEERFOUNDEXCEPTION_H__
#define _VCF_NOPEERFOUNDEXCEPTION_H__
//NoPeerFoundException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class FOUNDATIONKIT_API NoPeerFoundException : public BasicException {
public:
	NoPeerFoundException( const String & message ):
	  BasicException( message ){};

	NoPeerFoundException():
		BasicException( NO_PEER ){};

	NoPeerFoundException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~NoPeerFoundException() throw() {};
};

};


#endif // _VCF_NOPEERFOUNDEXCEPTION_H__

/**
$Id$
*/
