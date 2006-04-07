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


using namespace VCF;

static DefaultMenuItem* previousSelectedItem = NULL;

DefaultMenuItem::DefaultMenuItem():
	//peer_(NULL),
	//index_(0),
	data_(NULL),
	menuOwner_(NULL),
	parent_(NULL),
	imageIndex_(-1),
	currentAccelerator_(NULL)
{
	init();
}

DefaultMenuItem::DefaultMenuItem( const String& caption, MenuItem* parent, Menu* menuOwner ):
	//peer_(NULL),
	//index_(0),
	data_(NULL),
	menuOwner_(NULL),
	parent_(NULL),
	imageIndex_(-1),
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

	//delete peer_;
	//peer_ = NULL;

	menuItems_.clear();
}

void DefaultMenuItem::init()
{
	setTag(-1);

	//peer_ = UIToolkit::createMenuItemPeer( this );

	itemState_ |= MenuItem::mdsEnabled;
	itemState_ |= MenuItem::mdsVisible;

	//if ( NULL == peer_ ){
		//throw exception
	//	throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	//}

	//peer_->setMenuItem( this );

	container_.initContainer( menuItems_ );

	EventHandler* ev = new GenericEventHandler<DefaultMenuItem> ( this, &DefaultMenuItem::handleEvent, "DefaultMenuItem::handleEvent" );

	ComponentAdded += ev;
	ComponentRemoved += ev;
}

bool DefaultMenuItem::containsPoint( Point * pt )
{
	return true;
}

unsigned long DefaultMenuItem::getIndex()
{
	Menu* owner = getMenuOwner();
	if ( NULL == owner ) {
		return MenuItem::InvalidMenuIndex;
	}
	return owner->getItemIndex( this );
}

void DefaultMenuItem::setIndex( const unsigned long& index ){}
//{
//	index_ = index;
//}

void* DefaultMenuItem::getData()
{
	return data_;
}

void DefaultMenuItem::setData( void* data )
{
	data_ = data;
}

void DefaultMenuItem::paint( GraphicsContext* context, Rect* paintRect )
{
	//StringUtils::trace( "DefaultMenuItem::paint " + paintRect->toString() +"\n" );
	bounds_ = *paintRect;

	String text = caption_;
	if ( this->getUseLocaleStrings() ) {
		text = System::getCurrentThreadLocale()->translate( caption_ );
	}

	context->textAt( paintRect->left_, paintRect->top_, text );
}

bool DefaultMenuItem::isSelected()
{
	return (itemState_ & MenuItem::mdsSelected) ? true : false;
}

void DefaultMenuItem::setSelected( const bool& selected )
{
	if ( (NULL != previousSelectedItem) && (previousSelectedItem != this) ) {
		previousSelectedItem->setSelected( false );
	}

	if ( selected ) {
		itemState_ |= MenuItem::mdsSelected;

		//ItemEvent event( this, ITEM_EVENT_SELECTED );
		//ItemSelected.fireEvent( &event );

		getMenuOwner()->itemChanged( MenuItem::miSelected, this );
	}
	else {
		itemState_ &= ~MenuItem::mdsSelected;
	}	
	
	previousSelectedItem = this;
}

Enumerator<MenuItem*>* DefaultMenuItem::getChildren()
{
	return container_.getEnumerator();
}

void DefaultMenuItem::addChild( MenuItem* child )
{
	menuItems_.push_back( child );

	child->setParent( this );

	if ( NULL == child->getOwner() ) {
		addComponent( child );
	}

	//child->setIndex( menuItems_.size() - 1 );

	child->setMenuOwner( getMenuOwner() );

	//peer_->addChild( child );

	//ItemEvent event( this, ITEM_EVENT_ADDED );
	//ItemAdded.fireEvent( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miAdded, child );
	}
}

