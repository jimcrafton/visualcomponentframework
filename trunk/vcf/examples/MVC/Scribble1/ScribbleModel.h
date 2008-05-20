#ifndef _SCRIBBLE_MODEL_H__
#define _SCRIBBLE_MODEL_H__


#include "vcf/ApplicationKit/SimpleListModel.h"

using VCF::Matrix2D;
using VCF::Point;
using VCF::Rect;
using VCF::Color;
using VCF::VariantData;
using VCF::uint32;


class ScribbleShape : public VCF::Object {
public:
	ScribbleShape():type(stLine),strokeWidth(1.0),filled(true) {}
	enum Type {
		stLine,
		stRect,
		stEllipse,
		stPolygon,
		stFreehand
	};
	
	Matrix2D mat;
	std::vector<Point> points;
	Type type;
	double strokeWidth;
	bool filled;
	Color fill;
	Color stroke;

	
};

class ScribbleModel : public VCF::SimpleListModel {
public:
	ScribbleModel(){
		//set this to true to 
		//delete all our objects
		deleteVariantObjects_ = true;

		backColor = *Color::getColor("white");
	}

	ScribbleShape* getShape( const unsigned int& index ) {
		return (ScribbleShape*) (VCF::Object*) get(index);
	}

	void addLine( const Point& p1, const Point& p2 ) {
		ScribbleShape* s = new ScribbleShape();
		*s = defaultShape;
		s->points.push_back( p1 );
		s->points.push_back( p2 );
		s->type = ScribbleShape::stLine;
		add( s );
	}

	void addRect( const Point& p1, const Point& p2 ) {
		ScribbleShape* s = new ScribbleShape();
		*s = defaultShape;
		s->points.push_back( p1 );
		s->points.push_back( p2 );
		s->type = ScribbleShape::stRect;
		add( s );
	}

	void addEllipse( const Point& p1, const Point& p2 ) {
		ScribbleShape* s = new ScribbleShape();
		*s = defaultShape;
		s->points.push_back( p1 );
		s->points.push_back( p2 );
		s->type = ScribbleShape::stEllipse;
		add( s );
	}

	void addCircle( const Point& center, double radius ) {
		ScribbleShape* s = new ScribbleShape();
		*s = defaultShape;
		Point pt;
		pt.x_ = center.x_ - radius;
		pt.y_ = center.y_ - radius;

		s->points.push_back( pt );

		pt.x_ = center.x_ + radius;
		pt.y_ = center.y_ + radius;
		s->points.push_back( pt );

		s->type = ScribbleShape::stEllipse;
		add( s );
	}

	void addPolygon( const std::vector<Point>& pts ) {
		ScribbleShape* s = new ScribbleShape();
		*s = defaultShape;
		s->points = pts;
		s->type = ScribbleShape::stPolygon;
		add( s );
	}

	void addFreehand( const std::vector<Point>& pts ) {
		ScribbleShape* s = new ScribbleShape();
		*s = defaultShape;
		s->points = pts;
		s->type = ScribbleShape::stFreehand;
		add( s );
	}

	void setDefaultWidth( const double& val ) {
		defaultShape.strokeWidth = val;
	}

	void setDefaultFilled( const bool& val ) {
		defaultShape.filled = val;
	}

	void setDefaultStrokeColor( Color* val ) {
		defaultShape.stroke = *val;
	}

	void setDefaultFillColor( Color* val ) {
		defaultShape.fill = *val;
	}

	void setDefaultMatrix( Matrix2D* val ) {
		defaultShape.mat = *val;
	}

	double getDefaultWidth() {
		return defaultShape.strokeWidth;
	}

	bool getDefaultFilled() {
		return defaultShape.filled;
	}

	Color* getDefaultFillColor() {
		return &defaultShape.fill;
	}

	Color* getDefaultStrokeColor() {
		return &defaultShape.stroke;
	}

	Matrix2D* getDefaultMatrix() {
		return &defaultShape.mat;
	}
	


	void setBackColor( Color* val ) {
		backColor = *val;
		VCF::ModelEvent e( this, VCF::Model::MODEL_CHANGED );
		changed( &e );
	}

	Color* getBackColor() {
		return &backColor;
	}

	Rect getMaxBounds() {
		Rect result;

		size_t count = getCount();
		for (size_t i=0;i<count;i++ ) {
			const ScribbleShape* shape = getShape(i);
			std::vector<Point>::const_iterator it = shape->points.begin();
			while ( it != shape->points.end() ) {
				Point pt = *it;

				pt = shape->mat.apply( &pt );

				if ( pt.x_ < result.left_ ) {
					result.left_ = pt.x_;
				}
				else if ( pt.x_ > result.right_ ) {
					result.right_ = pt.x_;
				}

				if ( pt.y_ < result.top_ ) {
					result.top_ = pt.y_;
				}
				else if ( pt.y_ > result.bottom_ ) {
					result.bottom_ = pt.y_;
				}

				++it;
			}
		}

		return result;
	}
	
protected:
	ScribbleShape defaultShape;
	Color backColor;
};


#endif //_SCRIBBLE_MODEL_H__