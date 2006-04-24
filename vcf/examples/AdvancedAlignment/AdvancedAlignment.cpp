//AdvancedAlignment.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;

/**
This example will demonstrate how to write a custom container to use
your own layout algorithms.
*/


/**
This represents a custom container class. We derive from
AbstractContainer, as it implements all the grunt methods for
a container. The one key method we need to implement ourselves
is the resizeChildren() method. This is where all our layout
logic will be performed.
*/
class LeftToRightContainer : public AbstractContainer {
public:

	/**
	This is our implementation of the resizeChildren() method.
	This will be called whenever the control that this container
	belongs has been resized and potentially needs to resize it;s
	children as well. In our case we will keep things simple.
	Our layout will calculate the width and height. Divide the
	width into as many equal sections as we have child controls,
	and then position each control accordingly.
	*/
	virtual void resizeChildren( Control* control ) {
		//controlContainer_ is the control that this container is attached to
		Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		bool controlJustAdded = false;
		if ( NULL != control ) {
			//we may have to position this separately - if it is the first time it
			//has been added then it will not be in the child control list
			//search for the control
			std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );

			//if found equals the controls_.end, then control has not been added yet, and this is the first time
			//this control has been positioned for this container
			controlJustAdded = ( found == controls_.end() );
		}

		double childCount = AbstractContainer::getChildCount();
                //check for zero is added because on Borland getChildCount returns 0
                //during initialization and than we have floating point exception
		if ( controlJustAdded ) {
			childCount = childCount + 1.0;
		}

		//calculate the width for each section
                double width = clientBounds.getWidth() / ((childCount <= 0.0) ? 1.0 : childCount) ;

		//note: we could have used the containers vector - this would be every so slightly faster,
		//but this is a bit cleaner for teh sake of an example.
		Enumerator<Control*>* children = AbstractContainer::getChildren();
		Rect childBounds;
		double left = clientBounds.left_;
		while ( children->hasMoreElements() ) {
			Control* child = children->nextElement();

			//set the childBounds rect
			childBounds.setRect( left, clientBounds.top_, left + width, clientBounds.bottom_ );

			//set the child control's bounds
			child->setBounds( &childBounds );

			//increment the left variable by width
			left += width;
		}

		if ( controlJustAdded ) {
			childBounds.setRect( left, clientBounds.top_, left + width, clientBounds.bottom_ );
			control->setBounds( &childBounds );
		}


	}
};

class Layout1 : public Dialog {
public:
	Layout1() {
		setWidth( 500 );
		setHeight( 500 );
		setFrameStyle( fstSizeable );

		setCaption( "Left-to-Right layout example" );

		Label* label = new Label();
		label->setHeight( 50 );
		add( label, AlignTop );
		label->setWordWrap( true );
		label->setCaption( "Left-to-Right layout example\ntry resizing to see the layout in action.\nClick the \"X\" button, or hit the \"Esc\" key to close this dialog." );

		Panel* main = new Panel();

		add( main, AlignClient );


		//set the main panels container to our custom container
		main->setContainer( new LeftToRightContainer() );

		Panel* p1 = new Panel();
		p1->setColor( Color::getColor("red") );
		p1->setUseColorForBackground( true );
		main->add( p1 );

		Panel* p2 = new Panel();
		p2->setColor( Color::getColor("green") );
		p2->setUseColorForBackground( true );
		main->add( p2 );

		Panel* p3 = new Panel();
		p3->setColor( Color::getColor("blue") );
		p3->setUseColorForBackground( true );
		main->add( p3 );

	}
};




/**
This is our next container class. We'll simulate a paged container,
something similar to Java's CardLayout class. Each child
control will take up all the client space, and we'll add a method
to toggle through the children, making each on visible and in front.
We'll also derive from StandardContainer to pick up support
for left, right, top, and bottom "buffer zones".
*/
class PagedContainer : public StandardContainer {
public:

