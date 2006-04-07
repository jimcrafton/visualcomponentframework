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

	EventHandler* ev = new GenericEventHandler<Menu> ( this, &Menu::handleEvent, "Menu::handleEvent" );

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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.3  2005/08/28 05:14:17  ddiego
*small changes to component editor class.
*
*Revision 1.3.2.2  2005/08/27 04:49:35  ddiego
*menu fixes.
*
*Revision 1.3.2.1  2005/08/25 01:48:19  ddiego
*minor update to popupmenu code
*
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/08 03:27:26  ddiego
*fix for popup menus
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
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
*Revision 1.11.2.1  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.11  2003/08/09 02:56:45  ddiego
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
*Revision 1.10.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:13:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.7  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


