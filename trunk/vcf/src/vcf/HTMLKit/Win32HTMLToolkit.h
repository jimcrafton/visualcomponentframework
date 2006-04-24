#ifndef _VCF_WIN32HTMLTOOLKIT_H__
#define _VCF_WIN32HTMLTOOLKIT_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class HTMLKIT_API Win32HTMLToolkit : public HTMLToolkit {
public:	
	Win32HTMLToolkit();

	virtual ~Win32HTMLToolkit();
protected:
	virtual HTMLBrowserPeer* internal_createHTMLBrowserPeer( Control* control );
};

}


#endif //_VCF_WIN32HTMLTOOLKIT_H__