#ifndef _VCF_CIRCLE_H__
#define _VCF_CIRCLE_H__
//Circle.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF{


class GRAPHICSKIT_API Circle : public Ellipse {
public:
	Circle(){}

	virtual ~Circle(){}

	void circle( const Point& pt, const double& radius ) {		
		ellipse( Rect(pt.x_-radius,pt.y_-radius,pt.x_+radius,pt.y_+radius) );		
	}
};

};


#endif // _VCF_CIRCLE_H__

/**
$Id$
*/
