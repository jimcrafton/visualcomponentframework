//X11SimpleTextControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11UIToolkit.h"

#include "vcf/ApplicationKit/X11SimpleTextControl.h"
#include "vcf/ApplicationKit/TextControl.h"


using namespace VCF;




X11SimpleTextControl::X11SimpleTextControl( TextControl* component, const bool& isMultiLineControl ):
	X11Control( component ),
	currentLinePos_(0),
	selectionStart_(0),
	selectionEnd_(0),
	okToResetControlText_(true),
	leftMargin_(5.0),
	rightMargin_(5.0)
{

	TextModelEventHandler<X11SimpleTextControl>* tml =
			new TextModelEventHandler<X11SimpleTextControl>( this, &X11SimpleTextControl::onTextModelTextChanged, "onTextModelTextChanged" );

	TextModel* tm = component->getTextModel();
	tm->addTextModelChangedHandler( tml );

}

X11SimpleTextControl::~X11SimpleTextControl()
{

}


void X11SimpleTextControl::handleEvent( XEvent* x11Event )
{

	switch ( x11Event->type ) {
		case KeyPress :  {
			int keyCode = x11Event->xkey.keycode;
			KeySym keySym;
			memset(&keySym, 0, sizeof(KeySym) );

			char keyBuffer[100];
			memset( keyBuffer, 0, 100 );

			int count = XLookupString( &x11Event->xkey, keyBuffer, 100-1, &keySym, 0 );
			X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );
			VirtualKeyCode code = toolkit->translateKeyCode( keySym );
			switch ( code ) {
				case vkLeftArrow : {
					if ( selectionStart_ > 0 ) {
						selectionStart_ -= 1;
						repaint();
					}
				}
				break;

				case vkRightArrow : {
					if ( selectionStart_ < text_.size() ) {
						selectionStart_ += 1;
						repaint();
					}
				}
				break;

				case vkBackSpace : {
					if ( selectionStart_ > 0 ) {
						selectionStart_ -= 1;
						TextControl* tc = reinterpret_cast<TextControl*>( control_ );

						TextModel* tm = tc->getTextModel();
						String text = tm->getText();

						text.erase( selectionStart_, 1 );

						tm->setText( text );
					}
				}
				break;

				case vkDelete : {
					TextControl* tc = reinterpret_cast<TextControl*>( control_ );

					TextModel* tm = tc->getTextModel();
					String text = tm->getText();

					text.erase( selectionStart_, 1 );
					selectionStart_ = minVal<ulong32>( selectionStart_, text.size() );

					tm->setText( text );
				}
				break;

				default : {
					if ( ((code >= vkNumber0) && (code <= vkLetterZ)) || (code == vkSpaceBar) || (code == vkReturn) ) {
						TextControl* tc = reinterpret_cast<TextControl*>( control_ );

						TextModel* tm = tc->getTextModel();
						String text = tm->getText();

						if ( code == vkReturn ) {
							text.insert( selectionStart_, "\n" );
						}
						else {
							text.insert( selectionStart_, 1, keyBuffer[0] );
						}

						selectionStart_ += 1;

						tm->setText( text );
					}
				}
				break;
			}

			X11Control::handleEvent( x11Event );
		}
		break;

		case KeyRelease : {
			X11Control::handleEvent( x11Event );
		}
		break;

		case ButtonPress : {
			VCF::Point pt( x11Event->xbutton.x, x11Event->xbutton.y );

			selectionStart_ = getCharIndexFromPosition( &pt );
			X11Control::handleEvent( x11Event );
		}
		break;

		case ButtonRelease : {
			X11Control::handleEvent( x11Event );
		}
		break;

		case MotionNotify : {
			X11Control::handleEvent( x11Event );
		}
		break;

		case FocusIn : {
			X11Control::handleEvent( x11Event );
		}
		break;

		case FocusOut : {
			X11Control::handleEvent( x11Event );
		}
		break;

		case SelectionClear : {

		}
		break;


		case SelectionRequest : {

		}
		break;

		case SelectionNotify : {

		}
		break;


		default : {
			X11Control::handleEvent( x11Event );
		}
	}
}

String X11SimpleTextControl::getText()
{
	return text_;
}

void X11SimpleTextControl::setText( const String& text )
{
	text_ = text;

	repaint();
}

void X11SimpleTextControl::setRightMargin( const double & rightMargin )
{
	rightMargin_ = rightMargin;
	repaint();
}

void X11SimpleTextControl::setLeftMargin( const double & leftMargin )
{
	leftMargin_ = leftMargin;
	repaint();
}

