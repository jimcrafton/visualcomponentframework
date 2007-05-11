//ComboBoxControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ComboBoxControl
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ComboBoxControl.h"
#include "vcf/ApplicationKit/ListBoxControl.h"
#include "vcf/ApplicationKit/DefaultListModel.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/Containers.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;

class DropDownListBox : public ListBoxControl {
public:
	DropDownListBox( ComboBoxControl* comboBoxControl ) :
		ListBoxControl( comboBoxControl->getListModel() ){
		comboBoxControl_ = comboBoxControl;
		// Remark: selectedItem_ differs from comboBoxControl->getListModel()->getSelectedItem() because of the DropDownListBox::mouseMove() action
		comboBoxControl->selectItems( false );

		ScrollbarManager* scrollBarMgr = new ScrollbarManager();
		scrollBarMgr->setTarget( this );
		addComponent( scrollBarMgr );

		scrollBarMgr->setHasHorizontalScrollbar( false );
		scrollBarMgr->setHasVerticalScrollbar( true );
		//scrollBarMgr->setVirtualViewVertStep( getDefaultItemHeight() );
		scrollBarMgr->setDiscreteScroll( false, comboBoxControl->getDiscreteScroll() );

		setUseColorForBackground( true );

		setFont( comboBoxControl->getFont() );
	}

	virtual ~DropDownListBox(){

	};


	virtual void paint( GraphicsContext* ctx ) {
		ListBoxControl::paint( ctx );
	}

	virtual void mouseDown( MouseEvent* event ) {

	}


	virtual void mouseMove( MouseEvent* event ) {
		CustomControl::mouseMove( event );

		if ( (Component::csNormal == getComponentState()) ) {
			ListItem* foundItem = findSingleSelectedItem( event->getPoint() );
			if ( NULL != foundItem ) {
				comboBoxControl_->selectItems( false );

				if ( true == allowsMultiSelect_ ) {

				}
				else {
					if ( foundItem != singleSelectedItem_ ) {
						setSelectedItem( foundItem );
					}
				}

			}
		}
	}

	virtual void setBounds( Rect* rect, const bool& anchorDeltasNeedUpdating=true ) {
		ListBoxControl::setBounds( rect, anchorDeltasNeedUpdating );

		getScrollable()->setVirtualViewWidth( rect->getWidth() );
		double h = getDefaultItemHeight();
		int count = getListModel()->getCount();
		h = count * h;
		getScrollable()->setVirtualViewHeight( h );
	}

	virtual void ensureVisible( ListItem* item, const bool& partialOK ) {
		// makes sure that item will be visible through scrolling
		DefaultListModel* listModel = (DefaultListModel*)comboBoxControl_->getListModel();
		uint32 index = listModel->getItemIndex( item );
		double verticalPosition = index * getDefaultItemHeight();
		getScrollable()->setVerticalPosition( verticalPosition );
		// Note: in the future we should call then
		//getScrollable()->getAdjustedPositions();
		//       in order to know the Window's adjustments for the scroll quantity
	}

public:
	std::vector<ListItem*> originalSelectedItems_;
	ComboBoxControl* comboBoxControl_;
};

class ComboBoxDropDown : public Window {
public:

	class Container : public StandardContainer {
	public:
		Container() {
			setBorderWidth( 1 );
		}

		virtual void resizeChildren(Control* control) {
			

			StandardContainer::resizeChildren( control );
		}
	};

