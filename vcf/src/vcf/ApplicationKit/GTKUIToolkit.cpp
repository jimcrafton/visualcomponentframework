//GTKUIToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/ApplicationKit/GTKUIToolkit.h"
#include "vcf/ApplicationKit/GTKDesktop.h"
#include "vcf/ApplicationKit/GTKApplication.h"
#include "vcf/ApplicationKit/GTKControlContext.h"
#include "vcf/ApplicationKit/GTKControl.h"
#include "vcf/ApplicationKit/GTKCursor.h"


#include "vcf/ApplicationKit/GTKWindow.h"


#include "vcf/ApplicationKit/LightweightComponent.h"

#include <gdk/gdkkeysyms.h>

#include "vcf/ApplicationKit/GTKDialog.h"
#include "vcf/ApplicationKit/GTKCommandButton.h"
#include "vcf/ApplicationKit/GTKTextControl.h"
#include "vcf/ApplicationKit/GTKFileOpenDialog.h"
#include "vcf/ApplicationKit/GTKToolbar.h"
#include "vcf/ApplicationKit/Toolbar.h"

//get rid of the stupip fscking warning from GCC
#define NULL 0


#define VCF_GTK_POST_EVENT			"VCF_GTK_POST_EVENT"



using namespace VCF;


//UIMetricsManager implementation for GTK
class GTKUIMetricsManager : public UIMetricsManager
{
public:
	GTKUIMetricsManager()
	{}

	virtual ~GTKUIMetricsManager()
	{}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type )
	{
		VCF::Font result( "ARIAL", 10 );

		result.setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_CAPTION_TEXT ) );
		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {}
				break;

			case UIMetricsManager::ftSelectedMenuItemFont : {}
				break;

			case UIMetricsManager::ftControlFont :
		case UIMetricsManager::ftSystemFont : {}
				break;

			case UIMetricsManager::ftMessageFont : {}
				break;

			case UIMetricsManager::ftToolTipFont : {}
				break;
		}

		return result;
	}

	virtual double getDefaultHeightFor( const UIMetricsManager::HeightType& type )
	{
		double result = 0.0;
		switch ( type ) {
			case UIMetricsManager::htLabelHeight : {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					result = f.getHeight() * 1.75;
				}
				break;

			case UIMetricsManager::htComboBoxHeight : {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					result = f.getHeight() * 2.0;
				}
				break;

			case UIMetricsManager::htListItemHeight : {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					result = f.getHeight() * 1.65;
				}
				break;

			case UIMetricsManager::htButtonHeight : {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					result = ( f.getHeight() * 1.75 ) + 2.50;
				}
				break;

			case UIMetricsManager::htRadioBoxHeight :
			case UIMetricsManager::htCheckBoxHeight : {
					//in Win32 a radio box or check box is ALWAYS 10 dialog units high
					//dialog units are converted by
					//(2 * average char height dialog font / average char height system font pixels
					//where average char height dialog font = TEXTMETRIC.tmHeight field or a Font::getHeight()


					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					result = ( 9.0 * ( ( 2.0 * f.getHeight() ) / f.getHeight() ) ) - 4.0; //0.590909;
				}
				break;

			case UIMetricsManager::htToolTipHeight : {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftToolTipFont );
					result = f.getHeight() * 1.2222;
				}
				break;

			case UIMetricsManager::htSeparatorHeight : {
					result = 2.0;
				}
				break;

			case UIMetricsManager::htInformationalControl : {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					result = f.getHeight() * 1.75;
				}
				break;
		}
		return result;

	}

	virtual double getPreferredSpacingFor( const UIMetricsManager::SpacingType& type )
	{
		double result = 0.0;

		//values largely derived from the Apple HIG at
		//http://developer.apple.com/techpubs/macosx/Essentials/AquaHIGuidelines/AHIGLayout/index.html
		switch ( type ) {
			case UIMetricsManager::stWindowBorderDelta : {
					result = 20.0;
				}
				break;

			case UIMetricsManager::stContainerBorderDelta : {
					result = 8.0;
				}
				break;

			case UIMetricsManager::stControlVerticalSpacing : {
					result = 14.0;
				}
				break;

			case UIMetricsManager::stControlHorizontalSpacing : {
					result = 10.0;
				}
				break;

			case UIMetricsManager::stInformationControlTopSpacer : {
					result = 2.0;
				}
				break;

			case UIMetricsManager::stInformationControlBottomSpacer : {
					result = 8.0;
				}
				break;
		}

		return result;
	}

	virtual Size getDefaultSliderThumbDimensions()
	{
		Size result;

		//where the hell do we get these ????
		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )
	{
		Size result;


		return result;
	}

	virtual Size getDefaultVerticalScrollButtonDimensions()
	{
		Size result;

		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultHorizontalScrollButtonDimensions()
	{
		Size result;

		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultTabDimensions( const String& caption )
	{
		Size result;

		return result;
	}
};










GTKUIToolkit::GTKUIToolkit() :
		defaultParent_( NULL )
{
	//this will work, but it means ignoring certain arguments that might be important for
	//gtk initialization - need to figure out a better way
	gdk_parse_args ( NULL, NULL );

	if ( !gdk_display_open_default_libgtk_only () ) {
		StringUtils::trace( "gdk_display_open_default_libgtk_only () failed!\n" );
		//throw exception????
	}


	metricsMgr_ = new GTKUIMetricsManager();
	createDefaultParentWnd();


	gdk_atom_intern( VCF_GTK_POST_EVENT, FALSE );
}

GTKUIToolkit::~GTKUIToolkit()
{}

ApplicationPeer* GTKUIToolkit::internal_createApplicationPeer()
{
	return new GTKApplication();
}

TextPeer* GTKUIToolkit::internal_createTextPeer( TextControl* component,
                                                 const bool& isMultiLineControl )
{
	return new GTKTextControl( component, isMultiLineControl );
}

TextPeer* GTKUIToolkit::internal_createTextPeer( TextControl* component,
                                                 const bool& isMultiLineControl,
                                                 ComponentType componentType )
{
	return new GTKTextControl( component, isMultiLineControl );
}


TreePeer* GTKUIToolkit::internal_createTreePeer( TreeControl* componentb )
{
	return 0;
}

ListviewPeer* GTKUIToolkit::internal_createListViewPeer( ListViewControl* component )
{
	return 0;
}

CommonPrintDialogPeer* GTKUIToolkit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return 0;
}

