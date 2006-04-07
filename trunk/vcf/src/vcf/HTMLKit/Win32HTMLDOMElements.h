#ifndef _VCF_WIN32HTMLDOMELEMENTS_H__
#define _VCF_WIN32HTMLDOMELEMENTS_H__

//Win32HTMLDOMElements.h

#if _MSC_VER > 1000
#   pragma once
#endif

#include <exdisp.h>		// Defines of stuff like IWebBrowser2. This is an include file with Visual C 6 and above
#include <mshtml.h>		// Defines of stuff like IHTMLDocument2. This is an include file with Visual C 6 and above
#include <mshtmhst.h>	// Defines of stuff like IDocHostUIHandler. This is an include file with Visual C 6 and above

#include "thirdparty/win32/comet/threading.h"
#include "thirdparty/win32/comet/uuid.h"
#include "thirdparty/win32/comet/bstr.h"
#include "thirdparty/win32/comet/safearray.h"
#include "vcf/ApplicationKit/Win32HResult.h"


#define COM_PTR(ifc) \
namespace comet { \
template<> struct comtype<ifc> { \
	static const IID& uuid() { \
        static const IID iid = IID_##ifc; \
        return iid; \
	} \
    typedef nil base;\
};\
};\
typedef comet::com_ptr<ifc> ifc##Ptr;\
\


COM_PTR(IHTMLDocument2)
COM_PTR(IHTMLElement)
COM_PTR(IHTMLElementCollection)
COM_PTR(IWebBrowser2)






using namespace comet;

namespace VCF {
	
	class HTMLElementCollectionPeer : public IHTMLElementCollectionPtr {
	public:
		HTMLElementCollectionPeer():IHTMLElementCollectionPtr(){}

		template<typename Itf>
		HTMLElementCollectionPeer( const impl::com_cast_t<Itf>& x ) throw () : IHTMLElementCollectionPtr(x) {}	
	};
	
	class HTMLElementPeer : public IHTMLElementPtr {
	public:
		HTMLElementPeer():IHTMLElementPtr(){}

		template<typename Itf>
		HTMLElementPeer( const impl::com_cast_t<Itf>& x ) throw () : IHTMLElementPtr(x) {}

	};
	
	
	class HTMLDocumentPeer : public IHTMLDocument2Ptr {
	public:
		HTMLDocumentPeer():IHTMLDocument2Ptr(){}

		template<typename Itf>
		HTMLDocumentPeer( const impl::com_cast_t<Itf>& x ) throw () : IHTMLDocument2Ptr(x) {}
	};
	
};





#endif //_VCF_WIN32HTMLDOMELEMENTS_H__
