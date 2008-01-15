//DefaultMenuItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"
#include "vcf/ApplicationKit/MenuManager.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;

static DefaultMenuItem* previousSelectedItem = NULL;

DefaultMenuItem::DefaultMenuItem():
	//peer_(NULL),
	//index_(0),
	menuOwner_(NULL),
	parent_(NULL),	
	currentAccelerator_(NULL)
{
	init();
}

DefaultMenuItem::DefaultMenuItem( const String& caption, MenuItem* parent, Menu* menuOwner ):
	//peer_(NULL),
	//index_(0),
	menuOwner_(NULL),
	parent_(NULL),
	currentAccelerator_(NULL)
{
	init();

	setCaption( caption );	
	
	if ( NULL != parent ){
		parent->addChild( this );
	}

	setMenuOwner( menuOwner );
}

DefaultMenuItem::~DefaultMenuItem()
{

	if ( NULL != currentAccelerator_ ) {
		UIToolkit::removeAccelerator( (VirtualKeyCode)currentAccelerator_->getKeyCode(),
																currentAccelerator_->getModifierMask(), this );
	}

	if ( this == previousSelectedItem )	{
		previousSelectedItem = NULL;
	}
	else if ( NULL == getParent() ) {
		previousSelectedItem = NULL;
	}

	menuItems_.clear();
}

void DefaultMenuItem::init()
{
	setTag(-1);

	displayState_ |= MenuItem::mdsEnabled;
	displayState_ |= MenuItem::mdsVisible;

	EventHandler* ev = new ClassProcedure1<Event*,DefaultMenuItem> ( this, &DefaultMenuItem::handleEvent, "DefaultMenuItem::handleEvent" );

	ComponentAdded += ev;
	ComponentRemoved += ev;
}

bool DefaultMenuItem::containsPoint( Point * pt )
{
	return true;
}

uint32 DefaultMenuItem::getIndex()  
{
	Menu* owner = getMenuOwner();
	if ( NULL == owner ) {
		return MenuItem::InvalidMenuIndex;
	}
	return owner->getItemIndex( this );
}

void DefaultMenuItem::setIndex( const uint32& index ){}
//{
//	index_ = index;
//}


void DefaultMenuItem::paint( GraphicsContext* context, Rect* paintRect )
{
	//StringUtils::trace( "DefaultMenuItem::paint " + paintRect->toString() +"\n" );
	bounds_ = *paintRect;

	String text = caption_;
	if ( this->getUseLocaleStrings() ) {
		text = System::getCurrentThreadLocale()->translate( caption_ );
	}

	//context->textAt( paintRect->left_, paintRect->top_, text );

	MenuState state;
	
	state.menuCaption_ = text;

	state.setEnabled( isEnabled() );
	state.setSelected( isSelected() );
	
	state.setHighlighted( isHighlighted() );

	state.setToggled( isChecked() );
	state.setHasChildren( hasChildren() );
	state.setSeparator( isSeparator() );

	context->drawThemeMenuItem( paintRect, state );

	context->drawThemeMenuItemText( paintRect, state );
}

bool DefaultMenuItem::isSelected() const 
{
	return (displayState_ & MenuItem::mdsSelected) ? true : false;
}

void DefaultMenuItem::setSelected( const bool& selected )
{
	if ( (NULL != previousSelectedItem) && (previousSelectedItem != this) ) {
		previousSelectedItem->setSelected( false );
	}

	if ( selected ) {
		displayState_ |= MenuItem::mdsSelected;

		//ItemEvent event( this, ITEM_EVENT_SELECTED );
		//ItemSelected( &event );

		getMenuOwner()->itemChanged( MenuItem::miSelected, this );
	}
	else {
		displayState_ &= ~MenuItem::mdsSelected;
	}	
	
	previousSelectedItem = this;
}

bool DefaultMenuItem::isHighlighted()
{
	return (displayState_ & MenuItem::mdsHighlighted) ? true : false;	
}

void DefaultMenuItem::setHighlighted( const bool& val )
{
	if ( val ) {
		displayState_ |= MenuItem::mdsHighlighted;		
	}
	else {
		displayState_ &= ~MenuItem::mdsHighlighted;
	}
}

Enumerator<MenuItem*>* DefaultMenuItem::getChildren()
{
	return menuItems_.getEnumerator();
}

void DefaultMenuItem::addChild( MenuItem* child )
{
	VCF_ASSERT( child != this );

	menuItems_.push_back( child );

	child->setParent( this );

	if ( NULL == child->getOwner() ) {
		addComponent( child );
	}

	child->setMenuOwner( getMenuOwner() );

	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miAdded, child );
	}
}

