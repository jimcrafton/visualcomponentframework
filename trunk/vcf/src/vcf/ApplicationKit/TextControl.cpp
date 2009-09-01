//TextControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/DefaultTextModel.h"
#include "vcf/ApplicationKit/TextPeer.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/ApplicationKit/ThemeBorder.h"
#include "vcf/ApplicationKit/InputValidation.h"

using namespace VCF;

TextControl::TextControl( const bool& multiLineControl ):
	readOnly_(false),
	validationStyle_(tvsOnKeyEvent),
	inputState_(0),
	inputValidator_(NULL)
{
	textPeer_ =	UIToolkit::createTextEditPeer( this, multiLineControl );

	if ( NULL == textPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	};


	peer_ = dynamic_cast<ControlPeer*>(textPeer_ );

	peer_->create( this );


	setColor(  GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );
	

	setTextModel( new DefaultTextModel() );

	addComponent( getViewModel() );	

	init();



}

TextControl::~TextControl()
{
	
}

void TextControl::init()
{
	setVisible( true );
	
	//setFocused();
	setEnabled( true );
	
	setCursorID( Cursor::SCT_TEXT );

	setBorder( new ThemeBorder(this,etTextbox) );

	/**
	create default accelerators for handling the 
	following standard keyboard shortcuts:
	UIPolicyManager::saEditUndo
	UIPolicyManager::saEditCut
	UIPolicyManager::saEditCopy
	UIPolicyManager::saEditPaste
	UIPolicyManager::saEditSelectAll
	*/

	enableStandardAccelerators();
}

void TextControl::disableStandardAccelerators()
{
	UIPolicyManager* mgr = UIToolkit::getUIPolicyManager();

	AcceleratorKey::Value val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditUndo);
	UIToolkit::removeAccelerator( val.getKeyCode(), val.getModifierMask(), this );


	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditRedo);
	UIToolkit::removeAccelerator( val.getKeyCode(), val.getModifierMask(), this );

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCut);
	UIToolkit::removeAccelerator( val.getKeyCode(), val.getModifierMask(), this );

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCopy);
	UIToolkit::removeAccelerator( val.getKeyCode(), val.getModifierMask(), this );

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditPaste);
	UIToolkit::removeAccelerator( val.getKeyCode(), val.getModifierMask(), this );

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditSelectAll);
	UIToolkit::removeAccelerator( val.getKeyCode(), val.getModifierMask(), this );
}

void TextControl::enableStandardAccelerators()
{
	EventHandler* ev = NULL;

	UIPolicyManager* mgr = UIToolkit::getUIPolicyManager();

	AcceleratorKey::Value val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditUndo);
	if ( !val.isEmpty() ) {
		ev = new ClassProcedure1<Event*,TextControl>(this, &TextControl::undoAccelerator, "TextControl::undoAccelerator" );
		addAcceleratorKey( val.getKeyCode(), val.getModifierMask(), ev );
	}

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditRedo);
	if ( !val.isEmpty() ) {
		ev = new ClassProcedure1<Event*,TextControl>(this, &TextControl::redoAccelerator, "TextControl::redoAccelerator" );
		addAcceleratorKey( val.getKeyCode(), val.getModifierMask(), ev );
	}


	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCut);
	if ( !val.isEmpty() ) {
		ev = new ClassProcedure1<Event*,TextControl>(this, &TextControl::cutAccelerator, "TextControl::cutAccelerator" );
		addAcceleratorKey( val.getKeyCode(), val.getModifierMask(), ev );
	}

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCopy);
	if ( !val.isEmpty() ) {
		ev = new ClassProcedure1<Event*,TextControl>(this, &TextControl::copyAccelerator, "TextControl::copyAccelerator" );
		addAcceleratorKey( val.getKeyCode(), val.getModifierMask(), ev );
	}

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditPaste);
	if ( !val.isEmpty() ) {
		ev = new ClassProcedure1<Event*,TextControl>(this, &TextControl::pasteAccelerator, "TextControl::pasteAccelerator" );
		addAcceleratorKey( val.getKeyCode(), val.getModifierMask(), ev );
	}

	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditSelectAll);
	if ( !val.isEmpty() ) {
		ev = new ClassProcedure1<Event*,TextControl>(this, &TextControl::selectAllAccelerator, "TextControl::selectAllAccelerator" );
		addAcceleratorKey( val.getKeyCode(), val.getModifierMask(), ev );
	}
}

