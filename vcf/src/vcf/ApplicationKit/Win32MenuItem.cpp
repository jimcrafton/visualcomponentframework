//Win32MenuItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"
#include "vcf/GraphicsKit/DrawUIState.h"



#define BASE_MENU_ID	32000
int globalLastMenuID = BASE_MENU_ID;

#define CXGAP				1		// num pixels between button and text
#define CXTEXTMARGIN		2		// num pixels after hilite to start text
#define CXBUTTONMARGIN		2		// num pixels wider button is than bitmap
#define CYBUTTONMARGIN		2		// ditto for height


using namespace VCF;

std::map<uint32, MenuItem*> Win32MenuItem::menuItemMap;
std::map<HMENU,MenuItem*> Win32MenuItem::menuItemHandleMap;

Win32MenuItem::Win32MenuItem( MenuItem* item ):
	itemAdded_(false)
{
	menuItem_ = item;
	init();
}

Win32MenuItem::Win32MenuItem():
	itemAdded_(false)
{
	init();
}

Win32MenuItem::~Win32MenuItem()
{
	std::map<uint32,MenuItem*>::iterator found = menuItemMap.find( itemId_ );
	if ( found != menuItemMap.end() ){
		menuItemMap.erase( found );
	}

	std::map<HMENU,MenuItem*>::iterator found2 = Win32MenuItem::menuItemHandleMap.find( itemHandle_ );
	if ( found2 != Win32MenuItem::menuItemHandleMap.end() ){
		Win32MenuItem::menuItemHandleMap.erase( found2 );
	}

	//globalLastMenuID --;

	if ( ::IsMenu( itemHandle_ ) ){
		DestroyMenu( itemHandle_ );
	}
	else if ( NULL != itemHandle_ ){
		if ( ! DestroyMenu( itemHandle_ ) ) {
			int err = GetLastError();
			//StringUtils::traceWithArgs( "Menu Item handle leak for handle %p with id of: %d, GetLastError(): %d\n", itemHandle_, itemId_, err );
		}
	}
}

void Win32MenuItem::init()
{
	itemHandle_ = NULL;

	globalLastMenuID ++;

	itemId_ = globalLastMenuID;

	menuItemMap[itemId_] = menuItem_;
}