DialogPeer* GTKUIToolkit::internal_createDialogPeer( Control* owner, Dialog* component )
{
	return new GTKDialog( owner, component );
}

DialogPeer* GTKUIToolkit::internal_createDialogPeer()
{
	return new GTKDialog();
}

ControlPeer* GTKUIToolkit::internal_createControlPeer( Control* component, ComponentType componentType )
{
	ControlPeer * result = NULL;

	switch ( componentType ) {
		case CT_LIGHTWEIGHT: {
				result = new LightweightComponent( component );
			}
			break;

		case CT_DEFAULT:
		case CT_HEAVYWEIGHT: {
				result = new GTKControl( component );
			}
			break;
	}
	return result;
}

WindowPeer* GTKUIToolkit::internal_createWindowPeer( Control* component,
                                                     Control* owner )
{
	return new GTKWindow( component, owner );
}

ToolbarPeer* GTKUIToolkit::internal_createToolbarPeer( Toolbar* toolbar )
{
	return new GTKToolbar( toolbar );
}

MenuItemPeer* GTKUIToolkit::internal_createMenuItemPeer( MenuItem* item )
{
	return NULL;
}

MenuBarPeer* GTKUIToolkit::internal_createMenuBarPeer( MenuBar* menuBar )
{
	return NULL;
}

PopupMenuPeer* GTKUIToolkit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
	return NULL;
}

ButtonPeer* GTKUIToolkit::internal_createButtonPeer( CommandButton* component )
{
	return new GTKCommandButton( component );
}

HTMLBrowserPeer* GTKUIToolkit::internal_createHTMLBrowserPeer( Control* control )
{
	return NULL;
}

ContextPeer* GTKUIToolkit::internal_createContextPeer( Control* component )
{
	return new GTKControlContext( component->getPeer() );
}

CommonFileDialogPeer* GTKUIToolkit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
	return new GTKFileOpenDialog( owner );
}

CommonFileDialogPeer* GTKUIToolkit::internal_createCommonFileSaveDialogPeer( Control* owner )
{
	return NULL;
}

