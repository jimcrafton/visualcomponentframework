//AbstractGTKControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/AbstractGTKControl.h"
#include "vcf/ApplicationKit/GTKControl.h"

using namespace VCF;

AbstractGTKControl::GTKControlMap AbstractGTKControl::gtkControlMap;

static GtkContainerClass * internalVCFParentClass = NULL;





AbstractGTKControl::AbstractGTKControl() :
		enabled_( false ),
		control_( NULL ),
		wndHandle_( NULL ),
		parent_( NULL ),
		repainted_( false )
{
}

AbstractGTKControl::~AbstractGTKControl()
{
}

void AbstractGTKControl::create( Control* owningControl )
{
}

void AbstractGTKControl::destroyControl()
{
}

String AbstractGTKControl::getText()
{
	String result;

	return result;
}

void AbstractGTKControl::setText( const String& text )
{
}

void AbstractGTKControl::setBounds( Rect* rect )
{
	bounds_ = *rect;


	if ( !GTK_IS_VCF_CONTAINER( wndHandle_ ) ) {
		GtkWidget * gdkParent = gtk_widget_get_parent ( wndHandle_ );

		if ( !GTK_IS_VCF_CONTAINER( gdkParent ) ) {
			//throw RuntimeException( MAKE_ERROR_MSG_2("Can't set bounds for gtk widget if it's not parented to a valid VCF widget!") );
			return ;
		}

		AbstractGTKControl::Container::moveChild( GTK_VCF_CONTAINER( gdkParent ), wndHandle_, ( int ) rect->left_, ( int ) rect->top_, ( int ) rect->getWidth(), ( int ) rect->getHeight() );
	} else {
		AbstractGTKControl::Container::move( wndHandle_, ( int ) rect->left_, ( int ) rect->top_, ( int ) rect->getWidth(), ( int ) rect->getHeight() );
	}

}

bool AbstractGTKControl::beginSetBounds( const ulong32& numberOfChildren )
{
	return true;
}

void AbstractGTKControl::endSetBounds()
{
}

Rect AbstractGTKControl::getBounds()
{
	return bounds_;
}

void AbstractGTKControl::setVisible( const bool& visible )
{
	if ( GTK_WIDGET_REALIZED( wndHandle_ ) ) {
		if ( visible ) {
			gtk_widget_show ( wndHandle_ );
		} else {
			gtk_widget_hide( wndHandle_ );
		}
	}
}

bool AbstractGTKControl::getVisible()
{
	//if ( GTK_WIDGET_REALIZED( wndHandle_ ) ) {
	//return gdk_window_is_visible( wndHandle_->window ) ? true : false;
	//}
	return GTK_WIDGET_VISIBLE( wndHandle_ ) ? true : false;
}


Control* AbstractGTKControl::getControl()
{
	return control_;
}

void AbstractGTKControl::setControl( Control* component )
{
	control_ = component;
}

void AbstractGTKControl::setCursor( Cursor* cursor )
{
	gdk_window_set_cursor( wndHandle_->window, ( GdkCursor* ) cursor->getPeer() ->getCursorHandleID() );
}

void AbstractGTKControl::setParent( Control* parent )
{
	GtkWidget * gdkParent = ( GtkWidget* ) parent->getPeer() ->getHandleID();

	if ( NULL == gtk_widget_get_parent( wndHandle_ ) ) {
		gtk_container_add ( GTK_CONTAINER ( gdkParent ), wndHandle_ );
	} else {
		gtk_widget_reparent( wndHandle_, gdkParent );
	}
}

Control* AbstractGTKControl::getParent()
{
	Control * result = NULL;

	GtkWidget* gdkParent = gtk_widget_get_parent ( wndHandle_ );
	AbstractGTKControl* parentCtrl = getGTKControlFromWidget( gdkParent );
	if ( NULL != parentCtrl ) {
		result = parentCtrl->getControl();
	}

	return result;
}

bool AbstractGTKControl::isFocused()
{

	return control_ == Control::getCurrentFocusedControl();
}

void AbstractGTKControl::setFocused()
{
	if ( GTK_WIDGET_CAN_FOCUS( wndHandle_ ) ) {
		gtk_widget_grab_focus( wndHandle_ ); //gdk_window_focus( wndHandle_->window, GDK_CURRENT_TIME );
	}
}

bool AbstractGTKControl::isEnabled()
{
	return enabled_;
}

void AbstractGTKControl::setEnabled( const bool& enabled )
{
	enabled_ = enabled;
}

