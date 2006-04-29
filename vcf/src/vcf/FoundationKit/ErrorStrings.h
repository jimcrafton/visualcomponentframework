#ifndef _VCF_ERRORSTRINGS_H__
#define _VCF_ERRORSTRINGS_H__
//ErrorStrings.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// the VCF namespace must be explicitely specified in this macro so it can be used inside any header file.
#ifdef _DEBUG
#define MAKE_ERROR_MSG(message)       VCF::String(message) +	VCF::String(L"\nException in file: ") + VCF::String( __FILE__ )
#define MAKE_ERROR_MSG_2(message)     VCF::String(message) +	VCF::String(L"\nException in file: ") + VCF::String( __FILE__ ) + VCF::String(" at line: ") + VCF::StringUtils::toString(__LINE__)
#else
#define MAKE_ERROR_MSG(message)       VCF::String(message)
#define MAKE_ERROR_MSG_2(message)     VCF::String(message)
#endif


namespace VCF
{

#define APPLICATION_EXCEPTION         L"Application error."
#define BAD_COMPONENTSTATE_EXCEPTION  L"The component is in an invalid state."
#define BAD_IMAGE_BITS_EXCEPTION      L"The image's pixel bits are corrupt or the pointer to them is referencing bad memory."
#define BAD_ITEMSTATE_EXCEPTION       L"The item is in an invalid state."
#define BAD_MODEL_STATE_EXCEPTION     L"The model's is corrupt or incorrect."
#define CLASS_NOT_FOUND               L"Requested class not found in the Framework Class Registry."
#define CANT_GET_INTERFACE_ERROR      L"Error retreiving interface. COM can't find or can't instantiate the requested Interface."
#define NO_FREE_MEMORY_AVALIABLE      L"No more memory is available on the heap for this process."
#define NO_GFX_TOOLKIT_ERROR          L"Error in VCF Framework: No Graphics toolkit found."
#define NO_PEER                       L"Attempt to use an invalid Peer."
#define NO_SUCH_ELEMENT_FOUND         L"No corresponding element can be found with the index specified."
#define NO_TOOLKIT_ERROR              L"Error in VCF Framework: No toolkit found."
#define NOT_IMPLEMENTED_EXCEPTION     L"Not implemented yet."
#define INVALID_POINTER_ERROR         L"Invalid pointer found. The pointer is either null or pointing to bad memory."
#define OUT_OF_BOUNDS_EXCEPTION       L"The requested index is outside of the coleections bounds."


#define INVALID_IMAGE                 L"This is image is invalid."

#define CANT_ACCESS_FILE              L"Error attempting to access file: "
#define CANT_WRITE_TO_FILE            L"Error attempting to write to file: "
#define PROPERTY_CHANGE_BAD           L"The requested value(s) cannot be set on the given object."

#define RUNTIME_ERROR                 L"A System runtime exception has occurred. Doh - you probably already knew that !"



#define BAD_DAY_VALUE                 L"Day Value is out of range (either less than 1 or greater than 31)"
#define BAD_MONTH_VALUE               L"Month Value is out of range (either less than 1 or greater than 12)"
#define BAD_HOUR_VALUE                L"Hour Value is out of range (either less than 0 or greater than 59)"
#define BAD_MIN_VALUE                 L"Minute Value is out of range (either less than 0 or greater than 59)"
#define BAD_SEC_VALUE                 L"Second Value is out of range (either less than 0 or greater than 59)"
#define BAD_MILLISEC_VALUE            L"Millisecond Value is out of range (either less than 0 or greater than 999)"



// macros mainly introduced to have the __FILE__ macro to return a unicode literal
#define VCF_WIDEN2(x) L ## x
#define VCF_WIDEN(x)  VCF_WIDEN2(x)
#define __WFILE__     VCF_WIDEN( __FILE__ )

};



#ifdef _DEBUG

/**
This macro takes 2 arguments - the condition that causes the
assert, and a string describing the reason for the assert.
*/
	#define VCF_ASSERT2(condition,msg) \
		{ \
			bool condValue = condition; \
			if ( ! (condValue) ) { \
				VCF::FoundationKit::assertCondition( condValue, VCF::String( msg ) + VCF::String( L"\nAssertion in file: " ) + VCF::String( __WFILE__ ) + VCF::String( L" at line: " ) + VCF::StringUtils::toString( __LINE__ ) ); \
			} \
		} \
		\

/**
Instead of calling FoundationKit::assertCondition() use this macro or VCF_ASSERT2.
Use this macro to assert if a certain condtion is false, which will cause an exception to
be thrown. For example:
\code
int doCalc( int p1, int p2 ) 
{
	VCF_ASSERT( p1 > 0 );
	
	return p2 / p1;
}
\endcode


If the assert fails (i.e. in this if p1 equals 0) the message will look something like 
\code
	p1 > 0
	Assertion in file: foo.cpp at line: 200

\endcode


Many thanks to Marcello for contributing this!!
@see VCF_ASSERT2
*/
	#define VCF_ASSERT(condition) VCF_ASSERT2( (condition), VCF_WIDEN( #condition ) )
	#define VCF_VERIFY(condition) VCF_ASSERT(condition)

#else
	#define VCF_ASSERT2(condition,msg)
	#define VCF_ASSERT(condition)
	#define VCF_VERIFY(condition) condition
#endif //_DEBUG


#endif // _VCF_ERRORSTRINGS_H__

/**
$Id$
*/
