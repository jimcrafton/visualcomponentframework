#ifndef _XMAKE_WARNINGS_OFF_H
#define _XMAKE_WARNINGS_OFF_H
//xmake_warnings_off.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#ifdef _MSC_VER


/*
	warning C4018: '<=' : signed/unsigned mismatch
	Comparing a signed and unsigned number required the compiler to convert the signed value to unsigned.
*/
//#pragma warning ( disable : 4018 )


/*
	warning C4503: 'identifier' : decorated name length exceeded, name was truncated
	The decorated name was longer than the compiler limit (247), and was truncated.
*/
#pragma warning ( disable : 4503 )


/* 
	warning C4786: 'blah' : identifier was truncated to '255' characters in the debug information
	The debugger cannot debug code with symbols longer than 255 characters. In the debugger, you cannot view, evaluate, update, or watch the truncated symbols.
	This is really a dumb warning....
*/
#pragma warning ( disable : 4786 )



#endif // _MSC_VER


#endif // _XMAKE_WARNINGS_OFF_H


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:18  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2004/12/21 01:25:17  marcelloptr
*added cvs log section
*
*/


