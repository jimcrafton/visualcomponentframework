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
	UIComponent( owner ),
	rootMenuItem_(NULL)
{

}

Menu::Menu( const String& name, Component* owner ):
	UIComponent( name, owner ),
	rootMenuItem_(NULL)
{

}

Menu::Menu( const String& name ):
	UIComponent( name ),
	rootMenuItem_(NULL)
{

}

Menu::~Menu()
{

}

void Menu::destroy()
{
	//if ( NULL != rootMenuItem_ ){
	//	rootMenuItem_->release();
	//	rootMenuItem_ = NULL;
	//}

	UIComponent::destroy();
}

MenuItem* Menu::getRootMenuItem()
{
	return rootMenuItem_;
}

void Menu::setRootMenuItem( MenuItem* item )
{
	if ( NULL != rootMenuItem_ ) {
		rootMenuItem_->getOwner()->removeComponent( rootMenuItem_ );
	}
	rootMenuItem_ = item;
	if ( NULL != rootMenuItem_ ){
		rootMenuItem_->setMenuOwner( this );
		addComponent( rootMenuItem_ );
	}
}

void Menu::itemChanged( const int& eventType, MenuItem* item )
{
	MenuItemEvent event(item,eventType);

	MenuItemChanged( &event );
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
	UIComponent::handleEvent( event );
	switch ( event->getType() ){
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			MenuItem* item = dynamic_cast<MenuItem*>(child);
			if ( NULL != item ) {
				MenuItem* root = getRootMenuItem();
				if ( root != item ) {
					root->addChild( item );
					if ( !(MenuItem::mdsBoundToMenuPeer & item->getDisplayState()) ) {
						root->getPeer()->addChild( item );
					}
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
