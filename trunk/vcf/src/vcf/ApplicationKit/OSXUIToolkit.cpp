//OSXUIToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
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
#include "vcf/ApplicationKit/OSXDropTargetPeer.h"
#include "vcf/ApplicationKit/OSXDragDropPeer.h"
#include "vcf/ApplicationKit/OSXUIShellPeer.h"

#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/OSXListview.h"

#include "vcf/ApplicationKit/OSXPopupMenu.h"
#include "vcf/ApplicationKit/OSXTree.h"

#include "vcf/ApplicationKit/MenuManagerPeer.h"
#include "vcf/ApplicationKit/OSXMenuManagerPeer.h"
#include "vcf/ApplicationKit/OSXTextPeer.h"
#include "vcf/ApplicationKit/OSXTextEditPeer.h"

#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/OSXToolbar.h"
#include "vcf/ApplicationKit/OSXScrollPeer.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/OSXAppResourceBundle.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/OSXAppResourceBundle.h"
#include "vcf/ApplicationKit/OSXCustomControl.h"

#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/OSXPopupWindow.h"

#include "vcf/ApplicationKit/TransparentWindowPeer.h"
#include "vcf/ApplicationKit/OSXTransparentWindow.h"

#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/OSXDropDown.h"

#include "vcf/ApplicationKit/OSXCommonFontDialog.h"

#include "vcf/ApplicationKit/OSXClipboard.h"

#include "vcf/ApplicationKit/SystemTrayPeer.h"
#include "vcf/ApplicationKit/OSXSystemTray.h"

#define kSleepTime	32767
/*
VCF::uint32 translateButtonMask( NSEvent* event )
{
	VCF::uint32 result = 0;
	
	NSUInteger flags = [event modifierFlags];
	
	if ( flags == kEventMouseButtonPrimary ) {
		result = VCF::mbmLeftButton;
	}
	else if ( flags == kEventMouseButtonSecondary ) {
		result = VCF::mbmRightButton;
	}
	else if ( flags == kEventMouseButtonTertiary ) {
		result = VCF::mbmMiddleButton;
	}
	
	return result;
}

VCF::uint32 translateKeyMask( NSEvent* event )
{
    VCF::uint32 result = 0;
	
	NSUInteger flags = [event modifierFlags];
	
    if ( flags & NSShiftKeyMask  ) {
        result |= VCF::kmShift;
    }
	
    if ( flags & NSAlternateKeyMask ) {
        result |= VCF::kmAlt;
    }
	
	if ( flags & NSCommandKeyMask ) {
        result |= VCF::kmCtrl;
    }
	
    if ( flags &  NSControlKeyMask  ) {
        result |= VCF::kmCtrl;
    }
    return result;
}
*/



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
//			double w = Desktop::getDesktop()->getWidth();
//			double h = Desktop::getDesktop()->getHeight();
//			
//			result.left_ = result.right_ = w / 2.0;
//			result.top_ = result.bottom_ = h / 3.0;
//			
//			result.inflate( dialog->getWidth()/2.0, dialog->getHeight()/2.0 );
			
		}
		
		return result;
	}
	
	virtual String transformMnemonicValues( const String& input ) {
		String result = input;
		
		size_t pos = result.find( "&" );
		while ( pos != String::npos ) {
			if ( result[pos+1] != '&' ) {
				result.erase( pos, 1 );
			}
			else {
				pos ++;
			}
			
			pos = result.find( "&", pos +1 );
		}
		
		return result;
	}
	
	virtual AcceleratorKey::Value getStandardAcceleratorFor( const StandardAccelerator& val ) {
		AcceleratorKey::Value result;
		
		switch ( val ) {
			case UIPolicyManager::saApplicationQuit : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterQ );
			}
			break;

			case UIPolicyManager::saApplicationAbout : {
				
			}
			break;

			case UIPolicyManager::saApplicationPreferences : {
				result = AcceleratorKey::Value( kmCtrl,vkComma );
			}
			break;

			case UIPolicyManager::saFileNew : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterN );
			}
			break;

			case UIPolicyManager::saFileOpen : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterO );
			}
			break;

			case UIPolicyManager::saFileSave : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterS );
			}
			break;

			case UIPolicyManager::saFileSaveAs : {
				result = AcceleratorKey::Value( kmCtrl | kmShift,vkLetterS );
			}
			break;

			case UIPolicyManager::saFilePrint : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterP );
			}
			break;

			case UIPolicyManager::saFilePageSetup : {
				result = AcceleratorKey::Value( kmCtrl | kmShift,vkLetterP );
			}
			break;

			case UIPolicyManager::saEditUndo : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterZ );
			}
			break;

			case UIPolicyManager::saEditRedo : {
				result = AcceleratorKey::Value( kmCtrl | kmShift,vkLetterZ );
			}
			break;

			case UIPolicyManager::saEditCut : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterX );
			}
			break;

			case UIPolicyManager::saEditCopy : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterC );
			}
			break;

			case UIPolicyManager::saEditPaste : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterV );
			}
			break;

			case UIPolicyManager::saEditDelete : {
				result = AcceleratorKey::Value( kmUndefined, vkDelete );
			}
			break;

			case UIPolicyManager::saEditSelectAll : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterA );
			}
			break;

			case UIPolicyManager::saEditFind : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterF );
			}
			break;

			case UIPolicyManager::saEditFindNext : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterG );
			}
			break;

			case UIPolicyManager::saHelpContents : {
				result = AcceleratorKey::Value( kmCtrl, vkQuestionMark );
			}
			break;
		}

		return result;
	}
};




};//end of VCF namespace

