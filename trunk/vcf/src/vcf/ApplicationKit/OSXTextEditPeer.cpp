//OSXTextEditPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXTextEditPeer.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/FoundationKit/Dictionary.h"



using namespace VCF;

OSXTextEditPeer::OSXTextEditPeer( TextControl* component, const bool& isMultiLineControl ):
	OSXControl( component ),
	OSXTextPeer( true, isMultiLineControl ),
	textControl_(component),
	editState_(0)
{
	if ( isMultiLineControl ) {
		editState_ |= esMultiLined; 
	}
}

OSXTextEditPeer::~OSXTextEditPeer()
{
	
}

void OSXTextEditPeer::create( Control* owningControl )
{
	if ( NULL == textControl_ ){
		//throw exception !!!!!!
	}

	OSXControl::create( owningControl );
	

	if ( hiView_ ){
		TXNFrameOptions frameOptions;
		frameOptions = kTXNDoFontSubstitutionMask;
		
		//we may want these in the future
		//kTXNShowWindowMask | kTXNWantVScrollBarMask |
		//kTXNWantHScrollBarMask |kTXNDrawGrowIconMask;
		::HIRect r;
		r.origin.x = 0;
		r.origin.y = 0;				
		r.size.width = 0;
		r.size.height = 0;
		if ( noErr != TXNCreateObject( &r, frameOptions, &txnObject_ ) ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("MLTE TXNCreateObject failed!") );
		}
		
		TXNCarbonEventInfo      carbonEventInfo;
		TXNControlTag           iControlTags[] = { kTXNUseCarbonEvents };  
		TXNControlData          iControlData[1];
		carbonEventInfo.useCarbonEvents = false;  
		carbonEventInfo.filler = 0;
		carbonEventInfo.flags = 0;   
		carbonEventInfo.fDictionary = NULL;
		iControlData[0].uValue = (UInt32) &carbonEventInfo;
		TXNSetTXNObjectControls( txnObject_, false, 1, iControlTags, iControlData ); 

		setFont( textControl_->getFont() );

		textControl_->ControlModelChanged +=
			new GenericEventHandler<OSXTextEditPeer>( this, &OSXTextEditPeer::onControlModelChanged, "OSXTextEditPeer::onControlModelChanged" );


		textControl_->getFont()->FontChanged += 
			new GenericEventHandler<OSXTextEditPeer>( this, &OSXTextEditPeer::onTextControlFontChanged, "OSXTextEditPeer::onTextControlFontChanged" );

	}
	else {
		//throw exception
		throw RuntimeException( "Runtime Exception!" );
	}

}

	
OSStatus OSXTextEditPeer::handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	OSStatus result = eventNotHandledErr;
	
    UInt32 whatHappened = GetEventKind (theEvent);
	TCarbonEvent event( theEvent );
	
	switch ( GetEventClass( theEvent ) )  {				 
		case kEventClassControl : {
			switch( whatHappened ) {				
			
				case kEventControlOwningWindowChanged : {
					WindowRef owningWindow;
					GetEventParameter( theEvent, kEventParamControlCurrentOwningWindow, typeWindowRef, NULL,
										sizeof (WindowRef), NULL, &owningWindow);
										
					TXNAttachObjectToWindowRef( txnObject_, owningWindow );
				}
				break;
				
				case kEventControlActivate : {
					TXNFocus( txnObject_, true );
					result = OSXControl::handleOSXEvent( nextHandler, theEvent );
                }
                break;
				
				case kEventControlDeactivate : {
					TXNFocus( txnObject_, false );
					result = OSXControl::handleOSXEvent( nextHandler, theEvent );					
                }
                break;
				
				case kEventControlBoundsChanged : {
					UInt32 attributes = 0;
					OSStatus err = GetEventParameter( theEvent,
                                                kEventParamAttributes,
                                                typeUInt32,
                                                NULL,
                                                sizeof( UInt32 ),
                                                NULL, &attributes );

					if ( err == noErr ) 	{
                        ::Rect currentBounds;
						GetEventParameter( theEvent, kEventParamCurrentBounds, typeQDRectangle,
                                                NULL, sizeof(currentBounds), NULL, &currentBounds);

						HIRect hiBounds;
						hiBounds.origin.x = currentBounds.left;
						hiBounds.origin.y = currentBounds.top;
						hiBounds.size.width = currentBounds.right - currentBounds.left;
						hiBounds.size.height = currentBounds.bottom - currentBounds.top;
						
						TXNSetHIRectBounds( txnObject_, &hiBounds, &hiBounds, false );
					}
                }
                break;
				
				default : {
                    result = OSXControl::handleOSXEvent( nextHandler, theEvent );
                }
                break;
			}
		}
		break;
		
		default : {
            result = OSXControl::handleOSXEvent( nextHandler, theEvent );
        }
        break; 
	}	
	
	return result;
}
	

