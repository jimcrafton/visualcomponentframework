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


class Tool : public VCF::ObjectWithCallbacks {
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
class ToolManager : public VCF::ObjectWithCallbacks {
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



	static void initialize();
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


#endif // _VCF_SKETCHTOOLS_H__

/**
$Id$
*/
