//TextLayout.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Graphics4.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

/**
Thie will show some of the various text
options that are possible when drawing text
*/

class TextLayoutWindow : public Window {
public:
	TextLayoutWindow() {
		setCaption( "TextLayout" );

	}

	virtual ~TextLayoutWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );

		/**
		first we'll create 3 different fonts
		One with Times New Roman, in 16 point bold
		Another with Verdana, using the default font size, and bold
		And finally the third in Courier at 16 points
		*/

		Font font1;
		font1.setName( "Times New Roman" );
		font1.setPointSize( 16 );
		font1.setBold( true );

		Font font2;
		font2.setName( "Verdana" );
		font2.setItalic( true );

		Font font3;
		font3.setName( "Courier" );
		font3.setPointSize( 16 );



		/**
		Initial x and y coordinates for the text
		*/
		double x = 20;
		double y = 20;

		/**
		To change the GraphicsContext's font, make a call to
		GraphicsContext::setCurrentFont, passing in a pointer to
		the font. The passed in font will be copied over, so you
		do not have to hold on it.
		*/
		ctx->setCurrentFont( &font1 );

		/**
		Set the color of the context for line drawing
		*/
		ctx->setColor( Color::getColor( "black" ) );

		/**
		draw a horizontal line, showing where the top of the text will be drawn
		*/
		ctx->moveTo( x, y );
		ctx->lineTo( x + 600, y );
		ctx->strokePath();


		/**
		Now draw the text using the current font of the GraphicsContext
		*/
		ctx->textAt( x, y, "Text Example - " );

		/**
		Determine the text width. The GraphicsContext uses it's
		current font to determine this
		*/
		double width = ctx->getTextWidth( "Text Example - " );

		/**
		Now change the GraphicsContext's current to our second font
		*/
		ctx->setCurrentFont( &font2 );

		/**
		and draw our next chunk of text
		*/
		ctx->textAt( x + width, y, "all on a single line" );


		x = 20;
		y = 100;

		ctx->moveTo( x, y );
		ctx->lineTo( x + 600, y );
		ctx->strokePath();

		ctx->setCurrentFont( &font1 );

		/**
		The GraphicsContext::textWithStateAt draws text in either an enabled or disabled
		format, using the GraphicsContext's current font
		*/
		ctx->textWithStateAt( x, y, "Text Example - ", false );

		width = ctx->getTextWidth( "Text Example - " );

		ctx->setCurrentFont( &font2 );

		ctx->textWithStateAt( x + width, y, "all on a single line", true );


		y += 100;

		ctx->setCurrentFont( &font3 );

		/**
		Now we'll prepare to draw text using
		a Rect to specify the bounds that the text will be
		drawn within
		*/
		String text = "Text within bounds";
		Rect textBounds(x,y,x,y);

		/**
		This will mabe a rectangle that is the size of the text
		using the GraphicsContext's current font
		*/
		textBounds.right_ += ctx->getTextWidth( text );
		textBounds.bottom_ += ctx->getTextHeight( text );

		/**
		Draw the rectangle that encloses the text
		*/
		ctx->rectangle( textBounds );
		ctx->strokePath();

		/**
		Draw the text with x,y coordinates
		*/
		ctx->textAt( x, y, text );

		y += 100;

		textBounds.offset( 0, 100 );
		textBounds.right_ -= 50;
		textBounds.bottom_ += 100;

		ctx->rectangle( textBounds );
		ctx->strokePath();

		text = "Text within bounds, left aligned and word wrapped";

		/**
		Now draw the text using the rect's bounds. By default it will be word wrapped
		*/
		ctx->textBoundedBy( &textBounds, text );

		long drawingOptions = GraphicsContext::tdoCenterHorzAlign;

		ctx->setCurrentFont( &font2 );
		textBounds.offset( 350, -100 );
		textBounds.right_ += 100;
		textBounds.bottom_ -= 100;

		text = "Text within bounds, center aligned, single line";

		/**
		Now draw the text using the rect's bounds
		using the text drawing options specified in
		the drawingOptions variable
		*/
		ctx->textBoundedBy( &textBounds, text, drawingOptions );
		ctx->rectangle( textBounds );
		ctx->strokePath();

		textBounds.offset( 0, 50 );
		textBounds.right_ -= 50;

		text = "Clipped text within bounds, center aligned, single line";

		/**
		Draw the text but now that teh bounds have been shrunk, you'll see that
		the text becomes clipped
		*/
		ctx->textBoundedBy( &textBounds, text, drawingOptions );
		ctx->rectangle( textBounds );
		ctx->strokePath();


		textBounds.offset( 0, 50 );
		textBounds.right_ += 50;

		text = "Text within bounds, right aligned, single line";

		drawingOptions = GraphicsContext::tdoRightAlign;

		/**
		Draw the text with right alignment
		*/
		ctx->textBoundedBy( &textBounds, text, drawingOptions );
		ctx->rectangle( textBounds );
		ctx->strokePath();


		textBounds.offset( 0, 50 );
		textBounds.right_ += 50;
		textBounds.bottom_ += 100;

		text = "Text within bounds, left aligned, single line, centered vertically";

		drawingOptions = GraphicsContext::tdoCenterVertAlign;

		/**
		Draw the text and center it vertically
		*/
		ctx->textBoundedBy( &textBounds, text, drawingOptions );
		ctx->rectangle( textBounds );
		ctx->strokePath();


		x = textBounds.left_;
		y = textBounds.bottom_ + 50;


		textBounds.left_ = x;
		textBounds.top_ = y;


		ctx->moveTo( x, y );
		ctx->lineTo( x + 600, y );
		ctx->strokePath();


		drawingOptions = GraphicsContext::tdoBottomAlign;

		ctx->setCurrentFont( &font1 );
		textBounds.right_ = textBounds.left_ + ctx->getTextWidth( "Text Example - " );
		textBounds.bottom_ = textBounds.top_ + ctx->getTextHeight( "EM" );


		/**
		Draw the text and align it to the bottom of the bounds
		*/
		ctx->textBoundedBy( &textBounds, "Text Example - ", drawingOptions );


		ctx->setCurrentFont( &font2 );

		textBounds.left_ = textBounds.right_;
		textBounds.right_ = textBounds.left_ + ctx->getTextWidth( "all on a single line - bottom alignment" );


		ctx->textBoundedBy( &textBounds, "all on a single line - bottom alignment", drawingOptions );



		/**
		What follows shows you how to draw text that is aligned along a
		baseline
		*/

		x = 20;
		y = textBounds.top_ + 100;

		ctx->textAt( x, y -20, "The text below is aligned to the baseline, allowing for multiple fonts" );

		font1.setPointSize( 32 );

		ctx->setCurrentFont( &font1 );



		/**
		Generate the baseline. The baseline is determined by using the
		largest ascent in the series of font's you intend to use. In
		our case that's font1
		*/
		double baselineY = y + font1.getAscent() ;

		/**
		draw the baseline
		*/
		ctx->moveTo( x, baselineY );
		ctx->lineTo( x + 1000, baselineY );
		ctx->strokePath();


		/**
		draw the first part of the text
		*/
		ctx->textAt( x, y, "Text Example - " );

		/**
		nudge our x coordinate over by the width of the text we just drew
		*/
		x += ctx->getTextWidth( "Text Example - " );

		/**
		reset the y coordinate. It's new value is the baseline
		minus the ascent of the next font we are going to use
		*/
		y = baselineY - (font2.getAscent());

		/**
		set the next font
		*/
		ctx->setCurrentFont( &font2 );

		/**
		draw the text
		*/
		ctx->textAt( x, y, "all on a single line" );

		/**
		repeat ad infinitum...
		*/
		x += ctx->getTextWidth( "all on a single line" );

		ctx->setCurrentFont( &font3 );

		y = baselineY - (font3.getAscent());

		ctx->textAt( x, y, ", with even more Text!" );

		x += ctx->getTextWidth( ", with even more Text!" );

		font1.setColor( Color::getColor("red") );
		font1.setItalic( true );

		font1.setPointSize( 16 );

		ctx->setCurrentFont( &font1 );
		y = baselineY - (font1.getAscent());


		ctx->textAt( x, y, " And now in Technicolor :)" );

	}

};




class TextLayoutApp : public Application {
public:

	TextLayoutApp(int argc, char** argv) : Application(argc,argv){

	}
	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new TextLayoutWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 850.0, 700.0 );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TextLayoutApp( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2004/08/07 02:47:39  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.4.2.4  2004/04/29 03:40:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