void Win32MenuItem::insertSimpleMenuItem( MenuItem* child, HMENU menu )
{

	if ( NULL == menu ) {
		return;
	}


	MenuItemPeer* itemImpl = child->getPeer();
	Win32MenuItem* win32ChildImpl = (Win32MenuItem*)itemImpl;
	
	String itemName = child->getCaption();
	if ( child->getUseLocaleStrings() ) {
		itemName = System::getCurrentThreadLocale()->translate( itemName );
	}

	itemName = generateCaption( child, itemName );


	DWORD mask = MIIM_ID  | MIIM_STATE | MIIM_TYPE;
	DWORD type = 0;
	DWORD state = MFS_ENABLED;
	HMENU subMenu = NULL;
	DWORD id = win32ChildImpl->itemId_;

	if ( true == child->isSeparator() ){
		type |= MFT_SEPARATOR;
	}
	else {
		type = MFT_STRING;
	}
	//put this back in later
	if ( true == child->canPaint() ) {
		type |= MFT_OWNERDRAW;
	}

	if ( child->hasChildren() ){
		mask |= MIIM_SUBMENU;
		subMenu = (HMENU) itemImpl->getMenuID();
	}

	

	if ( System::isUnicodeEnabled() ) {
		MENUITEMINFOW info;
		memset(&info,0,sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = mask;
		info.fState = state;
		info.fType = type;		
		info.wID = id;
		info.hSubMenu = subMenu;


		info.cch = itemName.size();
		wchar_t* tmpName = new wchar_t[info.cch+1];
		memset( tmpName, 0, (info.cch+1)*sizeof(wchar_t) );
		itemName.copy( tmpName, info.cch );

		info.dwTypeData = tmpName;

		if ( InsertMenuItemW( menu, child->getIndex()/*info.wID*/, TRUE, &info ) ) {
			win32ChildImpl->itemAdded_ = true;
		}

		delete [] tmpName;

		MenuItem* parentItem = menuItem_->getParent();
		

		if ( NULL != parentItem ) {
			int index = menuItem_->getIndex();

			Win32MenuItem* win32ParentImpl = (Win32MenuItem*)parentItem->getPeer();
			HMENU parentMenuHandle = (HMENU)win32ParentImpl->getMenuID();
			
			MENUITEMINFOW thisInfo;
			memset(&thisInfo,0,sizeof(thisInfo));			
			
			thisInfo.cbSize = sizeof(thisInfo);
			thisInfo.fMask = MIIM_SUBMENU;			
			
			if ( NULL != parentMenuHandle ){
				if ( ::GetMenuItemInfoW( parentMenuHandle, itemId_, FALSE, &thisInfo ) ){
					thisInfo.fMask |= MIIM_SUBMENU;
					thisInfo.hSubMenu = (HMENU)getMenuID();
					::SetMenuItemInfoW( parentMenuHandle, itemId_, FALSE, &thisInfo );
				}
				else {
					//throw exception
				}
			}
		}
	}
	else{
		MENUITEMINFOA info;
		memset(&info,0,sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = mask;
		info.fState = state;
		info.fType = type;		
		info.wID = id;
		info.hSubMenu = subMenu;

		AnsiString s = itemName;
		info.cch = s.size();
		char* tmpName = new char[info.cch+1];
		memset( tmpName, 0, (info.cch+1) );
		s.copy( tmpName, info.cch );

		info.dwTypeData = tmpName;

		if ( InsertMenuItemA( menu, child->getIndex()/*info.wID*/, TRUE, &info ) ) {
			win32ChildImpl->itemAdded_ = true;
		}

		delete [] tmpName;

		MenuItem* parentItem = menuItem_->getParent();
		

		if ( NULL != parentItem ) {
			int index = menuItem_->getIndex();

			Win32MenuItem* win32ParentImpl = (Win32MenuItem*)parentItem->getPeer();
			HMENU parentMenuHandle = (HMENU)win32ParentImpl->getMenuID();

			MENUITEMINFOA thisInfo;
			memset(&thisInfo,0,sizeof(thisInfo));			
			
			thisInfo.cbSize = sizeof(thisInfo);
			thisInfo.fMask = MIIM_SUBMENU;			
			
			if ( NULL != parentMenuHandle ){
				if ( ::GetMenuItemInfoA( parentMenuHandle, itemId_, FALSE, &thisInfo ) ){
					thisInfo.fMask |= MIIM_SUBMENU;
					thisInfo.hSubMenu = (HMENU)getMenuID();
					::SetMenuItemInfoA( parentMenuHandle, itemId_, FALSE, &thisInfo );
				}
				else {
					//throw exception
				}
			}
		}
	}	

	/**
	check to see if we have children that have not yet been added
	*/
	fixChildren( child );	
}

void Win32MenuItem::fixChildren( MenuItem* child )
{
	if ( child->hasChildren() ) {
		Enumerator<MenuItem*>* children = child->getChildren();
		while ( children->hasMoreElements() ) {
			MenuItem* item = children->nextElement();
			Win32MenuItem* itemPeer = (Win32MenuItem*) item->getPeer();
			if ( false == itemPeer->itemAdded_ ) {
				item->setMenuOwner( child->getMenuOwner() );
				Win32MenuItem* peer = (Win32MenuItem*) child->getPeer();
				peer->insertSimpleMenuItem( item, (HMENU)peer->getMenuID() );
			}
		}
	}
}


void Win32MenuItem::addChild( MenuItem* child )
{
	VCF_ASSERT( NULL != child );
	
	insertSimpleMenuItem( child, (HMENU)getMenuID() );	

	//mark the child as being bound to the peer
	long state = child->getState();
	state |= MenuItem::mdsBoundToMenuPeer;
	child->setState( state );
}

void Win32MenuItem::insertChild( const unsigned long& index, MenuItem* child )
{
	child->setIndex( index );
	insertSimpleMenuItem( child, itemHandle_ );
}

void Win32MenuItem::deleteChild( MenuItem* child )
{
	int index = child->getIndex();

	Win32MenuItem* peer = (Win32MenuItem*)child->getPeer();
	peer->itemAdded_ = false;
	DeleteMenu( (HMENU)getMenuID(), peer->itemId_, MF_BYCOMMAND );
}

void Win32MenuItem::deleteChild( const unsigned long& index )
{
	MenuItem* child = menuItem_->getChildAt(index);
	Win32MenuItem* peer = (Win32MenuItem*)child->getPeer();
	peer->itemAdded_ = false;

	DeleteMenu( (HMENU)getMenuID(), peer->itemId_, MF_BYCOMMAND );
}

void Win32MenuItem::clearChildren()
{
	int count = GetMenuItemCount( itemHandle_ );
	for ( int i=0;i<count;i++ ){
		if ( !DeleteMenu( itemHandle_, 0, MF_BYPOSITION ) ) {
			int err = GetLastError();
			StringUtils::traceWithArgs( Format("DeleteMenu( %p, 0, MF_BYPOSITION ) failed,GetLastError(): %d\n") %
										itemHandle_ % err );
		}
	}
}

bool Win32MenuItem::isChecked()
{
	if ( true == menuItem_->isSeparator() ){
		return false;
	}
	/**
	JC
	Fix for bug
	[ 1119206 ] Win32MenuItem::isChecked returns "false". Allways!!!
	*/
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		if ( NULL != menuHandle ){
			MENUITEMINFO info;
			memset(&info,0,sizeof(info));
			info.cbSize = sizeof(MENUITEMINFO);
			info.fMask = MIIM_STATE;
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){

				return ((info.fState & MFS_CHECKED) != 0) ? true : false;
			}
		}
	}

	return false;
}

