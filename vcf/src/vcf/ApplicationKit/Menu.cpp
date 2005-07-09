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
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/06/08 03:27:26  ddiego
*fix for popup menus
*
*Revision 1.2.4.1  2005/06/06 02:34:06  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.12  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.2  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.11.4.1  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.11  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.1  2003/03/12 03:13:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.20.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


