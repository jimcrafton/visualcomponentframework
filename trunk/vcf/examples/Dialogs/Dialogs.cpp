//Dialogs.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"


using namespace VCF;

/**
This example demonstrates how to use dialogs
*/


/**
This demonstrates how to create a very simple 
dialog complete with OK/Cancel buttons, and  
horizontal layout that takes into consideration 
the proper (as specified in the UI metrics for the
platform) horizontal and vertial spacing between 
controls.
*/
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
		
		pane1->add( edit1 );


		Label* lable2 = new Label();
		lable2->setCaption( "Are you Mergatroid?:" );
		pane1->add( lable2 );

		CheckBoxControl* checkBox = new CheckBoxControl();
		checkBox->setCaption( "Yes I am!" );
		pane1->add( checkBox );

		add( pane1, AlignClient );

		CommandButton* okBtn = new CommandButton();

		Panel* bottom = new Panel();
		bottom->setBorder( NULL );

		UIMetricsManager* metrics = UIToolkit::getUIMetricsManager();		

		bottom->setHeight( okBtn->getPreferredHeight() + metrics->getPreferredSpacingFor(UIMetricsManager::stContainerBorderDelta) * 2 );
		

		HorizontalLayoutContainer* container2 = new HorizontalLayoutContainer();
		container2->setLeftBorderWidth( getWidth() / 2.0 );	

		double width = getWidth() / 2.0;
		width -= metrics->getPreferredSpacingFor(UIMetricsManager::stContainerBorderDelta);
		width -= container2->getColumnTweenWidth( 0 );

		container2->setColumnWidth( 0, width / 2.0 );
		
		bottom->setContainer( container2 );


		
		bottom->add( okBtn );

		CommandButton* cancelBtn = new CommandButton();
		bottom->add( cancelBtn );

		okBtn->setCaption( "OK" );
		okBtn->setCommandType ( BC_OK );
		okBtn->setDefault(true);

		cancelBtn->setCaption( "Cancel" );
		cancelBtn->setCommandType ( BC_CANCEL );

		add( bottom, AlignBottom );

		edit1->setFocused();

		setCaption( "Mergatroid Questionaire" );
	}
};



class DialogsWindow : public Window {
public:
	DialogsWindow() {
		setCaption( "Dialogs" );
		setVisible( true );


		CommandButton* btn1 = new CommandButton();
		btn1->setBounds( 10, 20, 175, btn1->getPreferredHeight() );
		btn1->setCaption( "Dialog::showMessage 1" );
		btn1->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example1, "DialogsWindow::example1" );
		add( btn1 );


