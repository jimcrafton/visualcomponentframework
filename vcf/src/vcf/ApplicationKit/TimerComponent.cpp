//TimerComponent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//TimerComponent.h
#include "vcf/ApplicationKit/ApplicationKit.h"
using namespace VCF;



TimerComponent::TimerComponent():
	timeoutInterval_(1000),
	isActive_(false)
{

}

TimerComponent::TimerComponent( Component* owner ):
	Component( owner ),
	timeoutInterval_(1000),
	isActive_(false)
{

}

TimerComponent::TimerComponent( const String& name, Component* owner ):
	Component( name, owner ),
	timeoutInterval_(1000),
	isActive_(false)
{

}

TimerComponent::TimerComponent( const String& name ):
	Component( name ),
	timeoutInterval_(1000),
	isActive_(false)
{

}


TimerComponent::~TimerComponent()
{
	setActivated( false );
}

void TimerComponent::afterCreate( ComponentEvent* event )
{

}

void TimerComponent::setActivated( const bool& isActive )
{
	isActive_ = isActive;

	EventHandler* handler = getTimerHandler();

	if ( true == isActive_ ) {
		TimerEvent event( this, TIMER_EVENT_ACTIVATED );
		TimerActivated.fireEvent( &event );

		UIToolkit::registerTimerHandler( this, handler, timeoutInterval_ );
	}
	else {
		UIToolkit::unregisterTimerHandler( handler );

		TimerEvent event( this, TIMER_EVENT_DEACTIVATED );
		TimerDeactivated.fireEvent( &event );
	}

}

void TimerComponent::setTimeoutInterval( const long& interval )
{
	setActivated( false );

	timeoutInterval_ = interval;
}

void TimerComponent::onInternalTimerPulse( TimerEvent* event )
{
	TimerPulse.fireEvent( event );
}

EventHandler* TimerComponent::getTimerHandler()
{
	EventHandler* result = getEventHandler( "TimerComponent::onInternalTimerPulse" );
	if ( NULL == result ) {
		result = new TimerEventHandler<TimerComponent>( this, &TimerComponent::onInternalTimerPulse, "TimerComponent::onInternalTimerPulse" );
		addEventHandler( "TimerComponent::onInternalTimerPulse", result );
	}
	return result;
}


/**
$Id$
*/
