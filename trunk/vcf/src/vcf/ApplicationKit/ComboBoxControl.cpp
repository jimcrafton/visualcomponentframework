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

		
		GraphicsContext* context = getContext();
		
		Font* font = context->getCurrentFont();

		UIMetricsManager* mgr = UIToolkit::getUIMetricsManager();
		setDefaultItemHeight( mgr->getDefaultHeightFor( UIMetricsManager::htListItemHeight ) );//context->getTextHeight("EM") ); //font->getPixelSize() );

		ScrollbarManager* scrollBarMgr = new ScrollbarManager();
		scrollBarMgr->setTarget( this );
		addComponent( scrollBarMgr );

		scrollBarMgr->setHasHorizontalScrollbar( false );
		scrollBarMgr->setHasVerticalScrollbar( true );
		setUseColorForBackground( true );
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
		ulong32 index = listModel->getItemIndex( item );
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

		ulong32 desktopH = Desktop::getDesktop()->getHeight();
		ulong32 desktopW = Desktop::getDesktop()->getWidth();

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


		//StringUtils::traceWithArgs( "ComboBoxDropDown::~ComboBoxDropDown() @ %p\n", this );

	}


	virtual void destroy() {
		listBox_->setListModel( NULL );
		comboBoxControl_->repaint();
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
	dropDownSelected_ = false;
	autoLookup_ = true;
	autoLookupIgnoreCase_ = true;

	setListModel( new DefaultListModel() );

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
			Size sz = UIToolkit::getUIMetricsManager()->getDefaultVerticalScrollButtonDimensions();
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
	switch ( event->getVirtualCode() ){
		case vkUpArrow :{
			ulong32 index = selectedIndex_ + 1;

			if ( index >=	this->listModel_->getCount() ){
				index = 0;
			}

			this->setSelectedItemIndex( index );

			this->repaint();
		}
		break;

		case vkDownArrow :{
			ulong32 index = selectedIndex_ - 1;
			/**
			* this is done this way because we have an UNSIGNED long so we
			*won't get negative numbers, anything over the count needs to be wrapped
			*/
			if ( index > this->listModel_->getCount() ){
				index = this->listModel_->getCount() -1;
			}

			this->setSelectedItemIndex( index );

			this->repaint();
		}
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
		
		setFocused();

 		ItemEvent event( selectedItem_, ITEM_EVENT_SELECTED );
		SelectionChanged.fireEvent( &event );
	}
	repaint();
}

void ComboBoxControl::setSelectedItemIndex( const ulong32& selectedIndex )
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

	Size sz = UIToolkit::getUIMetricsManager()->getDefaultVerticalScrollButtonDimensions();

	result.right_ -= sz.width_;	

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
	//StringUtils::traceWithArgs( "Key: %d\r\n", key );
}

void ComboBoxControl::onEditReturnKeyPressed( KeyboardEvent* event )
{
	if ( vkReturn == event->getVirtualCode() ) {
		ListItem* item = this->getSelectedItem();
		if ( NULL != item ) {
			item->setCaption( edit_->getTextModel()->getText() );
			repaint();
		}
	} else {
		if ( autoLookup_ ) {
			bool hasSpecialKey = ( event->getKeyMask() != 0 );
			if ( !hasSpecialKey ) {
				String caption, editCaption;
				editCaption = edit_->getTextModel()->getText();
				if ( editCaption != "" ) {
					if ( autoLookupIgnoreCase_ ) {
						editCaption = StringUtils::upperCase( editCaption );
					}

					ListItem* similarItem = NULL;
					Enumerator<ListItem*>* items = getListModel()->getItems();
					while ( true == items->hasMoreElements() ) {
						ListItem* item = items->nextElement();
						caption = item->getCaption();
						if ( autoLookupIgnoreCase_ ) {
							caption = StringUtils::upperCase( caption );
						}

						if ( NULL != dropDown_ ) {
							// this privilege the identical item, otherwise it accept the first more similar to the editCaption in the (unsorted) list
							if ( caption == editCaption ) {
								similarItem = item;
								break;
							} else if ( NULL == similarItem && 0 == caption.find( editCaption ) ) {
									similarItem = item;
							}
						}
					}

					if ( NULL != similarItem ) {
						this->selectItems( false );

						((ComboBoxDropDown*)dropDown_)->ensureVisible( similarItem, true );		//setSelectedItem( item );
						similarItem->setSelected( true );

						//break;
					}
				}
			}
		}
	}
}

void ComboBoxControl::setDropDownCount( const ulong32& dropDownCount )
{
	dropDownCount_ = dropDownCount;
}

void ComboBoxControl::setDropDownWidth( const ulong32& dropDownWidth )
{
	dropDownWidth_ = dropDownWidth;
}

