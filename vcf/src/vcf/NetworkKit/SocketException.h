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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/04 15:21:11  thrysoee
*Fix gcc error "looser throw specifier"
*This error occurs when a method in a derived class has a different throw specifier.
*http://www.agapow.net/programming/looser_throw_specifier.html
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:48  ddiego
*migration towards new directory structure
*
*Revision 1.5.10.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SOCKETEXCEPTION_H__