void DefaultMenuItem::insertChild( const uint32& index, MenuItem* child )
{
	menuItems_.insert( menuItems_.begin() + index, child );

	if ( NULL == child->getOwner() ) {
		addComponent( child );
	}

	/*
	std::vector<MenuItem*>::iterator it = menuItems_.begin() + index;
	uint32 newIndex = index;
	while ( it != menuItems_.end() ) {
		(*it)->setIndex( newIndex );		
		it ++;
		newIndex ++;
	}
	*/

	child->setParent( this );

	child->setMenuOwner( getMenuOwner() );

	//peer_->insertChild( index, child );

	//ItemEvent event( this, ITEM_EVENT_ADDED );
	//ItemAdded( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miAdded, child );
	}	
}

void DefaultMenuItem::deleteChild( MenuItem* child )
{
	std::vector<MenuItem*>::iterator found = std::find( menuItems_.begin(), menuItems_.end(), child );
	if ( found != menuItems_.end() ){
		uint32 index = found - menuItems_.begin();
	
		displayState_ &= ~MenuItem::mdsBoundToMenuPeer;

		Menu* owner = getMenuOwner();
		if ( NULL != owner ) {
			owner->itemChanged( MenuItem::miRemoved, child );
		}

		removeComponent( child );

		menuItems_.erase( found );
		child->free();
		child = NULL;	
	}
}

void DefaultMenuItem::deleteChild( const uint32& index )
{
	//peer_->deleteChild( index );

	std::vector<MenuItem*>::iterator found = menuItems_.begin() + index;
	if ( found != menuItems_.end() ){

		displayState_ &= ~MenuItem::mdsBoundToMenuPeer;

		Menu* owner = getMenuOwner();
		if ( NULL != owner ) {
			owner->itemChanged( MenuItem::miRemoved, *found );
		}

		removeComponent( *found );

        (*found)->free();
		menuItems_.erase( found );
	}
}

void DefaultMenuItem::clearChildren()
{
	std::vector<MenuItem*>::iterator it = menuItems_.begin();
	while ( it != menuItems_.end() ){
		removeComponent( *it );
		(*it)->free();
		it++;
	}
	menuItems_.clear();

	//peer_->clearChildren();
}

bool DefaultMenuItem::isChecked()
{
	return ((displayState_ & MenuItem::mdsChecked) == MenuItem::mdsChecked) ? true : false;// peer_->isChecked();
}

void DefaultMenuItem::setChecked( const bool& checked )
{
	//peer_->setChecked( checked );
	if ( checked ) {
		displayState_ &= ~MenuItem::mdsUnChecked;
		displayState_ |= MenuItem::mdsChecked;
	}
	else {
		displayState_ &= ~MenuItem::mdsChecked;
		displayState_ |= MenuItem::mdsUnChecked;
	}

	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miCheckStateChanged, this );
	}
}

bool DefaultMenuItem::hasParent()
{

	return (parent_ != NULL);
}

MenuItem* DefaultMenuItem::getParent()
{
	return parent_;
}

void DefaultMenuItem::setParent( MenuItem* parent )
{
	VCF_ASSERT( parent != this );

	parent_ = parent;
}

MenuItem* DefaultMenuItem::getChildAt( const uint32& index )
{
	if ( index >= menuItems_.size() ) {
		throw OutOfBoundsException(MAKE_ERROR_MSG(OUT_OF_BOUNDS_EXCEPTION), __LINE__);
	}
	return menuItems_[index];
}

bool DefaultMenuItem::isEnabled()
{
	bool result = (displayState_ & MenuItem::mdsEnabled) ? true : false;

	if ( result ) {
		MenuBar* menuBar = dynamic_cast<MenuBar*>( menuOwner_ );
		if ( NULL != menuBar ) {
			Frame* frame = menuBar->getFrame();
			if ( NULL != frame ) {
				result = frame->isEnabled();
			}
		}
	}
	return result;
}

void DefaultMenuItem::setEnabled( const bool& enabled )
{
	if ( enabled ) {
		displayState_ |= MenuItem::mdsEnabled;
	}
	else {
		displayState_ &= ~MenuItem::mdsEnabled;
	}

	//peer_->setEnabled( enabled );

	AcceleratorKey* accel = getAccelerator();
	if ( NULL != accel ) {
		accel->setEnabled( enabled );
	}

	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miEnabledStateChanged, this );
	}
}

bool DefaultMenuItem::isVisible()
{
	return (displayState_ & MenuItem::mdsVisible) ? true : false;
}

void DefaultMenuItem::setVisible( const bool& visible )
{
	if ( visible ) {
		displayState_ |= MenuItem::mdsVisible;
	}
	else {
		displayState_ &= ~MenuItem::mdsVisible;
	}

	//peer_->setVisible( visible );

	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miVisibleStateChanged, this );
	}
}