		CommandButton* btn2 = new CommandButton();
		btn2->setBounds( 10, btn1->getBottom() + 20, 175, btn2->getPreferredHeight() );
		btn2->setCaption( "Dialog::showMessage 2" );
		btn2->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example2, "DialogsWindow::example2" );
		add( btn2 );


		CommandButton* btn3 = new CommandButton();
		btn3->setBounds( 10, btn2->getBottom() + 20, 175, btn3->getPreferredHeight() );
		btn3->setCaption( "Show custom dialog" );
		btn3->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example3, "DialogsWindow::example3" );
		add( btn3 );

		CommandButton* btn4 = new CommandButton();
		btn4->setBounds( 10, btn3->getBottom() + 20, 175, btn4->getPreferredHeight() );
		btn4->setCaption( "Show Common Font Dialog" );
		btn4->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example4, "DialogsWindow::example4" );
		add( btn4 );

		CommandButton* btn5 = new CommandButton();
		btn5->setBounds( 10, btn4->getBottom() + 20, 175, btn4->getPreferredHeight() );
		btn5->setCaption( "Show Common Color Dialog" );
		btn5->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example5, "DialogsWindow::example5" );
		add( btn5 );

		CommandButton* btn6 = new CommandButton();
		btn6->setBounds( 10, btn5->getBottom() + 20, 175, btn6->getPreferredHeight() );
		btn6->setCaption( "Show Common File Browse Dialog" );
		btn6->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example6, "DialogsWindow::example6" );
		add( btn6 );

		CommandButton* btn7 = new CommandButton();
		btn7->setBounds( 10, btn6->getBottom() + 20, 175, btn6->getPreferredHeight() );
		btn7->setCaption( "Show Common File Open Dialog" );
		btn7->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example7, "DialogsWindow::example7" );
		add( btn7 );

		CommandButton* btn8 = new CommandButton();
		btn8->setBounds( 10, btn7->getBottom() + 20, 175, btn6->getPreferredHeight() );
		btn8->setCaption( "Show Common File Save Dialog" );
		btn8->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example8, "DialogsWindow::example8" );
		add( btn8 );

		CommandButton* btn9 = new CommandButton();
		btn9->setBounds( 10, btn8->getBottom() + 20, 175, btn6->getPreferredHeight() );
		btn9->setCaption( "Show Common Print Dialog" );
		btn9->ButtonClicked += 
			new GenericEventHandler<DialogsWindow>( this, &DialogsWindow::example9, "DialogsWindow::example9" );
		add( btn9 );
	}

	virtual ~DialogsWindow(){};

	/**
	This example will deomonstrate how to display a modal, information dialog,
	to present some information to a user.
	All you have to pass in is the caption - the title of the dialog will be assigned 
	the name of the application
	*/
	void example1( Event* e ) {
		Dialog::showMessage( "Hello - this is example 1." );
	}


	String modalReturnToString( UIToolkit::ModalReturnType val ) {
		String result;
		switch ( val ) {
			case UIToolkit::mrOK : {
				result = "UIToolkit::mrOK";
			}
			break;

			case UIToolkit::mrCancel : {
				result = "UIToolkit::mrCancel";
			}
			break;

			case UIToolkit::mrYes : {
				result = "UIToolkit::mrYes";
			}
			break;

			case UIToolkit::mrNo : {
				result = "UIToolkit::mrNo";
			}
			break;

			case UIToolkit::mrAbort : {
				result = "UIToolkit::mrAbort";
			}
			break;

			case UIToolkit::mrIgnore : {
				result = "UIToolkit::mrIgnore";
			}
			break;

			case UIToolkit::mrRetry : {
				result = "UIToolkit::mrRetry";
			}
			break;
		}
		return result;
	}

	/**
	This example also displays a modal dialog. You can specify more options
	such as the type of icon to display, the title of the dialog, and the 
	kind of buttons the user can respond with.
	*/
	void example2( Event* e ) {
		UIToolkit::ModalReturnType result;

		result = Dialog::showMessage( "Hello - this is an example using \nOK and Cancel buttons.", 
										"Fluffaluffagus",
										Dialog::mbOKCancel,
										Dialog::msError );

		Dialog::showMessage( "You selected: " + modalReturnToString( result ) );

		result = Dialog::showMessage( "Hello - this is an example using \nYes and No buttons.", 
										"Fluffaluffagus",
										Dialog::mbYesNo,
										Dialog::msWarning );

		Dialog::showMessage( "You selected: " + modalReturnToString( result ) );

		result = Dialog::showMessage( "Hello - this is an example using \nAbort, Retry and Ignore buttons.", 
										"Format your Hard Disk?",
										Dialog::mbAbortRetryIgnore,
										Dialog::msInfo );

		Dialog::showMessage( "You selected: " + modalReturnToString( result ) );
	}

	/**
	This example shows how to launch a custom
	modal dialog
	*/
	void example3( Event* e ) {
		MyDialog dialog;// = new MyDialog();
		UIToolkit::ModalReturnType result;

		result = dialog.showModal();

		Dialog::showMessage( "You selected: " + modalReturnToString( result ) );

		//dialog->free();
	}


	/**
	This example shows how to call up the common font dialog
	*/
	void example4( Event* e ) {
		CommonFont dlg(this);
		dlg.setSelectedFont( getFont() );
		if ( dlg.execute() ) {
			Font font = *dlg.getSelectedFont();

			Dialog::showMessage( "You selected the font named: " + font.getName() );
		}
	}

	/**
	This example shows how to call up the common Color dialog
	*/	
	void example5( Event* e ) {
		CommonColor dlg(this);
		dlg.setSelectedColor( getColor() );
		if ( dlg.execute() ) {
			Color color = *dlg.getSelectedColor();

			String hexName = StringUtils::format( "#%02X%02X%02X", 
													(int)(color.getRed() * 255.0),
													(int)(color.getGreen() * 255.0),
													(int)(color.getBlue() * 255.0) );

			Dialog::showMessage( "You chose color (in hex) : " + hexName );
		}
	}

	/**
	This example shows how to call up the common file browse dialog
	*/
	void example6( Event* e ) {
		CommonFileBrowse dlg(this);
		
		dlg.setDirectory( System::getCurrentWorkingDirectory() );

		if ( dlg.execute() ) {
			Dialog::showMessage( "You picked directory: " + dlg.getDirectory() );
		}
	}

	/**
	This example shows how to call up the common file open dialog
	*/
	void example7( Event* e ) {
		CommonFileOpen dlg(this);
		
		dlg.addFilter( "Pumpernikel Bread", "*.pmk" );
		if ( dlg.execute() ) {

		}
	}

	/**
	This example shows how to call up the common file save dialog
	*/
	void example8( Event* e ) {
		CommonFileSave dlg(this);
		
		if ( dlg.execute() ) {

		}
	}

	/**
	This example shows how to call up the common print dialog
	*/
	void example9( Event* e ) {
		CommonPrint dlg(this);
		
		if ( dlg.execute() ) {

		}
	}
};




class DialogsApplication : public Application {
public:

	DialogsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new DialogsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new DialogsApplication( argc, argv );

	Application::main();
	
	return 0;
}


