//Win32ToolKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32ToolKit.h"
#include "vcf/ApplicationKit/Win32Application.h"
#include "vcf/ApplicationKit/Win32Edit.h"
#include "vcf/ApplicationKit/Win32Tree.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/Win32Listview.h"
#include "vcf/ApplicationKit/HTMLBrowserPeer.h"
#include "vcf/ApplicationKit/Win32Dialog.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"
#include "vcf/ApplicationKit/Win32MenuBar.h"
#include "vcf/ApplicationKit/Win32Button.h"
#include "vcf/ApplicationKit/Win32ControlContext.h"
#include "vcf/ApplicationKit/Win32FileOpenDialog.h"
#include "vcf/ApplicationKit/Win32FileSaveDialog.h"
#include "vcf/ApplicationKit/Win32ColorDialog.h"
#include "vcf/ApplicationKit/Win32FolderBrowseDialog.h"
#include "vcf/ApplicationKit/Win32DropTargetPeer.h"
#include "vcf/ApplicationKit/Win32Clipboard.h"
#include "vcf/ApplicationKit/Win32PopupMenu.h"
#include "vcf/ApplicationKit/Win32FontDialog.h"
#include "vcf/ApplicationKit/Win32Desktop.h"
#include "vcf/ApplicationKit/Win32ScrollPeer.h"
#include "vcf/ApplicationKit/Win32CursorPeer.h"
#include "vcf/ApplicationKit/LightweightComponent.h"
#include "vcf/ApplicationKit/Win32Component.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/ApplicationKit/Win32DragDropPeer.h"
#include "vcf/ApplicationKit/COMUtils.h"
#include "vcf/ApplicationKit/Win32Toolbar.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/SystemTrayPeer.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/Win32AppResourceBundle.h"

#include <shellapi.h>
#include "vcf/ApplicationKit/Win32SystemTrayPeer.h"

//printing
#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/Win32PrintSession.h"
#include "vcf/ApplicationKit/Win32PrintDialog.h"


#include "vcf/ApplicationKit/Win32TextPeer.h"

#include "vcf/ApplicationKit/MenuManagerPeer.h"
#include "vcf/ApplicationKit/Win32MenuManagerPeer.h"



#ifdef _LIB
    /* a user not defining USE_WIN32HTMLBROWSER_LIB will not be able to
       link the Win32HTMLBrowser_StaticLib, but also he will not have to
       link to it either if is not using it in any of his projects */
#   ifdef USE_WIN32HTMLBROWSER_LIB
//     ApplicationKit statically linked in
#      include "vcf/ApplicationKit/Win32HTMLBrowserApplication.h"
#      pragma message ( "Win32HTMLBrowser is linked in statically" )
#   endif
#else
    /* Win32HTMLBrowser will be loaded at runtime */
#   define RUNTIME_LOADLIBRARY
#   pragma message ( "Win32HTMLBrowser is linked dynamically" )
#endif



#include "vcf/ApplicationKit/Win32HTMLBrowserSelectLib.h"


using namespace VCF;
using namespace VCFWin32;


#define TOOLTIP_TIMERID					30565
#define TOOLTIP_TIMEOUT_TIMERID			30566

static UINT ToolTipTimerID = 0;
static UINT ToolTipTimoutTimerID = 0;

static UINT VCF_POST_EVENT = 0;

HINSTANCE Win32ToolKit_toolkitHInstance = NULL;

#ifndef _LIB //DLL Linkage...

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {
			Win32ToolKit_toolkitHInstance = (HINSTANCE)hModule;
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {

		}
		break;
    }
    return TRUE;
}

#endif





//UIPolicyManager implementation

class Win32UIPolicyManager : public UIPolicyManager {
public:
	Win32UIPolicyManager() {

	}

	virtual ~Win32UIPolicyManager() {

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

		return result;
	}

	virtual Frame* getOwnerForDialog() {
		Frame* result = NULL;
		Frame* activeFrame = Frame::getActiveFrame();

		Application* app = Application::getRunningInstance();

		if ( NULL != activeFrame ) {
			result = activeFrame;
		}
		else if ( NULL != app ) {
			result = app->getMainWindow();
		}

		return result;
	}

	/**
	* merges two menus by adding to the menu items of windowMenu
	* all the items and subitems of appMenu that are not in windowMenu.
	*/
	virtual void mergeMenus( Menu* appMenu, Menu* windowMenu ) {
		MenuItem* windowRoot = windowMenu->getRootMenuItem();
		MenuItem* appRoot = appMenu->getRootMenuItem();
		// add all the first level menu items from appMenu to windowMenu
		Enumerator<MenuItem*>* appChildren = appRoot->getChildren();
		while ( appChildren->hasMoreElements() ) {
			MenuItem* child = appChildren->nextElement();

			MenuItem* matchingChild = getMatchingMenuItem( child, windowRoot );
			if ( NULL == matchingChild ) {
				matchingChild = (MenuItem*)child->clone();// new DefaultMenuItem2( child->getCaption(), windowRoot, windowRoot->getMenuOwner() );
				matchingChild->setMenuOwner( windowRoot->getMenuOwner() );

				String caption = StringUtils::lowerCase( matchingChild->getCaption() );

				if ( String::npos != caption.find( "file" ) ) {
					windowRoot->insertChild( 0, matchingChild );
				}
				else if ( String::npos != caption.find( "edit" ) ) {
					windowRoot->insertChild( 1, matchingChild );
				}
				else {
					windowRoot->addChild( matchingChild );
				}
			}

			// now merges the subitems of the first level menu items
			copyMenuItems( child, matchingChild );

		}
	}

	/**
	*
	*/
	virtual String transformMnemonicValues( const String& input ) {
		return input;
	}

	virtual AcceleratorKey::Value getStandardAcceleratorFor( const StandardAccelerator& val ) {
		AcceleratorKey::Value result;

		switch ( val ) {
			case UIPolicyManager::saApplicationQuit : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterQ );
			}
			break;

			case UIPolicyManager::saApplicationAbout : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterQ );
			}
			break;

			case UIPolicyManager::saApplicationPreferences : {

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

			}
			break;

			case UIPolicyManager::saEditUndo : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterZ );
			}
			break;

			case UIPolicyManager::saEditRedo : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterY );
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
				result = AcceleratorKey::Value( kmUndefined, vkF3 );
			}
			break;

			case UIPolicyManager::saHelpContents : {
				result = AcceleratorKey::Value( kmUndefined, vkF1 );
			}
			break;
		}

		return result;
	}
protected:

	/**
	* adds to the menu items of windowItem all the items of appItem that are not in windowItem.
	* In other words, it appends all the submenu items of appItem as subitems of the windowItem
	* except for the subitems already existing in the subitems of the windowItem.
	*@param MenuItem* appItem, the menu item in the 'source' menu
	*@param MenuItem* windowItem, the menu item in the 'destination' menu
	*/
	void copyMenuItems( MenuItem* appItem, MenuItem* windowItem ) {

		Enumerator<MenuItem*>* appChildren = appItem->getChildren();
		while ( appChildren->hasMoreElements() ) {
			MenuItem* child = appChildren->nextElement();

			if ( NULL == getMatchingMenuItem( child, windowItem ) ) {
				MenuItem* newChild = (MenuItem*)child->clone();
				newChild->setMenuOwner( windowItem->getMenuOwner() );
				windowItem->addChild( newChild );

					//new DefaultMenuItem( child->getCaption(), windowItem, windowItem->getMenuOwner() );
				//we need to be able to copy over event handlers??? HOW ?????

			}
		}
	}


	/**
	* search between the subitems of appItem a subitem having the same caption
	* or the same tag of the window's item to search,
	* no search is performed if appItem is a menu separator.
	*@param MenuItem* appItem, the menu item in the 'source' menu
	*@param MenuItem* windowItemToSearch, the menu item to search
	*/
	MenuItem* getMatchingMenuItem( MenuItem* appItem, MenuItem* windowItemToSearch ) {
		MenuItem* result = NULL;

		Enumerator<MenuItem*>* children = windowItemToSearch->getChildren();
		while ( children->hasMoreElements() ) {


			MenuItem* child = children->nextElement();

			String appItemCaption   = StringUtils::eraseRightOfChar( appItem->getCaption(), '\t', true );
			String childItemCaption = StringUtils::eraseRightOfChar( child->getCaption(), '\t', true );

			if ( ( childItemCaption == appItemCaption ) && (!child->isSeparator()) ) {
				result = child;
				break;
			}
			else if ( (child->getTag() == appItem->getTag()) && (child->getTag()!= -1) ) {
				result = child;
				break;
			}
			else if ( appItem->isSeparator() && child->isSeparator() ) {
				result = NULL;
				break;
			}
		}

		return result;
	}
};