OSHandleID OSXTextEditPeer::getTextObjectHandle()
{
	return OSXTextPeer::getTextObjectHandle();
}

void OSXTextEditPeer::setRightMargin( const double & rightMargin )
{
	editState_ |= esStyleChanging;

	

	editState_ &= ~esStyleChanging;
}

void OSXTextEditPeer::setLeftMargin( const double & leftMargin )
{
	editState_ |= esStyleChanging;

	

	editState_ &= ~esStyleChanging;
}

unsigned long OSXTextEditPeer::getLineCount()
{
	return 0;
}

VCF::Rect OSXTextEditPeer::getContentBoundsForWidth(const double& width)
{
	return OSXTextPeer::getContentBoundsForWidth(width);
}

unsigned long OSXTextEditPeer::getCurrentLinePosition()
{
	unsigned long result = 0;

	return result;
}

double OSXTextEditPeer::getLeftMargin()
{
	double result = 0.0;

	
	return result;
}

double OSXTextEditPeer::getRightMargin()
{
	double result = 0.0;

	
	return result;
}


void OSXTextEditPeer::insertText( unsigned int start, const String& text )
{
	editState_ |= esPeerTextChanging;

	OSXTextPeer::insertText( start, text );

	editState_ &= ~esPeerTextChanging;
}

void OSXTextEditPeer::deleteText( unsigned int start, unsigned int length )
{
	editState_ |= esPeerTextChanging;

	OSXTextPeer::deleteText( start, length );

	editState_ &= ~esPeerTextChanging;
}

unsigned int OSXTextEditPeer::getTextLength()
{
	return OSXTextPeer::getTextLength();
}

String OSXTextEditPeer::getText( unsigned int start, unsigned int length )
{
	return OSXTextPeer::getText(start,length);
}

String OSXTextEditPeer::getText()
{	
	return OSXTextPeer::getText( 0, OSXTextPeer::getTextLength() );
}



void OSXTextEditPeer::paint( GraphicsContext* context, const Rect& paintRect )
{
	OSXTextPeer::paint( context, paintRect );
}


void OSXTextEditPeer::setTopMargin( const double & topMargin )
{
	editState_ |= esStyleChanging;

	OSXTextPeer::setTopMargin( topMargin );

	editState_ &= ~esStyleChanging;
}

void OSXTextEditPeer::setBottomMargin( const double & bottomMargin )
{
	editState_ |= esStyleChanging;

	OSXTextPeer::setBottomMargin( bottomMargin );

	editState_ &= ~esStyleChanging;
}


double OSXTextEditPeer::getTopMargin()
{
	return OSXTextPeer::getTopMargin();
}

double OSXTextEditPeer::getBottomMargin()
{
	return OSXTextPeer::getBottomMargin();
}

void OSXTextEditPeer::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	editState_ |= esStyleChanging;

	OSXTextPeer::setStyle( start, length, styles );

	editState_ &= ~esStyleChanging;
}

void OSXTextEditPeer::getStyle( unsigned int start, unsigned int length, Dictionary& styles, Color& color )
{
	OSXTextPeer::getStyle( start, length, styles, color );
}


void OSXTextEditPeer::setDefaultStyle( Dictionary& styles )
{
	editState_ |= esStyleChanging;

	OSXTextPeer::setDefaultStyle( styles );

	editState_ &= ~esStyleChanging;
}



VCF::Point* OSXTextEditPeer::getPositionFromCharIndex( const unsigned long& index )
{
	
	return &ptAtCharPos_;
}

unsigned long OSXTextEditPeer::getCharIndexFromPosition( VCF::Point* point )
{
	unsigned long result = 0;

	return result;
}

unsigned long OSXTextEditPeer::getCaretPosition()
{
	return getSelectionStart();
}

void OSXTextEditPeer::setCaretPosition( const unsigned long& caretPos )
{

}

