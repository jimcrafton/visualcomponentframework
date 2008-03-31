//PushButton.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//PushButton.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/PushButton.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;



PushButton::PushButton():
	CustomControl( true )
{
	showCaption_ = true;
	imageList_ = NULL;
	autoSize_ = true;
	isHighlighted_ = false;
	captionAlignment_ = bcaCenter;
	isPressed_ = false;
	toggled_ = false;
	wasPressed_ = false;
	separationImageCaption_ = 5.0;
	moveImageWhenPressed_ = true;
	drawFocusRectWhenFocus_ = true;
	drawFocusRectWhenFocusDown_ = true;
	imageStateSpecified_ = -1;

	commandType_ = BC_NONE;

	FocusGained += new ClassProcedure1<FocusEvent*,PushButton>( this,
																&PushButton::onFocusGained,
																"PushButton::onFocusGained" );

	FocusLost += new ClassProcedure1<FocusEvent*,PushButton>( this,
																&PushButton::onFocusLost,
																"PushButton::onFocusLost" );
}

PushButton::~PushButton()
{

	UIToolkit::removeDefaultButton( this );
}

/*
void PushButton::drawHighLighted( const Rect& rect, GraphicsContext* ctx )
{
	Rect tmp = rect;
	tmp.inflate( -1, 0 );

	ButtonState state;
	state.setActive( true );
	state.setEnabled( isEnabled() );
	state.setPressed( isPressed_ );
	state.setFocused( true );
	ctx->drawThemeButtonRect( &tmp, state );
}

void PushButton::drawNormal( const Rect& rect, GraphicsContext* ctx )
{
	Rect tmp = rect;
	tmp.inflate( -1, 0 );
	ButtonState state;
	state.setActive( true );
	state.setEnabled( isEnabled() );
	state.setPressed( isPressed_ );
	state.setFocused( isFocused() || (this == UIToolkit::getDefaultButton()) );

	ctx->drawThemeButtonRect( &tmp, state );
}

void PushButton::drawCaption( const Rect& rect, Rect* imageRect, GraphicsContext* context )
{
	if ( true == showCaption_ ) {
		Rect textRect = rect;
		/\*
		if ( true == isPressed_ ) {
			textRect.setRect( textRect.left_ + 1.0, textRect.top_ + 1.0, textRect.right_ + 1.0, textRect.bottom_ + 1.0 );
		}
		*\/
		context->setCurrentFont( getFont() );
		context->textBoundedBy( &textRect, caption_, false );
	}
}
*/

void PushButton::drawImage( const Rect& rect, const ButtonState& state, const Rect* imageRect, GraphicsContext* context )
{
	if ( ( NULL != this->imageList_ ) && ( 0 != imageIndexes_.size() ) ) {

		ImageState imageState = bisUp;

		if ( !state.isEnabled() ) {
			imageState = bisDisable;
		}
		else {
			if ( toggled_ ) {
				if ( state.isPressed() ) {
					imageState = bisDown;

					if ( isHighlighted_ && ( imageStateSpecified_ & bisHighlight ) ) {
						imageState = bisHighlight;
					}
					else {
						if ( state.isFocused() ) {
							if ( imageStateSpecified_ & bisFocusDown ) {
								imageState = bisFocusDown;
							}
							else if ( imageStateSpecified_ & bisFocus ) {
								imageState = bisFocus;
							}
						}
					}

				}
				else {
					if ( isHighlighted_ && ( imageStateSpecified_ & bisHighlight ) ) {
						imageState = bisHighlight;
					}
					else {
						if ( state.isFocused() && ( imageStateSpecified_ & bisFocus ) ) {
							imageState = bisFocus;
						}
					}				
				}
			}
			else {
				if ( state.isPressed() ) {
					imageState = bisDown;
				}
				else if ( state.isFocused() ) {
					imageState = bisFocus;
				}
				else if ( isHighlighted_ ) { // state.isHighlighted()
					imageState = bisHighlight;
				}
			}
		}

		int32 btnImageIndex = getBtnImageIndex( imageState );
		if ( 0 <= btnImageIndex ) {
			Rect imgRect = *imageRect;
			//imgRect.inflate( -2, -2 );
			if ( ( true == isPressed_ ) && ( moveImageWhenPressed_ ) ) {
				imgRect.setRect( imgRect.left_ + 1.0, imgRect.top_ + 1.0, imgRect.right_ + 1.0, imgRect.bottom_ + 1.0 );
			}

			if ( 0 == ( imageStateSpecified_ & bisHighlight ) ) {
				// image manipulation here ?
			}

			if ( 0 == ( imageStateSpecified_ & bisFocus ) ) {
				// image manipulation here ?
			}

			imageList_->draw( context, btnImageIndex, &imgRect );

		}
	}
}

