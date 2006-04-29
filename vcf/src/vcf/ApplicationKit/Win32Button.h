#ifndef _VCF_WIN32BUTTON_H__
#define _VCF_WIN32BUTTON_H__
//Win32Button.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_DRAWUISTATE_H__
#	include "vcf/GraphicsKit/DrawUIState.h"
#endif // _VCF_DRAWUISTATE_H__

#ifndef _VCF_BUTTONPEER_H__
#	include "vcf/ApplicationKit/ButtonPeer.h"
#endif // _VCF_BUTTONPEER_H__



namespace VCF
{

class Win32Button  : public AbstractWin32Component, public ButtonPeer
{
public:
	Win32Button( CommandButton* component );

	virtual void create( Control* owningControl );

	virtual ~Win32Button();

	virtual Image* getImage();

    virtual void setImage( Image* image );

    virtual ButtonState getState();

	virtual CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

private:
	ButtonState state_;
	CommandButton* commandButton_;
	String windowCaption_;
};

};


#endif // _VCF_WIN32BUTTON_H__

/**
$Id$
*/