CommonColorDialogPeer* GTKUIToolkit::internal_createCommonColorDialogPeer( Control* owner )
{
	return NULL;
}

CommonFolderBrowseDialogPeer* GTKUIToolkit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
	return NULL;
}

CommonFontDialogPeer* GTKUIToolkit::internal_createCommonFontDialogPeer( Control* owner )
{
	return NULL;
}

DragDropPeer* GTKUIToolkit::internal_createDragDropPeer()
{
	return NULL;
}

DataObjectPeer* GTKUIToolkit::internal_createDataObjectPeer()
{
	return NULL;
}

DropTargetPeer* GTKUIToolkit::internal_createDropTargetPeer()
{
	return NULL;
}

DesktopPeer* GTKUIToolkit::internal_createDesktopPeer( Desktop* desktop )
{
	return new GTKDesktop( desktop );
}

ScrollPeer* GTKUIToolkit::internal_createScrollPeer( Control* control )
{
	return NULL;
}

CursorPeer* GTKUIToolkit::internal_createCursorPeer( Cursor* cursor )
{
	return new GTKCursor( cursor );
}

ClipboardPeer* GTKUIToolkit::internal_createClipboardPeer()
{
	return NULL;
}

bool GTKUIToolkit::internal_createCaret( Control* owningControl, Image* caretImage )
{
	bool result = false;

	return result;
}

bool GTKUIToolkit::internal_destroyCaret( Control* owningControl )
{
	bool result = false;

	return result;
}

void GTKUIToolkit::internal_setCaretVisible( const bool& caretVisible )
{}

void GTKUIToolkit::internal_setCaretPos( Point* point )
{}

void GTKUIToolkit::internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	GdkEventClient clientEvent;
	memset( &clientEvent, 0, sizeof( clientEvent ) );

	clientEvent.type = GDK_CLIENT_EVENT;
	clientEvent.message_type = gdk_atom_intern( VCF_GTK_POST_EVENT, FALSE );
	clientEvent.data.l[ 0 ] = ( unsigned long ) eventHandler;
	clientEvent.data.l[ 1 ] = ( unsigned long ) event->clone();
	clientEvent.data.l[ 2 ] = deleteHandler ? TRUE : FALSE;

	gdk_event_put( ( GdkEvent* ) & clientEvent );
}

void GTKUIToolkit::internal_registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds )
{


	std::map<EventHandler*, TimeOutHandler>::iterator found = timeoutHandlers_.find( handler );
	if ( found != timeoutHandlers_.end() ) {
		TimeOutHandler & tmHandler = found->second;
		gtk_timeout_remove ( tmHandler.timerID_ );
		timeoutHandlers_.erase( found );
	}


	TimeOutHandler tmHandler;
	tmHandler.source_ = source;
	tmHandler.handler_ = handler;
	tmHandler.timerID_ = gtk_timeout_add( timeoutInMilliSeconds,
	                                      GTKUIToolkit::gtkTimeOutHandler,
	                                      ( gpointer ) handler );

	timeoutHandlers_[ handler ] = tmHandler;

}

void GTKUIToolkit::internal_unregisterTimerHandler( EventHandler* handler )
{
	std::map<EventHandler*, TimeOutHandler>::iterator found = timeoutHandlers_.find( handler );
	if ( found != timeoutHandlers_.end() ) {
		TimeOutHandler & tmHandler = found->second;
		gtk_timeout_remove ( tmHandler.timerID_ );

		timeoutHandlers_.erase( found );
	}
}

gboolean GTKUIToolkit::gtkTimeOutHandler( gpointer data )
{
	EventHandler * handler = ( EventHandler* ) data;

	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) UIToolkit::internal_getDefaultUIToolkit();

	std::map<EventHandler*, TimeOutHandler>::iterator found = toolkit->timeoutHandlers_.find( handler );
	if ( found != toolkit->timeoutHandlers_.end() ) {
		TimeOutHandler & tmHandler = found->second;


		TimerEvent event( tmHandler.source_, TIMER_EVENT_PULSE );
		tmHandler.handler_->invoke( &event );
	}

	return TRUE;
}

