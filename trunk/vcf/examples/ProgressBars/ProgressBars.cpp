//ProgressBars.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;


class ProgressBarsWindow : public Window {
public:
	ProgressBarsWindow() {
		setCaption( "ProgressBars" );
		setWidth( 500 );
		setHeight( 500 );

		Rect bounds = getClientBounds();

		ProgressControl* progressHorzFast_ = new ProgressControl();		
		progressHorzFast_->setBounds( 20, 20, bounds.getWidth()-40, progressHorzFast_->getPreferredHeight() );
		progressHorzFast_->setStepItIncrement( 10 );
		progressHorzFast_->setPosition( 20 );
		progressHorzFast_->setAnchor( AnchorLeft | AnchorRight );
		progressHorzFast_->setDisplayProgressText( false );
		add( progressHorzFast_ );


		ProgressControl* progressHorz_ = new ProgressControl();
		progressHorz_->setBounds( 20, 50, bounds.getWidth()-40, 30 );		

		progressHorz_->setStepItIncrement( 1 );

		progressHorz_->setPosition( 20 );
		progressHorz_->setAnchor( AnchorLeft | AnchorRight );
		add( progressHorz_ );

		progressHorz_->setUseProgressFormatString( true );
		progressHorz_->setProgressFormatString( "Percent done: %0.3f %%" );
		progressHorz_->setDisplayProgressText( true );
		progressHorz_->getFont()->setPointSize( 8.0 );
		progressHorz_->getFont()->setBold( true );
		progressHorz_->getFont()->setColor( Color::getColor("blue") );


		ProgressControl* progressVert_ = new ProgressControl();
		progressVert_->setDisplayAlignment( ProgressControl::paVertical );

		progressVert_->setBounds( 20, progressHorz_->getBottom() + 40,
									progressVert_->getPreferredWidth()+30, 250 );

		progressVert_->setPosition( 65 );
		progressVert_->setAnchor( AnchorTop | AnchorBottom );
		add( progressVert_ );

		progressVert_->setDisplayProgressText( true );





		ProgressControl* progressVert2 = new ProgressControl();
		progressVert2->setDisplayAlignment( ProgressControl::paVertical );

		progressVert2->setBounds( progressVert_->getRight() + 10,
									progressVert_->getTop(),
									progressVert2->getPreferredWidth(), 250 );

		progressVert2->setPosition( 12 );
		progressVert2->setAnchor( AnchorTop | AnchorBottom );
		add( progressVert2 );

		progressVert2->setStepItIncrement( 5 );

		progressVert2->setProgressBarColor( Color::getColor("gold") );


		TimerComponent* tc = new TimerComponent();
		tc->TimerPulse += new ClassProcedure1<TimerEvent*,ProgressBarsWindow>( this, &ProgressBarsWindow::onTimer, "ProgressBarsWindow::onTimer" );
		tc->setTimeoutInterval( 33 );
		tc->setActivated( true );
		addComponent( tc );

	}

	virtual ~ProgressBarsWindow(){};

	void onTimer( TimerEvent* e ) {

		Enumerator<Control*>* children = getChildren();
		while ( children->hasMoreElements() ) {
			ProgressControl* pc = dynamic_cast<ProgressControl*>( children->nextElement() );
			if ( NULL != pc ) {
				if ( pc->getPosition() >= pc->getMaxValue() ) {
					pc->setPosition( pc->getMinValue() );
				}
				else {
					pc->stepIt();
				}
			}
		}
	}
};




class ProgressBarsApplication : public Application {
public:

	ProgressBarsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new ProgressBarsWindow();
		setMainWindow(mainWindow);
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ProgressBarsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
$Id$
*/
