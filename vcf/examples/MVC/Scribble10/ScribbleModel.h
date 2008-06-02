#ifndef _SCRIBBLE_MODEL_H__
#define _SCRIBBLE_MODEL_H__


#include "vcf/ApplicationKit/SimpleListModel.h"
#include "vcf/FoundationKit/StringTokenizer.h"

using VCF::Matrix2D;
using VCF::Point;
using VCF::Rect;
using VCF::Color;
using VCF::VariantData;
using VCF::uint32;
using VCF::String;
using VCF::StringTokenizer;
using VCF::StringUtils;
using VCF::Format;
using VCF::ModelEvent;
using VCF::Persistable;
using VCF::InputStream;
using VCF::OutputStream;
using VCF::MIMEType;
using VCF::AbstractCommand;
using VCF::DocumentManager;
using VCF::pdObject;
using VCF::Object;
using VCF::XMLNode;
using VCF::XMLParser;
using VCF::Enumerator;



class ScribbleShape : public VCF::Object {
public:
	

	ScribbleShape():type(stNone),strokeWidth(1.0),filled(true) {}
	enum Type {
		stNone,
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


	Color* getFill() {
		return &fill;
	}

	void setFill( Color* val ) {
		fill = *val;
	}

	Color* getStroke() {
		return &stroke;
	}

	void setStroke( Color* val ) {
		stroke = *val;
	}

	void setStrokeWidth( const double& val ) {
		strokeWidth = val;
	}

	double getStrokeWidth() {
		return strokeWidth;
	}

	void setData( const VCF::String& val ) {
		String tmp = StringUtils::lowerCase(val);
		points.clear();

		StringTokenizer tok(tmp, " \t\r\n");

		String dataType;
		if ( tok.hasMoreElements() ) {
			dataType = tok.nextElement();
		}

		while ( tok.hasMoreElements() ) {
			String s = tok.nextElement();
			if ( "z" == s ) {
				break;
			}

			Point p;
			p.x_ = StringUtils::fromStringAsDouble( tok.nextElement() );
			p.y_ = StringUtils::fromStringAsDouble( tok.nextElement() );

			points.push_back( p );
		}

		if ( dataType == "line" ) {
			type = stLine;
		}
		else if ( dataType == "rect" ) {
			type = stRect;
		}
		else if ( dataType == "ellipse" ) {
			type = stEllipse;
		}
		else if ( dataType == "poly" ) {
			type = stPolygon;
			points.push_back( points.front() );
		}
		else if ( dataType == "free" ) {
			type = stFreehand;
		}
	}

	VCF::String getData() {
		String result;
		switch ( type ) {
			case ScribbleShape::stLine : {
				result += "line ";
			}
			break;

			case ScribbleShape::stRect : {
				result += "rect ";
			}
			break;

			case ScribbleShape::stEllipse : {
				result += "ellipse ";
			}
			break;

			case ScribbleShape::stPolygon : {
				result += "poly ";
			}
			break;

			case ScribbleShape::stFreehand : {
				result += "free ";
			}
			break;
		}

		std::vector<Point>::const_iterator it = points.begin();
		while ( it != points.end() ) {
			const Point& pt = *it;
			
			if ( it == points.begin() ) {
				result += "M ";
			}
			else {
				result += "L ";
			}

			result += Format( "%0.3f %0.3f " ) % pt.x_ % pt.y_;
			
			++it;
		}

		return result;
	}


	void setFilled( const bool& val ) {
		filled = val;
	}

	bool getFilled() {
		return filled;
	}

	void setRotation( const double& val ) {
		mat *= Matrix2D::rotation( val );
	}

	double getRotation() {
		return mat.getRotation();
	}

	void setTranslateX( const double& val ) {
		mat *= Matrix2D::translation( val, 0 );
	}

	double getTranslateX() {
		return mat.getTranslateX();
	}

	void setTranslateY( const double& val ) {
		mat *= Matrix2D::translation( 0, val );
	}

	double getTranslateY() {
		return mat.getTranslateY();
	}

	void setScaleX( const double& val ) {
		mat *= Matrix2D::scaling( val, 1.0 );
	}

	double getScaleX() {
		return mat.getScaleX();
	}

	void setScaleY( const double& val ) {
		mat *= Matrix2D::scaling( 1.0, val );
	}

	double getScaleY() {
		return mat.getScaleY();
	}

	void setShearX( const double& val ) {
		mat *= Matrix2D::shearing( val, 0.0 );
	}

