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

	EventHandler* mih =
		new MenuItemEventHandler<MenuBar>( this, &MenuBar::onMenutItemAdded, "MenuBar::onMenutItemAdded" );

	MenuItemChanged += mih;
	//item->addItemAddedHandler( mih );

	mih =
		new MenuItemEventHandler<MenuBar>( this, &MenuBar::onMenutItemDeleted, "MenuBar::onMenutItemDeleted" );

	MenuItemChanged += mih;

	//item->addItemDeletedHandler( mih );

	EventHandler* ev = new GenericEventHandler<MenuBar> ( this, &MenuBar::handleEvent, "MenuBar::handleEvent" );

	ComponentAdded += ev;
	ComponentRemoved += ev;
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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/08/25 01:48:19  ddiego
*minor update to popupmenu code
*
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/06/08 03:27:26  ddiego
*fix for popup menus
*
*Revision 1.2.4.2  2005/06/06 02:34:06  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.2.4.1  2005/03/15 05:29:01  ddiego
*makes the accelerator check logic a bit smarter and also changes
*teh way menu items test to check whether or not they are enabled.
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
*Revision 1.16  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.14.2.1  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.14  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.2.2  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.13.2.1  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.13  2003/08/09 02:56:45  ddiego
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
*Revision 1.12.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.12  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:13:15  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.2  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10.14.1  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.9  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


