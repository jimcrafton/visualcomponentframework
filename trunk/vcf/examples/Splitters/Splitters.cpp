//Splitters.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#define USING_SPLITTER
#define NUM_OF_PANELS 5	 // 1-6


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;

class SplittersWindow;

class MyPanel : public Panel
{
public:
	MyPanel( SplittersWindow* mainWnd ) {
		mainWnd_ = mainWnd;
		MouseClicked += new ControlEventHandler<MyPanel>(this, &MyPanel::onMouseClicked, "MyPanel::onMouseClicked" );
	}

	SplittersWindow* getMainWindow() {
		return mainWnd_;
	}

	void onMouseClicked( ControlEvent* e );

public:
	SplittersWindow* mainWnd_;
};

class SplittersWindow : public Window {
public:
	SplittersWindow() {
		clickedPanel_ = NULL;
		panelVisible_ = true;

		setCaption( "Splitters" );

		ControlSized += new ControlEventHandler<SplittersWindow>(this, &SplittersWindow::onResized, "SplittersWindow::onResized" );
		ControlPositioned += new ControlEventHandler<SplittersWindow>(this, &SplittersWindow::onPosChanged, "SplittersWindow::onPosChanged" );

		Panel* buttonsPanel = new Panel();
		buttonsPanel->setUseColorForBackground( true );
		buttonsPanel->setHeight( 30 );
		buttonsPanel->setColor( Color::getColor("lightyellow") );
		add( buttonsPanel, AlignTop );


		btnShow_ = new CommandButton();
		btnShow_->ButtonClicked +=
			new ButtonEventHandler<SplittersWindow>(this,&SplittersWindow::onBtnShow, "SplittersWindow::onBtnShow");
		btnShow_->setBounds( 120, 2, 100, btnShow_->getPreferredHeight() );
		btnShow_->setCaption( "Hide" );
		btnShow_->setToolTipText( "Hide/Show any selected panel" );
		buttonsPanel->add( btnShow_, AlignLeft );

		Label* label = NULL;
		label = new Label();
		label->setWidth( 50 );
		label->setWordWrap( true );
		label->setCaption( "Click into a panel first and then press the Hide/Show button." );
		buttonsPanel->add( label, AlignClient );

		label = new Label();
		label->setHeight( 20 );
		label->setWordWrap( true );
		label->setCaption( "Drag a splitter to resize a panel - Try to DoubleClick on a splitter - Try then with the <Shift> key" );
		label->setColor( Color::getColor("blue") );
		add( label, AlignBottom );



		main_ = new Panel;
		main_->setHeight( 25 );
		main_->setUseColorForBackground( true );
		main_->setColor( Color::getColor("brown") );
		main_->setToolTipText( "main: AlignClient, brown" );
		add( main_, AlignClient );

		panelLeft_ = new Panel;
		panelLeft_->setUseColorForBackground( true );
		panelLeft_->setWidth( main_->getWidth()/2 );
		panelLeft_->setColor( Color::getColor("cyan") );
		panelLeft_->setToolTipText( "left: AlignLeft, cyan" );
		main_->add( panelLeft_, AlignLeft );

		panelRight_ = new Panel;
		panelRight_->setUseColorForBackground( true );
		panelRight_->setWidth( main_->getWidth()/2 );
		panelRight_->setColor( Color::getColor("navy") );
		panelRight_->setToolTipText( "right: AlignRight, navy" );
		main_->add( panelRight_, AlignRight );

		addPanels( panelLeft_ , NUM_OF_PANELS, AlignLeft );
		addPanels( panelRight_, NUM_OF_PANELS, AlignTop );
	}