	ComboBoxDropDown( ComboBoxControl* comboBoxControl, EventHandler* closeHandler ) {

		setContainer( new ComboBoxDropDown::Container() );

		selectedItem_ = NULL;

		closeHandler_ = closeHandler;

		comboBoxControl_ = comboBoxControl;
		listBox_ = new DropDownListBox( comboBoxControl );
		add( listBox_, AlignClient );

		listBox_->MouseUp.addHandler( new MouseEventHandler<ComboBoxDropDown>( this, &ComboBoxDropDown::onListboxMouseUp, "onListboxMouseUp" ) );

		setColor( Color::getColor( "black" ) );
		setUseColorForBackground( true );
		setFrameStyle( fstNoBorderFixed );
		setFrameTopmost( true );

		Rect itemRect = comboBoxControl_->getBounds();
		comboBoxControl_->getParent()->translateToScreenCoords( &itemRect );

		uint32 desktopH = UIShell::getUIShell()->getHeight();
		uint32 desktopW = UIShell::getUIShell()->getWidth();

		int count = minVal<>( listBox_->getListModel()->getCount(), comboBoxControl_->getDropDownCount() );
		
		int winHeight = ( listBox_->getDefaultItemHeight() ) * count;
		if ( desktopH < winHeight ) {
			winHeight = desktopH;
		}

		if ( (itemRect.bottom_ + winHeight) > desktopH ) {
			if ( winHeight <= itemRect.top_ ) {
				itemRect.top_ = itemRect.top_ - winHeight;
				itemRect.bottom_ = itemRect.top_ + winHeight;
			} else if ( false == comboBoxControl_->getDropDownExtendFullScreen() ) {
				if ( desktopH / 2 < itemRect.top_ ) {
					itemRect.bottom_ = itemRect.top_;
					itemRect.top_ = 0;
				} else {
					itemRect.top_ += comboBoxControl_->getBounds().getHeight();
					itemRect.bottom_ = desktopH;
				}
			} else {
				if ( itemRect.top_ > desktopH - itemRect.bottom_ ) {
					itemRect.top_ = 0;
					itemRect.bottom_ = winHeight;
				} else {
					itemRect.top_ = desktopH - winHeight;
					itemRect.bottom_ = desktopH;
				}
			}
		}
		else {
			itemRect.top_ += comboBoxControl_->getBounds().getHeight();
			itemRect.bottom_ = itemRect.top_ + winHeight;

			// this fixes the bug that scrollbar is always there even when itemsCount < dropDownCount
			// +=2 comes from the viewable bounds are one pixel on the top and one pixel on the bottom 
			// less than the height of the listbox control itself ( see Control::adjustViewableBoundsAndOriginForScrollable() )
			// +=1 comes from rounding reasons.
			// Any value less than listBox_->getDefaultItemHeight() would fix the problem.
			// See also: DropDownListBox::setBounds()
			itemRect.bottom_ += 3;
		}

		if ( 0 < comboBoxControl_->getDropDownWidth() ) {
			itemRect.right_ = itemRect.left_ + comboBoxControl_->getDropDownWidth();
		}

		setBounds( &itemRect );

		selectedItem_ = comboBoxControl_->getSelectedItem();
		if ( NULL != selectedItem_ ) {
			selectedItem_->setSelected( true );
			ensureVisible( selectedItem_, false );
		}
	}

	virtual ~ComboBoxDropDown() {


		//StringUtils::trace( Format( "ComboBoxDropDown::~ComboBoxDropDown() @ %p\n" ) % this );

	}

	virtual void destroy() {
		listBox_->setListModel( NULL );

		// bugfix [ 1099910 ] commented away. The combobox
		// may have been already destroyed by another control
		// since the time dropDown_->close() has been called.
		//comboBoxControl_->repaint();

		Window::destroy();
	}

	virtual void beforeDestroy( ComponentEvent* e ) {

		Window::beforeDestroy( e );
	}


	void onListboxMouseUp( MouseEvent* e ) {
		Rect clientRect = listBox_->getClientBounds();

		Scrollable* scrollable = listBox_->getScrollable();
		if ( NULL != scrollable ) {
			clientRect.offset( 0, scrollable->getVerticalPosition() );
		}

		if ( clientRect.containsPt( e->getPoint() ) ) {
			selectedItem_ = listBox_->getSelectedItem();
		}
		else {
			selectedItem_ = NULL;
		}

		Event* closeEvent = new Event( this,666777 );
		UIToolkit::postEvent( closeHandler_, closeEvent, false );
	}

	ListItem* getSelectedItem() {
		return selectedItem_;
	}

	ListBoxControl* getListBox() {
		return listBox_;
	}

	void ensureVisible( ListItem* item, const bool& partialOK ) {
		DropDownListBox* listBox = (DropDownListBox*)listBox_;
		listBox->ensureVisible( item, false );
	}

protected:
	ListItem* selectedItem_;
	ComboBoxControl* comboBoxControl_;
	ListBoxControl* listBox_;
	EventHandler* closeHandler_;
};



class ComboBoxEdit : public TextControl {
public:
	ComboBoxEdit() {
		setBorder( NULL );
	}

	virtual bool keepsArrowKeys() {
		return true;
	}
};

class ComboBoxContainer : public StandardContainer {
public:
	virtual void resizeChildren( Control* control ) {
		Rect bounds = ((ComboBoxControl*)controlContainer_)->getEditBounds();

		std::vector<Control*>::iterator it = controls_.begin();
		while ( it != controls_.end() ) {
			(*it)->setBounds( &bounds );
			it ++;
		}
	}
};


