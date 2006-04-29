#ifndef _VCF_THREADEXCEPTION_H__
#define _VCF_THREADEXCEPTION_H__
//ThreadException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class FOUNDATIONKIT_API ThreadException : public VCF::BasicException {
public:

    ThreadException(const String & message ):
		BasicException( message ){

	};


	ThreadException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~ThreadException() throw() {};
};

};


#endif // _VCF_THREADEXCEPTION_H__

/**
$Id$
*/
