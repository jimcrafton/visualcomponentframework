#ifndef _VCF_RESOURCEEXCEPTION_H__
#define _VCF_RESOURCEEXCEPTION_H__
//ResourceException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class FOUNDATIONKIT_API ResourceException : public RuntimeException{

public:
	ResourceException( const VCF::String & message ):
		RuntimeException( message ){

	};

	ResourceException():
		RuntimeException( RUNTIME_ERROR ){

	};

	ResourceException( const VCF::String & message, const int lineNumber ):
		VCF::RuntimeException(message, lineNumber){};

	virtual ~ResourceException() throw() {};

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:38  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.6.3  2003/10/04 20:14:59  ddiego
*aaddec changes to support compiling on GCC 3.3.1, which is much more
*picky than some of the previous versions.
*
*Revision 1.4.6.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*/


#endif // _VCF_RESOURCEEXCEPTION_H__