ComboBoxControl::ComboBoxControl():
	CustomControl( true ),//make this a heavyweight control !
	listModel_(NULL)
{
	init();
}

void ComboBoxControl::init()
{
	comboBoxStyle_ = cbsDropDown;
	selectedItem_ = NULL;
	dropDown_ = NULL;
	dropDownCount_ = 6;
	dropDownWidth_ = 0;
	dropDownExtendFullScreen_ = false;
	discreteScroll_ = true; // for a combo and any listbox it should be true by default
	dropDownSelected_ = false;
	autoLookup_ = true;
	autoLookupIgnoreCase_ = true;

	setListModel( new DefaultListModel() );

	addComponent( getViewModel() );

	setContainer( new ComboBoxContainer() );

	selectedIndex_ = 0;
	arrowPressed_ = false;
	mouseOver_ = false;


	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );

	edit_ = new ComboBoxEdit();

	edit_->setBounds( &Rect(0,0,0,0) );

	getContainer()->add( edit_ );
	edit_->setVisible( (comboBoxStyle_ == cbsDropDownWithEdit) );
	edit_->setEnabled( (comboBoxStyle_ == cbsDropDownWithEdit) );

	edit_->setKeepTabbingCharacters( true );

	edit_->KeyPressed.addHandler(
		new KeyboardEventHandler<ComboBoxControl>( this, &ComboBoxControl::onEditKeyPressed, "ComboBoxControl::onEditKeyPressed" ) );

	updateEditBounds();

	FocusGained.addHandler( new FocusEventHandler<ComboBoxControl>( this, &ComboBoxControl::onFocusGained, "ComboBoxControl::onFocusGained" ) );

	setUseColorForBackground( true );

	Basic3DBorder* border = new Basic3DBorder();
	border->setInverted( true );
	setBorder( border );
}

ComboBoxControl::~ComboBoxControl()
{

}

void ComboBoxControl::destroy()
{
	CustomControl::destroy();

	/*
	if ( NULL != listModel_ ){
		listModel_->release();
		listModel_ = NULL;
	}
	*/

	/*
	Model* model = this->getViewModel();
	if ( NULL != model ) {
		model->release();
	}
	*/
	listModel_ = NULL;
}

ListModel* ComboBoxControl::getListModel()
{
	return listModel_;
}

void ComboBoxControl::setListModel(ListModel * model)
{
	EventHandler* changed = getEventHandler( "ComboBox_onListModelContentsChanged" );
	if ( NULL == changed ) {
		changed =
			new ListModelEventHandler<ComboBoxControl>( this,
														&ComboBoxControl::onListModelContentsChanged,
														"ComboBox_onListModelContentsChanged" );
	}

	EventHandler* itemAdded = getEventHandler( "ComboBox_onItemAdded" );
	if ( NULL == itemAdded ) {
		itemAdded =
			new ListModelEventHandler<ComboBoxControl>( this,
														&ComboBoxControl::onItemAdded,
														"ComboBox_onItemAdded" );
	}

	EventHandler* itemDeleted = getEventHandler( "ComboBox_onItemDeleted" );
	if ( NULL == itemDeleted ) {
		itemDeleted =
			new ListModelEventHandler<ComboBoxControl>( this,
														&ComboBoxControl::onItemDeleted,
														"ComboBox_onItemDeleted" );
	}

	if ( NULL != listModel_ ) {
		listModel_->removeContentsChangedHandler( changed );

		listModel_->removeItemAddedHandler( itemAdded );

		listModel_->removeItemDeletedHandler( itemDeleted );
	}

	listModel_ = model;

	if ( NULL != listModel_ ) {		

		listModel_->addContentsChangedHandler( changed );

		listModel_->addItemAddedHandler( itemAdded );

		listModel_->addItemDeletedHandler( itemDeleted );
	}

	setViewModel( dynamic_cast<Model*>(listModel_) );
}

void ComboBoxControl::mouseEnter( MouseEvent* event )
{
	mouseOver_ = true;
	repaint();
}

void ComboBoxControl::mouseLeave( MouseEvent* event )
{
	mouseOver_ = false;
	repaint();
}

