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

	virtual bool containsPoint( Point * pt );

    virtual uint32 getIndex();

	virtual void setIndex( const uint32& index );

    virtual void* getData();

	virtual void setData( void* data );
	
	virtual void setPageName( const String& name );

	virtual String getPageName();

	virtual Control* getPageComponent();

	virtual void setPageComponent( Control* component );

	virtual bool isSelected();

	virtual void setSelected( const bool& selected );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual uint32 getPreferredHeight();

	virtual Rect* getBounds() {
		return &bounds_;
	}

	virtual Control* getControl() {
		return owningControl_;
	}


	virtual void setControl( Control* control ) {
		owningControl_ = control;
	}

	virtual int32 getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const int32& imageIndex );

	virtual bool canPaint() {
		return true;
	}
	
	virtual void setBounds( Rect* bounds );

	/**
	*not supported
	*/
	virtual int32 getStateImageIndex(){
		return -1;
	};

	/**
	*not supported
	*/
	virtual void setStateImageIndex( const int32& index ){}

private:
	uint32 index_;
	String pageName_;
	Control* component_;
	bool selected_;
	uint32 preferredHeight_;
	Rect bounds_;
	int32 imageIndex_;
	void* data_;
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABPAGE_H__

/**
$Id$
*/
