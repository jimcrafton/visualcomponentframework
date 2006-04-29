//Toolbar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/ToolbarPeer.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


//******************************************************************************
//ToolbarItem
//******************************************************************************

ToolbarItem::ToolbarItem():
	data_(NULL),
	imageIndex_(0),
	imageStateIndex_(0),
	itemControl_(NULL)
{
	tag_ = -1;
	itemState_ = tisEnabled;
}

void ToolbarItem::click()
{
	ButtonEvent event( this, ToolbarItem::tbItemClicked );

	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {
		ItemClicked.fireEvent( &event );
	}

}

bool ToolbarItem::updateAction()
{
	if ( !Component::updateAction() ) {
		Event event( this, ToolbarItem::tbItemUpdate );
		ItemUpdate.fireEvent( &event );
		return true;
	}

	return false;
}

void ToolbarItem::handleEvent( Event* event )
{
	Component::handleEvent( event );
	switch ( event->getType() ){
		case Action::UpdateEvent : {
			ActionEvent* actionEvent = (ActionEvent*)event;


			setEnabled( actionEvent->isEnabled() );

			Toolbar* toolbar = (Toolbar*)getControl();

			if ( NULL != toolbar ) {
				if ( toolbar->getShowButtonCaptions() ) {
					setCaption( actionEvent->getText() );
				}
				else {
					setTooltip( actionEvent->getText() );
				}
			}

			if ( this->isChecked() && (actionEvent->getState() & tisPressed) ) {
				setPressed( true );
			}
			else if ( isChecked() ) {
				setPressed( false );
			}
		}
		break;	
		
		
	}
}

bool ToolbarItem::containsPoint( Point * pt )
{
	return bounds_.containsPt(pt);
}

void ToolbarItem::setItemControl( Control* control )
{
	itemControl_ = control;

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbItemControlAdded, this );
	}
}

void ToolbarItem::setAsSeparator()
{
	setState( tisSeparator );
}

void ToolbarItem::setPressed( bool val )
{
	if ( ( (itemState_ & ToolbarItem::tisPressed) != 0 ) == val ) {
		return;
	}

	long state = itemState_;
	if ( val ) {
		state |= tisPressed;
	}
	else {
		state &= ~tisPressed;
	}
	setState( state );
}

bool ToolbarItem::isEnabled()
{
	return (itemState_ & ToolbarItem::tisEnabled) ? true : false;
}

void ToolbarItem::setEnabled( const bool& val )
{
	if ( isEnabled() == val ) {
		return;
	}

	long state = itemState_;
	if ( val ) {
		state |= ToolbarItem::tisEnabled;
	}
	else {
		state &= ~ToolbarItem::tisEnabled;
	}

	setState( state );
}

void ToolbarItem::setState( const long& state )
{
	if ( itemState_ == state ) {
		return ;
	}

	itemState_ = state;

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbStateChanged, this );
	}
}

void ToolbarItem::setStateImageIndex( const long& index )
{
	imageStateIndex_ = index;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbStateImageIndexChanged, this );
	}
}

ulong32 ToolbarItem::getIndex()
{
	return ((ToolbarModel*)model_)->getItemIndex(this);
}

void ToolbarItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbImageIndexChanged, this );
	}
}

void ToolbarItem::setIndex( const unsigned long& index )
{
	//no-op
}

bool ToolbarItem::isSelected()
{
	return (itemState_ & tisSelected) ? true : false;
}

void ToolbarItem::setSelected( const bool& selected )
{
	if ( isSelected() == selected ) {
		return;
	}

	if ( selected ) {
		itemState_ |= tisSelected;
	}
	else {
		itemState_ &= ~tisSelected;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbSelected, this );
	}
}

void ToolbarItem::internal_setBounds( const Rect& bounds ) //Parameter made const for ANSI compliance - ACH
{
	bounds_ = bounds;
	if ( NULL != itemControl_ ) {
		Rect controlBounds = itemControl_->getBounds();
		//if ( !(controlBounds == bounds_) ) {
			itemControl_->setBounds( &bounds_ );
		//}
	}
}

void ToolbarItem::setBounds( Rect* bounds )
{
	internal_setBounds( *bounds );
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbDimensionsChanged, this );
	}
}

void ToolbarItem::setWidth( const double& val )
{
	bounds_.right_ = bounds_.left_ + val;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbDimensionsChanged, this );
	}
}


void ToolbarItem::setCaption( const String& val )
{
	if ( val == caption_ ) {
		return;
	}

	caption_ = val;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbCaptionChanged, this );
	}
}

void ToolbarItem::setTooltip( const String& val )
{
	if ( val == tooltip_ ) {
		return;
	}

	tooltip_ = val;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbTooltipChanged, this );
	}
}

void ToolbarItem::setGrouped( const bool& val )
{
	if ( val == isGrouped() ) {
		return;
	}

	if ( val ) {
		itemState_ |= tisGrouped;
	}
	else {
		itemState_ &= ~tisGrouped;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbGroupChanged, this );
	}
}

bool ToolbarItem::isGrouped()
{
	return (itemState_ & tisGrouped) ? true : false;
}

void ToolbarItem::setChecked( const bool& val )
{
	if ( val == isChecked() ) {
		return;
	}

	if ( val ) {
		itemState_ |= tisChecked;
	}
	else {
		itemState_ &= ~tisChecked;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbCheckChanged, this );
	}
}