Rect PushButton::calcCenterRect( const Rect& rect, Rect* captionRect, Rect* imageRect )
{
	Rect captRect, imgRect, rc;

	if ( showCaption_ || ( NULL != imageList_ ) ) {
		// the caption and the image are both displayed
		// in a rectangle centered in the button

		double sep = separationImageCaption_;

		double ch = 0;
		double cw = 0;
		if ( showCaption_ ) {
			ch = getFont()->getTextHeight( caption_ );
			cw = getFont()->getTextWidth( caption_ );
		}

		double ih = 0;
		double iw = 0;
		if ( NULL != imageList_ ) {
			ih = imageList_->getImageHeight();
			iw = imageList_->getImageWidth();
		}

		if ( !showCaption_ || ( NULL == imageList_ ) ) {
			sep = 0;
		}

		Rect r = rect;
		double rh = r.getHeight();
		double rw = r.getWidth();

		// if the rect is empty, it calculates rect as the minimum rect
		if ( r.isEmpty() ) {
			switch ( captionAlignment_ ) {
				case bcaLeft : case bcaRight : {
					rh = maxVal<double>( ch, ih );
					rw = cw + sep + iw;
				}
				break;

				case bcaTop : case bcaBottom : {
					rh = ch + sep + ih;
					rw = maxVal<double>( cw, iw );
				}
				break;

				case bcaCenter : {
					rh = maxVal<double>( ch, ih );
					rw = maxVal<double>( cw, iw );
				}
				break;
			}
			r.bottom_ = r.top_ + rh;
			r.right_ = r.left_ + rw;
		}

		Point center( ( r.left_ + rw / 2.0 ), r.top_ + ( rh / 2.0 ) );

		// the centered rectangle including both captionRect and imageRect
		double h, w;
		switch ( captionAlignment_ ) {
			case bcaLeft : case bcaRight : {
				sep = minVal<double>( sep, rw-(cw+iw) );
				if ( sep < 0.0 ) sep = 0.0;

				h = maxVal<double>( ch, ih );
				w = cw + sep + iw;
			}
			break;

			case bcaTop : case bcaBottom : {
				sep = minVal<double>( sep, rh-(ch+ih) );
				if ( sep < 0.0 ) sep = 0.0;

				h = ch + sep + ih;
				w = maxVal<double>( cw, iw );
			}
			break;

			case bcaCenter : {
				h = maxVal<double>( ch, ih );
				w = maxVal<double>( cw, iw );
			}
			break;
		}

		rc.top_ = maxVal<double>( r.top_, center.y_ - h/2.0 );
		rc.bottom_ = minVal<double>( r.bottom_, center.y_ + h/2.0 );

		rc.left_ = maxVal<double>( r.left_, center.x_ - w/2.0 );
		rc.right_ = minVal<double>( r.right_, center.x_ + w/2.0 );

		switch ( captionAlignment_ ) {
			case bcaLeft : {
				captRect.top_ = maxVal<double>( rc.top_, center.y_ - ch/2.0 );
				captRect.bottom_ = minVal<double>( rc.bottom_, center.y_ + ch/2.0 );
				captRect.left_ = rc.left_;
				captRect.right_ = rc.left_ + cw;

				imgRect.top_ = maxVal<double>( rc.top_, center.y_ - ih/2.0 );
				imgRect.bottom_ = minVal<double>( rc.bottom_, center.y_ + ih/2.0 );
				imgRect.left_ = rc.right_ - iw;
				imgRect.right_ = rc.right_;
			}
			break;

			case bcaRight : {
				captRect.top_ = maxVal<double>( rc.top_, center.y_ - ch/2.0 );
				captRect.bottom_ = minVal<double>( rc.bottom_, center.y_ + ch/2.0 );
				captRect.left_ = rc.right_ - cw;
				captRect.right_ = rc.right_;

				imgRect.top_ = maxVal<double>( rc.top_, center.y_ - ih/2.0 );
				imgRect.bottom_ = minVal<double>( rc.bottom_, center.y_ + ih/2.0 );
				imgRect.left_ = rc.left_;
				imgRect.right_ = rc.left_ + iw;
			}
			break;

			case bcaTop : {
				captRect.top_ = rc.top_;
				captRect.bottom_ = rc.top_ + ch;
				captRect.left_ = maxVal<double>( rc.left_, center.x_ - cw/2.0 );
				captRect.right_ = minVal<double>( rc.right_, center.x_ + cw/2.0 );

				imgRect.top_ = rc.bottom_ - ih;
				imgRect.bottom_ = rc.bottom_;
				imgRect.left_ = maxVal<double>( rc.left_, center.x_ - iw/2.0 );
				imgRect.right_ = minVal<double>( rc.right_, center.x_ + iw/2.0 );
			}
			break;

			case bcaBottom : {
				captRect.top_ = rc.bottom_ - ch;
				captRect.bottom_ = rc.bottom_;
				captRect.left_ = maxVal<double>( rc.left_, center.x_ - cw/2.0 );
				captRect.right_ = minVal<double>( rc.right_, center.x_ + cw/2.0 );

				imgRect.top_ = rc.top_;
				imgRect.bottom_ = rc.top_ + ih;
				imgRect.left_ = maxVal<double>( rc.left_, center.x_ - iw/2.0 );
				imgRect.right_ = minVal<double>( rc.right_, center.x_ + iw/2.0 );
			}
			break;

			case bcaCenter : {
				captRect.top_ = maxVal<double>( rc.top_, center.y_ - ch/2.0 );
				captRect.bottom_ = minVal<double>( rc.bottom_, center.y_ + ch/2.0 );
				captRect.left_ = maxVal<double>( rc.left_, center.x_ - cw/2.0 );
				captRect.right_ = minVal<double>( rc.right_, center.x_ + cw/2.0 );

				imgRect.top_ = maxVal<double>( rc.top_, center.y_ - ih/2.0 );
				imgRect.bottom_ = minVal<double>( rc.bottom_, center.y_ + ih/2.0 );
				imgRect.left_ = maxVal<double>( rc.left_, center.x_ - iw/2.0 );
				imgRect.right_ = minVal<double>( rc.right_, center.x_ + iw/2.0 );
			}
			break;
		}

	}

	if ( showCaption_ && ( NULL != captionRect ) ) {
		*captionRect = captRect;
	}

	if ( ( NULL != imageList_ ) && ( NULL != imageRect ) ) {
		*imageRect = imgRect;
	}

	return rc;
}

