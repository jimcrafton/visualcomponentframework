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

\par
If the assert fails (i.e. in this if p1 equals 0) the message will look something like 
\code
	p1 > 0
	Assertion in file: foo.cpp at line: 200

\endcode

\par
Many thanks to Marcello for contributing this!!
@see VCF_ASSERT2
*/
	#define VCF_ASSERT(condition) VCF_ASSERT2( (condition), VCF_WIDEN( #condition ) )


#else
	#define VCF_ASSERT2(condition,msg)
	#define VCF_ASSERT(condition)
#endif //_DEBUG


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.2  2005/03/15 17:35:42  marcelloptr
*VCF_ASSERT2 fixed so to evaluate the condition only once
*
*Revision 1.4.2.1  2005/01/17 22:45:37  augusto_roman
*ErrorStrings - Fixed VCF namespace in VCF_ASSERT
*ItemEvent - Added item unselected event
*TreeListControl:
*- Added handling for sending unselected event
*- Added correct state drawing for checked/unchecked items
*
*Revision 1.4  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.2  2004/11/10 02:04:39  marcelloptr
*minor fix on MAKE_ERROR_MSG so it can be used inside any header files
*
*Revision 1.3.2.1  2004/08/23 22:26:06  marcelloptr
*added NotImplementedException
*
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/05 20:05:36  marcelloptr
*other adjustment on the assert macro for better performance with Unicode
*
*Revision 1.1.2.3  2004/06/25 20:00:52  marcelloptr
*adjusted macros and other changes for better performance with Unicode
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.12.2.2  2004/04/26 21:58:38  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12.2.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.12  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.10.2.1  2004/01/17 06:09:49  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.10.2.4  2004/03/26 01:37:39  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.10.2.3  2004/02/21 03:27:06  ddiego
*updates for OSX porting
*
*Revision 1.10.2.2  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.10.2.1  2004/01/17 06:09:49  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*/


#endif // _VCF_ERRORSTRINGS_H__


