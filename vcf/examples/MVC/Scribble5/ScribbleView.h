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
	ScribbleView(){}

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

			int gcs = ctx->saveState();

			ctx->setCurrentTransform( shape->mat );
			switch ( shape->type ) {
				case ScribbleShape::stLine : {
					ctx->setColor( &shape->stroke );
					ctx->setStrokeWidth( shape->strokeWidth );

					ctx->moveTo( shape->points[0] );
					ctx->lineTo( shape->points[1] );
					ctx->strokePath();
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
					ctx->polyline( shape->points );
					ctx->closePath( shape->points.back() );
				}
				break;

				case ScribbleShape::stFreehand : {
					ctx->polyline( shape->points );
				}
				break;
			}

			if ( shape->type != ScribbleShape::stLine ) {
				if ( shape->filled ) {
					ctx->setColor( &shape->fill );
					ctx->fillPath();
				}

				ctx->setStrokeWidth( shape->strokeWidth );
				ctx->setColor( &shape->stroke );
				ctx->strokePath();


				
			}

			if ( shape == scribble->getActiveShape() ) {
				Color c( (unsigned char)0x47,(unsigned char)0x8A,(unsigned char)0xFF );
				ctx->setStrokeWidth( 2.0 );
				ctx->setColor( &c );
				ctx->strokePath();
			}


			ctx->restoreState( gcs );
		}
	}
};

#endif //_SCRIBBLE_VIEW_H__