bool DefaultMenuItem::getRadioItem()
{
	return (displayState_ & MenuItem::mdsRadioItem) ? true : false;
}

void DefaultMenuItem::setRadioItem( const bool& value )
{
	if ( value ) {
		displayState_ |= MenuItem::mdsRadioItem;
	}
	else {
		displayState_ &= ~MenuItem::mdsRadioItem;
	}
	
	//peer_->setRadioItem( value );

	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miRadioStateChanged, this );
	}
}

void DefaultMenuItem::setCaption( const String& caption )
{
	caption_ = caption;

	//peer_->setCaption( caption_ );

	//ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	//ItemChanged( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miCaptionChanged, this );
	}
}

String DefaultMenuItem::getCaption()
{
	return caption_;
}

MenuItemPeer* DefaultMenuItem::getPeer()
{
	return MenuManager::getMenuItemPeer(this); //peer_;
}

bool DefaultMenuItem::hasChildren()
{
	return ! menuItems_.empty();
}

void DefaultMenuItem::click()
{
	if ( ! isEnabled() ) {
		return;
	}

	MenuItemEvent event( this, MENU_ITEM_EVENT_CLICKED );

	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {		
		MenuItemClicked( &event );
	}
}

void DefaultMenuItem::update()
{
	Action* action = getAction();
	if ( NULL != action ) {
		action->update();
	}
	else {
		MenuItemEvent event( this, MENU_ITEM_EVENT_UPDATED );
		MenuItemUpdate( &event );
	}
}

Menu* DefaultMenuItem::getMenuOwner()
{
	return menuOwner_;
}

void DefaultMenuItem::setMenuOwner( Menu* menuOwner )
{
	menuOwner_ = menuOwner;
	std::vector<MenuItem*>::iterator it = menuItems_.begin();
	while ( it != menuItems_.end() ){
		MenuItem* child = *it;
		if ( NULL != child ) {
			Menu* prevOwner = child->getMenuOwner();
			child->setMenuOwner( menuOwner );
		}
		it++;
	}
}

bool DefaultMenuItem::canPaint() const
{
	return (displayState_ & Item::idsCanPaint) ? true : false;
}

void DefaultMenuItem::setCanPaint( const bool& val )
{
	if ( val ) {
		displayState_ |= Item::idsCanPaint;
	}
	else {
		displayState_ &= ~Item::idsCanPaint;
	}

	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miCanPaintStateChanged, this );
	}
}


bool DefaultMenuItem::isSeparator()
{
	return (displayState_ & MenuItem::mdsSeparator) ? true : false;;
}

void DefaultMenuItem::setSeparator( const bool& separator )
{
	if ( separator ) {
		displayState_ |= MenuItem::mdsSeparator;
	}
	else {
		displayState_ &= ~MenuItem::mdsSeparator;
	}

	//peer_->setAsSeparator( separator );

	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miSeparatorStateChanged, this );
	}
}

void DefaultMenuItem::setImageIndex( const int32& imageIndex )
{
	imageIndex_ = imageIndex;
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miImageIndexChanged, this );
	}
}


AcceleratorKey* DefaultMenuItem::getAccelerator() 
{
	AcceleratorKey* result = NULL;

	if ( NULL != currentAccelerator_ ) {
		result = currentAccelerator_;
	}
	else {
		Action* action = getAction();
		if ( NULL != action ) {
			result = action->getAccelerator();
		}
	}

	return result;
}

void DefaultMenuItem::setAcceleratorKey( const VirtualKeyCode& keyCode, const uint32& modifierMask )
{
	CallBack* eventHandler = this->getCallback( "DefaultMenuItem::onAccelerator" );
	if ( NULL == eventHandler ) {
		eventHandler = new ClassProcedure1<KeyboardEvent*,DefaultMenuItem>( this, &DefaultMenuItem::onAccelerator, "DefaultMenuItem::onAccelerator" );
	}
	AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, modifierMask, (EventHandler*)eventHandler );

	setAcceleratorKey( newAccelKey );
}

void DefaultMenuItem::setAcceleratorKey( AcceleratorKey* accelerator )
{
	//remove the old if present
	if ( NULL != currentAccelerator_ ) {
		UIToolkit::removeAccelerator( (VirtualKeyCode)currentAccelerator_->getKeyCode(),
																currentAccelerator_->getModifierMask(), this );
	}

	currentAccelerator_ = accelerator;

	if ( NULL != currentAccelerator_ ) {
		UIToolkit::registerAccelerator( currentAccelerator_ );
	}

	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miAcceleratorChanged, this );
	}

	//peer_->setAcceleratorKey( currentAccelerator_ );
}

