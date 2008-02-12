#ifndef _VCF_DRAWUISTATE_H__
#define _VCF_DRAWUISTATE_H__
//DrawUIState.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class DrawStates DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
A set of values for different states. These are masked together to form a 
single value that represents the actual state of a UI element such as a
button.
*/
class DrawStates{
public:
	enum {
		/**
		No state is indicated
		*/
		dsNone							= 0x00000000,

		/**
		The element is "active" - the precise specifics of this may be 
		windowing-platform specific.
		*/
		dsActive						= 0x00000001,

		/**
		The element is "enabled" and can receive user input.
		*/
		dsEnabled						= 0x00000002,

		/**
		The element has the keyboard focus and is eligible for keyboard input. In
		general, on most windowing platforms only one UI element can have the keyboard 
		focus at any moment.
		*/
		dsFocused						= 0x00000004,

		/**
		The element is highlighted.
		*/
		dsHighlighted					= 0x00000008,

		/**
		The element is verticallly aligned. The exact meaning depends on the UI element
		in question
		*/
		dsVertical						= 0x00000010,

		/**
		The element is selected.
		*/
		dsSelected						= 0x00000020,

		/**
		The element is "pressed" - this typically only means something 
		with UI elements that are buttons.
		*/
		dsPressed						= 0x00000040,

		/**
		The element is a slider and has tick marks either on the top (if
		it's a horizontal slider) or the left (if it's a vertical slider).
		*/
		dsTickMarksOnTopLeft			= 0x00000080,

		/**
		The element is a slider and has tick marks either on the bottom (if
		it's a horizontal slider) or the right (if it's a vertical slider).
		*/
		dsTickMarksOnBottomRight		= 0x00000100,

		/**
		The tab items (or pages) should be on the top of the tab control
		*/
		dsTabOnTop						= 0x00000200,

		/**
		The tab items (or pages) should be on the bottom of the tab control
		*/
		dsTabOnBottom					= 0x00000400,

		/**
		The tab items (or pages) should be on the left of the tab control
		*/
		dsTabOnLeft						= 0x00000800,

		/**
		The tab items (or pages) should be on the right of the tab control
		*/
		dsTabOnRight					= 0x00001000,

		/**
		The tab element is in front of all other tabs
		*/
		dsTabInFront					= 0x00002000,

		/**
		the scroll bar increment button has been pressed
		*/
		dsScrollBarIncrArrowPressed		= 0x00004000,

		/**
		the scroll bar decrement button has been pressed
		*/
		dsScrollBarDecrArrowPressed		= 0x00008000,

		/**
		the scroll bar "thumb" button has been pressed
		*/
		dsScrollBarThumbPressed			= 0x00010000,

		/**
		The disclose element is "closed". On OS X this is usually
		represented by a triangle that points horizontally to the right.
		On Win32 this is usually a "+" sign.
		*/
		dsDisclosureClosed				= 0x00020000,

		/**
		
		*/
		dsDisclosurePartialOpened		= 0x00040000,

		/**
		The disclose element is "open". On OS X this is usually
		represented by a triangle that points down.
		On Win32 this is usually a "-" sign.
		*/
		dsDisclosureOpened				= 0x00080000,

		/**
		The element is "toggled" in the affirmative. In a check box this
		would typically cause the "check" mark to be visible.
		*/
		dsToggledYes					= 0x00100000,

		/**
		The element is "toggled" in the negative. In a check box this
		would typically cause the "check" mark to be cleared.
		*/
		dsToggledNo						= 0x00200000,

		/**
		The ui element is a menu item separator
		*/
		dsMenuItemSeparator				= 0x00400000,

		/**
		The element is a the default button. Usually, on most windowing platforms,
		the default button is the button that will be "clicked" if the user hits the 
		enter or return key.
		*/
		dsDefaultButton					= 0x00800000,

		/**
		Indicates that the custom color should be used if the underlying
		windowing theme API supports this. 
		*/
		dsUseCustomProgressColor		= 0x01000000,
		dsUseCustomProgressTextColor	= 0x02000000,

