#ifndef _VCF_HTMLTOOLKIT_H__
#define _VCF_HTMLTOOLKIT_H__
//HTMLToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Control;
class HTMLBrowserPeer;

/**
\class HTMLToolkit HTMLToolkit.h "vcf/HTMLKit/HTMLToolkit.h"
*/
class HTMLKIT_API HTMLToolkit {
public:	
	virtual ~HTMLToolkit(){};

	static void create();
	static void destroy();

	static HTMLBrowserPeer* createHTMLBrowserPeer( Control* control );
protected:
	static HTMLToolkit* toolkitInstance;
	virtual HTMLBrowserPeer* internal_createHTMLBrowserPeer( Control* control ) = 0;
};

}



#endif // _VCF_HTMLTOOLKIT_H__


