//OSXUIToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXDesktopPeer.h"
#include "vcf/ApplicationKit/OSXApplicationPeer.h"
#include "vcf/ApplicationKit/OSXControlContextPeer.h"
#include "vcf/ApplicationKit/OSXCursorPeer.h"
#include "vcf/ApplicationKit/OSXWindow.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXLightweightControl.h"
#include "vcf/ApplicationKit/OSXDialog.h"
#include "vcf/ApplicationKit/OSXButton.h"
#include "vcf/ApplicationKit/OSXColorDialog.h"
#include "vcf/ApplicationKit/OSXFolderBrowseDialog.h"
#include "vcf/ApplicationKit/OSXFileOpenDialog.h"
#include "vcf/ApplicationKit/OSXFileSaveDialog.h"
#include "vcf/ApplicationKit/OSXMenuBar.h"
#include "vcf/ApplicationKit/OSXMenuItem.h"


#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/OSXAppResourceBundle.h"


#define kSleepTime	32767


namespace VCF {


VirtualKeyCode translateOSXKeyToVirtKeyCode( VCFChar ch, UInt32 keyCode, UInt32 mod )
{
	VirtualKeyCode result = vkUndefined;
	switch ( ch ) {
		case kHomeCharCode : {
			result = vkHome;
		}
        break;

		case kEnterCharCode : {
			result = vkReturn;
		}
        break;

        case kEndCharCode : {
			result = vkEnd;
		}
		break;

        case kHelpCharCode : {
			result = vkF1;
		}
		break;

        case kBackspaceCharCode : {
			result = vkBackSpace;
		}
        break;

        case kTabCharCode : {
			result = vkTab;
		}
		break;

        case kPageUpCharCode : {
			result = vkPgUp;
		}
        break;

		case kPageDownCharCode : {
			result = vkPgDown;
		}
        break;

		case kReturnCharCode : {
			result = vkReturn;
		}
        break;

		case kEscapeCharCode : {
			result = vkEscape;
		}
        break;

		case kLeftArrowCharCode : {
			result = vkLeftArrow;
		}
        break;

		case kRightArrowCharCode : {
			result = vkRightArrow;
		}
        break;

		case kUpArrowCharCode : {
			result = vkUpArrow;
		}
        break;

		case kDownArrowCharCode : {
			result = vkDownArrow;
		}
        break;

		case kDeleteCharCode : {
			result = vkDelete;
		}
        break;

		case kSpaceCharCode : {
			result = vkSpaceBar;
		}
        break;

		case kFunctionKeyCharCode : {
			switch( keyCode ) {
				case 0x7a : {
					result = vkF1;
				}
				break;

				case 0x78 : {
					result = vkF2;
				}
				break;

				case 0x63 : {
					result = vkF3;
				}
				break;

				case 0x76 : {
					result = vkF4;
				}
				break;

				case 0x60 : {
					result = vkF5;
				}
				break;

				case 0x61 : {
					result = vkF6;
				}
				break;

				case 0x62 : {
					result = vkF7;
				}
				break;

				case 0x64 : {
					result = vkF8;
				}
				break;

				case 0x65 : {
					result = vkF9;
				}
				break;

				case 0x6D : {
					result = vkF10;
				}
				break;

				case 0x67 : {
					result = vkF11;
				}
				break;

				case 0x6F : {
					result = vkF12;
				}
				break;
				/*
				case 0x69 : {
					result = vkF13;
				}
				break;

				case 0x6B : {
					result = vkF14;
				}
				break;

				case 0x71 : {
					result = vkF15;
				}
				break;
				*/
			}
		}
	}


	if ( result == vkUndefined ) {
		switch ( ch ) {
			case 'A': case 'a': {
				result = vkLetterA;
			}
			break;

			case 'B': case 'b': {
				result = vkLetterB;
			}
			break;

			case 'C': case 'c': {
				result = vkLetterC;
			}
			break;

			case 'D': case 'd': {
				result = vkLetterD;
			}
			break;

			case 'E': case 'e': {
				result = vkLetterE;
			}
			break;

			case 'F': case 'f': {
				result = vkLetterF;
			}
			break;

			case 'G': case 'g': {
				result = vkLetterG;
			}
			break;

			case 'H': case 'h': {
				result = vkLetterH;
			}
			break;

			case 'I': case 'i': {
				result = vkLetterI;
			}
			break;

			case 'J': case 'j': {
				result = vkLetterJ;
			}
			break;

			case 'K': case 'k': {
				result = vkLetterK;
			}
			break;

			case 'L': case 'l': {
				result = vkLetterL;
			}
			break;

			case 'M': case 'm': {
				result = vkLetterM;
			}
			break;

			case 'N': case 'n': {
				result = vkLetterN;
			}
			break;

			case 'O': case 'o': {
				result = vkLetterO;
			}
			break;

			case 'P': case 'p': {
				result = vkLetterP;
			}
			break;

			case 'Q': case 'q': {
				result = vkLetterQ;
			}
			break;

			case 'R': case 'r': {
				result = vkLetterR;
			}
			break;

			case 'S': case 's': {
				result = vkLetterS;
			}
			break;

			case 'T': case 't': {
				result = vkLetterT;
			}
			break;

			case 'U': case 'u': {
				result = vkLetterU;
			}
			break;

			case 'V': case 'v': {
				result = vkLetterV;
			}
			break;

			case 'W': case 'w': {
				result = vkLetterW;
			}
			break;

			case 'X': case 'x': {
				result = vkLetterX;
			}
			break;

			case 'Y': case 'y': {
				result = vkLetterY;
			}
			break;

			case 'Z': case 'z': {
				result = vkLetterZ;
			}
			break;
		}
	}
	return result;
}



//UIMetricsManager implementation for OSX
class OSXUIMetricsManager : public UIMetricsManager {
public:
	OSXUIMetricsManager(){}

