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

	FocusGained.addHandler( new FocusEventHandler<PushButton>( this,
																&PushButton::onFocusGained,
																"PushButton::onFocusGained" ) );

	FocusLost.addHandler( new FocusEventHandler<PushButton>( this,
																&PushButton::onFocusLost,
																"PushButton::onFocusLost" ) );
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
	if ( NULL != this->imageList_ ) {

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

		long btnImageIndex = getBtnImageIndex( imageState );
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

Rect PushButton::calcCenterRect( const Rect& rect, GraphicsContext* context, Rect* captionRect, Rect* imageRect )
{
	Rect captRect, imgRect, rc;

	if ( showCaption_ || ( NULL != imageList_ ) ) {
		// the caption and the image are both displayed
		// in a rectangle centered in the button

		double sep = separationImageCaption_;

		double ch = 0;
		double cw = 0;
		if ( showCaption_ ) {
			ch = context->getTextHeight( caption_ );
			cw = context->getTextWidth( caption_ );
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

Rect PushButton::calcCaptionRect( const Rect& rect, GraphicsContext* context )
{
	Rect captionRect;

	calcCenterRect( rect, context, &captionRect );

	return captionRect;
}

Rect PushButton::calcImageRect( const Rect& rect, GraphicsContext* context )
{
	Rect captionRect, imageRect;

	calcCenterRect( rect, context, &captionRect, &imageRect );

	return imageRect;
}

Size PushButton::calcMinimumSize()
{
	Size size;

	GraphicsContext* context = this->getContext();

	Rect rect;
	rect.setEmpty(); // this makes to calculate the minimum rect
	Rect rc = calcCenterRect( rect, context );

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
		Rect rc = calcCenterRect( r, context, &captionRect, &imageRect );
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
		ButtonClicked.fireEvent( &event );
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
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htButtonHeight );
}

double PushButton::getPreferredWidth()
{
	return 120;
}

void PushButton::setInitialStatePressed( const bool& pressed )
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

long PushButton::getBtnImageIndex( const ImageState& imgState )
{
	long index = -1;
	std::map< long, ulong32 >::iterator found = imageIndexes_.find( imgState );
	if ( found != imageIndexes_.end() ) {
		index = found->second;
	}

	return index;
}

void PushButton::setBtnImageIndex( const long& btnImageIndex, ImageState imgStates, const bool& redraw )
{
	if ( NULL == imageList_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "No image list specified yet" ) );
	}

	long imageCount = imageList_->getImageCount();
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
		imageIndexes_[ imgStates & bisUp        ] = btnImageIndex;
		imageIndexes_[ imgStates & bisDown      ] = btnImageIndex;
		imageIndexes_[ imgStates & bisDisable   ] = btnImageIndex;
		imageIndexes_[ imgStates & bisFocus     ] = btnImageIndex;
		imageIndexes_[ imgStates & bisFocusDown ] = btnImageIndex;
		imageIndexes_[ imgStates & bisHighlight ] = btnImageIndex;
	}

	imageStateSpecified_ |= ( imgStates & bisUp        );
	imageStateSpecified_ |= ( imgStates & bisDown      );
	imageStateSpecified_ |= ( imgStates & bisDisable   );
	imageStateSpecified_ |= ( imgStates & bisFocus     );
	imageStateSpecified_ |= ( imgStates & bisFocusDown );
	imageStateSpecified_ |= ( imgStates & bisHighlight );

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

void PushButton::setBtnImageIndex( ImageList* imageList, const long& btnImageIndex, const CaptionAlignment& captionAlignment, const double& separationImageCaption ) {
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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.12  2005/07/06 00:23:12  marcelloptr
*two very minor bug fixes more. Hope the last ones.
*
*Revision 1.2.4.11  2005/07/05 03:36:00  marcelloptr
*PushButton, toggled, needs also an image for FocusDown. Management images improved and fully tested.
*
*Revision 1.2.4.8  2005/07/02 20:52:37  marcelloptr
*with the button is pressed, the image was moving when it was higlighted, i.e. when passing the mouse over it
*
*Revision 1.2.4.5  2005/07/02 04:15:19  marcelloptr
*forgotten removeDefaultButton in the dtor was causing crash after closing a MessageDialog
*
*Revision 1.2.4.3  2005/07/01 15:45:43  marcelloptr
*minor improvements on PushButton
*
*Revision 1.2.4.2  2005/06/26 01:27:53  marcelloptr
*added images to a PushButton
*
*Revision 1.2.4.1  2005/02/27 01:45:33  ddiego
*fixed bug in testing whether a path should be loaded as a bundle.
*added some additional rtti info for certain classes in app kit.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.2  2004/07/09 02:01:28  ddiego
*more osx updates
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.10  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.2.2  2003/12/02 05:50:06  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.9.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.9  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.8.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.8  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:13:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.2.8  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.6.2.7  2003/02/03 05:22:55  ddiego
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
*Revision 1.6.2.6  2003/02/02 04:56:40  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.6.2.5  2003/01/23 04:39:10  ddiego
*fixes to x port - issues with lightweight controls not quite drawing right. - a
*bug in the line drawing code when the origin is not 0,0
*
*Revision 1.6.2.4  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6.2.3  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6.2.2  2002/12/27 23:05:07  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6.2.1  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.6  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.5.10.1  2002/09/24 21:02:37  ddiego
*started to work on fixing up the tabbedpages control
*
*Revision 1.5  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.4.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.4  2002/01/26 15:11:09  ddiego
*Default button now working
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


