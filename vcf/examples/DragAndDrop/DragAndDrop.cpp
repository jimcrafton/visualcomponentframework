//DragAndDrop.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"
#include "utils/StringTokenizer.h"

using namespace VCF;



/**
This example demonstrates how to use drag and drop 
with the VCF
*/


/**
This simple class creates a panel that 
creates data for dragging and dropping.
*/
class DraggingPanel : public Panel {
public:

	/**
	By overriding the beginDragDrop()
	method of the VCF::Control class we can drag 
	data from one place to another.
	The method should return true if the drag drop operation
	completed, otherwise return false.
	*/
	virtual bool beginDragDrop( MouseEvent* e ) {
		/**
		Here we create our data source for the 
		drag drop operation
		*/
		DragSource src;
		/**
		We set the action type to "link". Me can 
		set it to link, copy, move, or none. 
		*/
		src.setActionType( daLink );

		/**
		We create our data object. This is what actually
		holds the data for the drag drop operation.
		*/
		TextDataObject sourceData("Some Text To Drag!");

		/**
		calling startDragDrop(), tells the OS that we are ready to 
		drag and drop. startDragDrop() will block till hte operation
		is completed or cancelled out.
		*/
		src.startDragDrop( &sourceData );

		return true;

	}
};


/**
Our main window is going to hold several controls.
One of the controls will be a drag source, so that when you drag
the mouse on it, you'll be able to drag a small piece of 
"text" to another control.
The other panel below it will accept files if you drop them on the panel
Finally, the last panel will accept image and briefly display the
image dropped on it.
*/
class DragAndDropWindow : public Window {
public:
	DragAndDropWindow() {
		setCaption( "DragAndDrop" );
		setVisible( true );

		/**
		Add a label
		*/
		Label* label = new Label();
		label->setBounds( 20, 5, 100, label->getPreferredHeight() );
		label->setCaption( "Text drag source" );
		add( label );

		/**
		Add our text source panel.
		Dragging on this panel will create a DragSource and 
		begin a drag-drop operation.
		*/
		Panel* textSrcPanel = new DraggingPanel();
		/**
		setting auto start dragdrop to true lets the VCF decide 
		when a drag-drop operation has potentially begun.
		*/
		textSrcPanel->setAutoStartDragDrop( true );
		
		//set the tooltip text
		textSrcPanel->setToolTipText( "Drag me to the right most panel" );

		//set the bounds and add the panel
		textSrcPanel->setBounds( 20, 20, 100, 50 );
		add( textSrcPanel );


		label = new Label();
		label->setBounds( 200, 5, 100, label->getPreferredHeight() );
		label->setCaption( "Text drag destination" );
		add( label );

		/**
		This adds a panel that will accept text. Note that
		the text can be dragged from any application that properly
		implements the native windowing system/OS drag-drop protocol.
		*/
		Panel* textDestPanel = new Panel();
		//set bounds, add the control
		textDestPanel->setBounds( 200, 20, 100, 50 );
		add( textDestPanel );

		/**
		We create a drop target. The drop target is attached to a control
		and the drop target will become notified when a drag-drop operation
		enters it's target control, drags over the target control, drops on
		the target control, or leaves the target control.
		
		The drop target is *not* itself a control.

		A control *must* be connected to a drop target to 
		recieve drag drop operations.

		For the purposes of this example we will only add event handlers
		for recieving events on entering and dropping over the drop target.
		*/
		DropTarget* textDestDropTarget = new DropTarget( textDestPanel );
		//add the component to our main window. 
		addComponent( textDestDropTarget );

		//add the two event handlers to the drop target's delegates
		textDestDropTarget->DropTargetDropped += 
			new DropEventHandler<DragAndDropWindow>( this, &DragAndDropWindow::onTextDestDropped, "onTextDestDropped" );

		textDestDropTarget->DropTargetEntered += 
			new DropEventHandler<DragAndDropWindow>( this, &DragAndDropWindow::onTextDestEntered, "onTextDestEntered" );
		
		

		label = new Label();
		label->setBounds( 20, textDestPanel->getBottom() + 45, 280, label->getPreferredHeight() );
		label->setCaption( "Drag and drop files on the panel below" );
		add( label );

		/**
		Add another panel that will proces drag drop operations from files
		*/
		Panel* filesDestPanel = new Panel();		
		filesDestPanel->setBounds( 20, label->getBottom(), 280, 50 );
		filesDestPanel->setToolTipText( "Drop files on me!" );
		add( filesDestPanel );

		/**
		Add another drop target, this one to our file drop panel
		*/
		DropTarget* fileDestDropTarget = new DropTarget( filesDestPanel );
		
		addComponent( fileDestDropTarget );

		fileDestDropTarget->DropTargetDropped += 
			new DropEventHandler<DragAndDropWindow>( this, &DragAndDropWindow::onFileDestDropped, "onFileDestDropped" );


		label = new Label();
		label->setBounds( 20, filesDestPanel->getBottom() + 10, 280, label->getPreferredHeight() );
		label->setCaption( "Drag and drop images on the panel below" );
		add( label );


		/**
		This panel will respond to drag drop operations from an image source.
		The image can be a native VCF Image, or basic image types from other sources.
		For example, on Win32, if you drag and drop and object from Microsoft PowerPoint
		over this panel, drag drop system will correctly render the Windows Meta File (WMF)
		onto an image, which can tehn be extracted.
		*/
		Panel* imageDestPanel = new Panel();
		
		imageDestPanel->setBounds( 20, label->getBottom(), 280, 200 );
		imageDestPanel->setToolTipText( "Drop images on me!" );
		add( imageDestPanel );

		//drop target for the image panel
		DropTarget* imageDestDropTarget = new DropTarget( imageDestPanel );
		addComponent( imageDestDropTarget );

		imageDestDropTarget->DropTargetDropped += 
			new DropEventHandler<DragAndDropWindow>( this, &DragAndDropWindow::onImageDestDropped, "onImageDestDropped" );

		
	}