void AbstractGTKControl::setFont( Font* font )
{
	GTKFont * peer = ( GTKFont* ) font->getFontPeer();

	gtk_widget_modify_font( wndHandle_, peer->getPangoFontDescription() );

	//gtk_widget_modify_font
	//((GTKFont*)font->getPeer())->getPangoFontDescription()
}

void AbstractGTKControl::repaint( Rect* repaintRect )
{
	if ( repainted_ ) {
		return ;
	}

	repainted_ = true;

	if ( GTK_WIDGET_DRAWABLE( wndHandle_ ) ) {

		GdkRectangle rect;
		if ( NULL != repaintRect ) {
			rect.x = ( int ) repaintRect->left_;
			rect.y = ( int ) repaintRect->top_;
			rect.width = ( int ) repaintRect->getWidth();
			rect.height = ( int ) repaintRect->getHeight();
		} else {

			rect.x = 0;
			rect.y = 0;
			rect.width = ( int ) bounds_.getWidth();
			rect.height = ( int ) bounds_.getHeight();
		}

		gdk_window_invalidate_rect( wndHandle_->window, &rect, FALSE );
	}
}

void AbstractGTKControl::keepMouseEvents()
{
	//return;
	//GdkEventMask eventMask = (GdkEventMask)
	//							(GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_RELEASE_MASK);

	int eventMask = GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_BUTTON1_MOTION_MASK | GDK_BUTTON2_MOTION_MASK | GDK_BUTTON3_MOTION_MASK;
	int res = gdk_pointer_grab( wndHandle_->window, FALSE, ( GdkEventMask ) eventMask, NULL, NULL, GDK_CURRENT_TIME );

	if ( res != GDK_GRAB_SUCCESS ) {
		//report error throw exception here ????
		StringUtils::traceWithArgs( "gdk_pointer_grab failed!\n" );
		return ;
	}

	gtk_grab_add ( wndHandle_ );
}

void AbstractGTKControl::releaseMouseEvents()
{
	//return;
	GdkDisplay * display = gtk_widget_get_display ( wndHandle_ );

	gtk_grab_remove ( wndHandle_ );

	if ( gdk_display_pointer_is_grabbed ( display ) ) {

		gdk_display_pointer_ungrab ( display, GDK_CURRENT_TIME );
	}

	gdk_pointer_ungrab( GDK_CURRENT_TIME );
}


String GTK_EventToString( GdkEvent* gtkEvent )
{
	String result;

	static unsigned long count = 0;

	switch ( gtkEvent->type ) {
		case GDK_NOTHING : {
				result += "GDK_NOTHING";
			}
			break;

		case GDK_KEY_RELEASE : {
				result += "GDK_KEY_RELEASE";
			}
			break;

		case GDK_ENTER_NOTIFY : {
				result += "GDK_ENTER_NOTIFY";
			}
			break;

		case GDK_KEY_PRESS : {
				result += "GDK_KEY_PRESS";
			}
			break;

		case GDK_BUTTON_RELEASE : {
				result += "GDK_BUTTON_RELEASE";
			}
			break;

		case GDK_3BUTTON_PRESS : {
				result += "GDK_3BUTTON_PRESS";
			}
			break;

		case GDK_2BUTTON_PRESS : {
				result += "GDK_2BUTTON_PRESS";
			}
			break;

		case GDK_BUTTON_PRESS : {
				result += "GDK_BUTTON_PRESS";
			}
			break;

		case GDK_MOTION_NOTIFY : {
				result += "GDK_MOTION_NOTIFY";
			}
			break;
		case GDK_EXPOSE : {
				result += "GDK_EXPOSE";
			}
			break;

		case GDK_DESTROY : {
				result += "GDK_DESTROY";
			}
			break;

		case GDK_DELETE : {
				result += "GDK_DELETE";
			}
			break;

		case GDK_SELECTION_REQUEST : {
				result += "GDK_SELECTION_REQUEST";
			}
			break;

		case GDK_SELECTION_CLEAR : {
				result += "GDK_SELECTION_CLEAR";
			}
			break;

		case GDK_PROPERTY_NOTIFY : {
				result += "GDK_PROPERTY_NOTIFY";
			}
			break;

		case GDK_UNMAP : {
				result += "GDK_UNMAP";
			}
			break;

		case GDK_MAP : {
				result += "GDK_MAP";
			}
			break;

		case GDK_CONFIGURE : {
				result += "GDK_CONFIGURE";
			}
			break;

		case GDK_FOCUS_CHANGE : {
				result += "GDK_FOCUS_CHANGE";
			}
			break;

		case GDK_LEAVE_NOTIFY : {
				result += "GDK_LEAVE_NOTIFY";
			}
			break;

		case GDK_DRAG_MOTION : {
				result += "GDK_DRAG_MOTION";
			}
			break;

		case GDK_DRAG_LEAVE : {
				result += "GDK_DRAG_LEAVE";
			}
			break;

		case GDK_DRAG_ENTER : {
				result += "GDK_DRAG_ENTER";
			}
			break;

		case GDK_PROXIMITY_OUT : {
				result += "GDK_PROXIMITY_OUT";
			}
			break;

		case GDK_PROXIMITY_IN : {
				result += "GDK_PROXIMITY_IN";
			}
			break;

		case GDK_SELECTION_NOTIFY : {
				result += "GDK_SELECTION_NOTIFY";
			}
			break;

		case GDK_NO_EXPOSE : {
				result += "GDK_NO_EXPOSE";
			}
			break;

		case GDK_VISIBILITY_NOTIFY : {
				result += "GDK_VISIBILITY_NOTIFY";
			}
			break;

		case GDK_CLIENT_EVENT : {
				result += "GDK_CLIENT_EVENT";
			}
			break;

		case GDK_DROP_FINISHED : {
				result += "GDK_DROP_FINISHED";
			}
			break;

		case GDK_DROP_START : {
				result += "GDK_DROP_START";
			}
			break;

		case GDK_DRAG_STATUS : {
				result += "GDK_DRAG_STATUS";
			}
			break;

		case GDK_SETTING : {
				result += "GDK_SETTING";
			}
			break;

		case GDK_WINDOW_STATE : {
				result += "GDK_WINDOW_STATE";
			}
			break;

		case GDK_SCROLL : {
				result += "GDK_SCROLL";
			}
			break;
	}

	result += " count: " + StringUtils::toString( count );

	count ++;

	return result;
}


