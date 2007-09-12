//Gradients.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/GradientFills.h"
#include "vcf/GraphicsKit/ShadowFill.h"




using namespace VCF;


void doLogo( GraphicsContext* ctx, Rect& logoRect )
{
	BezierCurve curve;

	BasicFill logoBack;
	logoBack.setColor( &Color(0.019,0.141,0.262) );
	ctx->setCurrentFill( &logoBack );
	
	VCF::Circle circ;
	circ.circle( logoRect.getCenter(), 42 );
	ctx->draw(&circ);		
	
	VerticalGradientFill logoGrad;
	logoGrad.setColorValue( 0, Color(0.568, 0.6196, 0.6745, 1.0 ) );
	logoGrad.setColorValue( 1, Color(0.0392, 0.1529, 0.2867, 1.0 ) );		
	logoGrad.setColorLocation( 1, 0.26 );
	logoGrad.setMidPoint( 0, 0.55 );
	
	logoGrad.addColor( Color(0.0941, 0.2235, 0.4235, 1.0 ), 0.67 );
	logoGrad.addColor( Color(0.2941, 0.6588, 0.8078, 1.0 ), 0.95 );
	
	logoGrad.setStart( logoRect.top_ );
	logoGrad.setEnd( logoRect.bottom_ );
	
	ctx->setCurrentFill( &logoGrad );
	circ.circle( logoRect.getCenter(), 41 );
	ctx->draw(&circ);		
}

void doLogoDropShadow( GraphicsContext* ctx, Rect logoRect )
{
	BezierCurve curve;
	ShadowFill logoDropShad;		
	logoDropShad.setAlpha( 1 );
	logoDropShad.setRadius(4);
	logoDropShad.setColor( Color("white") );
	
	ctx->setCurrentFill( &logoDropShad );
	
	logoRect.offset( 2, 2 );

	curve.clear();		
	curve.curve( logoRect.left_+25.5, logoRect.top_+17.5, 
		logoRect.left_+54,logoRect.top_+8.5, 
		logoRect.left_+47.25,logoRect.top_+32.5, 
		logoRect.left_+71.5,logoRect.top_+22 );
	
	curve.lineTo( logoRect.left_+59.5, logoRect.top_+64.5 );
	
	curve.curve( logoRect.left_+59.5,logoRect.top_+64.5, 
		logoRect.left_+34,logoRect.top_+75.25, 
		logoRect.left_+38.25,logoRect.top_+51.75, 
		logoRect.left_+13.5,logoRect.top_+59 );
	
	curve.lineTo( logoRect.left_+25.5, logoRect.top_+17.5 );
	
	curve.close();
	ctx->draw(&curve);
	
	ctx->setCurrentFill( NULL );	
}

class GradientsWindow : public Window {
public:
	GradientsWindow() {
		setCaption( "Gradients" );	
		setUsingRenderBuffer(true);
	}

	virtual ~GradientsWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint(ctx);

		BezierCurve curve;


		
		VCF::RadialGradientFill fill;
		ctx->setCurrentFill(&fill);
		
		curve.rectangle( Rect(0,10,100,90) );
		ctx->draw( &curve );

		VCF::HorizontalGradientFill fill2;
		ctx->setCurrentFill(&fill2);

		fill2.setStart(0);
		fill2.setEnd(200);

		curve.clear();
		curve.rectangle( Rect(0,100,200,190) );
		ctx->draw( &curve );

		fill2.setGradientMatrix( Matrix2D::scaling(0.78,1.0) * Matrix2D::rotation(10) );

		fill2.setMaxColorProfileSize( 128 );
		fill2.setAlpha( 0.5 );		

		curve.clear();
		curve.rectangle( Rect(0,200,200,290) );
		ctx->draw( &curve );


		fill2.setMaxColorProfileSize( 256 );
		fill2.setGradientMatrix( Matrix2D() );
		fill2.setAlpha( 0.60 );	
		fill2.setColorValue( 0, Color("yellow") );
		fill2.setMidPoint( 0, 0.23 );

		fill2.addColor( Color("blue"), 0.67 );

		fill2.setStart( 50 );
		fill2.setEnd( 250 );


		curve.clear();
		curve.rectangle( Rect(50,250,250,340) );
		ctx->draw( &curve );



		ConicGradientFill fill3;
		fill3.setGradientMatrix( Matrix2D::translation(100, 410) );
		fill3.setColorValue( 0, Color("gold") );
		fill3.setColorValue( 1, Color("red") );

		ctx->setCurrentFill(&fill3);

		VCF::Ellipse el;
		el.ellipse( Rect(0,360,200,460) );

		ctx->draw(&el);


		ctx->setCompositingMode( GraphicsContext::cmScreen );
		
		fill3.setGradientMatrix( Matrix2D::translation(350, 410) );

