//Combos.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;

class CombosApplication : public Application {
public:
	CombosApplication( int argc, char** argv ): Application(argc, argv) {	}

	virtual bool initRunningApplication();
};

class MainWindow : public Window {
public:
	MainWindow(CombosApplication* app);
	virtual ~MainWindow() {	}

	void onSetComboItemCount( ButtonEvent* event );
	void setComboItemCount();

	void onSetDropDownCount( ButtonEvent* event );
	void setDropDownCount();

	void onSetDropDownWidth( ButtonEvent* event );
	void setDropDownWidth();

	void onSetDropDownExtendFullScreen( ButtonEvent* event );
	void updateDropDownExtendFullScreen();

	void onSetDiscreteScroll( ButtonEvent* event );
	void updateDiscreteScroll();

public:
	VCF::TextControl* edic_;
	VCF::TextControl* eddc_;
	VCF::TextControl* eddw_;
	ComboBoxControl* cb_;
	CheckBoxControl* chkDropDownExtendFullScreen_;
	CheckBoxControl* chkDiscreteScroll_;
	int itemCount_;
	int dropDownCount_;
	int dropDownWidth_;
	bool dropDownExtendFullScreen_;
	bool discreteScroll_;
};

MainWindow::MainWindow(CombosApplication* app)
{
	setBounds( &Rect( 100.0, 100.0, 480.0, 450.0 ) );

	Panel* p = new Panel();
	add( p , AlignClient );

	itemCount_ = 10;
	dropDownExtendFullScreen_ = false;
	discreteScroll_ = true; // for a combo and any listbox it should be true by default 

	cb_ = new ComboBoxControl();
	cb_->setBounds( &Rect(250, 50, 350, cb_->getPreferredHeight()) );
	//cb->addItem( "Item 1" );
	cb_->setVisible( true );
	cb_->setComboBoxStyle( cbsDropDownWithEdit );
	cb_->setDropDownCount( 200 );
	add( cb_ );

	VCF::CommandButton* btn;
	CallBack* bh;

	eddc_ = new TextControl();
	eddc_->setBounds( 25, 20, 45, eddc_->getPreferredHeight() );
	eddc_->setVisible( true );
	eddc_->setToolTipText( "dropdown count for the combo" );
	add( eddc_ );

	btn = new CommandButton();

	btn->setCaption( "Set DropDown Count" );
	btn->setBounds ( 100, 20, btn->getPreferredWidth(), btn->getPreferredHeight() );	
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDropDownCount, "MainWindow::onSetDropDownCount" );
	btn->ButtonClicked += bh;
	add( btn );


	edic_ = new TextControl();
	edic_->setBounds( 25, 75, 45, edic_->getPreferredHeight() );
	edic_->setVisible( true );
	edic_->setToolTipText( "number of items in the combo" );
	add( edic_ );

	btn = new CommandButton();

	btn->setCaption( "Set Items count" );
	btn->setBounds ( 100, 75, btn->getPreferredWidth(), btn->getPreferredHeight() );	
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetComboItemCount, "MainWindow::onSetComboItemCount" );
	btn->ButtonClicked += bh;
	add( btn );


	eddw_ = new TextControl();
	eddw_->setBounds( 25, 125, 45, eddw_->getPreferredHeight() );
	eddw_->setVisible( true );
	eddw_->setToolTipText( "dropdown width for the combo" );
	add( eddw_ );

	btn = new CommandButton();

	btn->setCaption( "Set DropDown Width" );
	btn->setBounds ( 100, 125, btn->getPreferredWidth(), btn->getPreferredHeight() );
	
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDropDownWidth, "MainWindow::onSetDropDownWidth" );
	btn->ButtonClicked += bh;
	add( btn );


	chkDropDownExtendFullScreen_ = new CheckBoxControl();
	chkDropDownExtendFullScreen_->setCaption( "DropDown List Extend to full screen" );
	chkDropDownExtendFullScreen_->setToolTipText( "allow the dropdown list of the combo to extend to the full screen" );
	chkDropDownExtendFullScreen_->setBounds ( &Rect(25, 175, 225, 200) );
	chkDropDownExtendFullScreen_->setTabStop( true );
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDropDownExtendFullScreen, "MainWindow::onSetDropDownExtendFullScreen" );
	chkDropDownExtendFullScreen_->ButtonClicked += bh;
	add( chkDropDownExtendFullScreen_ );


	chkDiscreteScroll_ = new CheckBoxControl();
	chkDiscreteScroll_->setCaption( "Scrolling by discrete amounts" );
	chkDiscreteScroll_->setToolTipText( "allow the dropdown list of the combo to be scrolled only by discrete quantities" );
	chkDiscreteScroll_->setBounds ( &Rect(25, 215, 225, 240) );
	chkDiscreteScroll_->setTabStop( true );
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDiscreteScroll, "MainWindow::onSetDiscreteScroll" );
	chkDiscreteScroll_->ButtonClicked += bh;
	add( chkDiscreteScroll_ );
}

