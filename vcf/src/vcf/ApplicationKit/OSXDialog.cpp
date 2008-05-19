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

//void OSXDialog::createAsSheetWindow()/
//{
	//sheetParent_ = NULL;
/*
	WindowAttributes attrs = kWindowCompositingAttribute | kWindowStandardHandlerAttribute;
	
	::Rect bounds = {0,0,0,0};
	
	OSStatus err = CreateNewWindow( kSheetAlertWindowClass, attrs, &bounds, &windowRef_ );
	if ( noErr != err ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("CreateNewWindow() failed!") );
	}
	else {
		isWindowSheet_ = true;
	
		OSXDialog* thisPtr = this;
		err = SetWindowProperty( windowRef_, 
								 VCF_PROPERTY_CREATOR, 
								 VCF_PROPERTY_WINDOW_VAL, 
								 sizeof(OSXDialog*), 
								 &thisPtr );
		
		if ( noErr != err ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("SetWindowProperty() failed!") );
		}
		
		static EventTypeSpec eventsToHandle[] ={
			// { kEventClassWindow, kEventWindowGetIdealSize },
			//{ kEventClassCommand, kEventCommandProcess },
			//{ kEventClassCommand, kEventCommandUpdateStatus },
		{ kEventClassWindow, kEventWindowClose },
		{ kEventClassWindow, kEventWindowActivated },
		{ kEventClassWindow, kEventWindowDeactivated },
		{ kEventClassWindow, kEventWindowFocusAcquired },
		{ kEventClassWindow, kEventWindowFocusRelinquish },
			
		{ kEventClassWindow, kEventWindowDrawContent },
		{ kEventClassMouse, kEventMouseDown },
		{ kEventClassMouse, kEventMouseUp },
		{ kEventClassMouse, kEventMouseMoved },
		{ kEventClassMouse, kEventMouseDragged },
		{ kEventClassMouse, kEventMouseEntered },
		{ kEventClassMouse, kEventMouseExited },
		{ kEventClassMouse, kEventMouseWheelMoved },
		{ kEventClassKeyboard, kEventRawKeyDown },
		{ kEventClassKeyboard, kEventRawKeyUp },
		{ kEventClassWindow, kEventWindowBoundsChanged } };
		
		
		InstallWindowEventHandler( windowRef_,
								   OSXWindow::getEventHandlerUPP(),
								   sizeof(eventsToHandle)/sizeof(eventsToHandle[0]),
								   eventsToHandle,
								   this,
								   &handlerRef_ );
		
		static EventTypeSpec contentViewEvents[] ={ { kEventClassControl, kEventControlDraw } };
		
		ControlRef root = getRootControl();
		InstallEventHandler( GetControlEventTarget( root ), 
							OSXWindow::wndContentViewHandler,
							sizeof(contentViewEvents) / sizeof(EventTypeSpec), 
							contentViewEvents, 
							this, 
							&contentViewHandlerRef_ );
							
		
		Frame* ownerFrame = owner_->getParentFrame();
		sheetParent_ = (WindowRef) ownerFrame->getPeer()->getHandleID();
	}
	*/
//}