void ComboBoxControl::paint( GraphicsContext* context )
{
	CustomControl::paint( context );
/*
	Rect clientRect = getClientBounds();

	arrowRect_ = clientRect;

	

	arrowRect_.left_ = clientRect.right_ - sz.width_;
*/
	

	ButtonState state;
	Rect clientRect = getClientBounds();

	state.setActive( this->isActive() );
	state.setEnabled( this->isEnabled() );
	state.setPressed( arrowPressed_ );
	state.setFocused( this->isFocused() );

	ListItem* selectedItem = getSelectedItem();
	if ( NULL != selectedItem ){
		state.buttonCaption_ = selectedItem->getCaption();
	}
	
	context->drawThemeComboboxRect( &clientRect, state );

	if ( NULL != selectedItem ){		
		if ( selectedItem->canPaint() ) {
			Rect r = clientRect;
			Size sz = UIToolkit::getUIMetricSize( UIMetricsManager::mtVerticalSliderThumbSize );
			r.right_ -= sz.width_;
			selectedItem->paint( context, &r );
		}
	}

	getContainer()->paintChildren( context );
}

void ComboBoxControl::onListModelContentsChanged( ListModelEvent* event )
{
	if ( NULL != event ){
		switch ( event->getType() ){
			case LIST_MODEL_CONTENTS_DELETED: {
				if ( selectedItem_ ==  event->getListItem() ) {
					selectedItem_ = NULL;
					selectedIndex_ = 0;
				}
			}
			break;

			case LIST_MODEL_ITEM_CHANGED: {
				ListItem* item = event->getListItem();
				if ( NULL != item ){

				}
			}
			break;
		}
	}
}

void ComboBoxControl::onItemAdded( ListModelEvent* event )
{
}

void ComboBoxControl::onItemDeleted( ListModelEvent* event )
{
	if ( selectedItem_ ==  event->getListItem() ) {
		selectedItem_ = NULL;
		selectedIndex_ = 0;
	}
}

void ComboBoxControl::closeDropDown( Event* event )
{
	if ( NULL != dropDown_ ) {
		ComboBoxDropDown* dropdown = (ComboBoxDropDown*)dropDown_;
		ListItem* selectedItem = dropdown->getSelectedItem();

		EventHandler* lostFocusHandler = getEventHandler( "ComboBoxControl::onDropDownLostFocus" );
		dropDown_->FrameActivation.removeHandler( lostFocusHandler );

		dropDown_->setVisible( false );
		this->repaint();
		dropDown_->close();

		if ( NULL != selectedItem  ) {
			// not when we just lost the focus
			if ( event->getType() != 888999 ) {
				setDropDownSelected( true );
				setSelectedItem( selectedItem );
				setDropDownSelected( false );
			}
		}

		if ( cbsDropDownWithEdit == comboBoxStyle_ ) {
			ListItem* item = getSelectedItem();
			if ( NULL != item ) {
				setCurrentText( item->getCaption() );
			}
		}

		//delete dropDown_;
	}
	dropDown_ = NULL;
}

void ComboBoxControl::onDropDownLostFocus( WindowEvent* event )
{
	if ( NULL != dropDown_ ) {
		Frame* frame = (Frame*)event->getSource();
		if ( false == frame->isActive() ) {

			dropDown_->setVisible( false );

			Event* closeEvent = new Event( dropDown_, 888999 );
			EventHandler* ev = new GenericEventHandler<ComboBoxControl>( this, &ComboBoxControl::closeDropDown );
			UIToolkit::postEvent( ev, closeEvent );
		}
	}

	this->arrowPressed_ = false;
}

void ComboBoxControl::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );

	//this->arrowPressed_ = this->arrowRect_.containsPt( event->getPoint() );

	this->keepMouseEvents();

	Rect clientRect = getClientBounds();
	this->arrowPressed_ = clientRect.containsPt( event->getPoint() );

	if ( true == arrowPressed_ ){
		if ( dropDown_ != NULL ) {
			//drop down is still up, this will close it
			return;
		}
		dropDown_ = NULL;

		ListModel* model = getListModel();

		if ( NULL != model ) {
			if ( model->getCount() > 0 ) {
				EventHandler* closeHandler = getEventHandler( "ComboBoxControl::closeDropDown" );
				if ( NULL == closeHandler ) {
					closeHandler = new GenericEventHandler<ComboBoxControl>( this, &ComboBoxControl::closeDropDown, "ComboBoxControl::closeDropDown" );
				}

				ComboBoxDropDown* dropDown = new ComboBoxDropDown( this, closeHandler );

				EventHandler* lostFocusHandler = getEventHandler( "ComboBoxControl::onDropDownLostFocus" );
				if ( NULL == lostFocusHandler ) {
					lostFocusHandler = new WindowEventHandler<ComboBoxControl>( this,
																				&ComboBoxControl::onDropDownLostFocus,
																				"ComboBoxControl::onDropDownLostFocus" );
				}

				dropDown->FrameActivation.addHandler( lostFocusHandler );
				dropDown_ = dropDown;
				dropDown_->show();
			}
		}
	}
	this->repaint();
}

