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



//enum PushButtonCaptionAlignment{
//	BCA_RIGHT=0,
//	BCA_TOP,
//	BCA_LEFT,
//	BCA_BOTTOM
//};
//
//
//static String PushButtonCaptionAlignmentNames [] = { "BCA_RIGHT",
//											"BCA_TOP",
//											"BCA_LEFT",
//											"BCA_BOTTOM" };


#define PUSHBUTTON_CLASSID		"4ddfe31e-c1c1-4f8a-b8e6-82e041041fd2"


class ImageList;


#define IMAGE_CAPTION_BUFFER		3

static String ButtonCaptionAlignmentNames [] = { "bcaRight",
											"bcaTop",
											"bcaLeft",
											"bcaBottom" };


/**
\class PushButton PushButton.h "vcf/ApplicationKit/PushButton.h"
*Class PushButton documentation
*/
class APPLICATIONKIT_API PushButton : public CustomControl, public Button {
public:
	/**
	@see getCaptionAlignment
	*/
	enum CaptionAlignment {
		bcaCenter=0,
		bcaRight,
		bcaTop,
		bcaLeft,
		bcaBottom,
	};

	/**
	helps the user to know which image index is used
	by the button to paint its different states.
	bisUp is used in the normal state.
	bisDown is used when the button is pressed.
	bisFocused is used when it has the focus.
	bisDisabled is used when the button is disabled.
	bisHover is used when the mouse in the normal state.
	*/
	enum ImageState {
		bisNone         = 0x0,
		bisNormal       = 0x1,
		bisUp=bisNormal,
		bisDown         = 0x2,
		bisDisable      = 0x4,
		bisFocus        = 0x8,
		bisFocusDown    = 0x10,
		bisHighlight    = 0x20,
		bisAll = bisUp|bisDown|bisDisable|bisFocus|bisFocusDown|bisHighlight,
		/* bisLast = bisHover // remove this soon */
	};

public:

	PushButton();

	virtual ~PushButton();

	DELEGATE(ButtonClicked);

	virtual void setName( const String& name );
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

	bool getShowCaption(){
		return showCaption_;
	}

	void setShowCaption( const bool& showCaption );

	/**
	The button resize itself automatically to adjust
	itself to the caption's size.
	*/
	bool getAutoSize() {
		return autoSize_;
	}

	void setAutoSize( const bool& autoSize );

	/**
	gets the calculated size of the button. This is the minimum size for the button
	to contain both caption and image ( if shown ), separated as requested
	by getSeparationImageCaption().
	*/
	Size calcMinimumSize();

	/**
	gets the ImageList instance used to display an image in the button.
	*/
	ImageList* getImageList() {
		return imageList_;
	}

	/**
	sets the ImageList instance used to display an image in the button.
	@param ImageList* imageList, the instance. To set this value to NULL
	is a simple way to disable the display of an image.
	*/
	void setImageList( ImageList* imageList );

	/**
	Tells which image index is used for an image inside the ImageList,
	in order to display the specified ImageState ( i.e. the state of the
	button displayed through a specified image ).
	@param ImageState& imgState, tells which image state we are referring to.
	If the specified ImageState is a combination of more than one ImageState,
	or none of the values bisUp,bisDown,bisDisable,bisFocus,bisHighlight, or
	not a valid number, the return value is -1.
	If no images are used, then the return value is -1.
	*/
	long getBtnImageIndex( const ImageState& imgState );

	/**
	sets which image index is used for an image inside the ImageList,
	in order to display the specified ImageState(s)
	@param const long& btnImageIndex, the desired index in the ImageList
	@param ImageState imgStates, tells which image states are going to be displayed
	with the given image index. The user can specify more than one image state at
	the same time for the given index. If this function is called only once
	for one ImageState only, then that index will be used for all image states.
	@param const bool& redraw, repaint the button once changed the image. The default is true
	but the user may want this false in some cases.
	*/
	void setBtnImageIndex( const long& btnImageIndex, ImageState imgStates=bisNormal, const bool& redraw=false );

	/**
	helper to write less and more clear code.
	For the button image is assumed the bisNormal ImageState.
	*/
	void setBtnImageIndex( ImageList* imageList, const long& btnImageIndex, const CaptionAlignment& captionAlignment=bcaRight, const double& separationImageCaption=5.0 );

	/**
	Tells if the button's caption needs to be aligned on the left, right,
	top or bottom,or it should be centered.
	*/
	CaptionAlignment getCaptionAlignment() {
		return captionAlignment_;
	}

	void setCaptionAlignment( const CaptionAlignment& captionAlignment );

	/**
	tells the separation between image and caption when they are both displayed.
	Unless the function calcCaptionImageRect is overriden, the caption and the image
	are both displayed in a rectangle centered in the button.
	*/
	double getSeparationImageCaption() {
		return separationImageCaption_;
	}

	void setSeparationImageCaption( const double& separationImageCaption ) {
		separationImageCaption_ = separationImageCaption;
	}


	/**
	tells if the buttons has the behaviour of a toggled button. 
	This means that it stays down if clicked until it is clicked again.
	*/
	bool isToggled() {
		return toggled_;
	}

	void setToggled( const bool& toggled ) {
		toggled_ = toggled;
	}

	/**
	tells if the buttons is currently pressed. i.e. if it is in the down state.
	If the button isToggled, then it could be pressed even if we are not clicking on it.
	*/
	bool isPressed() {
		return isPressed_;
	}