	double getShearX() {
		return mat.getShearX();
	}

	void setShearY( const double& val ) {
		mat *= Matrix2D::shearing( 0.0, val );
	}

	double getShearY() {
		return mat.getShearY();
	}


	Matrix2D getMatrix() {
		return mat;
	}

	String getTypeName() {
		String result;
		switch ( type ) {
			case ScribbleShape::stLine : {
				result = "Line";
			}
			break;

			case ScribbleShape::stRect : {
				result = "Rect";
			}
			break;

			case ScribbleShape::stEllipse : {
				result = "Ellipse";
			}
			break;

			case ScribbleShape::stPolygon : {
				result = "Polygon";
			}
			break;

			case ScribbleShape::stFreehand : {
				result = "Freehand";
			}
			break;
		}

		return result;
	}
};






class ScribbleModel : public VCF::SimpleListModel, public Persistable {
public:

	enum ScribbleModelEvents {
		ActiveShapeChanged =  MODEL_LAST_EVENT + 10,
		ShapeMatrixChanged,
		ShapePointsChanged,
		ShapeAttributesChanged,
	};

	class AddShape : public AbstractCommand {
	public:
		AddShape( ScribbleModel* model, ScribbleShape* shape, const uint32& insertIndex ):
			model_(model), shape_(shape),insertIndex_(insertIndex) {
			isUndoable_ = true;
			commandName_ = "Add " + shape_->getTypeName();
		}

		virtual ~AddShape(){
			VariantData v = shape_;
			uint32 index = model_->getIndexOf(v);
			if ( index == ListModel::IndexNotFound ) {
				delete shape_;
			}
		}

		virtual void undo() {
			VariantData v = shape_;
			
			model_->internal_remove( model_->getIndexOf(v) );
		}

		virtual void redo() {
			model_->internal_insert( insertIndex_, shape_ );
		}

		virtual void execute() {
			model_->internal_insert( insertIndex_, shape_ );
		}
	protected:
		ScribbleModel* model_;
		ScribbleShape* shape_;
		uint32 insertIndex_;

	};

	class RemoveShape : public AbstractCommand {
	public:
		RemoveShape( ScribbleModel* model, const uint32& index ):model_(model), index_(index) {
			isUndoable_ = true;

			shape_ = model->getShape(index);

			commandName_ = "Remove " + shape_->getTypeName();			
		}


		virtual void undo() {			
			model_->internal_insert( index_, shape_ );
		}

		virtual void redo() {
			model_->internal_remove( index_ );
		}

		virtual void execute() {			
			model_->internal_remove( index_ );
		}
	protected:
		ScribbleModel* model_;
		ScribbleShape* shape_;
		uint32 index_;
	};

	class ModifyShapeAttributes : public AbstractCommand {
	public:
		ModifyShapeAttributes( ScribbleModel* model, ScribbleShape* shape, bool filled, const Color& fill, const Color& stroke, double width ):
			model_(model), shape_(shape), filled_(filled), fill_(fill), stroke_(stroke), width_(width) {

			filledOld_ = shape_->filled;
			fillOld_ = shape_->fill;
			strokeOld_ = shape_->stroke;
			widthOld_ = shape_->strokeWidth;

			commandName_ = "Modify " + shape_->getTypeName() + " attributes";
		}

		virtual void undo() {			
			model_->internal_modifyAttributes( shape_, filledOld_, fillOld_, strokeOld_, widthOld_ );
		}

		virtual void redo() {
			model_->internal_modifyAttributes( shape_, filled_, fill_, stroke_, width_ );
		}

		virtual void execute() {			
			model_->internal_modifyAttributes( shape_, filled_, fill_, stroke_, width_ );
		}

		ScribbleModel* model_;
		ScribbleShape* shape_;
		bool filled_;
		Color fill_;
		Color stroke_;
		double width_;

		bool filledOld_;
		Color fillOld_;
		Color strokeOld_;
		double widthOld_;
	};

	class ModifyShapeMatrix : public AbstractCommand {
	public:
		ModifyShapeMatrix( ScribbleModel* model, ScribbleShape* shape, const Matrix2D& mat ):
			model_(model), shape_(shape), mat_(mat) {

			matOld_ = shape_->mat;

			commandName_ = "Modify " + shape_->getTypeName() + " transform";
		}

		virtual void undo() {			
			model_->internal_setShapeMatrix( shape_, matOld_ );
		}