//UIMetricsManager implementation
class Win32UIMetricsManager : public UIMetricsManager {
public:

	static Point DLUToPixel( const Point& dlu, VCF::Font& font ) {
		Point result;
		HDC dc = GetDC( ::GetDesktopWindow() );

		int baseUnitY = 0;
		int cx = 0;

		HFONT hf = NULL;
		HFONT old = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) font.getFontPeer()->getFontHandleID();
			hf = ::CreateFontIndirectW( lf );


			old = (HFONT)SelectObject(dc, hf );

			TEXTMETRICW tm;
			GetTextMetricsW( dc, &tm );
			baseUnitY = tm.tmHeight;
			SIZE sz;
			::GetTextExtentPointW( dc,
								L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
								52, &sz );

			cx = sz.cx;
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) font.getFontPeer()->getFontHandleID();
			hf = ::CreateFontIndirectA( lf );

			old = (HFONT)SelectObject(dc, hf );

			TEXTMETRICA tm;
			GetTextMetricsA( dc, &tm );
			baseUnitY = tm.tmHeight;
			SIZE sz;
			::GetTextExtentPointA( dc,
								"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
								52, &sz );

			cx = sz.cx;
		}




		int baseUnitX = (cx / 26 + 1) / 2;
		result.x_ = MulDiv(dlu.x_, baseUnitX, 4);
		result.y_ = MulDiv(dlu.y_, baseUnitY, 8);

		//(dlu.x_ * baseUnitX) / 4;
		//result.y_  = (dlu.y_ * baseUnitY) / 8;

		SelectObject(dc, old );
		DeleteObject( hf );
		ReleaseDC( ::GetDesktopWindow(), dc );


		return result;
	}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type ) {
		VCF::Font result;

		NONCLIENTMETRICSA ncm;
		memset( &ncm, 0, sizeof(ncm) );

		ncm.cbSize = sizeof(ncm);

		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMenuFont.lfFaceName ) ;
					result.setBold( ncm.lfMenuFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_MENUTEXT ) ) );
					result.setItalic( ncm.lfMenuFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMenuFont.lfHeight );
					result.setStrikeOut( ncm.lfMenuFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMenuFont.lfUnderline ? true : false );
				}
				//
			}
			break;

			case UIMetricsManager::ftSelectedMenuItemFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMenuFont.lfFaceName ) ;
					result.setBold( ncm.lfMenuFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_HIGHLIGHTTEXT ) ) );
					result.setItalic( ncm.lfMenuFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMenuFont.lfHeight );
					result.setStrikeOut( ncm.lfMenuFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMenuFont.lfUnderline ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftControlFont :  case UIMetricsManager::ftSystemFont : {
				//do nothing the Win32Font already is initialized ot this by default
				result.setColor( &Color( ::GetSysColor( COLOR_WINDOWTEXT ) ) );
			}
			break;

			case UIMetricsManager::ftMessageFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMessageFont.lfFaceName ) ;
					result.setBold( ncm.lfMessageFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_WINDOWTEXT ) ) );
					result.setItalic( ncm.lfMessageFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMessageFont.lfHeight );
					result.setStrikeOut( ncm.lfMessageFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMessageFont.lfUnderline ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftToolTipFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfStatusFont.lfFaceName ) ;
					result.setBold( ncm.lfStatusFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_INFOTEXT ) ) );
					result.setItalic( ncm.lfStatusFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfStatusFont.lfHeight );
					result.setStrikeOut( ncm.lfStatusFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfStatusFont.lfUnderline ? true : false );
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
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				//result = f.getHeight();// * 1.75;
				Point pt = DLUToPixel( Point(0,11), f );
				result = pt.y_;
			}
			break;

			case UIMetricsManager::htComboBoxHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				Point pt = DLUToPixel( Point(0,12), f );
				result = pt.y_;

			}
			break;

			case UIMetricsManager::htListItemHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				Point pt = DLUToPixel( Point(0,9), f );
				result = pt.y_;
			}
			break;

			case UIMetricsManager::htButtonHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = (f.getHeight() * 1.75) + 2.50;

				Point pt = DLUToPixel( Point(0,14), f );
				result = pt.y_;
			}
			break;

			case UIMetricsManager::htRadioBoxHeight : case UIMetricsManager::htCheckBoxHeight : {
				/**
				JC
				Stripped this all out  -
				it turns out that the height/width is ALWAYS 13 pixels - no matter what
				the DPI is
				GetSystemMetrics( SM_CXMENUCHECK ) returns a value that changes based on the DPI
				13 at 96 DPI and 17 at 120 DPI
				*/
				result = 13;
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
				Point pt = DLUToPixel( Point(0,11), f );
				result = pt.y_;//f.getHeight() * 1.75;
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
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				Point pt = DLUToPixel( Point(0,7), f );
				result = pt.y_;
			}
			break;

			case UIMetricsManager::stContainerBorderDelta : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				Point pt = DLUToPixel( Point(0,5), f );

				result = pt.y_;
			}
			break;

			case UIMetricsManager::stControlVerticalSpacing : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				Point pt = DLUToPixel( Point(0,4), f );
				result = pt.y_;
			}
			break;

			case UIMetricsManager::stControlHorizontalSpacing : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				Point pt = DLUToPixel( Point(5,0), f );
				result = pt.x_;
			}
			break;

			case UIMetricsManager::stInformationControlTopSpacer : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftMessageFont );
				Point pt = DLUToPixel( Point(0,2), f );
				result = pt.y_;
			}
			break;

			case UIMetricsManager::stInformationControlBottomSpacer : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftMessageFont );
				Point pt = DLUToPixel( Point(0,1), f );
				result = pt.y_;
			}
			break;
		}

		return result;
	}

	virtual Size getDefaultSliderThumbDimensions()  {
		Size result;

		result.width_ = ::GetSystemMetrics( SM_CXHTHUMB )*0.85+1;
		result.height_ = ::GetSystemMetrics( SM_CYVTHUMB );

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )  {
		Size result;

		NONCLIENTMETRICSA ncInfo;
		ncInfo.cbSize = sizeof(ncInfo);
		::SystemParametersInfoA (SPI_GETNONCLIENTMETRICS, sizeof(ncInfo), &ncInfo, 0);
		HFONT menuHFont = CreateFontIndirectA( &ncInfo.lfMenuFont );
		if ( NULL != menuHFont ) {
			HDC dc = ::CreateCompatibleDC( NULL );// screen DC--I won't actually draw on it
			HFONT oldFont = (HFONT)SelectObject( dc, menuHFont );
			RECT rcText = {0,0,0,0};
			if ( System::isUnicodeEnabled() ) {
				::DrawTextW( dc, caption.c_str(), caption.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
			}
			else {
				AnsiString tmp = caption;
				::DrawTextA( dc, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
			}


			SelectObject( dc, oldFont );

			// height of item is just height of a standard menu item
			result.height_ = __max( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );

			const int CXGAP = 1;		// num pixels between button and text
			const int CXTEXTMARGIN = 2;		// num pixels after hilite to start text
			const int CXBUTTONMARGIN = 2;		// num pixels wider button is than bitmap
			const int CYBUTTONMARGIN = 2;		// ditto for height

			// width is width of text plus a bunch of stuff
			int cx = rcText.right - rcText.left;	// text width
			cx += CXTEXTMARGIN << 1;		// L/R margin for readability
			cx += CXGAP;					// space between button and menu text

			//cx += szButton_.cx<<1;		// button width (L=button; R=empty margin)

			// whatever value I return in lpms->itemWidth, Windows will add the
			// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
			//
			cx += GetSystemMetrics(SM_CXMENUCHECK)-1;
			result.width_ = cx;		// done deal

			::DeleteObject( menuHFont );
			::DeleteDC( dc );
		}

		return result;
	}

	virtual Size getDefaultVerticalScrollButtonDimensions()  {
		Size result;

		int w = ::GetSystemMetrics( SM_CXHTHUMB );
		if ( (w % 2) == 0 ) {
			w ++;
		}
		result.width_ = w;
		result.height_ = ::GetSystemMetrics( SM_CYVTHUMB );

		NONCLIENTMETRICS ncm;
		memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
		ncm.cbSize = sizeof(NONCLIENTMETRICS);

		SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );

		result.width_ = ncm.iScrollWidth;

		return result;
	}

	virtual Size getDefaultHorizontalScrollButtonDimensions()  {
		Size result;

		result.width_ = ::GetSystemMetrics( SM_CXHTHUMB );
		result.height_ = ::GetSystemMetrics( SM_CYVTHUMB );

		return result;
	}

	virtual Size getDefaultTabDimensions( const String& caption )  {
		Size result;

		return result;
	}
};








