//GTKCommandButton.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/AbstractGTKControl.h"
#include "vcf/ApplicationKit/GTKCommandButton.h"
#include "vcf/ApplicationKit/CommandButton.h"

using namespace VCF;

GTKCommandButton::GTKCommandButton( CommandButton* component )
{
	control_ = ( Control* ) component;
	commandButton_ = component;
	gtkButton_ = NULL;
}

GTKCommandButton::~GTKCommandButton()
{}

void GTKCommandButton::create( Control* owningControl )
{
	GTKGraphicsToolkit * grafToolkit = ( GTKGraphicsToolkit* ) GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) UIToolkit::internal_getDefaultUIToolkit();

	wndHandle_ = gtk_button_new_with_label ( "" );

	if ( NULL == wndHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "gtk_button_new_with_label() failed" ) );
	}

	gtkButton_ = GTK_BUTTON( wndHandle_ );

	gtk_container_add( GTK_CONTAINER( toolkit->getDefaultParent() ), wndHandle_ );

	gtk_widget_show ( wndHandle_ );

	g_signal_connect ( G_OBJECT ( gtkButton_ ), "clicked",
	                   G_CALLBACK ( GTKCommandButton::gtkButtonClicked ), ( gpointer ) this );

	AbstractGTKControl::registerGTKControl( this );
}

Image* GTKCommandButton::getImage()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return NULL;
}

void GTKCommandButton::setImage( Image* image )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

ButtonState GTKCommandButton::getState()
{
	return state_;
}

void GTKCommandButton::setState( const ulong32& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKCommandButton::gtkButtonClicked( GtkButton* button, gpointer data )
{
	GTKCommandButton * thisPtr = ( GTKCommandButton* ) data;
	thisPtr->commandButton_->click();
}

String GTKCommandButton::getText()
{
	String result;
	result = gtk_button_get_label( gtkButton_ );
	return result;
}

void GTKCommandButton::setText( const String& text )
{
	gtk_button_set_label( gtkButton_, text.ansi_c_str() );
}

void GTKCommandButton::setBorder( Border* border )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

gboolean GTKCommandButton::handleEvent( GdkEvent* gtkEvent )
{
	GTKUIToolkit * toolkit = reinterpret_cast<GTKUIToolkit*>( UIToolkit::internal_getDefaultUIToolkit() );

	gboolean result = FALSE;

	switch ( gtkEvent->type ) {

		case GDK_EXPOSE : {
				AbstractGTKControl::handleEvent( gtkEvent );

				return FALSE;
			}
			break;

		case GDK_BUTTON_PRESS :
		case GDK_2BUTTON_PRESS :
		case GDK_3BUTTON_PRESS : {
				result = AbstractGTKControl::handleEvent( gtkEvent );
			}
			break;

		default : {
				result = AbstractGTKControl::handleEvent( gtkEvent );
			}
			break;
	}

	return result;
}

void GTKCommandButton::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKCommandButton::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKCommandButton::repaint( Rect* repaintRect, const bool& immediately )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

/**
$Id$
*/