gboolean AbstractGTKControl::handleEvent( GdkEvent* gtkEvent )
{


	//StringUtils::traceWithArgs( "widget: %p, name: %s, event: %s\n",
	//								wndHandle_,
	//								wndHandle_->name,
	//								GTK_EventToString(gtkEvent).c_str() );



	gboolean result = FALSE;

	if ( gtkEvent->type == GDK_EXPOSE ) {
		GdkEventExpose * gdkExposeEvent = ( GdkEventExpose* ) gtkEvent;

		GraphicsContext* gc = control_->getContext();

		gc->getPeer() ->setContextID( wndHandle_->window );

		if ( GTK_WIDGET_NO_WINDOW( wndHandle_ ) ) {

			gc->setOrigin( bounds_.left_, bounds_.top_ );
		}

		control_->paint( gc );
		repainted_ = false;

		return FALSE;
	} else if ( gtkEvent->type == GDK_CONFIGURE ) {
		//handle this explicitly here

		int i = 0;
		i++;

		GdkEventConfigure* configEv = ( GdkEventConfigure* ) gtkEvent;

		VCF::Point pt( configEv->x, configEv->y );

		VCF::ControlEvent posEvent( control_, pt );

		VCF::Size sz( configEv->width, configEv->height );

		VCF::ControlEvent szEvent( control_, sz );


		control_->handleEvent( &posEvent );

		control_->handleEvent( &szEvent );



	} else {
		GTKEventMsg eventMsg( gtkEvent, this->control_ );


		Event* event = UIToolkit::createEventFromNativeOSEventData( ( void* ) & eventMsg );

		if ( NULL != event ) {
			control_->handleEvent( event );
			event->free();
			//result = TRUE;
		}
	}

	return result;
}

AbstractGTKControl* AbstractGTKControl::getGTKControlFromWidget( GtkWidget* wndHandle )
{
	AbstractGTKControl * result = NULL;

	AbstractGTKControl::GTKControlMap::iterator found = AbstractGTKControl::gtkControlMap.find( wndHandle );
	if ( found != AbstractGTKControl::gtkControlMap.end() ) {
		result = found->second;
	}

	return result;
}

void AbstractGTKControl_onCreateEvent( ComponentEvent* e )
{
	if ( NULL != e ) {
		Control * control = ( Control* ) e->getSource();

		GtkWidget* widget = ( GtkWidget* ) control->getPeer() ->getHandleID();
		gtk_widget_set_name( widget, control->getClassName().ansi_c_str() );

		control->handleEvent( e );
	}
}

