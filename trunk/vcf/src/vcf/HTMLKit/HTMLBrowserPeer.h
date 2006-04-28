#ifndef _VCF_HTMLBROWSERPEER_H__
#define _VCF_HTMLBROWSERPEER_H__
//HTMLBrowserPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_HTMLDOMELEMENTS_H__
#include "vcf/HTMLKit/HTMLDOMElements.h"
#endif


namespace VCF  {

/**
\class HTMLBrowserPeer HTMLBrowserPeer.h "vcf/HTMLKit/HTMLBrowserPeer.h"
*HTMLBrowserPeer describes
*a generic interface for a browser control.
*Since browsers have become so common, as well as useful,
*it has been added to the set of peers for the ApplicationKit.
*/
class HTMLKIT_API HTMLBrowserPeer : public VCF::Interface {
public:
	virtual ~HTMLBrowserPeer(){};

	virtual String getCurrentURL() = 0;

	virtual void setCurrentURL( const String& url ) = 0;

	virtual void goBack() = 0;

	virtual void goForward() = 0;

	virtual void goHome() = 0;

	virtual void refresh() = 0;

	virtual bool isLoadingURL() = 0;

	virtual void stopLoadingURL() = 0;

	virtual void setFromHTML( const String& html ) = 0;

	virtual String getTitle() = 0;

	virtual void edit( const bool& val ) = 0;

	virtual void copy() = 0;

	virtual void selectAll() = 0;

	virtual void setAllowsPopupWindows( bool val ) = 0;

	virtual void setAllowsScrollbars( bool val ) = 0;

	virtual void setAllowsTextSelection( bool val ) = 0;

	virtual String getElementHTMLText( const String& elementName ) = 0;

	virtual void setElementHTMLText( const String& elementName, const String& html ) = 0;

	virtual String getElementText( const String& elementName ) = 0;

	virtual void setElementText( const String& elementName, const String& text ) = 0;

	virtual String getActiveElementID() = 0;

	virtual String getElementIDFromPoint( Point* pt ) = 0;

	virtual bool setElementClickedEventHandler( const String& elementName, EventHandler* handler ) = 0;

	virtual HTMLDocument getDocument() = 0;
};


}; //end of namespace VCF


#endif // _VCF_HTMLBROWSERPEER_H__

/**
$Id$
*/