	void addPanels( Panel* panel, int num, AlignmentType alignment  )
	{
		panel->setContainer( new StandardContainer() );

		int n = maxVal<int>( minVal<int>( num, NUM_OF_PANELS ), 1 );
		int width = panel->getWidth() / n;
		int height = panel->getHeight() / n;

		std::vector< String > colors;
		colors.push_back( "red" );
		colors.push_back( "green" );
		colors.push_back( "blue" );
		colors.push_back( "violet" );
		colors.push_back( "yellow" );
		colors.push_back( "gold" );

		String alignments[6];
		alignments[AlignNone]		= "AlignNone";
		alignments[AlignTop]		= "AlignTop";
		alignments[AlignLeft]		= "AlignLeft";
		alignments[AlignRight]	= "AlignRight";
		alignments[AlignBottom] = "AlignBottom";
		alignments[AlignClient] = "AlignClient";

		String s, sTip;
		Splitter* splitter = NULL;

		for ( int i = 1; i <= n; i ++ ) {
			MyPanel* p = new MyPanel( this );
			p->setUseColorForBackground( true );
			p->setWidth( width );
			p->setHeight( height );
			p->setColor( Color::getColor( colors[i-1] ) );
			p->setBorder( NULL );
			s = Format( "panel%d" ) % i;
			p->setName( s );
			if ( i < n ) {
				sTip = Format( "p%d: %s, %s" ) % i % alignments[alignment] % colors[i-1];
				p->setToolTipText( sTip );
				panel->add( p, alignment );

#ifdef USING_SPLITTER
				splitter = new Splitter( alignment );
				s = Format( "splitter %d" ) % i;
				splitter->setToolTipText( s );
				splitter->setToolTipText( s );
				splitter->setWidth( 5 );
				splitter->setMinimumWidth( 35 );
				splitter->setDblClickEnabled( true );
				panel->add( splitter, alignment );
#endif
			} else {
				sTip = Format( "p%d: %s, %s" ) % i % alignments[AlignClient] % colors[i-1];
				p->setToolTipText( sTip );
				panel->add( p, AlignClient );
			}
		}
	}

	virtual ~SplittersWindow(){};

	void onBtnHide( ButtonEvent* e ) {
		int i = 1;
		String s = Format( "panel%d" ) % i;
		//Panel* panel = (Panel*)panelLeft_->findComponent( s );
		if ( NULL != clickedPanel_ ) {
			clickedPanel_->setVisible( false );
			int x = 0;
		}
	}

	void onBtnShow( ButtonEvent* e ) {
		//String s = Format( "panel%d" ) % i ;
		//Panel* panel = (Panel*)panelLeft_->findComponent( s );
		if ( NULL != clickedPanel_ ) {
			panelVisible_ = !panelVisible_;
			clickedPanel_->setVisible( panelVisible_ );
			if ( panelVisible_ ) {
				clickedPanel_ = NULL;
				btnShow_->setCaption( "Hide" );
			} else {
				btnShow_->setCaption( "Show " + clickedPanel_->getName() );
			}
		} else {
			Dialog::showMessage( "Please, click on a window first." );
		}
	}

	void setClickedPanel( Panel* panel ) {
		if ( panelVisible_ ) {
			clickedPanel_ = panel;
		} else {
			Dialog::showMessage( "Please, press the show/hide button first" );
		}
	}
/*
	virtual void resizeChildren( Control* control ) {
		Window::resizeChildren( control );
	}
*/
	void onResized( ControlEvent*e ) {

		double w = main_->getWidth()/2;
		StringUtils::trace( Format("w: %0.2f\n") % w );

		panelLeft_->setWidth( w );

		panelRight_->setWidth( w );
	}

	void onPosChanged( ControlEvent*e ) {

	}

public:
	Panel* main_;
	Panel* panelLeft_;
	Panel* panelRight_;
	Panel* clickedPanel_;
	bool panelVisible_;
	CommandButton* btnShow_;
};

void MyPanel::onMouseClicked( ControlEvent* e ) {
	//Panel* panel = (Panel*)e->getSource();
	getMainWindow()->setClickedPanel( this );
	getMainWindow()->btnShow_->setCaption( "Hide " + getName() );
	//Rect r = getBounds();
	//trace( Format( "New Left/Top: %0.2f, %0.2f\n", r.left_, r.top_ );
}



class SplittersApplication : public Application {
public:

	SplittersApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new SplittersWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 700.0, 700.0 ) );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new SplittersApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.8  2006/04/07 02:34:42  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.7.2.2  2006/03/16 18:45:23  kdmix
*setVisible(true) removed from constructor of the main window.
*
*Revision 1.7.2.1  2005/07/23 21:45:42  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.6.2.3  2005/07/11 19:39:57  marcelloptr
*fixed all deprecated traceWithArgs(...) and format(...) calls
*
*Revision 1.6.2.2  2005/06/28 20:37:08  marcelloptr
*first step to remove flickering when dragging a splitter
*
*Revision 1.6.2.1  2005/04/17 15:11:47  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.6  2004/12/01 04:15:14  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.5.2.1  2004/10/07 15:03:35  kiklop74
*Fixed building issues with bcb
*
*Revision 1.5  2004/08/07 02:47:37  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.4.2.6  2004/07/11 22:54:03  ddiego
*fixed some miscellaneous examples
*
*Revision 1.4.2.5  2004/07/08 15:09:53  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.4.2.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


