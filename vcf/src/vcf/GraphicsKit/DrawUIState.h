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

class DrawStates{
public:
	enum {
		dsNone							= 0x00000000,
		dsActive						= 0x00000001,
		dsEnabled						= 0x00000002,
		dsFocused						= 0x00000004,
		dsHighlighted					= 0x00000008,
		dsVertical						= 0x00000010,
		dsSelected						= 0x00000020,
		dsPressed						= 0x00000040,
		dsTickMarksOnTopLeft			= 0x00000080,
		dsTickMarksOnBottomRight		= 0x00000100,
		dsTabOnTop						= 0x00000200,
		dsTabOnBottom					= 0x00000400,
		dsTabOnLeft						= 0x00000800,
		dsTabOnRight					= 0x00001000,
		dsTabInFront					= 0x00002000,
		dsScrollBarIncrArrowPressed		= 0x00004000,
		dsScrollBarDecrArrowPressed		= 0x00008000,
		dsScrollBarThumbPressed			= 0x00010000,
		dsDisclosureClosed				= 0x00020000,
		dsDisclosurePartialOpened		= 0x00040000,
		dsDisclosureOpened				= 0x00080000,
		dsToggledYes					= 0x00100000,
		dsToggledNo						= 0x00200000,
		dsMenuItemSeparator				= 0x00400000,
		dsDefaultButton					= 0x00800000
	};	
};


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
	long state_;
};


class BackgroundState : public DrawUIState {
public:
	
	BackgroundState(): colorType_(0) {};	
	
	
	/**
	See the SYS_COLOR_XXX constants in Color.h
	*/
	int colorType_;
	
};


class MenuState : public DrawUIState {
public:
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
	
	
	String menuCaption_;
};

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

	
	String buttonCaption_;
};


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
	
	
	String progressCaption_;
	double min_;
	double max_;
	double position_;
};



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
	
	
	
	String sliderCaption_;
	double min_;
	double max_;
	double position_;
	double tickMarkFrequency_;
};




class ScrollBarState : public DrawUIState {
public:
	ScrollBarState(): min_(0.0), max_(0.0), position_(0.0), viewSize_(0.0){};

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
	
	double min_;
	double max_;
	double position_;
	double viewSize_;
};




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
		long val = DrawStates::dsTabOnBottom | DrawStates::dsTabOnLeft | DrawStates::dsTabOnRight;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnTop;
	}
	
	void setTabOnBottom() {
		long val = DrawStates::dsTabOnTop | DrawStates::dsTabOnLeft | DrawStates::dsTabOnRight;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnBottom;		
	}
	
	void setTabOnLeft() {
		long val = DrawStates::dsTabOnBottom | DrawStates::dsTabOnTop | DrawStates::dsTabOnRight;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnLeft;		
	}
	
	void setTabOnRight() {
		long val = DrawStates::dsTabOnBottom | DrawStates::dsTabOnTop | DrawStates::dsTabOnLeft;

		state_&= ~val;
		
		state_ |= DrawStates::dsTabOnRight;
	}
	
	String tabCaption_;
};



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
	
	int themeFontType_;
	String text_;
	bool wrapText_;
};



};


#endif //_VCF_DRAWUISTATE_H__






