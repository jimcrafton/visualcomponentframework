//Labels.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"

using namespace VCF;

/**
This example demostrates how to use labels
*/

class LabelsWindow : public Window {
public:
	LabelsWindow() {
		setCaption( "Labels" );
		
		setWidth( 500 );
		setHeight( 700 );

		Rect clientBounds = getClientBounds();
		double y = 20;

		/**
		Make a single label, with text along one line
		*/
		Label* label1 = new Label();
		label1->setCaption( "This is a single line, left aligned label" );
		label1->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, label1->getPreferredHeight() );
		add( label1 );
		label1->setAnchor( AnchorLeft | AnchorRight );

		y = label1->getBottom() + 10;

		/**
		This changes the horizontal alignment - this is accomplished 
		by the label2->setTextAlignment( taTextRight ) call
		which will change the alignment to right aligned text.
		*/
		Label* label2 = new Label();
		label2->setCaption( "This is a single line, right aligned label" );
		label2->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, label2->getPreferredHeight() );
		add( label2 );
		label2->setAnchor( AnchorLeft | AnchorRight );
		label2->setTextAlignment( taTextRight );

		y = label2->getBottom() + 10;

		/**
		This centers the text, and gives the background color of the control a 
		red color. Again, setTextAlignment() changes the alignment, and calling
		setColor() and passing a color instance, will change the lables color.
		Please note: the label (and any control for that matter) maintains it's 
		own copy of a Color object - therefore it is safe to pass in temporary
		or stack based color instances. When setting the color of a control,
		if the control is lightweight, you need to turn ther control's transparent
		flag off. Thus the call to label3->setTransparent( false ).
		*/
		Label* label3 = new Label();
		label3->setCaption( "This is a single line, centered aligned label, with a red background" );
		label3->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, label3->getPreferredHeight() );
		add( label3 );
		label3->setAnchor( AnchorLeft | AnchorRight );
		label3->setTextAlignment( taTextCenter );
		label3->setColor( Color::getColor( "red" ) );
		label3->setTransparent( false );

		y = label3->getBottom() + 10;


		/**
		This one changes the font, fairly straight forward.
		We also change the vertical alignment. This is accomplished with 
		a call to setVerticalAlignment(). Vertical alignment default to 
		top, and can be changed to top, center, or bottom (tvaTextTop,
		tvaTextCenter, and tvaTextBottom, respectively)
		*/
		Label* label4 = new Label();
		label4->setCaption( "This is a single line, bold, italic, centered aligned, and vertically centered label, with a gold background" );
		label4->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, label4->getPreferredHeight() );
		add( label4 );
		label4->setAnchor( AnchorLeft | AnchorRight );
		label4->setTextAlignment( taTextCenter );
		
		label4->setVerticalAlignment( tvaTextCenter );

		label4->setColor( Color::getColor( "gold" ) );
		label4->setTransparent( false );
		label4->getFont()->setName( "Arial" );
		label4->getFont()->setBold( true );
		label4->getFont()->setItalic( true );
		label4->getFont()->setPointSize( label4->getFont()->getPointSize() + 6 );

		y = label4->getBottom() + 10;

		/**
		This aligns text at the bottom of the label, using setVerticalAlignment()
		and passing in tvaTextBottom.
		*/
		Label* label5 = new Label();
		label5->setCaption( "This is a single line, centered aligned, and vertical bottom aligned label, with a gray background" );
		label5->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, label5->getPreferredHeight() + 40 );
		add( label5 );
		label5->setAnchor( AnchorLeft | AnchorRight );
		label5->setTextAlignment( taTextCenter );
		
		label5->setVerticalAlignment( tvaTextBottom );

		label5->setColor( Color::getColor( "gray125" ) );
		label5->setTransparent( false );


		y = label5->getBottom() + 10;

		/**
		Sets a disabled label - the labels text should show up as grayed out.
		*/
		Label* label6 = new Label();
		label6->setCaption( "This is a single line, DISABLED, left aligned, and vertically centered label" );
		label6->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, label6->getPreferredHeight() );
		add( label6 );
		label6->setAnchor( AnchorLeft | AnchorRight );		
		
		label6->setVerticalAlignment( tvaTextCenter );

		label6->setEnabled( false );

		y = label6->getBottom() + 10;

		/**
		This sets the label to allow for multiple lines - the change is made by calling
		setWordWrap() - pass in true and you have a word wrapping multi line lable, 
		pass in false and the behaviour reverts to displaying a single line of text
		*/
		Label* label7 = new Label();
		label7->setCaption( "This is a multi line, left aligned, bordered, label, with lots of ridiculous text that pontificates the pompous bogosity of the inferior mammossity of partial differential equations." );
		label7->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, 100 );
		add( label7 );
		label7->setAnchor( AnchorLeft | AnchorRight );
		
		label7->setWordWrap( true );
		
		label7->setBorder( new Light3DBorder() );


		y = label7->getBottom() + 10;


		/**
		This shows how hot keys (like Alt+ <some character>) can be associated with a label,
		and how that label can pass along the focus request to it's "buddy" control.
		Setting the "buddy" is done via a call to setFocusControl(). The hot key
		(or mnemonic) is set by setting the caption of the label and including the "&"
		character in the text.
		*/
		Label* label8 = new Label();
		label8->setCaption( "This next label will test using mnemonics. When you click Alt+L (the mnemonic for the label) it will set focus to it's focus control, the edit box" );
		label8->setBounds( clientBounds.left_ + 20, y, clientBounds.getWidth()-40, 100 );
		add( label8 );
		label8->setAnchor( AnchorLeft | AnchorRight );				
		label8->setWordWrap( true );

		label8->getFont()->setName( "Verdana" );
		label8->getFont()->setPointSize( 18 );

		y = label8->getBottom() + 10;


		/**
		*/
		Label* label9 = new Label();
		label9->setCaption( "Text &Label:" );
		label9->setBounds( clientBounds.left_ + 20, y, 80, label9->getPreferredHeight() );
		add( label9 );		
		
		label9->setVerticalAlignment( tvaTextCenter );


		TextControl* text = new TextControl();

		text->setBounds( label9->getRight() + 10, y, 200, text->getPreferredHeight() );
		add( text ); 
		text->getTextModel()->setText( "Hello World !" );

		label9->setFocusControl( text );


	}

	virtual ~LabelsWindow(){};

};




class LabelsApplication : public Application {
public:

	LabelsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new LabelsWindow();
		setMainWindow(mainWindow);
		mainWindow->show();
		
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new LabelsApplication( argc, argv );

	Application::main();
	
	return 0;
}