/**
*used by the ToolKitHookWndProc andthe construcor for Win32ToolKit()
*/
static HHOOK hookHandle;

class Win32PostEventRecord {
public:
	Win32PostEventRecord( EventHandler* handler, Event* event, bool deleteHandler ) {
		handler_ = handler;
		event_ = event;
		deleteHandler_ = deleteHandler;
	}

	virtual ~Win32PostEventRecord() {
		delete event_;
		event_ = NULL;
		if ( true == deleteHandler_ ) {
			delete handler_;
		}
		handler_ = NULL;
	}

	EventHandler* handler_;
	Event* event_;
	bool deleteHandler_;
};




class Win32ToolTip : public Window {
public:
	Win32ToolTip() {
		Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();

		setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP ) );
		getFont()->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP_TEXT ) );
		setFrameStyle( fstNoBorderFixed );
		setFrameTopmost( true );

		setUseColorForBackground( true );

		getPeer()->setText( "Win32ToolTip" );
	};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );
		ctx->setColor( Color::getColor( "black" ) );
		Rect r(0,0,getWidth() - 1.0, getHeight() - 1.0 );
		ctx->rectangle( &r );
		ctx->strokePath();

		r.inflate( -1, -1 );

		ctx->setCurrentFont( getFont() );

		long drawingOptions = GraphicsContext::tdoCenterHorzAlign | GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &r, getCaption(), drawingOptions );
	}

	virtual void mouseClick( MouseEvent* e ) {
		hide();
	}

	virtual void mouseDown( MouseEvent* e ) {
		hide();
	}

	virtual bool allowsActivation() {
		return false;
	}
};

class ToolTipWatcher : public ObjectWithEvents {
public:
	ToolTipWatcher() {
		currentControlWithTooltip_ = NULL;

		toolTip_ = NULL;

		if ( NULL == toolTip_ ) {
			toolTip_ = new Win32ToolTip();

			//toolTip_->setVisible( false );
			toolTip_->FrameActivation.addHandler( new WindowEventHandler<ToolTipWatcher>( this,
													&ToolTipWatcher::onToolTipLostFocus,
													"toolTipWatcherHandler" ) );

			Frame* f = Window::getActiveFrame();
			//toolTip_->setParent( f );
		}

	}

	virtual ~ToolTipWatcher() {
		if ( NULL != toolTip_ ) {
			toolTip_->free();
		}
	}

	Control* getActualToolTipControl( Control* control, Point* pt ) {
		Control* result = NULL;

		Container* container = control->getContainer();
		if ( NULL != container ) {
			Enumerator<Control*>* children = container->getChildren();
			bool found = false;
			while ( (true == children->hasMoreElements()) && (false == found) ) {
				Control* child = children->nextElement();
				if ( true == child->isLightWeight() ) {
					Rect bounds = child->getBounds();
					if ( true == bounds.containsPt( pt ) ) {
						Point tmpPt = *pt;
						child->translateToLocal( &tmpPt );
						result = getActualToolTipControl( child, &tmpPt );
						if ( NULL != result  ) {
							found = true;//quit the loop
						}
					}
				}
			}
			if ( (false == found) && (NULL == result) ) {
				result = control;
			}
		}
		else {
			result = control;
		}

		return result;
	}

	void showTooltip( Control* control, Point* pt ) {


		//pt is in screen coordinates
		Point tmpPt = *pt;
		control->translateFromScreenCoords( &tmpPt );

		Control* actualToolTipControl = getActualToolTipControl( control, &tmpPt );
		if ( NULL == actualToolTipControl ) {
			return;// nothing to do
		}


		String tooltip = actualToolTipControl->getToolTipText();

		ToolTipEvent tooltipEvent( actualToolTipControl, 0 );
		tooltipEvent.setToolTipLocation( pt );
		tooltipEvent.setCustomTooltipContext( toolTip_->getContext() );
		Size sz;
		tooltipEvent.setToolTipSize( &sz );

		if ( true == tooltip.empty() ) {
			//fire a tooltip requested
			tooltipEvent.setType( TOOLTIP_EVENT_TIP_REQESTED );

			actualToolTipControl->ToolTipRequested.fireEvent( &tooltipEvent );

			tooltip = tooltipEvent.getToolTipString();

			tooltipEvent.setType( 0 );
		}

		if ( false == tooltip.empty() ) {

			actualToolTipControl->ToolTip.fireEvent( &tooltipEvent );
			Point tmpPt = *tooltipEvent.getToolTipLocation();



			toolTip_->setLeft( tmpPt.x_ );
			toolTip_->setTop( tmpPt.y_ );

			sz = *tooltipEvent.getToolTipSize();
			if ( sz.height_ > 0.0 ) {
				toolTip_->setHeight( sz.height_ );
			}
			else {
				toolTip_->setHeight( toolTip_->getContext()->getTextHeight( "EM" ) + 5 );
			}

			if ( sz.width_ > 0.0 ) {
				toolTip_->setWidth( sz.width_ );
			}
			else {
				toolTip_->setWidth( toolTip_->getContext()->getTextWidth( tooltip ) + 10 );
			}

			if ( toolTip_->getParent() == NULL ) {
				//toolTip_->setParent(  );
			}

			toolTip_->setCaption( tooltip );
			toolTip_->show();
			//toolTip_->setFrameTopmost( true );
			currentControlWithTooltip_ = actualToolTipControl;
		}
	}

	void onToolTipLostFocus( WindowEvent* e ) {
		Window* w = (Window*)e->getSource();

		if ( false == w->isActive() ) {
			w->hide();
		}
	};

	Win32ToolTip* toolTip_;
	Point checkPt_;
	Control* currentControlWithTooltip_;
};

static ToolTipWatcher* toolTipWatcher = NULL;

LRESULT CALLBACK ToolKitHookWndProc( int nCode, WPARAM wParam, LPARAM lParam );


