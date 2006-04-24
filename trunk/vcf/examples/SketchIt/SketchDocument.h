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


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:34:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2005/07/23 21:45:41  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.3.4.1  2005/03/06 22:50:56  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.3  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.6.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.2.6.1  2004/04/28 00:27:40  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/08/09 02:56:41  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.2  2003/07/21 03:08:29  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.1.2.1  2003/07/17 03:02:46  ddiego
*added sketch example
*
*/


#endif // _VCF_SKETCHDOCUMENT_H__