@interface OSXPostEvent : NSObject {
@public	
	VCF::EventHandler* eventHandler;
	VCF::Event* event;
	bool deleteHandler;
}
@end

@implementation OSXPostEvent
@end



@interface OSXTimerInfo : NSObject 
{
	@public
	
	VCF::EventHandler* eventHandler;
}
@end

@implementation OSXTimerInfo
@end



@interface ToolkitDelegate : NSObject
{
@public
	
}
- (void) handleTimer:(NSTimer*)theTimer;
- (void)handleEvent:(OSXPostEvent*) e;
- (void)didEndSheet:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
@end


@implementation ToolkitDelegate


- (void) postEvent: (NSNotification *)notification
{
	OSXPostEvent* e = [notification object];

	e->eventHandler->invoke( e->event );
	if ( e->deleteHandler ) {
		e->eventHandler->free();
	}
	
	[e release];
}

- (void)didEndSheet:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    [sheet orderOut:self];
}

- (void) handleTimer:(NSTimer*)theTimer
{
	OSXTimerInfo* info = (OSXTimerInfo*) [theTimer userInfo];
	
}

@end


using namespace VCF;



OSXUIToolkit::OSXUIToolkit():
    quitEventLoop_(false),
	toolkitDelegate_(nil),
	rlObserver_(NULL)
{
	policyMgr_ = new OSXUIPolicyManager();
	
	
	
	toolkitDelegate_ = [[ToolkitDelegate alloc] init];
	[[NSNotificationCenter defaultCenter] addObserver:toolkitDelegate_
                                             selector:@selector(postEvent:)
                                                 name:@"OSXUIToolkit_postEvent" 
                                               object:nil];
	
	
	lastRLDate_ = DateTime::now();
	
	CFRunLoopObserverContext ctx = {0};
	ctx.version = 0;
	ctx.info = this;
	
	
	rlObserver_ = CFRunLoopObserverCreate( kCFAllocatorDefault, 
											kCFRunLoopExit, 
										  true, 0, 
										  OSXUIToolkit::handleRunLoopObserver, 
										  &ctx );
	
	
	CFRunLoopAddObserver( CFRunLoopGetMain(), rlObserver_,  kCFRunLoopCommonModes );
	
	
}

OSXUIToolkit::~OSXUIToolkit()
{
	[toolkitDelegate_ release];

    std::map<EventHandler*,NSTimer*>::iterator found = timeoutHandlers_.begin();
    while ( !timeoutHandlers_.empty() ) {
        NSTimer* timer = found->second;
		[timer invalidate];
		[timer release];
    }
	timeoutHandlers_.clear();
	
	CFRelease( rlObserver_ );

    printf( "OSXUIToolkit destroyed\n");
}

