//Help.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"


using namespace VCF;

class MyDialog : public Dialog {
public:
	MyDialog() {

		setWidth( 350 );
		setHeight( 150 );

		Panel* pane1 = new Panel();
		pane1->setBorder( NULL );

		HorizontalLayoutContainer* container = new HorizontalLayoutContainer();		
		pane1->setContainer( container );

		

		Label* lable1 = new Label();
		lable1->setCaption( "Name:" );
		pane1->add( lable1 );

		TextControl* edit1 = new TextControl();
		//set your what's this help description here.
		edit1->setWhatThisHelpString( "Type in your name here." );

		pane1->add( edit1 );


		Label* lable2 = new Label();
		lable2->setCaption( "Are you Mergatroid?:" );
		pane1->add( lable2 );

		CheckBoxControl* checkBox = new CheckBoxControl();
		checkBox->setCaption( "Yes I am!" );
		
		//set your what's this help description here.
		checkBox->setWhatThisHelpString( "This indicates whether or not you're a Mergatroid. \nThink carefully before answering." );

		pane1->add( checkBox );

		add( pane1, AlignClient );

		CommandButton* okBtn = new CommandButton();

		Panel* bottom = new Panel();
		bottom->setBorder( NULL );

		bottom->setHeight( okBtn->getPreferredHeight() + UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta) * 2 );
		

		HorizontalLayoutContainer* container2 = new HorizontalLayoutContainer();
		container2->setLeftBorderWidth( getWidth() / 2.0 );	

		double width = getWidth() / 2.0;
		width -= UIToolkit::getUIMetricValue(UIMetricsManager::mtContainerBorderDelta);
		width -= container2->getColumnTweenWidth( 0 );

		container2->setColumnWidth( 0, width / 2.0 );
		
		bottom->setContainer( container2 );


		
		
		bottom->add( okBtn );

		CommandButton* cancelBtn = new CommandButton();
		bottom->add( cancelBtn );

		okBtn->setCaption( "OK" );
		okBtn->setCommandType ( BC_OK );
		okBtn->setDefault(true);
		okBtn->setWhatThisHelpString( "Click this to accept the changes and close the dialog!" );

		cancelBtn->setCaption( "Cancel" );
		cancelBtn->setCommandType ( BC_CANCEL );
		cancelBtn->setWhatThisHelpString( "Click this close the dialog without relaying any information to the SSDC*!\n\n\n\t*Super Secret Decoder Club" );

		add( bottom, AlignBottom );

		edit1->setFocused();

		setCaption( "Mergatroid Questionaire" );
	}
};


class HelpWindow : public Window {
public:
	

