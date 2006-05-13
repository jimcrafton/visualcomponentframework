#ifndef _VCF_BASICFILL_H__
#define _VCF_BASICFILL_H__
//BasicFill.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

/**
\class BasicFill BasicFill.h "vcf/GraphicsKit/BasicFill.h"
This class is a basic implementation of the Fill interface. It is suitable for 
rendering a solid color fill with optional alpha and anti-aliasing support.
If anti-aliasing is turned on then an attempt will be made to render the
fill using <a href="http://www.antigrain.com/">AGG</a>, assuming a render
buffer for the GraphicsContext is available. Alpha support is only used if 
the rendering is performed by AGG, otherwise it is ignored.
@see Fill
*/
class GRAPHICSKIT_API BasicFill : public Object, public Fill {
public:
	BasicFill();

	virtual ~BasicFill();

	virtual void setContext( GraphicsContext* context ) {
		context_ = context;
	}

    virtual void render( Path* path );

	/**
	Gets the color for the fill
	*/
	Color getColor() {
		return color_;
	}

	/**
	Sets the color for the fill
	*/
	void setColor( Color* color ) {
		color_ = *color;
	}
	

	/**
	returns whether or not to allow antialiasing when rendering the fill
	*/
	bool allowAntiAlias() {
		return antiAlias_;
	}

	/**
	toggles whether or not to perform anti-aliasing when rendering the fill.
	*/
	void setAllowAntiAlias( bool val ) {
		antiAlias_ = val;
	}
protected:

	double opacity_;
	Color color_;
	GraphicsContext* context_;
	bool antiAlias_;
};

};


#endif // _VCF_BASICFILL_H__

/**
$Id$
*/
