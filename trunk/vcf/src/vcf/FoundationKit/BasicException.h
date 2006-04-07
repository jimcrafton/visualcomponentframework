#ifndef _VCF_BASICEXCEPTION_H__
#define _VCF_BASICEXCEPTION_H__
//BasicException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

/**
\class BasicException BasicException.h "vcf/FoundationKit/BasicException.h"
*The base exception class in the Framework.
*All exceptions should try and describe what went wrong as clearly as possible.
*For convenience a basic set of error strings are defined in ErrorStrings.h.
*
*@version 1.0
*@author Jim Crafton
*/
class FOUNDATIONKIT_API BasicException : public std::exception {
public:

	/**
	*Basic constructor
	*All Exceptions take a text message identifying (in human readable terms ) what
	*went wrong.
	*/
	BasicException( const VCF::String & message );

	BasicException( const VCF::String & message, const int lineNumber );

	virtual ~BasicException() throw() {} ;

	/**
	*returns the message text associated with the exception
	*@return String - the error text
	*/
    VCF::String getMessage();


	/**
	overrides the std::exception's what() method to return the same as
	getMessage() does, making this exception (and all it's derivations)
	suitable for use in try/catch blocks where the catch traps std::exception&.
	*/
	virtual const char* what() const throw() {
		return message_.ansi_c_str();
	}

	/**
	*set the error text to be associated with the exception
	* so it is possible to add informations and rethrow the same exception
	*/
	void setMessage( const VCF::String& message );

private:
    VCF::String message_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.10.2.2  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10.2.1  2004/04/21 02:17:07  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.10  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.9  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.8.2.1  2004/01/17 06:09:49  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.8.2.3  2004/03/21 00:39:22  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.8.2.2  2004/01/25 22:37:35  marcelloptr
*changes related to rethrowing exceptions
*
*Revision 1.8.2.1  2004/01/17 06:09:49  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.8  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*/


#endif // _VCF_BASICEXCEPTION_H__


