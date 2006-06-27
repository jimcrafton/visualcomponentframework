#ifndef _VCF_TIMERCOMPONENT_H__
#define _VCF_TIMERCOMPONENT_H__
//TimerComponent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define TIMERCOMPONENT_CLASSID		"69f9637c-6273-4e10-a9d1-fad815095b61"


namespace VCF  {


/**
\class TimerComponent TimerComponent.h "vcf/ApplicationKit/TimerComponent.h"
The TimerComponent is used to fire timer events. Simply create
the component, add an event handler to it's TimerPulse delegate,
set it's time out interval, and activate the timer. You can
stop the timer at any point by call it's setActivated() function
and passing in false. The default state of the timer is not 
active.
*/
class APPLICATIONKIT_API TimerComponent : public Component {
public:

	TimerComponent();

	TimerComponent( Component* owner );

	TimerComponent( const String& name, Component* owner );

	TimerComponent( const String& name );


	virtual ~TimerComponent();

	DELEGATE(TimerActivated)
	DELEGATE(TimerDeactivated)
	DELEGATE(TimerPulse)


	virtual void afterCreate( ComponentEvent* event );

	/**
	Indicates whether or not the component is active. The timer is 
	considered active if it is firing timer events. It 
	will remain active till it's destroyed, or setActive() is called
	with false for a value.
	*/
	bool isActive() {
		return isActive_;
	}

	/**
	Activates the timer. Pass in true to activate the timer, and
	false to turn it off. If the timer is activated, it will
	start to fire timer events.
	*/
	void setActivated( const bool& isActive );

	/**
	Returns the time out interval in milliseconds.
	*/
	int32 getTimeoutInterval() {
		return timeoutInterval_;
	}

	/**
	Set's the time out interval. A new timer event, i.e. 
	TimerPulse will fire an event, ever interval number of 
	milliseconds.
	*/
	void setTimeoutInterval( const int32& interval );

protected:
	bool isActive_;
	int32 timeoutInterval_;
	void onInternalTimerPulse( TimerEvent* event );

	EventHandler* getTimerHandler();
};


}; //end of namespace VCF


#endif // _VCF_TIMERCOMPONENT_H__

/**
$Id$
*/