void AbstractGTKControl::registerGTKControl( AbstractGTKControl* gtkControl )
{
	if ( NULL == gtkControl->wndHandle_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "Attemtping to register an invalid GtkWidget handle" ) );
	}


	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) UIToolkit::internal_getDefaultUIToolkit();

	AbstractGTKControl::gtkControlMap[ gtkControl->wndHandle_ ] = gtkControl;
	gtkControl->initGdkEventHandlers();

	toolkit->postEvent( new StaticEventHandlerInstance<ComponentEvent>( &AbstractGTKControl_onCreateEvent, gtkControl, "AbstractGTKControl_onCreateEvent" ),
	                    new VCF::ComponentEvent( gtkControl->getControl() , Component::COMPONENT_CREATED ),
	                    true );
}

void AbstractGTKControl::unRegisterGTKControl( AbstractGTKControl* gtkControl )
{
	AbstractGTKControl::GTKControlMap::iterator found = AbstractGTKControl::gtkControlMap.find( gtkControl->wndHandle_ );
	if ( found != AbstractGTKControl::gtkControlMap.end() ) {
		AbstractGTKControl::gtkControlMap.erase( found );
	}
}

void AbstractGTKControl::translateToScreenCoords( Point* pt )
{
	//gtk_widget_translate_coordinates


}


void AbstractGTKControl::translateFromScreenCoords( Point* pt )
{
}

void AbstractGTKControl::initGdkEventHandlers()
{
	gtk_widget_add_events( wndHandle_, GDK_ALL_EVENTS_MASK );

	g_signal_connect ( G_OBJECT ( wndHandle_ ), "event",
	                   G_CALLBACK ( AbstractGTKControl::onGdkEvent ),
	                   ( gpointer ) this );
}

gboolean AbstractGTKControl::onGdkEvent( GtkWidget *widget, GdkEvent *event, gpointer user_data )
{
	AbstractGTKControl * thisPtr = AbstractGTKControl::getGTKControlFromWidget( widget );

	if ( NULL == thisPtr ) {
		return FALSE;
	}

	//AbstractGTKControl* thisPtr = (AbstractGTKControl*)user_data;
	if ( widget != thisPtr->wndHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "Gdk event received for a widget that doesn't match the AbstractGTKControl's widget" ) );
	}

	return thisPtr->handleEvent( event );
}













GType AbstractGTKControl::getGTKType ()
{
	static GType container_type = 0;

	if ( !container_type ) {
		static const GTypeInfo container_info = {
		                                            sizeof ( AbstractGTKControl::ContainerClass ),
		                                            NULL,
		                                            NULL,
		                                            ( GClassInitFunc ) AbstractGTKControl::ContainerClass::init,
		                                            NULL,
		                                            NULL,
		                                            sizeof ( AbstractGTKControl::Container ),
		                                            0,
		                                            ( GInstanceInitFunc ) AbstractGTKControl::Container::init,
		                                        };

		container_type = g_type_register_static ( GTK_TYPE_CONTAINER, "AbstractGTKControl_Container", &container_info, ( GTypeFlags ) 0 );
	}

	return container_type;
}


void AbstractGTKControl::Container::move( GtkWidget* widget,
                                          int x,
                                          int y,
                                          int width,
                                          int height )
{
	/*
	container->x = x;
	container->y = y;
	container->width = width;
	container->height = height;
	*/

	Rect bounds( x, y, x + width, y + height );

	AbstractGTKControl* peer = AbstractGTKControl::Container::getControlPeer( widget );
	if ( NULL == peer ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "no AbstractGTKControl instance associated with this widget!" ) );
	}
	peer->internal_setBounds( bounds );

	if ( !GTK_IS_VCF_CONTAINER ( widget ) ) {
		widget->allocation.x = int( bounds.left_ );
		widget->allocation.y = int( bounds.top_ );
		widget->allocation.width = int( bounds.getWidth() );
		widget->allocation.height = int( bounds.getHeight() );
	}

	if ( GTK_WIDGET_REALIZED ( widget ) ) {
		GtkWidget * gdkParent = gtk_widget_get_parent ( widget );
		gtk_widget_queue_resize( gdkParent );
	}
}


GtkWidget* AbstractGTKControl::Container::create( GtkAdjustment *adjustment, AbstractGTKControl* gtkControlPeer )
{
	AbstractGTKControl::Container * container;

	container = ( AbstractGTKControl::Container* ) g_object_new ( AbstractGTKControl::getGTKType (), NULL );

	if ( !adjustment )
		adjustment = ( GtkAdjustment* ) gtk_adjustment_new ( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );

	AbstractGTKControl::Container::setAdjustment( container, adjustment );

	container->gtkControlPeer_ = gtkControlPeer;

	return GTK_WIDGET ( container );
}