/**
*this is a weird case that Win32 gives us, so here's the deal:
*A hidden dummy window, whose parent is the Desktop, is created and made
*available as a temporary parent to Peers before the created window is actually
*hooked into into the real parent. What seems to happen with the common controls
*is the first parent hwnd sent in to the control when it is first created is the
*one to which all future WM_NOTIFY messages are sent to. This is fine and well if
*you are writing a big fat SDK switch statement (like the one you're looking at now :),
*but really sucks if you have your code broken up into a well organized
*framework (like I am attempting to build here ! ). What this means is
*that Control objects can never handle their own notifications!
*So the code below exists to route those messages back to the child Win32Object
*where they are handled. So to facilitate this we'll do our processing here
*(which at the moment is nothing) and then pass the message right back to the
*child that sent it !
*First the lParam is typecasted into a NMHDR structure. This gives us access to
*the hwnd and hopefully the Win32Object. If we have a valid Win32Object then we
*call the Win32Object::handleEventMessages(), passing the NMHDR.code field as the
*reflected window message, the original wParam, which gets ignored anyways, and
*the original lParam, which upon arriving back at the child control will again
*get typcast back to some other notification structure.
*PS: Yes, this is one of the biggest hacks I've seen  ;-)
*PPS This also works for WM_COMMAND messages as well
*/
LRESULT CALLBACK Win32ToolKit::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch ( message ){

		case WM_INPUTLANGCHANGE : {
			StringUtils::trace( "WM_INPUTLANGCHANGE\n" );
		}
		break;

		case WM_ACTIVATEAPP: {

			BOOL fActive = (BOOL) wParam;

			/**
			this is a total hack to get around the fact that if I create the dummyParentWnd_
			with a WS_CHILD style it causes a WM_NCACTIVATE with a active=0 to teh new popup
			window, which de-activates the caption bar and focus. However if I change the
			creation style to WS_POPUP it avoids the above, but then any time a popup window
			(like that of the ComboBox popup) is created it causes the main parent window to
			lose focus. So...create the dummyParentWnd_ with a WS_POPUP style to avoid the first
			goof, and then switch it back to a WS_CHILD style here to avoid the other goof.
			Of course, ideally it would be nice to never get either goof, but...
			*/
			static bool changeStyle = true;

			if ( changeStyle ) {
				Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
				long style = ::GetWindowLong( toolkit->dummyParentWnd_, GWL_STYLE );
				if ( style & WS_POPUP ) {
					style &= ~WS_POPUP;
					style |= WS_CHILD;
					::SetWindowLong( toolkit->dummyParentWnd_, GWL_STYLE, style );
					::SetWindowPos( toolkit->dummyParentWnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
				}
			}
			changeStyle = false;

			if ( fActive ) {

				ToolTipTimerID = ::SetTimer( hWnd, TOOLTIP_TIMERID, 500, NULL );
				Frame* activeFrame = Frame::getActiveFrame();

				if ( NULL != activeFrame ) {
					/** - MP -
					REMARK: if we break here with a crash of the application, we probably had the
					crash before the main frame window for the application has been fully initialized.
					In order to see what the cause was, please put a break on the Dialog::showMessage
					line inside the catch block of Application::main() and then skip it and continue 
					to run from the throw statement.
					*/
					activeFrame->activate();
				}
			}
			else {
				::KillTimer( hWnd, TOOLTIP_TIMERID );

			}
		}
		break;

		case WM_CREATE:	{

		}
		break;

		case WM_TIMER:	{

			UINT wTimerID = wParam;
			if ( ToolTipTimerID == wTimerID ) {
				POINT pt = {0,0};
				if ( NULL == toolTipWatcher ) {
					toolTipWatcher = new ToolTipWatcher();
				}
				if ( GetCursorPos( &pt ) ) {
					Point tmpPt( pt.x, pt.y );
					HWND hwndCursorIsOver = WindowFromPoint( pt );
					if ( NULL != hwndCursorIsOver ) {
						ScreenToClient( hwndCursorIsOver, &pt );
						HWND childWnd = ChildWindowFromPointEx( hwndCursorIsOver, pt, CWP_SKIPINVISIBLE );
						if ( childWnd != NULL ) {
							ClientToScreen( hwndCursorIsOver, &pt );

							hwndCursorIsOver = childWnd;

							ScreenToClient( hwndCursorIsOver, &pt );
						}

						if ( FALSE != IsWindow( hwndCursorIsOver ) ) {
							Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCursorIsOver );

							if ( NULL != win32Obj ) {

								if ( NULL != toolTipWatcher->toolTip_ ) {
									if ( (HWND)toolTipWatcher->toolTip_->getPeer()->getHandleID() == hwndCursorIsOver ) {
										break;
									}
								}
								tmpPt.y_ += (::GetSystemMetrics( SM_CYCURSOR )*0.66);

								if ( (toolTipWatcher->checkPt_.x_ == tmpPt.x_) && (toolTipWatcher->checkPt_.y_ == tmpPt.y_) ) {
									toolTipWatcher->showTooltip( win32Obj->getPeerControl(), &tmpPt );
									ToolTipTimoutTimerID = ::SetTimer( hWnd, TOOLTIP_TIMEOUT_TIMERID, 5000, NULL );
								}
								else {
									if ( NULL != toolTipWatcher->toolTip_ ) {
										toolTipWatcher->toolTip_->hide();
									}
								}
							}
						}
					}
					toolTipWatcher->checkPt_ = tmpPt;
				}
			}

			else if ( ToolTipTimoutTimerID == wTimerID ) {
				::KillTimer( hWnd, TOOLTIP_TIMEOUT_TIMERID );

				if ( NULL != toolTipWatcher->toolTip_ ) {
					toolTipWatcher->toolTip_->hide();
				}

			}
			else {
				//we may have a registered timer to look for
				Win32ToolKit::TimerRec* timerRec =
					((Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit())->findTimerRec( wTimerID );

				if ( NULL != timerRec ) {
					EventHandler* handler = timerRec->handler_;
					TimerEvent event( timerRec->source_, TIMER_EVENT_PULSE );
					handler->invoke( &event );
				}
			}
		}
		break;

		case WM_DESTROY:	{
			::KillTimer( hWnd, TOOLTIP_TIMERID );
			delete toolTipWatcher;
			if ( System::isUnicodeEnabled() ) {
				result =  DefWindowProcW( hWnd, message, wParam, lParam );
			}
			else {
				result =  DefWindowProcA( hWnd, message, wParam, lParam );
			}
		}
		break;

		case WM_NOTIFY:{
			NMHDR* notificationHdr = (LPNMHDR)lParam;

			Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( notificationHdr->hwndFrom );
			if ( NULL != win32Obj ){
				win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, result );
			}
			else {
				//handle some special case messages here that wouldn't ordinarily get caught
				//because they are from child windows of a common control (like the header control in a listview)
				switch ( notificationHdr->code ) {
				case HDN_ITEMCHANGING: case HDN_TRACK: case HDN_ENDTRACK : case HDN_BEGINTRACK: {
						HWND parent = ::GetParent( notificationHdr->hwndFrom );
						win32Obj = Win32Object::getWin32ObjectFromHWND( parent );
						if ( NULL != win32Obj ){
							win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, result );
						}
					}
					break;
				}
			}
		}
		break;

		case WM_COMMAND:{

			HWND hwndCtl = (HWND) lParam;
			Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
			if ( NULL != win32Obj ){
				if ( win32Obj->acceptsWMCommandMessages() ) {
					win32Obj->handleEventMessages( message, wParam, lParam, result );
				}
			}
			if ( System::isUnicodeEnabled() ) {
				result =  DefWindowProcW( hWnd, message, wParam, lParam );
			}
			else {
				result =  DefWindowProcA( hWnd, message, wParam, lParam );
			}
		}
		break;

		case WM_DRAWITEM:{
			DRAWITEMSTRUCT* drawItem = (DRAWITEMSTRUCT*)lParam;
			if ( ODT_BUTTON == drawItem->CtlType ) {
				HWND hwndCtl = drawItem->hwndItem;
				Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
				if ( NULL != win32Obj ){
					win32Obj->handleEventMessages( WM_DRAWITEM, wParam, lParam, result );
				}
				else {
					if ( System::isUnicodeEnabled() ) {
						result =  DefWindowProcW( hWnd, message, wParam, lParam );
					}
					else {
						result =  DefWindowProcA( hWnd, message, wParam, lParam );
					}
				}
			}
			else {
				if ( System::isUnicodeEnabled() ) {
					result =  DefWindowProcW( hWnd, message, wParam, lParam );
				}
				else {
					result =  DefWindowProcA( hWnd, message, wParam, lParam );
				}
			}
		}
		break;
		/*
		case WM_CTLCOLOREDIT : case WM_CTLCOLORBTN: case WM_CTLCOLORLISTBOX: {

			HWND hwndCtl = (HWND) lParam; // handle to static control
			Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
			if ( NULL != win32Obj ){
				result = win32Obj->handleEventMessages( message, wParam, lParam );
			}
			if ( result != 0 ) {
				result = ::DefWindowProc( hWnd, message, wParam, lParam );
			}
		}
		break;
		*/
		default : {
			if ( VCF_POST_EVENT == message ) {
				Win32PostEventRecord* postedRecord = (Win32PostEventRecord*)lParam;

				postedRecord->handler_->invoke( postedRecord->event_ );
				delete postedRecord;
			}
			else {
				if ( System::isUnicodeEnabled() ) {
					result =  DefWindowProcW( hWnd, message, wParam, lParam );
				}
				else {
					result =  DefWindowProcA( hWnd, message, wParam, lParam );
				}
			}
		}
		break;
	}
	return result;
}

ATOM Win32ToolKit::RegisterWin32ToolKitClass(HINSTANCE hInstance)
{
	if ( System::isUnicodeEnabled() ) {
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)Win32ToolKit::wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= L"Win32ToolKit";
		wcex.hIconSm		= NULL;

		return RegisterClassExW(&wcex);
	}
	else{
		WNDCLASSEXA wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)Win32ToolKit::wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= "Win32ToolKit";
		wcex.hIconSm		= NULL;

		return RegisterClassExA(&wcex);
	}

	return NULL;
}