bool ToolbarItem::isChecked()
{
	return (itemState_ & tisChecked) ? true : false;
}

//******************************************************************************
//ToolbarModel
//******************************************************************************

ToolbarModel::ToolbarModel()
{
	itemsContainer_.initContainer( toolbarItems_ );
}

ToolbarModel::~ToolbarModel()
{
	std::vector<ToolbarItem*>::iterator it = toolbarItems_.begin();
	while ( it != toolbarItems_.end() ) {
		ToolbarItem* item = *it;
		item->release();
		it ++;
	}

	toolbarItems_.clear();
}

void ToolbarModel::addItem( ToolbarItem* item )
{
	toolbarItems_.push_back( item );
	item->setModel( this );
	itemChanged( ToolbarItem::tbAdded, item );
}

void ToolbarModel::insertItem( ToolbarItem* item, const ulong32& index )
{
	toolbarItems_.insert( toolbarItems_.begin() + index, item );
	item->setModel( this );
	itemChanged( ToolbarItem::tbAdded, item );
}

void ToolbarModel::removeItem( ToolbarItem* item )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {

		toolbarItems_.erase( found );

		itemChanged( ToolbarItem::tbRemoved, item );
	}
}

void ToolbarModel::itemChanged( const ulong32& eventType, ToolbarItem* item )
{
	ToolbarModelEvent e(this, eventType);
	e.setItem( item );

	ModelChanged.fireEvent( &e );
}

ulong32 ToolbarModel::getItemIndex( ToolbarItem* item )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {
		return found - toolbarItems_.begin();
	}
	return 0;
}

void ToolbarModel::setItemIndex( ToolbarItem* item, const ulong32& newIndex )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {
		toolbarItems_.erase( found );

		toolbarItems_.insert( toolbarItems_.begin()+newIndex, item );

		itemChanged( ToolbarItem::tbAdded, item );
	}
}







//******************************************************************************
//Toolbar
//******************************************************************************

Toolbar::Toolbar():
	Control(),
	toolbarPeer_(NULL),
	showButtonCaptions_(false),
	buttonCaptionsHorizontal_(false)
{
	toolbarPeer_ = UIToolkit::createToolbarPeer( this );
	peer_ = dynamic_cast<ControlPeer*>(toolbarPeer_);	

	setViewModel( new ToolbarModel() );

	addComponent( getViewModel() );

	peer_->create( this );

	setVisible( true );

	setContainer( new StandardContainer() );
}


Toolbar::~Toolbar()
{
	this->removeFromUpdateList();
}


void Toolbar::setImageList( ImageList* imageList )
{
	imageList_ = imageList;
	toolbarPeer_->setImageList( imageList );
}

void Toolbar::setShowButtonCaptions( const bool& val )
{
	showButtonCaptions_ = val;
	toolbarPeer_->showButtonCaptions( showButtonCaptions_ );

	Control* parent = getParent();
	if ( NULL != parent ) {
		parent->getContainer()->resizeChildren(NULL);
	}
}

void Toolbar::setButtonSize( const Size& buttonSize )
{
	buttonSize_ = buttonSize;
	toolbarPeer_->setButtonSize( buttonSize_ );

	Control* parent = getParent();
	if ( NULL != parent ) {
		parent->getContainer()->resizeChildren(NULL);
	}
}

void Toolbar::setButtonCaptionsHorizontal( const bool& val )
{
	buttonCaptionsHorizontal_ = val;

	toolbarPeer_->setButtonCaptionPlacementHorizontal( val );

	Control* parent = getParent();
	if ( NULL != parent ) {
		parent->getContainer()->resizeChildren(NULL);
	}
}

void Toolbar::handleEvent( Event* event )
{
	Control::handleEvent( event );
	switch ( event->getType() ){
		/*
		case Component::COMPONENT_NEEDS_UPDATING : {
			ToolbarModel* model = getToolbarModel();
			if ( NULL != model ) {
				Enumerator<ToolbarItem*>* items = model->getToolbarItems();
				while ( items->hasMoreElements() ) {
					ToolbarItem* item = items->nextElement();
					item->handleEvent( event );
				}
			}
		}
		break;
		*/

		case CONTROL_SIZED:{
			Control::handleEvent( event );
			if ( getParent() ) {
				getParent()->getContainer()->resizeChildren( NULL );
			}
		}
		break;
	}
}

void Toolbar::paint( GraphicsContext* context )
{
	Rect innerBounds = getClientBounds( true );
	BackgroundState bkg;
	bkg.setEnabled( isEnabled() );
	bkg.setActive( isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;	
	
	context->drawThemeBackground( &innerBounds, bkg );	
}

void Toolbar::setEnableAutoResize( const bool& val )
{
	toolbarPeer_->setEnableAutoResize( val );
}

bool Toolbar::isAutoResizeEnabled()
{
	return toolbarPeer_->isAutoResizeEnabled();
}







//******************************************************************************
//Toolbar::FloatingToolbar
//******************************************************************************


Toolbar::FloatingToolbar::FloatingToolbar()
{
	this->setFrameStyle( fstToolbarBorderFixed );
}

Toolbar::FloatingToolbar::~FloatingToolbar()
{

}


/**
$Id$
*/
