//Basic3DBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


Basic3DBorder::Basic3DBorder():
	inverted_(false)
{

}

Basic3DBorder::Basic3DBorder( bool inverted ):
	inverted_(inverted)
{

}

Basic3DBorder::Basic3DBorder( Component* owner ):
	Border( owner ),
	inverted_(false)
{

}

Basic3DBorder::~Basic3DBorder()
{

}

Rect Basic3DBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;	
	
	result.inflate( -2.0, -2.0 );
	
	return result;
}

void Basic3DBorder::paint( Rect* bounds, GraphicsContext* context )
{
	if ( NULL != bounds ){

		Color* hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );

		Color* shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );

		Color* face = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );

		if ( true == inverted_ ){

			//outside left and top
			context->moveTo( bounds->left_, bounds->bottom_-2. );	
			context->lineTo( bounds->left_, bounds->top_ );
			context->lineTo( bounds->right_-1.0, bounds->top_ );
			context->setColor( shadow );		
			context->strokePath();

			//inside left and top
			context->moveTo( bounds->left_+1., bounds->bottom_-2. );	
			context->lineTo( bounds->left_+1., bounds->top_+1. );
			context->lineTo( bounds->right_-2., bounds->top_+1. );
			context->setColor( &Color(181.0,181.0,181.0) );// prob. should be 3DdarkShadow		
			context->strokePath();

			//outside bottom and right
			context->moveTo( bounds->left_, bounds->bottom_-1. );	
			context->lineTo( bounds->right_-1., bounds->bottom_-1. );
			context->lineTo( bounds->right_-1., bounds->top_-1. );
			context->setColor( hilight );		
			context->strokePath();

			//inside bottom and right
			context->moveTo( bounds->left_+1., bounds->bottom_-2. );
			context->lineTo( bounds->right_-2., bounds->bottom_-2. );
			context->lineTo( bounds->right_-2., bounds->top_ ); 
			context->setColor( face );		                   
			context->strokePath();    

		}
		else {

			//outside left and top
			context->moveTo( bounds->left_, bounds->bottom_-2. );	
			context->lineTo( bounds->left_, bounds->top_ );
			context->lineTo( bounds->right_-1.0, bounds->top_ );
			context->setColor( hilight );		
			context->strokePath();

			//inside left and top
			context->moveTo( bounds->left_+1., bounds->bottom_-2. );	
			context->lineTo( bounds->left_+1., bounds->top_+1. );
			context->lineTo( bounds->right_-2., bounds->top_+1. );
			context->setColor( face );		
			context->strokePath();

			//outside bottom and right
			context->moveTo( bounds->left_, bounds->bottom_-1. );	
			context->lineTo( bounds->right_-1., bounds->bottom_-1. );
			context->lineTo( bounds->right_-1., bounds->top_-1. );
			context->setColor( &Color(181.0,181.0,181.0) );		
			context->strokePath();

			//inside bottom and right
			context->moveTo( bounds->left_+1., bounds->bottom_-2. );
			context->lineTo( bounds->right_-2., bounds->bottom_-2. );
			context->lineTo( bounds->right_-2., bounds->top_ ); 
			context->setColor( shadow );		                   
			context->strokePath();  
			/*
			context->rectangle( bounds->left_, bounds->top_, bounds->right_, bounds->bottom_ );
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

			context->moveTo( bounds->right_-1, bounds->top_ );
			context->lineTo( bounds->right_-1, bounds->bottom_-1 );
			context->lineTo( bounds->left_, bounds->bottom_-1 );

			context->setColor( &Color(0.0,0.0,0.0) );
			context->strokePath();
			*/
		}
	}
}

void Basic3DBorder::paint( Control* component, GraphicsContext* context )
{
	if ( NULL == component ){
		//throw exception
	}
	Rect bounds = component->getClientBounds(false);

	if ( !bounds.isEmpty() ) {
		paint( &bounds, context );
	}

}


/**
$Id$
*/