Win32ToolKit::Win32ToolKit():
	UIToolkit()
{
	runEventCount_ = 0;
	dummyParentWnd_ = NULL;
#if defined( _LIB ) && defined ( USE_WIN32HTMLBROWSER_LIB ) //statically linked in
	browserLibAvailable_ = true;
	Win32ToolKit_toolkitHInstance = ::GetModuleHandle( NULL );
	initWin32HTMLBrowserLib( Win32ToolKit_toolkitHInstance );

#else
	browserLibAvailable_ = false;
#endif

#if defined(VCF_CW) && defined(UNICODE)
	VCF_POST_EVENT = RegisterWindowMessage( L"VCF_POST_EVENT" );
#else
	VCF_POST_EVENT = RegisterWindowMessage( "VCF_POST_EVENT" );
#endif
	if ( 0 == VCF_POST_EVENT ) {
		//oops it failed - do it the stupid way
		VCF_POST_EVENT = WM_USER + 2000;
	}
#if defined(VCF_CW) && defined(UNICODE)
	HBITMAP bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, L"stop", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#else
	HBITMAP bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, "stop", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#endif
	if ( NULL != bmp ) {
		stopImage_ = new Win32Image( bmp );
	}
#if defined(VCF_CW) && defined(UNICODE)
	bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, L"warning", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#else
	bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, "warning", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#endif
	if ( NULL != bmp ) {
		warningImage_ = new Win32Image( bmp );
	}
#if defined(VCF_CW) && defined(UNICODE)
	bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, L"inform", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#else
	bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, "inform", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#endif
	if ( NULL != bmp ) {
		informationImage_ = new Win32Image( bmp );
		informationImage_->setTransparencyColor( &Color(0.0,1.0,0.0) );
		informationImage_->setIsTransparent( true );
	}
#if defined(VCF_CW) && defined(UNICODE)
	bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, L"question", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#else
	bmp = (HBITMAP)::LoadImage( Win32ToolKit_toolkitHInstance, "question", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
#endif
	if ( NULL != bmp ) {
		questionImage_ = new Win32Image( bmp );
	}

	createDummyParentWindow();

	metricsMgr_ = new Win32UIMetricsManager();
	policyMgr_ = new Win32UIPolicyManager();


	VCFCOM::COMUtils::registerDataTypes();
}


Win32ToolKit::~Win32ToolKit()
{
#if defined( _LIB ) && defined ( USE_WIN32HTMLBROWSER_LIB )
	terminateWin32HTMLBrowserLib();
#endif

	std::map<UINT,TimerRec*>::iterator it = timerMap_.begin();
	while ( it != timerMap_.end() ) {
		KillTimer( dummyParentWnd_, it->first );
		delete it->second;
		it++;
	}
	timerMap_.clear();

	if ( !::DestroyWindow( dummyParentWnd_ ) ) {
		int err = GetLastError();
		StringUtils::traceWithArgs( Format("::DestroyWindow( dummyParentWnd_[=%p] ) failed!, err: %d\n") % dummyParentWnd_ % err );

		if ( NULL != toolTipWatcher ) {
			toolTipWatcher->free();
		}
	}
}

ApplicationPeer* Win32ToolKit::internal_createApplicationPeer()
{
	return new Win32Application();
}

TextPeer* Win32ToolKit::internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined )
{
	return new Win32TextPeer(autoWordWrap,multiLined);
}

TextEditPeer* Win32ToolKit::internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl)
{
	return new Win32Edit( component, isMultiLineControl );
}

TreePeer* Win32ToolKit::internal_createTreePeer( TreeControl* component )
{
	return new Win32Tree( component );
}

ListviewPeer* Win32ToolKit::internal_createListViewPeer( ListViewControl* component )
{
	return new Win32Listview( component );
}

HTMLBrowserPeer* Win32ToolKit::internal_createHTMLBrowserPeer( Control* control )
{
	HTMLBrowserPeer* result = NULL;
	if ( false == browserLibAvailable_ ) {
		try {
			browserLib_.load( WIN32HTMLBROWSER_DYNLIB );
			browserLibAvailable_ = true;
		}
		catch ( BasicException&  ) {
			browserLibAvailable_ = false;
		}
	}
	if ( true == browserLibAvailable_ ) {
		Object* win32HTMLBrowser = ClassRegistry::createNewInstance( "VCF::Win32HTMLBrowser" );
		if ( NULL != win32HTMLBrowser ) {
			result = dynamic_cast<HTMLBrowserPeer*>( win32HTMLBrowser );
			if ( NULL == result ) {
				delete win32HTMLBrowser;
			}
			else {
				ControlPeer* controlPeer = dynamic_cast<ControlPeer*>( win32HTMLBrowser );
				if ( NULL != controlPeer ) {
					controlPeer->setControl( control );
				}
			}
		}
		else {
			throw RuntimeException( "initWin32HTMLBrowserLib was not called correctly, and/or the Win32HTMLBroswer Lib was not linked with" );
		}
	}
	return result;
}

DialogPeer* Win32ToolKit::internal_createDialogPeer( Control* owner, Dialog* component )
{
	return new Win32Dialog( owner, component );
}

DialogPeer* Win32ToolKit::internal_createDialogPeer()
{
	return new Win32Dialog();
}

void Win32ToolKit::createDummyParentWindow()
{

	HWND parent = ::GetDesktopWindow();


	if ( System::isUnicodeEnabled() ) {
		RegisterWin32ToolKitClass( ::GetModuleHandleW( NULL ) );

		dummyParentWnd_ = ::CreateWindowW( L"Win32ToolKit", NULL, WS_POPUP , 0, 0, 0, 0, parent, NULL, ::GetModuleHandleW( NULL ), NULL );
	}
	else {
		RegisterWin32ToolKitClass( ::GetModuleHandleA( NULL ) );

		dummyParentWnd_ = ::CreateWindowA( "Win32ToolKit", NULL, WS_POPUP , 0, 0, 0, 0, parent, NULL, ::GetModuleHandleA( NULL ), NULL );
	}

}

HWND Win32ToolKit::getDummyParent()
{
	if ( NULL == dummyParentWnd_ ){
		this->createDummyParentWindow();
	}
	return this->dummyParentWnd_;
}

MenuItemPeer* Win32ToolKit::internal_createMenuItemPeer( MenuItem* item )
{
	return new Win32MenuItem( item );
}

MenuBarPeer* Win32ToolKit::internal_createMenuBarPeer( MenuBar* menuBar )
{
	return new Win32MenuBar( menuBar );
}

ButtonPeer* Win32ToolKit::internal_createButtonPeer( CommandButton* component)
{
	return new Win32Button( component );
}

ContextPeer* Win32ToolKit::internal_createContextPeer( Control* component )
{
	return new Win32ControlContext( component->getPeer() );
}

CommonFileDialogPeer* Win32ToolKit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
	return new Win32FileOpenDialog( owner );
}

CommonFileDialogPeer* Win32ToolKit::internal_createCommonFileSaveDialogPeer( Control* owner )
{
	return new Win32FileSaveDialog( owner );
}

CommonColorDialogPeer* Win32ToolKit::internal_createCommonColorDialogPeer( Control* owner )
{
	return new Win32ColorDialog( owner );
}

CommonFolderBrowseDialogPeer* Win32ToolKit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
	return new Win32FolderBrowseDialog();
}

DragDropPeer* Win32ToolKit::internal_createDragDropPeer()
{
	return new Win32DragDropPeer();
}

DataObjectPeer* Win32ToolKit::internal_createDataObjectPeer()
{
	return NULL;
}

DropTargetPeer* Win32ToolKit::internal_createDropTargetPeer()
{
	return new Win32DropTargetPeer();
}

ClipboardPeer* Win32ToolKit::internal_createClipboardPeer()
{
	return new Win32Clipboard();
}

PopupMenuPeer* Win32ToolKit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
	return new Win32PopupMenu( popupMenu );
}

CommonFontDialogPeer* Win32ToolKit::internal_createCommonFontDialogPeer( Control* owner )
{
	return new Win32FontDialog( owner );
}

CommonPrintDialogPeer* Win32ToolKit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return new Win32PrintDialog( owner );
}


DesktopPeer* Win32ToolKit::internal_createDesktopPeer( Desktop* desktop )
{
	return new Win32Desktop( desktop );
}

ScrollPeer* Win32ToolKit::internal_createScrollPeer( Control* control )
{
	return new Win32ScrollPeer( control );
}

CursorPeer* Win32ToolKit::internal_createCursorPeer( Cursor* cursor )
{
	return new Win32CursorPeer( cursor );
}

ControlPeer* Win32ToolKit::internal_createControlPeer( Control* component, ComponentType componentType)
{
	ControlPeer* result = NULL;

	switch ( componentType ){
		case CT_LIGHTWEIGHT:{
			result = new LightweightComponent( component );
		}
		break;

		case CT_DEFAULT: case CT_HEAVYWEIGHT:{
			result = new Win32Component( component );
		}
		break;
	}
	return result;
}


WindowPeer* Win32ToolKit::internal_createWindowPeer( Control* component, Control* owner)
{
	return new Win32Window( component, owner );
}

ToolbarPeer* Win32ToolKit::internal_createToolbarPeer( Toolbar* toolbar )
{
	return new Win32Toolbar( toolbar );
}

SystemTrayPeer* Win32ToolKit::internal_createSystemTrayPeer()
{
	return new Win32SystemTrayPeer();
}


MenuManagerPeer* Win32ToolKit::internal_createMenuManagerPeer()
{
	return new Win32MenuManagerPeer();
}

GraphicsResourceBundlePeer* Win32ToolKit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new Win32AppResourceBundle( app );
}

bool Win32ToolKit::internal_createCaret( Control* owningControl, Image* caretImage  )
{
	return false;
}

bool Win32ToolKit::internal_destroyCaret( Control* owningControl )
{
	return false;
}

void Win32ToolKit::internal_setCaretVisible( const bool& caretVisible )
{

}

void Win32ToolKit::internal_setCaretPos( Point* point )
{

}

