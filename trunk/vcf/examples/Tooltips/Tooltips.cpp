//Tooltips.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/ApplicationKit/TextPeer.h"

using namespace VCF;

class Cooltip : public Panel {
public:
	Cooltip() {
		setBorder( NULL );
		setBorderSize( 1 );

		MultilineTextControl* edit = new MultilineTextControl();
		edit->setBorder( NULL );

		edit->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP ) );
		edit->setTextWrapping(false);

		edit->getFont()->setPointSize( 12 );		
		edit->getFont()->setName( "Times New Roman" );

		String text = "Tooltip Help\nThis is some help for this cool tooltip.\nIt's in multiple styles!";
		edit->getTextModel()->setText( text );

		Dictionary styles;
		styles [ Text::fsBold ] = true;
		styles [ Text::fsPointSize ] = 14.0;
		styles [ Text::fsFontName ] = "Arial";
		styles [ Text::psAlignment ] = Text::paCenter;
		styles [ Text::fsColor ] = Color::getColor("blue");
		edit->setStyle( 0, 12, styles );

		styles.clear();
		styles [ Text::fsItalic ] = true;
		styles [ Text::fsColor ] = Color::getColor("red");
		edit->setStyle( text.size()-25, 24, styles );
		
		add( edit, AlignClient );	
	}

};

class TooltipsWindow : public Window {
public:
	TooltipsWindow() {
		setCaption( "Tooltips" );

		setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		Panel* p1 = new Panel();

		HorizontalLayoutContainer* hlc = new HorizontalLayoutContainer();
		hlc->setNumberOfColumns(1);

		p1->setContainer( hlc );

		CheckBoxControl* cb1 = new CheckBoxControl();
		cb1->ToolTip += 
			new ToolTipEventHandler<TooltipsWindow>(this,&TooltipsWindow::onToolTipCB1, "TooltipsWindow::onToolTipCB1" );

		cb1->setToolTipText( "This is a tooltip from check box 1 - see my background color!" );
		cb1->setCaption( "This is a check box" );
		p1->add( cb1 );

		CheckBoxControl* cb2 = new CheckBoxControl();
		cb2->ToolTip += 
			new ToolTipEventHandler<TooltipsWindow>(this,&TooltipsWindow::onToolTipCB2, "TooltipsWindow::onToolTipCB2" );

		cb2->setCaption( "And another checkbox" );
		cb2->setToolTipText( "Yet another tip!" );
		p1->add( cb2 );

		p1->setHeight( 80 );
		add( p1, AlignTop );

		MultilineTextControl* tc = new MultilineTextControl();
		
		tc->setToolTipText( "null" );
		tc->ToolTip += 
			new ToolTipEventHandler<TooltipsWindow>(this,&TooltipsWindow::onToolTip, "TooltipsWindow::onToolTip" );
		add( tc, AlignClient );

	}

	virtual ~TooltipsWindow(){};

	void onToolTipCB1( ToolTipEvent* e ) {
		e->setBackgroundColor( Color::getColor("green") );
	}

	void onToolTipCB2( ToolTipEvent* e ) {
		
	}

	void onToolTip( ToolTipEvent* e ) {
		e->setToolTipSize( &Size(200, 100) );
		Cooltip* cooltip = new Cooltip();

		e->setAutoDestroyEmbeddedControl( true );
		e->setEmbeddedControl( cooltip );
	}
};




class TooltipsApplication : public Application {
public:

	TooltipsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new TooltipsWindow();
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TooltipsApplication( argc, argv );

	Application::main();
	
	return 0;
}


