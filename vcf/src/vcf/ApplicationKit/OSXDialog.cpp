//OSXDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXDialog.h"
#include "vcf/ApplicationKit/OSXControl.h"

using namespace VCF;

OSXDialog::OSXDialog()	:
	owner_(NULL),
	dialogComponent_(NULL),
	isWindowSheet_(false)
{

}

OSXDialog::OSXDialog( Control* owner, Dialog* component ):
	owner_(owner),
	dialogComponent_(component),
	isWindowSheet_(false)
{
	
}

OSXDialog::~OSXDialog()
{

}

NSUInteger OSXDialog::getCreateStyleMask()
{
	return NSTitledWindowMask | NSClosableWindowMask;
}

NSWindow* OSXDialog::allocateWindow() 
{
	return [NSPanel alloc];	
}

void OSXDialog::create( Control* owningControl )
{
	if ( NULL == owner_ ) {
		OSXWindow::create( owningControl );		
		
	}
	else {
		control_ = owningControl;
		
	}
}

void OSXDialog::setBounds( Rect* rect )
{
	realSheetBounds_ = *rect;
	
	OSXWindow::setBounds( rect );
}

VCF::Rect OSXDialog::getBounds()
{
	VCF::Rect result;
	
	if ( isWindowSheet_ && !getVisible() ) {
		result = realSheetBounds_;
	}
	else {
		result = OSXWindow::getBounds();
	}
	
	return result;
}

void OSXDialog::setVisible( const bool& visible )
{
	//we are being displayed - chewck if we need to 
	//"turn into" a sheet from a dialog, or vice-versa
	Dialog* dialog = (Dialog*)control_;
	if ( dialog->isSheetModal() ) {
		if ( !isWindowSheet_ ) {
			
		}
	}
	else {
		
	}
	/*
	
		//check if we are alread a sheet
		
		if ( !isWindowSheet_ ) {
			//oops! We are not a sheet! Store off
			//our current window ref, create a new sheet
			//window, and transfer the controls from our old window ref
			//to our new sheet!
			VCF::Rect oldBounds = control_->getBounds();
			String oldCaption = getText();
			WindowRef oldWnd = windowRef_;
			//remove old handler!!!
			RemoveEventHandler( handlerRef_ );
			
			RemoveEventHandler( contentViewHandlerRef_ );
			
			contentViewHandlerRef_ = NULL;
			handlerRef_ = NULL;
			windowRef_ = NULL;
			
			//creates a new sheet
			createAsSheetWindow();
			
			//copies over the controls from the wnd to the sheet
			copyControlsFromWndRef( oldWnd );
			
			//kill the old window
			DisposeWindow( oldWnd );
			
			//reset the bounds
			control_->setBounds( &oldBounds );
			
			setText( oldCaption );
		}
	}
//	else if ( dialog->isModal() ) {
	//no-op for now??
//	}
	else {
		if ( isWindowSheet_ ) {
			//oops we are a sheet! Transfer us back into a regular window!
			VCF::Rect oldBounds = realSheetBounds_;
			String oldCaption = getText();
			
			WindowRef oldWnd = windowRef_;
			
			//remove old handler!!!
			RemoveEventHandler( handlerRef_ );
			
			RemoveEventHandler( contentViewHandlerRef_ );
			
			contentViewHandlerRef_ = NULL;
			handlerRef_ = NULL;
			windowRef_ = NULL;
			
			createAsWindow();
			
			//copies over the controls from the wnd to the sheet
			copyControlsFromWndRef( oldWnd );
			
			//kill the old window
			DisposeWindow( oldWnd );
			
			//reset the bounds
			setBounds( &oldBounds );
			setText( oldCaption );
		}
	}

	 if ( isWindowSheet_ ) {
		if ( visible ) {
			ShowSheetWindow( windowRef_, sheetParent_ );
			ActivateWindow( windowRef_, TRUE );
		}
		else {
			HideSheetWindow( windowRef_ );
		}
	 }
	 else {
		OSXWindow::setVisible( visible );
		if ( visible ) {
			ActivateWindow( windowRef_, TRUE ); 
			repaint(NULL, false);
		}
	 }
	 */
}