		virtual void redo() {
			model_->internal_setShapeMatrix( shape_, mat_ );
		}

		virtual void execute() {			
			model_->internal_setShapeMatrix( shape_, mat_ );
		}

		ScribbleModel* model_;
		ScribbleShape* shape_;
		Matrix2D mat_;
		Matrix2D matOld_;
	};

	friend class AddShape;
	friend class RemoveShape;
	friend class ModifyShapeAttributes;
	friend class ModifyShapeMatrix;




	ScribbleModel():activeShape(NULL){

		backColor = *Color::getColor("white");
		defaultShape.fill = *Color::getColor("white");
	}

	virtual ~ScribbleModel() {
		deleteVariantObjects_ = true;
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
		add(s);
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
		s->filled = false;
		add( s );
	}


	void setRect( const size_t& index, const Point& p1, const Point& p2 ) {
		ScribbleShape* s = getShape( index );

		Rect r(p1.x_,p1.y_,p2.x_,p2.y_);
		r.normalize();

		s->points[0] = r.getTopLeft();
		s->points[1] = r.getBottomRight();

		ModelEvent e(this,ShapePointsChanged);		
		changed( &e );
	}

	void setLine( const size_t& index, const Point& p1, const Point& p2 ) {
		ScribbleShape* s = getShape( index );
		Rect r(p1.x_,p1.y_,p2.x_,p2.y_);
		//r.normalize();

		s->points[0] = r.getTopLeft();
		s->points[1] = r.getBottomRight();

		ModelEvent e(this,ShapePointsChanged);		
		changed( &e );
	}

	void setEllipse( const size_t& index, const Point& p1, const Point& p2 ) {
		ScribbleShape* s = getShape( index );
		Rect r(p1.x_,p1.y_,p2.x_,p2.y_);
		r.normalize();

		s->points[0] = r.getTopLeft();
		s->points[1] = r.getBottomRight();

		ModelEvent e(this,ShapePointsChanged);		
		changed( &e );
	}

	void addPolygonPt( const size_t& index, const Point& p1 ) {
		ScribbleShape* s = getShape( index );
		s->points.push_back( p1 );

		ModelEvent e(this,ShapePointsChanged);		
		changed( &e );
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


	virtual VariantData get( const uint32& index ) {

		size_t missing = 0;
		if ( (index+1) > data_.size() ) {
			missing = (index+1) - data_.size();
		}
		//add empty shapes if we need to
		if ( missing > 0 ) {
			size_t i=data_.size();
			data_.resize( missing + data_.size() );
			while ( i < data_.size() ) {
				ScribbleShape* s = new ScribbleShape();
				*s = defaultShape;

				data_[i] = s;
				i++;
			}
		}

		return data_[index];
	}

	virtual String getAsString(const uint32& index ) {
		String result;
		ScribbleShape* shape = getShape(index);
		if ( NULL != shape ) {
			result = String("Shape #") + (index+1) + " pts: " + shape->points.size();
		}
		
		return result;
	}

	ScribbleShape* getActiveShape() {
		return activeShape;
	}

	void setActiveShape(ScribbleShape* val) {
		activeShape = val;
		ModelEvent e(this,ActiveShapeChanged);
		changed( &e );
	}
	
	void setShapeMatrix( ScribbleShape* shape, const Matrix2D& m, bool undoable = false ) {
		if ( undoable ) {
			DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new ModifyShapeMatrix( this, shape, m ) );			
		}
		else {
			shape->mat = m;
			ModelEvent e(this,ShapeMatrixChanged);		
			changed( &e );
		}
	}
	

