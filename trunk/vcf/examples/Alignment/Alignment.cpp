//Alignment.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;

/**
This example will introduce the basics of working with alignments.
The example will demonstrate how to align by client, top, left, right,
bottom. We'll make use of both heavyweight and lighweight containers.
For a further information on lightweight vs. heavyweight controls,
please see the documentation, or the HeavyAndLight example.
This example will use Panel controls for simplicity, but same techniques can
be used with any control.
*/


class LightWeightControl : public ControlContainer {
public:
	LightWeightControl(): ControlContainer(false){}


};



class AlignmentWindow : public Window {
public:


	AlignmentWindow() {
		setCaption( "Alignment" );


		//first we create a Panel, this will hold the other controls
		//we don't have to do this - this is strictly to have a control
		//that is aligned as a AlignClient
		Panel* main = new Panel();
		add( main, AlignClient );
		main->setToolTipText( "main panel" );

		//create a new container  - agina, by default we do not have top do this
		//as a panel already has a container instance. Setting it here will destroy
		//the previous one
		StandardContainer* container = new StandardContainer();

		//set the border width
		container->setBorderWidth( 10 );

		//set the container. Settings the container will delete and replace the previous one
		//if one was already set
		main->setContainer( container );


		/**
		Now lets add a bunch of child controls - each one a panel, each one a
		different color. Notice that the order the control is added IS retained
		as the parent control is resized.
		*/
		/**
		The first set will be aligned to the bottom. This means that the original height of the
		control is maintained, but the left and right sides are controlled by the parent,
		making the child control's width changed as the parent is resized.
		*/
		Panel* p1 = new Panel();
		p1->setHeight( 20 );
		p1->setUseColorForBackground( true );
		main->add( p1, AlignBottom );
		p1->setColor( Color::getColor("yellow") );
		p1->setToolTipText( "p1: AlignBottom, yellow" );

		Panel* p2 = new Panel();
		p2->setHeight( 5 );
		p2->setUseColorForBackground( true );
		main->add( p2, AlignBottom );
		p2->setColor( Color::getColor("blue") );
		p2->setToolTipText( "p2: AlignBottom, blue" );

		Panel* p3 = new Panel();
		p3->setHeight( 20 );
		p3->setUseColorForBackground( true );
		main->add( p3, AlignBottom );
		p3->setColor( Color::getColor("red") );
		p3->setToolTipText( "p3: AlignBottom, red" );

		/**
		These two  control are aligned to the left. This will maintain the controls
		width, but alter the height to match that of the parent.
		*/
		Panel* p4 = new Panel();
		p4->setWidth( 23 );
		p4->setUseColorForBackground( true );
		main->add( p4, AlignLeft );
		p4->setColor( Color::getColor("white") );
		p4->setToolTipText( "p4: AlignLeft, white" );


		Panel* p4a = new Panel();
		p4a->setWidth( 50 );
		p4a->setUseColorForBackground( true );
		main->add( p4a, AlignLeft );
		p4a->setColor( Color::getColor("gold") );
		p4a->setToolTipText( "p4a: AlignLeft, gold" );



		Panel* p5 = new Panel();
		p5->setWidth( 45 );
		p5->setUseColorForBackground( true );
		main->add( p5, AlignRight );
		p5->setColor( Color::getColor("green") );
		p5->setToolTipText( "p5: AlignRight, green" );

		Panel* p5a = new Panel();
		p5a->setWidth( 45 );
		p5a->setUseColorForBackground( true );
		main->add( p5a, AlignRight );
		p5a->setColor( Color::getColor("pink") );
		p5a->setToolTipText( "p5a: AlignRight, pink" );


		Panel* p6 = new Panel();
		p6->setHeight( 25 );
		p6->setUseColorForBackground( true );
		main->add( p6, AlignTop );
		p6->setColor( Color::getColor("black") );
		p6->setToolTipText( "p6: AlignTop, black" );


		/**
		Now we add a lightweight control that *also* holds a
		container - this means you can have container that are *not*
		heavy weight controls, and cuts down on resources a bit.
		*/
		LightWeightControl* clientControl = new LightWeightControl();

		/**
		add the control aligned as a client.
		A control that is client aligned will take up any remain space left
		after the bounds for left, top, right, and bottom aligned controls
		have been calculated (using a standard container - other custom
		container may enforce their own layout algorithms).
		*/
		main->add( clientControl, AlignClient );
		clientControl->setBorderSize( 20 );
		clientControl->setToolTipText( "clientControl: AlignClient" );

		Panel* clientP1 = new Panel();
		clientP1->setHeight( 25 );
		clientP1->setToolTipText( "clientControl/clientP1: AlignTop" );
		clientControl->add( clientP1, AlignTop );

		Label* label1 = new Label();
		label1->setHeight( 35 );
		label1->setColor( Color::getColor("white") );
		label1->setTransparent( false );
		label1->setWordWrap( true );
		label1->setCaption( "This is Label 1" );
		label1->setToolTipText( "clientControl/label1: AlignTop, white" );
		clientControl->add( label1, AlignTop );



		Label* label2 = new Label();
		label2->setHeight( 75 );
		label2->setColor( Color::getColor("gray158") );
		label2->setTransparent( false );
		label2->setWordWrap( true );
		label2->setCaption( "This is Label 2, Aligned to the Bottom!" );
		label2->setVerticalAlignment( tvaTextBottom );
		label2->setToolTipText( "clientControl/label2: AlignBottom, gray158" );
		clientControl->add( label2, AlignBottom );		
		
	}

	virtual ~AlignmentWindow(){};

};




class AlignmentApplication : public Application {
public:

	AlignmentApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new AlignmentWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &VCF::Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new AlignmentApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2004/08/07 02:46:55  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.7  2004/07/11 22:53:45  ddiego
*fixed some miscellaneous examples
*
*Revision 1.3.2.6  2004/07/09 03:39:27  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*

*Revision 1.3.2.5  2004/07/08 15:09:18  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.3.2.4.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.3.2.4  2004/04/29 03:40:51  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


