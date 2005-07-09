//OSXMenuItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXMenuItem.h"




using namespace VCF;


uint32 OSXMenuItem::globalMenuItemID = 0;

OSXMenuItem::OSXMenuItem( MenuItem* item ):
	itemID_(0),
	menuItem_(item),
	itemHandle_(NULL),
	itemAdded_(false)
{
	init();
}

OSXMenuItem::OSXMenuItem():
	itemID_(0),
	menuItem_(NULL),
	itemHandle_(NULL),
	itemAdded_(false)
{
	init();
}

OSXMenuItem::~OSXMenuItem()
{
	if ( NULL != itemHandle_ ) {
		DisposeMenu( itemHandle_ );
	}	
}

void OSXMenuItem::init()
{
	OSXMenuItem::globalMenuItemID ++;
	itemID_ = OSXMenuItem::globalMenuItemID;
}

bool OSXMenuItem::isMenuItemRoot( MenuItem* item )
{
	bool result = false;
		
	if ( NULL != item ) {
		MenuItem* parent = item->getParent();
		Menu* menuOwner = item->getMenuOwner();
		if ( NULL == menuOwner ) {
			while ( parent != NULL ) {
				menuOwner = parent->getMenuOwner();
				if ( NULL != menuOwner ) {
					break;
				}
				parent = parent->getParent();
			}
			parent = item->getParent();
		}
		
		if ( NULL != menuOwner ) {
			result = (menuOwner->getRootMenuItem() == item);
		}
		else if ( NULL == parent ) {
			result = true;
		}
	}
	return result;
}
	
bool OSXMenuItem::isParentMenuItemRoot( MenuItem* item )
{
	bool result = false;
		
	if ( NULL != item ) {
		MenuItem* parent = item->getParent();
		Menu* menuOwner = item->getMenuOwner();
		if ( NULL == menuOwner ) {
			while ( parent != NULL ) {
				menuOwner = parent->getMenuOwner();
				if ( NULL != menuOwner ) {
					break;
				}
				parent = parent->getParent();
			}
			parent = item->getParent();
		}
		
		if ( NULL != menuOwner ) {
			result = (menuOwner->getRootMenuItem() == parent);
		}
		else  if ( NULL != parent ) {
			if ( NULL == parent->getParent() ) {
				result = true;
			}
		}
	}
	return result;
}


bool OSXMenuItem::isMenuItemRoot()
{
	return OSXMenuItem::isMenuItemRoot( menuItem_ );
}

bool OSXMenuItem::isParentMenuItemRoot()
{
	return OSXMenuItem::isParentMenuItemRoot( menuItem_ );
}

void OSXMenuItem::addChild( MenuItem* child )
{
	unsigned long index = child->getIndex();// maxVal<unsigned long>( menuItem_->getChildCount()-1, 0 );
	
	insertChild( index, child );
}

void OSXMenuItem::fixChildren( MenuItem* child )
{
	if ( child->hasChildren() ) {
		Enumerator<MenuItem*>* children = child->getChildren();
		while ( children->hasMoreElements() ) {
			MenuItem* item = children->nextElement();
			OSXMenuItem* itemPeer = (OSXMenuItem*) item->getPeer();
			if ( false == itemPeer->itemAdded_ ) {
				item->setMenuOwner( child->getMenuOwner() );
				OSXMenuItem* peer = (OSXMenuItem*) child->getPeer();
				peer->addChild( item );
			}
		}
	}
}

