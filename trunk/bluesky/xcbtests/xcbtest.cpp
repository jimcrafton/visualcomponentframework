#include "xcbtest.h"
#include "vcf/GraphicsKit/DrawUIState.h"
//compile with : g++ xcbtest.cpp -D_DEBUG -DVCF_XCB -Wno-multichar -frtti -fexceptions -I$VCF_ROOT/src -L$VCF_ROOT/bin -L$VCF_ROOT/lib -L/usr/local/lib -lFoundationKit_d -lGraphicsKit_d  -lxcb-image -lxcb-shm -lxcb -o xcbtest


struct RGBAs {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

using namespace VCF;

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

	

	Font f2;
	gc.setCurrentFont( &f2 );
	gc.getColor()->setAlpha( 1 );
	

	VCF::GraphicsContext* ctx = &gc;

	Rect r(0,0,400,400);

		r.inflate( -10, -10 );

		Rect btn = r;
		Rect textR = r;
		btn.right_ = btn.left_ + btn.getWidth()/2;
		btn.bottom_ = btn.top_ + 35;

		textR.left_ = btn.right_;
		textR.bottom_ = btn.bottom_;

		int32 options = GraphicsContext::tdoCenterHorzAlign |
							GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &textR, "Button Focus Rect", options );


		ctx->drawThemeButtonFocusRect( &btn );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Button Rect", options );

		ButtonState state;
		state.setEnabled( true );
		state.setFocused( false );
		state.setActive( true );

		state.buttonCaption_ = "A Button";
		ctx->drawThemeButtonRect( &btn, state, &btn );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Button Rect Pressed", options );

		state.setPressed(true);
		ctx->drawThemeButtonRect( &btn, state, &btn );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Button Rect Disabled", options );

		state.setPressed(false);
		state.setEnabled( false );
		ctx->drawThemeButtonRect( &btn, state, &btn );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Check box Rect", options );

		ButtonState cbState;
		cbState.setEnabled( true );
		cbState.setFocused( false );
		cbState.setActive( true );
		cbState.buttonCaption_ = "A Checkbox";

		ctx->drawThemeCheckboxRect( &btn, cbState );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Check box Rect toggled", options );

		cbState.setToggled( true );
		ctx->drawThemeCheckboxRect( &btn, cbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Check box Rect Disabled and toggled", options );

		cbState.setEnabled( false );
		ctx->drawThemeCheckboxRect( &btn, cbState );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Radio button Rect", options );

		ButtonState rbState;
		rbState.setEnabled( true );
		rbState.setFocused( false );
		rbState.setActive( true );
		rbState.buttonCaption_ = "A Radio button";

		ctx->drawThemeRadioButtonRect( &btn, rbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Radio box Rect toggled", options );

		rbState.setToggled( true );
		ctx->drawThemeRadioButtonRect( &btn, rbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Radio box Rect Disabled and toggled", options );

		rbState.setEnabled( false );
		ctx->drawThemeRadioButtonRect( &btn, rbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ButtonState cmboState;
		cmboState.setEnabled( true );
		cmboState.setFocused( false );
		cmboState.setActive( true );
		cmboState.buttonCaption_ = "A Combo Box";

		ctx->textBoundedBy( &textR, "Combo box Rect", options );
		ctx->drawThemeComboboxRect( &btn, cmboState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Combo box Rect Disabled", options );

		cmboState.setEnabled( false );
		ctx->drawThemeComboboxRect( &btn, cmboState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Combo box Rect Focused", options );

		cmboState.setEnabled( true );
		cmboState.setFocused( true );
		ctx->drawThemeComboboxRect( &btn, cmboState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ScrollBarState scrollState;
		scrollState.setEnabled( true );
		scrollState.setFocused( false );
		scrollState.setActive( true );
		scrollState.setButtonType( ScrollBarState::sbUpOrLeftBtn );

		ctx->textBoundedBy( &textR, "Scroll bar btn Rect", options );
		ctx->drawThemeScrollButtonRect( &btn, scrollState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		scrollState.setScrollBarIncrArrowPressed( true );
		ctx->textBoundedBy( &textR, "Scroll bar btn pressed Rect", options );
		ctx->drawThemeScrollButtonRect( &btn, scrollState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		scrollState.setEnabled( false );
		ctx->textBoundedBy( &textR, "Scroll bar btn disabled Rect", options );
		ctx->drawThemeScrollButtonRect( &btn, scrollState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );


		DisclosureButtonState disclState;
		disclState.setEnabled( true );
		disclState.setFocused( false );
		disclState.setActive( true );
		disclState.setClosed( true );
		disclState.setOpened( false );

		ctx->textBoundedBy( &textR, "Disclosure btn Rect - closed", options );
		ctx->drawThemeDisclosureButton( &btn, disclState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		disclState.setClosed( false );
		disclState.setOpened( true );
		ctx->textBoundedBy( &textR, "Disclosure btn Rect - open", options );
		ctx->drawThemeDisclosureButton( &btn, disclState );
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
