#ifndef _VCF_INVALIDSTATEEXCEPTION_H__
#define _VCF_INVALIDSTATEEXCEPTION_H__
//InvalidStateException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class APPLICATIONKIT_API InvalidStateException : public BasicException {
public:
	InvalidStateException(const VCF::String & message ):
		BasicException( message ){

	};

	InvalidStateException():
		BasicException( BAD_ITEMSTATE_EXCEPTION ){

	};

	InvalidStateException( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};



};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_INVALIDSTATEEXCEPTION_H__