	virtual void loadFromStream( InputStream* stream, const MIMEType& type ) {
		if ( type == "application/x-scribbledoc" ) {
			readShape( stream, &defaultShape );
			
			double val = 0;
			stream->read( val );
			backColor.setRed(val);
			
			stream->read( val );
			backColor.setGreen(val);
			
			stream->read( val );
			backColor.setBlue(val);
			
			stream->read( val );
			backColor.setAlpha(val);
			

			size_t count = 0;
			stream->read( count );

			for (size_t i=0;i<count;i++ ) {
				ScribbleShape* shape = getShape(i);
				readShape( stream, shape );
			}
		}
		else if ( "text/plain" == type ) {
			XMLParser parser;
			parser.parse( stream );

			Enumerator<XMLNode*>* nodes = parser.getParsedNodes();

			while ( nodes->hasMoreElements() ) {
				XMLNode* node = nodes->nextElement();

				if ( node->getName() == "ScribbleDoc" ) {

					ScribbleShape* shape = new ScribbleShape();

					XMLNode* active = node->getNodeByName( "activeShape" );
					XMLNode* mat = active->getNodeByName( "transform" );
					shape->mat[Matrix2D::mei00] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei00")->getCDATA() );
					shape->mat[Matrix2D::mei01] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei01")->getCDATA() );
					shape->mat[Matrix2D::mei02] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei02")->getCDATA() );
					shape->mat[Matrix2D::mei10] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei10")->getCDATA() );
					shape->mat[Matrix2D::mei11] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei11")->getCDATA() );
					shape->mat[Matrix2D::mei12] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei12")->getCDATA() );
					shape->mat[Matrix2D::mei20] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei20")->getCDATA() );
					shape->mat[Matrix2D::mei21] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei21")->getCDATA() );
					shape->mat[Matrix2D::mei22] = StringUtils::fromStringAsDouble( mat->getNodeByName("mei22")->getCDATA() );

				
					shape->filled = StringUtils::fromStringAsBool( active->getAttrByName("filled")->getValue() );
					shape->fill.setFromString( active->getAttrByName("fill")->getValue() );
					shape->stroke.setFromString( active->getAttrByName("stroke")->getValue() );
					shape->strokeWidth = StringUtils::fromStringAsDouble( active->getAttrByName("strokeWidth")->getValue() );


					XMLNode* pts = active->getNodeByName( "points" );

					shape->setData( pts->getCDATA() );

					shape->mat *= Matrix2D::translation( 10, 10 );

					add( shape );
					
					break;
				}
			}

		}
		else if ( "application/x-scribbleshape" == type ) {			
			ScribbleShape* shape = new ScribbleShape();
			readShape( stream, shape );

			shape->mat *= Matrix2D::translation( 10, 10 ); //make a slight offset

			add( shape );
		}
	}

	virtual void saveToStream( OutputStream* stream, const MIMEType& type ) {
		if ( type == "application/x-scribbledoc" ) {
			writeShape( stream, &defaultShape );

			stream->write( backColor.getRed()  );
			stream->write( backColor.getGreen()  );
			stream->write( backColor.getBlue()  );
			stream->write( backColor.getAlpha()  );

			size_t count = getCount();
			stream->write( count );

			for (size_t i=0;i<count;i++ ) {
				ScribbleShape* shape = getShape(i);
				writeShape( stream, shape );
			}
		}
		else if ( "text/plain" == type ) {
			VCF_ASSERT( NULL != activeShape );

			XMLNode root("ScribbleDoc");		
			
			XMLNode* node = root.addChildNode( "activeShape" );
			node->addAttr( "filled", StringUtils::toString(activeShape->filled) );

			node->addAttr( "fill", activeShape->fill.toString() );
			node->addAttr( "stroke", activeShape->stroke.toString() );
			node->addAttr( "strokeWidth", StringUtils::toString(activeShape->strokeWidth) );
			

			node->addAttr( "type", StringUtils::toString(activeShape->type) );

			XMLNode* mat = node->addChildNode( "transform" );
			mat->addChildNode( "mei00" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei00]) );
			mat->addChildNode( "mei01" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei01]) );
			mat->addChildNode( "mei02" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei02]) );
			mat->addChildNode( "mei10" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei10]) );
			mat->addChildNode( "mei11" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei11]) );
			mat->addChildNode( "mei12" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei12]) );
			mat->addChildNode( "mei20" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei20]) );
			mat->addChildNode( "mei21" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei21]) );
			mat->addChildNode( "mei22" )->setCDATA( StringUtils::toString(activeShape->mat[Matrix2D::mei22]) );
			
			

			XMLNode* pts = node->addChildNode( "points" );
			pts->setCDATA( activeShape->getData() );

			stream->write( root.toString() );
		}
		else if ( "application/x-scribbleshape" == type ) {
			VCF_ASSERT( NULL != activeShape );

			writeShape( stream, activeShape );
		}
	}

	void modifyAttributes( ScribbleShape* shape, bool filled, const Color& fill, const Color& stroke, double width ) {
		DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new ModifyShapeAttributes( this, shape, filled, fill, stroke, width ) );
		
	}