	void first() {
		if ( !pages_.empty() ) {
			//resort the pages_
			Control* control = controls_.front();

			while ( control != pages_.front() ) {
				Control* tmp = pages_.front();
				pages_.pop_front();
				pages_.push_back( tmp );
			}


			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void last() {
		if ( !pages_.empty() ) {
			Control* control = controls_.back();

			while ( control != pages_.front() ) {
				Control* tmp = pages_.front();
				pages_.pop_front();
				pages_.push_back( tmp );
			}

			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void next() {
		if ( !pages_.empty() ) {
			Control* control = pages_.front();
			pages_.pop_front();
			pages_.push_back( control );

			control = pages_.front();

			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	virtual void resizeChildren( Control* control ) {
		//controlContainer_ is the control that this container is attached to
		Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
								clientBounds.top_ + topBorderHeight_,
								clientBounds.right_ - rightBorderWidth_,
								clientBounds.bottom_ - bottomBorderHeight_ );



		bool controlJustAdded = false;
		if ( NULL != control ) {
			//we may have to position this separately - if it is the first time it
			//has been added then it will not be in the child control list
			//search for the control
			std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );

			//if found equals the controls_.end, then control has not been added yet, and this is the first time
			//this control has been positioned for this container
			controlJustAdded = ( found == controls_.end() );
		}


		if ( controlJustAdded ) {
			control->setBounds( &clientBounds );
			pages_.push_back( control );
		}
		else {
			//note: we could have used the containers vector - this would be ever so slightly faster,
			//but this is a bit cleaner for the sake of an example.
			Enumerator<Control*>* children = AbstractContainer::getChildren();

			while ( children->hasMoreElements() ) {
				Control* child = children->nextElement();
				if ( child->getVisible() ) {
					child->setBounds( &clientBounds );
				}
			}
		}
	}

protected:
	std::deque<Control*> pages_;
};




class Layout2 : public Dialog {
public:

	PagedContainer* pagedContainer_;

	Layout2() : pagedContainer_(NULL) {
		setWidth( 500 );
		setHeight( 500 );
		setFrameStyle( fstSizeable );

		setCaption( "Paged layout example" );

		Label* label = new Label();
		label->setHeight( 50 );
		add( label, AlignTop );
		label->setWordWrap( true );
		label->setCaption( "Paged layout example\ntry resizing to see the layout in action.\nClick the \"X\" button, or hit the \"Esc\" key to close this dialog." );

		//add a panel to hold buttons - the buttons will
		//demonstrate the first/last/next methods of the PagedLayout class
		Panel* btnPanel = new Panel();
		btnPanel->setHeight( 50 );
		add( btnPanel, AlignTop );

		EventHandler* btnHandler =
			new ButtonEventHandler<Layout2>( this, &Layout2::onButtonClicked, "onButtonClicked" );

		//this button will switch to the first control - note the use of the setTag() call
		//this is ab easy to share a comon event handler and then use a switch() statement
		//to control behaviour
		CommandButton* btn1 = new CommandButton();
		btn1->setBounds( 10, 10, 100, btn1->getPreferredHeight() );
		btnPanel->add( btn1 );
		btn1->ButtonClicked += btnHandler;
		btn1->setTag( 1 );
		btn1->setCaption( "First Control" );

		//this goes to the last control
		CommandButton* btn2 = new CommandButton();
		btn2->setBounds( 120, 10, 100, btn2->getPreferredHeight() );
		btnPanel->add( btn2 );
		btn2->ButtonClicked += btnHandler;
		btn2->setTag( 2 );
		btn2->setCaption( "Last Control" );

		//this will go to the next control
		CommandButton* btn3 = new CommandButton();
		btn3->setBounds( 230, 10, 100, btn3->getPreferredHeight() );
		btnPanel->add( btn3 );
		btn3->ButtonClicked += btnHandler;
		btn3->setTag( 3 );
		btn3->setCaption( "Next Control" );





		//here we add our main panel to hold our child controls
		Panel* main = new Panel();

		add( main, AlignClient );

		//we create a PagedContainer instance and set our member variable to the new instance
		pagedContainer_ = new PagedContainer();
		pagedContainer_->setBorderWidth( 10 );

		//set the main panels container to our custom container
		main->setContainer( pagedContainer_ );

		//add our children
		Panel* p1 = new Panel();
		p1->setColor( Color::getColor("red") );
		p1->setUseColorForBackground( true );
		main->add( p1 );

		Panel* p2 = new Panel();
		p2->setColor( Color::getColor("green") );
		p2->setUseColorForBackground( true );
		main->add( p2 );

		Panel* p3 = new Panel();
		p3->setColor( Color::getColor("blue") );
		p3->setUseColorForBackground( true );
		main->add( p3 );

		Panel* p4 = new Panel();
		p4->setColor( Color::getColor("white") );
		p4->setUseColorForBackground( true );
		main->add( p4 );

		Panel* p5 = new Panel();
		p5->setColor( Color::getColor("black") );
		p5->setUseColorForBackground( true );
		main->add( p5 );

		Panel* p6 = new Panel();
		p6->setColor( Color::getColor("gold") );
		p6->setUseColorForBackground( true );
		main->add( p6 );

	}

	void onButtonClicked( ButtonEvent* e ) {
		Component* component = (Component*)e->getSource();
		switch ( component->getTag() ) {
			case 1 : {
				pagedContainer_->first();
			}
			break;

			case 2 : {
				pagedContainer_->last();
			}
			break;

			case 3 : {
				pagedContainer_->next();
			}
			break;
		}
	}
};


class AdvancedAlignmentWindow : public Window {
public:
	AdvancedAlignmentWindow() {
		setCaption( "AdvancedAlignment" );


		CommandButton* btn1 = new CommandButton();
		btn1->ButtonClicked +=
			new ButtonEventHandler<AdvancedAlignmentWindow>(this,&AdvancedAlignmentWindow::onBtn1Clicked, "AdvancedAlignmentWindow::onBtn1Clicked");

		btn1->setBounds( 20, 20, 100, btn1->getPreferredHeight() );
		btn1->setCaption( "Left-to-Right layout" );

		add( btn1 );


		CommandButton* btn2 = new CommandButton();
		btn2->ButtonClicked +=
			new ButtonEventHandler<AdvancedAlignmentWindow>(this,&AdvancedAlignmentWindow::onBtn2Clicked, "AdvancedAlignmentWindow::onBtn2Clicked");

		btn2->setBounds( 120, 20, 100, btn1->getPreferredHeight() );
		btn2->setCaption( "Paged layout" );

		add( btn2 );

	}

	virtual ~AdvancedAlignmentWindow(){};

	void onBtn1Clicked( ButtonEvent* e ) {
		Layout1 layout1;

		layout1.showModal();

	}

	void onBtn2Clicked( ButtonEvent* e ) {
		Layout2 layout2;

		layout2.showModal();

	}
};




class AdvancedAlignmentApplication : public Application {
public:

	AdvancedAlignmentApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new AdvancedAlignmentWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 250.0, 150.0 );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new AdvancedAlignmentApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:34:09  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.4  2006/03/16 01:32:18  ddiego
*fixed AdvancedAlignment example per fraggles req.
*
*Revision 1.5.2.3  2005/10/14 13:00:58  kiklop74
*Fix exception error with divide by zero
*
*Revision 1.5.2.2  2005/08/01 16:44:04  marcelloptr
*forgotten fixes
*
*Revision 1.5.2.1  2005/07/23 21:44:57  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.4.4.1  2005/06/25 22:46:10  marcelloptr
*[bugfix 1227549] HorizontalLayoutContainer set the heights in the wrong rows.
*AbstractContainer::add() needs to resizeChildren *after* the child control has been added.
*
*Revision 1.4  2004/08/07 02:46:54  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:51  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


