//Action.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"


using namespace VCF;


Action::Action():
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( Component* owner ):
	Component(owner),
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( const String& name, Component* owner ):
	Component(name, owner),
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( const String& name ):
	Component(name),
	currentAccelerator_(NULL)
{
	targetsContainer_.initContainer(targets_);
}

Action::~Action()
{

}


void Action::update()
{
	ActionEvent event( this, Action::UpdateEvent );

	// let the application to set the desired state for the ActionEvent.
	Update.fireEvent( &event );


	std::vector<Component*>::iterator it = targets_.begin();

	while ( it != targets_.end() ) {
		(*it)->handleEvent( &event );
		it ++;
	}

	if ( NULL != currentAccelerator_ ) {
		currentAccelerator_->setEnabled( event.isEnabled() );
	}
}

void Action::perform( Event* event )
{
	if ( NULL != event ) {
		Performed.fireEvent( event );
	}
	else {
		ActionEvent e( this, Action::ActionPerformedEvent );
		Performed.fireEvent( &e );
	}
}

void Action::addTarget( Component* target )
{
	std::vector<Component*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_.push_back( target );
		target->setAction( this );
	}
}

void Action::removeTarget( Component* target )
{
	std::vector<Component*>::iterator found = std::find( targets_.begin(), targets_.end(), target );

	if ( found != targets_.end() ) {
		targets_.erase( found );
	}
}

Enumerator<Component*>* Action::getTargets()
{
	return targetsContainer_.getEnumerator();
}

unsigned long Action::getTargetCount()
{
	return targets_.size();
}

EventHandler* Action::getAcceleratorEventHandler()
{
	EventHandler* result = getEventHandler( "Action::onAccelerator" );
	if ( NULL == result ) {
		result = 
			new KeyboardEventHandler<Action>( this, &Action::onAccelerator, "Action::onAccelerator" );
	}

	return result;
}


void Action::setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask )
{
	
	EventHandler* eventHandler = getAcceleratorEventHandler();

	AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, modifierMask, eventHandler );

	setAcceleratorKey( newAccelKey );
}

void Action::setAcceleratorKey( AcceleratorKey* accelerator )
{
	//remove the old if present
	if ( NULL != currentAccelerator_ ) {
		UIToolkit::removeAccelerator( (VirtualKeyCode)currentAccelerator_->getKeyCode(),
																currentAccelerator_->getModifierMask(), this );
	}

	currentAccelerator_ = accelerator;

	if ( NULL != currentAccelerator_ ) {
		UIToolkit::registerAccelerator( currentAccelerator_ );
	}

	std::vector<Component*>::iterator it = targets_.begin();

	Event event(this, Action::AcceleratorChanged );

	while ( it != targets_.end() ) {
		(*it)->handleEvent( &event );
		it ++;
	}
}

AcceleratorKey* Action::getAccelerator()
{
	return currentAccelerator_;
}

void Action::onAccelerator( KeyboardEvent* e )
{
	perform();
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/06/02 15:28:35  marcelloptr
*more documentation
*
*Revision 1.2.4.2  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2.4.1  2005/03/14 04:17:22  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.2  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.1.2.1  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*/


