//GTKTextControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/AbstractGTKControl.h"
#include "vcf/ApplicationKit/GTKTextControl.h"
#include "vcf/ApplicationKit/TextControl.h"


using namespace VCF;


GTKTextControl::GTKTextControl( TextControl* component, const bool& isMultiLineControl ) :
		textControl_( component ),
		isMultiLineControl_( isMultiLineControl ),
		singleLine_( NULL ),
		multiLine_( NULL ),
		internalTextChange_( false )
{
}

GTKTextControl::~GTKTextControl()
{
}

void GTKTextControl::create( Control* owningControl )
{
	control_ = owningControl;

	GTKGraphicsToolkit* grafToolkit = ( GTKGraphicsToolkit* ) GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) UIToolkit::internal_getDefaultUIToolkit();

	if ( isMultiLineControl_ ) {
		wndHandle_ = gtk_text_view_new();

		if ( NULL == wndHandle_ ) {
			throw RuntimeException( MAKE_ERROR_MSG_2( "gtk_text_view_new() failed" ) );
		}

		multiLine_ = GTK_TEXT_VIEW( wndHandle_ );
		gtk_text_view_set_wrap_mode ( multiLine_, GTK_WRAP_WORD );
	} else {
		wndHandle_ = gtk_entry_new();

		if ( NULL == wndHandle_ ) {
			throw RuntimeException( MAKE_ERROR_MSG_2( "gtk_entry_new() failed" ) );
		}

		singleLine_ = GTK_ENTRY( wndHandle_ );
	}

	gtk_container_add( GTK_CONTAINER( toolkit->getDefaultParent() ), wndHandle_ );

	gtk_widget_show ( wndHandle_ );

	TextModelEventHandler<GTKTextControl>* tml =
	    new TextModelEventHandler<GTKTextControl>( this, &GTKTextControl::onTextModelTextChanged, "GTKTextControl::onTextModelTextChanged" );


	TextModel* tm = textControl_->getTextModel();
	tm->addTextModelChangedHandler( tml );

	AbstractGTKControl::registerGTKControl( this );
}

void GTKTextControl::setRightMargin( const double & rightMargin )
{
	if ( isMultiLineControl_ ) {
		gtk_text_view_set_right_margin( multiLine_, ( gint ) rightMargin );
	}
}

void GTKTextControl::setLeftMargin( const double & leftMargin )
{
	if ( isMultiLineControl_ ) {
		gtk_text_view_set_left_margin( multiLine_, ( gint ) leftMargin );
	}
}

unsigned long GTKTextControl::getLineCount()
{
	unsigned long result = 1;
	if ( isMultiLineControl_ ) {
		GtkTextBuffer * buff = gtk_text_view_get_buffer( multiLine_ );
		result = ( unsigned long ) gtk_text_buffer_get_line_count( buff );
	}
	return result;
}

unsigned long GTKTextControl::getCurrentLinePosition()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	unsigned long result = 0;
	if ( isMultiLineControl_ ) {
		//result = gtk_text_view_get_left_margin( multiLine_ );
	}
	return result;
}

double GTKTextControl::getLeftMargin()
{
	double result = 0.0;
	if ( isMultiLineControl_ ) {
		result = gtk_text_view_get_left_margin( multiLine_ );
	}
	return result;
}

double GTKTextControl::getRightMargin()
{
	double result = 0.0;
	if ( isMultiLineControl_ ) {
		result = gtk_text_view_get_right_margin( multiLine_ );
	}
	return result;
}

Point* GTKTextControl::getPositionFromCharIndex( const unsigned long& index )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	if ( isMultiLineControl_ ) {
	}
	return NULL;
}

unsigned long GTKTextControl::getCharIndexFromPosition( Point* point )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	if ( isMultiLineControl_ ) {
	}
	return 0;
}

unsigned long GTKTextControl::getCaretPosition()
{
	unsigned long result = 0;
	if ( isMultiLineControl_ ) {
	}
	else {
		GtkEditable * editable = GTK_EDITABLE( singleLine_ );
		result = gtk_editable_get_position( editable );
	}

	return result;
}

void GTKTextControl::setCaretPosition( const unsigned long& caretPos )
{
	if ( isMultiLineControl_ ) {
	}
	else {
		GtkEditable * editable = GTK_EDITABLE( singleLine_ );
		gtk_editable_set_position( editable, caretPos );
	}
}

