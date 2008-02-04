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
	imageStateIndex_(0),
	itemControl_(NULL)
{
	tag_ = -1;
	displayState_ = tisEnabled;
}

void ToolbarItem::click()
{
	ButtonEvent event( this, ToolbarItem::tbItemClicked );

	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {
		ItemClicked( &event );
	}

}

bool ToolbarItem::updateAction()
{
	if ( !UIComponent::updateAction() ) {
		Event event( this, ToolbarItem::tbItemUpdate );
		ItemUpdate( &event );
		return true;
	}

	return false;
}

void ToolbarItem::handleEvent( Event* event )
{
	UIComponent::handleEvent( event );
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

void ToolbarItem::setAsSeparator(const bool& val)
{
	if ( val ) {
		setDisplayState( tisSeparator );
	}
	else {
		setDisplayState( getDisplayState() & ~tisSeparator );
	}
}

void ToolbarItem::setPressed( const bool& val )
{
	if ( ( (displayState_ & ToolbarItem::tisPressed) != 0 ) == val ) {
		return;
	}

	int32 state = displayState_;
	if ( val ) {
		state |= tisPressed;
	}
	else {
		state &= ~tisPressed;
	}
	setDisplayState( state );
}

bool ToolbarItem::isEnabled()
{
	return (displayState_ & ToolbarItem::tisEnabled) ? true : false;
}

void ToolbarItem::setEnabled( const bool& val )
{
	if ( isEnabled() == val ) {
		return;
	}

	int32 state = displayState_;
	if ( val ) {
		state |= ToolbarItem::tisEnabled;
	}
	else {
		state &= ~ToolbarItem::tisEnabled;
	}

	setDisplayState( state );
}

void ToolbarItem::setDisplayState( const int32& state )
{
	if ( displayState_ == state ) {
		return ;
	}

	displayState_ = state;

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbStateChanged, this );
	}
}

void ToolbarItem::setStateImageIndex( const int32& index )
{
	imageStateIndex_ = index;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbStateImageIndexChanged, this );
	}
}

uint32 ToolbarItem::getIndex()
{
	return ((ToolbarModel*)model_)->getItemIndex(this);
}

void ToolbarItem::setImageIndex( const int32& imageIndex )
{
	imageIndex_ = imageIndex;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbImageIndexChanged, this );
	}
}

void ToolbarItem::setIndex( const uint32& index )
{
	//no-op
}

bool ToolbarItem::isSelected()
{
	return (displayState_ & tisSelected) ? true : false;
}

void ToolbarItem::setSelected( const bool& selected )
{
	if ( isSelected() == selected ) {
		return;
	}

	if ( selected ) {
		displayState_ |= tisSelected;
	}
	else {
		displayState_ &= ~tisSelected;
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

double ToolbarItem::getWidth()
{
	return bounds_.getWidth();
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
		displayState_ |= tisGrouped;
	}
	else {
		displayState_ &= ~tisGrouped;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbGroupChanged, this );
	}
}

bool ToolbarItem::isGrouped()
{
	return (displayState_ & tisGrouped) ? true : false;
}

void ToolbarItem::setChecked( const bool& val )
{
	if ( val == isChecked() ) {
		return;
	}

	if ( val ) {
		displayState_ |= tisChecked;
	}
	else {
		displayState_ &= ~tisChecked;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbCheckChanged, this );
	}
}

bool ToolbarItem::isChecked()
{
	return (displayState_ & tisChecked) ? true : false;
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

void ToolbarModel::insertItem( ToolbarItem* item, const uint32& index )
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

void ToolbarModel::itemChanged( const uint32& eventType, ToolbarItem* item )
{
	ToolbarModelEvent e(this, eventType);
	e.setItem( item );

	ModelChanged( &e );
}

uint32 ToolbarModel::getItemIndex( ToolbarItem* item )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {
		return found - toolbarItems_.begin();
	}
	return 0;
}

void ToolbarModel::setItemIndex( ToolbarItem* item, const uint32& newIndex )
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

		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			ToolbarItem* item = dynamic_cast<ToolbarItem*>(child);
			if ( NULL != item ) {
				
				getToolbarModel()->addItem( item );
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
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