void ComboBoxControl::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );
	if ( event->hasLeftButton() ){
		//this->arrowPressed_ = this->arrowRect_.containsPt( event->getPoint() );
		Rect clientRect = getClientBounds();
		this->arrowPressed_ = clientRect.containsPt( event->getPoint() );

		this->repaint();
	}
}

void ComboBoxControl::mouseUp( MouseEvent* event )
{
	CustomControl::mouseUp( event );
	this->releaseMouseEvents();
	arrowPressed_ = false;
	this->repaint();
}

void ComboBoxControl::keyPressed( KeyboardEvent* event )
{
	// this case is called when the focus is on the DropDownListBox
	//  control, as it happens when an item is selected;
	// it is not called when the focus is on the edit_ control

	switch ( event->getVirtualCode() ){
		case vkUpArrow :{
			uint32 index = selectedIndex_ + 1;

			if ( index >=	this->listModel_->getCount() ){
				index = 0;
			}

			this->setSelectedItemIndex( index );

			this->repaint();
		}
		break;

		case vkDownArrow :{
			uint32 index = selectedIndex_ - 1;
			/**
			* this is done this way because we have an uint32 so we
			*won't get negative numbers, anything over the count needs to be wrapped
			*/
			if ( index > this->listModel_->getCount() ){
				index = this->listModel_->getCount() -1;
			}

			this->setSelectedItemIndex( index );

			this->repaint();
		}
		break;

		case vkEscape : {
			if ( NULL != dropDown_ ) {
				Event ev( this );
				closeDropDown( &ev );
			}
		}
		break;

		case vkReturn : {
			StringUtils::trace( "ComboBoxControl::keyPressed: vkReturn()\n" );
			if ( NULL != dropDown_ ) {
				ListItem* item = ((ComboBoxDropDown*)dropDown_)->getListBox()->getSelectedItem();

				// we close the drodownbox here because if we do it after, 
				// we would set back the current selected item, while
				// the selected item is going to be changed by this code.
				Event ev( this );
				closeDropDown( &ev );

				setSelectedItem( item );

				if ( cbsDropDownWithEdit == comboBoxStyle_ ) {
					item = getSelectedItem();
					if ( NULL != item ) {
						setCurrentText( item->getCaption() );
					}
				}

			}
		}
		break;

	default:
		break;



	}
}

ListItem* ComboBoxControl::getSelectedItem()
{

	return selectedItem_;
}

void ComboBoxControl::onPostSelect( ItemEvent* e )
{
	SelectionChanged.fireEvent( e );
}

void ComboBoxControl::setSelectedItem( ListItem* selectedItem )
{
	if ( NULL != selectedItem_ ) {
		selectedItem_->setSelected( false );
	}

	selectedItem_ = selectedItem;
	if ( NULL != selectedItem_ ) {
		selectedItem_->setSelected( true );
		
		if ( cbsDropDownWithEdit == comboBoxStyle_	) {
			edit_->getTextModel()->setText( selectedItem_->getCaption() );
		}

		setFocused();

		/**
		JC
		I changed this so that the source is the ComboBoxControl
		instance as opposed to the selected item
		*/
 		ItemEvent event( this, ITEM_EVENT_SELECTED );
		event.setUserData( (void*)selectedItem_ );
		SelectionChanged.fireEvent( &event );
	}

	repaint();
}

void ComboBoxControl::setSelectedItemIndex( const uint32& selectedIndex )
{
	selectedIndex_ = selectedIndex;
	if ( NULL != listModel_ ){
		if ( listModel_->getCount() > 0 ){
			ListItem* item = listModel_->getItemFromIndex( selectedIndex );
			setSelectedItem( item );
		}
	}
}

