#ifndef _VCF_TABPAGE_H__
#define _VCF_TABPAGE_H__
//TabPage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define TABPAGE_CLASSID		"86F02172-3E7F-11d4-8EA7-00207811CFAB"

/**
\class TabPage TabPage.h "vcf/ApplicationKit/TabPage.h"
*/
class APPLICATIONKIT_API TabPage : public Item {
public:

	TabPage(){

	};

	virtual ~TabPage(){};

	virtual void setPageName( const String& name ) = 0;

	virtual String getPageName() = 0;

	virtual Control* getPageComponent() = 0;

	virtual void setPageComponent( Control* component ) = 0;

	virtual uint32 getPreferredHeight() = 0;

	virtual uint32 getIndex() const  = 0;

	virtual void setIndex( const uint32& index ) = 0;
};

}; //end of namespace VCF


#endif // _VCF_TABPAGE_H__

/**
$Id$
*/
