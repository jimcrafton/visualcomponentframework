#ifndef _VCF_PUSHBUTTON_H__
#define _VCF_PUSHBUTTON_H__
//PushButton.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {



enum PushButtonCaptionAlignment{
	BCA_RIGHT=0,
	BCA_TOP,
	BCA_LEFT,
	BCA_BOTTOM
};


static String PushButtonCaptionAlignmentNames [] = { "BCA_RIGHT",
											"BCA_TOP",
											"BCA_LEFT",
											"BCA_BOTTOM" };


#define PUSHBUTTON_CLASSID		"4ddfe31e-c1c1-4f8a-b8e6-82e041041fd2"


class ImageList;


#define IMAGE_CAPTION_BUFFER		3


/**
*Class PushButton documentation
*/
class APPLICATIONKIT_API PushButton : public CustomControl, public Button  {
public:

	PushButton();

	virtual ~PushButton();

	DELEGATE(ButtonClicked);

	/**
	*This macro creates a method for adding a listener to the CommandButton's events
	*/
	virtual void addButtonClickHandler( EventHandler* handler ) {
		ButtonClicked += handler;
	}

	/**
	*This macro creates a method for removing a listener to the CommandButton's events
	*/
	virtual void removeButtonClickHandler( EventHandler* handler ) {
		ButtonClicked -= handler;
	}

	virtual void paint(GraphicsContext * context);

	virtual void click();

	virtual void setDefault( const bool& defaultButton );

	virtual bool isDefault();

	virtual void setCaption( const String& caption );

    virtual String getCaption();

	virtual double getPreferredHeight();

	virtual double getPreferredWidth();

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseEnter( MouseEvent* event );

	virtual void mouseLeave( MouseEvent* event );

	virtual void mouseClick(  MouseEvent* event );

	virtual void keyDown( KeyboardEvent* event );

	virtual void keyUp( KeyboardEvent* event );

	bool isShowingCaption(){
		return showCaption_;
	}

	void setShowCaption( const bool& showCaption );

	long getBtnImageIndex() {
		return BtnImageIndex_;
	}

	void setBtnImageIndex( const long& btnImageIndex );

	ImageList* getImageList() {
		return imageList_;
	}

	void setImageList( ImageList* imageList );

	PushButtonCaptionAlignment getCaptionAlignment() {
		return captionAlignment_;
	}

	void setCaptionAlignment( const PushButtonCaptionAlignment& captionAlignment );

	bool getAutoSizeCaption() {
		return autoSizeForCaption_;
	}

	void setAutoSizeCaption( const bool& autoSizeForCaption );

	/**
	*The command type the button represents.
	*Certain command types will automatically send
	*the event to the dialog they belong to when
	*used on modal dialogs.
	*/
	ButtonCommandType getCommandType() {
		return commandType_;
	}

	/**
	*sets the
	*/
	void setCommandType( const ButtonCommandType& commandType );
protected:
	std::string caption_;
	long BtnImageIndex_;
	ImageList* imageList_;
	bool autoSizeForCaption_;
	bool showCaption_;
	bool isHighlighted_;
	bool isPressed_;
	PushButtonCaptionAlignment captionAlignment_;

	ButtonCommandType commandType_;

	virtual void drawHighLighted( Rect* rect, GraphicsContext* ctx );

	virtual void drawNormal( Rect* rect, GraphicsContext* ctx );

	virtual void drawImage( Rect* rect, Rect* imageRect, GraphicsContext* ctx );

	virtual void drawCaption( Rect* rect, Rect* imageRect, GraphicsContext* ctx );

	void onFocusGained( FocusEvent* event );
	void onFocusLost( FocusEvent* event );


private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.6.4.2  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.6.4.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.6  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:09:42  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.2  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.4.14.1  2003/02/03 05:21:55  ddiego
*added support for command types to the PuchButton class
*added support for clicks in the PuchButton class to auto close a dialog
*if it is parented to one, similar to the CommandButton. This is part of the
*gradual phase out of the CommandButton class
*Add supprt for drawing a focus rect in the PushButton class
*plugged in tabbing bahaviour to the X11UIToolkit. It seems as though
*"Shift" + "Tab" is not being picked up properly
*Finished implementing the X11Dialog::showMessage(String,String) method
*and also add some finishing touches to teh X11Dialog so it displays correctly
*Add some finishing touches to the X11UIToolkit::runModalEventLoop() as well
*
*Revision 1.4  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.3  2002/01/26 15:11:08  ddiego
*Default button now working
*
*Revision 1.2  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PUSHBUTTON_H__


