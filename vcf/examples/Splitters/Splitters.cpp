//Splitters.cpp

#define USING_SPLITTER
#define NUM_OF_PANELS 5	 // 1-6


#include "ApplicationKit.h"
#include "ControlsKit.h"

using namespace VCF;

class SplittersWindow;

class MyPanel : public Panel
{
public:
	MyPanel( SplittersWindow* mainWnd ) {
		mainWnd_ = mainWnd;
		MouseClicked += new ControlEventHandler<MyPanel>(this, MyPanel::onMouseClicked, "MyPanel::onMouseClicked" );
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
		setVisible( true );

		ControlSized += new ControlEventHandler<SplittersWindow>(this, SplittersWindow::onResized, "SplittersWindow::onResized" );
		ControlPositioned += new ControlEventHandler<SplittersWindow>(this, SplittersWindow::onPosChanged, "SplittersWindow::onPosChanged" );

		Panel* buttonsPanel = new Panel();
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
		main_->setColor( Color::getColor("brown") );
		main_->setToolTipText( "main: AlignClient, brown" );
		add( main_, AlignClient );

		panelLeft_ = new Panel;
		panelLeft_->setWidth( main_->getWidth()/2 );
		panelLeft_->setColor( Color::getColor("cyan") );
		panelLeft_->setToolTipText( "left: AlignLeft, cyan" );
		main_->add( panelLeft_, AlignLeft );

		panelRight_ = new Panel;
		panelRight_->setWidth( main_->getWidth()/2 );
		panelRight_->setColor( Color::getColor("navy") );
		panelRight_->setToolTipText( "right: AlignRight, navy" );
		main_->add( panelRight_, AlignRight );

		addPanels( panelLeft_ , NUM_OF_PANELS, AlignLeft );
		addPanels( panelRight_, NUM_OF_PANELS, AlignTop );
	}

	void addPanels( Panel* panel, int num, AlignmentType alignment  )
	{
		panel->setContainer( new FixedStandardContainer() );

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
			p->setWidth( width );
			p->setHeight( height );
			p->setColor( Color::getColor( colors[i-1] ) );
			p->setBorder( NULL );
			s = StringUtils::format( "panel%d", i );
			p->setName( s );
			if ( i < n ) {
				sTip = StringUtils::format( "p%d: %s, %s", i, alignments[alignment].c_str(), colors[i-1].c_str() );
				p->setToolTipText( sTip );
				panel->add( p, alignment );

#ifdef USING_SPLITTER
				splitter = new Splitter( alignment );
				s = StringUtils::format( "splitter %d", i );
				splitter->setToolTipText( s );
				splitter->setToolTipText( s );
				splitter->setWidth( 5 );
				splitter->setMinimumWidth( 35 );
				splitter->setDblClickEnabled( true );
				panel->add( splitter, alignment );
#endif
			} else {
				sTip = StringUtils::format( "p%d: %s, %s", i, alignments[AlignClient].c_str(), colors[i-1].c_str() );
				p->setToolTipText( sTip );
				panel->add( p, AlignClient );
			}
		}
	}

	virtual ~SplittersWindow(){};

	void onBtnHide( ButtonEvent* e ) {
		int i = 1;
		String s = StringUtils::format( "panel%d", i );
		//Panel* panel = (Panel*)panelLeft_->findComponent( s );
		if ( NULL != clickedPanel_ ) {
			clickedPanel_->setVisible( false );
			int x = 0;
		}
	}

	void onBtnShow( ButtonEvent* e ) {
		//String s = StringUtils::format( "panel%d", i );
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
		StringUtils::traceWithArgs( "w: %0.2f\n", w );

		panelLeft_->setWidth( w );

		w = main_->getWidth()/2;

		StringUtils::traceWithArgs( "w: %0.2f\n", w );

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
	//StringUtils::traceWithArgs( "New Left/Top: %0.2f, %0.2f\n", r.left_, r.top_ );
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
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new SplittersApplication( argc, argv );

	Application::main();
	
	return 0;
}


