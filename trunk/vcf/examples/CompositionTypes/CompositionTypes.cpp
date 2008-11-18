//CompositionTypes.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/GraphicsKit/GradientFills.h"
#include "vcf/ApplicationKit/SliderControl.h"


using namespace VCF;

class CompositionsView : public CustomControl {
public:

	CompositionsView() {
		background = GraphicsToolkit::createImage( "res:lily.png" );	

		compMode = GraphicsContext::cmSource;
		
		addCallback( new ClassProcedure1<Event*,CompositionsView>(this, &CompositionsView::onCircleColChanged), "CompositionsView::onCircleColChanged" );
		addCallback( new ClassProcedure1<Event*,CompositionsView>(this, &CompositionsView::onCircleAlphaChanged), "CompositionsView::onCircleAlphaChanged" );	
		addCallback( new ClassProcedure1<Event*,CompositionsView>(this, &CompositionsView::onCompMode), "CompositionsView::onCompMode" );			
	}

	void onCircleColChanged( Event* e ) {
		SliderControl* slider = (SliderControl*)e->getSource();

		modeFillColor.setHSL( (slider->getPosition()/(slider->getMaxValue()-slider->getMinValue())) * 5.0, 
								0.50, 1.0 );
		repaint();

	}

	void onCircleAlphaChanged( Event* e ) {
		SliderControl* slider = (SliderControl*)e->getSource();

		modeFillColor.setAlpha( slider->getPosition()/(slider->getMaxValue()-slider->getMinValue()) );
		repaint();
	}

	void onCompMode( Event* e ) {
		Component* comp = (SliderControl*)e->getSource();
		compMode = (GraphicsContext::CompositingMode)comp->getTag();
		repaint();		
	}

	void drawCheckerboard(GraphicsContext* ctx) 
	{
		Rect r = getClientBounds();

		ctx->setColor( &Color(0.90,0.90,0.90,1.0) );
		ctx->rectangle(&r);
		ctx->fillPath();

		double chkSize = 80;
		Rect chk;

		ctx->setColor( &Color(1.0,1.0,1.0,1.0) );
		for (int y = 0;y<(r.getHeight()/chkSize) + 1;y++ ) {
			for (int x = 0;x<(r.getWidth()/chkSize) + 1;x++ ) {
				if ( y % 2 ) {
					if ( !(x % 2) ) {
						chk.setRect(x*chkSize,y*chkSize,
							x*chkSize+chkSize,y*chkSize+chkSize);

						ctx->rectangle(&chk);
					}
				}
				else {
					if ( (x % 2) ) {
						chk.setRect(x*chkSize,y*chkSize,
							x*chkSize+chkSize,y*chkSize+chkSize);

						ctx->rectangle(&chk);
					}
				}
				
			}			
		}

		ctx->fillPath();
	}

	void drawBackground( GraphicsContext* ctx ) {
		if ( NULL != background ) {
			ctx->drawImage( 0,0, background, false );

			ctx->renderImages(false);
		}
	}

	void drawGradient( GraphicsContext* ctx ) {
		Rect r = getClientBounds();

		Image* img = GraphicsToolkit::createImage( r.getWidth(), r.getHeight() );

		{
			ImageContext ictx = img;
			
			ictx->setAntiAliasingOn(true);
			
			VerticalGradientFill fill;
			fill.setColorValue( 0, Color("red") );
			fill.setColorValue( 1, Color("red") );

			fill.addColor( Color("yellow" ), 0.148 );
			fill.addColor( Color("lime" ), 0.258 );
			fill.addColor( Color("cyan" ), 0.428 );
			fill.addColor( Color("blue" ), 0.571 );
			fill.addColor( Color("purple" ), 0.714 );
			fill.addColor( Color("red" ), 0.857 );
			

			fill.setStart( r.top_ );
			fill.setEnd( r.bottom_ );
			
			
			ictx->setCurrentFill(&fill);
			
			BezierCurve curve;
			
			
			curve.rectangle( r );
			ictx->draw( &curve );
		}


		{
			ColorPixels pix = img;
			AlphaChannel alpha(pix);
			
			Image* alphaImg = alpha.createImage();
			{
				HorizontalGradientFill fill;
				
				fill.setColorLocation( 1, 0.848 );
				fill.setMidPoint( 0, 0.9 );				

				fill.setStart( r.left_ );
				fill.setEnd( r.right_ );
				
				ImageContext ictx = alphaImg;
				ictx->setAntiAliasingOn(true);
				ictx->setCurrentFill(&fill);
				
				BezierCurve curve;			
				
				curve.rectangle( r );
				ictx->draw( &curve );
			}
			alpha.updateFromImage( alphaImg );
			delete alphaImg;
		}



		ctx->drawImage( r.getTopLeft(), img, false );
		ctx->renderImages();
	}

	void drawEllipse( GraphicsContext* ctx ) {

		ctx->ellipse( modePt.x_ - 80, modePt.y_-50,
						modePt.x_ + 80, modePt.y_ + 50 );

		ctx->setColor( &modeFillColor );
		ctx->setCompositingMode( compMode );
		ctx->fillPath();

	}

	virtual void paint( GraphicsContext* ctx ) {		
		CustomControl::paint(ctx);

		drawCheckerboard( ctx );

		drawBackground( ctx );
		
		drawGradient( ctx );

		drawEllipse( ctx );
	}


	virtual void mouseDown( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			modePt = *e->getPoint();
			repaint();
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			modePt = *e->getPoint();
			repaint();
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			modePt = *e->getPoint();
			repaint();
		}
	}

	Point modePt;
	Color modeFillColor;
	GraphicsContext::CompositingMode compMode;

	//from http://www.flickr.com/photos/marc50/288161827/sizes/l/
	Image* background;
};


class CompositionTypesWindow : public Window {
public:
	CompositionTypesWindow() {}
	virtual ~CompositionTypesWindow(){};
};




_class_rtti_(CompositionsView, "VCF::CustomControl", "CompositionsView")
_class_rtti_end_

_class_rtti_(CompositionTypesWindow, "VCF::Window", "CompositionTypesWindow")
_class_rtti_end_





class CompositionTypesApplication : public Application {
public:

	CompositionTypesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(CompositionTypesWindow);
		REGISTER_CLASSINFO_EXTERNAL(CompositionsView);
		

		Window* mainWindow = Frame::createWindow( classid(CompositionTypesWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<CompositionTypesApplication>(argc,argv);
}