void TextControl::undoAccelerator( Event* e )
{
	undo();
}

void TextControl::redoAccelerator( Event* e )
{
	redo();
}

void TextControl::cutAccelerator( Event* e )
{
	cut();
}

void TextControl::copyAccelerator( Event* e )
{
	copy();
}

void TextControl::pasteAccelerator( Event* e )
{
	paste();
}

void TextControl::selectAllAccelerator( Event* e )
{
	selectAll();
}

void TextControl::paint( GraphicsContext * context )
{
	Border* border = getBorder();

	Rect innerBounds = getClientBounds( false );

	context->setColor( getColor() );

	context->rectangle( &innerBounds );

	context->fillPath();
}

String TextControl::getText() 
{
	TextModel* tm = getTextModel();
	if ( NULL != tm ) {
		return tm->getText();
	}

	return getViewModel()->getValueAsString( this->getModelKey() );
}

void TextControl::setText( const String& val ) 
{
	TextModel* tm = getTextModel();
	if ( NULL != tm ) {
		tm->setText( val );
	}
	else {
		getViewModel()->setValueAsString( val, getModelKey() );
	}
}


void TextControl::setTextModel( TextModel * model )
{
	setViewModel( model );
}

TextModel* TextControl::getTextModel()
{
	return dynamic_cast<TextModel*>( getViewModel() );
}

uint32 TextControl::getCaretPosition()
{
	uint32 result = 0;
	result = textPeer_->getCaretPosition();
	return result;

}

void TextControl::setCaretPosition( const uint32& caretPos )
{

	textPeer_->setCaretPosition( caretPos );
}

void TextControl::setRightMargin( const double & rightMargin )
{
	textPeer_->setRightMargin( rightMargin );
}

void TextControl::setLeftMargin( const double & leftMargin )
{
	textPeer_->setLeftMargin( leftMargin );
}

uint32 TextControl::getLineCount()
{
	return textPeer_->getLineCount();
}

uint32 TextControl::getCurrentLinePosition()
{
	return textPeer_->getCurrentLinePosition();
}

double TextControl::getLeftMargin()
{
	return textPeer_->getLeftMargin();
}

double TextControl::getRightMargin()
{
	return textPeer_->getRightMargin();
}

Point* TextControl::getPositionFromCharIndex( const uint32& index )
{
	return textPeer_->getPositionFromCharIndex( index );
}

uint32 TextControl::getCharIndexFromPosition( Point* point )
{
	return textPeer_->getCharIndexFromPosition( point );
}

uint32 TextControl::getSelectionStart()
{
	return textPeer_->getSelectionStart();
}

uint32 TextControl::getSelectionCount()
{
	return textPeer_->getSelectionCount();
}

void TextControl::setSelectionMark( const uint32& start, const uint32& count )
{
	textPeer_->setSelectionMark( start, count );
}

void TextControl::selectAll()
{
	TextModel* tm = getTextModel();
	String text = tm->getText();

	textPeer_->setSelectionMark( 0, text.size() );
}

void TextControl::getStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	textPeer_->getStyle( start, length, styles );
	//make sure the dictionary owns the objects it's assigned!!!
	styles.setOwnsObjectValues( true );
}

void TextControl::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	//make sure the dictionary owns the objects it's assigned!!!
	styles.setOwnsObjectValues( true );

	textPeer_->setStyle( start, length, styles );
}

void TextControl::setDefaultStyle( Dictionary& styles )
{
	//make sure the dictionary owns the objects it's assigned!!!
	styles.setOwnsObjectValues( true );

	textPeer_->setDefaultStyle( styles );
}