void DefaultMenuItem::insertChild( const unsigned long& index, MenuItem* child )
{
	menuItems_.insert( menuItems_.begin() + index, child );

	if ( NULL == child->getOwner() ) {
		addComponent( child );
	}

	/*
	std::vector<MenuItem*>::iterator it = menuItems_.begin() + index;
	unsigned long newIndex = index;
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
	//ItemAdded.fireEvent( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miAdded, child );
	}	
}

void DefaultMenuItem::deleteChild( MenuItem* child )
{
	std::vector<MenuItem*>::iterator found = std::find( menuItems_.begin(), menuItems_.end(), child );
	if ( found != menuItems_.end() ){
		unsigned long index = found - menuItems_.begin();
	
		itemState_ &= ~MenuItem::mdsBoundToMenuPeer;

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

void DefaultMenuItem::deleteChild( const unsigned long& index )
{
	//peer_->deleteChild( index );

	std::vector<MenuItem*>::iterator found = menuItems_.begin() + index;
	if ( found != menuItems_.end() ){

		itemState_ &= ~MenuItem::mdsBoundToMenuPeer;

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
	return ((itemState_ & MenuItem::mdsChecked) == MenuItem::mdsChecked) ? true : false;// peer_->isChecked();
}

void DefaultMenuItem::setChecked( const bool& checked )
{
	//peer_->setChecked( checked );
	if ( checked ) {
		itemState_ &= ~MenuItem::mdsUnChecked;
		itemState_ |= MenuItem::mdsChecked;
	}
	else {
		itemState_ &= ~MenuItem::mdsChecked;
		itemState_ |= MenuItem::mdsUnChecked;
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
	parent_ = parent;
}

MenuItem* DefaultMenuItem::getChildAt( const unsigned long& index )
{
	if ( index >= menuItems_.size() ) {
		throw OutOfBoundsException(MAKE_ERROR_MSG(OUT_OF_BOUNDS_EXCEPTION), __LINE__);
	}
	return menuItems_[index];
}

bool DefaultMenuItem::isEnabled()
{
	bool result = (itemState_ & MenuItem::mdsEnabled) ? true : false;

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
		itemState_ |= MenuItem::mdsEnabled;
	}
	else {
		itemState_ &= ~MenuItem::mdsEnabled;
	}

	//peer_->setEnabled( enabled );

	AcceleratorKey* accel = getAccelerator();
	if ( NULL != accel ) {
		accel->setEnabled( enabled );
	}

	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged.fireEvent( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miEnabledStateChanged, this );
	}
}

bool DefaultMenuItem::isVisible()
{
	return (itemState_ & MenuItem::mdsVisible) ? true : false;
}

void DefaultMenuItem::setVisible( const bool& visible )
{
	if ( visible ) {
		itemState_ |= MenuItem::mdsVisible;
	}
	else {
		itemState_ &= ~MenuItem::mdsVisible;
	}

	//peer_->setVisible( visible );

	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged.fireEvent( &event );
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miVisibleStateChanged, this );
	}
}

bool DefaultMenuItem::getRadioItem()
{
	return (itemState_ & MenuItem::mdsRadioItem) ? true : false;
}

void DefaultMenuItem::setRadioItem( const bool& value )
{
	if ( value ) {
		itemState_ |= MenuItem::mdsRadioItem;
	}
	else {
		itemState_ &= ~MenuItem::mdsRadioItem;
	}
	
	//peer_->setRadioItem( value );

	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged.fireEvent( &event );
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
	//ItemChanged.fireEvent( &event );
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
		MenuItemClicked.fireEvent( &event );
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
		MenuItemUpdate.fireEvent( &event );
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

bool DefaultMenuItem::isSeparator()
{
	return (itemState_ & MenuItem::mdsSeparator) ? true : false;;
}

void DefaultMenuItem::setSeparator( const bool& separator )
{
	if ( separator ) {
		itemState_ |= MenuItem::mdsSeparator;
	}
	else {
		itemState_ &= ~MenuItem::mdsSeparator;
	}

	//peer_->setAsSeparator( separator );

	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miSeparatorStateChanged, this );
	}
}

void DefaultMenuItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
	Menu* owner = getMenuOwner();
	if ( NULL != owner ) {
		owner->itemChanged( MenuItem::miImageIndexChanged, this );
	}
}

void DefaultMenuItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
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

void DefaultMenuItem::setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask )
{
	EventHandler* eventHandler = this->getEventHandler( "DefaultMenuItem::onAccelerator" );
	if ( NULL == eventHandler ) {
		eventHandler = new KeyboardEventHandler<DefaultMenuItem>( this, &DefaultMenuItem::onAccelerator, "DefaultMenuItem::onAccelerator" );
	}
	AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, modifierMask, eventHandler );

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
				getEventHandler( "DefaultMenuItem::onAccelerator" ) ) {

			VirtualKeyCode keyCode = (VirtualKeyCode)accel->getKeyCode();
			ulong32 mask = accel->getModifierMask();
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

unsigned long DefaultMenuItem::getChildCount()
{
	return menuItems_.size();
}

void DefaultMenuItem::handleEvent( Event* event )
{
	Component::handleEvent( event );
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
					if ( itemState_ & MenuItem::mdsBoundToMenuPeer ) {
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

MenuItem* DefaultMenuItem::findChildNamedSimilarTo( const String& name )
{
	MenuItem* result = NULL;

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

	return result;
}


MenuItem* DefaultMenuItem::findChildNamed( const String& name )
{
	MenuItem* result = NULL;

	
	std::vector<MenuItem*>::iterator it = menuItems_.begin();
	while ( it != menuItems_.end() ){
		MenuItem* child = *it;
		
		if ( child->getCaption() == name ) {
			result = child;
			break;
		}
		it++;
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
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.3  2006/03/05 02:28:04  ddiego
*updated the Item interface and adjusted the other classes accordingly.
*
*Revision 1.4.2.2  2005/11/17 06:38:38  obirsoy
*. fixed an invalidated vector iterator bug.
*
*Revision 1.4.2.1  2005/08/27 04:49:35  ddiego
*menu fixes.
*
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.4  2005/06/06 02:34:05  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.3.2.3  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.2  2005/03/15 05:29:01  ddiego
*makes the accelerator check logic a bit smarter and also changes
*teh way menu items test to check whether or not they are enabled.
*
*Revision 1.3.2.1  2005/03/14 04:17:23  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/18 06:45:43  ddiego
*updated toolbar btn bug, and added text edit sample.
*
*Revision 1.2.2.2  2004/11/15 05:41:27  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2.2.1  2004/09/07 00:49:12  ddiego
*minor fixes in printg code in graphics kit, and added a 2 ways to print in the printing example.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.28  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.27  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.25.2.3  2004/03/08 04:41:07  ddiego
*minor changes to DocumentManager - allow the use of
*Actions so that other UI elements can be added besides menu
*items (like Toolbar items)
*
*Revision 1.25.2.2  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.25.2.1  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.25  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.24.2.5  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.24.2.4  2003/12/02 22:11:30  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.24.2.3  2003/12/02 05:50:06  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.24.2.2  2003/10/17 21:23:10  ddiego
*added menu item child count function
*fixed a selection glitch in tree list control
*
*Revision 1.24.2.1  2003/09/15 02:52:36  ddiego
*miscellaneous changes
*
*Revision 1.24  2003/08/09 02:56:45  ddiego
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
*Revision 1.23.2.4  2003/08/06 21:27:49  ddiego
*minor changes
*
*Revision 1.23.2.3  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.23.2.2  2003/07/16 04:59:07  ddiego
*added some changes to the fil and stroke classes to allow changing whether
*they use anti-aliasing or not. Also implemented Matrix2D::invert(),
*plus properly implemented clone() on the DefaultMenuItem class.
*
*Revision 1.23.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.23  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.22.2.1  2003/03/12 03:13:07  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.22  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.21.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.21.2.3  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.21.2.2  2002/12/27 23:05:00  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21.2.1  2002/12/25 22:06:35  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.21  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.20.10.1  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.20  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.19.4.2  2002/04/27 15:52:45  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.19.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.19  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


