//GTKWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKWindow.h"
#include "vcf/ApplicationKit/GTKUIToolkit.h"


using namespace VCF;

GTKWindow::GTKWindow( Control* control, Control* owner ):
	sizeState_(GTKWindow::wsNone)
{

	control_ = control;
}

GTKWindow::~GTKWindow()
{

}

void GTKWindow::create( Control* owningControl )
{
	GTKGraphicsToolkit* grafToolkit = reinterpret_cast<GTKGraphicsToolkit*>(GraphicsToolkit::internal_getDefaultGraphicsToolkit());
	GTKUIToolkit* toolkit = (GTKUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();

	wndHandle_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if ( NULL == wndHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("gtk_window_new() failed") );
	}
	gtk_widget_realize ( wndHandle_ );



	g_signal_connect (G_OBJECT (wndHandle_), "delete_event",
		      G_CALLBACK (GTKWindow::deleteEvent), (gpointer)this);

	g_signal_connect (G_OBJECT (wndHandle_), "destroy",
		      G_CALLBACK (GTKWindow::destroyEvent), (gpointer)this);

	containerWidget_ = AbstractGTKControl::Container::create(NULL, this);	//gtk_layout_new( NULL, NULL );

		//
	gtk_container_add( GTK_CONTAINER( wndHandle_ ), containerWidget_ );

	GtkWindow* wnd = (GTK_WINDOW(wndHandle_) );

	GdkGeometry geom;
	memset( &geom, 0, sizeof(geom) );
	geom.min_width = 1;
	geom.min_height = 1;

	gtk_window_set_geometry_hints( wnd, wndHandle_, &geom,
									(GdkWindowHints)(GDK_HINT_MIN_SIZE) );

	AbstractGTKControl::registerGTKControl( this );



	gtk_widget_set_name ( containerWidget_, "VCF::WINDOW-Container" );

	gtk_widget_show (containerWidget_);

	gtk_widget_set_app_paintable(wndHandle_, TRUE);
}


void GTKWindow::initGdkEventHandlers()
{
	AbstractGTKControl::initGdkEventHandlers();

	AbstractGTKControl::gtkControlMap[containerWidget_] = this;

	gtk_widget_add_events( containerWidget_, GDK_ALL_EVENTS_MASK );

	g_signal_connect ( G_OBJECT (containerWidget_), "event",
						G_CALLBACK (GTKWindow::onGdkEventForContainer),
						(gpointer)this );
}

gboolean GTKWindow::onGdkEventForContainer( GtkWidget *widget, GdkEvent *event, gpointer user_data )
{
	GTKWindow* thisPtr = (GTKWindow*)user_data;
	if ( widget != thisPtr->containerWidget_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Gdk event received for a widget that doesn't match the AbstractGTKControl's widget") );
	}

	return thisPtr->handleEvent( event );
}


long GTKWindow::getHandleID()
{
	return (long)containerWidget_;
}

Rect GTKWindow::getClientBounds()
{
	clientBounds_ = getBounds();
	clientBounds_.offset( -clientBounds_.left_, -clientBounds_.top_ );
	return clientBounds_;
}

void  GTKWindow::setClientBounds( Rect* bounds )
{
	setBounds( bounds );
	clientBounds_ = *bounds;
}

void GTKWindow::setBounds( Rect* rect )
{
	if ( GTK_WIDGET_REALIZED (wndHandle_) )  {

		gdk_window_move_resize( wndHandle_->window,
								(int)rect->left_,
								(int)rect->top_,
								(int)rect->getWidth(),
								(int)rect->getHeight() );


    }
}

void GTKWindow::close()
{

	//GTKUIToolkit* toolkit = reinterpret_cast<GTKUIToolkit*>(UIToolkit::getDefaultUIToolkit());
	//GTKGraphicsToolkit* grafToolkit = reinterpret_cast<GTKGraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());


}

void GTKWindow::setFrameStyle( const FrameStyleType& frameStyle )
{
	gboolean useDecorations = FALSE;
	gboolean resizeable = TRUE;

	switch ( frameStyle ){
		case fstSizeable :{
			resizeable = TRUE;
		}
		break;

		case fstNoBorder :{
			useDecorations = FALSE;
			resizeable = TRUE;
		}
		break;

		case fstFixed :{
			useDecorations = TRUE;
			resizeable = FALSE;
		}
		break;

		case fstNoBorderFixed :{
			useDecorations = FALSE;
			resizeable = FALSE;
		}
		break;

		case fstToolbarBorder :{
			useDecorations = TRUE;
			resizeable = TRUE;
		}
		break;

		case fstToolbarBorderFixed :{
			useDecorations = TRUE;
			resizeable = FALSE;
		}
		break;

	}
	gtk_window_set_decorated( (GtkWindow*)wndHandle_, useDecorations );
	gtk_window_set_resizable( (GtkWindow*)wndHandle_, resizeable );
}

void GTKWindow::setFrameTopmost( const bool& isTopmost )
{
	if ( true == isTopmost ) {

	}

}

bool GTKWindow::isMaximized()
{
	return sizeState_ == GTKWindow::wsMaximized;
}

void GTKWindow::setMaximized( const bool maximised )
{
	if ( maximised ) {
		sizeState_ = GTKWindow::wsMaximized;
		gtk_window_maximize( (GtkWindow*)wndHandle_ );
	}
	else{
		sizeState_ = GTKWindow::wsNormal;
		gtk_window_unmaximize( (GtkWindow*)wndHandle_ );
	}
}

bool GTKWindow::isMinimized()
{
	return sizeState_ == GTKWindow::wsMinimized;
}