Rect PushButton::calcCaptionRect( const Rect& rect )
{
	Rect captionRect;

	calcCenterRect( rect, &captionRect );

	return captionRect;
}

Rect PushButton::calcImageRect( const Rect& rect )
{
	Rect captionRect, imageRect;

	calcCenterRect( rect, &captionRect, &imageRect );

	return imageRect;
}

Size PushButton::calcMinimumSize()
{
	Size size;

	Rect rect;
	rect.setEmpty(); // this makes to calculate the minimum rect
	Rect rc = calcCenterRect( rect );

	double cw = rc.getWidth();
	double ch = rc.getHeight();
	size.set( cw, ch );

	rect.setRect( 0, 0, cw, ch );

	//// counterbalance what done in paint()
	//rect.inflate( 2, 3 );

	// drawThemeButtonRect requires this ( 4, 4 are just for the focus rect ).
	// It seems that under windows the best dimensions are (5,5)
	rect.inflate( 5, 5 );

	size.set( rect.getWidth(), rect.getHeight() );

	return size;
}

void PushButton::paint(GraphicsContext * context)
{
	CustomControl::paint( context );
	Rect r( 0,0,getWidth(), getHeight() );
	//r.inflate( -2, -3 );

	ButtonState state;
	state.setActive( isActive() );
	state.setEnabled( isEnabled() );
	state.setPressed( isPressed_ );
	state.setFocused( isFocused() || (this == UIToolkit::getDefaultButton()) );
	if ( showCaption_ ) {
		state.buttonCaption_ = caption_;

		if ( getUseLocaleStrings() ) {
			state.buttonCaption_ = System::getCurrentThreadLocale()->translate( caption_ );
		}
	}

	if ( NULL != imageList_ ) {
		// in this order. The image is supposed to stay inside the button border
		// and its focus rect. Otherwise the bitmap needs to draw that too.
		Rect captionRect, imageRect;
		Rect rc = calcCenterRect( r, &captionRect, &imageRect );
		context->drawThemeButtonRect( &r, state, &captionRect );
		drawImage( r, state, &imageRect, context );
	}
	else {
		context->drawThemeButtonRect( &r, state );
	}


	bool drawFocusRect = ( state.isFocused() &&
				( (!isPressed_ && drawFocusRectWhenFocus_ ) || ( isPressed_ && drawFocusRectWhenFocusDown_ ) ) );

	if ( drawFocusRect ) {
		context->drawThemeButtonFocusRect( &r );
	}
}

