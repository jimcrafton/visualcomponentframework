//Win32MenuItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"


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
	MENUITEMINFO info = {0};
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_ID  | MIIM_STATE | MIIM_TYPE;
	info.fState = MFS_ENABLED;
	if ( true == child->isSeparator() ){
		info.fType |= MFT_SEPARATOR;
	}
	else {
		info.fType = MFT_STRING;
	}

	//put this back in later
	if ( true == child->canPaint() ) {
		info.fType |= MFT_OWNERDRAW;
	}
	info.wID = win32ChildImpl->itemId_;

	if ( child->hasChildren() ){
		info.fMask |= MIIM_SUBMENU;
		info.hSubMenu = (HMENU) itemImpl->getMenuID();
	}
	String itemName = child->getCaption();
	if ( child->getUseLocaleStrings() ) {
		itemName = System::getCurrentThreadLocale()->translate( itemName );
	}

	info.cch = itemName.size();

	char* tmpName = new char[info.cch+1];
	memset( tmpName, 0, info.cch+1 );
	itemName.copy( tmpName, info.cch );

	info.dwTypeData = tmpName;

	if ( InsertMenuItem( menu, child->getIndex()/*info.wID*/, TRUE, &info ) ) {
		win32ChildImpl->itemAdded_ = true;
	}


	MenuItem* parentItem = menuItem_->getParent();

	if ( NULL != parentItem ) {
		int index = menuItem_->getIndex();
		MENUITEMINFO thisInfo = {0};


		thisInfo.cbSize = sizeof(MENUITEMINFO);
		thisInfo.fMask = MIIM_SUBMENU;
		Win32MenuItem* win32ParentImpl = (Win32MenuItem*)parentItem->getPeer();
		HMENU parentMenuHandle = (HMENU)win32ParentImpl->getMenuID();

		if ( NULL != parentMenuHandle ){
			if ( GetMenuItemInfo( parentMenuHandle, itemId_, FALSE, &thisInfo ) ){
				thisInfo.fMask |= MIIM_SUBMENU;
				thisInfo.hSubMenu = (HMENU)getMenuID();
				::SetMenuItemInfo( parentMenuHandle, itemId_, FALSE, &thisInfo );
			}
			else {
				//throw exception
			}
		}

	}

	/**
	check to see if we have children that have not yet been added
	*/
	fixChildren( child );

	delete [] tmpName;
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
	if ( NULL != child ){
		insertSimpleMenuItem( child, (HMENU)getMenuID() );
	}
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
			StringUtils::traceWithArgs( "DeleteMenu( %p, 0, MF_BYPOSITION ) failed,GetLastError(): %d\n",
										itemHandle_, err );
		}
	}
}