//void OSXDialog::createAsWindow()
//{
/*	sheetParent_ = NULL;
	WindowAttributes attrs=getCreationWinAttrs();// = kWindowCompositingAttribute | kWindowStandardHandlerAttribute;
    
    ::Rect bounds = {0,0,0,0};

    OSStatus err = CreateNewWindow( getCreationWinClass(), attrs, &bounds, &windowRef_ );
    if ( noErr != err ) {
        throw RuntimeException( MAKE_ERROR_MSG_2("CreateNewWindow() failed!") );
    }
    else {
		OSXWindow* thisPtr = this;
        err = SetWindowProperty( windowRef_, 
								VCF_PROPERTY_CREATOR, 
								VCF_PROPERTY_WINDOW_VAL, 
								sizeof(OSXWindow*), 
								&thisPtr );

		isWindowSheet_ = false;
		
		if ( noErr != err ) {
            throw RuntimeException( MAKE_ERROR_MSG_2("SetWindowProperty() failed!") );
        }
		
		SetThemeWindowBackground( windowRef_, kThemeBrushSheetBackgroundTransparent, true );
		
        static EventTypeSpec eventsToHandle[] ={
                            // { kEventClassWindow, kEventWindowGetIdealSize },
                            //{ kEventClassCommand, kEventCommandProcess },
                            //{ kEventClassCommand, kEventCommandUpdateStatus },
                            { kEventClassWindow, kEventWindowClose },
                            { kEventClassWindow, kEventWindowActivated },
                            { kEventClassWindow, kEventWindowDeactivated },
                            { kEventClassWindow, kEventWindowFocusAcquired },
                            { kEventClassWindow, kEventWindowFocusRelinquish },

                            { kEventClassWindow, kEventWindowDrawContent },
                            { kEventClassMouse, kEventMouseDown },
                            { kEventClassMouse, kEventMouseUp },
                            { kEventClassMouse, kEventMouseMoved },
                            { kEventClassMouse, kEventMouseDragged },
                            { kEventClassMouse, kEventMouseEntered },
                            { kEventClassMouse, kEventMouseExited },
                            { kEventClassMouse, kEventMouseWheelMoved },
                            { kEventClassKeyboard, kEventRawKeyDown },
                            { kEventClassKeyboard, kEventRawKeyUp },
                            { kEventClassWindow, kEventWindowBoundsChanged } };


        InstallWindowEventHandler( windowRef_,
                                    OSXWindow::getEventHandlerUPP(),
                                    sizeof(eventsToHandle)/sizeof(eventsToHandle[0]),
                                    eventsToHandle,
                                    this,
                                    &handlerRef_ );
		
				
		static EventTypeSpec contentViewEvents[] ={ { kEventClassControl, kEventControlDraw } };
		
		ControlRef root = getRootControl();
		InstallEventHandler( GetControlEventTarget( root ), 
							OSXWindow::wndContentViewHandler,
							sizeof(contentViewEvents) / sizeof(EventTypeSpec), 
							contentViewEvents, 
							this, 
							&contentViewHandlerRef_ );
	}
	*/
//}

