//SketchView.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "SketchView.h"
#include "SketchModel.h"
#include "SketchTools.h"



//#include "vcf/GraphicsKit/AggCommon.h"



using namespace VCF;


SketchView::SketchView()
{

}

SketchView::~SketchView()
{

}


class ColorAlpha {
public:
	int alphaValue_;

	int calculate(int alpha, int c, int, int, int) const {
		return alphaValue_;
	}
};

void SketchView::paintView( GraphicsContext* ctx )
{
	ctx->setColor( Color::getColor( "white" ) );

	Rect clientBounds = getViewControl()->getClientBounds();
	ctx->rectangle( clientBounds );
	ctx->fillPath();


	SketchModel* model = (SketchModel*)getViewModel();

	BasicStroke bs;
	BasicFill bf;
	ctx->setCurrentStroke( &bs );

	Rect viewBounds = ctx->getViewableBounds();


	Enumerator<Shape*>* shapes = model->getShapes();
	while ( shapes->hasMoreElements() ) {
		Shape* shape = shapes->nextElement();

		bs.setColor( &shape->strokeColor_ );
		bs.setWidth( shape->width_ );

		if ( shape->fill_ ) {
			bf.setColor( &shape->fillColor_ );
			ctx->setCurrentFill( &bf );
		}
		else {
			ctx->setCurrentFill( NULL );
		}

		ctx->draw( &shape->polygon_ );

		if ( NULL != shape->image_ ) {
			Rect bounds = shape->polygon_.getBounds();

			ctx->drawImage( bounds.left_, bounds.top_, shape->image_ );
			
		}
	}

	ctx->setCurrentStroke( NULL );
	ctx->setCurrentFill( NULL );

	Tool* tool = ToolManager::getToolManager()->getCurrentTool();

	if ( NULL != tool ) {
		tool->paintState( ctx );
	}

}


/**
$Id$
*/
