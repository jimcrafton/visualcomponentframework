#ifndef _DATETIMEPICKERCONTROL_H__
#define _DATETIMEPICKERCONTROL_H__
//DateTimePickerControl.h



namespace VCF  {


class APPLICATIONKIT_API DateTimePickerPeer : public Interface  {
public:
	virtual ~DateTimePickerPeer(){}


	virtual DateTime getCurrentDateTime() = 0;
	virtual void setCurrentDateTime( const DateTime& dt ) = 0;

	virtual void setFormat( const String& format ) = 0;

	virtual bool allowsNullDates() = 0;
	virtual void setAllowsNullDates( const bool& val ) = 0;

	virtual bool upDownControlsVisible() = 0;
	virtual void setUpDownControlsVisible( const bool& val )  = 0;

};







typedef Delegate2<Event*,DateTime> DateChangedDelegate; 

class APPLICATIONKIT_API DateTimePickerControl : public Control {
public:
	DateTimePickerControl();
	virtual void paint( GraphicsContext * context );

	DELEGATE(DateChangedDelegate,DateChanged);

	DateTime getCurrentDateTime();
	void setCurrentDateTime( const DateTime& dt );

	String getFormat() {
		return formatStr_;
	}
	void setFormat( const String& format );

	bool allowsNullDates();
	void setAllowsNullDates( const bool& val );
	bool upDownControlsVisible();
	void setUpDownControlsVisible( const bool& val );

protected:
	String formatStr_;
	DateTimePickerPeer* dtpPeer_;

};

};


#endif //_DATETIMEPICKERCONTROL_H__