	virtual ~DragAndDropWindow(){};

	/**
	This methods allows us to control what data types 
	we will respond to. If the data type is "text/plain"
	then we will allows drag drop operations, otherwise
	we'll ignore them.
	*/
	void onTextDestEntered( DropTargetEvent* e ) {
		// get hte data object from the event
		DataObject* dataObj = e->getDataObject();

		//get the enumerator of data types from the data object
		Enumerator<String>* dataTypes = dataObj->getSupportedDataTypes();
		while ( true == dataTypes->hasMoreElements() ) {
			//enumerate each data type
			String dataType = dataTypes->nextElement();
			StringUtils::trace( "Data Type mime is : " + dataType + "\n" );
		}

		/**
		if the data object supports "text/plain" data then
		set the event's action type to daCopy, which will
		allow us to respond to the rest of the drag drop operation
		(such as the drag overs, and eventual drop itself).
		If it doesn't support "text/plain" then set the action type
		to daNone, which will tell the VCF that this target doesn't 
		respond to drag overs/drops for this particualar drag drop operation.
		Please note, that at this point all the data object contains is an
		indication of the types it supports. The actual data itself is 
		not made available until a drop is made.
		*/
		if ( dataObj->isTypeSupported( "text/plain" ) ) {
			e->setActionType( daCopy );
		}
		else {
			e->setActionType( daNone );
		}
	}

	/**
	A drop has been detected on the drop target
	so we handle it here.
	Since we only handle text, we check to see if the data
	support "text/plain" and then retreive the data
	*/
	void onTextDestDropped( DropTargetEvent* e ) {
		DataObject* dataObj = e->getDataObject();

		if ( dataObj->isTypeSupported( "text/plain" ) ) {
			//create a basic output stream to write the data to
			BasicOutputStream stream;

			//write the data in hte data object to the stream
			if ( dataObj->saveToStream( "text/plain", &stream ) ) {
				//create a string from the data
				String string;
				//append the data in the stream's buffer to the string
				string.append( stream.getBuffer(), stream.getSize() );

				//popup a message box to display the text
				Dialog::showMessage( "onTextDestDropped got: " + string );
			}
		}
	}

	/**
	This handler is called when files are dropped on the file drop target
	The data for files will be stored as text. Each file name will be separated
	by a '/n' character.
	*/
	void onFileDestDropped( DropTargetEvent* e ) {
		DataObject* dataObj = e->getDataObject();

		//check to see if we have a file data type
		if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
			//create a basic output stream to write the data to
			BasicOutputStream stream;

			//write the data in the data object to the stream
			if ( dataObj->saveToStream( FILE_DATA_TYPE, &stream ) ) {
				//create a string from the output streams data
				String fileNames;
				fileNames.append( stream.getBuffer(), stream.getSize() );

				//create a string tokenizer, with the delimeter set to '\n'
				StringTokenizer tok( fileNames, "\n");
				//enumerate through all the file names
				while ( tok.hasMoreElements() ) {
					String fileName = tok.nextElement();
					Dialog::showMessage( "onFileDestDropped got: " + fileName );
				}	
			}
		}
	}

	/**
	This handler will be called when an image is dragged over the image drop
	target. 
	*/
	void onImageDestDropped( DropTargetEvent* e ) {
		DataObject* dataObj = e->getDataObject();
		//check to see if the data obejct has image data
		if ( dataObj->isTypeSupported( IMAGE_DATA_TYPE ) ) {
			//create a stream
			BasicOutputStream stream;
			if ( dataObj->saveToStream( IMAGE_DATA_TYPE, &stream ) ) {
				//create an image (1X1 pixels in dimension)
				Image* image = GraphicsToolkit::createImage( 1, 1 );
				//create a basic input stream from the buffer in output stream
				BasicInputStream bis( stream.getBuffer(), stream.getSize() );

				//read the data from the input stream
				bis >> dynamic_cast<Persistable*>(image);

				//get the drop target
				DropTarget* dropTarget = (DropTarget*)e->getSource();

				//get the graphics context for hte drop target's control
				GraphicsContext* ctx = dropTarget->getTarget()->getContext();
				//draw the image
				ctx->drawImage( 20, 20, image );
				delete image;
			}
		}
	}

	
};




class DragAndDropApplication : public Application {
public:

	DragAndDropApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new DragAndDropWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{	 
	Application* app = new DragAndDropApplication( argc, argv );

	Application::main();
	
	return 0;
}