void GTKUIToolkit::internal_gdkEventHandler( GdkEvent *gdkEvent, gpointer data )
{
	Application * runningApp = Application::getRunningInstance();
	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) data;


	if ( toolkit->handleGdkEvent( gdkEvent ) ) {
		gtk_main_do_event( gdkEvent );
	}
}

gboolean GTKUIToolkit::internal_gdkIdleHandler( gpointer data )
{
	/*
	This fucntion is currently causing hte app to run with 100% CPU utilization
	need to fix this...
	*/
	Application * runningApp = Application::getRunningInstance();
	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) data;

	if ( NULL != runningApp ) {
		runningApp->idleTime();
	}

	//check library apps;
	Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
	while ( true == registeredLibs->hasMoreElements() ) {

		LibraryApplication * libraryApp = registeredLibs->nextElement();
		libraryApp->idleTime();
	}

	return TRUE;
}


bool GTKUIToolkit::handleGdkEvent( GdkEvent* gdkEvent )
{
	bool result = true;
	AbstractGTKControl* gtkControl = NULL;
	if ( NULL != gdkEvent ) {

		switch ( gdkEvent->type ) {
			case GDK_CLIENT_EVENT : {

					GdkEventClient * clientEvent = ( GdkEventClient* ) gdkEvent;
					if ( gdk_atom_intern( VCF_GTK_POST_EVENT, FALSE ) == clientEvent->message_type ) {

						result = false;

						EventHandler* eventHandler = ( EventHandler* ) ( unsigned long ) clientEvent->data.l[ 0 ];
						Event* event = ( Event* ) ( unsigned long ) clientEvent->data.l[ 1 ];
						bool deleteHandler = ( clientEvent->data.l[ 2 ] == TRUE ) ? true : false;

						if ( NULL != eventHandler ) {
							eventHandler->invoke( event );
						}

						delete event;
						if ( deleteHandler ) {
							delete eventHandler;
						}
					}
				}
				break;

			case GDK_KEY_PRESS :
			case GDK_KEY_RELEASE : {
					GtkWidget* gtkWidget = gtk_get_event_widget( gdkEvent );
					gtkControl = AbstractGTKControl::getGTKControlFromWidget( gtkWidget );

					GdkEventKey* gdkKeyEvent = ( GdkEventKey* ) gdkEvent;

					StringUtils::trace( "GTKUIToolkit::handleGdkEvent() GDK_KEY_PRESS/GDK_KEY_RELEASE\n" );
					KeyboardMasks modifierKey = ( KeyboardMasks ) translateKeyMask( ( GdkModifierType ) gdkKeyEvent->state );
					VirtualKeyCode vkCode = translateKeyCode( gdkKeyEvent->keyval );

					if ( NULL != gtkControl ) {
						Control * control = gtkControl->getControl();
						Control* currentFocusedControl = Control::getCurrentFocusedControl();
						if ( NULL != currentFocusedControl ) {
							if ( ( control != currentFocusedControl ) && ( currentFocusedControl->isLightWeight() ) ) {
								control = currentFocusedControl;
							}
						}
						VCFChar keyChar = '0';
						if ( gdkKeyEvent->length > 0 ) {
							keyChar = gdkKeyEvent->string[ 0 ];
						}
						KeyboardEvent event( control, Control::KEYBOARD_ACCELERATOR, 1,
						                     modifierKey, keyChar, vkCode );

						StringUtils::traceWithArgs( "control: %p, keyChar: %c\n", control, keyChar );
						handleKeyboardEvent( &event );
						if ( event.isConsumed() ) {
							result = false;
						}
					}
				}
				break;
		}
	}
	/*
		if ( (result) && (NULL != gtkControl) ) {
			gtkControl->handleEvent( gdkEvent );
		}
	*/ 
	return result;
}

void GTKUIToolkit::internal_runEventLoop()
{
	StringUtils::trace( "starting GTKUIToolkit runEventLoop()...\n" );
	gtk_main ();
}


UIToolkit::ModalReturnType GTKUIToolkit::internal_runModalEventLoopFor( Control* control )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrFalse;
	printf( "starting GTKUIToolkit runModalEventLoopFor( %p )...\n", control );

	gtk_main ();

	return result;
}

void GTKUIToolkit::internal_quitCurrentEventLoop()
{
	gtk_main_quit ();
}

