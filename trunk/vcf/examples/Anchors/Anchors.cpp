//Anchors.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"


using namespace VCF;

/**
This example will deomstrate how to use anchors with controls.
This example will only use the CommandButton and Panel controls
to demonstrate this, but you can use anchors with *any* control
in the framework.

One note: for acnhors to work, the control parent's container 
*must* implement an algorithm that takes advantage of this. The 
default container used by any control that support's containers
*does*, in fact, implement this support, so if you are simply using 
the default settings this will not be a problem. If, however,
you explicitly set the container to something else, then you may 
get different behaviour.
*/

class AnchorsWindow : public Window {
public:
	AnchorsWindow() {
		setCaption( "Anchors" );
		setVisible( true );

		/**
		note: we must have the width (or height) set 
		to some value PRIOR to adding the child controls that will
		be anchored in it.
		*/
		setWidth( 500 );
		setHeight( 500 );

		Rect bounds = getClientBounds();

		CommandButton* btn1 = new CommandButton();
		//set the initial bounds for the button
		btn1->setBounds( 20, 20, bounds.getWidth() - 40, btn1->getPreferredHeight() );

		/**
		set the anchor - the anchor can be any combination of AnchorLeft, AnchorRight,
		AnchorTop, or AnchorBottom, or it can be set to AnchorNone, to indicate that
		no anchoring layout is to be performed for the control. AnchorNone is the 
		default anchor value for all controls.
		*/
		btn1->setAnchor( AnchorLeft | AnchorRight );
		btn1->setCaption( "Button with anchor set to: AnchorLeft | AnchorRight" );
		add( btn1 );


		TextControl* text = new TextControl();
		text->setBounds( 100, 70, 300, text->getPreferredHeight() );
		text->getTextModel()->setText( "Text with anchor set to: AnchorRight" );

		text->setAnchor( AnchorRight );

		add( text );



		//add a panel and set it's bounds to take up some of the remain client space
		Panel* panel = new Panel();
		panel->setBounds( 20, 200, bounds.getWidth() - 40, bounds.getHeight() - (200 + 20) );

		//now set the anchor to all sides, left,top,right, and bottom - this will
		//resize the panel to accordingly
		panel->setAnchor( AnchorLeft | AnchorRight | AnchorTop | AnchorBottom );
		panel->setColor( Color::getColor("blue") );

		add( panel );

	}

	virtual ~AnchorsWindow(){};

};




class AnchorsApplication : public Application {
public:

	AnchorsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new AnchorsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	AnchorsApplication app( argc, argv );

	Application::main();
	
	return 0;
}


