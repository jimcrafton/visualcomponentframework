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

using namespace VCF;

static DefaultMenuItem* previousSelectedItem = NULL;

DefaultMenuItem::DefaultMenuItem()
{
	init();
}

DefaultMenuItem::DefaultMenuItem( const String& caption, MenuItem* parent, Menu* menuOwner )
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
																currentAccelerator_->getModifierMask() );
	}

	if ( this == previousSelectedItem )	{
		previousSelectedItem = NULL;
	}
	else if ( NULL == getParent() ) {
		previousSelectedItem = NULL;
	}

	/*
	std::vector<MenuItem*>::iterator it = menuItems_.begin();
	while ( it != menuItems_.end() ){
		MenuItem* item = *it;
		delete item;
		item = NULL;
		it ++;
	}
	*/

	delete Peer_;
	Peer_ = NULL;

	menuItems_.clear();
}

void DefaultMenuItem::init()
{
	tag_ = -1;
	currentAccelerator_ = NULL;
	selected_ = false;
	imageIndex_ = 0;
	parent_ = NULL;
	radioItem_ = false;
	visible_ = true;
	data_ = NULL;
	separator_ = false;
	isEnabled_ = true;
	menuOwner_ = NULL;

	Peer_ = UIToolkit::createMenuItemPeer( this );

	if ( NULL == Peer_ ){
		//throw exception
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	Peer_->setMenuItem( this );

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
	return index_;
}

void DefaultMenuItem::setIndex( const unsigned long& index )
{
	index_ = index;
}

void* DefaultMenuItem::getData()
{
	return data_;
}

void DefaultMenuItem::setData( void* data )
{
	data_ = data;
}

Model* DefaultMenuItem::getModel()
{
	return NULL;
}

void DefaultMenuItem::setModel( Model* model )
{

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
	return selected_;
}

void DefaultMenuItem::setSelected( const bool& selected )
{
	if ( (NULL != previousSelectedItem) && (previousSelectedItem != this) ) {
		previousSelectedItem->setSelected( false );
	}
	selected_ = selected;
	if ( true == selected_ ) {
		ItemEvent event( this, ITEM_EVENT_SELECTED );
		ItemSelected.fireEvent( &event );
	}
	previousSelectedItem = this;
}

Enumerator<MenuItem*>* DefaultMenuItem::getChildren()
{
	return container_.getEnumerator();
}

void DefaultMenuItem::addChild( MenuItem* child )
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	menuItems_.push_back( child );

	child->setParent( this );

	if ( NULL == child->getOwner() ) {
		addComponent( child );
	}

	child->setIndex( menuItems_.size() - 1 );

	child->setMenuOwner( getMenuOwner() );

	Peer_->addChild( child );

	ItemEvent event( this, ITEM_EVENT_ADDED );
	ItemAdded.fireEvent( &event );
}

void DefaultMenuItem::insertChild( const unsigned long& index, MenuItem* child )
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	menuItems_.insert( menuItems_.begin() + index, child );

	if ( NULL == child->getOwner() ) {
		addComponent( child );
	}

	child->setIndex( index );

	child->setParent( this );

	child->setMenuOwner( getMenuOwner() );

	Peer_->insertChild( index, child );

	ItemEvent event( this, ITEM_EVENT_ADDED );
	ItemAdded.fireEvent( &event );
}

void DefaultMenuItem::deleteChild( MenuItem* child )
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	Peer_->deleteChild( child );

	std::vector<MenuItem*>::iterator found = std::find( menuItems_.begin(), menuItems_.end(), child );
	if ( found != menuItems_.end() ){
		ItemEvent event( this, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &event );

		removeComponent( child );

		menuItems_.erase( found );
		child->free();
		child = NULL;
	}
}

void DefaultMenuItem::deleteChild( const unsigned long& index )
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	Peer_->deleteChild( index );

	std::vector<MenuItem*>::iterator found = menuItems_.begin() + index;
	if ( found != menuItems_.end() ){

		ItemEvent event( this, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &event );

		removeComponent( *found );

		menuItems_.erase( found );
		(*found)->free();
	}
}

void DefaultMenuItem::clearChildren()
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	std::vector<MenuItem*>::iterator it = menuItems_.begin();
	while ( it != menuItems_.end() ){
		removeComponent( *it );
		(*it)->free();
		it++;
	}
	menuItems_.clear();

	Peer_->clearChildren();
}

bool DefaultMenuItem::isChecked()
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	return Peer_->isChecked();
}

void DefaultMenuItem::setChecked( const bool& checked )
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	Peer_->setChecked( checked );
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
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	if ( index >= menuItems_.size() ) {
		throw OutOfBoundsException(MAKE_ERROR_MSG(OUT_OF_BOUNDS_EXCEPTION), __LINE__);
	}
	return menuItems_[index];
}

bool DefaultMenuItem::isEnabled()
{
	return isEnabled_;//Peer_->isEnabled();
}

void DefaultMenuItem::setEnabled( const bool& enabled )
{
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	isEnabled_ = enabled;
	Peer_->setEnabled( enabled );

	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

bool DefaultMenuItem::isVisible()
{
	return visible_;
}

void DefaultMenuItem::setVisible( const bool& visible )
{
	visible_ = visible;
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	Peer_->setVisible( visible );

	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

bool DefaultMenuItem::getRadioItem()
{
	return radioItem_;
}

void DefaultMenuItem::setRadioItem( const bool& value )
{
	radioItem_ = value;
	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	Peer_->setRadioItem( radioItem_ );

	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultMenuItem::setCaption( const String& caption )
{
	caption_ = caption;

	if ( NULL == Peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	Peer_->setCaption( caption_ );

	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged.fireEvent( &event );
}

String DefaultMenuItem::getCaption()
{
	return caption_;
}

MenuItemPeer* DefaultMenuItem::getPeer()
{
	return Peer_;
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
			child->setMenuOwner( menuOwner );
		}
		it++;
	}
}

bool DefaultMenuItem::isSeparator()
{
	return separator_;
}

void DefaultMenuItem::setSeparator( const bool& separator )
{
	separator_ = separator;
	Peer_->setAsSeparator( separator_ );
}

void DefaultMenuItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultMenuItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}

void DefaultMenuItem::setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask )
{
	EventHandler* eventHandler = this->getEventHandler( "DefaultMenuItem::onAccelerator" );
	if ( NULL == eventHandler ) {
		eventHandler = new KeyboardEventHandler<DefaultMenuItem>( this, &DefaultMenuItem::onAccelerator, "DefaultMenuItem::onAccelerator" );
	}
	AcceleratorKey* newAccelKey = new AcceleratorKey( NULL, keyCode, modifierMask, eventHandler );

	addAcceleratorKey( newAccelKey );
}

void DefaultMenuItem::addAcceleratorKey( AcceleratorKey* accelerator )
{
	//remove the old if present
	if ( NULL != currentAccelerator_ ) {
		UIToolkit::removeAccelerator( (VirtualKeyCode)currentAccelerator_->getKeyCode(),
																currentAccelerator_->getModifierMask() );
	}

	currentAccelerator_ = accelerator;

	if ( NULL != currentAccelerator_ ) {
		UIToolkit::registerAccelerator( currentAccelerator_ );
	}

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
		result->setAcceleratorKey( (VCF::VirtualKeyCode)accel->getKeyCode(), accel->getModifierMask() );
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

			}
			break;
	}
}


/**
*CVS Log info
*$Log$
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


