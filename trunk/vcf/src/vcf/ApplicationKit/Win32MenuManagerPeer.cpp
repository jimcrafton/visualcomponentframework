//Win32MenuManagerPeer.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/MenuManagerPeer.h"
#include "vcf/ApplicationKit/Win32MenuManagerPeer.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"

using namespace VCF;

Win32MenuManagerPeer::Win32MenuManagerPeer()
{

}

Win32MenuManagerPeer::~Win32MenuManagerPeer()
{

}

MenuItemPeer* Win32MenuManagerPeer::getMenuItemPeer( MenuItem* item )
{
	MenuItemPeer* result = NULL;

	MenuItemMap::iterator found = menuItemsMap_.find( item );
	if ( found != menuItemsMap_.end() ) {
		result = found->second; 
	}
	else {
		result = UIToolkit::createMenuItemPeer( item );
		result->setMenuItem( item );
		menuItemsMap_.insert( MenuItemMap::value_type(item,(Win32MenuItem*)result) );
	}

	return result;
}

void Win32MenuManagerPeer::destroyMenuItemPeer( MenuItem* item )
{
	MenuItemMap::iterator found = menuItemsMap_.find( item );
	if ( found != menuItemsMap_.end() ) {
		MenuItemPeer* peer = found->second; 
		menuItemsMap_.erase( found );
		delete peer;
	}
}

void Win32MenuManagerPeer::windowActivated( Window* window )
{
	MenuBar* menuBar = window->getMenuBar();
	if ( NULL != menuBar ) {
		
	}
}

void Win32MenuManagerPeer::windowClosed( Window* window )
{

}

void Win32MenuManagerPeer::menuItemChanged( int menuItemEventType, MenuItem* item )
{
	MenuItemPeer* peer = NULL;
	switch ( menuItemEventType ) {
		case MenuItem::miAdded : {
			MenuItem* parent = item->getParent();
			peer = parent->getPeer();
			peer->addChild( item );
		}
		break;

		case MenuItem::miRemoved : {
			MenuItem* parent = item->getParent();
			peer = parent->getPeer();
			peer->deleteChild( item );
		}
		break;

		case MenuItem::miCaptionChanged : {
			peer = item->getPeer();
			peer->setCaption( item->getCaption() );
		}
		break;

		case MenuItem::miStateChanged : {

		}
		break;

		case MenuItem::miSeparatorStateChanged : {
			peer = item->getPeer();
			peer->setAsSeparator( item->isSeparator() );
		}
		break;

		case MenuItem::miCheckStateChanged : {
			peer = item->getPeer();
			peer->setChecked( item->isChecked() );
		}
		break;

		case MenuItem::miRadioStateChanged : {
			peer = item->getPeer();
			peer->setRadioItem( item->getRadioItem() );
		}
		break;

		case MenuItem::miVisibleStateChanged : {
			
		}
		break;

		case MenuItem::miEnabledStateChanged : {
			peer = item->getPeer();
			peer->setEnabled( item->isEnabled() );
		}
		break;

		case MenuItem::miAcceleratorChanged : {
			peer = item->getPeer();
			peer->setAcceleratorKey( item->getAccelerator() );
		}
		break;
		
		case MenuItem::miSelected : {
						
		}
		break;	
	}
}