void OSXDialog::close()
{
	 OSXWindow::close(); 
}

void OSXDialog::showMessage( const String& message, const String& caption )
{
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle:@"OK"];
	[alert setAlertStyle:NSInformationalAlertStyle];
	CFTextString tmp(message);
	[alert setMessageText:tmp];
	
	tmp = caption;
	[[alert window] setTitle: tmp];
	
	
	[alert runModal];
	
	[alert release];
}

UIToolkit::ModalReturnType OSXDialog::showMessage( const String& message, const String& caption,
												const int32& messageButtons,	const Dialog::MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrNone;
	
	NSAlert *alert = [[NSAlert alloc] init];
	
	
	CFTextString tmp(message);
	[alert setMessageText:tmp];
	
	tmp = caption;
	[[alert window] setTitle: tmp];
	
	NSAlertStyle alertStyle = NSInformationalAlertStyle;
	
	switch ( messageStyle ){
		case Dialog::msDefault: {

		}
		break;

		case Dialog::msError: {
			alertStyle = NSCriticalAlertStyle;
		}
		break;

		case Dialog::msInfo: {
			alertStyle = NSInformationalAlertStyle;
		}
		break;

		case Dialog::msWarning: {
			alertStyle = NSWarningAlertStyle;
		}
		break;
	}
	
	[alert setAlertStyle:alertStyle];
	
	if ( messageButtons & Dialog::mbOK ) {
		[alert addButtonWithTitle:@"OK"];
	}
	else if ( messageButtons & Dialog::mbOKCancel ) {
		[alert addButtonWithTitle:@"OK"];
		[alert addButtonWithTitle:@"Cancel"];
	}
	else if ( messageButtons & Dialog::mbYesNo ) {
		[alert addButtonWithTitle:@"Yes"];
		[alert addButtonWithTitle:@"No"];
	}
	else if ( messageButtons & Dialog::mbYesNoCancel ) {
		[alert addButtonWithTitle:@"Yes"];
		[alert addButtonWithTitle:@"No"];
		[alert addButtonWithTitle:@"Cancel"];
	}
	else if ( messageButtons & Dialog::mbRetryCancel ) {
		[alert addButtonWithTitle:@"Retry"];
		[alert addButtonWithTitle:@"Cancel"];
	}
	else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		[alert addButtonWithTitle:@"Abort"];
		[alert addButtonWithTitle:@"Retry"];
		[alert addButtonWithTitle:@"Ignore"];
	}

	if ( messageButtons & Dialog::mbHelp ) {
		
	}
	
	
	NSInteger res = [alert runModal];
	
	if ( messageButtons & Dialog::mbOK ) {
		if ( res == NSAlertFirstButtonReturn ) {
			result = UIToolkit::mrOK;
		}
	}
	else if ( messageButtons & Dialog::mbOKCancel ) {
		if ( res == NSAlertFirstButtonReturn ) {
			result = UIToolkit::mrOK;
		}
		else if ( res == NSAlertSecondButtonReturn ) {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbYesNo ) {
		if ( res == NSAlertFirstButtonReturn ) {
			result = UIToolkit::mrYes;
		}
		else if ( res == NSAlertSecondButtonReturn ) {
			result = UIToolkit::mrNo;
		}
	}
	else if ( messageButtons & Dialog::mbYesNoCancel ) {
		if ( res == NSAlertFirstButtonReturn ) {
			result = UIToolkit::mrYes;
		}
		else if ( res == NSAlertSecondButtonReturn ) {
			result = UIToolkit::mrNo;
		}
		else if ( res == NSAlertThirdButtonReturn ) {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbRetryCancel ) {
		if ( res == NSAlertFirstButtonReturn ) {
			result = UIToolkit::mrRetry;
		}
		else if ( res == NSAlertSecondButtonReturn ) {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		if ( res == NSAlertFirstButtonReturn ) {
			result = UIToolkit::mrAbort;
		}
		else if ( res == NSAlertSecondButtonReturn ) {
			result = UIToolkit::mrRetry;
		}
		else if ( res == NSAlertThirdButtonReturn ) {
			result = UIToolkit::mrIgnore;
		}
	}
	
	[alert release];
	
	return result;
}


/**
$Id$
*/
