//SketchModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "SketchModel.h"

using namespace VCF;


SketchModel::SketchModel()
{

}

SketchModel::~SketchModel()
{
	deleteShapes();
}
/*
void SketchModel::initNew()
{

}

bool SketchModel::saveAsType( const String& fileType, OutputStream& stream )
{
	return false;
}


bool SketchModel::openFromType( const String& fileType, InputStream& stream )
{
	return false;
}
*/

void SketchModel::empty()
{
	deleteShapes();
	Model::empty();
}

void SketchModel::addShape( Shape& shape )
{
	shapes_.push_back( new Shape(shape) );

//	setModified( true );

	ModelEvent e( this, Model::MODEL_CHANGED );
	ModelChanged( &e );

	updateAllViews();
}

void SketchModel::setSelectedShape( Shape* shape )
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

void SketchModel::deleteShapes()
{
	std::vector<Shape*>::iterator it = shapes_.begin();
	while ( it != shapes_.end() ) {
		delete *it;
		it ++;
	}
	shapes_.clear();
}

void SketchModel::addSelectedShape( Shape* shape )
{
	if ( NULL != shape ) {
		std::vector<Shape*>::iterator found = std::find( shapes_.begin(), shapes_.end(), shape );
		if ( found != shapes_.end() ) {
			selectedShapes_.push_back( shape );
			updateAllViews();
		}
	}
}

void SketchModel::removeSelectedShape( Shape* shape )
{
	if ( NULL != shape ) {
		std::vector<Shape*>::iterator found = std::find( selectedShapes_.begin(), selectedShapes_.end(), shape );
		if ( found != selectedShapes_.end() ) {
			selectedShapes_.erase( found );
			updateAllViews();
		}
	}
}

void SketchModel::removeShape( Shape* shape )
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

Shape* SketchModel::getSelectedShape()
{
	Shape* result = NULL;

	if ( selectedShapes_.size() == 1 ) {
		result = selectedShapes_[0];
	}

	return result;
}


/**
$Id: SketchModel.cpp 3184 2007-09-17 02:26:00Z ddiego $
*/