void ComboBoxControl::setComboBoxStyle( const ComboBoxStyleType& comboBoxStyle )
{
	comboBoxStyle_ = comboBoxStyle;
	edit_->setVisible( (comboBoxStyle_ == cbsDropDownWithEdit) );
	edit_->setEnabled( (comboBoxStyle_ == cbsDropDownWithEdit) );

	if ( cbsDropDownWithEdit == comboBoxStyle_ ) {
		setTabStop( false );
	}
	else {
		setTabStop( true );
	}

	updateEditBounds();
}

/*
void ComboBoxControl::setBounds( Rect* rect, const bool& anchorDeltasNeedUpdating )
{
	CustomControl::setBounds( rect, anchorDeltasNeedUpdating );

	if ( comboBoxStyle_ == cbsDropDownWithEdit ) {

		Rect rectTmp( 0, 0, rect->getWidth() - rect->getHeight(), rect->getHeight() );
		rectTmp.inflate( -1, -1 );
		rectTmp.right_ += 2;

		edit_->setBounds( &rectTmp );
	}
	else {
		edit_->setBounds( &Rect(0,0,0,0) );
	}
}
*/

Rect ComboBoxControl::getEditBounds()
{
	Rect result;
	result = getClientBounds();

	//Size sz = 
		//getUIMetricsManager()->getDefaultVerticalScrollButtonDimensions();

	result.right_ -= UIToolkit::getUIMetricValue( UIMetricsManager::mtVerticalScrollbarThumbWidth );	

	result.right_ -= 3;
	result.inflate( -2, -1 );

	return result;
}

void ComboBoxControl::updateEditBounds()
{
	if ( comboBoxStyle_ == cbsDropDownWithEdit ) {

		edit_->setBounds( &getEditBounds() );
	}
	else {
		edit_->setBounds( &Rect(0,0,0,0) );
	}
}

void ComboBoxControl::onEditKeyPressed( KeyboardEvent* event )
{
	//if (  vkReturn == event->getVirtualCode() ) {
		KeyboardEvent* postedEvent = new KeyboardEvent( event->getSource(), event->getType(),
														event->getRepeatCount(), event->getKeyMask(),
														event->getKeyValue(), event->getVirtualCode() );
		UIToolkit::postEvent(
			new KeyboardEventHandler<ComboBoxControl>( this, &ComboBoxControl::onEditReturnKeyPressed ), postedEvent );
	//}
	//VirtualKeyCode key = event->getVirtualCode();
	//StringUtils::trace( Format( "Key: %d\r\n" ) % key );
}

void ComboBoxControl::onEditReturnKeyPressed( KeyboardEvent* event )
{
	// we get here only if the focus is on the edit control;
	// if we select an item, the focus will go to the DropDownListBox instead.

	if ( vkReturn == event->getVirtualCode() ) {
		if ( NULL != dropDown_ ) {
			ListItem* item = ((ComboBoxDropDown*)dropDown_)->getListBox()->getSelectedItem();

			// we close the drodownbox now because if we do it after, 
			// we would set back the current selected item
			Event ev( this );
			closeDropDown( &ev );

			setSelectedItem( item );

			if ( cbsDropDownWithEdit == comboBoxStyle_ ) {
				ListItem* item = getSelectedItem();
				if ( NULL != item ) {
					setCurrentText( item->getCaption() );
				}
			}

		}
		else {
			ListItem* item = this->getSelectedItem();
			if ( NULL != item ) {
				// commented as we don't want to change the caption of the items in the list [ bugfix 1112867]
				//item->setCaption( edit_->getTextModel()->getText() );
				repaint();
			}
		}

	}
	else if ( vkEscape == event->getVirtualCode() ) {
		Event ev( this );
		closeDropDown( &ev );
	}
	else {
		if ( NULL != dropDown_ ) {
			// find the item and select it
			if ( autoLookup_ ) {
				bool hasSpecialKey = ( event->getKeyMask() != 0 );
				if ( !hasSpecialKey ) {
					String caption, editCaption;
					editCaption = edit_->getTextModel()->getText();

					ListItem* found = lookupItem( editCaption, autoLookupIgnoreCase_ );
					if ( NULL != found ) {
						this->selectItems( false );

						((ComboBoxDropDown*)dropDown_)->ensureVisible( found, true );
						found->setSelected( true );
					}

				}
			}
		}
	}
}

