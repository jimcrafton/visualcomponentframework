//Action.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


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
	Update( &event );


	std::vector<UIComponent*>::iterator it = targets_.begin();

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
		Performed( (ActionEvent*)event );
	}
	else {
		ActionEvent e( this, Action::ActionPerformedEvent );
		Performed( &e );
	}
}

void Action::addTarget( UIComponent* target )
{
	std::vector<UIComponent*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_.push_back( target );
		target->setAction( this );
	}
}

void Action::removeTarget( UIComponent* target )
{
	std::vector<UIComponent*>::iterator found = std::find( targets_.begin(), targets_.end(), target );

	if ( found != targets_.end() ) {
		targets_.erase( found );
	}
}

UIComponent* Action::getTarget( const uint32& index )
{
	return targets_.at( index );
}

void Action::setTarget( const uint32& index, UIComponent* target )
{
	size_t missing = (index+1) - targets_.size();
	if ( missing > 0 ) {
		targets_.resize( missing + targets_.size() );
	}

	std::vector<UIComponent*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_[index] = target;
		target->setAction( this );
	}	
}

uint32 Action::getTargetIndexes( std::vector<uint32>& indexes )
{
	indexes.resize( targets_.size() );

	for (size_t i=0;i<indexes.size();i++ ) {
		indexes[i] = i;
	}

	return indexes.size();
}

Enumerator<UIComponent*>* Action::getTargets()
{
	return targetsContainer_.getEnumerator();
}

uint32 Action::getTargetCount()
{
	return targets_.size();
}

EventHandler* Action::getAcceleratorEventHandler()
{
	EventHandler* result = (EventHandler*)getCallback( "Action::onAccelerator" );
	if ( NULL == result ) {
		result = 
			new ClassProcedure1<Event*,Action>( this, &Action::onAccelerator, "Action::onAccelerator" );
	}

	return result;
}


void Action::setAcceleratorKey( const VirtualKeyCode& keyCode, const uint32& modifierMask )
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

	std::vector<UIComponent*>::iterator it = targets_.begin();

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

void Action::onAccelerator( Event* e )
{
	perform();
}


/**
$Id$
*/