		/**
		This indicates that the UI will be a radio button
		like look. In other words only one choice will show up.
		Its typicalle used in menu items. 
		*/
		dsMutualExclusiveToggle			= 0x04000000,

		dsMenuItemHasChildren			= 0x08000000,
		dsMenuItemHasImage				= 0x10000000,

	};	
};



enum BackgroundColors {
	bgShadow = 0,
	bgFace,
	bgHighlight,
	bgActiveCaption,
	bgActiveBorder,
	bgDesktop,
	bgCaptionText,
	bgSelection,
	bgSelectionText,
	bgInactiveBorder,
	bgInactiveCaption,
	bgToolTip,
	bgToolTipText,
	bgMenu,
	bgMenuText,
	bgWindow,
	bgWindowText,
	bgWindowFrame,
	bgTab,
	bgControl,
	bgStatus,
	bgToolbar,
	bgScrollbar,
	bgScrollBarThumb,
	bgScrollBarBtn,
	bgMenuItem,
	bgToolbarButton,
	bgHeader,
	bgHeaderItem,
	bgProgress,
};

/**
\class DrawUIState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
The DrawUIState is a utility class to make it easy to indicate the user interface state of 
a GUI element, such as a button. The base settings indicate whether the element is active,
enabled, focused, or highlighted.

The various sub classes of DrawUIState simply make it easier to identify the state of the
element, as well as adding a few more states, and optionally storing additional state information
like the text or caption of the control.
*/
class DrawUIState {
public:
	DrawUIState(): state_(0){}
	
	virtual ~DrawUIState(){}

	bool isEnabled() const {
		return (state_ & DrawStates::dsEnabled) ? true : false;
	}
	
	bool isFocused() const {
		return (state_ & DrawStates::dsFocused) ? true : false;
	}
	
	bool isActive() const {
		return (state_ & DrawStates::dsActive) ? true : false;
	}
	
	bool isHighlighted() const {
		return (state_ & DrawStates::dsHighlighted) ? true : false;
	}
	
	void setEnabled( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsEnabled;
		}
		else {
			state_ &= ~DrawStates::dsEnabled;
		}
	}
	
	void setFocused( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsFocused;
		}
		else {
			state_ &= ~DrawStates::dsFocused;
		}
	}
	
	void setActive( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsActive;
		}
		else {
			state_ &= ~DrawStates::dsActive;
		}
	}
	
	void setHighlighted( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsHighlighted;
		}
		else {
			state_ &= ~DrawStates::dsHighlighted;
		}
	}
	
	
	
protected:
	int32 state_;
};


/**
\class BackgroundState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class BackgroundState : public DrawUIState {
public:

	
	
	BackgroundState(): colorType_(0) {};	
	
	
	/**
	See the SYS_COLOR_XXX constants in Color.h or BackgroundColors
	*/
	int colorType_;
	
};

