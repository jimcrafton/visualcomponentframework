//ThreadsInGUI.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"
#include "core/DefaultListItem.h"

using namespace VCF;


/**
This example will demonstrate running a separate thread that 
increments a count, and then updating it's state in the user
interface
*/


/**
This is out thread class which does the work of incrementing a 
count variable. Our thread class is not an auto-delete thread
and the thread's deletion is done by and event handler that
is notified when the thread is ready to be deleted.
It takes three event handlers in it's constructor, one
for notification of a change in state, one for notification
that the thread has stopped, and one to notify the event
handler's owner that the thread should be deleted. 
*/
class CounterThread : public Thread {
public:
	CounterThread( EventHandler* changed, 
					EventHandler* stopped,
					EventHandler* deleteMe ):Thread(false),
											changed_(changed), 
											stopped_(stopped), 
											deleteMe_(deleteMe), 
											currentCount_(0){

	}
	

	/**
	our run method initializes the currentCount_ to 0
	*/
	virtual bool run() {
		currentCount_ = 0;
		
		/**
		Loop while we're able to, and increment the count
		each time we do this we'll post an event for this
		see the change() method
		*/
		while ( canContinue() && currentCount_ < 1000 ) {
			currentCount_ ++;

			change();

			sleep( 1 );
		}
		currentCount_ = -1;

		/**
		post the change once more
		*/
		change();

		/**
		post a stop event and a deletion event
		*/
		stopped();
		return true;
	}
	
	int currentCount() {
		return currentCount_;
	}
protected:
	/**
	This post's an event to the windowing systems event queue,
	which will in turn invoke our changed_ event handler.
	We pass in false, to prevent the UIToolkit from automatically
	deleting the changed_ event handler
	*/
	void change() {
		UIToolkit::postEvent( changed_, new Event(this), false );
	}

	/**
	This post's an stopped event, and then a deletion event.
	When the deletion event handler is invoked, the thread will
	be deleted
	*/
	void stopped() {
		UIToolkit::postEvent( stopped_, new Event(this), false );
		UIToolkit::postEvent( deleteMe_, new Event(this), false );
	}

	int currentCount_;
	EventHandler* changed_;
	EventHandler* stopped_;
	EventHandler* deleteMe_;
};



/**
This is a thread item class
We'll add one of these to our ListBoxControl's ListModel
for each thread.
To customize it, we have overriden the DefaultListItem's 
getCaption() method with our own custom handling which
prints out the thread's current state. 
Doing this is a bit simpler than overriding the list items
paint method()
*/
class ThreadItem : public DefaultListItem {
public:
	ThreadItem() {
		setData( NULL );
	}

	virtual String getCaption() {
		String result = DefaultListItem::getCaption();
		
		if ( result.empty() ) {
			CounterThread* thread = (CounterThread*)getData();
			if ( NULL != thread ) { 
				result = thread->toString();
				result += " " + StringUtils::toString( thread->currentCount() );
			}
			else {
				result = "Thread died and is dead and gone";
				setData( NULL );
				setCaption( result );
			}
		}

		return result;
	}
};


/**
*/
class ThreadsInGUIWindow : public Window {
public:
	ThreadsInGUIWindow() {
		setCaption( "ThreadsInGUI" );

		setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		EventHandler* ev = 
			new GenericEventHandler<ThreadsInGUIWindow>( this, 
														&ThreadsInGUIWindow::threadChanged, 
														"ThreadsInGUIWindow::threadChanged" );

		ev = 
			new GenericEventHandler<ThreadsInGUIWindow>( this, 
														&ThreadsInGUIWindow::threadStopped, 
														"ThreadsInGUIWindow::threadStopped" );

		ev = 
			new GenericEventHandler<ThreadsInGUIWindow>( this, 
														&ThreadsInGUIWindow::deleteThread, 
														"ThreadsInGUIWindow::deleteThread" );

		CommandButton* btn = new CommandButton();
		btn->setBounds( 20, 20, 100, btn->getPreferredHeight() );
		btn->setCaption( "Start Thread" );
		add( btn );

		btn->addButtonClickHandler( new ButtonEventHandler<ThreadsInGUIWindow>( this, 
														&ThreadsInGUIWindow::addThread, 
														"ThreadsInGUIWindow::addThread" ) );


		listBox_ = new ListBoxControl();

		Rect bounds = getClientBounds();
		bounds.inflate( -5, -5 );

		bounds.top_ += (btn->getTop() + btn->getHeight());

		listBox_->setAnchor( AnchorLeft | AnchorTop | AnchorBottom | AnchorRight );
		listBox_->setBounds( &bounds );

		add( listBox_ );


		setVisible( true );
	}

	void addThread( ButtonEvent* e ) {
		Thread* thread = new CounterThread( getEventHandler("ThreadsInGUIWindow::threadChanged"),
										getEventHandler("ThreadsInGUIWindow::threadStopped"),
										getEventHandler("ThreadsInGUIWindow::deleteThread") );

		ListModel* lm = listBox_->getListModel();
		ListItem* item = new ThreadItem();
		item->setData( thread );

		lm->addItem( item );

		thread->start();
	}

	virtual ~ThreadsInGUIWindow(){};

	void threadStopped( Event* e ) {
		listBox_->repaint();
	}

	void threadChanged( Event* e ) {
		listBox_->repaint();
	}

	void deleteThread( Event* e ) {
		Thread* thread = (Thread*)e->getSource();
		
		Enumerator<ListItem*>* items = listBox_->getListModel()->getItems();
		while ( items->hasMoreElements() ) {
			ListItem* item = items->nextElement();
			if ( item->getData() == thread ) {
				item->setData( NULL );
				break;
			}
		}

		thread->free();
	}

	ListBoxControl* listBox_;
};




class ThreadsInGUIApplication : public Application {
public:

	ThreadsInGUIApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new ThreadsInGUIWindow();
		setMainWindow(mainWindow);
		
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ThreadsInGUIApplication( argc, argv );

	Application::main();
	
	return 0;
}