void MainWindow::onSetComboItemCount( ButtonEvent* event )
{
	setComboItemCount();
}

void MainWindow::setComboItemCount()
{
	String s;

	s = edic_->getTextModel()->getText();
	itemCount_ = StringUtils::fromStringAsInt( s );

	cb_->setSelectedItem( NULL );	// bugfix ! otherwise it crashes when emptying the model
	cb_->getViewModel()->empty(); // cb_->getListModel()->empty(); is obsolete

	for (int i=0; i < itemCount_; i++) {
		s = Format( "item %d")% (i+1);
		cb_->addItem( s );
	}
}

void MainWindow::onSetDropDownCount( ButtonEvent* event )
{
	setDropDownCount();
}

void MainWindow::setDropDownCount()
{
	String s;

	s = eddc_->getTextModel()->getText();
	dropDownCount_ = StringUtils::fromStringAsInt( s );

	cb_->setDropDownCount( dropDownCount_ );	// bugfix ! otherwise it crashes when emptying the model
}

void MainWindow::onSetDropDownWidth( ButtonEvent* event )
{
	setDropDownWidth();
}

void MainWindow::setDropDownWidth()
{
	String s;

	s = eddw_->getTextModel()->getText();
	dropDownWidth_ = StringUtils::fromStringAsInt( s );

	cb_->setDropDownWidth( dropDownWidth_ );
}

void MainWindow::onSetDropDownExtendFullScreen( ButtonEvent* event )
{
	dropDownExtendFullScreen_ = !dropDownExtendFullScreen_;
	updateDropDownExtendFullScreen();
}

void MainWindow::updateDropDownExtendFullScreen()
{
	cb_->setDropDownExtendFullScreen( dropDownExtendFullScreen_ );	// bugfix ! otherwise it crashes when emptying the model
	chkDropDownExtendFullScreen_->setChecked( dropDownExtendFullScreen_ );
}

void MainWindow::onSetDiscreteScroll( ButtonEvent* event )
{
	discreteScroll_ = !discreteScroll_;
	updateDiscreteScroll();
}

void MainWindow::updateDiscreteScroll()
{
	cb_->setDiscreteScroll( discreteScroll_ );
	chkDiscreteScroll_->setChecked( discreteScroll_ );
}

bool CombosApplication::initRunningApplication(){
	bool result = Application::initRunningApplication();
	
	MainWindow* mainWindow = new MainWindow(this);
	setMainWindow(mainWindow);
	
	mainWindow->setCaption( "Combos !" );
	mainWindow->eddc_->getTextModel()->setText( "130" );
	mainWindow->edic_->getTextModel()->setText( "135" );
	mainWindow->eddw_->getTextModel()->setText( "0" );
	ButtonEvent be( mainWindow, 0 );	// is it correct to use mask = 0 ?
	mainWindow->onSetDropDownCount( &be );
	mainWindow->onSetComboItemCount( &be );
	mainWindow->updateDropDownExtendFullScreen();
	mainWindow->updateDiscreteScroll();
	mainWindow->show();

	return result;
}

int main(int argc, char *argv[])
{
	Application* app = new CombosApplication( argc, argv );

	Application::main();
	
	return 0;
}