void Win32ToolKit::internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	Win32PostEventRecord* postEventRecord = new Win32PostEventRecord( eventHandler, event, deleteHandler );
	if ( ! ::PostMessage( dummyParentWnd_, VCF_POST_EVENT, 0, (LPARAM)postEventRecord ) ) {
		int err = ::GetLastError();
		StringUtils::traceWithArgs( Format("!!!!!!! WARNING ::PostMessage Failed (GetLastError(): %d !!!!!!\n") %
									err );

	}
}

void Win32ToolKit::internal_registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds )
{
	std::map<UINT,TimerRec*>::iterator found = timerMap_.begin();
	while ( found != timerMap_.end() ) {
		if ( found->second->handler_ == handler ) {
			KillTimer( dummyParentWnd_, found->first );

			delete found->second;

			timerMap_.erase( found );

			break;
		}
		found ++;
	}

	UINT id = ::SetTimer( dummyParentWnd_, (UINT)handler, timeoutInMilliSeconds, NULL );

	if ( id == 0 ) {
		//throw exception
	}
	else {
		timerMap_[id] = new TimerRec( source, handler );
	}
}

void Win32ToolKit::internal_unregisterTimerHandler( EventHandler* handler )
{
	std::map<UINT,TimerRec*>::iterator found = timerMap_.begin();
	while ( found != timerMap_.end() ) {
		if ( found->second->handler_ == handler ) {
			KillTimer( dummyParentWnd_, found->first );
			delete found->second;

			timerMap_.erase( found );

			break;
		}
		found ++;
	}
}

Win32ToolKit::TimerRec* Win32ToolKit::findTimerRec( UINT id )
{
	TimerRec* result = NULL;
	std::map<UINT,TimerRec*>::iterator found = timerMap_.find( id );
	if ( found != timerMap_.end() ) {
		result = found->second;
	}

	return result;
}

HINSTANCE Win32ToolKit::getInstanceHandle()
{
	return Win32ToolKit_toolkitHInstance;
}

Event* Win32ToolKit::internal_createEventFromNativeOSEventData( void* eventData )
{
	Event* result = NULL;

	Win32MSG* msg = (Win32MSG*)eventData;

	switch ( msg->msg_.message ) {
		case WM_SIZE: {
			VCF::Size sz( LOWORD(msg->msg_.lParam), HIWORD(msg->msg_.lParam) );
			result = new ControlEvent( msg->control_, sz );
		}
		break;

		case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:{
			VCF::Point pt( Win32Utils::getXFromLParam( msg->msg_.lParam ),
							Win32Utils::getYFromLParam( msg->msg_.lParam ) );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_DOWN,
											Win32Utils::translateButtonMask( msg->msg_.wParam ),
											Win32Utils::translateKeyMask( msg->msg_.wParam ), &pt );
		}
		break;

		case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:{
			VCF::Point pt( Win32Utils::getXFromLParam( msg->msg_.lParam ) ,
						   Win32Utils::getYFromLParam( msg->msg_.lParam ) );


			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			WPARAM tmpWParam = msg->msg_.wParam;
			switch ( msg->msg_.message ){
				case WM_LBUTTONUP:{
					tmpWParam |= MK_LBUTTON;
				}
				break;
				case WM_MBUTTONUP:{
					tmpWParam |= MK_MBUTTON;
				}
				break;

				case WM_RBUTTONUP:{
					tmpWParam |= MK_RBUTTON;
				}
				break;
			}

			result = new VCF::MouseEvent( msg->control_, Control::MOUSE_UP,
											Win32Utils::translateButtonMask( tmpWParam ),
											Win32Utils::translateKeyMask( tmpWParam ), &pt );

		}
		break;

		case WM_SETFOCUS: {
			result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_GAINED );
		}
		break;

		case WM_KILLFOCUS: {
			result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_LOST );
		}
		break;

		case WM_CREATE: {
			result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_CREATED );
		}
		break;

		case WM_HELP : {
			HELPINFO* helpInfo = (HELPINFO*) msg->msg_.lParam;
			result = new HelpEvent(msg->control_);

		}
		break;

		case VCF_CONTROL_CREATE: {
			result = new VCF::ComponentEvent ( msg->control_, Component::COMPONENT_CREATED );
		}
		break;

		case WM_DESTROY: {
			result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_DELETED );
		}
		break;

		case WM_LBUTTONDBLCLK: case WM_MBUTTONDBLCLK: case WM_RBUTTONDBLCLK:{

			VCF::Point pt( Win32Utils::getXFromLParam( msg->msg_.lParam ) ,
							Win32Utils::getYFromLParam( msg->msg_.lParam ) );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( msg->control_, Control::MOUSE_DBLCLICK,
											Win32Utils::translateButtonMask( msg->msg_.wParam ),
											Win32Utils::translateKeyMask( msg->msg_.wParam ), &pt );


		}
		break;

		case WM_MOVE: {
			VCF::Point pt( Win32Utils::getXFromLParam( msg->msg_.lParam ) ,
							Win32Utils::getYFromLParam( msg->msg_.lParam ) );

			result = new VCF::ControlEvent( msg->control_, pt );

		}
		break;

		case WM_MOUSEMOVE: {
			VCF::Point pt( Win32Utils::getXFromLParam( msg->msg_.lParam ) ,
							Win32Utils::getYFromLParam( msg->msg_.lParam ) );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}


			result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
											Win32Utils::translateButtonMask( msg->msg_.wParam ),
											Win32Utils::translateKeyMask( msg->msg_.wParam ),
											&pt );
		}
		break;

		case WM_MOUSELEAVE: {
			POINT pt = {0,0};
			::GetCursorPos( &pt );
			ScreenToClient( msg->msg_.hwnd, &pt );

			VCF::Point pt2( pt.x , pt.y );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt2.x_ += scrollable->getHorizontalPosition();
				pt2.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( msg->control_, Control::MOUSE_LEAVE,
											Win32Utils::translateButtonMask( 0 ),
											Win32Utils::translateKeyMask( 0 ), &pt2 );
		}
		break;

		case WM_CHAR: case WM_KEYDOWN: case WM_KEYUP: {
			KeyboardData keyData = Win32Utils::translateKeyData( msg->msg_.hwnd, msg->msg_.lParam );
			unsigned long eventType = 0;
			switch ( msg->msg_.message ){
				case WM_CHAR: {
					eventType = Control::KEYBOARD_PRESSED;
				}
				break;

				case WM_KEYDOWN: {
					eventType = Control::KEYBOARD_DOWN;//KEYBOARD_EVENT_DOWN;
				}
				break;

				case WM_KEYUP: {
					eventType = Control::KEYBOARD_UP;
				}
				break;
			}

			unsigned long keyMask = Win32Utils::translateKeyMask( keyData.keyMask );

			ulong32 virtKeyCode = Win32Utils::translateVKCode( keyData.VKeyCode );
			result = new VCF::KeyboardEvent( msg->control_,
											eventType,
											keyData.repeatCount,
											keyMask,
											(VCF::VCFChar)keyData.character,
											(VirtualKeyCode)virtKeyCode );


		}
		break;

	}


	return result;
}

