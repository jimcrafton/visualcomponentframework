//GTKDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKDialog.h"


using namespace VCF;

GTKDialog::GTKDialog()
		: GTKWindow( 0, 0 )
		, owner_( 0 )
		, dialogComponent_( 0 )
		, isModal_( false )
{}

GTKDialog::GTKDialog( Control* owner, Dialog* component )
		: GTKWindow( owner, component )
		, owner_( owner )
		, dialogComponent_( component )
		, isModal_( false )
{}

GTKDialog::~GTKDialog()
{}

void GTKDialog::create( Control* owningControl )
{}

void GTKDialog::showMessage( const String& message, const String& caption )
{
	GtkWidget * dialog = gtk_message_dialog_new ( 0, GTK_DIALOG_MODAL,
	                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
	                                              message.ansi_c_str() );

	gtk_window_set_title( ( GtkWindow* ) dialog, caption.ansi_c_str() );

	gtk_dialog_run ( GTK_DIALOG ( dialog ) );

	gtk_widget_destroy ( dialog );
}

UIToolkit::ModalReturnType GTKDialog::showMessage( const String& message,
                                                   const String& caption,
                                                   const long& messageButtons,
                                                   const Dialog::MessageStyle& messageStyle )
{

	int gtkButtons = 0;
	int gtkStyle = 0;

	UIToolkit::ModalReturnType result;

	switch ( messageStyle ) {
		case Dialog::msDefault: {
				gtkStyle = GTK_MESSAGE_QUESTION;
			}
			break;

		case Dialog::msInfo: {
				gtkStyle = GTK_MESSAGE_INFO;
			}
			break;

		case Dialog::msError: {
				gtkStyle = GTK_MESSAGE_ERROR;
			}
			break;

		case Dialog::msWarning: {
				gtkStyle = GTK_MESSAGE_WARNING;
			}
			break;
	}

	if ( messageButtons & Dialog::mbOK ) {
		gtkButtons = GTK_BUTTONS_OK;
	} else if ( messageButtons & Dialog::mbOKCancel ) {
		gtkButtons = GTK_BUTTONS_OK_CANCEL;
	} else if ( messageButtons & Dialog::mbYesNo ) {
		gtkButtons = GTK_BUTTONS_YES_NO;
	}


	GtkWidget* dialog = gtk_message_dialog_new ( 0, GTK_DIALOG_MODAL,
	                                             ( GtkMessageType ) gtkStyle,
	                                             ( GtkButtonsType ) gtkButtons,
	                                             message.ansi_c_str() );

	gtk_window_set_title( ( GtkWindow* ) dialog, caption.ansi_c_str() );

	if ( messageButtons & Dialog::mbYesNoCancel ) {
		gtkButtons = GTK_BUTTONS_NONE;
	} else if ( messageButtons & Dialog::mbRetryCancel ) {
		gtkButtons = GTK_BUTTONS_NONE;
	} else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		gtkButtons = GTK_BUTTONS_NONE;
	}

	if ( messageButtons & Dialog::mbHelp ) {
		//add custom help button ?
	}

	//gtk_dialog_run (GTK_DIALOG (dialog));

	gint res = gtk_dialog_run ( GTK_DIALOG ( dialog ) );

	switch ( res ) {
		case GTK_RESPONSE_NONE: {}
			break;

		case GTK_RESPONSE_OK: {}
			break;

		case GTK_RESPONSE_CANCEL: {}
			break;

		case GTK_RESPONSE_CLOSE: {}
			break;

		case GTK_RESPONSE_YES: {}
			break;

		case GTK_RESPONSE_NO: {}
			break;

		case GTK_RESPONSE_APPLY: {}
			break;

		case GTK_RESPONSE_HELP: {}
			break;
	}

	gtk_widget_destroy ( dialog );

	return result;
}

void GTKDialog::setBorder( Border* border )
{}

/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


