//HeavyAndLight.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

/**
This example demonstrate the difference between light weight and heavy weight controls.
The basic idea to understand is that a heavy weight control represents a full native
windowing system control, and thus it has it's own set of resources (as specificed
by the underlying windowing system). In Win32 terms, this means that each heavyweight
control has it's HWND and HDC associated with it (as would an HWND that you create
in Win32). In linux systems that use GTK, this mean that each heavyweight control
has it's own GtkWidget (and it's associated GdkWindow handle). Thus heavyweight controls
receive user interface events directly from the windowing systems, where they are
caught by the VCF peer implementation(s), translated into VCF event's and then
dispatched to the VCF control.
In contrast, lightweight controls do NOT have their own windowing system control resources.
Instead they share these resources with the first heavyweight parent that contains the
lightweight control. The VCF takes care of simulating events to lightweight controls,
so from the perspective of the developer, the difference is basically non-existant.
*/


/**
A simple control class.
We derive from the CustomControl class, which is the
base class for all custom controls in the VCF.
*/
class LightWeightControl : public CustomControl {
public:

	/**
	Note that we pass in "false" to the CustomControl
	constructor, indicating that we are *not* a heavyweight
	control.
	*/
	LightWeightControl() : CustomControl(false) {
		Color color;
		//set the HLS color, where 240 is the color/hue (240 is Blue in a 360 color wheel)
		//and lightness is at 70% and saturation at 100%
		color.setHLS(240.0,0.7,1.0);

		//set the color for the control
		setColor( &color );
		setUseColorForBackground( true );

		//set transparency to false
		setTransparent(false);
	}

	virtual void paint( GraphicsContext* gc ) {
		CustomControl::paint( gc );

		//draw some text
		Rect bounds = getClientBounds();

		String text = "This is a lightweight Control!";
		double w = gc->getTextWidth( text );
		double h = gc->getTextHeight( text );

		double x = bounds.getWidth()/2 - w/2;
		double y = bounds.getHeight()/2 - h/2;
		gc->textAt( x, y, text );

		y += h;

		//draw the GraphicsContext's peer handler, in Win32 this is the
		//value of the HDC handle for the GraphicsContext
		text = StringUtils::format( "GraphicsContext's peer handle: 0x%08X", gc->getPeer()->getContextID() );
		gc->textBoundedBy(&Rect(0,y,bounds.getWidth(),y+h), text, false );

	}
};


/**
This is a heavyweight control. We still derive from CustomControl
but note that in the constructor we use the default constructor
for CustomControl, which creates a heavyweight control for us.
*/
class HeavyWeightControl : public CustomControl {
public:

	HeavyWeightControl() : CustomControl() {
		Color color;

		color.setHLS(60.0,0.5,1.0);

		//set the color for the control
		setColor( &color );
		setUseColorForBackground( true );
	}

	virtual void paint( GraphicsContext* gc ) {
		CustomControl::paint( gc );

		//draw some text
		Rect bounds = getClientBounds();

		String text = "This is a heavyweight Control!";
		double w = gc->getTextWidth( text );
		double h = gc->getTextHeight( text );

		double x = bounds.getWidth()/2 - w/2;
		double y = bounds.getHeight()/2 - h/2;
		gc->textAt( x, y, text );

		y += h;

		//draw the GraphicsContext's peer handler, in Win32 this is the
		//value of the HDC handle for the GraphicsContext
		text = StringUtils::format( "GraphicsContext's peer handle: 0x%08X", gc->getPeer()->getContextID() );
		gc->textBoundedBy(&Rect(0,y,bounds.getWidth(),y+h), text, false );
	}
};

class HeavyAndLightWindow : public Window {
public:
	HeavyAndLightWindow() {
		setCaption( "HeavyAndLight" );
		setVisible( true );


		EventHandler* ev = new MouseEventHandler<HeavyAndLightWindow>(this,&HeavyAndLightWindow::onCtrlMouseDown, "onCtrlMouseDown" );

		//create a light weight control
		LightWeightControl* control1 = new LightWeightControl();
		add( control1 );
		control1->setBounds( 20, 20, 350, 200 );
		control1->MouseDown += ev;
		control1->setName( "Control1" );



		//create a heavy weight control
		HeavyWeightControl* control2 = new HeavyWeightControl();
		add( control2 );
		control2->setBounds( 20, 250, 350, 200 );
		control2->MouseDown += ev;
		control2->setName( "Control2" );
	}

	virtual ~HeavyAndLightWindow(){};

	void paint( GraphicsContext* gc ) {
		Window::paint( gc );

		String text = StringUtils::format( "GraphicsContext's peer handle: 0x%08X", gc->getPeer()->getContextID() );

		gc->textAt( 0, 0, text );
	}

	void onCtrlMouseDown( MouseEvent* e ) {
		Control* c = (Control*)e->getSource();
		Dialog::showMessage( "Clicked on " + c->getName() );
	}
};




class HeavyAndLightApplication : public Application {
public:

	HeavyAndLightApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new HeavyAndLightWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new HeavyAndLightApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2004/08/07 02:47:04  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:54  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