void Win32MenuItem::setChecked( const bool& checked )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	int index = menuItem_->getIndex();
	MENUITEMINFO info;
	memset(&info,0,sizeof(info));
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STATE;
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
				if ( checked ){
					info.fState |= MFS_CHECKED;
					info.fState &= ~MFS_UNCHECKED;
				}
				else {
					info.fState &= ~MFS_CHECKED;
					info.fState |= MFS_UNCHECKED;
				}

				SetMenuItemInfo( menuHandle, itemId_, FALSE, &info );
			}
		}
	}
}

bool Win32MenuItem::hasParent()
{
	return false;
}

MenuItem* Win32MenuItem::getParent()
{
	return menuItem_->getParent();
}

MenuItem* Win32MenuItem::getChildAt( const unsigned long& index )
{
	return NULL;
}

bool Win32MenuItem::isEnabled()
{
	if ( true == menuItem_->isSeparator() ){
		return false;
	}

	MenuItem* parent = getParent();
	if ( NULL != parent ) {
		int index = menuItem_->getIndex();


		MENUITEMINFO info;
		memset(&info,0,sizeof(info));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_STATE;
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		//HMENU menuHandle = (HMENU)getMenuID();
		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
				bool res = ((info.fState == MFS_ENABLED) != 0) ? true : false;
				return res;
			}
			else {
				int err = GetLastError();
			}
		}
	}
	return false;
}

void Win32MenuItem::setEnabled( const bool& enabled )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	int index = menuItem_->getIndex();
	MENUITEMINFO info;
	memset(&info,0,sizeof(info));
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STATE;
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
				if ( true == enabled ){
					info.fState |= MFS_ENABLED;
					info.fState &= ~MFS_DISABLED;
				}
				else {
					info.fState &= ~MFS_ENABLED;
					info.fState |= MFS_DISABLED;

				}

				SetMenuItemInfo( menuHandle, itemId_, FALSE, &info );
			}
		}
	}
}

