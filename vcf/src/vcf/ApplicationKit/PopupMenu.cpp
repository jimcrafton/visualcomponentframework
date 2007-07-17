//PopupMenu.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/PopupMenuPeer.h"
#include "vcf/ApplicationKit/MenuManager.h"



using namespace VCF;

PopupMenu::PopupMenu( Control* control )
{

	popupPeer_ = UIToolkit::createPopupMenuPeer( this );

	if ( NULL == popupPeer_ ){
		//throw exception
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	if ( NULL != control )	{
		control->addComponent( this );
	}
	setControl( control );

	init();
}

PopupMenu::PopupMenu( Component* owner ):
	Menu( owner )
{
	popupPeer_ = UIToolkit::createPopupMenuPeer( this );

	if ( NULL == popupPeer_ ){
		//throw exception
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	init();
}

PopupMenu::PopupMenu( const String& name, Component* owner ):
	Menu( name, owner )
{
	popupPeer_ = UIToolkit::createPopupMenuPeer( this );

	if ( NULL == popupPeer_ ){
		//throw exception
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	init();
}

PopupMenu::PopupMenu( const String& name ):
	Menu( name )
{
	popupPeer_ = UIToolkit::createPopupMenuPeer( this );

	if ( NULL == popupPeer_ ){
		//throw exception
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	init();
}

PopupMenu::~PopupMenu()
{
	if ( NULL != popupPeer_ ){
		delete popupPeer_;
	}

	popupPeer_ = NULL;
}

void PopupMenu::destroy()
{
	if ( NULL != popupPeer_ ){
		delete popupPeer_;
		popupPeer_ = NULL;
	}

	Menu::destroy();
}

void PopupMenu::init()
{
	MenuManager::registerPopupMenu( this );

	setRootMenuItem( new DefaultMenuItem() );
	
	MenuItem* item = getRootMenuItem();

	item->setMenuOwner( this );
	item->setName( "RootMenuItem" );

	CallBack* ev = new ClassProcedure1<Event*,Menu> ( this, &Menu::handleEvent, "Menu::handleEvent" );

	ComponentAdded += ev;
	ComponentRemoved += ev;
}

MenuItem* PopupMenu::popup( Point* pt )
{
	return popupPeer_->popup( pt );
}

void PopupMenu::setControl( Control* control )
{
	popupPeer_->setControl( control );
}


/**
$Id$
*/
