/**
*CVS Log info
*$Log$
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




#ifndef _SKETCHDOCUMENT_H__
#define _SKETCHDOCUMENT_H__

#include "ModelViewKit.h"

#include "graphics/BezierCurve.h"


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

	BEGIN_CLASSINFO( SketchDocument, "SketchDocument", "VCF::Document", SKETCHDOCUMENT_CLASSID )
	END_CLASSINFO( SketchDocument )

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



#endif //_SKETCHDOCUMENT_H__




