#ifndef _VCF_DEFAULTTABPAGE_H__
#define _VCF_DEFAULTTABPAGE_H__
//DefaultTabPage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/TabPage.h"


namespace VCF {

#define DEFAULTTABPAGE_CLASSID	"86F02173-3E7F-11d4-8EA7-00207811CFAB"

/**
\class DefaultTabPage DefaultTabPage.h "vcf/ApplicationKit/DefaultTabPage.h"
*/
class APPLICATIONKIT_API DefaultTabPage : public TabPage {
public:

	DefaultTabPage( Control* component=NULL );

	virtual ~DefaultTabPage();

    virtual uint32 getIndex() const ;

	virtual void setIndex( const uint32& index );

    
	virtual void setPageName( const String& name );

	virtual String getPageName();

	virtual Control* getPageComponent();

	virtual void setPageComponent( Control* component );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual uint32 getPreferredHeight();
	
	virtual bool canPaint() {
		return true;
	}
	
	

	

private:	
	String pageName_;
	Control* component_;	
	uint32 preferredHeight_;
	uint32 index_;
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABPAGE_H__

/**
$Id$
*/
