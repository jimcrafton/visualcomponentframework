#ifndef _VCF_SIMPLEDLL_H__
#define _VCF_SIMPLEDLL_H__
//SimpleDLL.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifdef _MSC_VER
#define SIMPLEDLL_API	__declspec(dllexport)
#else
#define SIMPLEDLL_API
#endif


class SIMPLEDLL_API HelloWorld {
public:
	 HelloWorld(){};
		virtual ~HelloWorld(){};
	void hello();

};

extern "C" {
	SIMPLEDLL_API int getAnInteger( int val1, double d );

}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.3  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_SIMPLEDLL_H__


