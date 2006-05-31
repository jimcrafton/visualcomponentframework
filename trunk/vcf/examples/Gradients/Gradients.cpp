//Gradients.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/GradientFills.h"


#include "thirdparty/common/agg/include/agg_ellipse.h"
#include "thirdparty/common/agg/include/agg_bounding_rect.h"


using namespace VCF;


class Ellipse2 : public VCF::Object, public VCF::Path {
public:
	virtual void applyTransform( const Matrix2D& transform ) {
		agg::trans_affine mat = transform;
		agg::conv_transform< agg::path_storage > xfrmdPath(ellipsePath_,mat);

		ellipsePath_.remove_all();
		ellipsePath_.concat_path(xfrmdPath);
	}

	virtual bool contains( const Rect& rect) {
		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_curve<agg::path_storage> smooth(ellipsePath_);
		rasterizer.add_path( smooth );

		Point topLeft = rect.getTopLeft();
		Point bottomRight = rect.getTopLeft();

		return rasterizer.hit_test( (unsigned int)bottomRight.x_, (unsigned int)bottomRight.y_ ) && rasterizer.hit_test( (unsigned int)topLeft.x_, (unsigned int)topLeft.y_ );
	}

    virtual bool contains( const Point& pt ) {
		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_curve<agg::path_storage> smooth(ellipsePath_);
		rasterizer.add_path( smooth );

		return rasterizer.hit_test( (unsigned int)pt.x_, (unsigned int)pt.y_ );
	}

    virtual bool intersects( const Point& pt ) {
		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_curve<agg::path_storage> smooth(ellipsePath_);
		agg::conv_stroke<agg::conv_curve<agg::path_storage> >  stroke(smooth);
		stroke.width( 2 );

		rasterizer.add_path( stroke );
		return rasterizer.hit_test( (unsigned int)pt.x_, (unsigned int)pt.y_ );
	}

    virtual bool intersects( const Rect& rect ) {
		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_curve<agg::path_storage> smooth(ellipsePath_);
		rasterizer.add_path( smooth );
		
		if ( rasterizer.hit_test( (unsigned int)rect.left_, (unsigned int)rect.top_ ) ) {
			return true;
		}
		
		if ( rasterizer.hit_test( (unsigned int)rect.right_, (unsigned int)rect.top_ ) ) {
			return true;
		}
		
		if ( rasterizer.hit_test( (unsigned int)rect.right_, (unsigned int)rect.bottom_ ) ) {
			return true;
		}
		
		if ( rasterizer.hit_test( (unsigned int)rect.left_, (unsigned int)rect.bottom_ ) ) {
			return true;
		}
		
		return false;
	}

	virtual Rect getBounds() {
		Rect result;

		uint32 pid[1] = {0};

		agg::bounding_rect( ellipsePath_, pid, 0, 1,
						&result.left_, &result.top_,
						&result.right_, &result.bottom_ );

		return result;
	}

	virtual WindingRule getWindingRule() {
		return wrNonZero;
	}

	virtual void setWindingRule( WindingRule rule ) {

	}

	virtual bool getPoints( std::vector<PathPoint>& points, Matrix2D* transform ) {
		agg::trans_affine mat;
		if ( NULL != transform ) {
			mat = *transform;
		}
		agg::conv_transform< agg::path_storage > xfrmdPath(ellipsePath_,mat);
		
		for ( size_t i=0;i<ellipsePath_.total_vertices();i++ ) {
			PathPoint pt;
			unsigned vertCmd = xfrmdPath.vertex(&pt.point_.x_, &pt.point_.y_);
			switch ( vertCmd ) {
				case agg::path_cmd_move_to : {
					pt.type_ = PathPoint::ptMoveTo;
				}
				break;

				case agg::path_cmd_line_to : {
					pt.type_ = PathPoint::ptLineTo;
				}
				break;

				default : {
					if ( vertCmd & agg::path_flags_close ) {
						pt.type_ = PathPoint::ptClose;
					}
				}
				break;
			}

			points.push_back( pt );
		}


		return !points.empty();
	}

	virtual void flattenPoints( std::vector<Point>& flattenedPoints ) {

	}


	void ellipse( const Rect& bounds ) {
		agg::ellipse ellipseShape( bounds.left_ + bounds.getWidth()/2.0, 
									bounds.top_ + bounds.getHeight()/2.0,
									bounds.getWidth(), 
									bounds.getHeight(), 100 );

		ellipsePath_.rewind(0);
		ellipsePath_.remove_all();
		ellipsePath_.concat_path( ellipseShape );

	}
protected:
	agg::path_storage ellipsePath_;
};

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
		curve.rectangle( Rect(0,10,1000,90) );
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
		fill3.setEnd( 150 );
		fill3.setStart( 0 );
		fill3.setGradientMatrix( Matrix2D::translation(100, 410) );
		fill3.setColorValue( 0, Color("gold") );
		fill3.setColorValue( 1, Color("red") );

		ctx->setCurrentFill(&fill3);

		Ellipse2 el;
		el.ellipse( Rect(0,360,200,460) );

		ctx->draw(&el);
		


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