/**
*@param void* in this implementation, the eventData represents a
*pointer to an GTK XEvent structure.
*/
VCF::Event* GTKUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
	GTKEventMsg * eventMsg = ( GTKEventMsg* ) eventData;

	Event* event = NULL;

	switch ( eventMsg->gdkEvent_->type ) {
		case GDK_DELETE : {}
			break;

		case GDK_DESTROY : {
				event = new VCF::ComponentEvent( eventMsg->control_, Component::COMPONENT_DELETED );
			}
			break;

		case GDK_MOTION_NOTIFY	: {
				GdkEventMotion* gdkMotionEvent = ( GdkEventMotion* ) eventMsg->gdkEvent_;
				KeyboardMasks modifierKey = ( KeyboardMasks ) translateKeyMask( ( GdkModifierType ) gdkMotionEvent->state );
				translateButtonMask( ( GdkModifierType ) gdkMotionEvent->state );

				VCF::Point pt( gdkMotionEvent->x, gdkMotionEvent->y );
				event = new VCF::MouseEvent ( eventMsg->control_, Control::MOUSE_MOVE,
				                              translateButtonMask( ( GdkModifierType ) gdkMotionEvent->state ),
				                              translateKeyMask( ( GdkModifierType ) gdkMotionEvent->state ), &pt );

			}
			break;

		case GDK_BUTTON_PRESS :
		case GDK_2BUTTON_PRESS :
		case GDK_3BUTTON_PRESS : {
				StringUtils::traceWithArgs( "GDK_BUTTON_PRESS, %p\n", eventMsg->control_ );
				GdkEventButton* gdkBtnEvent = ( GdkEventButton* ) eventMsg->gdkEvent_;

				VCF::Point pt( gdkBtnEvent->x, gdkBtnEvent->y );
				event = new VCF::MouseEvent ( eventMsg->control_, Control::MOUSE_DOWN,
				                              translateButtonMask( ( GdkModifierType ) gdkBtnEvent->state ),
				                              translateKeyMask( ( GdkModifierType ) gdkBtnEvent->state ), &pt );
			}
			break;

		case GDK_BUTTON_RELEASE : {
				GdkEventButton* gdkBtnEvent = ( GdkEventButton* ) eventMsg->gdkEvent_;

				VCF::Point pt( gdkBtnEvent->x, gdkBtnEvent->y );

				ulong32 buttonMask = 0;
				if ( 1 == gdkBtnEvent->button ) {
					buttonMask |= VCF::mbmLeftButton;
				}

				if ( 2 == gdkBtnEvent->button ) {
					buttonMask |= VCF::mbmMiddleButton;
				}

				if ( 3 == gdkBtnEvent->button ) {
					buttonMask |= VCF::mbmRightButton;
				}

				event = new VCF::MouseEvent ( eventMsg->control_, Control::MOUSE_UP, buttonMask,
				                              translateKeyMask( ( GdkModifierType ) gdkBtnEvent->state ), &pt );
			}
			break;

		case GDK_KEY_PRESS :
		case GDK_KEY_RELEASE : {
				GdkEventKey* gdkKeyEvent = ( GdkEventKey* ) eventMsg->gdkEvent_;
				KeyboardMasks modifierKey = ( KeyboardMasks ) translateKeyMask( ( GdkModifierType ) gdkKeyEvent->state );
				VirtualKeyCode vkCode = translateKeyCode( gdkKeyEvent->keyval );
				VCFChar keyChar = '0';
				if ( gdkKeyEvent->length > 0 ) {
					keyChar = gdkKeyEvent->string[ 0 ];
				}

				event = new KeyboardEvent( eventMsg->control_,
				                           ( eventMsg->gdkEvent_->type == GDK_KEY_PRESS ) ?
				                           Control::KEYBOARD_DOWN : Control::KEYBOARD_UP,
				                           1, modifierKey, keyChar, vkCode );


			}
			break;

		case GDK_ENTER_NOTIFY :
		case GDK_LEAVE_NOTIFY : {
				GdkEventCrossing* gdkCrossingEvent = ( GdkEventCrossing * ) eventMsg->gdkEvent_;
				VCF::Point pt( gdkCrossingEvent->x, gdkCrossingEvent->y );
				ulong32 eventType = ( gdkCrossingEvent->type == GDK_ENTER_NOTIFY ) ? Control::MOUSE_ENTERED : Control::MOUSE_LEAVE;
				//the peer will fill out the button and key masks
				event = new VCF::MouseEvent ( eventMsg->control_, eventType,
				                              translateButtonMask( ( GdkModifierType ) gdkCrossingEvent->state ),
				                              translateKeyMask( ( GdkModifierType ) gdkCrossingEvent->state ), &pt );
			}
			break;

		case GDK_FOCUS_CHANGE : {
				GdkEventFocus* gdkFocusEvent = ( GdkEventFocus* ) eventMsg->gdkEvent_;
				event = new VCF::FocusEvent ( eventMsg->control_, gdkFocusEvent->in ? Control::FOCUS_GAINED : Control::FOCUS_LOST );
			}
			break;

		case GDK_CONFIGURE : {
				//we are going to return NULL here -
				//the problem is that there are two separate VCF event objects that
				//need to be created, so we are going to let the AbstractGTKControl deal
				//with this directly
			}
			break;

		case GDK_MAP : {}
			break;

		case GDK_UNMAP : {}
			break;

		case GDK_VISIBILITY_NOTIFY : {}
			break;


	}
	return event;
}