protected:
	void internal_setShapeMatrix( ScribbleShape* shape, const Matrix2D& m ) {
		shape->mat = m;
		ModelEvent e(this,ShapeMatrixChanged);
		changed( &e );
	}

	void internal_modifyAttributes( ScribbleShape* shape, bool filled, const Color& fill, const Color& stroke, double width ) {
		shape->stroke = stroke;
		shape->fill = fill;
		shape->filled = filled;
		shape->strokeWidth = width;
		ModelEvent e(this,ShapeAttributesChanged);
		changed( &e );		
	}

	void readShape( InputStream* stream, ScribbleShape* shape ) {
		double val = 0;

		stream->read( shape->filled );
		stream->read( val );
		shape->fill.setRed(val);

		stream->read( val );
		shape->fill.setGreen(val);

		stream->read( val );
		shape->fill.setBlue(val);

		stream->read( val );
		shape->fill.setAlpha(val);

		stream->read( val );
		shape->stroke.setRed(val);

		stream->read( val );
		shape->stroke.setGreen(val);

		stream->read( val );
		shape->stroke.setBlue(val);

		stream->read( val );
		shape->stroke.setAlpha(val);

		stream->read( shape->strokeWidth );

		int val2 = 0;
		stream->read( val2);
		shape->type = (ScribbleShape::Type)val2;

		stream->read( shape->mat[Matrix2D::mei00] );
		stream->read( shape->mat[Matrix2D::mei01] );
		stream->read( shape->mat[Matrix2D::mei02] );
		stream->read( shape->mat[Matrix2D::mei10] );
		stream->read( shape->mat[Matrix2D::mei11] );
		stream->read( shape->mat[Matrix2D::mei12] );
		stream->read( shape->mat[Matrix2D::mei20] );
		stream->read( shape->mat[Matrix2D::mei21] );
		stream->read( shape->mat[Matrix2D::mei22] );

		size_t ptCount = 0;
		stream->read( ptCount );
		shape->points.resize(ptCount);

		for (size_t j=0;j<ptCount;j++ ) {
			Point& pt = shape->points[j];
			stream->read( pt.x_ );
			stream->read( pt.y_ );
		} 
	}

	void writeShape( OutputStream* stream, ScribbleShape* shape ) {
		stream->write( shape->filled  );
		stream->write( shape->fill.getRed()  );
		stream->write( shape->fill.getGreen()  );
		stream->write( shape->fill.getBlue()  );
		stream->write( shape->fill.getAlpha()  );
		
		stream->write( shape->stroke.getRed()  );
		stream->write( shape->stroke.getGreen()  );
		stream->write( shape->stroke.getBlue()  );
		stream->write( shape->stroke.getAlpha()  );
		
		stream->write( shape->strokeWidth );
		
		stream->write( (int)shape->type );
		
		stream->write( shape->mat[Matrix2D::mei00] );
		stream->write( shape->mat[Matrix2D::mei01] );
		stream->write( shape->mat[Matrix2D::mei02] );
		stream->write( shape->mat[Matrix2D::mei10] );
		stream->write( shape->mat[Matrix2D::mei11] );
		stream->write( shape->mat[Matrix2D::mei12] );
		stream->write( shape->mat[Matrix2D::mei20] );
		stream->write( shape->mat[Matrix2D::mei21] );
		stream->write( shape->mat[Matrix2D::mei22] );
		
		
		size_t ptCount = shape->points.size();
		stream->write( ptCount );
		for (size_t j=0;j<ptCount;j++ ) {
			const Point& pt = shape->points[j];
			stream->write( pt.x_ );
			stream->write( pt.y_ );
		}
	}

	void internal_insert( const uint32 & index, const VariantData& item ) {
		SimpleListModel::doInsert( index, item );
		updateAllViews();
	}

	void internal_remove( const uint32 & index ) {
		activeShape = NULL;
		deleteVariantObjects_ = false;
		SimpleListModel::doRemove( index );
		updateAllViews();
	}

	virtual bool doInsert( const uint32 & index, const VariantData& item ) {
		VCF_ASSERT( item.type == pdObject );
		if ( item.type != pdObject ) {
			return false;
		}

		Object* o = item;
		ScribbleShape* s = (ScribbleShape*)o;

		DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new AddShape( this, s, index ) );
		return true;
	}

	virtual bool doRemove( const uint32& index ) {
		

		DocumentManager::getDocumentManager()->getUndoRedoStack(this).addCommand( new RemoveShape( this, index ) );

		return true;
	}

	

	ScribbleShape defaultShape;
	Color backColor;
	ScribbleShape* activeShape;
};


#endif //_SCRIBBLE_MODEL_H__