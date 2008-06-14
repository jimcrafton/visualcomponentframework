//DropTarget.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/ApplicationKit/ApplicationKit.h"



using namespace VCF;

DropTarget::DropTarget( Control* control )
{
	dropTargetPeer_ = UIToolkit::createDropTargetPeer();
	if ( NULL != dropTargetPeer_ ){
		dropTargetPeer_->setDropTarget( this );
	}
	else {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create DropTarget peer") );
	}

	addTarget( control );
}

DropTarget::DropTarget()
{	
	dropTargetPeer_ = UIToolkit::createDropTargetPeer();
	if ( NULL != dropTargetPeer_ ){
		dropTargetPeer_->setDropTarget( this );
	}
	else {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create DropTarget peer") );
	}
}

DropTarget::DropTarget( Component* owner ):
	Component( owner )
{
	dropTargetPeer_ = UIToolkit::createDropTargetPeer();
	if ( NULL != dropTargetPeer_ ){
		dropTargetPeer_->setDropTarget( this );
	}
	else {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create DropTarget peer") );
	}
}

DropTarget::DropTarget( const String& name, Component* owner ):
	Component( name, owner )
{
	dropTargetPeer_ = UIToolkit::createDropTargetPeer();
	if ( NULL != dropTargetPeer_ ){
		dropTargetPeer_->setDropTarget( this );
	}
	else {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create DropTarget peer") );
	}
}

DropTarget::DropTarget( const String& name ):
	Component( name )
{
	dropTargetPeer_ = UIToolkit::createDropTargetPeer();
	if ( NULL != dropTargetPeer_ ){
		dropTargetPeer_->setDropTarget( this );
	}
	else {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create DropTarget peer") );
	}
}

DropTarget::~DropTarget()
{
	if ( NULL != dropTargetPeer_ ){
		delete dropTargetPeer_;
		dropTargetPeer_ = NULL;
	}
}

void DropTarget::handleEvent( Event* event )
{

	if ( NULL != event ){
		uint32 eventType = event->getType();
		switch ( eventType ){
			case DropTarget::DRAG_ENTERED : {
				DropTargetEntered( (DropTargetEvent*)event );
			}
			break;

			case DropTarget::DRAG_LEFT : {
				DropTargetLeft( (DropTargetEvent*)event );
			}
			break;

			case DropTarget::DRAGGING_OVER : {
				DropTargetDraggingOver( (DropTargetEvent*)event );
			}
			break;

			case DropTarget::DRAG_DROPPED : {
				DropTargetDropped( (DropTargetEvent*)event );
			}
			break;

			default : {
				Component::handleEvent( event );
			}
			break;
		}
	}
}

DropTargetPeer* DropTarget::getDropTargetPeer()
{
	return this->dropTargetPeer_;
}


Control* DropTarget::getTarget()
{
	Control* result = NULL;
	if ( !targets_.empty() ) {
		result = targets_.front();
	}

	return result;
}


Enumerator<Control*>* DropTarget::getTargets()
{
	return targets_.getEnumerator();
}

void DropTarget::addTarget( Control* control )
{
	std::vector<Control*>::iterator found = std::find( targets_.begin(), targets_.end(), control );
	if ( found == targets_.end() ) {
		targets_.push_back( control );
		dropTargetPeer_->registerTarget( control );
	}
}

void DropTarget::removeTarget( Control* control )
{
	if ( NULL != control ) {
		std::vector<Control*>::iterator found = std::find( targets_.begin(), targets_.end(), control );
		if ( found != targets_.end() ) {
			dropTargetPeer_->unregisterTarget( control );
			targets_.erase( found );
		}
	}
}

Control* DropTarget::getTargetControl( const uint32& index )
{
	if ( index < targets_.size() ) {
		return targets_[index];
	}

	return NULL;
}

void DropTarget::setTargetControl( const uint32& index, Control* target )
{
	size_t missing = (index+1) - targets_.size();
	if ( missing > 0 ) {
		targets_.resize( missing + targets_.size() );
	}

	Array<Control*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_[index] = target;
		dropTargetPeer_->registerTarget( target );
	}
}

void DropTarget::insertTargetControl( const uint32& index, Control* target )
{
	Array<Control*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_.insert( targets_.begin() + index, target );
		dropTargetPeer_->registerTarget( target );
	}
}

void DropTarget::removeTargetControl( const uint32& index )
{
	if ( index < targets_.size() ) {
		Control* control = targets_[index];
		
		dropTargetPeer_->unregisterTarget( control );
		targets_.erase( targets_.begin() + index );
	}
}

uint32 DropTarget::getTargetControlCount() {
	return targets_.size();
}

/**
$Id$
*/
