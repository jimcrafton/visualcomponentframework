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
													const long& messageButtons,	const Dialog::MessageStyle& messageStyle );

	void init();

	virtual OSStatus handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent );
	
	virtual WindowAttributes getCreationWinAttrs();
	
	virtual WindowClass getCreationWinClass();
	
	virtual void close();
private:
	Control* owner_;
	Dialog* dialogComponent_;
	DialogRef dialogRef_;
	WindowRef sheetParent_;
	bool isWindowSheet_;	
	VCF::Rect realSheetBounds_;
	
	void createAsSheetWindow();
	
	void createAsWindow();
};


};




/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/10/28 03:34:16  ddiego
*more dialog updates for osx
*
*Revision 1.2.2.3  2004/10/25 03:23:57  ddiego
*and even more dialog updates. Introduced smore docs to the dialog class and added a new showXXX function.
*
*Revision 1.2.2.2  2004/10/23 18:10:43  ddiego
*mac osx updates, some more fixes for dialog code and for command button peer functionality
*
*Revision 1.2.2.1  2004/10/18 03:10:30  ddiego
*osx updates - add initial command button support, fixed rpoblem in mouse handling, and added dialog support.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


#endif // _VCF_OSXDIALOG_H__


