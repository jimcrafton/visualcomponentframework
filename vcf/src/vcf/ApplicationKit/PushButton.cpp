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
	BtnImageIndex_ = -1;
	imageList_ = NULL;
	autoSizeForCaption_ = true;
	isHighlighted_ = false;
	captionAlignment_ = BCA_RIGHT;
	isPressed_ = false;

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

}

void PushButton::drawHighLighted( Rect* rect, GraphicsContext* ctx )
{
	Rect tmp = *rect;
	tmp.inflate( -1, 0 );

	ButtonState state;
	state.setActive( true );
	state.setEnabled( isEnabled() );
	state.setPressed( isPressed_ );
	state.setFocused( true );	
	ctx->drawThemeButtonRect( &tmp, state );	
}

void PushButton::drawNormal( Rect* rect, GraphicsContext* ctx )
{
	Rect tmp = *rect;
	tmp.inflate( -1, 0 );
	ButtonState state;
	state.setActive( true );
	state.setEnabled( isEnabled() );
	state.setPressed( isPressed_ );
	state.setFocused( isFocused() || (this == UIToolkit::getDefaultButton()) );
	
	ctx->drawThemeButtonRect( &tmp, state );
}

void PushButton::drawImage( Rect* rect, Rect* imageRect, GraphicsContext* context )
{
	if ( NULL != this->imageList_ ) {
		if (this->BtnImageIndex_ >= 0 ) {
			switch ( captionAlignment_ ) {
				case BCA_RIGHT : {
					imageRect->top_ = maxVal<double>( rect->top_, (rect->getHeight()/2.0) - (imageList_->getImageHeight()/2.0) );
					imageRect->bottom_ = minVal<double>( rect->bottom_, imageRect->top_ + imageList_->getImageHeight() );

					imageRect->left_ = rect->left_ + 2;
					imageRect->right_ = imageRect->left_ + minVal<double>( rect->getWidth(), imageList_->getImageWidth() );
				}
				break;

				case BCA_TOP : {
					imageRect->top_ += context->getTextHeight( caption_ ) + IMAGE_CAPTION_BUFFER;
					imageRect->bottom_ = minVal<double>( imageList_->getImageHeight(), rect->getHeight() );

					imageRect->left_ = (rect->getWidth()/2.0) - (imageList_->getImageWidth()/2.0);
					imageRect->right_ = imageList_->getImageWidth();
				}
				break;

				case BCA_LEFT : {
					imageRect->right_ = rect->right_;
					imageRect->left_ = maxVal<double>( rect->left_, imageRect->right_ - imageList_->getImageWidth() );
					imageRect->top_ += context->getTextHeight( caption_ ) + IMAGE_CAPTION_BUFFER;
					imageRect->bottom_ = minVal<double>( imageList_->getImageHeight(), rect->getHeight() );
				}
				break;

				case BCA_BOTTOM : {
					imageRect->top_ = rect->top_;//context->getTextHeight( caption_ ) + IMAGE_CAPTION_BUFFER;
					imageRect->bottom_ = imageRect->top_ + ( minVal<double>( imageList_->getImageHeight(), rect->getHeight() ) );

					imageRect->left_ = (rect->getWidth()/2.0) - (imageList_->getImageWidth()/2.0);
					imageRect->right_ = imageList_->getImageWidth();
				}
				break;
			}
			//imageRect->inflate( -2, -2 );
			if ( true == isPressed_ ) {
				imageRect->setRect( imageRect->left_ + 1.0, imageRect->top_ + 1.0, imageRect->right_ + 1.0, imageRect->bottom_ + 1.0 );
			}
			imageList_->draw( context, BtnImageIndex_, imageRect );
		}
	}
}