	/**
	set the state as pressed for a toggled button.
	This function establish an association between a user's variable and 
	the pressed/unpressed state of the button. For example, if the variable
	is onlyToday_, then toggleButton_->setInitialStatePressed( !onlyToday_ )
	will state that the button will appear pressed when onlyToday_ is false.
	The management of the pressed/unpressed state should be done through
	the click() member function or through mouseClick() or keyUp() handlers,
	so it is suggested to use this function only to set the initial state.
	*/
	void setStatePressed( const bool& pressed );

	/**
	tells if the buttons is currently highlighted, i.e. the mouse is over it.
	*/
	bool isHighlighted() {
		return isHighlighted_;
	}

	/**
	let the user to specify if we want to move the image when pressing the button.
	The default is to move it only if an image index has \em not been specified
	for the bisDown ImageState ( i.e. false if specified, and true if not ). In
	other words the user should paint the down state with in the bisDown image
	if he's using it.
	*/
	bool getMoveImageWhenPressed() {
		return moveImageWhenPressed_;
	}

	void setMoveImageWhenPressed( const bool& moveImageWhenPressed ) {
		moveImageWhenPressed_ = moveImageWhenPressed;
	}

	/**
	let the user to specify if we want to draw the focus rect when the button
	has the focus.  The default is to always draw it.
	Use the value false if the focus is already drawn by the image.
	This flag is automatically set to false if a bisFocus state image is provided,
	but you can set it back to true, if you need, after the focus images are set.
	*/
	bool getDrawFocusRectWhenFocus() {
		return drawFocusRectWhenFocus_;
	}
	void setDrawFocusRectWhenFocus( const bool& drawFocusRectWhenFocus ) {
		drawFocusRectWhenFocus_ = drawFocusRectWhenFocus;
	}

	/**
	same as getDrawFocusRectWhenFocus, but when the button is pressed down.
	This is important for toggled buttons, as the 'focus rect' may be good
	when the button is up, but not when it is down or viceversa.
	This flag is automatically set to true if a bisFocusDown state image is provided,
	but you can set it back to true, if you need, after the focus images are set.
	*/
	bool getDrawFocusRectWhenFocusDown() {
		return drawFocusRectWhenFocusDown_;
	}
	void setDrawFocusRectWhenFocusDown( const bool& drawFocusRectWhenFocusDown ) {
		drawFocusRectWhenFocusDown_ = drawFocusRectWhenFocusDown;
	}

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
	*sets the commad type
	*/
	void setCommandType( const ButtonCommandType& commandType );

protected:
	/**
	event handler called when the button gets the focus
	*/
	void onFocusGained( FocusEvent* event );

	/**
	event handler called when the button looses the focus
	*/
	void onFocusLost( FocusEvent* event );

	/*
	draws the image for the button, if any
	*/
	virtual void drawImage( const Rect& rect, const ButtonState& state, const Rect* imageRect, GraphicsContext* ctx );

	/**
	calculates the central rectangle including both the image and the caption ( if shown ).
	@param const Rect& rect, the rectangle of the button. If the given rectangle is empy,
	then the function returns the minimum rectangle containing both image and caption.
	*/
	virtual Rect calcCenterRect( const Rect& rect, GraphicsContext* context, Rect* captionRect=NULL, Rect* imageRect=NULL );

	/**
	calculates the Rect where the caption should be placed inside the button
	*/
	virtual Rect calcCaptionRect( const Rect& rect, GraphicsContext* context );

	/**
	calculates the Rect where the image should be placed inside the button
	*/
	virtual Rect calcImageRect( const Rect& rect, GraphicsContext* context );

protected:
	String caption_;
	ButtonCommandType commandType_;

	bool showCaption_;
	bool isHighlighted_;
	bool isPressed_;
	bool toggled_;
	bool wasPressed_; // used for a toggle button only
	bool autoSize_;

	ImageList* imageList_;
	double separationImageCaption_;
	CaptionAlignment captionAlignment_;
	std::map< long, ulong32 > imageIndexes_;
	bool moveImageWhenPressed_;
	bool drawFocusRectWhenFocus_;
	bool drawFocusRectWhenFocusDown_;
	long imageStateSpecified_; // the image states explicitely specified

private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.5.2.1  2005/08/01 18:50:31  marcelloptr
*minor changes
*
*Revision 1.5  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.6  2005/07/06 00:23:12  marcelloptr
*two very minor bug fixes more. Hope the last ones.
*
*Revision 1.4.2.5  2005/07/04 03:43:23  marcelloptr
*PushButton, toggled, needs also an image for FocusDown. Management images improved and fully tested.
*
*Revision 1.4.2.4  2005/07/01 15:45:43  marcelloptr
*minor improvements on PushButton
*
*Revision 1.4.2.3  2005/06/29 05:00:03  marcelloptr
*some white spaces
*
*Revision 1.4.2.2  2005/06/26 01:27:53  marcelloptr
*added images to a PushButton
*
*Revision 1.4.2.1  2005/02/27 01:45:33  ddiego
*fixed bug in testing whether a path should be loaded as a bundle.
*added some additional rtti info for certain classes in app kit.
*
*Revision 1.4  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*

*Revision 1.3  2004/09/15 02:39:20  ddiego
*fixed a bug in the declaration of the caption member variable that was incorrectly declared as a std::string when it should have been a String. This causing bad display character to show up. Many, many, many thanks to Duff(Eddie) for tracking this down! Also many thanks to Marcello for catching and fixing this in the current dev branch.
*

*Revision 1.2.2.1  2004/08/19 16:37:57  marcelloptr
*Preparation of the UnicodeString class to accept a custom allocator. Added missed conversion and assignement operators.
*

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


