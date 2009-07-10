//ListBoxControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListBoxControl.h"
#include "vcf/ApplicationKit/DefaultListModel.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;


static ListItem* previouslySelectedListItem = NULL;


ListBoxControl::ListBoxControl():
	ListControl(),
	currentMaxWidth_(0),
	currentMaxHeight_(0),
	leftGutter_(2),
	rightGutter_(2),
	textBounded_(false),	
	stateItemIndent_(19)
{
	peer_ =	UIToolkit::createControlPeer( this, CT_HEAVYWEIGHT );
	peer_->create( this );
	setEnabled( true );
	setVisible( true );

	setViewModel( new DefaultListModel() );

	addComponent( getViewModel() );

	allowsMultiSelect_ = false;

	allowsExtendedSelect_ = true;

	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );
	
	defaultItemHeight_ = UIToolkit::getUIMetricValue( UIMetricsManager::mtListItemHeight );

	setUseColorForBackground( true );

	
}


ListBoxControl::ListBoxControl( ListModel* listModel ):
	currentMaxWidth_(0),
	currentMaxHeight_(0),
	leftGutter_(2),
	rightGutter_(2),
	textBounded_(false),	
	stateItemIndent_(19)
{
	peer_ =	UIToolkit::createControlPeer( this, CT_HEAVYWEIGHT );
	peer_->create( this );

	setViewModel( listModel );
	allowsMultiSelect_ = false;

	allowsExtendedSelect_ = true;

	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );
	
	defaultItemHeight_ = UIToolkit::getUIMetricValue( UIMetricsManager::mtListItemHeight );

	setUseColorForBackground( true );

	setEnabled( true );
	setVisible( true );
}


ListBoxControl::~ListBoxControl()
{
	
}

void ListBoxControl::destroy()
{
	
	selectedItems_.clear();
	items_.clear();

	ListControl::destroy();
}

void ListBoxControl::handleEvent( Event* event )
{
	ListControl::handleEvent(event);
	switch ( event->getType() ) {
		case lmeContentsDeleted: {
			selectedItems_.clear();
			
			
			repaint();
		}
		break;
	}
}

void ListBoxControl::recalcBoundsForItem( ListItem* item )
{
	Scrollable* scrollable = getScrollable();


	double width = getWidth();

	Rect itemRect;

	double scrollW = 0;

	if ( NULL != scrollable ) {
		if ( scrollable->getVirtualViewHeight() > getHeight() ) {
			scrollW = scrollable->getVerticalScrollbarWidth();
		}
	}

	Font* font = getFont();

	itemRect.setRect( 0, currentMaxHeight_, width-scrollW, currentMaxHeight_ + defaultItemHeight_ );
	item->setBounds( itemRect );	

	currentMaxHeight_ += item->getBounds().getHeight();

	double imageWidth = 0.0;

	if ( NULL != getSmallImageList() ) {
		imageWidth += getSmallImageList()->getImageWidth();
	}

	currentMaxWidth_ = maxVal<double>( font->getTextWidth( item->getCaption() ) + leftGutter_ + rightGutter_ + imageWidth, currentMaxWidth_ ); 

	if ( NULL != scrollable ) {
		if ( (getHeight() > currentMaxHeight_) && (scrollable->getVerticalPosition() > 0.0) ) {
			scrollable->setVerticalPosition( 0.0 );
		}

		if ( (getWidth() > currentMaxWidth_) && (scrollable->getHorizontalPosition() > 0.0) ) {
			scrollable->setHorizontalPosition( 0.0 );
		}

		scrollable->setVirtualViewSize( currentMaxWidth_, currentMaxHeight_ );
	}
}

void ListBoxControl::onItemAdded( ListModelEvent* event )
{
	ListControl::onItemAdded(event);
	ListItem* item = getItem( event->index );
	
	recalcBoundsForItem(item);

	repaint();
}

