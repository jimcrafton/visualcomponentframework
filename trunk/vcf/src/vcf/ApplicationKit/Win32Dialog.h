#ifndef _VCF_WIN32DIALOG_H__
#define _VCF_WIN32DIALOG_H__
//Win32Dialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32Dialog.h: interface for the Win32Dialog class.
//
//////////////////////////////////////////////////////////////////////


#include "vcf/ApplicationKit/DialogPeer.h"
#include "vcf/ApplicationKit/Win32Window.h"

namespace VCF
{

#define DEFAULT_DLG_WIDTH		120
#define DEFAULT_DLG_HEIGHT		120

class Win32Dialog : public Win32Window, public DialogPeer
{
public:
	/**
	*default constructor used for showMessage calls
	*/
	Win32Dialog();

	Win32Dialog( Control* owner, Dialog* component );

	virtual ~Win32Dialog();

	virtual void create( Control* owningControl );

	virtual Win32Object::CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual void showMessage( const String& message, const String& caption );

	virtual UIToolkit::ModalReturnType showMessage( const String& message, const String& caption,
													const long& messageButtons,	const Dialog::MessageStyle& messageStyle );

protected:
	virtual DWORD generateStyleForSetParent(VCF::Control* parent);

	Control* owner_;
	Dialog* dialogComponent_;
};


};


#endif // _VCF_WIN32DIALOG_H__

/**
$Id$
*/
