#ifndef _VCF_SKETCHTOOLS_H__
#define _VCF_SKETCHTOOLS_H__
//SketchTools.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


class Tool : public VCF::ObjectWithEvents {
public:

	Tool() : currentControl_(NULL){

	}

	void attach( VCF::Control* control );

	VCF::Control* detach();


	virtual void paintState( VCF::GraphicsContext* ctx ) {}

	virtual void onMouseDown( VCF::MouseEvent* e ) {

	}

	virtual void onMouseMove( VCF::MouseEvent* e ) {

	}

	virtual void onMouseUp( VCF::MouseEvent* e ) {

	}

	virtual void onDblClick( VCF::MouseEvent* e ) {

	}

	virtual void onKeyPressed( VCF::KeyboardEvent* e ) {

	}

	virtual void onKeyDown( VCF::KeyboardEvent* e ) {

	}

	virtual void onKeyUp( VCF::KeyboardEvent* e ) {

	}

	virtual void reset(){};

protected:
	VCF::Control* currentControl_;
};



/**
class ToolManager documentation
*/
class ToolManager : public VCF::ObjectWithEvents {
public:

	void registerTool( Tool* tool, VCF::MenuItem* item );

	Tool* getCurrentTool() {
		return currentTool_;
	}

	VCF::Control* getCurrentControl() {
		return currentControl_;
	}

	void setCurrentControl( VCF::Control* val ) {
		currentControl_ = val;
	}



	static void init();
	static void terminate();

	static ToolManager* getToolManager();
protected:
	static ToolManager* manager;
	std::map<VCF::MenuItem*,Tool*> toolMap_;
	Tool* currentTool_;
	VCF::Control* currentControl_;
	void onMenuItemClicked( VCF::MenuItemEvent* e );
	void onMenuItemUpdate( VCF::MenuItemEvent* e );
private:
	ToolManager();
	virtual ~ToolManager();
};


class Shape;



/**
class SelectTool documentation
*/
class SelectTool : public Tool{
public:
	SelectTool();
	virtual ~SelectTool();

	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );

	virtual void paintState( VCF::GraphicsContext* ctx );
protected:
	Shape* mouseOverShape_;
	Shape* hitTest( VCF::Point& pt );
	VCF::Point startDragPoint_;
	VCF::Point dragPoint_;

};



/**
class LineTool documentation
*/
class LineTool : public Tool {
public:
	LineTool();
	virtual ~LineTool();

	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );
protected:
	VCF::Point start_;
	VCF::Point end_;
};


class RotateTool : public Tool {
public:
	virtual void paintState( VCF::GraphicsContext* ctx );

	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );
protected:
	VCF::Point startDragPoint_;
	VCF::Point dragPoint_;
	double startAngle_;
	VCF::Point origin_;

	void rotateShape( Shape* shape, VCF::Point pt );
};

class ScaleTool : public Tool {
public:
	virtual void paintState( VCF::GraphicsContext* ctx );

	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );
protected:
	VCF::Point startDragPoint_;
	VCF::Point dragPoint_;

	VCF::Point origin_;
	VCF::Rect bounds_;

	void scaleShape( Shape* shape, VCF::Point pt );
};



class SkewTool : public Tool {
public:
	virtual void paintState( VCF::GraphicsContext* ctx );

	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );
protected:
	VCF::Point startDragPoint_;
	VCF::Point dragPoint_;
	double startAngle_;
	VCF::Point origin_;
	VCF::Rect bounds_;

	void skewShape( Shape* shape, VCF::Point pt );
};


class RectangleTool : public Tool {
public:


	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );
protected:
	VCF::Point start_;
	VCF::Point end_;
};


class CurveTool : public Tool {
public:
	enum State {
		sFirstPoint = 0,
		sNextPoint
	};

	struct Segment {
		VCF::Point pt1;
		VCF::Point pt2;
		VCF::Point ctrl1;
		VCF::Point ctrl2;

		bool operator ==( const Segment& rhs ) const{
			return (pt1 == rhs.pt1) &&
						(pt2 == rhs.pt2) &&
						(ctrl1 == rhs.ctrl1) &&
						(ctrl2 == rhs.ctrl2);
		}

		bool operator !=( const Segment& rhs ) const{
			return (pt1 != rhs.pt1) ||
						(pt2 != rhs.pt2) ||
						(ctrl1 != rhs.ctrl1) ||
						(ctrl2 != rhs.ctrl2);
		}
	};


	CurveTool(): state_(sFirstPoint){}



	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );

	virtual void onDblClick( VCF::MouseEvent* e );

	virtual void paintState( VCF::GraphicsContext* ctx );

	virtual void reset();
protected:
	VCF::Point start_;
	VCF::Point end_;

	Segment segment_;
	std::vector<Segment> segments_;

	State state_;


	void drawCurve( VCF::GraphicsContext* ctx );
	bool overFirstPoint( VCF::Point& pt );
	void finishCurve();
	void paintSegments( VCF::GraphicsContext* ctx );

};


class ImageTool : public Tool {
public:

	ImageTool(): img_(NULL){}

	virtual void onMouseDown( VCF::MouseEvent* e );

	virtual void onMouseMove( VCF::MouseEvent* e );

	virtual void onMouseUp( VCF::MouseEvent* e );

	virtual void paintState( VCF::GraphicsContext* ctx );
protected:
	VCF::Point start_;
	VCF::Point end_;
	VCF::Image* img_;
};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:37  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.6.3  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.2  2003/08/09 02:56:42  ddiego
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
*Revision 1.1.2.4  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.1.2.3  2003/07/21 03:08:29  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.1.2.2  2003/07/18 04:38:54  ddiego
*got more work done on the sketch examples plus fixed a bug in the application
*of a transform ot a path
*
*Revision 1.1.2.1  2003/07/17 03:02:46  ddiego
*added sketch example
*
*/


#endif // _VCF_SKETCHTOOLS_H__