void ListBoxControl::removeItem( ListItem* item, const uint32& itemIndex )
{
	if ( item->isSelected() ) {
		eraseFromSelectedItems( item );
	}
	
	currentMaxHeight_ -= item->getBounds().getHeight();
	//need to recalc currentMaxWidth_ here also if item removed was the widest item. DT
	
	Scrollable* scrollable = getScrollable();
	
	if ( NULL != scrollable ) {
		if ( (getHeight() > currentMaxHeight_) && (scrollable->getVerticalPosition() > 0.0) ) {
			scrollable->setVerticalPosition( 0.0 );
		}
		
		if ( (getWidth() > currentMaxWidth_) && (scrollable->getHorizontalPosition() > 0.0) ) {
			scrollable->setHorizontalPosition( 0.0 );
		}		
		
		scrollable->setVirtualViewSize( currentMaxWidth_, currentMaxHeight_ );	
	}

	Array<ListItem*>::iterator found = items_.begin() + itemIndex;
	Array<ListItem*>::iterator it = found;
	it ++;
	while ( it != items_.end() ) {
		ListItem* itemAfter = *it;
		itemAfter->setIndex( itemAfter->getIndex() - 1 );
		
		++it;
	}

	items_.erase( found );

	removeComponent( item );
	item->free();
	
	repaint();
}

void ListBoxControl::onItemDeleted( ListModelEvent* event )
{
	Array<uint32>::iterator it1 = selectedIndices_.begin();
	while ( it1 != selectedIndices_.end() ) {
		if ( *it1 == event->index ) {
			selectedIndices_.erase( it1 );
			break;
		}
		++it1;
	}

	Array<ListItem*>::iterator it2 = selectedItems_.begin();
	while ( it2 != selectedItems_.end() ) {
		ListItem* item = *it2;
		if ( item->getIndex() == event->index ) {
			selectedItems_.erase( it2 );
			break;
		}
		++it2;
	}

	if ( items_.size() > event->index ) {
		ListItem* item = items_[event->index];
		
		if ( NULL != item ) {
			currentMaxHeight_ -= item->getBounds().getHeight();
			//need to recalc currentMaxWidth_ here also if item removed was the widest item. DT
			
			Scrollable* scrollable = getScrollable();
			
			if ( NULL != scrollable ) {
				if ( (getHeight() > currentMaxHeight_) && (scrollable->getVerticalPosition() > 0.0) ) {
					scrollable->setVerticalPosition( 0.0 );
				}
				
				if ( (getWidth() > currentMaxWidth_) && (scrollable->getHorizontalPosition() > 0.0) ) {
					scrollable->setHorizontalPosition( 0.0 );
				}		
				
				scrollable->setVirtualViewSize( currentMaxWidth_, currentMaxHeight_ );	
			}
		}
	}

	ListControl::onItemDeleted(event);
}

void ListBoxControl::rangeSelect( const bool & isSelected, ListItem * first, ListItem * last )
{
	if ( NULL == last ) {
		setSelectedItem( first ); //this will select it
		if ( !isSelected ) { // we'll deselect it
			first->setSelected( isSelected );
			setSelectedItem( NULL );
		}
		repaint();
	}
	else {
		ListItem* selected = getItem( getSelectedItem() );
		if ( NULL != selected ) {
			selected->setSelected( false );
		}

		selectedItems_.clear();

		ListModel* lm = getListModel();
		if ( NULL != lm ) {
			uint32 start = first->getIndex();
			uint32 end = last->getIndex();
			for ( uint32 i=start;i<=end;i++) {
				ListItem* item =  items_[i];
				item->setSelected( isSelected );
				if ( true == isSelected ) {
					selectedItems_.push_back( item );
				}
			}

			selectionChanged( NULL );
		}
	}
}


