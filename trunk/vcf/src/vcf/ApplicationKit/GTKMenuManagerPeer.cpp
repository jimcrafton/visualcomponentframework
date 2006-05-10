//Win32MenuManagerPeer.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/MenuManagerPeer.h"
#include "vcf/ApplicationKit/GTKMenuManagerPeer.h"

using namespace VCF;

GTKMenuManagerPeer::GTKMenuManagerPeer()
{
}

GTKMenuManagerPeer::~GTKMenuManagerPeer()
{
}

MenuItemPeer* GTKMenuManagerPeer::getMenuItemPeer( MenuItem* item )
{
	MenuItemPeer* result = NULL;
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return result;
}

void GTKMenuManagerPeer::destroyMenuItemPeer( MenuItem* item )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKMenuManagerPeer::windowActivated( Window* window )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKMenuManagerPeer::windowClosed( Window* window )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKMenuManagerPeer::menuItemChanged( int menuItemEventType, MenuItem* item )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");

	switch ( menuItemEventType ) {
	
		case MenuItem::miAdded : {
		}
		break;

		case MenuItem::miRemoved : {
		}
		break;

		case MenuItem::miCaptionChanged : {
		}
		break;
	

		case MenuItem::miStateChanged : {
		}
		break;

		case MenuItem::miCanPaintStateChanged : {
		}
		break;

		case MenuItem::miSeparatorStateChanged : {
		}
		break;

		case MenuItem::miCheckStateChanged : {
		}
		break;

		case MenuItem::miRadioStateChanged : {
		}
		break;

		case MenuItem::miVisibleStateChanged : {
		}
		break;

		case MenuItem::miEnabledStateChanged : {
		}
		break;

		case MenuItem::miAcceleratorChanged : {
		}
		break;
		
		case MenuItem::miSelected : {
		}
		break;	
	}
}


/**
$Id$
*/