void PushButton::click()
{
	ButtonEvent event( this, 0 );

	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {
		ButtonClicked( &event );
	}

	if ( BC_NONE != getCommandType() ) {
		//try and find hte parent that is a Dialog
		Control* parent = getParent();
		Frame* frame = dynamic_cast<Frame*>( parent );
		while ( (NULL == frame) && (parent != NULL) ) {
			parent = parent->getParent();
			frame = dynamic_cast<Frame*>( parent );
		}

		if ( NULL != frame ) {
			Dialog* dialog = dynamic_cast<Dialog*>( frame );
			if ( NULL != dialog ) {
				switch ( getCommandType() ){
					case BC_OK : {
						dialog->setModalReturnValue( UIToolkit::mrOK );
					}
					break;

					case BC_CANCEL : {
						dialog->setModalReturnValue( UIToolkit::mrCancel );
					}
					break;

					case BC_YES : {
						dialog->setModalReturnValue( UIToolkit::mrYes );
					}
					break;

					case BC_NO : {
						dialog->setModalReturnValue( UIToolkit::mrNo );
					}
					break;
				}
			}
			frame->close();
		}
	}
}

void PushButton::setName( const String& name )
{
	CustomControl::setName( name );
	if ( isDesigning() && caption_.empty() ) {
		setCaption( name );
	}
}

void PushButton::setCaption( const String& caption )
{
	caption_ = caption;
	repaint();
}

String PushButton::getCaption()
{
	return this->caption_;
}

void PushButton::setCommandType( const ButtonCommandType& commandType )
{
	commandType_ = commandType;
}

double PushButton::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtButtonHeight );
}

double PushButton::getPreferredWidth()
{
	return 120;
}

void PushButton::setStatePressed( const bool& pressed )
{
	isPressed_ = pressed;
	wasPressed_ = isPressed_;
	repaint();
}

void PushButton::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );
	keepMouseEvents();
	isPressed_ = ( event->hasLeftButton() || event->hasRightButton() );
	repaint();
}

void PushButton::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );
	Point* pt = event->getPoint();

	if ( !toggled_ ) {
		isPressed_ = false;
	}
	if ( true == event->hasLeftButton() ) {
		Rect r (0, 0, getWidth(), getHeight() );
		isPressed_ = r.containsPt( pt );
		repaint();
	}
}

void PushButton::mouseUp( MouseEvent* event )
{
	CustomControl::mouseUp( event );
	releaseMouseEvents();
	Rect r( 0, 0, getWidth(), getHeight() );
	bool ptInBounds = r.containsPt( event->getPoint() );
	isPressed_ = false;

	if ( (( event->hasLeftButton() || event->hasRightButton()) && ptInBounds) ) {
		if ( toggled_ ) {
			isPressed_ = !wasPressed_;
			wasPressed_ = isPressed_;
		}

		click();
	}
	repaint();
}