Rect ListBoxControl::getStateRect( ListItem* item )
{
	Rect result;

	if ( item->getDisplayState() != idsNone ) {
		Rect itemBounds = item->getBounds();

		result = itemBounds;

		result.left_ += leftGutter_;
		if ( NULL != stateImageList_ ) {
			result.right_ = result.left_ + stateImageList_->getImageWidth();
			result.top_ = itemBounds.top_ + (itemBounds.getHeight()/2.0 - stateImageList_->getImageHeight()/2.0);
			result.bottom_ = result.top_ + stateImageList_->getImageHeight();
		}
		else {
			result.right_ = result.left_ + stateItemIndent_;
			result.top_ = itemBounds.top_ + (itemBounds.getHeight()/2.0 - (minVal<double>(stateItemIndent_,defaultItemHeight_)/2.0));
			result.bottom_ = result.top_ + (minVal<double>(stateItemIndent_,defaultItemHeight_));
		}

		if ( NULL != smallImageList_ ) {
			if ( NULL != stateImageList_ ) {
				result.offset( (maxVal<double>( smallImageList_->getImageWidth(), stateImageList_->getImageWidth() )), 0 );
			}
			else {
				result.offset( (maxVal<double>( smallImageList_->getImageWidth(), stateItemIndent_ )), 0 );
			}
		}
		else {
			if ( NULL != stateImageList_ ) {
				result.offset( (maxVal<double>( stateItemIndent_, stateImageList_->getImageWidth() )), 0 );
			}
			else {
				//result.offset( -stateItemIndent_, 0 );
			}
		}

	}
	return result;
}

void ListBoxControl::paintItemState( GraphicsContext* ctx, Rect& itemRect, ListItem* item )
{
	Rect stateRect = getStateRect( item );

	stateRect.inflate( -1, -1 );

	if ( NULL != stateImageList_ ) {
		itemRect.left_ = stateRect.right_;
		stateImageList_->draw( ctx, item->getStateImageIndex(), &stateRect );
	}
	else {		
		stateRect.inflate( -1, -1 );
		
		itemRect.left_ = stateRect.right_;

		int32 state = item->getDisplayState();

		ButtonState buttonState;
		buttonState.setActive( true );

		if ( (state & idsChecked) || 
				(state & idsUnChecked) ) {

			buttonState.setPressed( state == idsChecked ? true : false );
			ctx->drawThemeCheckboxRect( &stateRect, buttonState );
		}
		else if ( (state & idsRadioPressed) || 
				(state & idsRadioUnpressed) ) {

			buttonState.setPressed( state == idsRadioPressed ? true : false );
			ctx->drawThemeRadioButtonRect( &stateRect, buttonState );
		}		
	}
}

void ListBoxControl::paintItemImage( GraphicsContext* ctx, Rect& itemRect, ListItem* item )
{
	Rect imageRect;
	imageRect.left_ += leftGutter_;
	imageRect.right_ = imageRect.left_ + smallImageList_->getImageWidth();

	uint32 index = item->getImageIndex();	

	imageRect.top_ = itemRect.top_ + (itemRect.getHeight()/2.0 - smallImageList_->getImageHeight()/2.0);
	imageRect.bottom_ = imageRect.top_ + smallImageList_->getImageHeight();
	
	if ( !imageRect.isEmpty() ) {

		imageRect.inflate( -1, -1 );

		itemRect.left_ = imageRect.right_;

		smallImageList_->draw( ctx, index, &imageRect );
	}
}

void ListBoxControl::paintItem( GraphicsContext* ctx, Rect& itemRect, 
							   double currentTop, Color* selectedTextColor, 
							   const Rect& bounds, double scrollWidth, double offsetX,
							   ListItem* item )
{
	double y = currentTop + ( (itemRect.getHeight()/2.0) - (ctx->getTextHeight( "EM" )/2.0) );
	if ( item->isSelected() ) {
		paintSelectionRect( ctx, &Rect(bounds.left_-leftGutter_, itemRect.top_, itemRect.right_, itemRect.bottom_), item );
		ctx->getCurrentFont()->setColor( selectedTextColor );
	}
	else {
		ctx->getCurrentFont()->setColor( getFont()->getColor() );
	}
	
	
	Rect tmp = itemRect;

	bool stateNeedsDrawing = false;
	bool imageNeedsDrawing = false;

	if ( NULL != smallImageList_ ) {
		imageNeedsDrawing = true;
	}

	if ( idsNone != item->getDisplayState() ) {
		stateNeedsDrawing = true;
	}

	itemRect.setLeft( bounds.left_ );

	if ( imageNeedsDrawing ) {
		paintItemImage( ctx, itemRect, item );
	}

	if ( stateNeedsDrawing ) {
		paintItemState( ctx, itemRect, item );
	}	

	String itemText = item->getCaption();
	if ( getUseLocaleStrings() ) {
		itemText = System::getCurrentThreadLocale()->translate( itemText );
	}
	
	if( textBounded_ ){
		Rect itemPaintRect;
		itemPaintRect.setRect(itemRect.left_ + leftGutter_, currentTop, offsetX + bounds.getWidth() - scrollWidth - leftGutter_, currentTop + defaultItemHeight_ );
		ctx->textBoundedBy( &itemPaintRect, itemText, false );
	}
	else{
		ctx->textAt( itemRect.left_ + leftGutter_, y, itemText );
	}
	

	if ( item->canPaint() ) {
		item->paint( ctx, &tmp );
	}
}

