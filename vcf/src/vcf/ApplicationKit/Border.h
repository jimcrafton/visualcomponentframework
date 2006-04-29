#ifndef _VCF_BORDER_H__
#define _VCF_BORDER_H__
//Border.h

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



#define BORDER_CLASSID		"3126B221-2819-11d4-B53A-00C04F0196DA"

/**
\class Border Border.h "vcf/ApplicationKit/Border.h"
A Border component is responsible for drawing the border of a control.
The border is used to produce effects like a 3D border or bevel, or
a border with a text/caption area. How this is made to look is entirely 
up to the implementer of the component. 
\p
In addition to painting the control's border, the Border instance is also 
responsible for correctly calculating the effect the border would have on a 
rectangle bounds. The getClientRect() method is used to determine, given
an initial set of rectangular bounds, what effect (if any) the presence 
of the border would have on the initial bounds, and adjusting it if neccessary.
For example, a border that paints an edge 2 pixels thick, would adjust the
initial bounds by reducing it's width and height by 2 pixels on either side
by calling the rect's inflate( -2, -2 ) method.
\p
Since a Border is derived from a Component, the owning component
will clean up any memory for the component.
*/
class APPLICATIONKIT_API Border : public Component {
public:


	Border() {}
	Border( Component* owner ) : Component(owner) {}

	virtual ~Border(){};

	/**
	Draw the border, using the passed in context to draw on. The
	control argument may be used for specific purposes, but typically
	it's just used to get the initial bounds for the border to draw within.
	*/
	virtual void paint( Control* control, GraphicsContext* context ) = 0;

	/**
	paints a border in the given bounds on the context
	@param Rect the rectangle that makes up the outer most region
	of the border
	@param GraphicsContext the context on which to paint the border
	*/
	virtual void paint( Rect* bounds, GraphicsContext* context ) = 0;

	/**
	\p
	Returns a client rect in which contained components may live.
	Thus if a particular implementation required a 3 pixel
	border at the edges to draw itself, then it would retrieve the
	component's border and then reduce it by 3 pixels. This new
	value is the available area that the component could use to
	place child components
	
	@param Rect* - the initial bounds to calculate a new client rectangle
	from.
	@param Control* - a control that may provide additional information
	
	@return Rect the new (possibly adjusted) client rectangle
	*/
	virtual Rect getClientRect( Rect* initialBounds, Control* control ) = 0;

};

};


#endif // _VCF_BORDER_H__

/**
$Id$
*/