void PushButton::mouseEnter( MouseEvent* event )
{
	isHighlighted_ = true;
	repaint();
}

void PushButton::mouseLeave( MouseEvent* event )
{
	isHighlighted_ = false;
	if ( toggled_ ) {
		isPressed_ = wasPressed_;
	}
	repaint();
}

void PushButton::mouseClick(  MouseEvent* event )
{

}

void PushButton::keyDown( KeyboardEvent* event )
{
	if ( vkReturn == event->getVirtualCode() ) {

	}
	else if ( vkSpaceBar == event->getVirtualCode() ) {
		isPressed_ = true;
		repaint();
	}
}

void PushButton::keyUp( KeyboardEvent* event )
{
	if ( vkReturn == event->getVirtualCode() ) {
		click();
	}
	else if ( vkSpaceBar == event->getVirtualCode() ) {
		isPressed_ = false;
		if ( toggled_ ) {
			isPressed_ = !wasPressed_;
			wasPressed_ = isPressed_;
		}
		repaint();
		click();
	}
}

void PushButton::setShowCaption( const bool& showCaption )
{
	showCaption_ = showCaption;
	repaint();
}

int32 PushButton::getBtnImageIndex( const ImageState& imgState )
{
	int32 index = -1;
	std::map< int32, uint32 >::iterator found = imageIndexes_.find( imgState );
	if ( found != imageIndexes_.end() ) {
		index = found->second;
	}

	return index;
}

void PushButton::setBtnImageIndex( const int32& btnImageIndex, ImageState imgStates, const bool& redraw )
{
	if ( NULL == imageList_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "No image list specified yet" ) );
	}

	if ( imgStates != ( imgStates & bisAll ) ) {
		String msg = Format("The specified image state(s) [0x00%x] is not valid ( see PushButtons::bisAll mask ).") % (int)imgStates ;
		StringUtils::trace( msg + "\n" );
		imgStates = (PushButton::ImageState)( imgStates & bisAll );
	}

	int32 imageCount = imageList_->getImageCount();
	if ( ( btnImageIndex < 0 ) || ( imageCount <= btnImageIndex ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( Format("PushButton request to set an image index [%d] outside range [0,%d]") % btnImageIndex % imageCount ) );
	}


	if ( 0 == imageIndexes_.size() ) {
		imageIndexes_[ bisUp        ] = btnImageIndex;
		imageIndexes_[ bisDown      ] = btnImageIndex;
		imageIndexes_[ bisDisable   ] = btnImageIndex;
		imageIndexes_[ bisFocus     ] = btnImageIndex;
		imageIndexes_[ bisFocusDown ] = btnImageIndex;
		imageIndexes_[ bisHighlight ] = btnImageIndex;
		imageStateSpecified_ = 0;
	}
	else {
		// note: we need not to add imageIndexes_[0]
		if ( 0 != ( imgStates & bisUp ) ) {
			imageIndexes_[ bisUp ] = btnImageIndex;
		}
		if ( 0 != ( imgStates & bisDown ) ) {
			imageIndexes_[ bisDown ] = btnImageIndex;
		}
		if ( 0 != ( imgStates & bisDisable ) ) {
			imageIndexes_[ bisDisable ] = btnImageIndex;
		}
		if ( 0 != ( imgStates & bisFocus ) ) {
			imageIndexes_[ bisFocus ] = btnImageIndex;
		}
		if ( 0 != ( imgStates & bisFocusDown ) ) {
			imageIndexes_[ bisFocusDown ] = btnImageIndex;
		}
		if ( 0 != ( imgStates & bisHighlight ) ) {
			imageIndexes_[ bisHighlight ] = btnImageIndex;
		}
	}

	imageStateSpecified_ |= ( imgStates & bisUp        );
	imageStateSpecified_ |= ( imgStates & bisDown      );
	imageStateSpecified_ |= ( imgStates & bisDisable   );
	imageStateSpecified_ |= ( imgStates & bisFocus     );
	imageStateSpecified_ |= ( imgStates & bisFocusDown );
	imageStateSpecified_ |= ( imgStates & bisHighlight );


	// if we are changing the bisUp image state, and it has been the only one set,
	// we need to set it for all the other unspecified image states
	if ( 0 != ( imgStates & bisUp ) ) {
		if ( 0 == ( imageStateSpecified_ & bisDown ) ) {
			imageIndexes_[ bisDown      ] = btnImageIndex;
		}
		if ( 0 == ( imageStateSpecified_ & bisDisable ) ) {
			imageIndexes_[ bisDisable   ] = btnImageIndex;
		}
		if ( 0 == ( imageStateSpecified_ & bisFocus ) ) {
			imageIndexes_[ bisFocus     ] = btnImageIndex;
		}
		if ( 0 == ( imageStateSpecified_ & bisFocusDown ) ) {
			imageIndexes_[ bisFocusDown ] = btnImageIndex;
		}
		if ( 0 == ( imageStateSpecified_ & bisHighlight ) ) {
			imageIndexes_[ bisHighlight ] = btnImageIndex;
		}
	}


	// if we specified a bisDown state image then we don't move it
	if ( 0 != ( imageStateSpecified_ & bisDown ) ) {
		moveImageWhenPressed_ = false;
	}

	// if we specified a bisDown state image then we don't move it
	if ( 0 != ( imageStateSpecified_ & bisFocus ) ) {
		drawFocusRectWhenFocus_ = false;
	}
	else {
		if ( 0 != ( imageStateSpecified_ & bisFocusDown ) ) {
			// the bisFocusDown state image supplies for the bisFocus one
			imageIndexes_[ bisFocus     ] = btnImageIndex;
		}
	}

	// if we specified a bisFocusDown state image then we don't move it
	if ( 0 != ( imageStateSpecified_ & bisFocusDown ) ) {
		drawFocusRectWhenFocusDown_ = false;
	}
	else {
		if ( 0 != ( imageStateSpecified_ & bisFocus ) ) {
			// the bisFocus state image supplies for the bisFocusDown one
			imageIndexes_[ bisFocusDown ] = btnImageIndex;
		}
	}

	if ( redraw ) {
		repaint();
	}
}

