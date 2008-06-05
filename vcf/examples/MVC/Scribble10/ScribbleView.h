#ifndef _SCRIBBLE_VIEW_H__
#define _SCRIBBLE_VIEW_H__

using VCF::AbstractView;
using VCF::GraphicsContext;
using VCF::Rect;
using VCF::Point;
using VCF::Control;
using VCF::Scrollable;

class ScribbleView : public AbstractView {
public:
	ScribbleView():hotShape(NULL),dragShape(NULL){}

	ScribbleShape* hotShape;
	ScribbleShape* dragShape;


	void drawShape( GraphicsContext* ctx, const ScribbleShape* shape ) {
		Rect r;
		ScribbleModel* scribble = (ScribbleModel*) getViewModel();

		if ( !shape->points.empty() ) {	

			int gcs = ctx->saveState();

			ctx->setCurrentTransform( shape->mat );
			switch ( shape->type ) {
				case ScribbleShape::stLine : {
					ctx->setColor( &shape->stroke );
					ctx->setStrokeWidth( shape->strokeWidth );

					ctx->moveTo( shape->points[0] );
					ctx->lineTo( shape->points[1] );

					if ( shape != dragShape ) {
						ctx->strokePath();
					}
				}
				break;

				case ScribbleShape::stRect : {
					
					r.setRect( shape->points[0].x_, shape->points[0].y_,
								shape->points[1].x_, shape->points[1].y_ );
					ctx->rectangle( r );
				}
				break;

				case ScribbleShape::stEllipse : {
					r.setRect( shape->points[0].x_, shape->points[0].y_,
								shape->points[1].x_, shape->points[1].y_ );

					ctx->ellipse( r.getTopLeft(), r.getBottomRight() );					
				}
				break;

				case ScribbleShape::stPolygon : {
					if ( shape->points.size() > 1 ) {
						ctx->polyline( shape->points );
						ctx->closePath( shape->points.back() );
					}
				}
				break;

				case ScribbleShape::stFreehand : {
					if ( shape->points.size() > 1 ) {
						ctx->polyline( shape->points );
					}
				}
				break;
			}

			if ( shape != dragShape ) {
				if ( shape->type != ScribbleShape::stLine ) {
					
					if ( shape->points.size() > 1 ) {
						
						if ( shape->filled ) {
							ctx->setColor( &shape->fill );
							ctx->fillPath();
						}
						
						ctx->setStrokeWidth( shape->strokeWidth );
						ctx->setColor( &shape->stroke );
						ctx->strokePath();
					}					
				}
				
				if ( shape == scribble->getActiveShape() ) {
					Color c( (unsigned char)0x47,(unsigned char)0x8A,(unsigned char)0xFF );
					ctx->setStrokeWidth( 2.0 );
					ctx->setColor( &c );
					ctx->strokePath();
				}
				
				if ( shape == hotShape ) {
					Color c( 1.0,0.0,0.0 );
					ctx->setStrokeWidth( 2.0 );
					ctx->setColor( &c );
					ctx->strokePath();
				}
			}
			else {
				Color c( 0.0,1.0,0.0 );
				ctx->setStrokeWidth( 1.0 );
				ctx->setColor( &c );
				ctx->strokePath();
			}


			ctx->restoreState( gcs );
		}
	}

	virtual void paintView( GraphicsContext* ctx ) {
		
		
		
		ScribbleModel* scribble = (ScribbleModel*) getViewModel();

		Control* control = getViewControl();
		Rect r = control->getClientBounds();

		ctx->rectangle( r );
		ctx->setColor( scribble->getBackColor() );
		ctx->fillPath();

		
		Scrollable* scrollable = control->getScrollable();
		if ( scrollable ) {
			Rect viewBounds = ctx->getViewableBounds();
			
			Point origin = ctx->getOrigin();
			
			control->adjustViewableBoundsAndOriginForScrollable( ctx, viewBounds, origin );
			
			ctx->setOrigin( origin );
			
			ctx->setViewableBounds( viewBounds );
		}


		size_t count = scribble->getCount();

		for (size_t i=0;i<count;i++ ) {
			const ScribbleShape* shape = scribble->getShape(i);			

			drawShape( ctx, shape );
		}

		if ( NULL != dragShape ) {
			drawShape( ctx, dragShape );
		}
	}
};

#endif //_SCRIBBLE_VIEW_H__

