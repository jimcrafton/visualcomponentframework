//Light3DBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Light3DBorder.h
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;
Light3DBorder::Light3DBorder():
	inverted_(false)
{
	
}

Light3DBorder::Light3DBorder( bool inverted ):
	inverted_(inverted)
{

}

Light3DBorder::Light3DBorder( Component* owner ):
	Border( owner ),
	inverted_(false)
{

}

Light3DBorder::~Light3DBorder()
{

}

void Light3DBorder::paint( Control* control, GraphicsContext* context )
{
	if ( NULL == control ){
		//throw exception
	}
	Rect bounds = control->getClientBounds(false);
	if ( !bounds.isEmpty() ){
		paint( &bounds, context );
	}
}

void Light3DBorder::paint( Rect* bounds, GraphicsContext* context )
{
	if ( NULL != bounds ){

		Color* shadow = NULL;
		if ( true == inverted_ ){
			shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
		}
		else {
			shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
		}

		Color* hilight = NULL;
		if ( true == inverted_ ){
			hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
		}
		else {
			hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
		}

		Color* face = NULL;
		face = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		
		context->rectangle( bounds );
		context->setColor( face );
		context->fillPath();

		context->moveTo( bounds->left_+1, bounds->bottom_-2 );
		context->lineTo( bounds->left_+1, bounds->top_+1 );
		context->lineTo( bounds->right_-2, bounds->top_+1 );

		context->setColor( hilight );
		context->strokePath();

		context->moveTo( bounds->right_-2, bounds->top_+1 );
		context->lineTo( bounds->right_-2, bounds->bottom_-2 );
		context->lineTo( bounds->left_+1, bounds->bottom_-2 );

		context->setColor( shadow );
		context->strokePath();
	}
}

Rect Light3DBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;

	result.inflate( -2.0, -2.0 );

	return result;
}


/**
$Id$
*/
