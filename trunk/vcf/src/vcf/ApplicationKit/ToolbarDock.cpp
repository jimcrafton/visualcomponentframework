//ToolbarDock.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ToolbarDock.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/Containers.h"

using namespace VCF;




ToolbarDock::ToolbarDock()
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );
	dockSide_ = tdsTop;
	backgroundImage_ = NULL;
	isUsingBackground_ = false;
	allowsDockDragging_ = true;
	backgroundStyle_ = tbksNone;
	setHeight( DEFAULT_TOOLBAR_HEIGHT );
	setAlignment( AlignTop );
	DockManager::getDockManager()->addDock( this );

	originalHeightWidth_ = 0.0;
}

ToolbarDock::~ToolbarDock()
{
	DockManager::getDockManager()->removeDock( this );
}

void ToolbarDock::recalcToolbarLayout()
{
	int currentDockRow = -1;
	double totalDelta = 0.0;
	/*
	Enumerator<Control*>* children = getChildren();
	while ( children->hasMoreElements() ) {
		Control* child = children->nextElement();
		Toolbar* toolbar = (Toolbar*)child;
		if ( currentDockRow != toolbar->getDockRow() ) {
			currentDockRow = toolbar->getDockRow();
			switch ( dockSide_ ) {
				case tdsTop : case tdsBottom : {
					totalDelta += toolbar->getPreferredHeight() + 4;
					toolbar->setWidth( 200 );
				}
				break;

				case tdsLeft : case tdsRight :{
					totalDelta += toolbar->getWidth() + 4;
				}
				break;
			}
		}
	}
	*/
	switch ( dockSide_ ) {
		case tdsTop : case tdsBottom : {
			setHeight( totalDelta );
		}
		break;

		case tdsLeft : case tdsRight : {
			setWidth( totalDelta );
		}
		break;
	}
}

void ToolbarDock::add( Control* child )
{
	DelegatedContainer<ToolbarDock>::add( child );
	recalcToolbarLayout();
}

void ToolbarDock::add( Control* child, const AlignmentType& alignment )
{
	DelegatedContainer<ToolbarDock>::add( child, alignment );
	recalcToolbarLayout();
}

ToolbarDockSide ToolbarDock::getDockSide()
{
	return dockSide_;
}

void ToolbarDock::setDockSide( const ToolbarDockSide& dockSide )
{
	dockSide_ = dockSide;
}

Image* ToolbarDock::getBackground()
{
	return backgroundImage_;
}

void ToolbarDock::setBackground( Image* background )
{
	backgroundImage_ = background;
}

ToolbarBackgroundStyle ToolbarDock::getBackgroundStyle()
{
	return backgroundStyle_;
}

void ToolbarDock::setBackgroundStyle( const ToolbarBackgroundStyle& backgroundStyle )
{
	backgroundStyle_ = backgroundStyle;
}

bool ToolbarDock::isUsingBackground()
{
	return isUsingBackground_;
}

void ToolbarDock::setUsingBackground( const bool& usingBackground )
{
	isUsingBackground_ = usingBackground;
}

bool ToolbarDock::allowsDragging()
{
	return allowsDockDragging_;
}

void ToolbarDock::setAllowsDragging( const bool& allowsDrag )
{
	allowsDockDragging_ = allowsDrag;
}

void ToolbarDock::paint( GraphicsContext* context )
{
	CustomControl::paint( context );
	if ( Component::csDesigning & getComponentState() ){
		Rect r = getBounds();
		r.inflate( -1, -1 );
		Color* oldColor = context->getColor();
		context->setColor( Color::getColor("black") );
		context->rectangle( &r );
		context->strokePath();
		context->setColor( oldColor );
	}
	paintChildren( context );
}

void ToolbarDock::mouseDown( MouseEvent* event )
{

}

void ToolbarDock::mouseMove( MouseEvent* event )
{

}

void ToolbarDock::mouseUp( MouseEvent* event )
{

}