void ListBoxControl::paint( GraphicsContext* ctx )
{
	if ( NULL != getView() ) {
		getView()->paintView( ctx );
		return;
	}


	

	Rect innerBounds = getClientBounds( true );//we DO need to account for the border here

	

	
	if ( useColorForBackground_ ) {
		ctx->setColor( getColor() );
		
		ctx->rectangle( &innerBounds );
		
		ctx->fillPath();		
	}
	else {	
		BackgroundState bkg;
		bkg.setEnabled( isEnabled() );
		bkg.setActive( isActive() );
		bkg.colorType_ = SYSCOLOR_FACE;	
		
		ctx->drawThemeBackground( &innerBounds, bkg );
	}
	

	ctx->setCurrentFont( getFont() );

	Scrollable* scrollable = getScrollable();
	if ( scrollable ) {
		Rect viewBounds = ctx->getViewableBounds();

		Point origin = ctx->getOrigin();

		adjustViewableBoundsAndOriginForScrollable( ctx, viewBounds, origin );

		ctx->setOrigin( origin );

		ctx->setViewableBounds( viewBounds );
	}


	ListModel* lm = getListModel();

	

	Rect bounds = getClientBounds();
	ctx->setClippingRect( &ctx->getViewableBounds() );

	double width = bounds.getWidth();
	double scrollW = 0;
	double offsetx = bounds.left_ + leftGutter_;
	if ( NULL != scrollable ) {
		if ( scrollable->getVirtualViewHeight() > getHeight() ) {
			scrollW = scrollable->getVerticalScrollbarWidth();
		}

		offsetx = maxVal<>( offsetx, offsetx + scrollable->getHorizontalPosition() );
	}

	if ( NULL != lm ) {
		Color* selectedTextColor =
				GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );
		
		double currentTop = bounds.top_;
		Rect itemRect;
		Rect itemPaintRect;
		double totalHeight = 0;


		Color oldFontColor;
		oldFontColor = *getFont()->getColor();



		Rect viewBounds = ctx->getViewableBounds();
		//Point origin = ctx->getOrigin();
		//viewBounds.offset( -origin.x_, -origin.y_ );
		Array<ListItem*>::iterator it = items_.begin();
		while ( it != items_.end() ) {
			ListItem* item = *it;
			itemRect.setRect( offsetx, currentTop, offsetx + (width-scrollW), currentTop + defaultItemHeight_ );

			item->setBounds( itemRect );

			if ( ((itemRect.top_ <= viewBounds.bottom_ ) && (itemRect.bottom_ >= viewBounds.top_ )) ||
					(itemRect.containsPt( &viewBounds.getTopLeft()) || (itemRect.containsPt( &viewBounds.getBottomRight() )) ) ) {
				totalHeight += itemRect.getHeight();			

				paintItem( ctx, itemRect, currentTop, selectedTextColor, 
							bounds, scrollW, offsetx, item );
				
			}

			currentTop += itemRect.getHeight();

			++it;
		}
	}
}

void ListBoxControl::paintSelectionRect( GraphicsContext* ctx, Rect* rect, ListItem* item )
{
	Color* selectedColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION );
	Color* selectedTextColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );
	Color* greyColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	ctx->setColor( selectedColor );
	ctx->rectangle( rect );
	ctx->fillPath();
	ctx->setColor( greyColor );
	ctx->strokePath();
	ctx->setColor( selectedTextColor );
}