bool Win32MenuItem::isVisible()
{
	return true;
}

void Win32MenuItem::setVisible( const bool& visible )
{
	int index = menuItem_->getIndex();
	if ( true == visible ){

	}
	else {
		//RemoveMenu( itemHandle_, index, MF_BYPOSITION );
	}
}

bool Win32MenuItem::getRadioItem()
{
	return false;
}

void Win32MenuItem::setRadioItem( const bool& value )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	int index = menuItem_->getIndex();

	//MENUITEMINFO info = {0};
	//info.cbSize = sizeof(MENUITEMINFO);
	//info.fMask = MIIM_TYPE | MIIM_STATE;
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		Enumerator<MenuItem*>* children = parent->getChildren();
		int count = 0;
		while ( children->hasMoreElements() ) {
			count ++;
			children->nextElement();
		}
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();

		CheckMenuRadioItem( menuHandle, 0, count-1, itemId_, MF_BYCOMMAND );

		/*


		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, index, TRUE, &info ) ){

				info.fType |= MFT_RADIOCHECK | MFT_STRING;
				info.dwTypeData = 0;
				info.cch = 0;
				if ( true == value ){
					info.fState |= MFS_CHECKED;
				}
				else {
					info.fState &= ~MFS_CHECKED;
				}

				SetMenuItemInfo( menuHandle, index, TRUE, &info );
			}
		}
		*/
	}
}

void Win32MenuItem::setMenuItem( MenuItem* item )
{
	menuItem_ = item;
}

String Win32MenuItem::generateCaption( MenuItem* item, String caption )
{
	String acceleratorText;
	VCF::AcceleratorKey* accelerator = item->getAccelerator();
	//generate accelerator text if we are not owner drawn
	if ( !item->canPaint() && (NULL != accelerator) ) {
		
		if ( accelerator->hasCtrlKey() ) {			
			acceleratorText += "Ctrl";
		}

		if ( accelerator->hasShiftKey() ) {
			if ( !acceleratorText.empty() ) {
				acceleratorText += "+";
			}
			acceleratorText += "Shift";
		}

		if ( accelerator->hasAltKey() ) {
			if ( !acceleratorText.empty() ) {
				acceleratorText += "+";
			}
			acceleratorText += "Alt";
		}

		if ( !acceleratorText.empty() ) {
			acceleratorText += "+";
		}

		acceleratorText += StringUtils::translateVKCodeToString( (VirtualKeyCode)accelerator->getKeyCode() );		
	}

	if ( !acceleratorText.empty() ) {
		caption = caption + "\t" + acceleratorText;
	}

	return caption;
}

