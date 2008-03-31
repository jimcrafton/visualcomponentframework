#ifndef _VCF_WIN32DROPDOWNPEER_H__
#define _VCF_WIN32DROPDOWNPEER_H__
//Win32DropDownPeer.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {
	class APPLICATIONKIT_API Win32DropDownPeer : public AbstractWin32Component, public DropDownPeer {
	public:
		Win32DropDownPeer();
		virtual ~Win32DropDownPeer();

		virtual void create( Control* owningControl );

		virtual Win32Object::CreateParams createParams();

		virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);
	

		virtual void enableEditBox( bool val );
		virtual bool editBoxEnabled();

		virtual void setEditText( const String& text );
		virtual String getEditText();

		virtual void setDropDownWidth( double val );
		virtual double getDropDownWidth();

		virtual void setDropDownCount( const uint32& dropDownCount );

	};

};



#endif //_VCF_WIN32DROPDOWNPEER_H__