ListItem* ListBoxControl::findSingleSelectedItem( Point* pt )
{
	ListItem* result = NULL;

	Point tmpPt = *pt;
	tmpPt.x_ = 1;

	ListModel* lm = getListModel();
	if ( NULL != lm ) {
		double currentTop = 0.0;
		Rect itemRect;
		Array<ListItem*>::iterator it = items_.begin();
		while ( it != items_.end() ) {
			ListItem* item = *it;
			itemRect.setRect( 0, currentTop, getWidth(), currentTop + defaultItemHeight_ );
			if ( true == itemRect.containsPt( &tmpPt ) ) {
				result = item;
				break;
			}
			currentTop += itemRect.getHeight();
			++it;
		}
	}

	return result;
}

bool ListBoxControl::stateHitTest( Point* point, ListItem* item )
{
	bool result = false;

	Rect stateRect = getStateRect( item );

	result = stateRect.containsPt( point );

	return result;
}

void ListBoxControl::mouseDown( MouseEvent* event )
{
	ListControl::mouseDown( event );
	if ( (true == event->hasLeftButton()) && (Component::csNormal == getComponentState()) ) {
		keepMouseEvents();

		ListItem* foundItem = findSingleSelectedItem( event->getPoint() );
		if ( NULL != foundItem ) {
			//check state hit test first!
			if ( foundItem->getDisplayState() != idsNone ) {
				if ( stateHitTest( event->getPoint(), foundItem ) ) {
					int32 state = foundItem->getDisplayState();
					if ( idsChecked == state ) {
						state = idsUnChecked;
					}
					else if ( idsUnChecked == state ) {
						state = idsChecked;
					}
					else if ( idsRadioUnpressed == state ) {
						state = idsRadioPressed;
					}
					else if ( idsRadioPressed == state ) {
						state = idsRadioUnpressed;
					}
					foundItem->setDisplayState( state );

					ItemEvent event( foundItem, ListBoxControl::lbeItemStateChangeRequested );
					ItemStateChangeRequested( &event );

					repaint();

					return;
				}
			}


			if ( true == allowsMultiSelect_ && true == allowsExtendedSelect_ ) {
				if( event->hasShiftKey() ){
					if( foundItem->getIndex() == getSelectedItem() ){
						for( uint32 j=0;j<selectedItems_.size();j++ ){
							selectedItems_[j]->setSelected(false);
						}
						selectedItems_.clear();
						selectedItems_.push_back(foundItem);
						foundItem->setSelected(true);
						selectionChanged( foundItem );
					}
					else if( ListModel::InvalidIndex != getSelectedItem() ){
						ListItem* selected = getItem( getSelectedItem() );
						uint32 foundItemPos = foundItem->getIndex();
						uint32 singlePos = selected->getIndex();
						for( uint32 j=0;j<selectedItems_.size();j++ ){
							selectedItems_[j]->setSelected(false);
						}
						if(foundItemPos < singlePos){// rangeSelect clears selectedItems_
							rangeSelect(true, foundItem, selected );
						}
						else{
							rangeSelect(true, selected, foundItem );
						}
						selectionChanged( foundItem );
					}
					else{// needed if no items currently selected.
						foundItem->setSelected(true);
						selectedItems_.push_back(foundItem);
						selectionChanged( foundItem );
					}
				}
				else if( event->hasControlKey() ){
					if( foundItem->isSelected() ){
						foundItem->setSelected(false);
						eraseFromSelectedItems( foundItem );
						selectionChanged( foundItem );
					}
					else{
						foundItem->setSelected(true);
						selectedItems_.push_back(foundItem);
						selectionChanged( foundItem );
					}
				}
				else{

					if( !(selectedItems_.empty()) ) {

						for( uint32 j=0;j<selectedItems_.size();j++ ){
							selectedItems_[j]->setSelected(false);
						}

						selectedItems_.clear();
					}					
					
					selectedItems_.push_back(foundItem);
					foundItem->setSelected( true );
					selectionChanged( foundItem );
				}
			}
			else if ( true == allowsMultiSelect_ && false == allowsExtendedSelect_ ){
				if( foundItem->isSelected() ){
					foundItem->setSelected(false);
					eraseFromSelectedItems( foundItem );
					selectionChanged( foundItem );
				}
				else{
					foundItem->setSelected( true );
					selectedItems_.push_back( foundItem );
					selectionChanged( foundItem );
				}
			}
			else {
				//selectedItems_.clear();
				//selectedItems_.push_back( foundItem );
				setSelectedItem( foundItem );
			}
		}
		repaint();
	}
}

