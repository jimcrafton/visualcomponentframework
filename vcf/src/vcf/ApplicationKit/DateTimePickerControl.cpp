//DateTimePickerControl.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DateTimePickerControl.h"
#include "vcf/GraphicsKit/DrawUIState.h"

#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32DateTimePicker.h"


using namespace VCF;



DateTimePickerControl::DateTimePickerControl()
{

	dtpPeer_ =  new Win32DateTimePicker(); //UIToolkit::createListViewPeer( this );
	peer_ = dynamic_cast<ControlPeer*>(dtpPeer_ );

	if ( NULL == this->peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->create( this );
}


void DateTimePickerControl::paint( GraphicsContext * context )
{
	Rect innerBounds = getClientBounds( false );	

	context->setColor( getColor() );
			
	context->rectangle( &innerBounds );
			
	context->fillPath();
}

DateTime DateTimePickerControl::getCurrentDateTime()
{
	return dtpPeer_->getCurrentDateTime();
}

void DateTimePickerControl::setCurrentDateTime( const DateTime& dt )
{
	dtpPeer_->setCurrentDateTime( dt );
}

void DateTimePickerControl::setFormat( const String& format )
{
	dtpPeer_->setFormat(format );
	formatStr_ = format;
}

bool DateTimePickerControl::allowsNullDates()
{
	return dtpPeer_->allowsNullDates();
}

void DateTimePickerControl::setAllowsNullDates( const bool& val )
{
	dtpPeer_->setAllowsNullDates(val);
}

bool DateTimePickerControl::upDownControlsVisible()
{
	return dtpPeer_->upDownControlsVisible();
}

void DateTimePickerControl::setUpDownControlsVisible( const bool& val )
{
	dtpPeer_->setUpDownControlsVisible(val);
}