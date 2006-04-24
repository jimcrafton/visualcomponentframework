#ifndef _VCF_WIN32INTERNETTOOLKIT_H__
#define _VCF_WIN32INTERNETTOOLKIT_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {
	


	class Win32InternetToolkit : public InternetToolkit {
	public:
		Win32InternetToolkit();
		virtual ~Win32InternetToolkit();
	protected:

		virtual void internal_getDataFromURL( URL* url, OutputStream* stream ); 
	};
};

#endif //_VCF_WIN32INTERNETTOOLKIT_H__