void DefaultMenuItem::onAccelerator( KeyboardEvent* e )
{
	update();

	click();
}

Object* DefaultMenuItem::clone(bool deep)
{
	DefaultMenuItem* result = new DefaultMenuItem( getCaption(), NULL, NULL );

	result->getMenuItemClicked() = getMenuItemClicked();
	result->getMenuItemUpdate() = getMenuItemUpdate();
	result->setTag( getTag() );
	if ( NULL != getAction() ) {
		getAction()->addTarget( result );
	}

	result->setSeparator( isSeparator() );

	AcceleratorKey* accel = getAccelerator();
	if ( NULL != accel ) {		
		if ( accel->getEventHandler() == 
				getCallback( "DefaultMenuItem::onAccelerator" ) ) {

			VirtualKeyCode keyCode = (VirtualKeyCode)accel->getKeyCode();
			uint32 mask = accel->getModifierMask();
			//remove the old one!
			UIToolkit::removeAccelerator( keyCode, mask, this );
			currentAccelerator_ = NULL;
			result->setAcceleratorKey( keyCode, mask );
		}
		else {
			result->setAcceleratorKey( (AcceleratorKey*)accel->clone() );
		}
	}

	return result;
}

uint32 DefaultMenuItem::getChildCount()
{
	return menuItems_.size();
}

void DefaultMenuItem::handleEvent( Event* event )
{
	UIComponent::handleEvent( event );
	switch ( event->getType() ){
		case Action::UpdateEvent : {
			ActionEvent* actionEvent = (ActionEvent*)event;

			if ( actionEvent->isModified() ) {
				setEnabled( actionEvent->isEnabled() );

				if ( !actionEvent->getText().empty() ) {
					setCaption( actionEvent->getText() );
				}

				if ( actionEvent->isExclusiveChecked() ) {
					setRadioItem( actionEvent->isChecked() );
				}
				else {
					setChecked( actionEvent->isChecked() );
				}
			}

		}
		break;

		case Action::AcceleratorChanged : {
			Action* action = (Action*)event->getSource();
		
			//update the peer!
			//peer_->setAcceleratorKey( action->getAccelerator() );
			Menu* owner = getMenuOwner();
			if ( NULL != owner ) {
				owner->itemChanged( MenuItem::miAcceleratorChanged, this );
			}
		}
		break;

		case Component::COMPONENT_ADDED : {
			if ( isLoading() ) {
				ComponentEvent* ev = (ComponentEvent*)event;
				Component* child = ev->getChildComponent();
				MenuItem* item = dynamic_cast<MenuItem*>(child);
				if ( NULL != item ) {
					item->setMenuOwner( getMenuOwner() );
					addChild( item );
				}
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			if ( isDestroying() ) {
				ComponentEvent* ev = (ComponentEvent*)event;
				Component* child = ev->getChildComponent();
				MenuItem* item = dynamic_cast<MenuItem*>(child);
				if ( NULL != item ) {
					if ( displayState_ & MenuItem::mdsBoundToMenuPeer ) {
						deleteChild( item );
					}
				}
			}
		}
		break;

		case Component::COMPONENT_DESTROYED : {
			MenuManager::destroyMenuItemPeer( this );
		}
		break;
	}
}

MenuItem* DefaultMenuItem::findChildNamed( const String& name, const bool& exactMatch )
{
	MenuItem* result = NULL;

	if ( exactMatch ) {	
		std::vector<MenuItem*>::iterator it = menuItems_.begin();
		while ( it != menuItems_.end() ){
			MenuItem* child = *it;
			
			if ( child->getCaption() == name ) {
				result = child;
				break;
			}
			it++;
		}
	}
	else {
		String tmp1 = StringUtils::lowerCase( name );
		String tmp2;
		
		std::vector<MenuItem*>::iterator it = menuItems_.begin();
		while ( it != menuItems_.end() ){
			MenuItem* child = *it;
			tmp2 = StringUtils::lowerCase( child->getCaption() );
			if ( tmp2.find( tmp1 ) != String::npos ) {
				result = child;
				break;
			}
			it++;
		}
	}

	return result;
}

uint32 DefaultMenuItem::getChildIndex( MenuItem* child )
{
	uint32 result = 0;

	std::vector<MenuItem*>::iterator found = std::find( menuItems_.begin(),
														menuItems_.end(),
														child );
	if ( found != menuItems_.end() ) {
		result = found - menuItems_.begin();
	}
	else {
		result = MenuItem::InvalidMenuIndex;
	}

	return result;
}


/**
$Id$
*/
