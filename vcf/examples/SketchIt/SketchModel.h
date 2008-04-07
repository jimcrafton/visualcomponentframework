#ifndef _VCF_SKETCHMODEL_H__
#define _VCF_SKETCHMODEL_H__
//SketchModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/ModelViewKit.h"

#include "vcf/GraphicsKit/BezierCurve.h"

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"


class Shape {
public:

	Shape() :image_(NULL), fill_(false), width_(1.0) {

	}

	Shape( const Shape& rhs ) {
		*this = rhs;
	}

	Shape& operator=( const Shape& rhs ) {
		strokeColor_ = rhs.strokeColor_;
		fillColor_ = rhs.fillColor_;

		transform_ = rhs.transform_;
		polygon_ = rhs.polygon_;

		fill_ = rhs.fill_;
		width_ = rhs.width_;

		image_ = rhs.image_;

		return *this;
	}

	VCF::BezierCurve polygon_;
	VCF::Color strokeColor_;
	VCF::Color fillColor_;
	VCF::Matrix2D transform_;
	VCF::Image* image_;

	bool fill_;
	double width_;
};


/**
class SketchModel documentation
*/

#define SKETCHMODEL_CLASSID		"SketchModel-5e2698e2-bbe0-4f6f-ab6e-938f522a3c0d"

class SketchModel : public VCF::Model {
public:

	_class_rtti_( SketchModel, "VCF::Model", SKETCHMODEL_CLASSID )
	_class_rtti_end_

	SketchModel();

	virtual ~SketchModel();
/*
	virtual void initNew();

	virtual bool canCutFromDocument() {
		return true;
	}

	virtual bool canCopyFromDocument() {
		return true;
	}

	virtual bool canPasteToDocument() {
		return true;
	}

	virtual bool saveAsType( const VCF::String& fileType, VCF::OutputStream& stream );

	virtual bool openFromType( const VCF::String& fileType, VCF::InputStream& stream );
*/
	virtual void empty();

	void addShape( Shape& shape );

	void removeShape( Shape* shape ) ;

	VCF::Enumerator<Shape*>* getShapes() {
		return shapes_.getEnumerator();
	}

	void setSelectedShape( Shape* shape ) ;

	void addSelectedShape( Shape* shape ) ;

	void removeSelectedShape( Shape* shape ) ;

	Shape* getSelectedShape();

	VCF::Enumerator<Shape*>* getSelectedShapes() {
		return selectedShapes_.getEnumerator();
	}

	bool hasMultipleShapesSelected() {
		return selectedShapes_.size() > 1;
	}

	virtual bool isEmpty() {		
		return shapes_.empty();
	}
protected:

	VCF::Array<Shape*> shapes_;
	VCF::Array<Shape*> selectedShapes_;

	void deleteShapes();
};


#endif // _VCF_SKETCHMODEL_H__

/**
$Id: SketchModel.h 2742 2006-06-01 05:01:27Z kdmix $
*/