ApplicationPeer* OSXUIToolkit::internal_createApplicationPeer()
{
    return new OSXApplicationPeer();
}

TextPeer* OSXUIToolkit::internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined )
{
	return new OSXTextPeer(autoWordWrap,multiLined);
}

TextEditPeer* OSXUIToolkit::internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl )
{
	return new OSXTextEditPeer(component,isMultiLineControl);
}
	
	
TreePeer* OSXUIToolkit::internal_createTreePeer( TreeControl* component )
{
    return new OSXTree(component);
}

ListviewPeer* OSXUIToolkit::internal_createListViewPeer( ListViewControl* component )
{
    return new OSXListview(component);
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
			result = new OSXCustomControl( control );
		}
		break;
	}
	return result;	
}

WindowPeer* OSXUIToolkit::internal_createWindowPeer( Control* control, Control* owner )
{
    return new OSXWindow( control, owner );
}

PopupWindowPeer* OSXUIToolkit::internal_createPopupWindowPeer( Frame* frame, Window* owner )
{
    return new OSXPopupWindow(frame,owner);
}

TransparentWindowPeer* OSXUIToolkit::internal_createTransparentWindowPeer( Frame* frame )
{
    return new OSXTransparentWindow(frame);
}

DropDownPeer* OSXUIToolkit::internal_createDropDownPeer( Control* control )
{
	return new OSXDropDown(control);
}


ToolbarPeer* OSXUIToolkit::internal_createToolbarPeer( Toolbar* toolbar )
{
    return new OSXToolbar(toolbar);
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
    return new OSXPopupMenu(popupMenu);
}

ButtonPeer* OSXUIToolkit::internal_createButtonPeer( CommandButton* component )
{
    return new OSXButton( component );
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
    return new OSXFontDialog(owner);
}

DragDropPeer* OSXUIToolkit::internal_createDragDropPeer()
{
    return new OSXDragDropPeer();
}

DataObjectPeer* OSXUIToolkit::internal_createDataObjectPeer()
{
    return NULL;
}

DropTargetPeer* OSXUIToolkit::internal_createDropTargetPeer()
{
    return new OSXDropTargetPeer();
}

ScrollPeer* OSXUIToolkit::internal_createScrollPeer( Control* control )
{
    return new OSXScrollPeer(control);
}

GraphicsResourceBundlePeer* OSXUIToolkit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new OSXAppResourceBundle( app );
}

SystemTrayPeer* OSXUIToolkit::internal_createSystemTrayPeer()
{
	return new OSXSystemTray();
}

MenuManagerPeer* OSXUIToolkit::internal_createMenuManagerPeer()
{
	return new OSXMenuManagerPeer();
}

CommonPrintDialogPeer* OSXUIToolkit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return NULL;
}

UIShellPeer* OSXUIToolkit::internal_createUIShellPeer( UIShell* shell )
{
    return new OSXUIShellPeer( shell );
}

CursorPeer* OSXUIToolkit::internal_createCursorPeer( Cursor* cursor )
{
    return new OSXCursorPeer(cursor);
}

ClipboardPeer* OSXUIToolkit::internal_createClipboardPeer()
{
    return new OSXClipboard();
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
	
	OSXPostEvent* pe = [[OSXPostEvent alloc] init];
	pe->eventHandler = eventHandler;
	pe->event = event;
	pe->deleteHandler = deleteHandler;
	
	NSNotification* todo = [NSNotification notificationWithName:@"OSXUIToolkit_postEvent" 
                                                         object: pe ];
    [[NSNotificationQueue defaultQueue] enqueueNotification:todo
                                               postingStyle:NSPostWhenIdle];
	
	
}

void OSXUIToolkit::internal_registerTimerHandler( Object* source, VCF::EventHandler* handler, const uint32& timeoutInMilliSeconds )
{
	NSRunLoop* runLoop = [NSRunLoop mainRunLoop];
	double timeout = (double)timeoutInMilliSeconds / 1000.0;
	
	
	OSXTimerInfo* info = [[OSXTimerInfo alloc] init];
	info->eventHandler = handler;
	
	NSTimer* timer = [NSTimer timerWithTimeInterval: timeout target:toolkitDelegate_ selector: @selector(handleTimer:) userInfo: info repeats:YES];
	
	
	timeoutHandlers_[handler] = timer;
	
	[runLoop addTimer: timer forMode:NSDefaultRunLoopMode];
}