	virtual ~OSXUIMetricsManager(){}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type ) {
		VCF::Font result("Arial", 13);

		result.setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_CAPTION_TEXT ) );
		
		Str255 fontName;
		SInt16 fontSize = 0;
		Style fontStyle = 0;
		OSStatus err = noErr;
		
		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {
				err = GetThemeFont( kThemeSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
				}				
			}
			break;

			case UIMetricsManager::ftSelectedMenuItemFont : {
				err = GetThemeFont( kThemeSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );					
				}
			}
			break;

			case UIMetricsManager::ftSystemFont : {
				err = GetThemeFont( kThemeSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;
			
			case UIMetricsManager::ftControlFont :   {
				err = GetThemeFont( kThemeLabelFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;
			

			case UIMetricsManager::ftMessageFont : {
				err = GetThemeFont( kThemeEmphasizedSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftToolTipFont : {
				err = GetThemeFont( kThemeSmallSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;
		}

		return result;
	}

	virtual double getDefaultHeightFor( const UIMetricsManager::HeightType& type )  {
		double result = 0.0;
		switch ( type ) {
			case UIMetricsManager::htLabelHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htComboBoxHeight : {
				result = 20;
			}
			break;

			case UIMetricsManager::htListItemHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htButtonHeight : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricPushButtonHeight, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case UIMetricsManager::htRadioBoxHeight : case UIMetricsManager::htCheckBoxHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htToolTipHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htSeparatorHeight : {
				result = 2.0;
			}
			break;

			case UIMetricsManager::htInformationalControl : {
				result = 15;
			}
			break;
		}
		return result;

	}

	virtual double getPreferredSpacingFor( const UIMetricsManager::SpacingType& type )  {
		double result = 0.0;

		//values largely derived from the Apple HIG at
		//http://developer.apple.com/techpubs/macosx/Essentials/AquaHIGuidelines/AHIGLayout/index.html
		switch ( type ) {
			case UIMetricsManager::stWindowBorderDelta : {
				result = 20.0;
			}
			break;

			case UIMetricsManager::stContainerBorderDelta : {
				result = 22;
			}
			break;

			case UIMetricsManager::stControlVerticalSpacing : {
				result = 12;
			}
			break;

			case UIMetricsManager::stControlHorizontalSpacing : {
				result = 12;
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

	virtual Size getDefaultSliderThumbDimensions()  {
		Size result;
		SInt32 val = 0;
		GetThemeMetric( kThemeMetricScrollBarWidth, &val );		

		result.width_ = val;
		result.height_ = val;

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )  {
		Size result;


		return result;
	}

	virtual Size getDefaultVerticalScrollButtonDimensions()  {
		Size result;
		SInt32 val = 0;
		GetThemeMetric( kThemeMetricScrollBarWidth, &val );		

		result.width_ = val;
		result.height_ = val;

		return result;
	}

	virtual Size getDefaultHorizontalScrollButtonDimensions()  {
		Size result;

		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultTabDimensions( const String& caption )  {
		Size result;

		return result;
	}
};






class OSXUIPolicyManager : public UIPolicyManager {
public:
	virtual void mergeMenus( Menu* appMenu, Menu* windowMenu ){
	
	}

	virtual Frame* getOwnerForDialog() {
		return NULL;
	}
	
	virtual Rect adjustInitialDialogBounds( Dialog* dialog ) {
		Rect result;
		Control* owner = dialog->getOwner();
		if ( NULL != owner ) {			
			result.left_ = owner->getLeft() + ( owner->getWidth()/2.0 - dialog->getWidth()/2.0 );
			result.top_ = owner->getTop() + ( owner->getHeight()/2.0 - dialog->getHeight()/2.0 );
			result.right_ = result.left_ + dialog->getWidth();
			result.bottom_ = result.top_ + dialog->getHeight();
			if ( NULL != owner->getParent() ) {
				owner->translateToScreenCoords( &result );
			}
		}
		else {
			//get the horizontal center of screen, and the vertical position
			//about 1/3 of the way from the top
			double w = Desktop::getDesktop()->getWidth();
			double h = Desktop::getDesktop()->getHeight();
			
			result.left_ = result.right_ = w / 2.0;
			result.top_ = result.bottom_ = h / 3.0;
			
			result.inflate( dialog->getWidth()/2.0, dialog->getHeight()/2.0 );
			
		}
		
		return result;
	}
};




};//end of VCF namespace


using namespace VCF;



OSXUIToolkit::OSXUIToolkit():
    quitEventLoop_(false),
    eventHandlerRef_(NULL),
    handlerUPP_(NULL),
    timerUPP_(NULL),
    idleTimerUPP_(NULL),
    idleTimerRef_(NULL)
{
    metricsMgr_ = new OSXUIMetricsManager();
	policyMgr_ = new OSXUIPolicyManager();
    //install event loop callbacks
    handlerUPP_ = NewEventHandlerUPP(OSXUIToolkit::handleOSXApplicationEvents);
    static EventTypeSpec eventsToHandle[] ={
                            { kEventClassCommand, kEventCommandProcess },
                            { kEventClassCommand, kEventCommandUpdateStatus },
                            { OSXUIToolkit::CustomEventClass, OSXUIToolkit::EventPosted} };

    OSStatus err = InstallEventHandler( GetApplicationEventTarget(),
                                        handlerUPP_,
                                        sizeof(eventsToHandle)/sizeof(eventsToHandle[0]),
                                        eventsToHandle,
                                        this,
                                        &eventHandlerRef_ );

    timerUPP_ = NewEventLoopTimerUPP(OSXUIToolkit::handleTimerEvent);
    idleTimerUPP_ = NewEventLoopIdleTimerUPP(OSXUIToolkit::handleIdleTimer);

    InstallEventLoopIdleTimer( GetCurrentEventLoop(), 0, 0.25,
                                idleTimerUPP_, this, &idleTimerRef_ );


    if ( err != noErr ) {
        printf( "InstallEventHandler failed" );
    }
}

OSXUIToolkit::~OSXUIToolkit()
{

    std::map<EventLoopTimerRef,TimeOutHandler>::iterator found = timeoutHandlers_.begin();
    while ( !timeoutHandlers_.empty() ) {
        internal_unregisterTimerHandler( found->second.handler_ );
        found = timeoutHandlers_.begin();
    }


    DisposeEventHandlerUPP(handlerUPP_);
    DisposeEventLoopTimerUPP(timerUPP_);

    RemoveEventLoopTimer( idleTimerRef_ );
    DisposeEventLoopIdleTimerUPP(idleTimerUPP_);
    printf( "OSXUIToolkit destroyed\n");
}

ApplicationPeer* OSXUIToolkit::internal_createApplicationPeer()
{
    return new OSXApplicationPeer();
}

TextPeer* OSXUIToolkit::internal_createTextPeer( TextControl* component, const bool& isMultiLineControl )
{
    return NULL;
}

TreePeer* OSXUIToolkit::internal_createTreePeer( TreeControl* component )
{
    return NULL;
}

ListviewPeer* OSXUIToolkit::internal_createListViewPeer( ListViewControl* component )
{
    return NULL;
}

DialogPeer* OSXUIToolkit::internal_createDialogPeer( Control* owner, Dialog* component )
{
    return new OSXDialog( owner, component );
}

DialogPeer* OSXUIToolkit::internal_createDialogPeer()
{
    return new OSXDialog();
}

ControlPeer* OSXUIToolkit::internal_createControlPeer( Control* control, ComponentType componentType )
{
	ControlPeer* result = NULL;

	switch ( componentType ){
		case CT_LIGHTWEIGHT:{
			result = new OSXLightweightControl( control );
		}
		break;

		case CT_DEFAULT: case CT_HEAVYWEIGHT:{
			result = new OSXControl( control );
		}
		break;
	}
	return result;	
}

WindowPeer* OSXUIToolkit::internal_createWindowPeer( Control* control, Control* owner )
{
    return new OSXWindow( control, owner );
}

ToolbarPeer* OSXUIToolkit::internal_createToolbarPeer( Toolbar* toolbar )
{
    return NULL;
}

MenuItemPeer* OSXUIToolkit::internal_createMenuItemPeer( MenuItem* item )
{
    return new OSXMenuItem( item );
}

MenuBarPeer* OSXUIToolkit::internal_createMenuBarPeer( MenuBar* menuBar )
{
    return new OSXMenuBar( menuBar );
}

PopupMenuPeer* OSXUIToolkit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
    return NULL;
}

ButtonPeer* OSXUIToolkit::internal_createButtonPeer( CommandButton* component )
{
    return new OSXButton( component );
}

HTMLBrowserPeer* OSXUIToolkit::internal_createHTMLBrowserPeer( Control* control )
{
    return NULL;
}

ContextPeer* OSXUIToolkit::internal_createContextPeer( Control* control )
{
    return new OSXControlContextPeer( control->getPeer() );
}

CommonFileDialogPeer* OSXUIToolkit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
    return new OSXFileOpenDialog(owner);
}

CommonFileDialogPeer* OSXUIToolkit::internal_createCommonFileSaveDialogPeer( Control* owner )
{
    return new OSXFileSaveDialog(owner);
}

CommonColorDialogPeer* OSXUIToolkit::internal_createCommonColorDialogPeer( Control* owner )
{
    return new OSXColorDialog( owner );
}

CommonFolderBrowseDialogPeer* OSXUIToolkit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
    return new OSXFolderBrowseDialog( owner );
}

CommonFontDialogPeer* OSXUIToolkit::internal_createCommonFontDialogPeer( Control* owner )
{
    return NULL;
}

DragDropPeer* OSXUIToolkit::internal_createDragDropPeer()
{
    return NULL;
}

DataObjectPeer* OSXUIToolkit::internal_createDataObjectPeer()
{
    return NULL;
}

DropTargetPeer* OSXUIToolkit::internal_createDropTargetPeer()
{
    return NULL;
}

DesktopPeer* OSXUIToolkit::internal_createDesktopPeer( Desktop* desktop )
{
    return new OSXDesktopPeer(desktop);
}

ScrollPeer* OSXUIToolkit::internal_createScrollPeer( Control* control )
{
    return NULL;
}

GraphicsResourceBundlePeer* OSXUIToolkit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new OSXAppResourceBundle( app );
}

SystemTrayPeer* OSXUIToolkit::internal_createSystemTrayPeer()
{
	return NULL;
}

CommonPrintDialogPeer* OSXUIToolkit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return NULL;
}

CursorPeer* OSXUIToolkit::internal_createCursorPeer( Cursor* cursor )
{
    return new OSXCursorPeer(cursor);
}

ClipboardPeer* OSXUIToolkit::internal_createClipboardPeer()
{
    return NULL;
}

bool OSXUIToolkit::internal_createCaret( Control* owningControl, Image* caretImage  )
{
    return false;
}

bool OSXUIToolkit::internal_destroyCaret( Control* owningControl )
{
    return false;
}

void OSXUIToolkit::internal_setCaretVisible( const bool& caretVisible )
{

}

void OSXUIToolkit::internal_setCaretPos( Point* point )
{

}

void OSXUIToolkit::internal_postEvent( VCF::EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
    EventRef osxEvent = OSXUIToolkit::createUserCarbonEvent(OSXUIToolkit::EventPosted);


    OSStatus err = SetEventParameter( osxEvent, OSXUIToolkit::EventHandler,
                        typeUInt32, OSXUIToolkit::SizeOfEventHandler, &eventHandler );
    if ( err != noErr ) {
        printf( "SetEventParameter failed\n" );
    }

    err = SetEventParameter( osxEvent, OSXUIToolkit::EventHandlerEvent,
                        typeUInt32, OSXUIToolkit::SizeOfEventHandlerEvent, &event );
	if ( err != noErr ) {
        printf( "SetEventParameter failed\n" );
    }

    Boolean val = deleteHandler ? TRUE : FALSE;
    err = SetEventParameter( osxEvent, OSXUIToolkit::DeletePostedEvent,
                        typeBoolean, OSXUIToolkit::SizeOfDeletePostedEvent, &val );
	if ( err != noErr ) {
        printf( "SetEventParameter failed\n" );
    }

    err = PostEventToQueue( GetCurrentEventQueue(), osxEvent, kEventPriorityStandard );
    if ( err != noErr ) {
        printf( "PostEventToQueue failed\n" );
    }
}

void OSXUIToolkit::handleIdleTimer( EventLoopTimerRef inTimer, EventLoopIdleTimerMessage inState, void *inUserData )
{
    OSXUIToolkit* toolkit = (OSXUIToolkit*)inUserData;

    printf( "idle handler...\n" );

    switch ( inState ) {
        case kEventLoopIdleTimerStarted : {

        }
        break;

        case kEventLoopIdleTimerIdling : {
            printf( "\tkEventLoopIdleTimerIdling...\n" );
            Application* app = Application::getRunningInstance();
            if ( NULL != app ) {
				app->idleTime();
			}

			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( true == registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}
        }
        break;

        case kEventLoopIdleTimerStopped : {

        }
        break;
    }
}

void OSXUIToolkit::handleTimerEvent( EventLoopTimerRef inTimer, void * inUserData )
{
   OSXUIToolkit* toolkit = (OSXUIToolkit*)inUserData;
   std::map<EventLoopTimerRef,TimeOutHandler>::iterator found =
        toolkit->timeoutHandlers_.find( inTimer );
    if ( found != toolkit->timeoutHandlers_.end() ) {
        TimeOutHandler& toh = found->second;
        TimerEvent event( toh.source_, TIMER_EVENT_PULSE );
		toh.handler_->invoke( &event );
    }
}


void OSXUIToolkit::internal_registerTimerHandler( Object* source, VCF::EventHandler* handler, const ulong32& timeoutInMilliSeconds )
{

    TimeOutHandler toh;
    toh.source_ = source;
    toh.handler_ = handler;


    std::map<EventLoopTimerRef,TimeOutHandler>::iterator found = timeoutHandlers_.begin();
    while ( found != timeoutHandlers_.end() ) {
        TimeOutHandler& tmHandler = found->second;
        if ( tmHandler.handler_ == handler ) {
            RemoveEventLoopTimer( tmHandler.timerRef_ );
            timeoutHandlers_.erase( found );
            break;
        }
        found ++;
    }

    double timeout = ((double)timeoutInMilliSeconds/1000.0);

    InstallEventLoopTimer( GetCurrentEventLoop(),
                            timeout,
                            timeout,
                            timerUPP_,
                            this,
                            &toh.timerRef_ );

    timeoutHandlers_[toh.timerRef_] = toh;
}

void OSXUIToolkit::internal_unregisterTimerHandler( VCF::EventHandler* handler )
{
    std::map<EventLoopTimerRef,TimeOutHandler>::iterator found = timeoutHandlers_.begin();
    while ( found != timeoutHandlers_.end() ) {
        TimeOutHandler& tmHandler = found->second;
        if ( tmHandler.handler_ == handler ) {
            RemoveEventLoopTimer( tmHandler.timerRef_ );
            timeoutHandlers_.erase( found );
            break;
        }
        found ++;
    }
}


void OSXUIToolkit::internal_runEventLoop()
{
    //set to false to begin with
    quitEventLoop_ = false;

    RunApplicationEventLoop();

    //reset back to false when finished
    quitEventLoop_ = false;
}

UIToolkit::ModalReturnType OSXUIToolkit::internal_runModalEventLoopFor( Control* control )
{
	Frame* ownerFrame = control->getParentFrame();
	WindowRef controlWindow = (WindowRef) ownerFrame->getPeer()->getHandleID();
	
	//EndAppModalStateForWindow( controlWindow );
	UIToolkit::ModalReturnType result = UIToolkit::mrTrue;
	/*
	EventRef theEvent;
	while  ( ReceiveNextEvent(0, NULL,kEventDurationForever,true, &theEvent)== noErr ) {
		
		SendEventToEventTarget (theEvent, GetEventDispatcherTarget());
				
		if ( kEventClassCommand == GetEventKind( theEvent ) ) {
			HICommand		command;
			GetEventParameter( theEvent, kEventParamDirectObject, typeHICommand, NULL,
								sizeof( HICommand ), NULL, &command );							
								
			if ( command.attributes & kHICommandFromControl ) {
				if ( kEventCommandProcess == GetEventKind( theEvent ) ) {
					switch ( command.commandID ) {
						case kHICommandOK : {
							//result = UIToolkit::mrOK;
						}
						break;
						
						case kHICommandCancel : {
							result = UIToolkit::mrCancel;
						}
						break;
					}
				}
			}					
		}
		
		
		ReleaseEvent(theEvent);
	}
	*/
	
	RunAppModalLoopForWindow( controlWindow );
	
	
	//EndAppModalStateForWindow( controlWindow );
	
    return result;
}

void OSXUIToolkit::internal_quitCurrentEventLoop()
{
    EventLoopRef currentLoop = GetCurrentEventLoop();
    QuitEventLoop( currentLoop );
    quitEventLoop_ = true;
}

OSStatus OSXUIToolkit::handleOSXApplicationEvents( EventHandlerCallRef nextHandler, EventRef osxEvent, void* userData )
{
    OSXUIToolkit * toolkit = (OSXUIToolkit*)userData;
    return toolkit->handleAppEvents( nextHandler, osxEvent );
}

OSStatus OSXUIToolkit::handleAppEvents( EventHandlerCallRef nextHandler, EventRef osxEvent )
{
    OSStatus result = eventNotHandledErr;
    switch ( GetEventClass( osxEvent ) ) {
        case OSXUIToolkit::CustomEventClass : {
            switch ( GetEventKind( osxEvent ) ) {
                case OSXUIToolkit::EventPosted : {
                    ::CallNextEventHandler( nextHandler, osxEvent );

                    UInt32 val;
                    Boolean deleteHandler;
                    OSStatus err = GetEventParameter( osxEvent,
                                        OSXUIToolkit::EventHandler,
                                        typeUInt32,
                                        NULL,
                                        OSXUIToolkit::SizeOfEventHandler,
                                        NULL,
                                        &val );

                    VCF::EventHandler* eventHandler  = (VCF::EventHandler*)val;

                    err = GetEventParameter( osxEvent,
                                        OSXUIToolkit::EventHandlerEvent,
                                        typeUInt32,NULL,
                                        OSXUIToolkit::SizeOfEventHandlerEvent,NULL,
                                        &val );


                    Event* e = (Event*)val;

                    err = GetEventParameter( osxEvent,
                                        OSXUIToolkit::DeletePostedEvent,
                                        typeBoolean,NULL,
                                        OSXUIToolkit::SizeOfDeletePostedEvent,NULL,
                                        &deleteHandler );


                    if ( (NULL != eventHandler) && (NULL != e ) ) {

                        eventHandler->invoke( e );

                        if ( deleteHandler ) {
                            delete eventHandler;
                        }
                        delete e;
                    }

                    result = noErr;
                }
                break;
            }
        }
        break;

		case kEventClassCommand : {
			switch ( GetEventKind( osxEvent ) ) {
				case kEventProcessCommand : {
					HICommand		command;
					GetEventParameter( osxEvent, kEventParamDirectObject, typeHICommand, NULL,
									sizeof( HICommand ), NULL, &command );
									
					MenuItem* item = NULL;
					GetMenuCommandProperty( command.menu.menuRef, 
										command.commandID,
										VCF_PROPERTY_CREATOR, 
										OSXMenuItem::propertyTag,
										sizeof(item),
										NULL, &item );
					
								
					if ( NULL != item ) {
						//cause the menu click method to be called!
						item->click();
						result = noErr;
					}										
                }
                break;
				
				case kEventCommandUpdateStatus : {
					HICommand		command;
					GetEventParameter( osxEvent, kEventParamDirectObject, typeHICommand, NULL,
									sizeof( HICommand ), NULL, &command );
									
					MenuItem* item = NULL;
					GetMenuCommandProperty( command.menu.menuRef, 
										command.commandID,
										VCF_PROPERTY_CREATOR, 
										OSXMenuItem::propertyTag,
										sizeof(item),
										NULL, &item );
					
					
					result = ::CallNextEventHandler( nextHandler, osxEvent );
								
					if ( NULL != item ) {					
						//cause the menu update method to be called!
						//this updates the menu item
						item->update();
					}										
                }
                break;
			}
		}
		break;
		
        default : {
            return ::CallNextEventHandler( nextHandler, osxEvent );
        }
        break;
    }

    return result;
}




VCF::Event* OSXUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
    VCF::Event* result = NULL;
    OSXEventMsg* msg = (OSXEventMsg*)eventData;
    UInt32 whatHappened = GetEventKind( msg->osxEvent_ );

    UInt32 type = GetEventClass( msg->osxEvent_ );

    switch ( type ) {
        case kEventClassMouse : {
            EventMouseButton button = kEventMouseButtonPrimary;
            GetEventParameter( msg->osxEvent_, kEventParamMouseButton, typeMouseButton, NULL,
                                sizeof (EventMouseButton), NULL, &button);

            UInt32 keyboardModifier = 0;
            GetEventParameter( msg->osxEvent_, kEventParamKeyModifiers, typeUInt32, NULL,
                                sizeof (keyboardModifier), NULL, &keyboardModifier);

            ::Point mousePos;
            GetEventParameter( msg->osxEvent_, kEventParamMouseLocation, typeQDPoint, NULL,
                                sizeof (mousePos), NULL, &mousePos);


            UInt32 clickCount = 0;
            GetEventParameter( msg->osxEvent_, kEventParamClickCount, typeUInt32, NULL,
                                sizeof (clickCount), NULL, &clickCount);

            VCF::Point pt( mousePos.h ,
						   mousePos.v );



            switch ( whatHappened ) {
                case kEventMouseDown : {

                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_DOWN,
											OSXUtils::translateButtonMask( button ),
											OSXUtils::translateKeyMask( keyboardModifier ), &pt );

                }
                break;

                case kEventMouseUp : {
                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_UP,
											OSXUtils::translateButtonMask( button ),
											OSXUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventMouseMoved : {

                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
                                                OSXUtils::translateButtonMask( button ),
                                                OSXUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventMouseDragged : {
					Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }
                    
                    result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
                                                OSXUtils::translateButtonMask( button ),
                                                OSXUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventMouseEntered : {
                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_ENTERED,
                                                    OSXUtils::translateButtonMask( 0 ),
                                                    OSXUtils::translateKeyMask( 0 ), &pt );
                }
                break;

                case kEventMouseExited : {
                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_LEAVE,
                                                    OSXUtils::translateButtonMask( 0 ),
                                                    OSXUtils::translateKeyMask( 0 ), &pt );
                }
                break;

                case kEventMouseWheelMoved : {

                }
                break;
            }
        }
        break;

        case kEventClassKeyboard : {
            switch ( whatHappened ) {
                case kEventRawKeyDown : {
					char c = 0;
					UInt32 keyCode = 0;
					UInt32 keyMods = 0;
					UInt32 kbType = 0;

					GetEventParameter( msg->osxEvent_, kEventParamKeyMacCharCodes, typeChar, NULL,
                                sizeof (char), NULL, &c);
					GetEventParameter( msg->osxEvent_, kEventParamKeyCode, typeUInt32, NULL,
                                sizeof (keyCode), NULL, &keyCode);
					GetEventParameter( msg->osxEvent_, kEventParamKeyModifiers, typeUInt32, NULL,
                                sizeof (keyMods), NULL, &keyMods);
					GetEventParameter( msg->osxEvent_, kEventParamKeyboardType, typeUInt32, NULL,
                                sizeof (kbType), NULL, &kbType);



					VirtualKeyCode virtKeyValue = translateOSXKeyToVirtKeyCode( c, keyCode, keyMods );
					unsigned long keyMask = 0;

					if ( keyMods & cmdKey ) {
						keyMask |= kmAlt;
					}

					if ( keyMods & shiftKey ) {
						keyMask |= kmShift;
					}

					if ( keyMods & controlKey ) {
						keyMask |= kmCtrl;
					}

					result = new VCF::KeyboardEvent( msg->control_, Control::KEYBOARD_DOWN,
														1, keyMask, c, virtKeyValue );

					UIToolkit::handleKeyboardEvent( (KeyboardEvent*)result );

					if ( result->isConsumed() ) {
						//result->free();
						//result = NULL;
					}

					StringUtils::traceWithArgs( "keyMask: %d, virtKeyValue: %d\n",
												keyMask, virtKeyValue );
                }
                break;

                case kEventRawKeyRepeat : {

                }
                break;

                case kEventRawKeyUp : {
					char c = 0;
					UInt32 keyCode = 0;
					UInt32 keyMods = 0;
					UInt32 kbType = 0;

					GetEventParameter( msg->osxEvent_, kEventParamKeyMacCharCodes, typeChar, NULL,
                                sizeof (char), NULL, &c);
					GetEventParameter( msg->osxEvent_, kEventParamKeyCode, typeUInt32, NULL,
                                sizeof (keyCode), NULL, &keyCode);
					GetEventParameter( msg->osxEvent_, kEventParamKeyModifiers, typeUInt32, NULL,
                                sizeof (keyMods), NULL, &keyMods);
					GetEventParameter( msg->osxEvent_, kEventParamKeyboardType, typeUInt32, NULL,
                                sizeof (kbType), NULL, &kbType);



					VirtualKeyCode virtKeyValue = translateOSXKeyToVirtKeyCode( c, keyCode, keyMods );
					unsigned long keyMask = 0;

					if ( keyMods & cmdKey ) {
						keyMask |= kmAlt;
					}

					if ( keyMods & shiftKey ) {
						keyMask |= kmShift;
					}

					if ( keyMods & controlKey ) {
						keyMask |= kmCtrl;
					}


					result = new VCF::KeyboardEvent( msg->control_, Control::KEYBOARD_UP,
														1, keyMask, c, virtKeyValue );


                }
                break;

                case kEventRawKeyModifiersChanged : {

                }
                break;

                case kEventHotKeyPressed : {

                }
                break;

                case kEventHotKeyReleased : {

                }
                break;
            }
        }
        break;

        case kEventClassTextInput : {
            switch ( whatHappened ) {

            }
        }
        break;

        case kEventClassApplication : {
            switch ( whatHappened ) {
                case kEventAppActivated : {

                }
                break;

                case kEventAppDeactivated : {

                }
                break;

                case kEventAppQuit : {

                }
                break;

                case kEventAppLaunchNotification : {

                }
                break;

                case kEventAppLaunched : {

                }
                break;

                case kEventAppTerminated : {

                }
                break;

                case kEventAppFrontSwitched : {

                }
                break;

                case kEventAppFocusMenuBar : {

                }
                break;

                case kEventAppFocusNextDocumentWindow : {

                }
                break;

                case kEventAppFocusNextFloatingWindow : {

                }
                break;

                case kEventAppFocusToolbar : {

                }
                break;

                case kEventAppGetDockTileMenu : {

                }
                break;

                case kEventAppHidden : {

                }
                break;

                case kEventAppShown : {

                }
                break;

                case kEventAppSystemUIModeChanged : {

                }
                break;
            }
        }
        break;

        case kEventClassAppleEvent : {

        }
        break;

        case kEventClassMenu : {
            switch ( whatHappened ) {
                case kEventMenuBeginTracking : {

                }
                break;

                case kEventMenuEndTracking : {

                }
                break;

                case kEventMenuChangeTrackingMode : {

                }
                break;

                case kEventMenuOpening : {

                }
                break;

                case kEventMenuClosed : {

                }
                break;

                case kEventMenuTargetItem : {

                }
                break;

                case kEventMenuMatchKey : {

                }
                break;

                case kEventMenuEnableItems : {

                }
                break;

                case kEventMenuPopulate : {

                }
                break;

                case kEventMenuMeasureItemWidth : {

                }
                break;

                case kEventMenuMeasureItemHeight : {

                }
                break;

                case kEventMenuDrawItem : {

                }
                break;

                case kEventMenuDrawItemContent : {

                }
                break;

                case kEventMenuDispose : {

                }
                break;
            }
        }
        break;

        case kEventClassWindow : {
            switch ( whatHappened ) {
                case kEventWindowFocusAcquired : {
                    result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_GAINED );
                }
                break;

                case kEventWindowFocusRelinquish : {
                    result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_LOST );
                }
                break;

                case kEventWindowCollapse : {

                }
                break;

                case kEventWindowCollapseAll : {

                }
                break;

                case kEventWindowExpand : {

                }
                break;

                case kEventWindowExpandAll : {

                }
                break;

                case kEventWindowClose : {
                    result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_DELETED );
                }
                break;

                case kEventWindowCloseAll : {

                }
                break;

                case kEventWindowZoom : {

                }
                break;

                case kEventWindowZoomAll : {

                }
                break;

                case kEventWindowContextualMenuSelect : {

                }
                break;

                case kEventWindowPathSelect : {

                }
                break;

                case kEventWindowGetIdealSize : {

                }
                break;

                case kEventWindowGetMinimumSize : {

                }
                break;

                case kEventWindowGetMaximumSize : {

                }
                break;

                case kEventWindowBoundsChanged: {
                    UInt32 attributes = 0;
					OSStatus err = GetEventParameter( msg->osxEvent_,
                                                kEventParamAttributes,
                                                typeUInt32,
                                                NULL,
                                                sizeof( UInt32 ),
                                                NULL, &attributes );

					if ( err == noErr ) 	{
                        ::Rect currentBounds;
                            GetEventParameter( msg->osxEvent_, kEventParamCurrentBounds, typeQDRectangle,
                                                NULL, sizeof(currentBounds), NULL, &currentBounds);

						if ( attributes & kWindowBoundsChangeSizeChanged ) {

                            VCF::Size sz( abs(currentBounds.right - currentBounds.left),
                                            abs(currentBounds.bottom - currentBounds.top) );
                            result = new ControlEvent( msg->control_, sz );
						}
						else if ( attributes & kWindowBoundsChangeOriginChanged ) {
							VCF::Point pt( currentBounds.left , currentBounds.top );
                            result = new VCF::ControlEvent( msg->control_, pt );
						}
					}
                }
                break;

                case kEventWindowConstrain : {

                }
                break;

                case kEventWindowHandleContentClick : {

                }
                break;

                case kEventWindowGetDockTileMenu : {

                }
                break;

                case kEventWindowProxyBeginDrag : {

                }
                break;

                case kEventWindowProxyEndDrag : {

                }
                break;

                case kEventWindowToolbarSwitchMode : {

                }
                break;
            }
        }
        break;

        case kEventClassControl : {
            switch ( whatHappened ) {

                case kEventControlInitialize : {
					result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_CREATED );
                }
                break;

                case kEventControlDispose : {
					result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_DELETED );
                }
                break;

                case kEventControlSetFocusPart : {
					UInt32 attributes = 0;
					ControlRef ctrl = NULL;
					ControlRef startCtrl = NULL;
					ControlPartCode part = 0;
					OSStatus err = GetEventParameter( msg->osxEvent_,
                                                kEventParamDirectObject,
                                                typeControlRef,
                                                NULL,
                                                sizeof( ControlRef ),
                                                NULL, &ctrl );
					
					err = GetEventParameter( msg->osxEvent_,
                                                kEventParamStartControl,
                                                typeControlRef,
                                                NULL,
                                                sizeof( ControlRef ),
                                                NULL, &startCtrl );
												
					err = GetEventParameter( msg->osxEvent_,
                                                kEventParamControlPart,
                                                typeControlPartCode,
                                                NULL,
                                                sizeof( ControlPartCode ),
                                                NULL, &part );	
												
																																				
                }
                break;

                case kEventControlGetOptimalBounds : {

                }
                break;
				
				case kEventControlHit : {

                }
                break;
				

                case kEventControlHitTest : {
					::Point mousePos;
					GetEventParameter( msg->osxEvent_, kEventParamMouseLocation, typeQDPoint, NULL,
										sizeof (mousePos), NULL, &mousePos);
                    
					//LocalToGlobal( &mousePos );
					VCF::Point pt( mousePos.h , mousePos.v );
					//localizes the coords
					//msg->control_->translateFromScreenCoords( &pt );
			
					Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }
					
                    result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
                                                mbmLeftButton,
                                                OSXUtils::translateKeyMask( 0 ), &pt );

                }
                break;

                
                
                
                case kEventControlGetFocusPart : {

                }
                break;

                case kEventControlActivate : {
					result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_GAINED );
                }
                break;

                case kEventControlDeactivate : {
					result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_LOST );
                }
                break;

                case kEventControlSetCursor : {

                }
                break;

                case kEventControlContextualMenuClick : {

                }
                break;

                case kEventControlClick : {

                }
                break;

                case kEventControlGetNextFocusCandidate : {

                }
                break;

                case kEventControlGetAutoToggleValue : {

                }
                break;

                case kEventControlInterceptSubviewClick : {

                }
                break;

                case kEventControlGetClickActivation : {

                }
                break;

                case kEventControlDragEnter : {

                }
                break;

                case kEventControlDragWithin : {

                }
                break;

                case kEventControlDragLeave : {

                }
                break;

                case kEventControlDragReceive : {

                }
                break;

                case kEventControlTrack : {
					ControlRef theControl;
					GetEventParameter( msg->osxEvent_, kEventParamDirectObject, typeControlRef, NULL,
										sizeof (theControl), NULL, &theControl);
					
					
						   
					::Point mousePos;
					GetEventParameter( msg->osxEvent_, kEventParamMouseLocation, typeQDPoint, NULL,
										sizeof (mousePos), NULL, &mousePos);
            
            
					//LocalToGlobal( &mousePos );
					
					UInt32 keyboardModifier = 0;            
					GetEventParameter( msg->osxEvent_, kEventParamKeyModifiers, typeUInt32, NULL,
										sizeof (keyboardModifier), NULL, &keyboardModifier);
								
					VCF::Point pt( mousePos.h , 
									mousePos.v );
					
					OSXControl* control = OSXControl::getControlFromControlRef( theControl );
					//localizes the coords
					//control->translateFromScreenCoords( &pt );
					
						   
					Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }
                    
                    result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_DOWN,
                                                mbmLeftButton,
                                                OSXUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventControlGetScrollToHereStartPoint : {

                }
                break;

                case kEventControlGetIndicatorDragConstraint : {

                }
                break;

                case kEventControlIndicatorMoved : {

                }
                break;

                case kEventControlGhostingFinished : {

                }
                break;

                case kEventControlGetActionProcPart : {

                }
                break;

                case kEventControlGetPartRegion : {

                }
                break;

                case kEventControlGetPartBounds : {

                }
                break;

                case kEventControlSetData : {

                }
                break;

                case kEventControlGetData : {

                }
                break;

                case kEventControlGetSizeConstraints : {

                }
                break;

                case kEventControlValueFieldChanged : {

                }
                break;

                case kEventControlAddedSubControl : {

                }
                break;

                case kEventControlRemovingSubControl : {

                }
                break;

                case kEventControlBoundsChanged : {
					UInt32 attributes = 0;
					OSStatus err = GetEventParameter( msg->osxEvent_,
                                                kEventParamAttributes,
                                                typeUInt32,
                                                NULL,
                                                sizeof( UInt32 ),
                                                NULL, &attributes );

					if ( err == noErr ) 	{
                        ::Rect currentBounds;
                            GetEventParameter( msg->osxEvent_, kEventParamCurrentBounds, typeQDRectangle,
                                                NULL, sizeof(currentBounds), NULL, &currentBounds);

						if ( attributes & kControlBoundsChangeSizeChanged  ) {

                            VCF::Size sz( abs(currentBounds.right - currentBounds.left),
                                            abs(currentBounds.bottom - currentBounds.top) );
                            result = new ControlEvent( msg->control_, sz );
						}
						else if ( attributes & kControlBoundsChangePositionChanged ) {
							VCF::Point pt( currentBounds.left , currentBounds.top );
                            result = new VCF::ControlEvent( msg->control_, pt );
						}
					}
                }
                break;

                case kEventControlTitleChanged : {

                }
                break;

                case kEventControlOwningWindowChanged : {

                }
                break;

                case kEventControlHiliteChanged : {

                }
                break;

                case kEventControlEnabledStateChanged : {

                }
                break;

                case kEventControlArbitraryMessage : {

                }
                break;
            }
        }
        break;

        case kEventClassCommand : {
            switch ( whatHappened ) {
                case kEventProcessCommand : {
					
					HICommand		command;
					GetEventParameter( msg->osxEvent_, kEventParamDirectObject, typeHICommand, NULL,
									sizeof( HICommand ), NULL, &command );
									
					MenuItem* item = NULL;
					GetMenuCommandProperty( command.menu.menuRef, 
										command.commandID,
										VCF_PROPERTY_CREATOR, 
										OSXMenuItem::propertyTag,
										sizeof(item),
										NULL, &item );				
								
					if ( NULL != item ) {
						
					}										
                }
                break;

                case kEventCommandUpdateStatus : {
					
                }
                break;
            }
        }
        break;

        case kEventClassTablet : {

        }
        break;

        case kEventClassVolume : {

        }
        break;

        case kEventClassAppearance : {
            switch ( whatHappened ) {
                case kEventParamNewScrollBarVariant : {

                }
                break;
            }
        }
        break;

        case kEventClassService : {
            switch ( whatHappened ) {
                case kEventServiceCopy : {

                }
                break;

                case kEventServicePaste : {

                }
                break;

                case kEventServiceGetTypes : {

                }
                break;

                case kEventServicePerform : {

                }
                break;
            }
        }
        break;

        case kEventClassToolbar : {
            switch ( whatHappened ) {
                case kEventParamToolbar : {

                }
                break;

                case kEventParamToolbarItem : {

                }
                break;

                case kEventParamToolbarItemIdentifier : {

                }
                break;

                case kEventParamToolbarItemConfigData : {

                }
                break;
            }
        }
        break;

        case kEventClassToolbarItem : {

        }
        break;

        case kEventClassAccessibility : {

        }
        break;
    }
    return result;
}

