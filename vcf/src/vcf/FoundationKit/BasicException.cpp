//BasicException.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include <vcf/FoundationKit/FoundationKit.h>
using namespace VCF;


BasicException::BasicException(const String & message)
{
	message_ = message;
	//JC - I commented this out - I am not sure want to FORCE 
	//this kind of output? It can clutter up the command line.
	//System::println( "Exception: " + message_ );
}

BasicException::BasicException( const VCF::String & message, const int lineNumber )
{
	message_ = message;
#ifdef _DEBUG
	char txt[256];
	sprintf( txt, "\nerror at line number %d", lineNumber );
	message_ += txt;
#endif

	//JC - I commented this out - I am not sure want to FORCE 
	//this kind of output? It can clutter up the command line.
	//System::println( "Exception: " + message_ );
	
}

String BasicException::getMessage()
{
	return message_;
}

void BasicException::setMessage( const VCF::String& message )
{
	message_ = message;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:15:01  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.3.2.1  2005/03/15 01:51:51  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/17 04:52:49  ddiego
*added some minor fixes to win32 resource loading, and added 2 new examples that demonstrate basic resource loading and basic usage of dialogs.
*
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:05  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


