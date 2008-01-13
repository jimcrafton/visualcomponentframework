//MenuBar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MenuBarPeer.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"

using namespace VCF;

MenuBar::MenuBar():
	Menu(),
	peer_(NULL),
	frame_(NULL)
{
	init();
}

MenuBar::MenuBar( Component* owner ):
	Menu( owner ),
	peer_(NULL),
	frame_(NULL)
{
	init();	
}

MenuBar::MenuBar( const String& name, Component* owner ):
	Menu( name, owner ),
	peer_(NULL),
	frame_(NULL)
{
	init();	
}

MenuBar::MenuBar( const String& name ):
	Menu( name ),
	peer_(NULL),
	frame_(NULL)
{
	init();
}


MenuBar::~MenuBar()
{

}

void MenuBar::destroy()
{
	if ( NULL != peer_ ){
		delete peer_;
		peer_ = NULL;
	}

	Menu::destroy();
}

void MenuBar::init()
{
	peer_ = UIToolkit::createMenuBarPeer( this );

	if ( NULL == peer_ ){
		//throw exception
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	setRootMenuItem( new DefaultMenuItem() );
	MenuItem* item = getRootMenuItem();

	peer_->setMenuItems( item );

	item->setMenuOwner( this );
	item->setName( "RootMenuItem" );

	CallBack* mih =
		new ClassProcedure1<MenuItemEvent*,MenuBar>( this, &MenuBar::onMenutItemAdded, "MenuBar::onMenutItemAdded" );

	MenuItemChanged += mih;
	//item->addItemAddedHandler( mih );

	mih =
		new ClassProcedure1<MenuItemEvent*,MenuBar>( this, &MenuBar::onMenutItemDeleted, "MenuBar::onMenutItemDeleted" );

	MenuItemChanged += mih;

	//item->addItemDeletedHandler( mih );

	//CallBack* ev = new ClassProcedure1<Event*,MenuBar> ( this, &MenuBar::handleEvent, "MenuBar::handleEvent" );

	//ComponentAdded += ev;
	//ComponentRemoved += ev;
}

void MenuBar::onMenutItemAdded( MenuItemEvent* event )
{
	if ( event->getType() == MenuItem::miAdded ) {
		peer_->update();
	}
}

void MenuBar::onMenutItemDeleted( MenuItemEvent* event )
{
	if ( event->getType() == MenuItem::miRemoved ) {
		peer_->update();
	}
}

Frame* MenuBar::getFrame()
{
	return frame_;
}

void MenuBar::setFrame( Frame* frame )
{
	peer_->setFrame( frame );
	frame_ = frame;
}

void MenuBar::handleEvent( Event* event )
{
	Menu::handleEvent( event );
}


/**
$Id$
*/
