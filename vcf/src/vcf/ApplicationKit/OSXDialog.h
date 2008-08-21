#ifndef _VCF_OSXDIALOG_H__
#define _VCF_OSXDIALOG_H__
//OSXDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/OSXWindow.h"
#include "vcf/ApplicationKit/DialogPeer.h"

namespace VCF
{

#define DEFAULT_DLG_WIDTH		120
#define DEFAULT_DLG_HEIGHT		120

class OSXDialog : public OSXWindow, public DialogPeer
{
public:
	/**
	*default constructor used for showMessage calls
	*/
	OSXDialog();

	OSXDialog( Control* owner, Dialog* component );

	virtual ~OSXDialog();

	virtual void create( Control* owningControl );
	
	virtual void setBounds( Rect* rect );
	
	virtual Rect getBounds();
	
	
	virtual void showMessage( const String& message, const String& caption );
	
	
	virtual void setVisible( const bool& visible );

	virtual UIToolkit::ModalReturnType showMessage( const String& message, const String& caption,
													const int32& messageButtons,	const Dialog::MessageStyle& messageStyle );

	virtual void close();
	
	virtual NSUInteger getCreateStyleMask();
	
	virtual NSWindow* allocateWindow();
private:
	Control* owner_;
	Dialog* dialogComponent_;
	bool isWindowSheet_;	
	VCF::Rect realSheetBounds_;	
	
};


};




#endif // _VCF_OSXDIALOG_H__

/**
$Id$
*/
