#ifndef _VCF_THEMEBORDER_H__
#define _VCF_THEMEBORDER_H__
//ThemeBorder.h

/*
Copyright 2000-2009 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/GraphicsKit/DrawUIState.h"


namespace VCF {


#define THEMEBORDER_CLASSID			"9BC38CBF-6A12-4F5D-85ED-2C5A0AC76019"

/**
\class ThemeBorder ThemeBorder.h "vcf/ApplicationKit/ThemeBorder.h"
*Draws a native theme compliant border around a component.
*
*@version 1.0
*@author Jim Crafton
*/
class APPLICATIONKIT_API ThemeBorder : public Border {

public:

	ThemeBorder():elementType_(etControl){};	

	ThemeBorder( Component* owner ):Border(owner),elementType_(etControl){};

	ThemeBorder( Component* owner, UIElementType val ):Border(owner),elementType_(val){};

	virtual ~ThemeBorder(){}

	/**
	*Paint the border on context
	*/
	virtual void paint( Control* control, GraphicsContext* context ) {
		Rect bounds = control->getClientBounds(false);
		
		if ( !bounds.isEmpty() ) {
			paint( &bounds, context );
		}
	}

	virtual void paint( Rect* bounds, GraphicsContext* context ) {
		if ( NULL != bounds ){
			DrawUIState state;
			state.setType(elementType_);
			context->drawThemeBorder( bounds, state );
		}
	}

	virtual Rect getClientRect( Rect* initialBounds, Control* control ) {
		Rect result = *initialBounds;

		result.inflate( -1.0, -1.0 );

		return result;
	}

	void setElementType( UIElementType val ) {
		elementType_ = val;
	}
protected:
	UIElementType elementType_;
};

};


#endif // _VCF_THEMEBORDER_H__

/**
$Id$
*/