/*
GtkAdjustment* AbstractGTKControl::Container::getAdjustment( AbstractGTKControl::Container *container )
{
 
}
*/

void AbstractGTKControl::Container::setUpdatePolicy( AbstractGTKControl::Container *container,
                                                     GtkUpdateType policy )
{
}

void AbstractGTKControl::Container::setAdjustment( AbstractGTKControl::Container *container,
                                                   GtkAdjustment *adjustment )
{
	g_return_if_fail ( container != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( container ) );

	if ( container->adjustment ) {
		g_signal_handlers_disconnect_by_func ( GTK_OBJECT ( container->adjustment ),
		                                       NULL,
		                                       ( gpointer ) container );

		g_object_unref ( GTK_OBJECT ( container->adjustment ) );
	}

	container->adjustment = adjustment;
	g_object_ref ( GTK_OBJECT ( container->adjustment ) );

	g_signal_connect ( GTK_OBJECT ( adjustment ), "changed",
	                   GTK_SIGNAL_FUNC ( AbstractGTKControl::Container::adjustmentChanged ),
	                   ( gpointer ) container );
	g_signal_connect ( GTK_OBJECT ( adjustment ), "value_changed",
	                   GTK_SIGNAL_FUNC ( AbstractGTKControl::Container::adjustmentValueChanged ),
	                   ( gpointer ) container );
}

void AbstractGTKControl::Container::init( AbstractGTKControl::Container *container )
{
	container->gtkControlPeer_ = NULL;
}


void AbstractGTKControl::Container::destroy ( GtkObject *object )
{
	AbstractGTKControl::Container * container;

	g_return_if_fail ( object != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( object ) );



	container = GTK_VCF_CONTAINER ( object );

	if ( container->adjustment ) {
		g_object_unref ( GTK_OBJECT ( container->adjustment ) );
		container->adjustment = NULL;
	}

	if ( GTK_OBJECT_CLASS ( internalVCFParentClass ) ->destroy ) {
		( * GTK_OBJECT_CLASS ( internalVCFParentClass ) ->destroy ) ( object );
	}
}

Rect AbstractGTKControl::Container::getBounds( GtkWidget* widget )
{
	Rect result;

	if ( GTK_IS_VCF_CONTAINER ( widget ) ) {
		AbstractGTKControl::Container * container = GTK_VCF_CONTAINER ( widget );
		result = container->gtkControlPeer_->internal_getBounds();
	} else {
		AbstractGTKControl* control = AbstractGTKControl::getGTKControlFromWidget( widget );
		if ( NULL == control ) {
			throw RuntimeException( MAKE_ERROR_MSG_2( "AbstractGTKControl::getGTKControlFromWidget() returned NULL - no control associated with this GTK widget!" ) );
		}
		result = control->internal_getBounds();
	}

	return result;
}

void AbstractGTKControl::Container::moveChild( AbstractGTKControl::Container *container,
                                               GtkWidget* child,
                                               int x,
                                               int y,
                                               int width,
                                               int height )
{
	g_return_if_fail ( container != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( container ) );
	g_return_if_fail ( child != NULL );

	printf( "AbstractGTKControl::Container::moveChild called\n" );


	GList *children = container->children;
	ContainerChild* childObj = NULL;
	while ( children ) {
		childObj = ( ContainerChild* ) children->data;

		if ( childObj->widget == child ) {
			childObj->x = x;
			childObj->y = y;
			childObj->width = width;
			childObj->height = height;

			Rect bounds( x, y, x + width, y + height );

			AbstractGTKControl* peer = AbstractGTKControl::Container::getControlPeer( child );
			if ( NULL == peer ) {
				//throw RuntimeException( MAKE_ERROR_MSG_2("no AbstractGTKControl instance associated with this widget!") );
			}

			if ( NULL != peer ) {
				peer->internal_setBounds( bounds );
			}

			gtk_widget_queue_resize ( GTK_WIDGET ( child ) );

			break;
		}

		children = children->next;
	}
}

Rect AbstractGTKControl::Container::getChildBounds( AbstractGTKControl::Container *container, GtkWidget* child )
{
	Rect result;

	GList *children = container->children;
	ContainerChild* childObj = NULL;
	while ( children ) {
		childObj = ( ContainerChild* ) children->data;

		if ( childObj->widget == child ) {
			result.left_ = childObj->x;
			result.top_ = childObj->y;
			result.right_ = result.left_ + childObj->width;
			result.bottom_ = result.top_ + childObj->height;

			break;
		}

		children = children->next;
	}

	return result;
}

