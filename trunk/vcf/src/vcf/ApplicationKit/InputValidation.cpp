//InputValidation.cpp
/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/TextModel.h"
#include "vcf/ApplicationKit/TextPeer.h"
#include "vcf/ApplicationKit/InputValidation.h"

using namespace VCF;


InputValidator::InputValidator():
	Component(),
	inputControl_(NULL)
{

}


void InputValidator::handleEvent( Event* e )
{
	Component::handleEvent(e);
	if ( isDesigning() ) {
		return;
	}


	switch ( e->getType() ) {
		case Control::KEYBOARD_DOWN : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_PRESSED : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_UP : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;
	}
}


void InputValidator::setInputControl( TextControl* val )
{
	if ( val != inputControl_ ) {
		inputControl_ = val;
		if ( NULL != inputControl_ ) {
			inputControl_->setInputValidator( this );
		}
	}
}

void InputValidator::resetText()
{
	if ( !isDesigning() && NULL != inputControl_ ) {
		String s = getValidText();
		if ( s != inputControl_->getText() ) {
			inputControl_->setText( s );
		}
	}
}


AlphaNumericValidator::AlphaNumericValidator():
	maxChars_(0),
	invalidChars_("%'*\"+?><:\\")
{

}


String AlphaNumericValidator::getValidText()
{
	String result;

	if ( NULL != inputControl_ ) {
		result = inputControl_->getText();
		if ( !result.empty() ) {
			result = result.substr( 0, minVal(maxChars_ , result.size()) );

			// Remove any invalid characters from the control's text
			for (size_t pos = result.size() - 1; pos >= 0; pos--)
			{
				if ( invalidChars_.find(result[pos]) != String::npos ) {
					result = result.substr(0, pos) + result.substr(pos + 1,result.size()-(pos + 1));
				}
			}
		}
	}

	return result;
}

void AlphaNumericValidator::handleEvent( Event* e )
{
	InputValidator::handleEvent(e);
	if ( isDesigning() ) {
		return;
	}


	switch ( e->getType() ) {
		case Control::KEYBOARD_DOWN : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;

		case Control::KEYBOARD_PRESSED : {
			KeyboardEvent* ke = (KeyboardEvent*)e;

			if ( this->inputControl_->isReadOnly() ) {
				return;
			}

			if ( !invalidChars_.empty() ) {
				// Check if the character is invalid
				if (invalidChars_.find( ke->keyValue ) != String::npos ) {
					InvalidInputEvent e(this);					
					e.invalidChar = ke->keyValue;

					InvalidInput(&e);

					ke->ignoreKeystroke = true;

					return;
				}
			}


			String text = inputControl_->getText();
			if ( text.length() == maxChars_ && maxChars_ && iswprint(ke->keyValue)) {
				
				size_t start = inputControl_->getSelectionStart();
				
				if ( start < maxChars_ && allowCharacter(ke->keyValue) ) {
					inputControl_->setSelectionMark( start, 1 );
					inputControl_->replaceSelectedText( String( 1, ke->keyValue) );
					inputControl_->setSelectionMark( start+1, 0 );
				}

				ke->ignoreKeystroke = true;
				return;
			}

			if ( !this->allowCharacter( ke->keyValue ) ) {
				ke->ignoreKeystroke = true;
			}
		}
		break;

		case Control::KEYBOARD_UP : {
			KeyboardEvent* ke = (KeyboardEvent*)e;
		}
		break;
	}
}

void AlphaNumericValidator::setInvalidCharacters( const String& val )
{
	if ( val != invalidChars_ ) {
		invalidChars_ = val;
		this->resetText();
	}
}

void AlphaNumericValidator::setMaxCharacters( size_t val )
{
	if ( val != maxChars_ ) {
		maxChars_ = val;
		this->resetText();
	}
}