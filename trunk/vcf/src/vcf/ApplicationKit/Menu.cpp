//Menu.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MenuBarPeer.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"

using namespace VCF;

Menu::Menu():
	rootMenuItem_(NULL)
{

}

Menu::Menu( Component* owner ):
	Component( owner ),
	rootMenuItem_(NULL)
{

}

Menu::Menu( const String& name, Component* owner ):
	Component( name, owner ),
	rootMenuItem_(NULL)
{

}

Menu::Menu( const String& name ):
	Component( name ),
	rootMenuItem_(NULL)
{

}

Menu::~Menu()
{

}

void Menu::destroy()
{
	if ( NULL != rootMenuItem_ ){
		rootMenuItem_->release();
		rootMenuItem_ = NULL;
	}

	Component::destroy();
}

MenuItem* Menu::getRootMenuItem()
{
	return rootMenuItem_;
}

void Menu::setRootMenuItem( MenuItem* item )
{
	rootMenuItem_ = item;
	if ( NULL != rootMenuItem_ ){
		rootMenuItem_->setMenuOwner( this );
	}
}

void Menu::itemChanged( const int& eventType, MenuItem* item )
{
	MenuItemEvent event(item,eventType);

	MenuItemChanged.fireEvent( &event );
}

uint32 Menu::getItemIndex( MenuItem* item )
{
	uint32 result = 0;

	MenuItem* parent = item->getParent();
	if ( NULL != parent ) {
		result = parent->getChildIndex( item );
	}

	return result;
}

void Menu::handleEvent( Event* event )
{
	Component::handleEvent( event );
	switch ( event->getType() ){
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			MenuItem* item = dynamic_cast<MenuItem*>(child);
			if ( NULL != item ) {
				getRootMenuItem()->addChild( item );
				if ( !(MenuItem::mdsBoundToMenuPeer & item->getState()) ) {
					getRootMenuItem()->getPeer()->addChild( item );
				}
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
		}
		break;
	}
}


/**
$Id$
*/