		VCF::Circle circ;
		circ.circle( Point(350,410),100 );
		ctx->draw(&circ);


		ctx->setCompositingMode( GraphicsContext::cmSource );


		VerticalGradientFill fill4a;

		fill4a.setColorValue( 0, Color(0.2627, 0.2784, 0.3215, 1.0 ) );
		fill4a.setColorValue( 1, Color(0.2980, 0.2980, 0.2980, 1.0 ) );		
		fill4a.setColorLocation( 1, 0.98 );
		
		fill4a.addColor( Color(0.2313, 0.2413, 0.2745, 1.0 ), 0.37 );
		fill4a.addColor( Color(0.1843, 0.1882, 0.1882, 1.0 ), 0.41 );
		fill4a.addColor( Color(0.2352, 0.2352, 0.2352, 1.0 ), 0.95 );

		fill4a.setMidPoint( 0, 0.5 );
		fill4a.setMidPoint( 0, 0.14 );
		fill4a.setMidPoint( 0, 0.76 );
		fill4a.setMidPoint( 0, 0.2 );

		fill4a.setStart( 300 );
		fill4a.setEnd( 325 );

		ctx->setCurrentFill(&fill4a);

		curve.clear();
		curve.rectangle( Rect(300,300,450,325) );
		ctx->draw( &curve );

		Font f;
		f.setColor( &Color("white") );
		f.setName( "Tahoma" );
		f.setPointSize( 11 );
		ctx->setCurrentFont( &f );
		ctx->textBoundedBy( &Rect(315,305,435,325), "Office 2007", false );



		VerticalGradientFill fill4b;
		fill4b.setColorValue( 0, Color(0.7803, 0.7764, 0.7803, 1.0 ) );
		fill4b.setColorValue( 1, Color(0.2745, 0.3058, 0.3490, 1.0 ) );		
		fill4b.setColorLocation( 1, 0.98 );
		
		fill4b.addColor( Color(0.6901, 0.6901, 0.6901, 1.0 ), 0.39 );
		fill4b.addColor( Color(0.6039, 0.6078, 0.6078, 1.0 ), 0.41 );

		fill4b.setMidPoint( 0, 0.5 );
		fill4b.setMidPoint( 0, 0.95 );
		fill4b.setMidPoint( 0, 0.69 );

		fill4b.setStart( 250 );
		fill4b.setEnd( 285 );

		ctx->setCurrentFill(&fill4b);


		curve.clear();
		curve.rectangle( Rect(300,250,450,285) );
		ctx->draw( &curve );

		
		f.setColor( &Color("black") );
		f.setName( "Tahoma" );
		f.setPointSize( 11 );
		f.setBold(true);
		ctx->setCurrentFont( &f );
		ctx->textBoundedBy( &Rect(315,258,435,280), "Office 2007", false );


		ctx->setCurrentFill(NULL);

		ctx->setCompositingMode( GraphicsContext::cmOverlay );

		BasicStroke stroke;

		ctx->setCurrentStroke( &stroke );

		stroke.setWidth( 12 );
		stroke.setColor( &Color("purple") );
		
		curve.clear();

		ctx->setMiterLimit( 1.2 );
		ctx->setLineCapStyle( GraphicsContext::lcsSquareCap );
		ctx->setLineJoinStyle( GraphicsContext::ljsMiterJoin );

		curve.moveTo( 400, 400 );
		curve.lineTo( 500, 400 );
		curve.lineTo( 450, 600 );
		curve.lineTo( 380, 380 );
		ctx->draw( &curve );

		ctx->setCurrentStroke( NULL );
		ctx->setCompositingMode( GraphicsContext::cmSource );


		ctx->setCompositingMode( GraphicsContext::cmColorDodge );

		BasicFill bf;

		ctx->setCurrentFill( &bf );

		bf.setColor( &Color("blue") );
		
		curve.clear();

		
		curve.rectangle( Rect(500,400,600,500) );

		ctx->draw( &curve );

		ctx->setCurrentFill( NULL );
		ctx->setCompositingMode( GraphicsContext::cmSource );	


		//ctx->setRotation( 10 );

		ShadowFill shadow;
		ctx->setCurrentFill( &shadow );
		shadow.setAlpha( 0.9863 );
		shadow.setRadius( 16 );

		curve.clear();

		Rect rect(mousePt.x_ - 100,mousePt.y_ - 50,mousePt.x_ + 100,mousePt.y_ + 50);
		curve.rectangle( rect );
		ctx->draw( &curve );

		rect.offset( -3, -3 );

		//ctx->setColor( &Color("blue") );
		//ctx->rectangle( &rect );
		//ctx->fillPath();

		ctx->setCurrentFill( NULL );
		ctx->setCompositingMode( GraphicsContext::cmSource );
	