unsigned long X11SimpleTextControl::getLineCount()
{
	unsigned long result = 0;

	const VCFChar* P = text_.c_str();
	const VCFChar* start = P;
	const VCFChar* line = P;
	int textSize = text_.size();
	while ( (P-start) < textSize ) {
		if ( (*P == '\n') || ((*P == '\r') && (*(P+1) == '\n')) ) {

			result ++;

			//process the new line
			if ( *(P+1) == '\n' ) {
				P++;
			}
			line = P;
			line ++;
		}
		P++;
	}

	if ( (line < P) && ((start-line) < textSize) ) {
		result ++;
	}

	return result;
}

unsigned long X11SimpleTextControl::getCurrentLinePosition()
{
	return currentLinePos_;
}

double X11SimpleTextControl::getLeftMargin()
{
	return leftMargin_;
}

double X11SimpleTextControl::getRightMargin()
{
	return rightMargin_;
}

Point* X11SimpleTextControl::getPositionFromCharIndex( const unsigned long& index )
{
	GraphicsContext* gc = control_->getContext();

	Rect clientRect = *control_->getClientBounds();

	gc->getPeer()->setContextID(wndHandle_);

	clientRect.left_ += leftMargin_;
	clientRect.right_ -= rightMargin_;

	clientRect.normalize();

	if ( clientRect.getWidth() > 0.0 ) {

		ulong32 pos = 0;

		const VCFChar* P = text_.c_str();
		const VCFChar* start = P;

		int size = text_.size();

		Rect glyphRect;
		glyphRect.setRect( clientRect.left_, 0,
								clientRect.left_, gc->getTextHeight( "EM" ) );

		String lineOfText;

		while ( ((P-start) < size) && (glyphRect.top_ < clientRect.getHeight()) ) {
			if ( !((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
				lineOfText.append( 1, *P );
			}

			glyphRect.right_ = gc->getTextWidth( lineOfText ) + clientRect.left_;

			if ( (glyphRect.right_ >= clientRect.getWidth()) || ((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
				//scootch back
				if ( (*P != ' ') && (*P != '\n') && (*P != '\r') ){
					const VCFChar* tmp = P;
					while ( (*P != ' ') && (*P != '\n') && (*P != '\r') && (P > start) ) {
						P--;
						pos --;
					}
					lineOfText.erase( lineOfText.size()-(tmp-P), tmp-P );

					glyphRect.right_ = gc->getTextWidth( lineOfText ) + clientRect.left_;
				}

				glyphRect.top_ += gc->getTextHeight( lineOfText );

				glyphRect.bottom_ = glyphRect.top_ + gc->getTextHeight( "EM" );

				glyphRect.left_ = clientRect.left_;

				if ( ((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
					if ( (*P == '\r') && (*(P+1) == '\n') ) {
						P++;
						pos ++;
					}
				}
				lineOfText = "";
			}
			else if ( index == pos ) {
				posAtChar_.x_ = glyphRect.left_;
				posAtChar_.y_ = glyphRect.top_;

				break;
			}
			pos ++;
			P++;

			glyphRect.left_ = glyphRect.right_;
		}
	}
	else {
		return NULL;
	}

	return &posAtChar_;
}

unsigned long X11SimpleTextControl::getCharIndexFromPosition( Point* point )
{
	ulong32 result = 0;

	GraphicsContext* gc = control_->getContext();

	Rect clientRect = *control_->getClientBounds();

	gc->getPeer()->setContextID(wndHandle_);

	clientRect.left_ += leftMargin_;
	clientRect.right_ -= rightMargin_;

	clientRect.normalize();

	if ( clientRect.getWidth() > 0.0 ) {

		const VCFChar* P = text_.c_str();
		const VCFChar* start = P;

		int size = text_.size();

		Rect glyphRect;
		glyphRect.setRect( clientRect.left_, 0,
								clientRect.left_, gc->getTextHeight( "EM" ) );

		String lineOfText;


		while ( ((P-start) < size) && (glyphRect.top_ < clientRect.getHeight()) ) {
			if ( !((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
				lineOfText.append( 1, *P );
			}

			glyphRect.right_ = gc->getTextWidth( lineOfText ) + clientRect.left_;

			if ( (glyphRect.right_ >= clientRect.getWidth()) || ((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
				//scootch back
				if ( (*P != ' ') && (*P != '\n') && (*P != '\r') ){
					const VCFChar* tmp = P;
					while ( (*P != ' ') && (*P != '\n') && (*P != '\r') && (P > start) ) {
						P--;
						result --;
					}
					lineOfText.erase( lineOfText.size()-(tmp-P), tmp-P );

					glyphRect.right_ = gc->getTextWidth( lineOfText ) + clientRect.left_;
				}

				glyphRect.top_ += gc->getTextHeight( lineOfText );

				glyphRect.bottom_ = glyphRect.top_ + gc->getTextHeight( "EM" );

				glyphRect.left_ = clientRect.left_;

				if ( ((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
					if ( (*P == '\r') && (*(P+1) == '\n') ) {
						P++;
						result ++;
					}
				}
				lineOfText = "";
			}
			else if ( glyphRect.containsPt( point ) ) {

				break;
			}
			result ++;
			P++;

			glyphRect.left_ = glyphRect.right_;
		}
	}
	return result;
}

unsigned long X11SimpleTextControl::getCaretPosition()
{
	return selectionStart_;
}

void X11SimpleTextControl::setCaretPosition( const unsigned long& caretPos )
{
	selectionStart_ = caretPos;
	selectionEnd_ = selectionStart_;
}

unsigned long X11SimpleTextControl::getSelectionStart()
{
	return selectionStart_;
}

unsigned long X11SimpleTextControl::getSelectionCount()
{
	return selectionEnd_ - selectionStart_;
}


void X11SimpleTextControl::setSelectionMark( const unsigned long& start, const unsigned long& count )
{
	selectionStart_ = start;
	selectionEnd_ = selectionStart_ + count;
}


void X11SimpleTextControl::setSelectionFont( Font* font )
{

}


void X11SimpleTextControl::setParagraphAlignment( const TextAlignmentType& alignment )
{

}


void X11SimpleTextControl::scrollToLine( const ulong32& lineIndex )
{

}

void X11SimpleTextControl::handlePaintEvent()
{
	Point* caret = getPositionFromCharIndex( selectionStart_ );

	GraphicsContext* gc = control_->getContext();
	if ( updateRects_.empty() ) {
		return;
	}

	std::vector<Rect>::iterator it = updateRects_.begin();

	Rect clipBounds = updateRects_.front();

	while ( it != updateRects_.end() ) {
		Rect& r = *it;

		clipBounds.left_ = minVal<double>( clipBounds.left_, r.left_ );
		clipBounds.top_ = minVal<double>( clipBounds.top_, r.top_ );

		clipBounds.right_ = maxVal<double>( clipBounds.right_, r.right_ );
		clipBounds.bottom_ = maxVal<double>( clipBounds.bottom_, r.bottom_ );

		it ++;
	}

	clipBounds.normalize();
	if ( (clipBounds.getHeight() <= 0.0) || (clipBounds.getWidth() <= 0.0) ) {
		return;
	}

	Rect clientRect = *control_->getClientBounds();

	gc->getPeer()->setContextID(wndHandle_);

	gc->setColor( control_->getColor() );
	gc->rectangle( &clientRect );
	gc->fillPath();
	gc->setCurrentFont( control_->getFont() );

	clientRect.left_ += leftMargin_;
	clientRect.right_ -= rightMargin_;

	clientRect.normalize();

	if ( clientRect.getWidth() > 0.0 ) {

		const VCFChar* P = text_.c_str();
		const VCFChar* start = P;
		const VCFChar* line = P;

		int size = text_.size();
		double y = 0;
		double x = clientRect.left_;
		String lineOfText;


		while ( ((P-start) < size) && (y < clientRect.getHeight()) ) {
			if ( !((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
				lineOfText.append( 1, *P );
			}

			x = gc->getTextWidth( lineOfText ) + clientRect.left_;


			if ( (x >= clientRect.getWidth()) || ((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {

				line = P;
				//scootch back
				if ( (*P != ' ') && (*P != '\n') && (*P != '\r') ){
					const VCFChar* tmp = P;
					while ( (*P != ' ') && (*P != '\n') && (*P != '\r') && (P > start) ) {
						P--;
					}
					lineOfText.erase( lineOfText.size()-(tmp-P), tmp-P );
					line ++;
				}

				gc->textAt( clientRect.left_, y, lineOfText );

				y += gc->getTextHeight( lineOfText );

				x = clientRect.left_;


				if ( ((*P == '\n') || ((*P == '\r') && (*(P+1) == '\n'))) ) {
					if ( (*P == '\r') && (*(P+1) == '\n') ) {
						P++;
						line++;
					}
					line++;
				}
				lineOfText = "";
			}
			P++;
		}
		if ( (line < P) && ((P-line) < size) && (y < clientRect.getHeight()) ) {
			lineOfText = "";
			lineOfText.append( line, P-line );

			gc->textAt( 0, y, lineOfText );
		}

		if ( NULL != caret ) {
			Rect r( caret->x_, caret->y_, caret->x_ + 2, caret->y_ + gc->getTextHeight( "EM" ) );
			gc->rectangle( &r );
			gc->setColor( Color::getColor("blue") );
			gc->fillPath();
		}
	}
	updateRects_.clear();
}


void X11SimpleTextControl::onTextModelTextChanged( TextEvent* event )
{
	if ( NULL != event ){
		String text = event->getChangeText();
		if ( true == okToResetControlText_ ){
			setText( text );
		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:40  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:12:45  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/09 05:38:54  ddiego
*added a VERY simple editable text control. It is dog slow though, but
*better than nothing.
*
Auto generated C++ implementation for class X11SimpleTextControl
*/