uint32 OSXTextEditPeer::convertCharToVKCode( VCFChar ch )
{
	uint32 result = 0;

	ch = tolower( ch );
	switch ( ch ) {
		case 'a' : {
			result = vkLetterA;
		}
		break;

		case 'b' : {
			result = vkLetterB;
		}
		break;

		case 'c' : {
			result = vkLetterC;
		}
		break;

		case 'd' : {
			result = vkLetterD;
		}
		break;

		case 'e' : {
			result = vkLetterE;
		}
		break;

		case 'f' : {
			result = vkLetterF;
		}
		break;

		case 'g' : {
			result = vkLetterG;
		}
		break;

		case 'h' : {
			result = vkLetterH;
		}
		break;

		case 'i' : {
			result = vkLetterI;
		}
		break;

		case 'j' : {
			result = vkLetterJ;
		}
		break;

		case 'k' : {
			result = vkLetterK;
		}
		break;

		case 'l' : {
			result = vkLetterL;
		}
		break;

		case 'm' : {
			result = vkLetterM;
		}
		break;

		case 'n' : {
			result = vkLetterN;
		}
		break;

		case 'o' : {
			result = vkLetterO;
		}
		break;

		case 'p' : {
			result = vkLetterP;
		}
		break;

		case 'q' : {
			result = vkLetterQ;
		}
		break;

		case 'r' : {
			result = vkLetterR;
		}
		break;

		case 's' : {
			result = vkLetterS;
		}
		break;

		case 't' : {
			result = vkLetterT;
		}
		break;

		case 'u' : {
			result = vkLetterU;
		}
		break;

		case 'v' : {
			result = vkLetterV;
		}
		break;

		case 'w' : {
			result = vkLetterW;
		}
		break;

		case 'x' : {
			result = vkLetterX;
		}
		break;

		case 'y' : {
			result = vkLetterY;
		}
		break;

		case 'z' : {
			result = vkLetterZ;
		}
		break;

		case '0' : {
			result = vkNumber0;
		}
		break;

		case '1' : {
			result = vkNumber1;
		}
		break;

		case '2' : {
			result = vkNumber2;
		}
		break;

		case '3' : {
			result = vkNumber3;
		}
		break;

		case '4' : {
			result = vkNumber4;
		}
		break;

		case '5' : {
			result = vkNumber5;
		}
		break;

		case '6' : {
			result = vkNumber6;
		}
		break;

		case '7' : {
			result = vkNumber7;
		}
		break;

		case '8' : {
			result = vkNumber8;
		}
		break;

		case '9' : {
			result = vkNumber9;
		}
		break;

		case '/' : {
			result = vkDivideSign;
		}
		break;

		case '+' : {
			result = vkPlusSign;
		}
		break;

		case '-' : {
			result = vkMinusSign;
		}
		break;

		case '=' : {
			result = vkEqualsSign;
		}
		break;

		case '_' : {
			result = vkUnderbar;
		}
		break;

		case '|' : {
			result = vkUprightBar;
		}
		break;

		case '{' : {
			result = vkOpenBrace;
		}
		break;

		case '}' : {
			result = vkCloseBrace;
		}
		break;

		case '[' : {
			result = vkOpenBracket;
		}
		break;

		case ']' : {
			result = vkCloseBracket;
		}
		break;

		case '<' : {
			result = vkLessThan;
		}
		break;

		case '>' : {
			result = vkGreaterThan;
		}
		break;

		case '.' : {
			result = vkPeriod;
		}
		break;

		case ',' : {
			result = vkComma;
		}
		break;

		case '!' : {
			result = vkExclamation;
		}
		break;

		case '~' : {
			result = vkTilde;
		}
		break;

		case '`' : {
			result = vkLeftApostrophe;
		}
		break;

		case '@' : {
			result = vkCommercialAt;
		}
		break;

		case '#' : {
			result = vkNumberSign;
		}
		break;

		case '$' : {
			result = vkDollarSign;
		}
		break;

		case '%' : {
			result = vkPercent;
		}
		break;

		case '^' : {
			result = vkCircumflex;
		}
		break;

		case '&' : {
			result = vkAmpersand;
		}
		break;

		case '*' : {
			result = vkAsterix;
		}
		break;

		case '(' : {
			result = vkOpenParen;
		}
		break;

		case ')' : {
			result = vkCloseParen;
		}
		break;

		case ':' : {
			result = vkColon;
		}
		break;

		case ';' : {
			result = vkSemiColon;
		}
		break;

		case '"' : {
			result = vkDoubleQuote;
		}
		break;

		case '\'' : {
			result = vkSingleQuote;
		}
		break;

		case '\\' : {
			result = vkBackSlash;
		}
		break;

		case '?' : {
			result = vkQuestionMark;
		}
		break;
	}
	return result;
}

bool OSXTextEditPeer::stateAllowsModelChange()
{
	bool result = false;

	if ( !(editState_ & esStyleChanging) && 
		!(editState_ & esPeerTextChanging) &&
		!(editState_ & esKeyEvent) &&
		!(editState_ & esExternalTextChanging) ) {

		result = true;
	}

	return result;
}

