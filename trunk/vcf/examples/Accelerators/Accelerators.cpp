//Accelerators.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
This example will introduce the basics of working with acceleratorss.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


class FocusPanel : public Panel {
public:

	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		if ( Panel::isFocused() ) {
			Rect r = getClientBounds();
			r.inflate( -5, -5 );
			DrawUIState state;
			ctx->drawThemeFocusRect( &r, state );
		}
	}
};


class AcceleratorsWindow : public Window {
public:
	AcceleratorsWindow() {
		setCaption( "Accelerators" );
		
		MenuBar* mb = new MenuBar( this );
		setMenuBar( mb );

		MenuItem* root = mb->getRootMenuItem();

		MenuItem* edit = new DefaultMenuItem( "Edit", root, mb);
		MenuItem* editUndo = new DefaultMenuItem( "Undo", edit, mb);
		MenuItem* editCopy = new DefaultMenuItem( "Copy", edit, mb);

		MenuItem* panels = new DefaultMenuItem( "Panels", root, mb);
		MenuItem* panelsChangeColor = new DefaultMenuItem( "Change Color", panels, mb);

		EventHandler* ehEditUndo1 = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onEditUndo1, "AcceleratorsWindow::onEditUndo1" );

		EventHandler* ehUpdateEditUndo1 = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onUpdateEditUndo1, "AcceleratorsWindow::onUpdateEditUndo1" );

		EventHandler* ehEditUndo2 = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onEditUndo2, "AcceleratorsWindow::onEditUndo2" );
					
		EventHandler* ehUpdateEditUndo2 = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onUpdateEditUndo2, "AcceleratorsWindow::onUpdateEditUndo2" );


		EventHandler* ehEditCopy = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onEditCopy, "AcceleratorsWindow::onEditCopy" );
					
		EventHandler* ehUpdateEditCopy = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onUpdateEditCopy, "AcceleratorsWindow::onUpdateEditCopy" );

		EventHandler* ehUpdateEditCopy1 = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onUpdateEditCopy1, "AcceleratorsWindow::onUpdateEditCopy1" );

		EventHandler* ehUpdateEditCopy2 = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onUpdateEditCopy2, "AcceleratorsWindow::onUpdateEditCopy2" );

		

		EventHandler* ehPanelsChangeColors = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onPanelsChangeColors, "AcceleratorsWindow::onPanelsChangeColors" );

		EventHandler* ehUpdatePanelsChangeColors = 
			new GenericEventHandler<AcceleratorsWindow>( this, &AcceleratorsWindow::onUpdatePanelsChangeColors, "AcceleratorsWindow::onUpdatePanelsChangeColors" );





		editUndo->setAcceleratorKey( vkLetterZ, kmCtrl );
		editUndo->MenuItemClicked += ehEditUndo1;
		editUndo->MenuItemUpdate += ehUpdateEditUndo1;
		// Note that the update handler has been assigned to the
		// menu item only, so it is different than the update handler
		// automatically assigned to the TextControl. Because of that 
		// the Ctrl+Z accelerator will still trigger the Undo operation
		// even if the Undo menu item is disabled.




		panelsChangeColor->MenuItemClicked += ehPanelsChangeColors;
		panelsChangeColor->MenuItemUpdate += ehUpdatePanelsChangeColors;


		TabbedPages* tabs = new TabbedPages();
		tabs->setName( "Tabs" );
		add( tabs, AlignClient );


		TabPage* tab = tabs->addNewPage( "Page 1" );

		TextControl* tc = new TextControl();
		//note setting the tag here - this is a cheap easy way to identify a component
		tc->setTag( 100 );

		tc->setBounds( 10, 10, 100, tc->getPreferredHeight() );
		tab->getPageComponent()->getContainer()->add (tc);


		TextControl* tc2 = new TextControl();
		tc2->setBounds( 10, 60, 100, tc2->getPreferredHeight() );
		tc2->setTag( 101 );
		tab->getPageComponent()->getContainer()->add (tc2);


		

		tab = tabs->addNewPage( "Page 2" );
		
		FocusPanel* p1 = new FocusPanel();
		p1->setBounds( 20, 40, 100, 40 );
		p1->setName( "Panel1" );
		Label* l = new Label();
		l->setCaption( "Click top panel to set it's focus, then click the Panels > Change Colors menu" );
		l->setWordWrap( true );
		l->setHeight( 40 );

		tab->getPageComponent()->getContainer()->add( l, AlignTop );

		tab->getPageComponent()->getContainer()->add (p1);

		FocusPanel* p2 = new FocusPanel();
		p2->setBounds( 20, 90, 100, 40 );
		p2->setName( "Panel2" );
		tab->getPageComponent()->getContainer()->add (p2);

		FocusPanel* p3 = new FocusPanel();
		p3->setBounds( 20, 150, 100, 40 );
		p3->setName( "Panel3" );
		tab->getPageComponent()->getContainer()->add (p3);


		Action* copyAction = new Action(this);

		//we can add multiple update handlers to the same action.
		copyAction->Performed += ehEditCopy;
		copyAction->Update += ehUpdateEditCopy;
		copyAction->Update += ehUpdateEditCopy1;
		copyAction->Update += ehUpdateEditCopy2;


		copyAction->addTarget( editCopy ); // the "Copy" menu item
		copyAction->setAcceleratorKey( vkLetterC, kmCtrl );

		//the text controls cannot be targets for the TextControl(s),
		// otherwise they would be enabled/disabled according to 
		// the state of the Action or Accelerator.
		//So the accelerator needs to be added to each control
		// we want to be responding to it.
		tc->addAcceleratorKey( vkLetterC, kmCtrl, copyAction );
		tc2->addAcceleratorKey( vkLetterC, kmCtrl, copyAction );
	}

	void onEditUndo1( Event* e ) {
		Dialog::showMessage( "Undo: Hello World!" );
	}

	void onUpdateEditUndo1( Event* e ) {
		MenuItem* item = (MenuItem*)e->getSource();

		Control* focusedControl = Control::getCurrentFocusedControl();

		switch ( focusedControl->getTag() ) {

			case 100 : {
				item->setEnabled( true );
				item->setCaption( "Undo on tc1" );
			}
			break;

			case 101 : {
				item->setEnabled( false );
				item->setCaption( "Undo on tc2, Sorry, no dice!!!" );
			}
			break;

			default : {
				item->setEnabled( true );
				item->setCaption( "Undo - no text control selected!" );
			}
			break;
			
		}
	}


	void onEditUndo2( Event* e ) {
		Dialog::showMessage( "onEditUndo2" );
	}

	void onUpdateEditUndo2( Event* e ) {

	}

	void onEditCopy( Event* e ) {
		Dialog::showMessage( "onEditCopy!" );
	}

	void onUpdateEditCopy( Event* e ) {
		ActionEvent* ae = (ActionEvent*)e;

		Control* focusedControl = Control::getCurrentFocusedControl();

		// the undo is disabled when the focus is on a generic control, by default.
		ae->setEnabled( false );
	}

	void onUpdateEditCopy1( Event* e ) {
		ActionEvent* ae = (ActionEvent*)e;

		Control* focusedControl = Control::getCurrentFocusedControl();

		switch ( focusedControl->getTag() ) {

			case 100 : {
				ae->setEnabled( true );
			}
			break;

		}
	}

	void onUpdateEditCopy2( Event* e ) {
		ActionEvent* ae = (ActionEvent*)e;

		Control* focusedControl = Control::getCurrentFocusedControl();

		ae->setText( "Copy text" );

		switch ( focusedControl->getTag() ) {

			case 101 : {
				ae->setEnabled( true );

				// any target (MenuItem) will read this ActionEvent's text 
				// and modify it's caption ( see Action::getText() ).
				ae->setText( "Copy" );
			}
			break;
			
		}
	}


	void onPanelsChangeColors( Event* e ) {
		double r = rand() % (255 - 0 + 1) + 0;
		double g = rand() % (255 - 0 + 1) + 0;
		double b = rand() % (255 - 0 + 1) + 0;
		Color c( r/255.0,g/255.0,b/255.0 );


		Panel* panel1 = (Panel*) Control::findComponent( "Panel1", true );

		panel1->setUseColorForBackground( true );
		panel1->setColor( &c );
	}

	void onUpdatePanelsChangeColors( Event* e ) {
		MenuItem* item = (MenuItem*)e->getSource();

		Control* focusedControl = Control::getCurrentFocusedControl();

		if ( focusedControl->getName() == "Panel1" ) {
			item->setEnabled(true);
		}
		else {
			item->setEnabled(false);
		}
	}

	virtual ~AcceleratorsWindow(){};

};




class AcceleratorsApplication : public Application {
public:

	AcceleratorsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new AcceleratorsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 300.0, 300.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new AcceleratorsApplication( argc, argv );

	Application::main();
	
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:34:09  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.2.3  2006/03/20 01:21:56  dougtinkham
*minor cosmetic change
*
*Revision 1.2.2.2  2006/03/16 01:31:31  ddiego
*fixed accelerators example per fraggles req.
*
*Revision 1.2.2.1  2006/01/29 18:18:10  dougtinkham
*minor change for mingw
*
*Revision 1.2  2005/07/09 23:14:13  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.5  2005/06/06 02:34:03  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.1.2.4  2005/06/02 20:27:03  marcelloptr
*few more comments
*
*Revision 1.1.2.2  2005/06/02 17:27:31  marcelloptr
*Example made by Jim.
*Added comments and few fixes.
*
*/