void GTKWindow::setMinimized( const bool& minimized )
{
	if ( minimized ) {
		sizeState_ = GTKWindow::wsMinimized;
		gtk_window_iconify ( (GtkWindow*)wndHandle_ );
	}
	else {
		sizeState_ = GTKWindow::wsMinimized;
		gtk_window_deiconify( (GtkWindow*)wndHandle_ );
	}
}

void GTKWindow::restore()
{
	if ( isMaximized() ) {
		gtk_window_unmaximize( (GtkWindow*)wndHandle_ );
	}
	else if ( isMinimized() ) {
		gtk_window_deiconify( (GtkWindow*)wndHandle_ );
	}
	sizeState_ = GTKWindow::wsNormal;
}

void GTKWindow::setIconImage( Image* icon )
{

}

gint GTKWindow::deleteEvent( GtkWidget *widget, GdkEvent  *event, gpointer data )
{
	gint result = TRUE;
	GTKWindow* gtkWnd = (GTKWindow*)data;

	VCF::Window* window = (VCF::Window*)gtkWnd->getControl();

	if ( window->allowClose() ) {

		VCF::WindowEvent event( gtkWnd->getControl(), WINDOW_EVENT_CLOSE );


		window->FrameClose.fireEvent( &event );

		//check if the main window is clossing - if it is
		//then close the app !
		result = FALSE;
	}


	return result;
}

void GTKWindow::destroyEvent( GtkWidget *widget, gpointer data )
{
	GTKWindow* gtkWnd = (GTKWindow*)data;

	VCF::Window* window = (VCF::Window*)gtkWnd->getControl();

	Application* app = Application::getRunningInstance();
	if ( NULL != app ){
		Window* mainWindow = app->getMainWindow();
		if ( mainWindow == gtkWnd->getControl() ){
			gtk_main_quit();
		}
	}
}

gboolean GTKWindow::handleEvent( GdkEvent* gtkEvent )
{
	GTKUIToolkit* toolkit = reinterpret_cast<GTKUIToolkit*>(UIToolkit::internal_getDefaultUIToolkit());

	gboolean result = FALSE;

	if ( gtkEvent->any.window == containerWidget_->window ) {
		StringUtils::trace( "containerWidget_ event\n" );
	}
	switch ( gtkEvent->type ) {

		case GDK_EXPOSE : {
			if ( gtkEvent->any.window == containerWidget_->window ) {
				GdkEventExpose* gdkExposeEvent = (GdkEventExpose*)gtkEvent;

				GraphicsContext* gc = control_->getContext();

				gc->getPeer()->setContextID( (ulong32)containerWidget_->window );

				control_->paint( gc );

				repainted_ = false;
				//result = TRUE;
			}

		}
		break;

		case GDK_CONFIGURE : {
			if ( gtkEvent->any.window == wndHandle_->window ) {
				printf( "GDK_CONFIGURE: gtkEvent->any.window == wndHandle_->window\n" );
				GdkEventConfigure* configEv = (GdkEventConfigure*)gtkEvent;

				gdk_window_move_resize( containerWidget_->window,
								(int)0,
								(int)0,
								(int)configEv->width,
								(int)configEv->height );

				AbstractGTKControl::Container::move( containerWidget_,


											0, 0, configEv->width, configEv->height );

				result = AbstractGTKControl::handleEvent( gtkEvent );




			}
			else {
				printf( "GDK_CONFIGURE: gtkEvent->any.window != wndHandle_->window\n" );
				result = AbstractGTKControl::handleEvent( gtkEvent );
			}
		}
		break;

		case GDK_BUTTON_PRESS : case GDK_2BUTTON_PRESS : case GDK_3BUTTON_PRESS : {
			if ( gtkEvent->any.window == wndHandle_->window ) {
				result = TRUE;
			}
			else {
				result = AbstractGTKControl::handleEvent( gtkEvent );
			}
		}
		break;

		default : {
			if ( gtkEvent->any.window == containerWidget_->window ) {
				result = AbstractGTKControl::handleEvent( gtkEvent );
			}
		}
		break;
	}

	return result;
}


String GTKWindow::getText()
{
	return text_;
}

/**
 * sets the text for the widget
 */
void GTKWindow::setText( const String& text )
{
	if ( text == text_ ) {
		return;
	}

	text_ = text;

	gtk_window_set_title( (GtkWindow*)wndHandle_, text_.ansi_c_str() );
}


Rect GTKWindow::getBounds()
{
	Rect result;
	int x, y, w, h;
	x = y = w = h = 0;

	gdk_window_get_geometry( wndHandle_->window, &x, &y, &w, &h, NULL );

	result.left_ = x;
	result.top_ = y;
	result.right_ = x + w;
	result.bottom_ = y + h;


	return result;
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
*Revision 1.11  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.7.2.4  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.7.2.3  2004/02/16 05:34:04  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.7.2.2  2004/01/24 16:56:45  ddiego
*general check in
*
*Revision 1.7.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.7  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.6  2003/08/09 02:56:46  ddiego
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
*Revision 1.5.2.4  2003/07/13 03:45:11  ddiego
*Added further fixes for the GTK port. Now have the event handling working
*correctly, and fixed an issue with too many repaint messages being sent
*which caused 100% CPU utilization.
*
*Revision 1.5.2.3  2003/07/09 03:53:19  ddiego
*some fixes to gtk port
*
*Revision 1.5.2.2  2003/06/01 16:44:01  ddiego
*further GTK support added
*
*Revision 1.5.2.1  2003/05/30 04:13:11  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.5  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.3  2003/04/23 03:42:54  ddiego
*further gtk dev got basic eventing code in place
*
*Revision 1.4.2.2  2003/04/19 03:31:15  ddiego
*basic code in place for gtk port for ApplicationKit - needs to be tested in
*linux
*
*Revision 1.4.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