void PushButton::setBtnImageIndex( ImageList* imageList, const int32& btnImageIndex, const CaptionAlignment& captionAlignment, const double& separationImageCaption ) {
	setImageList( imageList );
	setBtnImageIndex( btnImageIndex, bisNormal );
	setCaptionAlignment( captionAlignment );
	setSeparationImageCaption( separationImageCaption );
}

void PushButton::setImageList( ImageList* imageList )
{
	if ( imageList != imageList_ ) {
		imageList_ = imageList;

		imageIndexes_.clear();
		moveImageWhenPressed_ = true;
		drawFocusRectWhenFocus_ = true;
		imageStateSpecified_ = 0;

		// do not repaint, as we still need to check for the indexes
		// repaint();
	}
}


void PushButton::setCaptionAlignment( const CaptionAlignment& captionAlignment )
{
	captionAlignment_ = captionAlignment;
}

void PushButton::setAutoSize( const bool& autoSize )
{
	//autoSizeForCaption_ = autoSizeForCaption;
	autoSize_ = autoSize;
}

void PushButton::setDefault( const bool& defaultButton )
{
	if ( true == defaultButton ) {
		UIToolkit::setDefaultButton( this );
	}
	else {
		UIToolkit::removeDefaultButton( this );
	}
}

bool PushButton::isDefault()
{
	return (this == UIToolkit::getDefaultButton());
}

void PushButton::onFocusGained( FocusEvent* event )
{
	UIToolkit::setDefaultButton( this );
}

void PushButton::onFocusLost( FocusEvent* event )
{
	UIToolkit::removeDefaultButton( this );
}

bool PushButton::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_HEIGHT ) {
		if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtButtonHeight ) ) {
			strValue = CC_BUTTONHEIGHT;
			return true;
		}
	}

	return CustomControl::generatePropertyValue( fullPropertyName, property, value, strValue );
}


/**
$Id$
*/