String TextControl::getSelectedText()
{
	String result;

	uint32 selectionCount = getSelectionCount();

	if ( selectionCount > 0 ) {
		TextModel* tm = getTextModel();
		result = tm->getText();
		result = result.substr( getSelectionStart(), selectionCount );
	}

	return result;
}

void TextControl::replaceSelectedText( const String& text )
{
	uint32 selectionStart = getSelectionStart();
	uint32 selectionCount = getSelectionCount();

	if ( selectionCount == 0 ) {
		throw RuntimeException( "No characters currently selected. Invalid selection count." );
	}

	TextModel* tm = getTextModel();
	tm->replaceText( selectionStart, selectionCount, text );
}

void TextControl::gotFocus( FocusEvent* event )
{

	Model* m = getViewModel();
	TextModel* tm = dynamic_cast<TextModel*>(getViewModel());
	if ( NULL == m ) {
		return;
	}

	String text = m->getValueAsString( getModelKey() );
	
		//tm->getText();

	setSelectionMark( 0, text.size() );	
}

double TextControl::getPreferredHeight()
{
	double result = UIToolkit::getUIMetricValue( UIMetricsManager::mtTextControlHeight );

	if ( NULL != getFont() ) {
		//result = getFont()->getPixelSize() * 1.85;
	}

	return result;
}

void TextControl::modelChanged( Model* oldModel, Model* newModel )
{
	if ( NULL != oldModel ) {
		CallBack* cb = getCallback( "TextControl::onModelValidationFailed" );
		if ( NULL != cb ) {
			oldModel->ModelValidationFailed -= cb;
		}

		cb = getCallback( "TextControl::onModelValidated" );
		if ( NULL != cb ) {
			oldModel->ModelValidated -= cb;
		}
	}

	if ( NULL != newModel ) {
		CallBack* cb = getCallback( "TextControl::onModelValidationFailed" );
		if ( NULL == cb ) {
			cb = new ClassProcedure1<Event*,TextControl>( this, &TextControl::onModelValidationFailed, "TextControl::onModelValidationFailed" );
		}

		newModel->ModelValidationFailed += cb;

		cb = getCallback( "TextControl::onModelValidated" );
		if ( NULL == cb ) {
			cb = new ClassProcedure1<Event*,TextControl>( this, &TextControl::onModelValidated, "TextControl::onModelValidated" );
		}

		newModel->ModelValidated += cb;
	}
}

void TextControl::onModelValidationFailed( Event* e )
{
	ValidationErrorEvent* ve = (ValidationErrorEvent*)e;

	if ( ve->key == getModelKey() ) {
		inputState_ |= tisInputValidationFailed;
		inputState_ &= ~tisInputValidated;
	}
}

void TextControl::onModelValidated( Event* e )
{
	ValidationEvent* ve = (ValidationEvent*)e;

	if ( ve->key == getModelKey() ) {
		inputState_ |= tisInputValidated;
		inputState_ &= ~tisInputValidationFailed;
	}
}

