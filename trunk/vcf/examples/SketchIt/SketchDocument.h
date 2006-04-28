#ifndef _VCF_SKETCHDOCUMENT_H__
#define _VCF_SKETCHDOCUMENT_H__
//SketchDocument.h

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

	Shape() :image_(NULL), fill_(false), width_(1.0), opacity_(1.0){

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
		opacity_ = rhs.opacity_;

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
	double opacity_;
};


/**
class SketchDocument documentation
*/

#define SKETCHDOCUMENT_CLASSID		"5e2698e2-bbe0-4f6f-ab6e-938f522a3c0d"

class SketchDocument : public VCF::Document {
public:

	_class_rtti_( SketchDocument, "VCF::Document", SKETCHDOCUMENT_CLASSID )
	_class_rtti_end_

	SketchDocument();

	virtual ~SketchDocument();

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

	virtual void empty();

	void addShape( Shape& shape );

	void removeShape( Shape* shape ) ;

	VCF::Enumerator<Shape*>* getShapes() {
		return shapesContainer_.getEnumerator();
	}

	void setSelectedShape( Shape* shape ) ;

	void addSelectedShape( Shape* shape ) ;

	void removeSelectedShape( Shape* shape ) ;

	Shape* getSelectedShape();

	VCF::Enumerator<Shape*>* getSelectedShapes() {
		return selectedShapesContainer_.getEnumerator();
	}

	bool hasMultipleShapesSelected() {
		return selectedShapes_.size() > 1;
	}
protected:

	std::vector<Shape*> shapes_;
	std::vector<Shape*> selectedShapes_;
	VCF::EnumeratorContainer<std::vector<Shape*>,Shape*> shapesContainer_;
	VCF::EnumeratorContainer<std::vector<Shape*>,Shape*> selectedShapesContainer_;

	void deleteShapes();
};


#endif // _VCF_SKETCHDOCUMENT_H__

/**
$Id$
*/