void OSXUIToolkit::internal_unregisterTimerHandler( VCF::EventHandler* handler )
{
	std::map<EventHandler*,NSTimer*>::iterator found = timeoutHandlers_.find( handler );
	if ( found != timeoutHandlers_.end() ) {
		NSTimer* timer = found->second;
		[timer invalidate];
		[timer release];
	}	
}

void OSXUIToolkit::handleRunLoopObserver ( CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info )
{
	OSXUIToolkit* thisPtr = (OSXUIToolkit*)info;

	NSEvent *event = [NSApp nextEventMatchingMask: NSAnyEventMask 
										untilDate: [NSDate date] inMode: NSDefaultRunLoopMode
										  dequeue:NO];
	DateTime dt = DateTime::now();
	
	DateTimeSpan span = dt - thisPtr->lastRLDate_;	
		
	if ( span.getTotalMilliseconds() > 500 ) {
		if ( !event ) {
			//NSLog( @"doIdle called on Controller instance activity: %d!", activity );
			
			thisPtr->internal_idleTime();
			
			Application* runningApp = Application::getRunningInstance();
			
			if ( NULL != runningApp ) {
				runningApp->idleTime();
			}
			
			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}
			
			thisPtr->lastRLDate_ = DateTime::now();			
		}
	}	
}

bool OSXUIToolkit::handleAppEvents( NSEvent* event )
{
	bool result = true;
	
	internal_idleTime();
	
	Application* runningApp = Application::getRunningInstance();
	
	if ( NULL != runningApp ) {
		runningApp->idleTime();
	}
	
	//check library apps;
	Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
	while ( true == registeredLibs->hasMoreElements() ) {
		LibraryApplication* libraryApp = registeredLibs->nextElement();
		libraryApp->idleTime();
	}
	
	
	
	return result;
}

void OSXUIToolkit::internal_runEventLoop()
{
    //set to false to begin with
    quitEventLoop_ = false;
	
	NSApplication* app = [NSApplication sharedApplication];
	[app run];
	
    //reset back to false when finished
    quitEventLoop_ = false;
}

UIToolkit::ModalReturnType OSXUIToolkit::internal_runModalEventLoopFor( Control* control )
{
	Frame* ownerFrame = control->getParentFrame();
		
	UIToolkit::ModalReturnType result = UIToolkit::mrTrue;
	
	
	NSWindow* peerWnd = (NSWindow*) ownerFrame->getPeer()->getHandleID();
	
	Dialog* dialogFrame = dynamic_cast<Dialog*> (ownerFrame);
	bool asSheet = false;
	if ( NULL != dialogFrame ) {
		asSheet = dialogFrame->isSheetModal();
	}
	
	if ( asSheet ) {
		
		Frame* sheetOwner = dialogFrame->getOwner()->getParentFrame();
		NSWindow* modalWindow = (NSWindow*) sheetOwner->getPeer()->getHandleID();
		
		
		[NSApp beginSheet: peerWnd
		   modalForWindow: modalWindow
			modalDelegate: toolkitDelegate_
		   didEndSelector: @selector(didEndSheet:returnCode:contextInfo:)
			  contextInfo: nil];
	}
	else {
		NSInteger returnCode = [NSApp runModalForWindow: peerWnd];
		if ( returnCode > 0 ) {
			result = (UIToolkit::ModalReturnType) returnCode;
		}
	}
	
    return result;
}

void OSXUIToolkit::internal_quitCurrentEventLoop()
{
    //EventLoopRef currentLoop = GetCurrentEventLoop();
    //QuitEventLoop( currentLoop );
	NSApplication* app = [NSApplication sharedApplication];
	[app stop: app];
	
    quitEventLoop_ = true;
}