void ToolbarDock::addToolbar( Toolbar* toolbar )
{
	switch ( dockSide_ ) {
		case tdsTop : {
			setHeight( originalHeightWidth_ );
			add( toolbar, AlignLeft );
		}
		break;

		case tdsLeft : {
			setWidth( originalHeightWidth_ );
			add( toolbar, AlignTop );
		}
		break;

		case tdsRight : {
			setWidth( originalHeightWidth_ );
			add( toolbar, AlignTop );
		}
		break;

		case tdsBottom : {
			setHeight( originalHeightWidth_ );
			add( toolbar, AlignLeft );
		}
		break;
	}
}

Toolbar* ToolbarDock::findToolbar( Point* pt )
{
	Toolbar* result = NULL;
	return result;
}

void ToolbarDock::remove( Control* child )
{
	DelegatedContainer<ToolbarDock>::remove( child );

	if ( getChildCount() <= 0 ) {
		switch ( dockSide_ ) {
			case tdsTop : {
				originalHeightWidth_ = getHeight();
				setHeight( 1 );
			}
			break;

			case tdsLeft : {
				originalHeightWidth_ = getWidth();
				setWidth( 1 );
			}
			break;

			case tdsRight : {
				originalHeightWidth_ = getWidth();
				setWidth( 1 );
			}
			break;

			case tdsBottom : {
				originalHeightWidth_ = getHeight();
				setHeight( 1 );
			}
			break;
		}

		Control* parent = getParent();
		Container* parentContainer = parent->getContainer();
		if ( NULL != parentContainer ) {
			parentContainer->resizeChildren(NULL);
		}
	}
}



/**
*DockManager implementation
*/

DockManager* DockManager::create()
{
	if ( NULL == DockManager::dockManagerInstance ) {
		DockManager::dockManagerInstance = new DockManager();
		DockManager::dockManagerInstance->init();
	}

	return DockManager::dockManagerInstance;
}


DockManager::DockManager()
{

}

DockManager::~DockManager()
{

}

void DockManager::removeDock( ToolbarDock* dock )
{
	std::vector<ToolbarDock*>::iterator found = std::find( docks_.begin(), docks_.end(), dock );
	if ( found != docks_.end() ) {
		docks_.erase( found );
	}
}

ToolbarDock* DockManager::findDock( Point* point )
{
	ToolbarDock* result = NULL;

	std::vector<ToolbarDock*>::iterator it = docks_.begin();
	Point tmpPt;
	while ( it != docks_.end() ) {
		ToolbarDock* dock = *it;
		tmpPt = *point;
		dock->getParent()->translateFromScreenCoords( &tmpPt );
		Rect bounds = dock->getBounds();
		switch ( dock->getDockSide() ) {
			case tdsTop : case tdsBottom : {
				if ( dock->getChildCount() == 0 ) {
					bounds.inflate( 0, 20 );
				}
			}
			break;

			case tdsLeft : case tdsRight :{
				if ( dock->getChildCount() == 0 ) {
					bounds.inflate( 20, 0 );
				}
			}
			break;
		}

		if ( true == bounds.containsPt( &tmpPt ) ) {
			result = dock;
			break;
		}

		it++;
	}
	return result;
}

void DockManager::addFloatingToolbar( Toolbar* toolbar )
{
	floatingToolbars_.push_back( toolbar );
}

void DockManager::removeFloatingToolbar( Toolbar* toolbar )
{
	std::vector<Toolbar*>::iterator found = std::find( floatingToolbars_.begin(), floatingToolbars_.end(), toolbar );
	if ( found != floatingToolbars_.end() ) {
		floatingToolbars_.erase( found );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.19  2004/04/03 15:48:45  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.17.2.2  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.17.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.17  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.4.3  2003/10/31 05:06:38  ddiego
*added toolbar impl
*
*Revision 1.16.4.2  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.16.4.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.16  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.3  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.15.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15.2.1  2003/03/12 03:13:25  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.14.2  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14.14.1  2002/12/27 23:05:10  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.14  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.2  2002/04/27 15:52:52  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.13.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.13  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