void OSXMenuItem::insertChild( const unsigned long& index, MenuItem* child )
{
	child->setIndex( index );
	
	CFTextString tmp( child->getCaption() );
	//is this child a top level menu item?
	
	
	if ( OSXMenuItem::isParentMenuItemRoot( child ) ) {
		OSXMenuItem* peer = (OSXMenuItem*)child->getPeer();		
		MenuRef handle = (MenuRef) peer->getMenuID();
		if ( NULL != handle ) {
			InsertMenu( handle, peer->itemID_ );
			SetMenuTitleWithCFString( handle, tmp );
			itemAdded_ = true;
		}
		else {
			//we should get picked up later
			return;
		}
	}
	else {
		OSXMenuItem* peer = (OSXMenuItem*)child->getPeer();		
		MenuRef handle = 0;		
		
		if ( menuItem_->hasChildren() && (!isParentMenuItemRoot()) ) {
			OSXMenuItem* parentPeer = (OSXMenuItem*)menuItem_->getParent()->getPeer();
			MenuRef parentRef = (MenuRef) parentPeer->getMenuID();
			int index = menuItem_->getIndex();
			
			GetMenuItemHierarchicalMenu( parentRef, index, &handle );
			if ( NULL == handle ) {		
				handle = (MenuRef) getMenuID();
				
				//apparently the menu index is 1 based! Go figure!
				OSStatus err = SetMenuItemHierarchicalMenu( parentRef, index+1, handle );
				if ( err != noErr ) {
					printf( "Error with SetMenuItemHierarchicalMenu(): %d\n", err );
				}
			}
		}
		else {
			handle = (MenuRef) getMenuID();
		}
		
		MenuItemIndex childIndex = index;
		InsertMenuItemTextWithCFString( handle, tmp, childIndex, 0, peer->itemID_ );	
		itemAdded_ = true;
		
					
		SetMenuCommandProperty( handle, peer->itemID_, 
							VCF_PROPERTY_CREATOR, 
							OSXMenuItem::propertyTag,
							sizeof(child), 
							&child );		
	}
	
	/**
	check to see if we have children that have not yet been added
	*/
	fixChildren( child );
}

void OSXMenuItem::deleteChild( MenuItem* child )
{
	int index = child->getIndex();

	OSXMenuItem* peer = (OSXMenuItem*)child->getPeer();
	MenuRef handle = (MenuRef) getMenuID();	
	
	if ( child->hasChildren() ) {
		DeleteMenu( peer->itemID_ );
	}
	DeleteMenuItem( handle, index + 1 );
}

void OSXMenuItem::deleteChild( const unsigned long& index )
{
	MenuItem* child = menuItem_->getChildAt(index);
	deleteChild( child );
}

void OSXMenuItem::clearChildren()
{
	MenuRef handle = (MenuRef) getMenuID();	
	int start = 1;
	DeleteMenuItems( handle, 1,	menuItem_->getChildCount() );
}

bool OSXMenuItem::isChecked()
{
	bool result = false;
	
	MenuItem* parent = menuItem_->getParent();
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = 0;
	GetItemMark( parentHandle, index, &markChar );
	if ( checkMark == markChar ) {
		result = true;
	}
	return result;
}

void OSXMenuItem::setChecked( const bool& checked )
{
	if ( menuItem_->hasChildren() ) {
		return;
	}
	
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = checked ? checkMark : 0;
	SetItemMark( parentHandle, index, markChar );
}

bool OSXMenuItem::hasParent()
{
	return false;
}

MenuItem* OSXMenuItem::getParent()
{
	return menuItem_->getParent();
}

MenuItem* OSXMenuItem::getChildAt( const unsigned long& index )
{
	return NULL;
}

bool OSXMenuItem::isEnabled()
{
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	
	return IsMenuItemEnabled( parentHandle, index ) ? true : false;
}

void OSXMenuItem::setEnabled( const bool& enabled )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	if ( enabled ) {
		EnableMenuItem( parentHandle, index );
	}
	else {
		DisableMenuItem( parentHandle, index );
	}	
}

bool OSXMenuItem::isVisible()
{
	return true;
}

void OSXMenuItem::setVisible( const bool& visible )
{
	int index = menuItem_->getIndex();
	if ( visible ){

	}
	else {
		//RemoveMenu( itemHandle_, index, MF_BYPOSITION );
	}
}

bool OSXMenuItem::getRadioItem()
{
	bool result = false;
	
	MenuItem* parent = menuItem_->getParent();
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = 0;
	GetItemMark( parentHandle, index, &markChar );
	if ( diamondMark == markChar ) {
		result = true;
	}
	return result;
}