void OSXDialog::create( Control* owningControl )
{
	if ( NULL == owner_ ) {
		OSXWindow::create( owningControl );
	}
	else {
		control_ = owningControl;
		
		//createAsSheetWindow();
		//EventHandler* ev = new ClassProcedure1<Event*,Control>( owningControl, &Control::handleEvent );			
		//UIToolkit::postEvent( ev, new VCF::ComponentEvent( owningControl, Component::COMPONENT_CREATED ),	true );
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
	
	/*
	Dialog* dialog = (Dialog*)control_;
	if ( dialog->isSheetModal() ) {
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
	/*
	DialogItemIndex itemIndex;
	CFTextString msg;
	msg = message;
	
	
	CreateStandardAlert( kAlertPlainAlert, 
						 msg, 
						 NULL, 
						 NULL,
						 &dialogRef_ );
						 
	windowRef_ = GetDialogWindow(dialogRef_);
	
	setText( caption );
	
	RunStandardAlert (dialogRef_, NULL, &itemIndex);
	
	dialogRef_ = NULL;
	*/
}

UIToolkit::ModalReturnType OSXDialog::showMessage( const String& message, const String& caption,
												const int32& messageButtons,	const Dialog::MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrNone;
	/*
	
	DialogItemIndex itemIndex;
	CFTextString msg;
	msg = message;
	
	AlertStdCFStringAlertParamRec alertParams;
	
    AlertType alertType = kAlertPlainAlert;
	
	GetStandardAlertDefaultParams(&alertParams,kStdCFStringAlertVersionOne);
	
	switch ( messageStyle ){
		case Dialog::msDefault: {

		}
		break;

		case Dialog::msError: {
			alertType = kAlertStopAlert;
		}
		break;

		case Dialog::msInfo: {
			alertType = kAlertNoteAlert;
		}
		break;

		case Dialog::msWarning: {
			alertType = kAlertCautionAlert;
		}
		break;
	}
	
	if ( messageButtons & Dialog::mbOK ) {
		alertParams.defaultText=(CFStringRef)kAlertDefaultOKText;  
		alertParams.defaultButton=kAlertStdAlertOKButton;  
	}
	else if ( messageButtons & Dialog::mbOKCancel ) {
		alertParams.cancelText = (CFStringRef)kAlertDefaultCancelText;
		alertParams.cancelButton = kAlertStdAlertCancelButton;
	}
	else if ( messageButtons & Dialog::mbYesNo ) {
		alertParams.defaultText = CFSTR("Yes");
		
		alertParams.cancelText = CFSTR("No");
		alertParams.cancelButton = kAlertStdAlertOtherButton;
	}
	else if ( messageButtons & Dialog::mbYesNoCancel ) {
		alertParams.defaultText = CFSTR("Yes");
		
		alertParams.cancelText = CFSTR("No");
		alertParams.cancelButton = kAlertStdAlertOtherButton;
		
		alertParams.otherText = CFSTR("Cancel");
	}
	else if ( messageButtons & Dialog::mbRetryCancel ) {
		alertParams.defaultText = CFSTR("Retry");
		
		alertParams.cancelText = CFSTR("Cancel");
		alertParams.cancelButton = kAlertStdAlertOtherButton;
	}
	else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		alertParams.defaultText = CFSTR("Abort");
		
		alertParams.cancelText = CFSTR("Retry");
		alertParams.cancelButton = kAlertStdAlertOtherButton;
		
		alertParams.otherText = CFSTR("Ignore");
	}

	if ( messageButtons & Dialog::mbHelp ) {
		
	}
						
	CreateStandardAlert( alertType, 
						 msg, 
						 NULL, 
						 &alertParams,
						 &dialogRef_ );
						 
	windowRef_ = GetDialogWindow(dialogRef_);
	
	setText( caption );
	
	RunStandardAlert (dialogRef_, NULL, &itemIndex);
	
	if ( messageButtons & Dialog::mbOK ) {
		if ( itemIndex == 1 ) {
			result = UIToolkit::mrOK;
		}
		else {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbOKCancel ) {
		if ( itemIndex == 1 ) {
			result = UIToolkit::mrOK;
		}
		else if ( itemIndex == 2 ) {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbYesNo ) {
		if ( itemIndex == 1 ) {
			result = UIToolkit::mrYes;
		}
		else if ( itemIndex == 2 ) {
			result = UIToolkit::mrNo;
		}
	}
	else if ( messageButtons & Dialog::mbYesNoCancel ) {
		if ( itemIndex == 1 ) {
			result = UIToolkit::mrYes;
		}
		else if ( itemIndex == 2 ) {
			result = UIToolkit::mrNo;
		}
		else if ( itemIndex == 3 ) {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbRetryCancel ) {
		if ( itemIndex == 1 ) {
			result = UIToolkit::mrRetry;
		}
		else if ( itemIndex == 2 ) {
			result = UIToolkit::mrCancel;
		}
	}
	else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		if ( itemIndex == 1 ) {
			result = UIToolkit::mrAbort;
		}
		else if ( itemIndex == 2 ) {
			result = UIToolkit::mrRetry;
		}
		else if ( itemIndex == 3 ) {
			result = UIToolkit::mrIgnore;
		}
	} 
	
	dialogRef_ = NULL;
	*/
	return result;
}

void OSXDialog::init()
{

}
/*
OSStatus OSXDialog::handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	UInt32 whatHappened = GetEventKind (theEvent);
	switch ( GetEventClass( theEvent ) )  {
		case kEventClassWindow : {
            switch( whatHappened ) {
				case kEventWindowActivated : {
					printf( "\n\n\t!!!!!!\tOSXDialog kEventWindowActivated\t!!!!!\n\n\n" );
					
					printf( "\tActive frame: %p, dialog: %p\n\n", Frame::getActiveFrame(), control_ );
					
					return OSXWindow::handleOSXEvent( nextHandler, theEvent );
				}
				break;
				
                case kEventWindowClose : {

                    OSStatus result = noErr;//::CallNextEventHandler( nextHandler, theEvent );

                    VCF::Dialog* dlg = (VCF::Dialog*)getControl();

                    if ( dlg->allowClose() ) {

                        VCF::FrameEvent event( getControl(), Frame::CLOSE_EVENT );


                        dlg->FrameClose( &event );

                        if ( dlg->isModal() ){
							if ( isWindowSheet_ ) {
								HideSheetWindow( windowRef_ );
							}
							result = ::CallNextEventHandler( nextHandler, theEvent );
																			
							//EventLoopRef currentLoop = GetCurrentEventLoop();
							QuitAppModalLoopForWindow( windowRef_ );
                        }
						else if ( dlg->isSheetModal() ) {
							if ( isWindowSheet_ ) {
								HideSheetWindow( windowRef_ );
							}
							result = ::CallNextEventHandler( nextHandler, theEvent );							
						}
						else {						
							result = ::CallNextEventHandler( nextHandler, theEvent );
						}

                    }
					else {
						result = noErr;
					}
					
					return result;
                }
                break;
			}
		}
	}
				
	return OSXWindow::handleOSXEvent( nextHandler, theEvent );
}
*/

/**
$Id$
*/