void Win32MenuItem::setCaption( const String& caption )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	int index = menuItem_->getIndex();

	String realCaption = generateCaption( menuItem_, caption );

	if ( System::isUnicodeEnabled() ) {
		MENUITEMINFOW info;
		memset(&info,0,sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = MIIM_TYPE;
		MenuItem* parent = getParent();
		if ( NULL != parent ){
			MenuItemPeer* parentPeer = parent->getPeer();
			HMENU menuHandle = (HMENU)parentPeer->getMenuID();
			if ( NULL != menuHandle ){
				if ( GetMenuItemInfoW( menuHandle, itemId_, FALSE, &info ) ){
					info.cch = realCaption.size();

					VCFChar* tmpName = new VCFChar[info.cch+1];
					memset( tmpName, 0, (info.cch+1)*sizeof(VCFChar) );
					realCaption.copy( tmpName, info.cch );

					info.dwTypeData = tmpName;

					SetMenuItemInfoW( menuHandle, itemId_, FALSE, &info );

					delete [] tmpName;
				}
			}
		}
	}
	else {
		MENUITEMINFOA info;
		memset(&info,0,sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = MIIM_TYPE;
		MenuItem* parent = getParent();
		if ( NULL != parent ){
			MenuItemPeer* parentPeer = parent->getPeer();
			HMENU menuHandle = (HMENU)parentPeer->getMenuID();
			if ( NULL != menuHandle ){
				if ( GetMenuItemInfoA( menuHandle, itemId_, FALSE, &info ) ){
					AnsiString tmpCaption = realCaption;

					info.cch = tmpCaption.size();

					char* tmpName = new char[info.cch+1];
					memset( tmpName, 0, (info.cch+1)*sizeof(char) );
					tmpCaption.copy( tmpName, info.cch );

					info.dwTypeData = tmpName;

					SetMenuItemInfoA( menuHandle, itemId_, FALSE, &info );

					delete [] tmpName;
				}
			}
		}
	}


}

OSHandleID Win32MenuItem::getMenuID()
{
	if ( NULL != menuItem_ ){
		//throw exception !!!
		//throw InvalidPointerException();
		Menu* menuOwner = menuItem_->getMenuOwner();
		if ( NULL == menuOwner ){
			//throw exception !!!!
			//throw InvalidPointerException();
			MenuItem* parent = menuItem_->getParent();
			while ( parent != NULL ) {
				menuOwner = parent->getMenuOwner();
				if ( NULL != menuOwner ) {
					break;
				}
				parent = parent->getParent();
			}
		}

		if ( (NULL == itemHandle_) && (NULL != menuOwner)  ){
			PopupMenu* popupOwner = dynamic_cast<PopupMenu*>( menuOwner );
			if ( NULL != popupOwner ){
				itemHandle_ = ::CreatePopupMenu();
				Win32MenuItem::menuItemHandleMap[itemHandle_] = menuItem_;
			}
			else {
				MenuBar* menuBarOwner = dynamic_cast<MenuBar*>( menuOwner );
				if ( NULL != menuBarOwner ){
					if ( menuItem_->hasParent() ) {
						itemHandle_ = ::CreatePopupMenu();
						Win32MenuItem::menuItemHandleMap[itemHandle_] = menuItem_;
					}
					else {
						itemHandle_ = ::CreateMenu();
						Win32MenuItem::menuItemHandleMap[itemHandle_] = menuItem_;
					}
				}
				else {
					throw RuntimeException(MAKE_ERROR_MSG("Unknown or Invalid Menu Item owner"), __LINE__);
				}
			}

			if ( NULL == itemHandle_  ){
				throw RuntimeException(MAKE_ERROR_MSG("Error allocation Resources for Menu Item Peer"), __LINE__);
			}
		}
	}
	return (OSHandleID)itemHandle_;
}

MenuItem* Win32MenuItem::getMenuItemFromID( const uint32 id )
{
	MenuItem* result = NULL;

	std::map<uint32, MenuItem*>::iterator found = Win32MenuItem::menuItemMap.find( id );
	if ( found != Win32MenuItem::menuItemMap.end() ){
		result = found->second;
	}
	return result;
}

MenuItem* Win32MenuItem::getMenuItemFromHandle( HMENU handle )
{
	MenuItem* result = NULL;

	std::map<HMENU, MenuItem*>::iterator found = Win32MenuItem::menuItemHandleMap.find( handle );
	if ( found != Win32MenuItem::menuItemHandleMap.end() ){
		result = found->second;
	}
	return result;
}

void Win32MenuItem::setAcceleratorKey( AcceleratorKey* accelerator )
{
	//just call set caption to reset the menu item caption, 
	//which will in turn take into consideration the presence of the
	//accelerator

	setCaption( menuItem_->getCaption() );
}

void Win32MenuItem::setAsSeparator( const bool& isSeperator )
{
	int index = menuItem_->getIndex();
	MENUITEMINFO info;
	memset(&info,0,sizeof(info));
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_TYPE | MIIM_STATE;
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
				if ( true == isSeperator ) {
					info.fType |= MFT_SEPARATOR;
				}
				else {
					info.fType &= ~MFT_SEPARATOR;
				}

				SetMenuItemInfo( menuHandle, itemId_, FALSE, &info );
			}
		}
	}
}

