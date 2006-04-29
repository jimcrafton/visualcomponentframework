#ifndef _VCF_MESSAGEDIALOG_H__
#define _VCF_MESSAGEDIALOG_H__
//MessageDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define MESSAGEDIALOG_CLASSID		"c301c1f2-5825-46a6-92d4-a67ba5bb31b4"

namespace VCF {

class Label;
class CommandButton;
class PushButton;
class Panel;
/**
\class InvalidMessageDialogException MessageDialog.h "vcf/ApplicationKit/MessageDialog.h"
*/
class APPLICATIONKIT_API InvalidMessageDialogException : public BasicException {
public:
	InvalidMessageDialogException (const String& message ): BasicException(	message ){};
};


/**
\class MessageDialog MessageDialog.h "vcf/ApplicationKit/MessageDialog.h"
the MessageDialog class let the user to create at run time 
a dialog with many options for customization. Like captions
and images for the buttons.
*/
class APPLICATIONKIT_API MessageDialog : public Dialog {
public:

	MessageDialog();

	virtual ~MessageDialog();

	/**
	This is overridden to verify the following conditions:
	1) message_ is NOT empty (i.e. eqivalent to "" ). If it is, a
	InvalidMessageDialogException is thrown.

	2) information_ is NOT empty. If it is, a
	InvalidMessageDialogException is thrown.

	3) buttons_ is not empty. If it is then we have no buttons - not a good sign,
	which means that a InvalidMessageDialogException will be thrown.

	4) applicationIcon_ is NON NULL. If it is NULL then depending on value
	of style_ a standard icon image is assigned to it. If it is NOT NULL then
	if the style_ is Dialog::msDefault, the image is displayed normally. If the style_
	is Dialog::msError, Dialog::msQuestion, Dialog::msInfo, or Dialog::msWarning, then the standard icon for the 
	value is displayed normal size, while the applicationIcon_ is shrunk by 50% and superimposed
	on top of the standard image, aligned in the lower bottom right hand corner.
	The standard dimensions of the icon are windowing system dependent, but in general on Win32 systems
	the size is 32 X 32, and on MacOSX it would be 64 X 64 pixels.
	*/
	virtual UIToolkit::ModalReturnType showModal();

	/**
	Like the showModal() method, this is overridden to verify the same conditions as showModal().
	See showModal() for more information
	*/
	virtual void show();

	/**
	this adds a standard native button
	*/
	void addActionButton( const String& caption, const UIToolkit::ModalReturnType returnVal, const bool& defaultButton = false );

	/**
	this let to add a push button with images and other capabilities
	*/
	PushButton* addPushButton( const String& caption, const UIToolkit::ModalReturnType returnVal, const bool& defaultButton = false );

	String getMessage() {
		return message_;
	}

	void setMessage( const String& message );

	String getInformation() {
		return information_;
	}

	void setInformation( const String& information );

	Image* getApplicationIcon() {
		return applicationIcon_;
	}

	void setApplicationIcon( Image* icon );

protected:
	bool showTitle_;
	String message_;
	String information_;
	Dialog::MessageStyle style_;
	Image* applicationIcon_;
	Label* messageLabel_;
	Label* infoLabel_;
	std::vector<Button*> buttons_;
	Panel* imagePane_;
	Panel* labelsPane_;
	Panel* commandPane_;


	/**
	verifies the state of the dialog as described by showModal();
	*/
	void verifyUIState();
};


}; // namespace VCF


#endif // _VCF_MESSAGEDIALOG_H__

/**
$Id$
*/
