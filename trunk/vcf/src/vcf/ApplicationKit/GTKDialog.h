#ifndef _VCF_GTKDIALOG_H__
#define _VCF_GTKDIALOG_H__
//GTKDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_DIALOGPEER_H__
#	include "vcf/ApplicationKit/DialogPeer.h"
#endif // _VCF_DIALOGPEER_H__

#ifndef _VCF_GTKWINDOW_H__
#	include "vcf/ApplicationKit/GTKWindow.h"
#endif // _VCF_GTKWINDOW_H__

namespace VCF {

/**
class GTKDialog documentation
*/

class GTKDialog : public GTKWindow, public DialogPeer  {
public:
	GTKDialog();

	GTKDialog( Control* owner, Dialog* component );


	virtual ~GTKDialog();

	virtual void create( Control* owningControl );

	virtual void showMessage( const String& message, const String& caption );

	virtual UIToolkit::ModalReturnType showMessage( const String& message, const String& caption,
													const long& messageButtons,	const Dialog::MessageStyle& messageStyle );

protected:
	Control* owner_;
	Dialog* dialogComponent_;
	bool isModal_;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_GTKDIALOG_H__