void Win32MenuItem::changePaintState()
{
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		
		if ( NULL != menuHandle ){
			
			MENUITEMINFO info;
			memset(&info,0,sizeof(info));
			info.cbSize = sizeof(MENUITEMINFO);
			info.fMask = MIIM_TYPE;
			
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
					
				bool ownerDrawn = (info.fType & MFT_OWNERDRAW) ? true : false;
				if ( ownerDrawn != menuItem_->canPaint() ) {
					if ( menuItem_->canPaint() ) {
						info.fType |= MFT_OWNERDRAW;
					}
					else {
						info.fType &= ~MFT_OWNERDRAW;
					}
					SetMenuItemInfo( menuHandle, itemId_, FALSE, &info );
				}
			}
		}
	}
}

void Win32MenuItem::fillInMeasureItemInfo( MEASUREITEMSTRUCT& measureItemInfo )
{
	Size menuSz;

	if ( menuItem_->isSeparator() ) {
		menuSz = UIToolkit::getUIMetricSize( UIMetricsManager::mtMenuItemSeparatorSize );
	}
	else {
		String caption = menuItem_->getCaption();
		if ( menuItem_->getUseLocaleStrings() ) {
			caption = System::getCurrentThreadLocale()->translate( caption );
		}
		
		caption = generateCaption( menuItem_, caption );
		menuSz = UIToolkit::getUIMetricSize( UIMetricsManager::mtMenuItemSize, caption );
	}
	

	measureItemInfo.itemWidth = menuSz.width_;
	measureItemInfo.itemHeight = menuSz.height_;

/*
	int index = menuItem_->getIndex();
	MENUITEMINFO info = {0};
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_TYPE;
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
				if ( ODT_MENU != measureItemInfo.CtlType ) {
					return;
				}

				if ( (info.fType & MFT_SEPARATOR) != 0 ) {
					// separator: use half system height and zero width
					measureItemInfo.itemHeight = GetSystemMetrics(SM_CYMENU)>>1;
					measureItemInfo.itemWidth  = 0;
				}
				else {
					// compute size of text: use DrawText with DT_CALCRECT
					NONCLIENTMETRICS ncInfo;
					ncInfo.cbSize = sizeof(ncInfo);
					::SystemParametersInfo (SPI_GETNONCLIENTMETRICS, sizeof(ncInfo), &ncInfo, 0);
					HFONT menuHFont = CreateFontIndirect( &ncInfo.lfMenuFont );
					if ( NULL != menuHFont ) {
						String caption = menuItem_->getCaption();
						if ( menuItem_->getUseLocaleStrings() ) {
							caption = System::getCurrentThreadLocale()->translate( caption );
						}

						caption = generateCaption( menuItem_, caption );

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
						measureItemInfo.itemHeight = maxVal<int>( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );

						// width is width of text plus a bunch of stuff
						int cx = rcText.right - rcText.left;	// text width
						cx += CXTEXTMARGIN << 1;		// L/R margin for readability
						cx += CXGAP;					// space between button and menu text

						//cx += szButton_.cx<<1;		// button width (L=button; R=empty margin)

						// whatever value I return in lpms->itemWidth, Windows will add the
						// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
						//
						cx += GetSystemMetrics(SM_CXMENUCHECK)-1;
						measureItemInfo.itemWidth = cx;		// done deal

						::DeleteObject( menuHFont );
						::DeleteDC( dc );
					}
				}
			}
		}
	}
	*/
}


/**
$Id$
*/