unsigned long GTKTextControl::getSelectionStart()
{
	unsigned long result = 0;
	if ( isMultiLineControl_ ) {
	}
	else {
		GtkEditable * editable = GTK_EDITABLE( singleLine_ );
		int start = 0;
		gtk_editable_get_selection_bounds( editable, &start, NULL );
		result = ( unsigned long ) start;
	}

	return result;
}

unsigned long GTKTextControl::getSelectionCount()
{
	unsigned long result = 0;

	if ( isMultiLineControl_ ) {
	}
	else {
		GtkEditable * editable = GTK_EDITABLE( singleLine_ );
		int start = 0;
		int end = 0;
		gtk_editable_get_selection_bounds( editable, &start, &end );
		result = ( unsigned long ) ( end - start );
	}

	return result;
}

void GTKTextControl::setSelectionMark( const unsigned long& start, const unsigned long& count )
{
	if ( isMultiLineControl_ ) {
	}
	else {
		gtk_entry_select_region( singleLine_, start, start + count );
	}

}

void GTKTextControl::setSelectionFont( Font* font )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	if ( isMultiLineControl_ ) {
	}
}

void GTKTextControl::setParagraphAlignment( const TextAlignmentType& alignment )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	if ( isMultiLineControl_ ) {
	}
}

void GTKTextControl::scrollToLine( const ulong32& lineIndex )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	if ( isMultiLineControl_ ) {
	}
}

void GTKTextControl::onTextModelTextChanged( TextEvent* e )
{
	if ( !internalTextChange_ ) {
		TextModel * tm = textControl_->getTextModel();

		if ( isMultiLineControl_ ) {
			GtkTextBuffer * buff = gtk_text_view_get_buffer( multiLine_ );
			String text = tm->getText();
			gtk_text_buffer_set_text( buff, text.ansi_c_str(), text.size() );
		} else {
			gtk_entry_set_text( singleLine_, tm->getText().ansi_c_str() );
		}
	}
}

gboolean GTKTextControl::handleEvent( GdkEvent* gtkEvent )
{
	GTKUIToolkit * toolkit = reinterpret_cast<GTKUIToolkit*>( UIToolkit::internal_getDefaultUIToolkit() );

	gboolean result = FALSE;

	switch ( gtkEvent->type ) {

		case GDK_KEY_PRESS : {
				internalTextChange_ = true;

				result = AbstractGTKControl::handleEvent( gtkEvent );

				internalTextChange_ = false;
			}
			break;

		default : {
				result = AbstractGTKControl::handleEvent( gtkEvent );
			}
			break;
	}

	return result;
}


String GTKTextControl::getText()
{
	String result;
	if ( isMultiLineControl_ ) {
		GtkTextIter start;
		GtkTextIter end;
		GtkTextBuffer* buff = gtk_text_view_get_buffer( multiLine_ );
		gtk_text_buffer_get_iter_at_offset( buff, &start, 0 );

		gtk_text_buffer_get_iter_at_offset( buff, &end, -1 );
		gchar* text = gtk_text_buffer_get_text( buff, &start, &end, FALSE );
		result = text;
		//delete []  text;

	} else {
		result = String( gtk_entry_get_text( singleLine_ ) );
	}

	return result;
}

void GTKTextControl::setText( const String& text )
{
	TextModel * tm = textControl_->getTextModel();
	tm->setText( text );
}

void GTKTextControl::scrollToSelection( const bool& showEndSel )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::setReadOnly( const bool& readonly )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::setBorder( Border* border )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

ulong32 GTKTextControl::getTotalPrintablePageCount( PrintContext* context )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::print( PrintContext* context, const long& page )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::finishPrinting()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::repaint( Rect* repaintRect, const bool& immediately )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::insertText( unsigned int start, const String& text )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::deleteText( unsigned int start, unsigned int length )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::setDefaultStyle( Dictionary& styles )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

double GTKTextControl::getBottomMargin()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0.0;
}

void GTKTextControl::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::getStyle( unsigned int start, unsigned int length, VCF::Dictionary& styles )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

unsigned int GTKTextControl::getTextLength()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0;
}

void GTKTextControl::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::setBottomMargin( const double & bottomMargin )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

String GTKTextControl::getText( unsigned int start, unsigned int length )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return "";
}

OSHandleID GTKTextControl::getTextObjectHandle()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return NULL;
}

void GTKTextControl::setTopMargin( const double & topMargin )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKTextControl::paint( GraphicsContext* context, const Rect& paintRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

Rect GTKTextControl::getContentBoundsForWidth( const double& width )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return Rect();
}

double GTKTextControl::getTopMargin()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0.0;
}

/**
$Id$
*/