VCF::Event* OSXUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
    VCF::Event* result = NULL;
	/*
	OSXEventMsg* msg = (OSXEventMsg*) eventData;
	
	NSEventType type = [msg->event type];
	switch ( type ) {
		case NSLeftMouseDown: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_DOWN,VCF::mbmLeftButton,
												translateKeyMask( msg->event ), &pt );
			}
		}
		break;
		
		case NSLeftMouseUp: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_UP,VCF::mbmLeftButton,
												translateKeyMask( msg->event ), &pt );
			}		
		}
		break;
		
		case NSRightMouseDown: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_DOWN,VCF::mbmRightButton,
												translateKeyMask( msg->event ), &pt );
			}
		}
		break;
		
		case NSRightMouseUp: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_UP,VCF::mbmRightButton,
												translateKeyMask( msg->event ), &pt );
			}
		}
		break;
		
		case NSOtherMouseDown: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_DOWN,translateButtonMask(msg->event),
												translateKeyMask( msg->event ), &pt );
			}
		}
		break;
		
		case NSOtherMouseUp: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_UP,translateButtonMask(msg->event),
												translateKeyMask( msg->event ), &pt );
			}
		}
		break;
		
		case NSMouseMoved: {
			if ( msg->view != nil ) {
				NSPoint location = [msg->event locationInWindow];
				NSPoint local = [msg->view convertPoint:location fromView:nil];
				Point pt(local.x, local.y);
				
				result = new VCF::MouseEvent( msg->control, Control::MOUSE_UP,translateButtonMask(msg->event),
												translateKeyMask( msg->event ), &pt );
			}
		}
		break;
		
		case NSLeftMouseDragged: {
		
		}
		break;
		
		case NSRightMouseDragged: {
		
		}
		break;
		
		case NSOtherMouseDragged: {
		
		}
		break;
		
		case NSMouseEntered: {
		
		}
		break;
		
		case NSMouseExited: {
		
		}
		break;
		
		case NSKeyDown: {
		
		}
		break;
		
		case NSKeyUp: {
		
		}
		break;
		
	}
	*/
  /*
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
											OSXUIUtils::translateButtonMask( button ),
											OSXUIUtils::translateKeyMask( keyboardModifier ), &pt );

                }
                break;

                case kEventMouseUp : {
                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_UP,
											OSXUIUtils::translateButtonMask( button ),
											OSXUIUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventMouseMoved : {

                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
                                                OSXUIUtils::translateButtonMask( button ),
                                                OSXUIUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventMouseDragged : {
					Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }
                    
                    result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
                                                OSXUIUtils::translateButtonMask( button ),
                                                OSXUIUtils::translateKeyMask( keyboardModifier ), &pt );
                }
                break;

                case kEventMouseEntered : {
                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_ENTERED,
                                                    OSXUIUtils::translateButtonMask( 0 ),
                                                    OSXUIUtils::translateKeyMask( 0 ), &pt );
                }
                break;

                case kEventMouseExited : {
                    Scrollable* scrollable = msg->control_->getScrollable();
                    if ( NULL != scrollable ) {
                        pt.x_ += scrollable->getHorizontalPosition();
                        pt.y_ += scrollable->getVerticalPosition();
                    }

                    result = new VCF::MouseEvent( msg->control_, Control::MOUSE_LEAVE,
                                                    OSXUIUtils::translateButtonMask( 0 ),
                                                    OSXUIUtils::translateKeyMask( 0 ), &pt );
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
					uint32 keyMask = 0;

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

					StringUtils::trace( Format("keyMask: %d, virtKeyValue: %d\n") %
												keyMask% virtKeyValue );
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
					uint32 keyMask = 0;

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
                    result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_DESTROYED );
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
					result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_DESTROYED );
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
                                                OSXUIUtils::translateKeyMask( 0 ), &pt );

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
                                                OSXUIUtils::translateKeyMask( keyboardModifier ), &pt );
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
	*/
    return result;
}

VCF::Size OSXUIToolkit::internal_getDragDropDelta()
{
    Size result(5,5);
    return result;
}

void OSXUIToolkit::internal_displayHelpContents( const String& helpBookName, const String& helpDirectory )
{

}

void OSXUIToolkit::internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory )
{

}

bool OSXUIToolkit::internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory )
{
	return false;
}

void OSXUIToolkit::internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection )
{

}

void OSXUIToolkit::internal_systemSettingsChanged()
{

}


/**
$Id$
*/