void TextControl::handleEvent( Event* event )
{
	switch( event->getType() ) {

		

		/**
		I moved these two event types together to hopefully better hadnle the 
		text processing, at least for Win32 - hopefully this will not screw things
		up on OSX. 
		The basic idea is to process things like TAB, back space, delete,etc on
		Control::KEYBOARD_DOWN events, while processing actual printable characters
		on the Control::KEYBOARD_PRESSED events
		*/
		case Control::KEYBOARD_DOWN : case Control::KEYBOARD_PRESSED : {
			

			//do not process any events during design mode
			if ( isDesigning() ) {
				Control::handleEvent( event );
				return;
			}					

			if ( !isReadOnly() && !(getComponentState() & Component::csDesigning) ) {

				if ( event->getType() == Control::KEYBOARD_DOWN ) {
					inputState_ = tisProcessing;
				}


				KeyboardEvent* ke = (KeyboardEvent*)event;

				if ( event->getType() == Control::KEYBOARD_DOWN ) {

					if ( NULL != inputValidator_ ) {
						inputValidator_->handleEvent( ke );
					}

					if ( validationStyle_ != tvsOnKeyEvent ) {
						
						return;
					}

					//ignoreKeystroke is only meaningful if we have an
					//input validator set!
					if ( (NULL != inputValidator_) && (ke->ignoreKeystroke) ) {
						return;
					}

					internal_processKeyDown( ke );
				}
				else {

					if ( NULL != inputValidator_ ) {
						inputValidator_->handleEvent( ke );
						if ( ke->ignoreKeystroke ) {
							return;
						}
					}					

					internal_processKeyPress( ke );

					//inputState_ = tisWaitingForInput;
				}				
			}

			Control::handleEvent( event );
		}
		break;

		case Control::KEYBOARD_UP : {
			Control::handleEvent( event );
			if ( NULL != inputValidator_ ) {
				inputValidator_->handleEvent( event );				
			}	
			inputState_ = tisWaitingForInput;
		}
		break;

		case Control::FOCUS_LOST:{

			bool prevFocused = Control::getCurrentFocusedControl() == this;

			Control::handleEvent( event );
			FocusEvent* focusEvent = (FocusEvent*)event;
			
			if ( NULL != inputValidator_ ) {
				inputValidator_->handleEvent( event );
			}

			if ( prevFocused && (validationStyle_ == tvsOnFocusChange) ) {
				String text = getPeer()->getText();
				Model* model = getViewModel();
				model->setValueAsString( text, getModelKey() );
			}
		}
		break;

		default : {
			Control::handleEvent( event );
		}
		break;
	}
}

/**
HACK ALERT!
this is the braindead way - needs to be reworked in the future

for the future we need to be able to insertText and removeText from the
model according to the characters pressed. At first glance this is that
big of a deal: determine if we have a selection, delete the selected
text, and then insert the appropriate character. The problem comes in
determing what causes a delete and what to insert. Normally the only things
that should cause an delete/insert are the set of characters [a..z,A..Z,0..9],
back space, space, and delete. This is a valid assumption assuming en/US language
but for other languages this totally falls down...
#-------------------------------------------------------------------------------#
#UN-HACK ALERT!																	#
#-------------------------------------------------------------------------------#
JC - I have currently implemented this so that we now add text key press at 
a time,	or delete text if appropriate.
*/	