void PushButton::drawCaption( Rect* rect, Rect* imageRect, GraphicsContext* context )
{
	if ( true == showCaption_ ) {
		Rect textRect = *rect;

		switch ( captionAlignment_ ) {
			case BCA_RIGHT : {
				textRect.top_ = maxVal<double>( rect->top_, (rect->getHeight()/2.0) - (context->getTextHeight( caption_ ) / 2.0) );
				textRect.bottom_ = minVal<double>( rect->bottom_, textRect.top_ + context->getTextHeight( caption_ ) );
				if ( (NULL != this->imageList_) && (BtnImageIndex_ >= 0) ) {
					textRect.left_ = imageRect->right_ + IMAGE_CAPTION_BUFFER;
					textRect.right_ = rect->right_;
				}
				else {
					textRect.left_ = maxVal<double>( rect->left_, (rect->getWidth() / 2.0) - (context->getTextWidth( caption_ )/2.0) );
					textRect.right_ = minVal<double>( rect->right_, textRect.left_ + context->getTextWidth( caption_ ) );
				}
			}
			break;

			case BCA_TOP : {
				textRect.left_ = maxVal<double>( rect->left_, (rect->getWidth() / 2.0) - (context->getTextWidth( caption_ )/2.0) );
				textRect.right_ = minVal<double>( rect->right_, textRect.left_ + context->getTextWidth( caption_ ) );
				if ( (NULL != this->imageList_) && (BtnImageIndex_ >= 0) ) {
					textRect.top_ = rect->top_;
					textRect.bottom_ = imageRect->top_;
				}
				else {
					textRect.top_ = maxVal<double>( rect->top_, (rect->getHeight()/2.0) - (context->getTextHeight( caption_ ) / 2.0) );
					textRect.bottom_ = minVal<double>( rect->bottom_, textRect.top_ + context->getTextHeight( caption_ ) );
				}
			}
			break;

			case BCA_LEFT : {
				textRect.top_ = maxVal<double>( rect->top_, (rect->getHeight()/2.0) - (context->getTextHeight( caption_ ) / 2.0) );
				textRect.bottom_ = minVal<double>( rect->bottom_, textRect.top_ + context->getTextHeight( caption_ ) );
				if ( (NULL != this->imageList_) && (BtnImageIndex_ >= 0) ) {
					textRect.left_ = rect->left_;
					textRect.right_ = imageRect->left_ - IMAGE_CAPTION_BUFFER;
				}
				else {
					textRect.left_ = maxVal<double>( rect->left_, (rect->getWidth() / 2.0) - (context->getTextWidth( caption_ )/2.0) );
					textRect.right_ = minVal<double>( rect->right_, textRect.left_ + context->getTextWidth( caption_ ) );
				}
			}
			break;

			case BCA_BOTTOM : {
				textRect.left_ = maxVal<double>( rect->left_, (rect->getWidth() / 2.0) - (context->getTextWidth( caption_ )/2.0) );
				textRect.right_ = minVal<double>( rect->right_, textRect.left_ + context->getTextWidth( caption_ ) );
				if ( (NULL != this->imageList_) && (BtnImageIndex_ >= 0) ) {
					textRect.top_ = imageRect->bottom_;
					textRect.bottom_ = rect->bottom_;
				}
				else {
					textRect.top_ = maxVal<double>( rect->top_, (rect->getHeight()/2.0) - (context->getTextHeight( caption_ ) / 2.0) );
					textRect.bottom_ = minVal<double>( rect->bottom_, textRect.top_ + context->getTextHeight( caption_ ) );
				}
			}
			break;
		}
		if ( true == isPressed_ ) {
			textRect.setRect( textRect.left_ + 1.0, textRect.top_ + 1.0, textRect.right_ + 1.0, textRect.bottom_ + 1.0 );
		}
		context->setCurrentFont( getFont() );
		context->textBoundedBy( &textRect, caption_, false );
	}
}

void PushButton::paint(GraphicsContext * context)
{
	CustomControl::paint( context );
	Rect r( 0,0,getWidth(), getHeight() );
	r.inflate( -2, -3 );	
	
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
	
	context->drawThemeButtonRect( &r, state );	

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

void PushButton::setCaption( const String& caption )
{
	caption_ = caption;
	repaint();
}

String PushButton::getCaption()
{
	return this->caption_;
}

double PushButton::getPreferredHeight()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htButtonHeight ) + 6;
}

double PushButton::getPreferredWidth()
{
	return 120;
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

	isPressed_ = false;
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
		repaint();
		click();
	}
}

void PushButton::setShowCaption( const bool& showCaption )
{

}

void PushButton::setBtnImageIndex( const long& btnImageIndex )
{

}

void PushButton::setImageList( ImageList* imageList )
{

}


void PushButton::setCaptionAlignment( const PushButtonCaptionAlignment& captionAlignment )
{

}

void PushButton::setAutoSizeCaption( const bool& autoSizeForCaption )
{

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

void PushButton::setCommandType( const ButtonCommandType& commandType )
{
	commandType_ = commandType;
}


/**
*CVS Log info
*$Log$
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