/**
\class MenuState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class MenuState : public DrawUIState {
protected:
	enum ModifierMasks{
		mmUndefined = 0,
		mmAlt = 1,
		mmShift = 2,
		mmCtrl = 4
	};

public:
	MenuState() : DrawUIState(), keyCode_(vkUndefined), modifierMask_(0){}

	bool isSelected() const {
		return (state_ & DrawStates::dsSelected) ? true : false;
	}
	
	void setSelected( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsSelected;
		}
		else {
			state_ &= ~DrawStates::dsSelected;
		}
	}

	bool isSeparator() const {
		return (state_ & DrawStates::dsMenuItemSeparator) ? true : false;
	}
	
	void setSeparator( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsMenuItemSeparator;
		}
		else {
			state_ &= ~DrawStates::dsMenuItemSeparator;
		}
	}

	
	bool isToggled() const {
		return  (state_ & DrawStates::dsToggledYes) ? true : false;
	}
	
	void setToggled( bool val ) {
		if ( val ) {
			state_ &= ~DrawStates::dsToggledNo;
			state_ |= DrawStates::dsToggledYes;
		}
		else {
			state_ &= ~DrawStates::dsToggledYes;
			state_ |= DrawStates::dsToggledNo;
		}
	}

	bool isMutuallyExclusive() const {
		return  (state_ & DrawStates::dsMutualExclusiveToggle) ? true : false;
	}
	
	void setMutuallyExclusive( bool val ) {
		if ( val ) {			
			state_ |= DrawStates::dsMutualExclusiveToggle;
		}
		else {
			state_ &= ~DrawStates::dsMutualExclusiveToggle;
		}
	}
	
	bool hasChildren() const {
		return  (state_ & DrawStates::dsMenuItemHasChildren) ? true : false;
	}
	
	void setHasChildren( bool val ) {
		if ( val ) {			
			state_ |= DrawStates::dsMenuItemHasChildren;			
		}
		else {
			state_ &= ~DrawStates::dsMenuItemHasChildren;
		}
	}

	bool menuItemHasImage() const {
		return  (state_ & DrawStates::dsMenuItemHasImage) ? true : false;
	}
	
	void setMenuItemHasImage( bool val ) {
		if ( val ) {			
			state_ |= DrawStates::dsMenuItemHasImage;			
		}
		else {
			state_ &= ~DrawStates::dsMenuItemHasImage;
		}
	}
	
	void setHasShiftKey( bool val ) {
		if ( val ) {
			modifierMask_ |= MenuState::mmShift;
		}
		else {
			modifierMask_ &= ~MenuState::mmShift;
		}
	}

	void setHasControlKey( bool val ) {
		if ( val ) {
			modifierMask_ |= MenuState::mmCtrl;
		}
		else {
			modifierMask_ &= ~MenuState::mmCtrl;
		}
	}

	void setHasAltKey( bool val ) {
		if ( val ) {
			modifierMask_ |= MenuState::mmAlt;
		}
		else {
			modifierMask_ &= ~MenuState::mmAlt;
		}
	}

	bool hasShiftKey() const {
		return ( MenuState::mmShift & modifierMask_ ) != 0;
	}
	
	bool hasAltKey() const {
		return ( MenuState::mmAlt & modifierMask_ ) != 0;
	}
	
	bool hasControlKey() const {
		return ( MenuState::mmCtrl & modifierMask_ ) != 0;
	}

	VirtualKeyCode keyCode_;
	uint32 modifierMask_;
	String menuCaption_;

	/**
	This may be modified during the drawThemeMenuItem() call,
	or it may be set prior to this by the underlying OS windowing
	system during menu item events handled by the framework.
	*/
	Rect imageRect_;
};