void TextControl::internal_processKeyDown( KeyboardEvent* ke )
{
	if ( ke->dontProcessKeystroke ) {
		return;
	}

	Model* model = getViewModel();
	TextModel* textModel = dynamic_cast<TextModel*>(model);
	switch ( ke->virtualKeyCode ) {
		case vkDelete : {
			uint32 pos =  textPeer_->getSelectionStart();

			if ( NULL == textModel ) {
				String text;
				if ( NULL != model->getFormatter() ) {
					text = getPeer()->getText();
				}
				else {
					text = model->getValueAsString( getModelKey() );
				}

				uint32 size = text.length();

				if ( ( 0 < size ) && pos <= (size-1) ) {
					uint32 length = maxVal<uint32>( 1, textPeer_->getSelectionCount() );
					
					// workaround for a '\r\n' sequence: we need to
					// delete '\n' too at the end of the selection
					uint32 pos2 = pos+length-1;
					if ( pos2 < (size-1)  ) {
						const VCFChar* textBuffer = text.c_str();
						
						if ( textBuffer[pos2] == '\r' ) {
							if ( textBuffer[pos2+1] == '\n' ) {
								length += 1;
							}
						}
					}

					if ( 0 != length ) {
						text.erase( pos, length );
						model->setValueAsString( text, getModelKey() );
						if ( didInputValidationFail() ) {
							ke->ignoreKeystroke = true;
						}
					}
				}
			}
			else {
				//Thanks to Marcello to fixing this!!!
				uint32 size = textModel->getSize();
				if ( ( 0 < size ) && pos <= (size-1) ) {
					uint32 length = maxVal<uint32>( 1, textPeer_->getSelectionCount() );

					// workaround for a '\r\n' sequence: we need to
					// delete '\n' too at the end of the selection
					uint32 pos2 = pos+length-1;
					if ( pos2 < (size-1)  ) {
						String text = textModel->getText();
						const VCFChar* textBuffer = text.c_str();

						if ( textBuffer[pos2] == '\r' ) {
							if ( textBuffer[pos2+1] == '\n' ) {
								length += 1;
							}
						}
					}

					//Debug diagnostics - JC
					//String text = model->getText();
					//StringUtils::trace( Format( "vkDelete [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
					//											text % text[pos] % text[pos] % pos );

					if ( 0 != length ) {
						textModel->removeText( pos, length );
					}

					//text = model->getText();
					//StringUtils::trace( Format( "after vkDelete [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
					//											text % text[pos] % text[pos] % pos );
				}
			}
		}
		break;

		case vkBackSpace : {
			uint32 length = textPeer_->getSelectionCount();			

			if ( NULL == textModel ) {
				String text;
				if ( NULL != model->getFormatter() ) {
					text = getPeer()->getText();
				}
				else {
					text = model->getValueAsString( getModelKey() );
				}

				uint32 pos =  minVal<uint32>( text.size(), textPeer_->getSelectionStart() );
				
				// if the selection is not empty we delete it, but the cursor doesn't move.
				if ( 0 == length ) {
					if ( pos > 0 ) {
						// we are deleting the previous character
						pos -= 1;
						length = 1;
					}
				}
				
				
				// workaround for a '\r\n' sequence: we need to
				// delete '\r' too at the beginning of the selection
				if ( pos > 0 ) {
					const VCFChar* textBuffer = text.c_str();
					
					if ( textBuffer[pos] == '\n' ) {
						if ( textBuffer[pos-1] == '\r' ) {
							pos -= 1;
							length += 1;
						}
					}
				}
				
				//Debug diagnostics - JC
				//String text = model->getText();
				//StringUtils::trace( Format( "vkBackSpace [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
				//											text % text[pos] % text[pos] % pos );
				
				
				if ( 0 != length ) {
					text.erase( pos, length );
					model->setValueAsString( text, getModelKey() );
					if ( didInputValidationFail() ) {
						ke->ignoreKeystroke = true;
					}
				}
			}
			else {
				
				uint32 pos =  minVal<uint32>( textModel->getSize(), textPeer_->getSelectionStart() );
				
				// if the selection is not empty we delete it, but the cursor doesn't move.
				if ( 0 == length ) {
					if ( pos > 0 ) {
						// we are deleting the previous character
						pos -= 1;
						length = 1;
					}
				}
				
				
				// workaround for a '\r\n' sequence: we need to
				// delete '\r' too at the beginning of the selection
				if ( pos > 0 ) {
					String text = textModel->getText();
					const VCFChar* textBuffer = text.c_str();
					
					if ( textBuffer[pos] == '\n' ) {
						if ( textBuffer[pos-1] == '\r' ) {
							pos -= 1;
							length += 1;
						}
					}
				}
				
				//Debug diagnostics - JC
				//String text = model->getText();
				//StringUtils::trace( Format( "vkBackSpace [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
				//											text % text[pos] % text[pos] % pos );
				
				
				if ( 0 != length ) {
					textModel->removeText( pos, length );
				}
				
				
				//text = model->getText();
				//StringUtils::trace( Format( "after vkBackSpace [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
				//											text % text[pos-length] % text[pos-length] % pos-length );
				
			}

		}
		break;

		case vkLeftArrow : 
		case vkRightArrow : 
		case vkPgUp : 
		case vkPgDown : 
		case vkHome : 
		case vkEnd : 
		case vkInsert : 
		case vkAlt : 
		case vkCtrl : 
		case vkEscape : 
		case vkPrintScreen : 
		case vkScrollLock :
		case vkPause : 
		case vkCapsLock : 
		case vkShift : 
		case vkF1 :
		case vkF2 : 
		case vkF3 : 
		case vkF4 : 
		case vkF5 : 
		case vkF6 : 
		case vkF7 : 
		case vkF8 : 
		case vkF9 : 
		case vkF10 : 
		case vkF11 : 
		case vkF12 : 
		case vkDownArrow :
		case vkUpArrow : {
			//no-op for these, since we don't want to add/delete text for them
		}
		break;

		/**
		JC - added this to account for tab entry - 
		sometimes you'd end up with a tab character entered when all you 
		wanted was to tab to the next control
		*/
		case vkTab : {
			if ( keepsTabKey() ) {
				//process the tab

				if ( !ke->hasShiftKey() && !ke->hasAltKey() && !ke->hasControlKey() ) {
					// we add the 'tab' text in place of the selection

					uint32 pos =  textPeer_->getCaretPosition();
					String text;
					text += ke->keyValue;

					//determine if we have selected text. If we 
					//have, then delete the selection and *then*
					//add in the new character(s)

					uint32 length = textPeer_->getSelectionCount();

					if ( NULL == textModel ) {
						String newText = model->getValueAsString( getModelKey() );

						if ( length > 0 ) {
							newText.erase( pos, length );
						}

						newText.insert( pos, text );
						
						//check with the formatter and format our
						//new text. If formatted text is *smaller*
						//than what we are proposing, then mark the
						//event so that the peer does NOT process it!
						if ( model->getFormatter() != NULL ) {
							String tmp = model->getFormatter()->convertFromModel( getModelKey(), newText );
							if ( tmp.size() < newText.size() ) {
								ke->ignoreKeystroke = true;
							}
						}

						model->setValueAsString( newText, getModelKey() );
						if ( didInputValidationFail() ) {
							ke->ignoreKeystroke = true;
						}	
					}
					else {
						if ( length > 0 ) {
							textModel->removeText( pos, length );
						}
						
						
						textModel->insertText( pos, text );
					}
				}
			}
		}
		break;


		case vkEnter : {
			if ( !ke->hasAltKey() && !ke->hasControlKey() ) {
				if ( supportsMultiLinedText() ) {
					uint32 pos =  textPeer_->getCaretPosition();
					String text = "\n";

					uint32 length = textPeer_->getSelectionCount();


					if ( NULL == textModel ) {
						String newText = model->getValueAsString( getModelKey() );

						if ( length > 0 ) {
							newText.erase( pos, length );
						}

						newText.insert( pos, text );
						
						if ( model->getFormatter() != NULL ) {
							String tmp = model->getFormatter()->convertFromModel( getModelKey(), newText );
							if ( tmp.size() < newText.size() ) {
								ke->ignoreKeystroke = true;
							}
						}


						model->setValueAsString( newText, getModelKey() );
						if ( didInputValidationFail() ) {
							ke->ignoreKeystroke = true;
						}
					}
					else {
						
						if ( length > 0 ) {
							textModel->removeText( pos, length );
						}
						
						//StringUtils::trace( Format( "adding [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
						//											text % text[0] % text[0] % pos );
						
						textModel->insertText( pos, text );
					}
				}
			}
		}
		break;
	}
}

