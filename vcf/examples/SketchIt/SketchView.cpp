//SketchView.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "../examples/SketchIt/SketchView.h"
#include "../examples/SketchIt/SketchDocument.h"
#include "../examples/SketchIt/SketchTools.h"



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


	SketchDocument* doc = (SketchDocument*)getViewModel();

	BasicStroke bs;
	BasicFill bf;
	ctx->setCurrentStroke( &bs );

	Rect viewBounds = ctx->getViewableBounds();


	Enumerator<Shape*>* shapes = doc->getShapes();
	while ( shapes->hasMoreElements() ) {
		Shape* shape = shapes->nextElement();

		bs.setColor( &shape->strokeColor_ );
		bs.setOpacity( shape->opacity_ );
		bs.setWidth( shape->width_ );

		if ( shape->fill_ ) {
			bf.setColor( shape->fillColor_ );
			bf.setOpacity( shape->opacity_ );
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
*CVS Log info
*$Log$
*Revision 1.5  2004/12/01 04:15:13  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.4.2.1  2004/09/15 04:25:51  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.4  2004/08/07 02:47:37  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.4.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


