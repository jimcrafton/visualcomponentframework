//SketchDocument.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "../examples/SketchIt/SketchDocument.h"

using namespace VCF;


SketchDocument::SketchDocument()
{
	shapesContainer_.initContainer( shapes_ );
	selectedShapesContainer_.initContainer( selectedShapes_ );
}

SketchDocument::~SketchDocument()
{
	deleteShapes();
}

void SketchDocument::initNew()
{

}

bool SketchDocument::saveAsType( const String& fileType, OutputStream& stream )
{
	return false;
}


bool SketchDocument::openFromType( const String& fileType, InputStream& stream )
{
	return false;
}


void SketchDocument::empty()
{
	deleteShapes();
	Document::empty();
}

void SketchDocument::addShape( Shape& shape )
{
	shapes_.push_back( new Shape(shape) );

	setModified( true );

	ModelEvent e( this, Model::MODEL_CHANGED );
	ModelChanged.fireEvent( &e );

	updateAllViews();
}

void SketchDocument::setSelectedShape( Shape* shape )
{
	if ( (selectedShapes_.size() == 1) && (selectedShapes_[0] == shape) ) {
		return;
	}


	selectedShapes_.clear();

	if ( NULL != shape ) {
		std::vector<Shape*>::iterator found = std::find( shapes_.begin(), shapes_.end(), shape );
		if ( found != shapes_.end() ) {
			selectedShapes_.push_back( shape );
		}
	}
	updateAllViews();
}

void SketchDocument::deleteShapes()
{
	std::vector<Shape*>::iterator it = shapes_.begin();
	while ( it != shapes_.end() ) {
		delete *it;
		it ++;
	}
	shapes_.clear();
}

void SketchDocument::addSelectedShape( Shape* shape )
{
	if ( NULL != shape ) {
		std::vector<Shape*>::iterator found = std::find( shapes_.begin(), shapes_.end(), shape );
		if ( found != shapes_.end() ) {
			selectedShapes_.push_back( shape );
			updateAllViews();
		}
	}
}

void SketchDocument::removeSelectedShape( Shape* shape )
{
	if ( NULL != shape ) {
		std::vector<Shape*>::iterator found = std::find( selectedShapes_.begin(), selectedShapes_.end(), shape );
		if ( found != selectedShapes_.end() ) {
			selectedShapes_.erase( found );
			updateAllViews();
		}
	}
}

void SketchDocument::removeShape( Shape* shape )
{
	if ( NULL != shape ) {
		std::vector<Shape*>::iterator found = std::find( selectedShapes_.begin(), selectedShapes_.end(), shape );
		if ( found != selectedShapes_.end() ) {
			selectedShapes_.erase( found );
		}

		found = std::find( shapes_.begin(), shapes_.end(), shape );
		if ( found != shapes_.end() ) {
			shapes_.erase( found );
			updateAllViews();
		}
	}
}

Shape* SketchDocument::getSelectedShape()
{
	Shape* result = NULL;

	if ( selectedShapes_.size() == 1 ) {
		result = selectedShapes_[0];
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.6.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


