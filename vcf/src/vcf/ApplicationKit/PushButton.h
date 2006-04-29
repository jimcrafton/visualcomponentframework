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


#endif // _VCF_PUSHBUTTON_H__

/**
$Id$
*/