AbstractGTKControl* AbstractGTKControl::Container::getControlPeer( GtkWidget* widget )
{
	AbstractGTKControl * result = NULL;

	if ( GTK_IS_VCF_CONTAINER ( widget ) ) {
		AbstractGTKControl::Container * container = GTK_VCF_CONTAINER ( widget );
		result = container->gtkControlPeer_;
	} else {
		result = AbstractGTKControl::getGTKControlFromWidget( widget );
	}

	return result;
}

void AbstractGTKControl::Container::realize( GtkWidget *widget )
{
	AbstractGTKControl::Container * container;
	//printf( "gtk_absolute_container_realize\n" );

	GdkWindowAttr attributes;
	gint attributes_mask;

	g_return_if_fail ( widget != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( widget ) );

	GTK_WIDGET_SET_FLAGS ( widget, GTK_REALIZED );
	container = GTK_VCF_CONTAINER ( widget );

	attributes.x = widget->allocation.x;
	attributes.y = widget->allocation.y;
	attributes.width = widget->allocation.width;
	attributes.height = widget->allocation.height;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.event_mask = gtk_widget_get_events ( widget ) |
	                        GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK |
	                        GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK |
	                        GDK_POINTER_MOTION_HINT_MASK;
	attributes.visual = gtk_widget_get_visual ( widget );
	attributes.colormap = gtk_widget_get_colormap ( widget );

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
	widget->window = gdk_window_new ( widget->parent->window, &attributes, attributes_mask );

	widget->style = gtk_style_attach ( widget->style, widget->window );

	gdk_window_set_user_data ( widget->window, widget );

	gtk_style_set_background ( widget->style, widget->window, GTK_STATE_ACTIVE );
}

void AbstractGTKControl::Container::sizeRequest( GtkWidget *widget, GtkRequisition *requisition )
{
	//printf( "gtk_absolute_container_size_request\n" );
	g_return_if_fail ( widget != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( widget ) );
	g_return_if_fail ( requisition != NULL );

	StringUtils::traceWithArgs( "Container::sizeRequest widget: %p, name:%s\n", widget, widget->name );


	Rect bounds = AbstractGTKControl::Container::getBounds( widget );

	requisition->width = int( bounds.getWidth() );
	requisition->height = int( bounds.getHeight() );


	AbstractGTKControl::Container *container = GTK_VCF_CONTAINER ( widget );

	GList* children = container->children;
	AbstractGTKControl::ContainerChild* child = NULL;
	GtkRequisition child_requisition;
	while ( children ) {
		child = ( AbstractGTKControl::ContainerChild* ) children->data;
		children = children->next;

		if ( GTK_WIDGET_VISIBLE ( child->widget ) ) {
			//StringUtils::traceWithArgs( "\tcalling gtk_widget_size_request for widget: %p, name:%s, parent: %p\n",
			//							child->widget, child->widget->name, widget );
			gtk_widget_size_request ( child->widget, &child_requisition );
			/*
						if ( child->widget->name == String("VCF::CommandButton") ) {
							int i = 0;
						}
						*/
		}
	}

}

