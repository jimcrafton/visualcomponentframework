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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.1  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.7  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.6.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.6  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/12 03:13:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.4.14.2  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4.14.1  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.4  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