Size GTKUIToolkit::internal_getDragDropDelta()
{
	//this is completely arbitrary - need to read this from a file
	Size result( 4, 4 );

	return result;
}


void GTKUIToolkit::createDefaultParentWnd()
{
	defaultParent_ = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_widget_realize ( defaultParent_ );
}



VirtualKeyCode GTKUIToolkit::translateKeyCode( guint code )
{
	VirtualKeyCode result;


	//please note: all codes from gdk/gdkkeysym.h

	switch ( code ) {

		case GDK_F1 : {
				result = VCF::vkF1;
			}
			break;

		case GDK_F2 : {
				result = VCF::vkF2;
			}
			break;

		case GDK_F3 : {
				result = VCF::vkF3;
			}
			break;

		case GDK_F4 : {
				result = VCF::vkF4;
			}
			break;

		case GDK_F5 : {
				result = VCF::vkF5;
			}
			break;

		case GDK_F6 : {
				result = VCF::vkF6;
			}
			break;

		case GDK_F7 : {
				result = VCF::vkF7;
			}
			break;

		case GDK_F8 : {
				result = VCF::vkF8;
			}
			break;

		case GDK_F9 : {
				result = VCF::vkF9;
			}
			break;

		case GDK_F10 : {
				result = VCF::vkF10;
			}
			break;

		case GDK_F11 : {
				result = VCF::vkF11;
			}
			break;

		case GDK_F12 : {
				result = VCF::vkF12;
			}
			break;

		case GDK_KP_Up :
		case GDK_Up : {
				result = VCF::vkUpArrow;
			}
			break;

		case GDK_KP_Down :
		case GDK_Down : {
				result = VCF::vkDownArrow;
			}
			break;

		case GDK_KP_Left :
		case GDK_Left : {
				result = VCF::vkLeftArrow;
			}
			break;

		case GDK_KP_Right :
		case GDK_Right : {
				result = VCF::vkRightArrow;
			}
			break;

		case GDK_Delete : {
				result = VCF::vkDelete;
			}
			break;

		case GDK_Return : {
				result = VCF::vkReturn;
			}
			break;

		case GDK_BackSpace : {
				result = VCF::vkBackSpace;
			}
			break;

		case GDK_space : {
				result = VCF::vkSpaceBar;
			}
			break;

		case GDK_Escape : {
				result = VCF::vkEscape;
			}
			break;

		case GDK_Page_Down : {
				result = VCF::vkPgDown;
			}
			break;

		case GDK_Page_Up : {
				result = VCF::vkPgUp;
			}
			break;

		case GDK_Home : {
				result = VCF::vkHome;
			}
			break;

		case GDK_End : {
				result = VCF::vkEnd;
			}
			break;

		case GDK_Control_R :
		case GDK_Control_L : {
				result = VCF::vkCtrl;
			}
			break;

		case GDK_Alt_R :
		case GDK_Alt_L : {
				result = VCF::vkAlt;
			}
			break;

		case GDK_Shift_R :
		case GDK_Shift_L : {
				result = VCF::vkShift;
			}
			break;

		case GDK_Tab : {
				result = VCF::vkTab;
			}
			break;

		case GDK_0 :
		case GDK_KP_0 : {
				result = VCF::vkNumber0;
			}
			break;

		case GDK_1 :
		case GDK_KP_1 : {
				result = VCF::vkNumber1;
			}
			break;

		case GDK_2 :
		case GDK_KP_2 : {
				result = VCF::vkNumber2;
			}
			break;

		case GDK_3 :
		case GDK_KP_3 : {
				result = VCF::vkNumber3;
			}
			break;

		case GDK_4 :
		case GDK_KP_4 : {
				result = VCF::vkNumber4;
			}
			break;

		case GDK_5 :
		case GDK_KP_5 : {
				result = VCF::vkNumber5;
			}
			break;

		case GDK_6 :
		case GDK_KP_6 : {
				result = VCF::vkNumber6;
			}
			break;

		case GDK_7 :
		case GDK_KP_7 : {
				result = VCF::vkNumber7;
			}
			break;

		case GDK_8 :
		case GDK_KP_8 : {
				result = VCF::vkNumber8;
			}
			break;

		case GDK_9 :
		case GDK_KP_9 : {
				result = VCF::vkNumber9;
			}
			break;

		case GDK_a :
		case GDK_A : {
				result = VCF::vkLetterA;
			}
			break;

		case GDK_b :
		case GDK_B : {
				result = VCF::vkLetterB;
			}
			break;

		case GDK_c :
		case GDK_C : {
				result = VCF::vkLetterC;
			}
			break;

		case GDK_d :
		case GDK_D : {
				result = VCF::vkLetterD;
			}
			break;

		case GDK_e :
		case GDK_E : {
				result = VCF::vkLetterE;
			}
			break;

		case GDK_f :
		case GDK_F : {
				result = VCF::vkLetterF;
			}
			break;

		case GDK_g :
		case GDK_G : {
				result = VCF::vkLetterG;
			}
			break;

		case GDK_h :
		case GDK_H : {
				result = VCF::vkLetterH;
			}
			break;

		case GDK_i :
		case GDK_I : {
				result = VCF::vkLetterI;
			}
			break;

		case GDK_j :
		case GDK_J : {
				result = VCF::vkLetterJ;
			}
			break;

		case GDK_k :
		case GDK_K : {
				result = VCF::vkLetterK;
			}
			break;

		case GDK_l :
		case GDK_L : {
				result = VCF::vkLetterL;
			}
			break;

		case GDK_m :
		case GDK_M : {
				result = VCF::vkLetterM;
			}
			break;

		case GDK_n :
		case GDK_N : {
				result = VCF::vkLetterN;
			}
			break;

		case GDK_o :
		case GDK_O : {
				result = VCF::vkLetterO;
			}
			break;

		case GDK_p :
		case GDK_P : {
				result = VCF::vkLetterP;
			}
			break;

		case GDK_q :
		case GDK_Q : {
				result = VCF::vkLetterQ;
			}
			break;

		case GDK_r :
		case GDK_R : {
				result = VCF::vkLetterR;
			}
			break;

		case GDK_s :
		case GDK_S : {
				result = VCF::vkLetterS;
			}
			break;

		case GDK_t :
		case GDK_T : {
				result = VCF::vkLetterT;
			}
			break;

		case GDK_u :
		case GDK_U : {
				result = VCF::vkLetterU;
			}
			break;

		case GDK_v :
		case GDK_V : {
				result = VCF::vkLetterV;
			}
			break;

		case GDK_w :
		case GDK_W : {
				result = VCF::vkLetterW;
			}
			break;

		case GDK_x :
		case GDK_X : {
				result = VCF::vkLetterX;
			}
			break;

		case GDK_y :
		case GDK_Y : {
				result = VCF::vkLetterY;
			}
			break;

		case GDK_z :
		case GDK_Z : {
				result = VCF::vkLetterZ;
			}
			break;

		case GDK_Print : {
				result = VCF::vkPrintScreen;
			}
			break;

		case GDK_Pause : {
				result = VCF::vkPause;
			}
			break;

		case GDK_Scroll_Lock : {
				result = VCF::vkScrollLock;
			}
			break;

		case GDK_KP_Multiply :
		case GDK_multiply : {
				result = VCF::vkMultiplySign;
			}
			break;

		case GDK_plus :
		case GDK_KP_Add : {
				result = VCF::vkPlusSign;
			}
			break;

		case GDK_minus :
		case GDK_KP_Subtract : {
				result = VCF::vkMinusSign;
			}
			break;

		case GDK_period :
		case GDK_KP_Decimal : {
				result = VCF::vkPeriod;
			}
			break;

		case GDK_slash :
		case GDK_KP_Divide : {
				result = VCF::vkDivideSign;
			}
			break;

		case GDK_backslash : {
				result = VCF::vkBackSlash;
			}
			break;

		case GDK_bracketleft : {
				result = VCF::vkOpenBracket;
			}
			break;

		case GDK_braceleft : {
				result = VCF::vkOpenBrace;
			}
			break;

		case GDK_bracketright : {
				result = VCF::vkCloseBracket;
			}
			break;


		case GDK_braceright : {
				result = VCF::vkCloseBrace;
			}
			break;

		case GDK_semicolon : {
				result = VCF::vkSemiColon;
			}
			break;

		case GDK_colon : {
				result = VCF::vkColon;
			}
			break;

		case GDK_quoteright :
		case GDK_quoteleft : {
				result = VCF::vkSingleQuote;
			}
			break;

		case GDK_quotedbl : {
				result = VCF::vkDoubleQuote;
			}
			break;

		case GDK_comma : {
				result = VCF::vkComma;
			}
			break;

		case GDK_less : {
				result = VCF::vkLessThan;
			}
			break;

		case GDK_greater : {
				result = VCF::vkGreaterThan;
			}
			break;


		case GDK_question : {
				result = VCF::vkQuestionMark;
			}
			break;
	}

	return result;
}



