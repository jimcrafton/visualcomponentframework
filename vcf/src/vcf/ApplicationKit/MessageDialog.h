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
	class Panel;


	class APPLICATIONKIT_API InvalidMessageDialogException : public BasicException {
	public:
		InvalidMessageDialogException (const String& message ): BasicException(	message ){};
	};

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
		is Dialog::msError, Dialog::msInfo, or Dialog::msWarning, then the standard icon for the
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

		void addActionButton( const String& caption, const UIToolkit::ModalReturnType returnVal, const bool& defaultButton = false );

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
		std::vector<CommandButton*> buttons_;
		Panel* imagePane_;
		Panel* labelsPane_;
		Panel* commandPane_;


		/**
		verifies the state of the dialog as described by showModal();
		*/
		void verifyUIState();
	};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*/


#endif // _VCF_MESSAGEDIALOG_H__