void ListBoxControl::mouseMove( MouseEvent* event )
{
	ListControl::mouseMove( event );
	if ( (true == event->hasLeftButton()) && (Component::csNormal == getComponentState()) ) {
		ListItem* foundItem = findSingleSelectedItem( event->getPoint() );
		if ( NULL != foundItem ) {
			if ( true == allowsMultiSelect_ ) {
				//if ( true == foundItem->isSelected() ){
				//	singleSelectedItem_ = foundItem; 
			//	/}
			//	else {
					//selectedItems_.push_back( foundItem );
					setSelectedItem( foundItem );
			//	}
			}
			else {
				if ( foundItem->getIndex() != getSelectedItem() )  {	   
					//JC - Integrated change by Berkano (Thanks Brian!) - fixes bug [1015368] ListBoxControl Mousemove error 
					//if(!selectedItems_.empty()) {
					// selectedItems_[0] = foundItem;//assumes index 0 exists
					setSelectedItem( foundItem );
					//}
				}
			}
		}
	}
}

void ListBoxControl::mouseUp( MouseEvent* event )
{
	ListControl::mouseUp( event );
	if ( (true == event->hasLeftButton()) && (Component::csNormal == getComponentState()) ) {
		releaseMouseEvents();
		repaint();
	}
}

void ListBoxControl::mouseClick( MouseEvent* event )
{
	ListControl::mouseClick( event );
}

void ListBoxControl::mouseDblClick( MouseEvent* event )
{
	ListControl::mouseDblClick( event );
}

void ListBoxControl::keyDown( KeyboardEvent* event )
{
	ListControl::keyDown( event );

	if ( Component::csNormal == getComponentState() ) {
		if ( true == allowsMultiSelect_ ) {

		}
		else {
			ListItem* item = getItem( getSelectedItem() );
			ListModel* lm = getListModel();
			if ( (NULL != item) && (NULL != lm) ) {
				uint32 index = item->getIndex();

				if ( vkUpArrow == event->virtualKeyCode ) {
					index --;

				}
				else if ( vkDownArrow == event->virtualKeyCode ) {
					index ++;
				}
				Array<ListItem*>::iterator found = 
					items_.begin() + index;
				if ( found != items_.end() ) {
					setSelectedItem( *found );
				}
			}
		}
	}
}

void ListBoxControl::keyUp( KeyboardEvent* event )
{
	ListControl::keyUp( event );
}

void ListBoxControl::keyPressed( KeyboardEvent* event )
{
	ListControl::keyPressed( event );
}

void ListBoxControl::setDefaultItemHeight( const double& defaultItemHeight )
{
	defaultItemHeight_ = defaultItemHeight;
	repaint();
}

Enumerator<ListItem*>* ListBoxControl::getSelectedItems()
{
	return selectedItems_.getEnumerator();
}

void ListBoxControl::selectionChanged( ListItem* item )
{
	ItemEvent event( item, ItemEvent::Selected );
	ItemSelectionChanged( &event );
}