		Image* logo = GraphicsToolkit::createImage( "logo.png" );
		Rect logoRect(300,100,385,184);

		doLogo( ctx, logoRect );


		logoRect.offset( 100, 0 );

		doLogo( ctx, logoRect );
		ctx->drawImage( logoRect.getTopLeft(), logo, false );
		ctx->renderImages();

		logoRect.offset( 100, 0 );
		doLogoDropShadow( ctx, logoRect );


		logo = GraphicsToolkit::createImage( "logo.png" );
		logoRect.offset( 100, 0 );

		doLogo( ctx, logoRect );
		doLogoDropShadow( ctx, logoRect );
		
		ctx->drawImage( logoRect.getTopLeft(), logo, false );
		ctx->renderImages();
/*

		ShadowFill logoDropShad;		
		logoDropShad.setAlpha( 1 );
		logoDropShad.setRadius( 0 );
		//logoDropShad.setColor( &Color("black") );

		ctx->setCurrentFill( &logoDropShad );


		logoRect.offset( -100, -logoRect.top_ );

		
		curve.clear();		
		curve.curve( logoRect.left_+25.5, logoRect.top_+17.5, 
						logoRect.left_+54,logoRect.top_+8.5, 
						logoRect.left_+47.25,logoRect.top_+32.5, 
						logoRect.left_+71.5,logoRect.top_+22 );
		curve.lineTo( logoRect.left_+59.5, logoRect.top_+64.5 );
		curve.curve( logoRect.left_+59.5,logoRect.top_+64.5, 
						logoRect.left_+34,logoRect.top_+75.25, 
						logoRect.left_+38.25,logoRect.top_+51.75, 
						logoRect.left_+13.5,logoRect.top_+59 );
		curve.close();
		ctx->draw(&curve);
*/

		logoRect.offset( 100, 0 );

		//logoRect.setRect(0,0,0,0);

		//Matrix2D m;
		//m *= Matrix2D::translation( -10, -40 );
		//ctx->setCurrentTransform( m );

		BasicFill bf2;		
		bf2.setColor( &Color("black") );

		ctx->setCurrentFill( &bf );
		curve.clear();		
		curve.curve( logoRect.left_+25.5, logoRect.top_+17.5, 
						logoRect.left_+54,logoRect.top_+8.5, 
						logoRect.left_+47.25,logoRect.top_+32.5, 
						logoRect.left_+71.5,logoRect.top_+22 );
		curve.lineTo( logoRect.left_+59.5, logoRect.top_+64.5 );
		curve.curve( logoRect.left_+59.5,logoRect.top_+64.5, 
						logoRect.left_+34,logoRect.top_+75.25, 
						logoRect.left_+38.25,logoRect.top_+51.75, 
						logoRect.left_+13.5,logoRect.top_+59 );
		curve.close();
		ctx->draw(&curve);


		/*
		Image* gri = GraphicsToolkit::createImage( 100, 100, Image::itGrayscale );
		
		{
			ImageContext ictx = gri;

			ictx->setColor(&Color("white"));
			ictx->circle( 20, 20, 20 );
			ictx->fillPath();

			Image* im = GraphicsToolkit::createImage( 100, 100 );
			{
				ImageContext ictx2 = im;
				ictx2->setRenderArea(Rect(0,0,100,100));
				//ictx2->setViewableBounds( Rect(0,0,100,100) );

				Circle c;
				c.circle(Point(20,20),20);
				BasicFill b;
				b.setColor(&Color("blue"));
				ictx2->setCurrentFill(&b);
				ictx2->draw(&c);

				//ictx2->bitBlit( 0, 0, ictx2->getRenderArea() );
				//ctx->bitBlit( 500, 300, ictx2->getRenderArea() );
				//ictx->bitBlit( 50, 50, ictx2->getRenderArea() );


				ictx2->flushRenderArea();
				
			}

			//ctx->bitBlit( 500, 300, im );
			

			ictx->bitBlit( 50, 50, im );

			delete im;
		}

		ctx->drawImage( 300, 100, gri );

		delete gri;
		*/


		ctx->setCurrentFill( NULL );


	}


	virtual void mouseMove( MouseEvent* e ) {
		Window::mouseMove(e);
		if ( e->hasLeftButton() ) {
			mousePt = *e->getPoint();
			repaint();
		}
	}

	virtual void mouseDown( MouseEvent* e ) {
		Window::mouseDown(e);
		if ( e->hasLeftButton() ) {
			mousePt = *e->getPoint();
			repaint();
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		Window::mouseUp(e);
		if ( e->hasLeftButton() ) {
			mousePt = *e->getPoint();
			repaint();
		}
	}

	Point mousePt;
};




class GradientsApplication : public Application {
public:

	GradientsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new GradientsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new GradientsApplication( argc, argv );

	Application::main();
	
	return 0;
}


