#ifndef _VCF_BASIC3DBORDER_H__
#define _VCF_BASIC3DBORDER_H__
//Basic3DBorder.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{


#define BASIC3DBORDER_CLASSID			"3126B222-2819-11d4-B53A-00C04F0196DA"

/**
\class Basic3DBorder Basic3DBorder.h "vcf/ApplicationKit/Basic3DBorder.h"
*Draws a basic 3D border around a component. The border is 2 pixels thick
*
*@version 1.0
*@author Jim Crafton
*/
class APPLICATIONKIT_API Basic3DBorder : public Border {

public:


	Basic3DBorder();

	Basic3DBorder( bool inverted );

	Basic3DBorder( Component* owner );

	virtual ~Basic3DBorder();

	/**
	*Paint the border on context
	*/
	virtual void paint( Control* control, GraphicsContext* context );

	virtual void paint( Rect* bounds, GraphicsContext* context );

	virtual Rect getClientRect( Rect* initialBounds, Control* control );

	void setInverted( const bool& inverted ) {
		inverted_ = inverted;
	}

	bool isInverted() {
		return inverted_;
	}

protected:
	bool inverted_;
};

};


#endif // _VCF_BASIC3DBORDER_H__

/**
$Id$
*/