void ComboBoxControl::setDropDownExtendFullScreen( const bool& dropDownExtendFullScreen )
{
	dropDownExtendFullScreen_ = dropDownExtendFullScreen;
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

ListItem* ComboBoxControl::addItem( const String& caption, const ulong32 imageIndex )
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
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htComboBoxHeight );
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


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.3  2004/12/21 21:58:05  marcelloptr
*bugfix [ 1089382 ] ComboBox fires a SelectionChanged msg when loosing focus
*
*Revision 1.3.2.2  2004/12/20 21:57:50  ddiego
*committing cheeseheads patches for the combobox control.
*
*Revision 1.3.2.1  2004/12/20 05:01:47  ddiego
*fixed combobox draw bug for selected item
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/26 03:42:58  ddiego
*combo box fix
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/15 14:55:11  ddiego
*borders fixed
*
*Revision 1.1.2.7  2004/07/15 04:27:14  ddiego
*more updates for edit nc client painting
*
*Revision 1.1.2.6  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.5  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.4  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.3  2004/07/08 15:07:57  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.36  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.35  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.34.2.1  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.34  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.33.2.17  2003/11/10 01:57:43  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.33.2.16  2003/10/20 21:39:34  ddiego
*fixed a bug in combobox - was createing a new dropdown list when the
*old one was still in existance - resulted in faulty memory leak!
*
*Revision 1.33.2.15  2003/10/17 21:23:10  ddiego
*added menu item child count function
*fixed a selection glitch in tree list control
*
*Revision 1.33.2.14  2003/10/13 04:02:51  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.33.2.13  2003/10/12 19:38:34  ddiego
*added a fix in the combbox control due to changes in the container
*layout
*fixed a glitch in the StandardContainer::resizeChildrenUsingBounds
*method os that it correctly checks the passed in control for alignment
*or anchor  changes if neccessary
*
*Revision 1.33.2.12  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.33.2.11  2003/10/11 14:01:38  ddiego
*fixed a bug in the timing of when selection events are passed to the
*SelectionCHanged delegate on the combobox control. Now the drop
*down list is closed FIRST, and the event posted, then handled
*
*Revision 1.33.2.10  2003/10/11 13:19:36  ddiego
*patched in Marcellos fix for the ComboBox to fix a bug when setting the
*drop count to a large number - great work Marcello!!!
*
*Revision 1.33.2.9  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.33.2.8  2003/09/08 05:23:21  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.33.2.7  2003/09/06 20:24:13  ddiego
*made sure that the ComboBoxDropDown properly released it's hold on it's
*ListModel
*
*Revision 1.33.2.6  2003/09/05 21:03:20  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.33.2.5  2003/09/04 21:49:29  ddiego
*minor changes
*
*Revision 1.33.2.4  2003/09/03 01:41:39  ddiego
*some minor fixes
*
*Revision 1.33.2.3  2003/09/02 02:11:13  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.33.2.2  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.33.2.1  2003/08/17 21:48:22  ddiego
*fixed bug [ 788189 ] ComboBoxControl doesn't close when application loose
*focus. Also cleaned some old trace statements for debugging purposes.
*
*Revision 1.33  2003/08/09 02:56:44  ddiego
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
*Revision 1.32.2.2  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.32.2.1  2003/06/05 03:48:55  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.32  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.31.2.3  2003/04/17 04:29:52  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.31.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.31.2.1  2003/03/12 03:13:01  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.31  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.30.2.5  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.30.2.4  2003/01/08 00:19:58  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.30.2.3  2002/12/27 23:04:59  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.30.2.2  2002/12/25 22:06:34  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.30.2.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.30  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.29.4.2  2002/11/16 20:31:35  ddiego
*this fixes the following bugs:
*632802 TextControl's setViewModel not called
*639416 ListViewControl's setViewModel not called
*639417 TreeControl's setViewModel not called
*639418 ListBoxControl's setViewModel not called
*639419 ComboBoxControl's setViewModel not called
*639420 TreeListControl's setViewModel not called
*basically just required that setViewModel() get called. Also made changes to
*the TableControl and teh TabbedPages control
*
*Revision 1.29.4.1  2002/10/14 04:12:23  ddiego
*finalized the code generation for the generic C++ class. This now completes
*task 58649, to define a new Class template. Also made a few changes to the
*ComboBoxCOntrol so that if you setEnabled (val) and the edit box is present
*then the edit box is also enabled or disabled.
*
*Revision 1.29  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.28.6.2  2002/09/10 04:07:51  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.28.6.1  2002/09/06 20:12:41  ddiego
*tracking a bug in the ComboBoxCOntrol due to focus issues - still needs fixing
*
*Revision 1.28  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.26.4.2  2002/04/27 15:52:40  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.26.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.26  2002/03/13 03:09:54  ddiego
*adjusted tree control drawing code when not in full row selection
*addjust buffer overrun when calculating a single line of text for a
*MultilineTextControl
*
*Revision 1.25  2002/03/13 01:26:35  ddiego
*fixes to the TreeListControl
*plus fix for bug [ 529012 ] typecombo crash in the ComboBoxControl. Caused
*by not checking a null pointer in the UIToolkits' methods for getting the
*next and previous control
*
*Revision 1.24  2002/02/17 01:07:15  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.23  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