void Win32ToolKit::internal_runEventLoop()
{
	runEventCount_ ++;

	MSG msg;
	memset( &msg, 0, sizeof(MSG) );

	HACCEL hAccelTable = NULL;

	//we should have one of these, but it is not the end of the world if we don't.
	//we can check at the beginning here cause our app instance isn't going to magically
	//disapear on us, and if it does then we are doomed anyway...
	Application* runningApp = Application::getRunningInstance();

	bool isIdle = true;
	while (true) {
		// phase1: check to see if we can do idle work
		while ((true == isIdle) && (!::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) ) {

			if ( NULL != runningApp ) {
				runningApp->idleTime();
			}

			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( true == registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}
			isIdle = false;
		}

		if ( msg.message == WM_QUIT ) {
			StringUtils::trace( "WM_QUIT\n" );
			return;
		}
		else if ( msg.message == WM_EXITMENULOOP ) {
			StringUtils::trace( "WM_EXITMENULOOP\n" );
		}
		else if ( msg.message == WM_INPUTLANGCHANGE ) {
			StringUtils::trace( "WM_INPUTLANGCHANGE\n" );
		}
		else if ( msg.message == WM_WININICHANGE ) {
			StringUtils::trace( "WM_WININICHANGE\n" );
		}

		do	{
			//dispatch message, but quit on WM_QUIT
			if ( GetMessage( &msg, NULL, 0, 0 ) ) {
				/**
				*we're going to want to handle accelerators here
				*the steps should
				*identify if the message is a
				*WM_KEYPRESS
				*if it is then check to find the Control associated with the msg
				*if it is then call the Control's getAccelator and match to the
				*key stroke's VK code and modifier keys. if the accelerator is
				*found the call the invoke() method on the event handler for hte
				*accelerator.
				*if no accelerator is found on the control or no control is found,
				*try and get the running Application. if one is found then call
				*the getAccelerator() on the Application and do the same thing as described
				*for the control
				*if any accelerator is found then do NOT call TranslateMessage() and DispatchMessage()
				*
				*
				*/
				bool doTranslateAndDispatch = true;
				switch( msg.message ) {

					case WM_KEYDOWN :  case WM_SYSKEYDOWN : {

						KeyboardData keyData = Win32Utils::translateKeyData( msg.hwnd, msg.lParam );

						KeyboardMasks modifierKey = (KeyboardMasks)Win32Utils::translateKeyMask( keyData.keyMask );
						VirtualKeyCode vkCode = (VirtualKeyCode)Win32Utils::translateVKCode( keyData.VKeyCode );

						if ( vkUndefined == vkCode ) { //tranlsate by ascii value

							switch ( keyData.character ) {
								case '{' : {
									vkCode = vkOpenBrace;
								}
								break;

								case '}' : {
									vkCode = vkCloseBrace;
								}
								break;

								case '[' : {
									vkCode = vkOpenBracket;
								}
								break;

								case ']' : {
									vkCode = vkCloseBracket;
								}
								break;

								case '~' : {
									vkCode = vkTilde;
								}
								break;

								case '`' : {
									vkCode = vkLeftApostrophe;
								}
								break;
							}
						}

						Win32Object* w = Win32Object::getWin32ObjectFromHWND( msg.hwnd );

						Control* control = NULL;
						Control* currentFocusedControl = Control::getCurrentFocusedControl();

						if ( NULL != w ) {
							control = w->getPeerControl();
							if ( NULL != currentFocusedControl ) {
								if ( (control != currentFocusedControl) && (currentFocusedControl->isLightWeight()) ) {
									control = currentFocusedControl;
								}
							}
						}
						/**
						JC - I put this very small change to attempt to
						properly capture the "correct" focused control,
						from the VCF's perspective. It seems to work fine.
						*/
						else {
							control = currentFocusedControl;
						}

						KeyboardEvent event( control, Control::KEYBOARD_ACCELERATOR, keyData.repeatCount,
							modifierKey, keyData.character, vkCode );

						handleKeyboardEvent( &event );
						if ( event.isConsumed() ) {
							doTranslateAndDispatch = false;
						}
					}
				}

				if ( doTranslateAndDispatch ) {
					if (!TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) ) {
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}
				}

				if ( msg.message == WM_QUIT ) {
					StringUtils::trace( "WM_QUIT\n" );
					return;
				}
				else if ( msg.message == WM_EXITMENULOOP ) {
					StringUtils::trace( "WM_EXITMENULOOP\n" );
				}
			}
			else {
				return; //we're outta here - nothing more to do
			}

			/**
			0x0118 is a WM_SYSTIMER, according to MSDN:
			"The WM_SYSTIMER message in Windows is an undocumented system message;
			it should not be trapped or relied on by an application. This message
			can occasionally be viewed in Spy or in CodeView while debugging.

			Windows uses the WM_SYSTIMER message internally to control the scroll
			rate of highlighted text (text selected by the user) in edit controls,
			or highlighted items in list boxes.

			NOTE: The WM_SYSTIMER message is for Windows's internal use only and
			can be changed without prior notice. "
			*/

			// WM_PAINT and WM_SYSTIMER (caret blink)
			bool isIdleMessage = ( (msg.message != WM_PAINT) && (msg.message != 0x0118) );
			if ( true == isIdleMessage ) {
				if ( (msg.message == WM_MOUSEMOVE) || (msg.message == WM_NCMOUSEMOVE) ) {
					//check the prev mouse pt;
				}
			}

			if ( true == isIdleMessage ) {
				isIdle = true;
			}

		}
		while ( ::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) );
	}

	runEventCount_ --;
}



UIToolkit::ModalReturnType Win32ToolKit::internal_runModalEventLoopFor( Control* control )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrTrue;

	try {
		HWND controlHwnd = (HWND)control->getPeer()->getHandleID();

		Application* runningApp = Application::getRunningInstance();
		int err = 0;
		MSG msg;
		memset( &msg, 0, sizeof(MSG) );

		bool done = false;
		while (false == done) {

			if ( NULL != runningApp ) {
				runningApp->idleTime();
			}

			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( true == registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}

			do	{
				bool doTranslateAndDispatch = true;

				bool ESCkeyPressed = false;
				if ( GetMessage(  &msg, NULL, 0, 0 ) ) {
					switch( msg.message ) {

						case WM_KEYDOWN :  case WM_SYSKEYDOWN : {
							KeyboardData keyData = Win32Utils::translateKeyData( msg.hwnd, msg.lParam );

							KeyboardMasks modifierKey = (KeyboardMasks)Win32Utils::translateKeyMask( keyData.keyMask );
							VirtualKeyCode vkCode = (VirtualKeyCode)Win32Utils::translateVKCode( keyData.VKeyCode );

							ESCkeyPressed = (vkCode == vkEscape);

							Win32Object* w = Win32Object::getWin32ObjectFromHWND( msg.hwnd );

							Control* msgControl = NULL;
							if ( NULL != w ) {
								msgControl = w->getPeerControl();
								Control* currentFocusedControl = Control::getCurrentFocusedControl();
								if ( NULL != currentFocusedControl ) {
									if ( (msgControl != currentFocusedControl) && (currentFocusedControl->isLightWeight()) ) {
										msgControl = currentFocusedControl;
									}
								}
							}

							KeyboardEvent event( msgControl, Control::KEYBOARD_ACCELERATOR, keyData.repeatCount,
													modifierKey, keyData.character, vkCode );

							handleKeyboardEvent( &event );
							if ( event.isConsumed() ) {
								doTranslateAndDispatch = false;
							}
						}
					}
					if ( true == doTranslateAndDispatch ) {
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}
				}
				else {
					done = true;
					break;
				}
				/*
				if ( doTranslateAndDispatch ) {
					// show the window when certain special messages rec'd

					if ((msg.message == 0x118) || (msg.message == WM_SYSKEYDOWN) ) {
						//err = ::ShowWindow( controlHwnd, SW_SHOWNORMAL );
						//err = ::UpdateWindow( controlHwnd );

						//this is rather crufty and I'm a bit dubious about it's necessity??
						if ( (NULL != frame) && (msg.message == WM_SYSKEYDOWN) ) {
							//frame->activate();
						}
					}
				}
				*/
				switch ( msg.message ){
					case WM_KEYDOWN : {
						if ( ESCkeyPressed ) {
							result = UIToolkit::mrCancel;
						}
					}
					break;

					case WM_SYSCOMMAND: {
						if ( SC_CLOSE == msg.wParam ){
							result = UIToolkit::mrCancel;
							PostQuitMessage(0);
						}
					}
					break;

					case WM_QUIT:{
						done = true;
					}
					break;
				}

				if ( ! IsWindow( controlHwnd ) ) {

					PostQuitMessage(0);
				}

			} while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE));
		} //outer for loop

	}
	catch (...) {
		//display error ?
		result = mrFalse;
	}

	//EnumThreadWindows( GetCurrentThreadId(), EnumThreadWndProc, (LPARAM)this );



	return result;
}

void Win32ToolKit::internal_quitCurrentEventLoop()
{
	PostQuitMessage(0);
	//if (!PostMessage( dummyParentWnd_, WM_QUIT, 0, 0 )) {
	//	StringUtils::traceWithArgs( "GetLastError(): %d\n", GetLastError() );
	//}
	//else {
	//	StringUtils::traceWithArgs( "internal_quitCurrentEventLoop called, PostMessage(WM_QUIT) sent\n" );
	//}
}

