#ifndef _VCF_SOCKETEXCEPTION_H__
#define _VCF_SOCKETEXCEPTION_H__
//SocketException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define SOCKET_EXCEPTION		"Generic Socket error"

class SocketException : public VCF::BasicException{

public:
	SocketException():
		VCF::BasicException( SOCKET_EXCEPTION ){};

	SocketException( const VCF::String & message ):
		VCF::BasicException( message ){};

	virtual ~SocketException() throw() {};

};

}; //end of namespace VCF


#endif // _VCF_SOCKETEXCEPTION_H__

/**
$Id$
*/