/**
\class ButtonState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class ButtonState : public DrawUIState {
public:
	bool isPressed() const {
		return (state_ & DrawStates::dsPressed) ? true : false;
	}
	
	void setPressed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsPressed;
		}
		else {
			state_ &= ~DrawStates::dsPressed;
		}
	}
	
	bool isToggled() const {
		return  (state_ & DrawStates::dsToggledYes) ? true : false;
	}
	
	void setToggled( bool val ) {
		if ( val ) {
			state_ &= ~DrawStates::dsToggledNo;
			state_ |= DrawStates::dsToggledYes;
		}
		else {
			state_ &= ~DrawStates::dsToggledYes;
			state_ |= DrawStates::dsToggledNo;
		}
	}
	
	bool isDefaultButton() const {
		return (state_ & DrawStates::dsDefaultButton) ? true : false;
	}
	
	void setDefaultButton( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsDefaultButton;
		}
		else {
			state_ &= ~DrawStates::dsDefaultButton;
		}
	}

public:	
	String buttonCaption_;
};

/**
\class DisclosureButtonState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class DisclosureButtonState : public DrawUIState {
public:
	bool isClosed() const {
		return (state_ & DrawStates::dsDisclosureClosed) ? true : false;
	}
	
	void setClosed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsDisclosureClosed;
			state_ &= ~(DrawStates::dsDisclosureOpened | DrawStates::dsDisclosurePartialOpened);
		}
		else {
			state_ &= ~DrawStates::dsDisclosureClosed;
		}
	}
	
	bool isPartialOpened() const {
		return (state_ & DrawStates::dsDisclosurePartialOpened) ? true : false;
	}
	
	void setPartialOpened( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsDisclosurePartialOpened;
			state_ &= ~(DrawStates::dsDisclosureOpened | DrawStates::dsDisclosureClosed);
		}
		else {
			state_ &= ~DrawStates::dsDisclosurePartialOpened;
		}
	}
	
	bool isOpened() const {
		return (state_ & DrawStates::dsDisclosureOpened) ? true : false;
	}
	
	void setOpened( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsDisclosureOpened;
			state_ &= ~(DrawStates::dsDisclosurePartialOpened | DrawStates::dsDisclosureClosed);
		}
		else {
			state_ &= ~DrawStates::dsDisclosureOpened;
		}
	}
};


/**
\class ProgressState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class ProgressState : public DrawUIState {
public:
	ProgressState():min_(0.0),max_(100.0),position_(0.0){};
	
	bool isVertical() const {
		return (state_ & DrawStates::dsVertical) ? true : false;
	}
	
	void setVertical( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsVertical;
		}
		else {
			state_ &= ~DrawStates::dsVertical;
		}
	}
	
	void setUseCustomProgressColor( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsUseCustomProgressColor;		
		}
		else {
			state_ &= ~DrawStates::dsUseCustomProgressColor;
		}
	}

	bool useCustomProgressColor() const {
		return state_ & DrawStates::dsUseCustomProgressColor ? true : false;
	}

	void setUseCustomProgressTextColor( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsUseCustomProgressTextColor;		
		}
		else {
			state_ &= ~DrawStates::dsUseCustomProgressTextColor;
		}
	}

	bool useCustomProgressTextColor() const {
		return state_ & DrawStates::dsUseCustomProgressTextColor ? true : false;
	}

	
public:	
	Color customColor_;
	Color customTextColor_;
	String progressCaption_;
	double min_;
	double max_;
	double position_;
};


/**
\class SliderState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class SliderState : public DrawUIState {
public:
	SliderState():min_(0.0),max_(100.0),position_(0.0),tickMarkFrequency_(10.0){};

	bool isVertical() const {
		return (state_ & DrawStates::dsVertical) ? true : false;
	}
	
	void setVertical( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsVertical;
		}
		else {
			state_ &= ~DrawStates::dsVertical;
		}
	}
	
	bool isPressed() const {
		return (state_ & DrawStates::dsPressed) ? true : false;
	}
	
	void setPressed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsPressed;
		}
		else {
			state_ &= ~DrawStates::dsPressed;
		}
	}
	
	bool isTickMarkingOnTopLeft() const {
		return (state_ & DrawStates::dsTickMarksOnTopLeft) ? true : false;
	}
	
	void setTickMarkingOnTopLeft( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsTickMarksOnTopLeft;
		}
		else {
			state_ &= ~DrawStates::dsTickMarksOnTopLeft;
		}
	}
	
	bool isTickMarkingOnBottomRight() const {
		return (state_ & DrawStates::dsTickMarksOnBottomRight) ? true : false;
	}
	
	void setTickMarkingOnBottomRight( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsTickMarksOnBottomRight;
		}
		else {
			state_ &= ~DrawStates::dsTickMarksOnBottomRight;
		}
	}
	
	
	
public:	
	String sliderCaption_;
	double min_;
	double max_;
	double position_;
	double tickMarkFrequency_;
};



/**
\class ScrollBarState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class ScrollBarState : public DrawUIState {
public:
	ScrollBarState(): min_(0.0), max_(0.0), position_(0.0), viewSize_(0.0), buttonType_(sbNone){};

	enum ScrollButtonType {
		sbNone = 0,
		sbUpOrLeftBtn = 1,
		sbDownOrRightBtn = 2
	};

	void setButtonType( ScrollButtonType val ) {
		buttonType_ = val;
	}

	ScrollButtonType getButtonType() {
		return buttonType_;
	}

	bool isUpOrLeftBtn() const {
		return ScrollBarState::sbUpOrLeftBtn == buttonType_ ? true : false;
	}

	bool isDownOrRightBtn() const {
		return ScrollBarState::sbDownOrRightBtn == buttonType_ ? true : false;
	}

	bool isVertical() const {
		return (state_ & DrawStates::dsVertical) ? true : false;
	}
	
	void setVertical( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsVertical;
		}
		else {
			state_ &= ~DrawStates::dsVertical;
		}
	}
	
	bool isScrollBarIncrArrowPressed() const {
		return (state_ & DrawStates::dsScrollBarIncrArrowPressed) ? true : false;
	}
	
	void setScrollBarIncrArrowPressed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsScrollBarIncrArrowPressed;
			
			state_ &= ~(DrawStates::dsScrollBarDecrArrowPressed | DrawStates::dsScrollBarThumbPressed);
		}
		else {
			state_ &= ~DrawStates::dsScrollBarIncrArrowPressed;
		}
	}
	
	bool isScrollBarDecrArrowPressed() const {
		return (state_ & DrawStates::dsScrollBarDecrArrowPressed) ? true : false;
	}
	
	void setScrollBarDecrArrowPressed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsScrollBarDecrArrowPressed;
			
			state_ &= ~(DrawStates::dsScrollBarIncrArrowPressed | DrawStates::dsScrollBarThumbPressed);
		}
		else {
			state_ &= ~DrawStates::dsScrollBarDecrArrowPressed;
		}
	}
	
	bool isScrollBarThumbPressed() const {
		return (state_ & DrawStates::dsScrollBarThumbPressed) ? true : false;
	}
	
	void setScrollBarThumbPressed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsScrollBarThumbPressed;
			
			state_ &= ~(DrawStates::dsScrollBarIncrArrowPressed | DrawStates::dsScrollBarDecrArrowPressed);
		}
		else {
			state_ &= ~DrawStates::dsScrollBarThumbPressed;
		}
	}
	
public:	
	double min_;
	double max_;
	double position_;
	double viewSize_;
	ScrollButtonType buttonType_;
};




/**
\class TabState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class TabState : public DrawUIState {
public:
	bool isPressed() const {
		return (state_ & DrawStates::dsPressed) ? true : false;
	}
	
	void setPressed( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsPressed;
		}
		else {
			state_ &= ~DrawStates::dsPressed;
		}
	}
	
	bool isTabOnTop() const {
		return (state_ & DrawStates::dsTabOnTop) ? true : false;
	}
	
	bool isTabOnBottom() const {
		return (state_ & DrawStates::dsTabOnBottom) ? true : false;
	}
	
	bool isTabOnLeft() const {
		return (state_ & DrawStates::dsTabOnLeft) ? true : false;
	}
	
	bool isTabOnRight() const {
		return (state_ & DrawStates::dsTabOnRight) ? true : false;
	}
	
	void setTabOnTop() {
		int32 val = DrawStates::dsTabOnBottom | DrawStates::dsTabOnLeft | DrawStates::dsTabOnRight;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnTop;
	}
	
	void setTabOnBottom() {
		int32 val = DrawStates::dsTabOnTop | DrawStates::dsTabOnLeft | DrawStates::dsTabOnRight;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnBottom;		
	}
	
	void setTabOnLeft() {
		int32 val = DrawStates::dsTabOnBottom | DrawStates::dsTabOnTop | DrawStates::dsTabOnRight;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnLeft;		
	}
	
	void setTabOnRight() {
		int32 val = DrawStates::dsTabOnBottom | DrawStates::dsTabOnTop | DrawStates::dsTabOnLeft;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnRight;
	}
	
public:	
	String tabCaption_;
};



/**
\class TextState DrawUIState.h "vcf/GraphicsKit/DrawUIState.h"
*/
class TextState : public DrawUIState {
public:
	TextState(): DrawUIState(), themeFontType_(0),wrapText_(false){}
	
	bool isSelected() const {
		return (state_ & DrawStates::dsSelected) ? true : false;
	}
	
	void setSelected( bool val ) {
		if ( val ) {
			state_ |= DrawStates::dsSelected;
		}
		else {
			state_ &= ~DrawStates::dsSelected;
		}
	}
	
public:	
	int themeFontType_;
	String text_;
	bool wrapText_;
};



}; // namespace VCF


#endif //_VCF_DRAWUISTATE_H__

/**
$Id$
*/
