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

	virtual bool contains( const Rect& rect, Matrix2D* transform=NULL);

    virtual bool contains( const Point& pt, Matrix2D* transform=NULL );

    virtual bool intersects( const Point& pt, Matrix2D* transform=NULL );

    virtual bool intersects( const Rect& rect, Matrix2D* transform=NULL );

    virtual Rect getBounds();

    virtual WindingRule getWindingRule() {
		return windingRule_;
	}

	virtual void setWindingRule( WindingRule rule ) {
		windingRule_ = rule;
	}

	virtual bool getPoints( std::vector<PathPoint>& points, Matrix2D* transform );

	/**
	Gets the vector points of this curve.
	Added this function so that you edit the path points directly instead of having 
	to copy them each time you need to make an alteration.
	*/
	virtual std::vector<PathPoint>* getPoints() { return &points_; }

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
	int32 currentMoveToIndex_;
	std::vector<PathPoint> points_;

};



};


#endif // _VCF_BEZIERCURVE_H__

/**
$Id$
*/
