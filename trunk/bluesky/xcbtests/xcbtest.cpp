#include "xcbtest.h"

//compile with : g++ xcbtest.cpp -D_DEBUG -DVCF_XCB -Wno-multichar -frtti -fexceptions -I$VCF_ROOT/src -L$VCF_ROOT/bin -L$VCF_ROOT/lib -L/usr/local/lib -lFoundationKit_d -lGraphicsKit_d  -lxcb-image -lxcb-shm -lxcb -o xcbtest




struct RGBAs {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};


void paint( xcb_gcontext_t* the_gc, xcb_window_t* the_window, xcb_image_t* the_image )
{
	VCF::XCBSurface surf;
	surf.context = the_gc;
	surf.drawable = the_window;
	surf.drawableImage = the_image;
	
	VCF::GraphicsContext gc( (VCF::OSHandleID) &surf );
	gc.setColor(&VCF::Color("blue"));

	gc.setStrokeWidth(5);
	gc.moveTo(20, 55);
	gc.lineTo(40, 60);
	gc.lineTo(20, 160);
	gc.strokePath();

	gc.getColor()->setAlpha( 0.2 );		    			
	gc.rectangle( &VCF::Rect(5,67,200,300));
	gc.setStrokeWidth(1);
	gc.fillPath();
	
	
	gc.setColor(&VCF::Color("red"));
	gc.getColor()->setAlpha( 1 );		    			
	gc.rectangle( &VCF::Rect(24,233,200,400));
	gc.setStrokeWidth(1);
	gc.fillPath();
	
	gc.getCurrentFont()->setPointSize( 23 );
	gc.getCurrentFont()->setItalic( true );
	gc.getCurrentFont()->setColor( &VCF::Color("black") );
	gc.textAt( 100, 300, "Hello World!" );
	
	gc.getCurrentFont()->setPointSize( 75 );
	gc.getCurrentFont()->setItalic( false );
	gc.getCurrentFont()->setName( "Arial" );
	VCF::Color c("orange");
	c.setAlpha( 0.55 );
	gc.getCurrentFont()->setColor( &c );
	gc.textAt( 75, 200, "Hello World 2!" );
}

int main( int argc, char** argv )
{

	VCF::GraphicsKit::init( argc, argv );

	XcbTest test(paint);
	int res = test.run();
    
    VCF::GraphicsKit::terminate();
    
    printf( "Goodbye!\n" );
    
	return res;
}