void ListBoxControl::selectItem( const uint32& index )
{
	ListItem* selectedItem = getItem( index );

	if ( true != allowsMultiSelect_ ) {

		ListItem* oldSelected = getItem( getSelectedItem() );

		if( NULL != oldSelected ) {
			oldSelected->setSelected( false );		
		}
		
		if( !selectedItems_.empty() ) {

			for( uint32 j=0;j<selectedItems_.size();j++ ){
				selectedItems_[j]->setSelected(false);
			}

			selectedItems_.clear();
		}
	}

	if ( NULL != selectedItem ) {
		if ( selectedItems_.empty() ) {
			selectedItems_.push_back( selectedItem );		
		}
		else {
			if ( selectedItems_[0] != selectedItem ) {
				Array<ListItem*>::iterator found = 
					std::find( selectedItems_.begin(), selectedItems_.end(), selectedItem );
				if ( found != selectedItems_.end() ) {
					selectedItems_.erase( found );					
				}
				selectedItems_.insert( selectedItems_.begin(), selectedItem );				
			}
		}
	}


	if ( NULL != selectedItem ) {
		if( !(selectedItem->isSelected()) ) { //If already selected, it is already in selectedItems_!!			
			selectedItem->setSelected( true );
			selectionChanged( selectedItem );
		}
	}

	repaint();
}

void ListBoxControl::deselectAllItems()
{
	for( uint32 j=0;j<selectedItems_.size();j++ ){
		selectedItems_[j]->setSelected(false);
	}

	selectedItems_.clear();

	repaint();
}

void ListBoxControl::eraseFromSelectedItems(ListItem* item)
{
	std::vector<ListItem*>::iterator foundItemPos;
	foundItemPos = std::find( selectedItems_.begin(), selectedItems_.end(), item );
	
	if(foundItemPos != selectedItems_.end() ) selectedItems_.erase( foundItemPos );
}

void ListBoxControl::setAllowsExtendedSelect (const bool& allowsExtendedSelect)
{
	if ( true == allowsExtendedSelect ) {
		allowsMultiSelect_ = true;
	}

	allowsExtendedSelect_ = allowsExtendedSelect;
}

void ListBoxControl::setLeftGutter(const double& leftgutter)
{
	leftGutter_ = leftgutter;
	repaint();
}

void ListBoxControl::setRightGutter(const double& rightgutter)
{
	rightGutter_ = rightgutter;
	repaint();
}

void ListBoxControl::setTextBounded( const bool& istextbounded ){
	textBounded_ = istextbounded;
}

void ListBoxControl::setScrollable( Scrollable* scrollable )
{
	Control ::setScrollable( scrollable );

	scrollable_->setVirtualViewVertStep( getDefaultItemHeight() );
	scrollable_->setDiscreteScroll( false, true );
}


uint32 ListBoxControl::getSelectedItem()
{	
	uint32 result = ListModel::InvalidIndex;
	if ( !selectedItems_.empty() ) {
		result = selectedItems_[0]->getIndex();
	}
	return result;
}


void ListBoxControl::setLargeImageList( ImageList* imageList )
{
	largeImageList_ = imageList;
}

void ListBoxControl::setSmallImageList( ImageList* imageList )
{
	smallImageList_ = imageList;
}

void ListBoxControl::setStateImageList( ImageList* imageList )
{
	stateImageList_ = imageList;
}

Rect ListBoxControl::getItemImageRect( const uint32& index )
{
	Rect result;

	return result;
}

Enumerator<uint32>* ListBoxControl::getSelectedItemsByIndex()
{
	selectedIndices_.clear();
	selectedIndices_.resize( selectedItems_.size() );

	for (size_t i=0;i<selectedItems_.size();i++ ) {
		selectedIndices_[i] = selectedItems_[i]->getIndex();
	}

	return selectedIndices_.getEnumerator();
}

void ListBoxControl::rangeSelect( const Rect& selectionRect )
{

}

uint32 ListBoxControl::getFocusedItem()
{
	uint32 result = ListModel::InvalidIndex;
	return result;
}


bool ListBoxControl::allowsMultiSelect()
{
	return true;
}

void ListBoxControl::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	allowsMultiSelect_ = allowsMultiSelect;
}

uint32 ListBoxControl::hitTest( const Point& point )
{
	uint32 result = ListModel::InvalidIndex;
	return result;
}

Rect ListBoxControl::getItemRect( ListItem* item )
{
	Rect result;

	return result;
}

/**
$Id$
*/