void AbstractGTKControl::Container::sizeAllocate( GtkWidget *widget, GtkAllocation *allocation )
{
	g_return_if_fail ( widget != NULL );

	//g_return_if_fail (GTK_IS_VCF_CONTAINER (widget));

	g_return_if_fail ( allocation != NULL );

	StringUtils::traceWithArgs( "Container::sizeAllocate widget: %p, name:%s\n", widget, widget->name );

	AbstractGTKControl::Container *container;


	//printf( "gtk_absolute_container_size_allocate: %p\n", container );


	Rect bounds = AbstractGTKControl::Container::getBounds( widget );

	allocation->x = int( bounds.left_ ) ;
	allocation->y = int( bounds.top_ );
	allocation->width = int( bounds.getWidth() );
	allocation->height = int( bounds.getHeight() );



	widget->allocation = *allocation;


	if ( GTK_WIDGET_REALIZED ( widget ) ) {

		gdk_window_move_resize ( widget->window,
		                         allocation->x, allocation->y,
		                         allocation->width, allocation->height );

	}

	if ( GTK_IS_VCF_CONTAINER ( widget ) ) {
		container = GTK_VCF_CONTAINER ( widget );
		GList* children = container->children;
		AbstractGTKControl::ContainerChild* child = NULL;
		GtkRequisition child_requisition;
		GtkAllocation child_allocation;
		while ( children ) {
			child = ( AbstractGTKControl::ContainerChild* ) children->data;
			children = children->next;

			if ( GTK_WIDGET_VISIBLE ( widget ) ) {
				bounds = AbstractGTKControl::Container::getBounds( child->widget );
				//StringUtils::traceWithArgs( "\tcalling gtk_widget_get_child_requisition for widget: %p, name:%s, parent: %p\n",
				//						child->widget, child->widget->name, widget );

				gtk_widget_get_child_requisition ( child->widget, &child_requisition );
				child_allocation.x = int( bounds.left_ ); //child->x;
				child_allocation.y = int( bounds.top_ ); //child->y;

				if ( GTK_WIDGET_NO_WINDOW ( widget ) ) {
					child_allocation.x += widget->allocation.x;
					child_allocation.y += widget->allocation.y;
				}

				child_allocation.width = int( bounds.getWidth() ); //child->width;// child_requisition.width;
				child_allocation.height = int( bounds.getHeight() ); // child->height;//child_requisition.height;


				StringUtils::traceWithArgs( "\tcalling gtk_widget_size_allocate for widget: %p, name:%s, parent: %p\n\t\tx:%d, y:%d, w:%d, h:%d\n",
				                            child->widget, child->widget->name, widget,
				                            child->x,
				                            child->y,
				                            child->width,
				                            child->height );
				gtk_widget_size_allocate ( child->widget, &child_allocation );

				/*
								if ( child->widget->name == String("VCF::CommandButton") ) {
									int i = 0;
								}
								*/
			}
		}
	}
}

gboolean AbstractGTKControl::Container::expose( GtkWidget *widget, GdkEventExpose *event )
{
	g_return_val_if_fail ( GTK_IS_VCF_CONTAINER ( widget ), FALSE );
	g_return_val_if_fail ( event != NULL, FALSE );


	if ( GTK_WIDGET_DRAWABLE ( widget ) ) {


		//StringUtils::traceWithArgs( "AbstractGTKControl::Container::expose, widget: %p, name: %s\n",
		//								widget, widget->name );



		AbstractGTKControl::Container * absContainer = GTK_VCF_CONTAINER ( widget );




		GList *children = absContainer->children;
		AbstractGTKControl::ContainerChild* childObj = NULL;
		while ( children ) {
			childObj = ( AbstractGTKControl::ContainerChild* ) children->data;

			if ( GTK_IS_WIDGET ( childObj->widget ) ) {
				g_assert ( childObj->widget->parent == widget );
				if ( GTK_WIDGET_DRAWABLE ( childObj->widget ) &&
				        GTK_WIDGET_NO_WINDOW ( childObj->widget ) &&
				        ( childObj->widget->window == event->window ) ) {


					GdkEvent * child_event;
					child_event = gdk_event_new ( GDK_EXPOSE );
					child_event->expose = *event;
					g_object_ref ( child_event->expose.window );

					child_event->expose.region =
					    gtk_widget_region_intersect ( childObj->widget, event->region );

					if ( !gdk_region_empty ( child_event->expose.region ) ) {
						gdk_region_get_clipbox ( child_event->expose.region, &child_event->expose.area );


						//StringUtils::traceWithArgs( "gtk_widget_send_expose( %p - %s )\n",
						//								childObj->widget, childObj->widget->name );



						gtk_widget_send_expose ( childObj->widget, child_event );

					}

					gdk_event_free ( child_event );
				}
			}

			children = children->next;
		}
	}

	return FALSE;
}

void AbstractGTKControl::Container::adjustmentChanged( GtkAdjustment *adjustment, gpointer data )
{
}

void AbstractGTKControl::Container::adjustmentValueChanged( GtkAdjustment *adjustment, gpointer data )
{
}

void AbstractGTKControl::Container::add
	( GtkContainer* container, GtkWidget* widget )
{
	//printf( "gtk_absolute_container_add\n" );

	g_return_if_fail ( container != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( container ) );
	g_return_if_fail ( widget != NULL );

	//StringUtils::traceWithArgs( "Container::add container: %p, widget: %p, name:%s\n",
	//							container, widget, widget->name );


	AbstractGTKControl::Container *absContainer;
	absContainer = GTK_VCF_CONTAINER ( container );

	AbstractGTKControl::ContainerChild* newChild = g_new( AbstractGTKControl::ContainerChild, 1 );

	newChild->widget = widget;
	newChild->height = 1;
	newChild->width = 1;
	newChild->x = 0;
	newChild->y = 0;

	GtkRequisition child_requisition;

	gtk_widget_size_request ( newChild->widget, &child_requisition );

	absContainer->children = g_list_append( absContainer->children, newChild );

	gtk_widget_set_parent ( widget, GTK_WIDGET ( container ) );
}

