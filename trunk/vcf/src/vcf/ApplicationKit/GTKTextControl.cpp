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


GTKTextControl::GTKTextControl( TextControl* component, const bool& isMultiLineControl ):
	textControl_(component),
	isMultiLineControl_(isMultiLineControl),
	singleLine_(NULL),
	multiLine_(NULL),
	internalTextChange_(false)
{

}

GTKTextControl::~GTKTextControl()
{

}

void GTKTextControl::create( Control* owningControl )
{
	control_ = owningControl;

	GTKGraphicsToolkit* grafToolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	GTKUIToolkit* toolkit = (GTKUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();

	if ( isMultiLineControl_ ) {
		wndHandle_ = gtk_text_view_new();

		if ( NULL == wndHandle_ ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("gtk_text_view_new() failed") );
		}

		multiLine_ = GTK_TEXT_VIEW( wndHandle_ );
		gtk_text_view_set_wrap_mode ( multiLine_, GTK_WRAP_WORD );
	}
	else {
		wndHandle_ = gtk_entry_new();

		if ( NULL == wndHandle_ ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("gtk_entry_new() failed") );
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
		gtk_text_view_set_right_margin( multiLine_, (gint)rightMargin );
	}
}

void GTKTextControl::setLeftMargin( const double & leftMargin )
{
	if ( isMultiLineControl_ ) {
		gtk_text_view_set_left_margin( multiLine_, (gint)leftMargin );
	}
}

unsigned long GTKTextControl::getLineCount()
{
	unsigned long result = 1;
	if ( isMultiLineControl_ ) {
		 GtkTextBuffer* buff = gtk_text_view_get_buffer( multiLine_ );
		 result = (unsigned long) gtk_text_buffer_get_line_count( buff );
	}
	return result;
}

unsigned long GTKTextControl::getCurrentLinePosition()
{
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
	if ( isMultiLineControl_ ) {

	}
	return NULL;
}

unsigned long GTKTextControl::getCharIndexFromPosition( Point* point )
{
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
		GtkEditable* editable = GTK_EDITABLE( singleLine_ );
		result = gtk_editable_get_position( editable );
	}

	return result;
}

void GTKTextControl::setCaretPosition( const unsigned long& caretPos )
{
	if ( isMultiLineControl_ ) {

	}
	else {
		GtkEditable* editable = GTK_EDITABLE( singleLine_ );
		gtk_editable_set_position( editable, caretPos );
	}
}

unsigned long GTKTextControl::getSelectionStart()
{
	unsigned long result = 0;
	if ( isMultiLineControl_ ) {

	}
	else {
		GtkEditable* editable = GTK_EDITABLE( singleLine_ );
		int start = 0;
		gtk_editable_get_selection_bounds( editable, &start, NULL );
		result = (unsigned long)start;
	}

	return result;
}

unsigned long GTKTextControl::getSelectionCount()
{
	unsigned long result = 0;

	if ( isMultiLineControl_ ) {

	}
	else {
		GtkEditable* editable = GTK_EDITABLE( singleLine_ );
		int start = 0;
		int end = 0;
		gtk_editable_get_selection_bounds( editable, &start, &end );
		result = (unsigned long)(end - start);
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
	if ( isMultiLineControl_ ) {

	}
}

void GTKTextControl::setParagraphAlignment( const TextAlignmentType& alignment )
{
	if ( isMultiLineControl_ ) {

	}
}

void GTKTextControl::scrollToLine( const ulong32& lineIndex )
{
	if ( isMultiLineControl_ ) {

	}
}


void GTKTextControl::onTextModelTextChanged( TextEvent* e )
{
	if ( !internalTextChange_ ) {
		TextModel* tm = textControl_->getTextModel();

		if ( isMultiLineControl_ ) {
			GtkTextBuffer* buff = gtk_text_view_get_buffer( multiLine_ );
			String text = tm->getText();
			gtk_text_buffer_set_text( buff, text.ansi_c_str(), text.size() );
		}
		else {
			gtk_entry_set_text( singleLine_, tm->getText().ansi_c_str() );
		}
	}
}

gboolean GTKTextControl::handleEvent( GdkEvent* gtkEvent )
{
	GTKUIToolkit* toolkit = reinterpret_cast<GTKUIToolkit*>(UIToolkit::internal_getDefaultUIToolkit());

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

	}
	else {
		result = String( gtk_entry_get_text( singleLine_ ) );
	}

	return result;
}

void GTKTextControl::setText( const String& text )
{
	TextModel* tm = textControl_->getTextModel();
	tm->setText( text );
}

void GTKTextControl::scrollToSelection( const bool& showEndSel )
{

}

void GTKTextControl::setReadOnly( const bool& readonly )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:25  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.2  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.2.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.2  2003/08/09 02:56:46  ddiego
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
*Revision 1.1.2.1  2003/07/14 22:52:53  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*/


