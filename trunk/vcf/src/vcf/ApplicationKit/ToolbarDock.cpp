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
$Id$
*/