void OSXTextEditPeer::onTextModelTextChanged( TextEvent* event )
{
	if ( (NULL != event) && 
		!(editState_ & esModelTextChanging) &&
		!(editState_ & esKeyEvent) ){

		switch ( event->getType() ) {
			case TextModel::tmTextInserted : {
				insertText( event->getChangeStart(),
											event->getChangeText() );
			}
			break;

			case TextModel::tmTextReplaced : {
				String originalText = event->getOriginalText();
				deleteText( event->getChangeStart(),
											originalText.size() );

				insertText( event->getChangeStart(),
											event->getChangeText() );
			}
			break;

			case TextModel::tmTextRemoved : {
				deleteText( event->getChangeStart(),
											event->getChangeLength() );
			}
			break;

			case TextModel::tmTextSet : {
				setText( textControl_->getTextModel()->getText() );
			}
			break;
		}
	}
}


void OSXTextEditPeer::setText( const VCF::String& text )
{
	editState_ |= esPeerTextChanging;

	deleteText( 0, getTextLength() );
	
	insertText( 0, text );

	editState_ &= ~esPeerTextChanging;
}

unsigned long OSXTextEditPeer::getSelectionStart()
{
	unsigned long start = 0;
	
	TXNOffset s, e;
	
	TXNGetSelection( txnObject_, &s, &e );
	
	start = s;
	
	return start;
}

unsigned long OSXTextEditPeer::getSelectionCount()
{
	TXNOffset s, e;
	
	TXNGetSelection( txnObject_, &s, &e );
	
	return e - s;
}

/*
void OSXTextEditPeer::getSelectionMark( unsigned long & start, unsigned long & end )
{
	
}
*/


void OSXTextEditPeer::clearSelection()
{
	TXNClear( txnObject_ );
}

void OSXTextEditPeer::setSelectionMark( const unsigned long& start, const unsigned long& count )
{
	TXNSetSelection( txnObject_, start, start + count );
}


void OSXTextEditPeer::scrollToLine( const ulong32& lineIndex )
{
	
}

void OSXTextEditPeer::scrollToSelection( const bool& _showEndSel/*=false*/ )
{
	
}

void OSXTextEditPeer::repaint( Rect* repaintRect )
{
	OSXControl::repaint( repaintRect );
}

void OSXTextEditPeer::setReadOnly( const bool& readonly )
{
	
	TXNControlTag           iControlTags[] = { kTXNIOPrivilegesTag };  
	TXNControlData          iControlData[1];
	if ( readonly ) {
		iControlData[0].uValue = (UInt32) kTXNReadOnly;
	}
	else {
		iControlData[0].uValue = (UInt32) kTXNReadWrite;	
	}
	TXNSetTXNObjectControls( txnObject_, false, 1, iControlTags, iControlData ); 
}

ulong32 OSXTextEditPeer::getTotalPrintablePageCount( PrintContext* context )
{
	ulong32 result = 0;

	return result;
}

void OSXTextEditPeer::print( PrintContext* context, const long& page )
{
	
}

void OSXTextEditPeer::finishPrinting()
{
	
}

void OSXTextEditPeer::onControlModelChanged( Event* e )
{
	EventHandler* tml = getEventHandler( "OSXTextEditPeer::onTextModelTextChanged" );
	if ( NULL == tml ) {
		tml = new TextModelEventHandler<OSXTextEditPeer>( this, &OSXTextEditPeer::onTextModelTextChanged, "OSXTextEditPeer::onTextModelTextChanged" );
	}

	TextModel* tm = textControl_->getTextModel();
	tm->addTextModelChangedHandler( tml );

	String text = tm->getText();


	setText( text );
}

void OSXTextEditPeer::cut()
{
	if ( !textControl_->getReadOnly() ) {
		TXNCut( txnObject_ );
	}
}

void OSXTextEditPeer::copy()
{
	TXNCopy( txnObject_ );
}

void OSXTextEditPeer::paste()
{
	if ( !textControl_->getReadOnly() ) {
		TXNPaste( txnObject_ );
	}
}

bool OSXTextEditPeer::canUndo()
{
	return TXNCanUndo( txnObject_, NULL );
}

bool OSXTextEditPeer::canRedo()
{
	return TXNCanRedo( txnObject_, NULL );
}

void OSXTextEditPeer::undo()
{
	if ( !textControl_->getReadOnly() ) {
		TXNUndo( txnObject_ );
	}
}

void OSXTextEditPeer::redo()
{
	//this one is necessary too, otherwise the model wouldn't be updated
	if ( !textControl_->getReadOnly() ) {
		TXNRedo( txnObject_ );
	}
}

void OSXTextEditPeer::onTextControlFontChanged( Event* event )
{
	Font* font = (Font*) event->getSource();	

	setFont( font );
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.3  2005/07/07 23:28:58  ddiego
*last osx checkins before release - not complete :(
*
*Revision 1.1.2.2  2005/06/28 04:03:35  ddiego
*osx text edit mods and started on osx tree peer.
*
*Revision 1.1.2.1  2005/06/27 03:28:54  ddiego
*more osx work.
*
*/


