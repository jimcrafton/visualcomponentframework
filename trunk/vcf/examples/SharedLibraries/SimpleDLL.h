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



#endif // _VCF_SIMPLEDLL_H__

/**
$Id$
*/