ListItem* ComboBoxControl::lookupItem( const String& text, const bool& ignoreCase/*=false*/ )
{
	ListItem* found = NULL;

	if ( text != "" ) {
		String txt = text;
		if ( ignoreCase ) {
			txt = StringUtils::lowerCase( text );
		}

		String caption;
		ListItem* similarItem = NULL;
		Enumerator<ListItem*>* items = getListModel()->getItems();
		while ( true == items->hasMoreElements() ) {
			ListItem* item = items->nextElement();
			caption = item->getCaption();
			if ( ignoreCase ) {
				caption = StringUtils::lowerCase( caption );
			}

			// this privilege the identical item, otherwise it accept the first more similar to the text in the (unsorted) list
			if ( caption == txt ) {
				similarItem = item;
				break;
			} else if ( NULL == similarItem ) {
				if ( 0 == caption.find( txt ) ) {
						similarItem = item;
					}
			}
		}

		found = similarItem;

	}

	return found;
}

void ComboBoxControl::setDropDownCount( const uint32& dropDownCount )
{
	dropDownCount_ = dropDownCount;
}

void ComboBoxControl::setDropDownWidth( const uint32& dropDownWidth )
{
	dropDownWidth_ = dropDownWidth;
}

void ComboBoxControl::setDropDownExtendFullScreen( const bool& dropDownExtendFullScreen )
{
	dropDownExtendFullScreen_ = dropDownExtendFullScreen;
}

void ComboBoxControl::setDiscreteScroll( const bool& discreteScroll )
{
	discreteScroll_ = discreteScroll;
}

void ComboBoxControl::setDropDownSelected( const bool& dropDownSelected )
{
	dropDownSelected_ = dropDownSelected;
}

void ComboBoxControl::setAutoLookup( const bool& autoLookup )
{
	autoLookup_ = autoLookup;
}

void ComboBoxControl::setAutoLookupIgnoreCase( const bool& ignoreCase )
{
	autoLookupIgnoreCase_ = ignoreCase;
}

ListItem* ComboBoxControl::addItem( const String& caption, const uint32 imageIndex )
{
	ListItem* result = new DefaultListItem();
	result->setCaption( caption );
	result->setImageIndex( imageIndex );
	addItem( result );

	return result;
}

void ComboBoxControl::addItem( ListItem* item )
{
	if ( NULL != listModel_ ) {
		listModel_->addItem( item );
	}
}

void ComboBoxControl::onFocusGained( FocusEvent* event )
{
	if ( cbsDropDownWithEdit == comboBoxStyle_	) {
		edit_->setFocused();
	}
}


void ComboBoxControl::setEnabled( const bool& enabled )
{
	Control::setEnabled( enabled );
	if ( cbsDropDownWithEdit == comboBoxStyle_	) {
		edit_->setEnabled( enabled );
	}
}

String ComboBoxControl::getCurrentText()
{
	String result;

	if ( cbsDropDownWithEdit == comboBoxStyle_	) {
		result =  edit_->getTextModel()->getText();
	}
	else {
		ListItem* item = getSelectedItem();
		if ( NULL != item ) {
			result = item->getCaption();
		}
	}

	return result;
}

void ComboBoxControl::setCurrentText( const String& text )
{
	if ( cbsDropDownWithEdit == comboBoxStyle_	) {
		edit_->getTextModel()->setText( text );
	}
	else {
		if ( text.empty() ) {
			setSelectedItem( NULL );
		}
		else {
			Enumerator<ListItem*>* items = getListModel()->getItems();
			while ( true == items->hasMoreElements() ) {
				ListItem* item = items->nextElement();
				String caption = item->getCaption();
				int pos = caption.find( text );
				if ( String::npos != pos ) {
					setSelectedItem( item );
					break;
				}
			}
		}
	}
}

double ComboBoxControl::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtComboBoxHeight );
}

void ComboBoxControl::selectItems( const bool& select )
{
	// usually used to deselect all itmes in the drop down list box
	Enumerator<ListItem*>* items = this->getListModel()->getItems();
	while ( true == items->hasMoreElements() ) {
		ListItem* item = items->nextElement();
		//if ( true == item->isSelected() ) {
		//	originalSelectedItems_.push_back( item );
		//}
		item->setSelected( select );
	}
}

bool ComboBoxControl::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_HEIGHT ) {
		if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtComboBoxHeight ) ) {
			strValue = CC_COMBOBOXHEIGHT;
			return true;
		}
	}

	return Control::generatePropertyValue( fullPropertyName, property, value, strValue );
}

/**
$Id$
*/
