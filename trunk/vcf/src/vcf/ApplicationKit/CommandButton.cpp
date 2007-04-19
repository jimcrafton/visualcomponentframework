//CommandButton.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/ApplicationKit/ButtonPeer.h"
#include "vcf/ApplicationKit/Action.h"

using namespace VCF;




CommandButton::CommandButton()
{
	buttonPeer_ = UIToolkit::createButtonPeer( this );

	if ( NULL == buttonPeer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_ =
		dynamic_cast<ControlPeer*>( buttonPeer_ );

	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}


	peer_->create( this );
	peer_->setControl( this );



	commandType_ = BC_NONE;

	isPressed_ = false;

	setVisible( true );

	FocusGained.addHandler( new FocusEventHandler<CommandButton>( this,
																&CommandButton::onFocusGained,
																"CommandButton::onFocusGained" ) );

	FocusLost.addHandler( new FocusEventHandler<CommandButton>( this,
																&CommandButton::onFocusLost,
																"CommandButton::onFocusLost" ) );
}

CommandButton::~CommandButton()
{
	UIToolkit::removeDefaultButton( this );
}

void CommandButton::setName( const String& name )
{
	Control::setName( name );
	if ( isDesigning() && getCaption().empty() ) {
		setCaption( name );
	}
}


void CommandButton::setCaption( const String& caption )
{
	VirtualKeyCode keyCode = UIToolkit::findMnemonic( caption );

	if ( keyCode != vkUndefined ) {
		AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, kmAlt, NULL, true );
		addAcceleratorKey( newAccelKey );
	}

	this->peer_->setText( caption );
}

String CommandButton::getCaption()
{
	String result = peer_->getText();
	if ( getUseLocaleStrings() ) {
		result = System::getCurrentThreadLocale()->translate( result );
	}

	return result;
}

void CommandButton::setCommandType( const ButtonCommandType& commandType )
{
	commandType_ = commandType;
}

ButtonCommandType CommandButton::getCommandType()
{
	return this->commandType_;
}

double CommandButton::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtButtonHeight );
}

double CommandButton::getPreferredWidth()
{
	String s = getCaption();
	GraphicsContext* ctx = this->getContext();
	if ( !s.empty() ) {
		return maxVal<>( Control::getPreferredWidth(), ctx->getTextWidth( s ) + 20 );
	}

	return Control::getPreferredWidth();
}

void CommandButton::mnemonicActivate()
{
	Control::mnemonicActivate();
	click();
}

void CommandButton::click()
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

					case BC_ABORT : {
						dialog->setModalReturnValue( UIToolkit::mrAbort );
					}
					break;

					case BC_IGNORE : {
						dialog->setModalReturnValue( UIToolkit::mrIgnore );
					}
					break;
				}
			}
			frame->close();
		}
	}
}

void CommandButton::paint(GraphicsContext * context)
{

	Rect rect = getClientBounds( true );

	//rect.setRect( 0, 0, rect.getWidth(), rect.getHeight() );

	ButtonState state = buttonPeer_->getState();
	state.setActive( isActive() );

	state.setDefaultButton( this == UIToolkit::getDefaultButton() );
	state.buttonCaption_ = getCaption();

	state.setPressed( isPressed_ );

	context->setCurrentFont( getFont() );
	context->drawThemeButtonRect( &rect, state );
	if ( state.isFocused() ) {
		context->drawThemeButtonFocusRect( &rect ); // MP-
	}
}

void CommandButton::setDefault( const bool& defaultButton )
{
	if ( true == defaultButton ) {
		UIToolkit::setDefaultButton( this );
	}
	else {
		UIToolkit::removeDefaultButton( this );
	}
}

bool CommandButton::isDefault()
{
	return (this == UIToolkit::getDefaultButton());
}

void CommandButton::onFocusGained( FocusEvent* event )
{
	UIToolkit::setDefaultButton( this );
}

void CommandButton::onFocusLost( FocusEvent* event )
{
	UIToolkit::removeDefaultButton( this );
}


/**
$Id$
*/