bool Win32MenuItem::isChecked()
{
	if ( true == menuItem_->isSeparator() ){
		return false;
	}

	int index = menuItem_->getIndex();

	MENUITEMINFO info = {0};
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STATE;
	HMENU menuHandle = (HMENU)getMenuID();
	if ( NULL != menuHandle ){
		if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){
			return ((info.fState & MFS_CHECKED) != 0) ? true : false;
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
	MENUITEMINFO info = {0};
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


		MENUITEMINFO info = {0};
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
	MENUITEMINFO info = {0};
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

void Win32MenuItem::setCaption( const String& caption )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	int index = menuItem_->getIndex();

	if ( System::isUnicodeEnabled() ) {
		MENUITEMINFOW info = {0};
		info.cbSize = sizeof(info);
		info.fMask = MIIM_TYPE;
		MenuItem* parent = getParent();
		if ( NULL != parent ){
			MenuItemPeer* parentPeer = parent->getPeer();
			HMENU menuHandle = (HMENU)parentPeer->getMenuID();
			if ( NULL != menuHandle ){
				if ( GetMenuItemInfoW( menuHandle, itemId_, FALSE, &info ) ){
					info.cch = caption.size();

					VCFChar* tmpName = new VCFChar[info.cch+1];
					memset( tmpName, 0, (info.cch+1)*sizeof(VCFChar) );
					caption.copy( tmpName, info.cch );

					info.dwTypeData = tmpName;

					SetMenuItemInfoW( menuHandle, itemId_, FALSE, &info );

					delete [] tmpName;
				}
			}
		}
	}
	else {
		MENUITEMINFOA info = {0};
		info.cbSize = sizeof(info);
		info.fMask = MIIM_TYPE;
		MenuItem* parent = getParent();
		if ( NULL != parent ){
			MenuItemPeer* parentPeer = parent->getPeer();
			HMENU menuHandle = (HMENU)parentPeer->getMenuID();
			if ( NULL != menuHandle ){
				if ( GetMenuItemInfoA( menuHandle, itemId_, FALSE, &info ) ){
					AnsiString tmpCaption = caption;

					info.cch = tmpCaption.size();

					char* tmpName = new char[info.cch+1];
					memset( tmpName, 0, info.cch+1 );
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

void Win32MenuItem::setAsSeparator( const bool& isSeperator )
{
	int index = menuItem_->getIndex();
	MENUITEMINFO info = {0};
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

void Win32MenuItem::fillInMeasureItemInfo( MEASUREITEMSTRUCT& measureItemInfo )
{

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
						measureItemInfo.itemHeight = __max( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );

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
}

void Win32MenuItem::drawDefaultMenuItem( const UINT& idCtl, DRAWITEMSTRUCT& drawItemStruct )
{
	if ( drawItemStruct.CtlType != ODT_MENU ) {
		return; // not handled by me
	}

	if ( NULL == drawItemStruct.hDC ) {
		return; //throw exception ??
	}

	int index = menuItem_->getIndex();
	MENUITEMINFO info = {0};
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_TYPE | MIIM_CHECKMARKS;
	MenuItem* parent = getParent();
	if ( NULL != parent ){
		MenuItemPeer* parentPeer = parent->getPeer();
		HMENU menuHandle = (HMENU)parentPeer->getMenuID();
		if ( NULL != menuHandle ){
			if ( GetMenuItemInfo( menuHandle, itemId_, FALSE, &info ) ){

				if ( (info.fType & MFT_SEPARATOR) != 0 ) {
					// draw separator
					RECT tmp = drawItemStruct.rcItem;

					tmp.top += (tmp.bottom - tmp.top) >>1; 	// vertical center

					DrawEdge( drawItemStruct.hDC, &tmp, EDGE_ETCHED, BF_TOP);		// draw separator line
				}
				else {
					// not a separator
					bool menuDisabled = (drawItemStruct.itemState & ODS_GRAYED) != 0;
					bool menuSelected = (drawItemStruct.itemState & ODS_SELECTED) != 0;
					bool menuChecked  = (drawItemStruct.itemState & ODS_CHECKED) != 0;
					bool menuHasButn = false;



					RECT tmpBtnRect = {drawItemStruct.rcItem.left + 2, drawItemStruct.rcItem.top,
										drawItemStruct.rcItem.left + 2 + (drawItemStruct.rcItem.right - drawItemStruct.rcItem.left),
										drawItemStruct.rcItem.top + (drawItemStruct.rcItem.bottom - drawItemStruct.rcItem.top) };

					// no button: look for custom checked/unchecked bitmaps
					if ( (true == menuChecked) || (NULL != info.hbmpUnchecked) ) {
						menuHasButn =
							draw3DCheckmark( drawItemStruct.hDC, tmpBtnRect,
												menuSelected,
												menuChecked ? info.hbmpChecked : info.hbmpUnchecked );
					}

					// Done with button, now paint text. First do background if needed.
					int cxButn = tmpBtnRect.bottom - tmpBtnRect.top;				// width of button

					COLORREF colorBG = ::GetSysColor( menuSelected ? COLOR_HIGHLIGHT : COLOR_MENU );

					if ( (true == menuSelected) || (drawItemStruct.itemAction==ODA_SELECT) ) {
						// selected or selection state changed: paint text background
						RECT rcBG = drawItemStruct.rcItem;	// whole rectangle

						if ( true == menuHasButn) {	// if there's a button:
							rcBG.left += cxButn + CXGAP;			//  don't paint over it!
						}
						fillMenuItemRect( drawItemStruct.hDC, rcBG, colorBG );
					}

					// compute text rectangle and colors
					RECT rcText = drawItemStruct.rcItem;				 // start w/whole item
					rcText.left += cxButn + CXGAP + CXTEXTMARGIN; // left margin
					rcText.right -= cxButn;				 // right margin
					::SetBkMode( drawItemStruct.hDC, TRANSPARENT );			 // paint transparent text

					COLORREF colorText =
						GetSysColor( menuDisabled ?  COLOR_GRAYTEXT :
										(menuSelected ? COLOR_HIGHLIGHTTEXT : COLOR_MENUTEXT));

					// Now paint menu item text.	No need to select font,
					// because windows sets it up before sending WM_DRAWITEM
					//
					if ( (true == menuDisabled) && ((false == menuSelected) || (colorText == colorBG)) ) {
						// disabled: draw hilite text shifted southeast 1 pixel for embossed
						// look. Don't do it if item is selected, tho--unless text color same
						// as menu highlight color. Got it?
						//
						rcText.left += 1;
						rcText.top += 1;

						drawMenuItemText( drawItemStruct.hDC, rcText, GetSysColor(COLOR_3DHILIGHT) );
						rcText.left -= 1;
						rcText.top -= 1;
					}

					drawMenuItemText( drawItemStruct.hDC, rcText, colorText ); // finally!
				}
			}
		}
	}
}

bool Win32MenuItem::draw3DCheckmark( HDC dc, const RECT& rc, const bool& bSelected, HBITMAP hbmCheck )
{
	bool result = false;

	return result;
}


// Shorthand to fill a rectangle with a solid color.
void Win32MenuItem::fillMenuItemRect( HDC dc, const RECT& rc, COLORREF color )
{
	HBRUSH brush = ::CreateSolidBrush( color );

	HBRUSH oldBrush = (HBRUSH)::SelectObject( dc, brush );

	PatBlt( dc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, PATCOPY);

	::SelectObject( dc, oldBrush );
	DeleteObject( brush );
}

void Win32MenuItem::drawMenuItemText( HDC dc, RECT rc, COLORREF color )
{
	String left = menuItem_->getCaption();
	if ( menuItem_->getUseLocaleStrings() ) {
		left = System::getCurrentThreadLocale()->translate( left );
	}

	String right;

	int tabPos = left.find('\t');
	if ( tabPos != String::npos ) {
		if ( tabPos >= 0 ) {
			right = left.substr( tabPos + 1, left.size() - tabPos );

			left  = left.substr( 0, tabPos );
		}
	}

	::SetTextColor( dc, color );

	if ( System::isUnicodeEnabled() ) {
		DrawTextW( dc, left.c_str(), left.size(), &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
	}
	else {
		AnsiString tmp = left;
		DrawTextA( dc, tmp.c_str(), tmp.size(), &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
	}

	if (tabPos > 0) {
		if ( System::isUnicodeEnabled() ) {
			DrawTextW( dc, right.c_str(), right.size(), &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_RIGHT);
		}
		else {
			AnsiString tmp = right;
			DrawTextA( dc, tmp.c_str(), tmp.size(), &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_RIGHT);
		}

	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:05:00  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.25.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.25  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.22.2.2  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.22.2.1  2004/01/15 16:14:19  ddiego
*some minor change to the WIn32MenuItem class to support inserting menus better
*
*Revision 1.22  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.21.2.5  2003/10/09 22:05:20  ddiego
*menu item fix
*
*Revision 1.21.2.4  2003/10/08 04:53:54  ddiego
*minor futzing around with menu updates
*
*Revision 1.21.2.3  2003/09/18 17:56:44  ddiego
*added a fix to menu items (in hte assignment of their Win32 menuid)
*and to foward update events correctly (this was occasionally not working
*right for menus that had been dynamically inserted later on, after
*the main menu had already been constructed)
*
*Revision 1.21.2.2  2003/09/05 04:31:24  ddiego
*some minor fixes to menus
*
*Revision 1.21.2.1  2003/08/25 21:34:59  ddiego
*miscellaneous
*
*Revision 1.21  2003/08/09 02:56:46  ddiego
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
*Revision 1.20.2.1  2003/07/05 04:04:45  ddiego
*added more AGG support
*  added a common AGG header to use when accessing the AGG API directly
*  see the graphics/AggCommon.h header for this
*  Made some minor changes to Path to work a bit simpler
*  Implemented Polygon completely,
*  Implemented BasicFill and BasicStroke - using AGG
*
*Revision 1.20  2003/05/17 20:37:37  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.19.2.1  2003/03/12 03:12:39  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.19  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.18.2.3  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.18.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.18.2.1  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.18  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.17.10.3  2002/11/04 04:50:18  ddiego
*bug fixes are:
*void Win32MenuItem::clearChildren(), was passing in an incorrect index into DeleteMenu()
*fixed an issue when deleting a project from a workspace. This was crashing due to open
*documents with bad pointers. Closing a project now closes all open documents that are
*associated with the project
*Verified that the new file and new class and new form, and new project and checking the validity of
*entered data.
*Fixed a bug in Win32Dialog where the Frame::allowClose() virtual method was not being
*called.
*Fixed a bug in the Delegate class which would allow multiple additions of the same event handler.
*
*Revision 1.17.10.2  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.17.10.1  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.17  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.16.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.16.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.16  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.15  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


