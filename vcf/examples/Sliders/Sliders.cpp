//Sliders.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"

using namespace VCF;

/**
This example show how to add slider controls
*/
class SlidersWindow : public Window {
public:
	SlidersWindow() {
		setCaption( "Sliders" );
		setWidth( 500 );
		setHeight( 500 );

		Rect r = getClientBounds();

		double y = 20;

		Label* label = new Label();

		label->setBounds( 20, y, r.getWidth()-40, label->getPreferredHeight() );
		label->setAnchor( AnchorLeft|AnchorRight);		
		label->setCaption( "Slider 1 position: " );
		label->setName( "Label1" );
		add( label );


		y = label->getBottom() + 20;



		SliderControl* slider = new SliderControl();
		slider->setBounds( 20, y, r.getWidth()-40, slider->getPreferredHeight() );
		
		slider->setAnchor( AnchorLeft|AnchorRight);

		slider->setTickMarkStyle( SliderControl::tmsTopLeft );

		add( slider );
		slider->setPosition( slider->getMaxValue() );

		slider->PositionChanged += 
			new GenericEventHandler<SlidersWindow>( this, &SlidersWindow::onSliderPositionChanged, "SlidersWindow::onSliderPositionChanged" );

		

		y = slider->getBottom() + 20;


		slider = new SliderControl();
		slider->setBounds( 20, y, r.getWidth()-40, slider->getPreferredHeight() );
		
		slider->setAnchor( AnchorLeft|AnchorRight);

		slider->setTickMarkStyle( SliderControl::tmsBottomRight );

		add( slider );


		y = slider->getBottom() + 20;


		slider = new SliderControl();
		slider->setBounds( 20, y, r.getWidth()-40, slider->getPreferredHeight() );
		
		slider->setAnchor( AnchorLeft|AnchorRight);

		slider->setTickFrequency( 5 );

		slider->setMaxValue( 60 );
		slider->setMinValue( 10 );

		slider->setTickMarkStyle( SliderControl::tmsBottomRight | SliderControl::tmsTopLeft );

		add( slider );


		y = slider->getBottom() + 20;
		double x = 20;


		slider = new SliderControl();
		slider->setDisplayOrientation( SliderControl::doVertical );
		slider->setBounds( x, y, slider->getPreferredWidth(), 200 );
		
		slider->setAnchor( AnchorTop|AnchorBottom);
		slider->setTickMarkStyle( SliderControl::tmsBottomRight );

		add( slider );

		x = slider->getRight() + 20;


		slider = new SliderControl();
		slider->setDisplayOrientation( SliderControl::doVertical );
		slider->setBounds( x, y, slider->getPreferredWidth(), 200 );
		
		slider->setAnchor( AnchorTop|AnchorBottom);
		slider->setTickMarkStyle( SliderControl::tmsTopLeft );

		add( slider );

		x = slider->getRight() + 20;



		slider = new SliderControl();
		slider->setDisplayOrientation( SliderControl::doVertical );
		slider->setBounds( x, y, slider->getPreferredWidth(), 200 );
		
		slider->setAnchor( AnchorTop|AnchorBottom);
		slider->setTickMarkStyle( SliderControl::tmsBottomRight | SliderControl::tmsTopLeft );

		slider->setTickFrequency( 25 );

		add( slider );

		x = slider->getRight() + 20;


		//slider->setEnabled( false );
	}

	virtual ~SlidersWindow(){};

	void onSliderPositionChanged( Event* e ) {
		Label* label = (Label*)findComponent( "Label1" );
		SliderControl* slider = (SliderControl*)e->getSource();
		label->setCaption( StringUtils::format( "Slider1 position: %0.3f", slider->getPosition() ) );
	}
};




class SlidersApplication : public Application {
public:

	SlidersApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new SlidersWindow();
		setMainWindow(mainWindow);
		mainWindow->show();

		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new SlidersApplication( argc, argv );


	Application::main();
	
	return 0;
}