ulong32 GTKUIToolkit::translateButtonMask( GdkModifierType buttonState )
{
	ulong32 result = 0;

	if ( buttonState & GDK_BUTTON1_MASK ) {
		result |= VCF::mbmLeftButton;
	}
	if ( buttonState & GDK_BUTTON2_MASK ) {
		result |= VCF::mbmMiddleButton;
	}
	if ( buttonState & GDK_BUTTON3_MASK ) {
		result |= VCF::mbmRightButton;
	}

	return result;
}



ulong32 GTKUIToolkit::translateKeyMask( GdkModifierType keyState )
{
	ulong32 result = VCF::kmUndefined;

	if ( keyState & GDK_SHIFT_MASK ) {
		result |= VCF::kmShift;
	}
	if ( keyState & GDK_CONTROL_MASK ) {
		result |= VCF::kmCtrl;
	}
	if ( keyState & GDK_MOD1_MASK ) {
		result |= VCF::kmAlt;
	}


	return result;
}

GraphicsResourceBundlePeer*
GTKUIToolkit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return 0;
}

SystemTrayPeer* GTKUIToolkit::internal_createSystemTrayPeer()
{
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.8  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.7  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
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
*Revision 1.3.2.2  2003/11/01 20:35:23  ddiego
*added GTKToolbar class impl - no real functionality at this point
*
*Revision 1.3.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.3  2003/08/09 02:56:46  ddiego
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
*Revision 1.2.2.4  2003/07/14 22:52:53  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.2.2.3  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*Revision 1.2.2.2  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.2.2.1  2003/06/01 16:44:00  ddiego
*further GTK support added
*
*Revision 1.2  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.4  2003/04/23 03:42:54  ddiego
*further gtk dev got basic eventing code in place
*
*Revision 1.1.2.3  2003/04/19 22:22:56  ddiego
*tested the code developed in windows using gtk in linux. Seems to work ok except for a
*few minor compiler glitches. Had to comment out the partial specialization for
*floating point image bits in include/graphics/ImageBits.h. Also made some
*adjustments in the makefiles for building the GraphicsKit and ApplicationKit
*from the build/make/Makefile.
*
*Revision 1.1.2.2  2003/04/19 03:31:15  ddiego
*basic code in place for gtk port for ApplicationKit - needs to be tested in
*linux
*
*Revision 1.1.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


