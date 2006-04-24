//CopyAndPaste.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;

/**
This example will demonstrate how to use the clipboard for copy/paste
operations
*/

class CopyAndPasteWindow : public Window {
public:
	CopyAndPasteWindow() {
		setCaption( "CopyAndPaste" );

		//add a label
		Label* label = new Label();
		label->setCaption( "Enter text to copy" );
		label->setBounds( 20, 20, 200, label->getPreferredHeight() );
		add( label );

		/**
		add our text control into which we'll enter text to be copied to
		the clipboard
		*/
		TextControl* edit = new TextControl();
		edit->setName( "edit" );
		edit->setBounds( 20, label->getBottom() + 10, 200, edit->getPreferredHeight() );
		add( edit );


		/**
		add our copy button.
		When we press this we'll have the CopyAndPasteWindow::onCopyClicked
		method get called
		*/
		CommandButton* copyBtn = new CommandButton();
		copyBtn->setBounds( 20, edit->getBottom() + 20, 200, copyBtn->getPreferredHeight() );
		copyBtn->setCaption( "Copy text to clipboard" );
		add( copyBtn );

		//add the event handler
		copyBtn->addButtonClickHandler(
			new ButtonEventHandler<CopyAndPasteWindow>( this,
														&CopyAndPasteWindow::onCopyClicked,
														"CopyAndPasteWindow::onCopyClicked" ) );



		/**
		add our paste button.
		When we press this we'll have the CopyAndPasteWindow::onPasteClicked
		method get called
		*/
		CommandButton* pasteBtn = new CommandButton();
		pasteBtn->setBounds( 20, copyBtn->getBottom() + 45, 200, copyBtn->getPreferredHeight() );
		pasteBtn->setCaption( "Paste text from clipboard" );
		add( pasteBtn );

		//add the event handler
		pasteBtn->addButtonClickHandler(
			new ButtonEventHandler<CopyAndPasteWindow>( this,
															&CopyAndPasteWindow::onPasteClicked,
															"CopyAndPasteWindow::onPasteClicked" ) );

		label = new Label();
		label->setCaption( "Clipboard text" );
		label->setBounds( 20, pasteBtn->getBottom() + 20, 200, label->getPreferredHeight() );
		add( label );

		/**
		Add the text control into which any text from the clipboard will be copied into
		*/
		TextControl* edit2 = new TextControl();
		edit2->setName( "edit2" );
		edit2->setBounds( 20, label->getBottom() + 10, 200, edit2->getPreferredHeight() );
		edit2->setEnabled( false );
		add( edit2 );
	}

	virtual ~CopyAndPasteWindow(){};


	/**
	This method will handle transferring the text in the first edit control
	into the clipboard
	*/
	void onCopyClicked( ButtonEvent* e ) {
		//get the the text control from the list of components
		TextControl* edit = (TextControl*)findComponent( "edit" );

		//get the text from the text control's model
		String text = edit->getTextModel()->getText();

		/**
		create a new DataObject for text. In this case we'll use the
		TextDataObject which is a sub class of DataObject
		*/
		TextDataObject textData (text);

		/**
		copy the text data into the clipboard
		This now makes the data available to any application
		(regardless of whether or not it is based on the VCF)
		that makes use of the standard clipboard protocol for the
		native windowing system/OS.
		*/
		UIToolkit::getSystemClipboard()->copyTo( &textData );
	}


	/**
	This handler takes care of transferring the data from the clipboard to the
	second edit control.
	*/
	void onPasteClicked( ButtonEvent* e ) {

		/**
		get the system clipboard and paste any data from it that is of type
		"text/plain"
		*/
		DataObject* dataObject = UIToolkit::getSystemClipboard()->pasteFrom( "text/plain" );
		if ( NULL != dataObject ) {
			//create a stream
			BasicOutputStream stream;
			//write the data in the data object to the stream
			if ( dataObject->saveToStream( "text/plain", &stream ) ) {
				//find the second edit control
				TextControl* edit2 = (TextControl*)findComponent( "edit2" );

				//create some text
				String text;
				//append the contents of the stream's buffer to the string
				text.append( stream.getBuffer(), stream.getSize() );

				//set the text control model's text
				edit2->getTextModel()->setText( text );
			}

			dataObject->free();
		}
	}

};




class CopyAndPasteApplication : public Application {
public:

	CopyAndPasteApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new CopyAndPasteWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new CopyAndPasteApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:34:20  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.6.1  2006/03/16 18:45:25  kdmix
*setVisible(true) removed from constructor of the main window.
*
*Revision 1.4  2004/08/07 02:46:57  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.6  2004/06/26 15:22:49  ddiego
*fixes bug [ 978681 ] Copy past example busted
*
*Revision 1.3.2.5  2004/04/29 03:40:52  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