void OSXMenuItem::setRadioItem( const bool& value )
{	
	if ( menuItem_->hasChildren() || menuItem_->isSeparator() ) {
		return;
	}
	
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	CharParameter markChar = value ? diamondMark : 0;
	SetItemMark( parentHandle, index, markChar );
}

void OSXMenuItem::setMenuItem( MenuItem* item )
{
	menuItem_ = item;
}

void OSXMenuItem::setCaption( const String& caption )
{
	if ( true == menuItem_->isSeparator() ){
		return;
	}
	int index = menuItem_->getIndex();
	
	MenuItem* parent = menuItem_->getParent();
	
	if ( NULL != parent ) {
		CFTextString tmp(caption);
		
		if ( isParentMenuItemRoot() ) {
			MenuRef handle = (MenuRef) getMenuID();		
			if ( NULL != handle ) {		
				SetMenuTitleWithCFString( handle, tmp );
			}
		}
		else {
			OSXMenuItem* peer = (OSXMenuItem*)parent->getPeer();
			MenuRef ref = (MenuRef) peer->getMenuID();
			
			SetMenuItemTextWithCFString( ref, index + 1, tmp );
		}
	}
}


/**
This returns an "id" (handle would be a better name) to the menu item.
Not all menu items will have a handle.
If the menuItem_ is the "root" menu item then this is a no-op

*/
OSHandleID OSXMenuItem::getMenuID()
{
	if ( isMenuItemRoot() ) {
		printf( "the menu item is the root item!\n" );
		return 0;
	}
	
	if ( NULL != menuItem_ ){		
		Menu* menuOwner = menuItem_->getMenuOwner();
		//find our owner
		if ( NULL == menuOwner ){
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
				//itemHandle_ = ::CreatePopupMenu();
				//We need to create a popup menu - i.e. a context menu!
				
			}
			else {
				MenuBar* menuBarOwner = dynamic_cast<MenuBar*>( menuOwner );
				/**
				At this point we either have a menu bar, because we are top level 
				items, 
				or..
				We don't, which means we are nested hierarchical menu items
				*/
				if ( NULL != menuBarOwner ){
					if ( isParentMenuItemRoot() ) {
						CreateNewMenu( itemID_,0,&itemHandle_);
						CFTextString tmp( menuItem_->getCaption() );
						SetMenuTitleWithCFString( itemHandle_, tmp );
					}
					else {						
						OSStatus err = CreateNewMenu( itemID_,0,&itemHandle_);						
						if ( noErr != err ) {
							printf( "CreateNewMenu failed. err: %d\n", err );
						}
						CFTextString tmp( menuItem_->getCaption() );
						SetMenuTitleWithCFString( itemHandle_, tmp );
					}
					
					SetMenuCommandProperty( itemHandle_, 0, 
							VCF_PROPERTY_CREATOR, 
							OSXMenuItem::propertyTag,
							sizeof(menuItem_), 
							&menuItem_ );
				}
				else {
					throw RuntimeException(MAKE_ERROR_MSG("Unknown or Invalid Menu Item owner"), __LINE__);
				}
			}

			if ( menuItem_->hasChildren() && NULL == itemHandle_  ){
				throw RuntimeException(MAKE_ERROR_MSG("Error allocation Resources for Menu Item Peer. CreateNewMenu failed."), __LINE__);
			}
		}
	}
	return (OSHandleID)itemHandle_;
}


void OSXMenuItem::setAsSeparator( const bool& isSeperator )
{
	MenuItem* parent = menuItem_->getParent();	
	OSXMenuItem* parentPeer = (OSXMenuItem*)parent->getPeer();
 	MenuRef parentHandle = (MenuRef)parentPeer->getMenuID();
	
	int index = menuItem_->getIndex()+1;
	if ( isSeperator ) {
		ChangeMenuItemAttributes( parentHandle, index, kMenuItemAttrSeparator, 0 );
	}
	else{
		ChangeMenuItemAttributes( parentHandle, index, 0, kMenuItemAttrSeparator );
	}
}

void OSXMenuItem::setAcceleratorKey( AcceleratorKey* accelerator )
{

}






/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*Revision 1.2.2.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
*
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/11/15 05:41:28  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.1.2.1  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*
*/