void TextControl::internal_processKeyPress( KeyboardEvent* ke )
{
	if ( ke->dontProcessKeystroke ) {
		return;
	}

	Model* model = getViewModel();
	TextModel* textModel = dynamic_cast<TextModel*>(model);

	switch ( ke->virtualKeyCode ) {
		case vkDelete :
		case vkBackSpace : 
		case vkLeftArrow : 
		case vkRightArrow : 
		case vkPgUp : 
		case vkPgDown : 
		case vkHome : 
		case vkEnd : 
		case vkInsert : 
		case vkAlt : 
		case vkCtrl : 
		case vkEscape : 
		case vkPrintScreen : 
		case vkScrollLock :
		case vkPause : 
		case vkCapsLock : 
		case vkShift : 
		case vkF1 : 
		case vkF2 : 
		case vkF3 : 
		case vkF4 : 
		case vkF5 : 
		case vkF6 : 
		case vkF7 : 
		case vkF8 : 
		case vkF9 : 
		case vkF10 : 
		case vkF11 : 
		case vkF12 : 
		case vkDownArrow :
		case vkUpArrow :
		case vkTab :{
			//no-op for these, since we don't want to add/delete text for them
		}
		break;

		case vkEnter :{
			if ( validationStyle_ == tvsOnEnterKey ) {
				String text = getPeer()->getText();
				model->setValueAsString( text, getModelKey() );
			}
		}
		break;

		default : {
			if ( validationStyle_ != tvsOnKeyEvent ) {
				inputState_ = tisWaitingForInput;
				return;
			}
			// control + characters need not to be treated as inserted characters
			if ( !ke->hasAltKey() && !ke->hasControlKey() ) {

				uint32 pos =  textPeer_->getSelectionStart();

				String text;
				text += ke->keyValue;

				if ( !text.empty() ) {

					//StringUtils::trace( Format( "adding [ %s ] (as char: %c[0x%04X]) to text model at pos %d\n" ) %
					//											text % text[0] % text[0] % pos );

					//determnine if we have sleected text. If we 
					//have, then delete the selection ant *then*
					//add in the new character(s)

					uint32 length = textPeer_->getSelectionCount();

					if ( NULL == textModel ) {
						//String newText = model->getValueAsString( getModelKey() );
						String newText;
				if ( NULL != model->getFormatter() ) {
					newText = getPeer()->getText();
				}
				else {
					newText = model->getValueAsString( getModelKey() );
				}

/*
						if ( model->getFormatter() != NULL ) {
							if ( pos >= newText.size() ) {
								ke->ignoreKeystroke = true;
								inputState_ = tisWaitingForInput;
								return;
							}
						}
						*/

						if ( length > 0 ) {
							newText.erase( pos, length );
						}

						newText.insert( pos, text );
						
						if ( model->getFormatter() != NULL ) {
							String tmp = model->getFormatter()->convertFromModel( getModelKey(), newText );
							if ( tmp.size() < newText.size() ) {
								ke->ignoreKeystroke = true;
							}
						}
						

						model->setValueAsString( newText, getModelKey() );
						if ( didInputValidationFail() ) {
							ke->ignoreKeystroke = true;
						}
					}
					else {
						if ( length > 0 ) {
							textModel->removeText( pos, length );
						}
						
						
						textModel->insertText( pos, text );
					}
				}
			}
		}
		break;
	}
}

