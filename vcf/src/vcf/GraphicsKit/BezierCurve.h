#ifndef _VCF_BEZIERCURVE_H__
#define _VCF_BEZIERCURVE_H__
//BezierCurve.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
The BezierCurve is a basic implementation of the Path interface and provides
methods to create lines, rectangles, polylines, and curves.
@see Path
*/
class GRAPHICSKIT_API BezierCurve : public VCF::Object, public VCF::Path {
public:
	BezierCurve();

	virtual ~BezierCurve();

	virtual void applyTransform( const Matrix2D& transform );

	virtual bool contains( const Rect& rect);

    virtual bool contains( const Point& pt );

    virtual bool intersects( const Point& pt );

    virtual bool intersects( const Rect& rect );

    virtual Rect getBounds();

    virtual WindingRule getWindingRule() {
		return windingRule_;
	}

	virtual void setWindingRule( WindingRule rule ) {
		windingRule_ = rule;
	}

	virtual bool getPoints( std::vector<PathPoint>& points, Matrix2D* transform );

	virtual void flattenPoints( std::vector<Point>& flattenedPoints );

	/**
	Adds a curve to path, using the last point in path as the start point for the
	curve. 
	@param double represents the x coordinate of the 1st control point
	@param double represents the y coordinate of the 1st control point
	@param double represents the x coordinate of the 2nd control point
	@param double represents the y coordinate of the 2nd control point
	@param double represents the x coordinate of the end point of the curve
	@param double represents the y coordinate of the end point of the curve
	*/
	void curveTo( const double& cx1, const double& cy1,
					const double& cx2, const double& cy2,
					const double& x, const double& y);

	/**
	Adds a curve to path.
	@param double represents the x coordinate of the start point of the curve
	@param double represents the y coordinate of the start point of the curve
	@param double represents the x coordinate of the 1st control point
	@param double represents the y coordinate of the 1st control point
	@param double represents the x coordinate of the 2nd control point
	@param double represents the y coordinate of the 2nd control point
	@param double represents the x coordinate of the end point of the curve
	@param double represents the y coordinate of the end point of the curve
	*/
	void curve( const double& x1, const double& y1,
					const double& cx1, const double& cy1,
					const double& cx2, const double& cy2,
					const double& x2, const double& y2);

	/**
	makes a line from the last point in the path
	*/
	void lineTo( const double& x, const double& y );

	/**
	adds a non connected point to the path
	
	*/
	void moveTo( const double& x, const double& y );

	/**
	adds a rectangle to the path
	*/
	void rectangle( const Rect& rectangle );

	/**
	adds a series of lines to the path in the form of a polyline starting with 
	the last point in the path.
	@param std::vector<Point> the points to add to the path
	*/
	void polyTo( std::vector<Point>& points );

	/**
	adds a series of lines to the path in the form of a polyline.
	@param std::vector<Point> the points to add to the path
	*/
	void polyline( std::vector<Point>& points );

	/**
	closes the path.
	*/
	void close();

	/**
	removes all points from the path
	*/
	void clear();
protected:
	Path::WindingRule windingRule_;
	long currentMoveToIndex_;
	std::vector<PathPoint> points_;

};



};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/02 04:11:10  ddiego
*removed some old, extraneous files from graphics kit dir.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:30  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/26 21:58:38  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.2  2003/08/09 02:56:43  ddiego
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
*Revision 1.1.2.1  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*/


#endif // _VCF_BEZIERCURVE_H__