Size Win32ToolKit::internal_getDragDropDelta()
{
	Size result;

	result.width_ = ::GetSystemMetrics( SM_CXDRAG );
	result.height_ = ::GetSystemMetrics( SM_CYDRAG );

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.5  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.21  2005/07/04 03:46:07  marcelloptr
*made the error handling block to break in the right place even when the main application's frame is not fully initialized yet.
*
*Revision 1.3.2.15  2005/06/06 02:34:06  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.3.2.14  2005/05/20 03:04:05  ddiego
*minor mods to set focused control.
*
*Revision 1.3.2.13  2005/05/15 23:17:38  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.12  2005/04/25 00:11:58  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.3.2.11  2005/04/20 02:26:01  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.10  2005/04/13 00:57:02  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.3.2.9  2005/03/27 05:25:13  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.3.2.8  2005/03/15 01:51:50  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.7  2005/03/14 18:56:31  marcelloptr
*comments and added an error message to avoid an infinite loop
*
*Revision 1.3.2.6  2005/03/14 04:17:24  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3.2.5  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.4  2005/01/26 20:59:29  ddiego
*some fixes to table control and to teh table item editor interface
*
*Revision 1.3.2.3  2005/01/01 20:31:07  ddiego
*made an adjustment to quitting and event loop, and added some changes to the DefaultTabModel.
*
*Revision 1.3.2.2  2004/12/20 21:58:00  ddiego
*committing cheeseheads patches for the combobox control.
*
*Revision 1.3.2.1  2004/12/19 07:09:18  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.12  2004/11/13 22:30:42  marcelloptr
*more documentation
*
*Revision 1.2.2.11  2004/10/25 03:52:02  ddiego
*minor changes to osx checkin for win32
*
*Revision 1.2.2.10  2004/10/25 03:23:57  ddiego
*and even more dialog updates. Introduced smore docs to the dialog class and added a new showXXX function.
*
*Revision 1.2.2.9  2004/10/23 13:53:12  marcelloptr
*comments for setUseColorForBackground; setActiveFrame renamed as internal
*
*Revision 1.2.2.8  2004/10/23 12:19:13  marcelloptr
*bugfix [1048400] menus are now merged regardless of their shortcut key
*
*Revision 1.2.2.7  2004/09/29 16:16:24  dougtinkham
*fixed paint of border around ToolTip
*
*Revision 1.2.2.6  2004/09/28 20:18:49  marcelloptr
*just some spaces for clarity
*
*Revision 1.2.2.5  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2.2.4  2004/09/01 03:50:14  ddiego
*fixed font drawing bug that tinkham pointed out.
*
*Revision 1.2.2.3  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2.2.2  2004/08/19 03:22:54  ddiego
*updates so new system tray code compiles
*
*Revision 1.2.2.1  2004/08/18 21:20:24  ddiego
*added initial system tray code for win32
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/30 17:27:14  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.5  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.4  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.3  2004/06/30 19:19:29  ddiego
*fixed some font issues. got rid of methods that are not implementable on other platforms
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.51.2.3  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.51.2.2  2004/04/08 01:47:53  marcelloptr
*use of USE_WIN32HTMLBROWSER_LIB in applicationKit is now optional
*
*Revision 1.51.2.1  2004/04/07 03:25:57  ddiego
*fixed Win32HTMLBrowser ATL assert bug. The problem was a minor
*to teh ATL CComModule.Init() function. In VC6 version it just needed
*an HINSTANCE and and object map, in VC7 it also needs a GUID for the lib.
*Of course this is helpfully set to an INVALID default parameter, which is
*nice, I suppose.
*
*Revision 1.51  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.50  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.49.2.3  2004/03/28 00:46:22  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.49.2.2  2004/03/26 04:16:39  ddiego
*trying to get some subtle bugs with focus worked out
*
*Revision 1.49.2.1  2004/01/18 04:52:46  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.49.2.1  2004/01/18 04:52:46  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.49  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.48.2.15  2003/11/10 01:57:43  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.48.2.14  2003/10/31 05:06:38  ddiego
*added toolbar impl
*
*Revision 1.48.2.13  2003/10/30 22:29:54  ddiego
**** empty log message ***
*
*Revision 1.48.2.12  2003/10/27 04:20:40  ddiego
*more tweaks to the Slider control
*
*Revision 1.48.2.11  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*Revision 1.48.2.10  2003/10/24 21:50:26  ddiego
*bugfixes
*
*Revision 1.48.2.9  2003/10/13 21:28:41  ddiego
*fiddles with the containers a bit - didn't fix anything :(
*
*Revision 1.48.2.8  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.48.2.7  2003/09/09 19:32:03  marcelloptr
*minor changes and autoresizing of listbox columns
*
*Revision 1.48.2.6  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.48.2.5  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.48.2.4  2003/09/03 23:45:28  marcelloptr
*fixed minor namespace resolution problem
*
*Revision 1.48.2.3  2003/08/28 21:47:30  ddiego
*added escape reponse...
*
*Revision 1.48.2.2  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.48.2.1  2003/08/17 21:48:35  ddiego
*fixed bug [ 788189 ] ComboBoxControl doesn't close when application loose
*focus. Also cleaned some old trace statements for debugging purposes.
*
*Revision 1.48  2003/08/09 02:56:46  ddiego
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
*Revision 1.47.2.10  2003/08/01 00:50:17  ddiego
*added a fix for popup windows that also fixed a problem with the
*ComboBoxControl drop down list disapearing.
*
*Revision 1.47.2.9  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.47.2.8  2003/07/06 01:20:29  ddiego
*added basic Document/View classes. These are based on the existing MVC
*architecture already present in the framework already, and exapnd on the
*existing functionality. Many of the ideas were influenced by the NeXT/Cocoa's
*Document/View architecture. Some of the new features are:
*  automatic creation and connection of the various parts including the
*  Document, view and Window.
*  Automatic default menu items, to ensure standard UI conformance. The menu
*  items are merged with an existing ones.
*  Automatic clipboard support in the form of cut/copy/paste and connecting this
*  directly to the current document
*  Support for Undo/Redo item as well, including default menu item validation
*  Default support for opening and saving documents, including presenting the
*  correct Dialogs to the User, and properly filling the default data, based
*  on the documents data.
*  Support for multiple document types
*  Support for differnt Document Interface policies. Currently we support
*  SDI (Single Document Interface) and MDI (Multiple Document Interface)
*
*Revision 1.47.2.7  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.47.2.6  2003/06/27 03:10:59  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.47.2.5  2003/06/13 03:05:32  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.47.2.4  2003/06/13 00:02:13  ddiego
*more xmake fixes for the new version
*bug fixes for bugs
*509004	Opening a modal Dialog causes flicker
*also have tooltips working again
*
*Revision 1.47.2.3  2003/06/09 03:57:15  ddiego
*fixed an issue with tooltip not showing up, and while fixing that found it
*accidentally caused another problem with application focus for the main
*window not being handled correctly. This is now working OK! Now just
*have to get rid of the dialog flicker...
*Also fixed the QTPlayer example. It had some syntax errors from using the older
*event macros (not using Delegates)
*
*Revision 1.47.2.2  2003/06/05 03:48:54  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.47.2.1  2003/05/27 04:45:38  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.47  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.46.2.3  2003/05/13 14:17:15  ddiego

*fixed an code error due to the addition of the Control::translateXXX
*methods (previously this was part of the Desktop interface)
*
*Revision 1.46.2.2  2003/03/23 04:06:34  marcelloptr
*minor fixes
*
*Revision 1.46.2.1  2003/03/12 03:12:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.46  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.45.2.5  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.45.2.4  2003/01/08 00:19:54  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.45.2.3  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.45.2.2  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.45.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.45  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.44.4.6  2002/10/16 05:39:30  ddiego
*started working on adding support for creating a new form to a project
*
*Revision 1.44.4.5  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.44.4.4  2002/09/30 02:16:52  ddiego
*misc piddling
*
*Revision 1.44.4.3  2002/09/28 02:37:38  ddiego
*fixed up the radiobox and checkbox, label and header controls to properly
*take advantage of default heights from the UIMetricsManager
*fixed the default height for radioboxes and checkboxes in Win32 so that they are
*10 dialog units high - added the neccessary conversion code from dialog
*units to pixels
*
*Revision 1.44.4.2  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.44.4.1  2002/09/13 04:45:35  ddiego
*misc coding
*
*Revision 1.44  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.43.6.6  2002/09/10 21:36:18  ddiego
*misc UI touchup stuff
*
*Revision 1.43.6.5  2002/09/06 20:12:41  ddiego
*tracking a bug in the ComboBoxCOntrol due to focus issues - still needs fixing
*
*Revision 1.43.6.4  2002/09/06 05:24:52  ddiego
*fixed bug in TableControl where it does not proeprly finished the ItemEditor
*correctly on loss of focus for the editor's control
*
*Revision 1.43.6.3  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.43.6.2  2002/07/02 05:35:11  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.43.6.1  2002/06/28 17:45:30  ddiego
*migrated over lucki's changes (from his branch) for drag drop
*compiles OK, made chages to control and UIToolkit as neccessary
*still testing though.
*
*Revision 1.43  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.42.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.42.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.42  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.41  2002/02/07 04:38:55  ddiego
*fixes to Win32Edit, which include problems with setting text, and a bug that
*caused it to crash in Win 98. All textControls now default to the "EDIT"
*window class unles they are multiline, in which case an attempt is made to
*load the richedit control, and if that fails then the EDIT class is used
*Removed responding to WM_COMMAND messages
*in the default parent in the Win32Toolkit, also to fix the Win32Edit crash in 9.x
*
*Revision 1.40  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.39  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