	HelpWindow() {
		setCaption( "Help" );

		CommandButton* showHelpContents = new CommandButton();

		showHelpContents->setBounds( 20, 20, 150, showHelpContents->getPreferredHeight() );
		showHelpContents->setCaption( "Help Contents" );
		showHelpContents->setWhatThisHelpString( "This displays the help contents." );
		add( showHelpContents );

		CommandButton* showHelpIndex = new CommandButton();

		showHelpIndex->setBounds( 20, 70, 150, showHelpIndex->getPreferredHeight() );
		showHelpIndex->setCaption( "Help Index" );
		add( showHelpIndex );

		PopupMenu* whatsThisMenu = new PopupMenu(this);
		DefaultMenuItem* whatsThis = new DefaultMenuItem("What's this?", whatsThisMenu->getRootMenuItem(), whatsThisMenu );
		whatsThis->MenuItemClicked += new ClassProcedure1<Event*,HelpWindow>( this, &HelpWindow::whatsThisHelp, "HelpWindow::whatsThisHelp" );

		whatsThis->setData( showHelpContents );

		showHelpContents->setPopupMenu( whatsThisMenu );


		showHelpContents->ButtonClicked += new ClassProcedure1<Event*,HelpWindow>( this, &HelpWindow::showContents, "HelpWindow::showContents" );
		showHelpIndex->ButtonClicked += new ClassProcedure1<Event*,HelpWindow>( this, &HelpWindow::showIndex, "HelpWindow::showIndex" );
		


		CommandButton* showDlg = new CommandButton();
		showDlg->setBounds( 20, 120, 150, showDlg->getPreferredHeight() );
		showDlg->setCaption( "Show Dialog..." );
		showDlg->ButtonClicked += 
			new ClassProcedure1<Event*,HelpWindow>( this, &HelpWindow::showDialog, "HelpWindow::showDialog" );

		add( showDlg );

		



		Basic3DBorder* b = new Basic3DBorder(this);

		Panel* p = new Panel();
		p->setBorder( NULL );
		p->setHeight( 300 ) ;
		add( p, AlignBottom );

		l1 = new Label();
		l1->setBorder( b );
		l1->setCaption( "Deep Thoughts" );
		l1->setHeight( 25 );
		l1->getFont()->setName( "Times New Roman" );
		l1->getFont()->setPointSize( 15 );
		l1->setToolTipText( "Press F1 now, simpering fool!" );
		p->add( l1, AlignTop );


		l2 = new Label();
		l2->setBorder( b );
		l2->setCaption( "Trifectic Distemper?" );
		l2->setHeight( 50 );
		l2->getFont()->setName( "Arial" );
		l2->getFont()->setBold( true );
		l2->getFont()->setItalic( true );
		l2->getFont()->setPointSize( 35 );
		l2->setToolTipText( "I'm not kidding, press F1 now!" );
		p->add( l2, AlignTop );

		l3 = new Label();
		l3->setBorder( b );
		l3->setCaption( "Figure 1" );
		l3->setHeight( 50 );
		l3->getFont()->setName( "Courier New" );
		l3->getFont()->setPointSize( 13 );
		l3->getFont()->setColor( Color::getColor("green") );
		l3->setVerticalAlignment( tvaTextBottom );
		l3->setTextAlignment( taTextRight );
		l3->setToolTipText( "OK, I'm kidding, but press F1 anyways!" );

		p->add( l3, AlignTop );


		l4 = new Label();
		l4->setBorder( b );
		l4->setCaption( "The End!" );
		l4->setHeight( 80 );
		l4->getFont()->setName( "Courier New" );
		l4->getFont()->setPointSize( 56 );
		l4->getFont()->setColor( Color::getColor("blue") );
		l4->setVerticalAlignment( tvaTextBottom );
		l4->setTextAlignment( taTextCenter );
		l4->setToolTipText( "Please press F1 anyways, or I shall destroy Alderann!" );

		p->add( l4, AlignBottom );

		//grab the context help notifications!

		HelpRequested += 
			new ClassProcedure1<Event*,HelpWindow>(this,&HelpWindow::onContextHelp, "HelpWindow::onContextHelp" );
	}

	Label* l1;
	Label* l2;
	Label* l3;
	Label* l4;

	virtual ~HelpWindow(){};

	void showDialog( Event* e ) {
		MyDialog dialog;

		dialog.showModal();
	}


	void onContextHelp( Event* e ) {
		HelpEvent* he = (HelpEvent*)e;

		Point pt = UIShell::getUIShell()->getCurrentMousePosition();

		Rect r = l1->getBounds();
		l1->getParent()->translateToScreenCoords(&r);
		if ( r.containsPt( &pt ) ) {

			he->helpSection = "index.html#Complex";

			return;
		}

		r = l2->getBounds();
		l2->getParent()->translateToScreenCoords(&r);
		if ( r.containsPt( &pt ) ) {

			he->helpSection = "index.html#figure1";

			return;
		}

		r = l3->getBounds();
		l3->getParent()->translateToScreenCoords(&r);
		if ( r.containsPt( &pt ) ) {

			he->helpSection = "index.html#fig1expl";

			return;
		}

		r = l4->getBounds();
		l4->getParent()->translateToScreenCoords(&r);
		if ( r.containsPt( &pt ) ) {

			he->helpSection = "index.html#yada";

			return;
		}
	}

	void showContents( Event* e ) {
		UIToolkit::displayHelpContents();
	}

	void showIndex( Event* e ) {
		UIToolkit::displayHelpIndex();
	}

	void whatsThisHelp( Event* e ) {
		MenuItem* item = (MenuItem*)e->getSource();
		
		UIToolkit::displayContextHelpForControl( (Control*)item->getData() );
	}

};




class HelpApplication : public Application {
public:

	HelpApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){

		bool result = Application::initRunningApplication();

		setName( "Help App" );

		Window* mainWindow = new HelpWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
	
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new HelpApplication( argc, argv );

	Application::main();
	
	return 0;
}