void AbstractGTKControl::Container::remove
	( GtkContainer* container, GtkWidget* widget )
{
	//printf( "gtk_absolute_container_remove\n" );

	g_return_if_fail ( container != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( container ) );
	g_return_if_fail ( widget != NULL );

	AbstractGTKControl::Container *absContainer;
	absContainer = GTK_VCF_CONTAINER ( container );

	GList *children = absContainer->children;
	AbstractGTKControl::ContainerChild* child = NULL;
	while ( children ) {
		child = ( AbstractGTKControl::ContainerChild* ) children->data;

		if ( child->widget == widget ) {
			gboolean was_visible = GTK_WIDGET_VISIBLE ( widget );

			gtk_widget_unparent ( widget );

			absContainer->children = g_list_remove_link ( absContainer->children, children );
			g_list_free ( children );
			//g_free (child);

			if ( was_visible && GTK_WIDGET_VISIBLE ( container ) ) {
				gtk_widget_queue_resize ( GTK_WIDGET ( container ) );
			}
			break;
		}

		children = children->next;
	}
}

void AbstractGTKControl::Container::forall( GtkContainer* container,
                                            gboolean include_internals,
                                            GtkCallback callback,
                                            gpointer callback_data )
{
	//printf( "gtk_absolute_container_forall\n" );
	g_return_if_fail ( container != NULL );
	g_return_if_fail ( GTK_IS_VCF_CONTAINER ( container ) );
	g_return_if_fail ( callback != NULL );

	AbstractGTKControl::Container *absContainer;
	absContainer = GTK_VCF_CONTAINER ( container );

	GList *children = absContainer->children;
	AbstractGTKControl::ContainerChild* child = NULL;
	while ( children ) {
		child = ( AbstractGTKControl::ContainerChild* ) children->data;
		children = children->next;

		( * callback ) ( child->widget, callback_data );
	}
}

GType AbstractGTKControl::Container::getChildType( GtkContainer* container )
{
	return GTK_TYPE_WIDGET;
}




void AbstractGTKControl::ContainerClass::init ( ContainerClass *clazz )
{
	GtkWidgetClass * widget_class;
	GtkContainerClass *container_class;

	GtkObjectClass *object_class;
	object_class = ( GtkObjectClass* ) clazz;
	widget_class = ( GtkWidgetClass* ) clazz;
	container_class = ( GtkContainerClass* ) clazz;

	internalVCFParentClass = ( GtkContainerClass* ) gtk_type_class ( gtk_container_get_type () );

	object_class->destroy = AbstractGTKControl::Container::destroy;

	widget_class->realize = AbstractGTKControl::Container::realize;
	widget_class->expose_event = AbstractGTKControl::Container::expose;
	widget_class->size_request = AbstractGTKControl::Container::sizeRequest;
	widget_class->size_allocate = AbstractGTKControl::Container::sizeAllocate;


	container_class->add
	= AbstractGTKControl::Container::add
		  ;
	container_class->remove
	= AbstractGTKControl::Container::remove
		  ;
	container_class->forall = AbstractGTKControl::Container::forall;
	container_class->child_type = AbstractGTKControl::Container::getChildType;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:25  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.8  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.4.2.3  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.4.2.2  2004/02/16 05:34:04  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.4.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.4  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.2.2  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.3.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.3  2003/08/09 02:56:45  ddiego
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
*Revision 1.2.2.6  2003/07/14 22:52:53  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.2.2.5  2003/07/13 03:45:11  ddiego
*Added further fixes for the GTK port. Now have the event handling working
*correctly, and fixed an issue with too many repaint messages being sent
*which caused 100% CPU utilization.
*
*Revision 1.2.2.4  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*Revision 1.2.2.3  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.2.2.2  2003/06/01 16:43:59  ddiego
*further GTK support added
*
*Revision 1.2.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.2  2003/05/17 20:37:26  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.4  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.1.2.3  2003/04/23 03:42:54  ddiego
*further gtk dev got basic eventing code in place
*
*Revision 1.1.2.2  2003/04/19 03:31:15  ddiego
*basic code in place for gtk port for ApplicationKit - needs to be tested in
*linux
*
*Revision 1.1.2.1  2003/04/17 04:29:50  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


