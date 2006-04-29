#ifndef _VCF_LIGHT3DBORDER_H__
#define _VCF_LIGHT3DBORDER_H__
//Light3DBorder.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define LIGHT3DBORDER_CLASSID		"70ec3332-f241-4f39-8383-9b1ac02945dc"


namespace VCF  {

/**
\class Light3DBorder Light3DBorder.h "vcf/ApplicationKit/Light3DBorder.h"
*Class Light3DBorder documentation
*/
class APPLICATIONKIT_API Light3DBorder : public Border {
public:

	Light3DBorder();

	Light3DBorder( bool inverted );

	Light3DBorder( Component* owner );
 
	virtual ~Light3DBorder();

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


}; //end of namespace VCF


#endif // _VCF_LIGHT3DBORDER_H__

/**
$Id$
*/
