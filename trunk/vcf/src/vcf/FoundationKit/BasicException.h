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
    VCF::String getMessage() const;


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


#endif // _VCF_BASICEXCEPTION_H__

/**
$Id$
*/