EventRef OSXUIToolkit::createUserCarbonEvent( UInt32 eventType )
{
    EventRef result = NULL;

    OSStatus err = CreateEvent( NULL,
                                OSXUIToolkit::CustomEventClass,
                                eventType,
                                0,
                                kEventAttributeUserEvent,
                                &result );

    if ( err != noErr ) {
        printf( "OSXUIToolkit::createUserCarbonEvent CreateEvent failed!\n" );
    }
    else {

    }

    return result;
}

VCF::Size OSXUIToolkit::internal_getDragDropDelta()
{
    Size result;
    return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.8  2004/11/15 05:41:28  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2.2.7  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*Revision 1.2.2.6  2004/11/02 05:19:13  ddiego
*more osx updates for open file dialog.
*
*Revision 1.2.2.5  2004/10/30 20:27:26  ddiego
*added osx color dialog and browse for folder dialog
*
*Revision 1.2.2.4  2004/10/27 03:11:40  ddiego
*integrated chrisk changes
*
*Revision 1.2.2.3  2004/10/25 03:23:57  ddiego
*and even more dialog updates. Introduced smore docs to the dialog class and added a new showXXX function.
*
*Revision 1.2.2.2  2004/10/18 03:10:30  ddiego
*osx updates - add initial command button support, fixed rpoblem in mouse handling, and added dialog support.
*
*Revision 1.2.2.1  2004/10/10 15:23:12  ddiego
*updated os x code
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.11.2.2  2004/07/09 02:01:28  ddiego
*more osx updates
*
*Revision 1.1.2.11.2.1  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.11  2004/06/07 03:07:07  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.1.2.10  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