void TextControl::setReadOnly( const bool& val )
{
	readOnly_ = val;
	textPeer_->setReadOnly( readOnly_ );
}

void TextControl::cut()
{
	if ( readOnly_ ) {
		return;
	}
	textPeer_->cut();
}

void TextControl::copy()
{
	textPeer_->copy();
}

void TextControl::paste()
{
	if ( readOnly_ ) {
		return;
	}
	textPeer_->paste();
}

bool TextControl::canUndo()
{
	return textPeer_->canUndo();
}

bool TextControl::canRedo()
{
	return textPeer_->canRedo();
}


void TextControl::undo()
{
	if ( readOnly_ ) {
		return;
	}
	textPeer_->undo();
}


void TextControl::redo()
{
	if ( readOnly_ ) {
		return;
	}
	textPeer_->redo();
}

void TextControl::setTextWrapping( const bool& val )
{
	textPeer_->setTextWrapping(val);
}

bool TextControl::getTextWrapping()
{
	return textPeer_->getTextWrapping();
}

bool TextControl::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_HEIGHT ) {
		if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtTextControlHeight ) ) {
			strValue = CC_TEXTHEIGHT;
			return true;
		}
	}

	return Control::generatePropertyValue( fullPropertyName, property, value, strValue );
}

void TextControl::setInputValidator( InputValidator* val )
{
	if ( inputValidator_ != val ) {
		inputValidator_ = val;

		if ( NULL != inputValidator_ ) {
			inputValidator_->setInputControl(this);
		}
	}
}


void TextControl::updateView( Model* updatedModel )
{
	Control::updateView(updatedModel);
	
	if ( NULL != updatedModel && !getModelKey().isNull() ) {
		String s = updatedModel->getValueAsString( this->getModelKey() );
		if ( s != peer_->getText() ) {
			this->peer_->setText( s );
		}
	}
}

/**
$Id$
*/
