//Win32DateTimePicker.h
#ifndef _WIN32DATETIMEPICKER_H__
#define _WIN32DATETIMEPICKER_H__


namespace VCF {


class APPLICATIONKIT_API Win32DateTimePicker : public AbstractWin32Component, public DateTimePickerPeer {
public:
	Win32DateTimePicker();

	virtual void create( Control* owningControl );

	virtual Win32Object::CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual DateTime getCurrentDateTime();
	virtual void setCurrentDateTime( const DateTime& dt );

	virtual void setFormat( const String& format );

	virtual bool allowsNullDates();
	virtual void setAllowsNullDates( const bool& val );

	virtual bool upDownControlsVisible();
	virtual void setUpDownControlsVisible( const bool& val );

protected:
	void onControlModelChanged( Event* );
	bool internalChange_;
};

};


#endif //_WIN32DATETIMEPICKER_H__

