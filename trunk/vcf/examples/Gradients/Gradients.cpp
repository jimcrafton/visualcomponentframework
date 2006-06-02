//Gradients.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/GradientFills.h"



using namespace VCF;


class GradientsWindow : public Window {
public:
	GradientsWindow() {
		setCaption( "Gradients" );	
		setUsingRenderBuffer(true);
	}

	virtual ~GradientsWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint(ctx);

		VCF::RadialGradientFill fill;
		ctx->setCurrentFill(&fill);
		BezierCurve curve;
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


		curve.clear();
		curve.rectangle( Rect(0,250,200,340) );
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

		ctx->setCompositingMode( GraphicsContext::cmMultiply );

		BasicStroke stroke;

		ctx->setCurrentStroke( &stroke );

		stroke.setWidth( 12 );
		stroke.setColor( &Color("purple") );
		
		curve.clear();

		curve.moveTo( 400, 400 );
		curve.lineTo( 500, 400 );
		curve.lineTo( 450, 600 );
		curve.lineTo( 380, 380 );
		ctx->draw( &curve );

		ctx->setCurrentStroke( NULL );
		ctx->setCompositingMode( GraphicsContext::cmSource );


		ctx->setCompositingMode( GraphicsContext::cmOverlay );

		BasicFill bf;

		ctx->setCurrentFill( &bf );

		bf.setColor( &Color("blue") );
		
		curve.clear();

		curve.rectangle( Rect(500,400,600,500) );

		ctx->draw( &curve );

		ctx->setCurrentFill( NULL );
		ctx->setCompositingMode( GraphicsContext::cmSource );

	}

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


