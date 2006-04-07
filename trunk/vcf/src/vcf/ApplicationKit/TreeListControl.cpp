//TreeListControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TreeListControl.h"
#include "vcf/ApplicationKit/HeaderControl.h"
#include "vcf/ApplicationKit/DefaultTreeModel.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"
#include "vcf/ApplicationKit/Containers.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


#define EXPANDER_SPACER		5.0




TreeListControl::TreeListControl():
	CustomControl(),
	header_(NULL),
	imageList_(NULL),
	stateImageList_(NULL),
	treeModel_(NULL),
	itemHeight_(25.0),
	columnHeight_(0.0),
	itemIndent_(19.0),
	displayOptions_(TreeListControl::tdoNone),
	allowLabelEditing_(false),
	allowMultipleSelection_(false),
	stateItemIndent_(19.0),
	draggingSelectionRect_(false),
	currentEditColumn_(-1),
	currentEditingControl_(NULL)
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );
	init();
}

TreeListControl::~TreeListControl()
{
	if ( NULL != treeModel_ ) {
//		treeModel_->release();
	}
}

void TreeListControl::init()
{
	draggingSelectionRect_ = false;
	treeModel_ = NULL;
	header_ = NULL;
	imageList_ = NULL;
	stateImageList_ = NULL;

	selectedItemContainer_.initContainer( selectedItems_ );

	allowMultipleSelection_ = false;
	allowLabelEditing_ = false;


	setTreeModel( new DefaultTreeModel() );

	addComponent( getViewModel() );

	itemHeight_ = getContext()->getTextHeight("EM") + 2.0;
	itemIndent_ = 19;
	stateItemIndent_ = 19;

	visibleItemsHeight_ = 0.0;

	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );

	rowLineColor_ = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	columnLineColor_ = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );


	header_ = new HeaderControl();
	columnHeight_ = header_->getHeight();
	add( header_, AlignTop );


	header_->setIgnoreForParentScrolling( true );

	header_->ColumnWidthChanged.addHandler(
							new ItemEventHandler<TreeListControl>( this,
																	&TreeListControl::onColumnWidthChanged,
																	"TreeListControl::onColumnWidthChanged" ) );

	setDisplayOptions( TreeListControl::tdoNone );

	setUseColorForBackground( true );

	EventHandler* ev = 
			new GenericEventHandler<TreeListControl>( this, &TreeListControl::onEditorFocusLost, "TreeListControl::onEditorFocusLost" );

		ev = 
			new KeyboardEventHandler<TreeListControl>( this, &TreeListControl::onEditingControlKeyPressed, "TreeListControl::onEditingControlKeyPressed" );
}

void TreeListControl::setTreeModel(TreeModel * model)
{
	if ( NULL != treeModel_ ) {
		EventHandler* handler = getEventHandler( "TreeListControl::onModelChanged" );
		if ( NULL != handler ) {
			treeModel_->removeTreeNodeAddedHandler( handler );
			treeModel_->removeTreeNodeDeletedHandler( handler );
		}
		getViewModel()->removeView( this );
	}

	treeModel_ = model;

	if ( NULL != treeModel_ ) {
		Model* tm = dynamic_cast<Model*>(treeModel_);

		tm->addView( this );

		EventHandler* handler = getEventHandler( "TreeListControl::onModelChanged" );
		if ( NULL == handler ) {
			handler = new TreeModelEventHandler<TreeListControl>( this, &TreeListControl::onModelChanged, "TreeListControl::onModelChanged" );
			
			//JC - commented this out - this is unneccesary
			//addEventHandler( "TreeListControl::onModelChanged", handler );
		}

		treeModel_->addTreeNodeAddedHandler( handler );
		treeModel_->addTreeNodeDeletedHandler( handler );	
		
		handler = getEventHandler( "TreeListControl::onModelEmptied" );
		if ( NULL == handler ) {
			handler = new GenericEventHandler<TreeListControl>( this, &TreeListControl::onModelEmptied, "TreeListControl::onModelEmptied" );
		}
		tm->addModelHandler( handler );
	}
	else {
		setViewModel( NULL );
	}
}

TreeModel* TreeListControl::getTreeModel()
{
	return treeModel_;
}

void TreeListControl::onModelEmptied( Event* event )
{
	if ( Model::MODEL_EMPTIED == event->getType() ) {
		selectedItems_.clear();
		cancelEditing();
		recalcScrollable();
	}
}

void TreeListControl::onModelChanged( TreeModelEvent* event )
{
	switch ( event->getType() ) {
		case TreeModel::TREEITEM_DELETED : {
			std::vector<TreeItem*>::iterator found = std::find( selectedItems_.begin(),
																selectedItems_.end(),
																event->getTreeItem() );
			if ( found != selectedItems_.end() ) {
				selectedItems_.erase( found );
				repaint();
			}
		}
		break;

		case TreeModel::TREEITEM_ADDED : {
			event->getTreeItem()->setControl( this );
		}
		break;
	}


	recalcScrollable();
	
}

void TreeListControl::recalcScrollable()
{
	Scrollable* scrollable = getScrollable();
	if ( NULL != scrollable ) {
		double oldVisibleHeight = visibleItemsHeight_;

		visibleItemsHeight_ = 0;
		if ( header_->getVisible() ) {
			visibleItemsHeight_ += header_->getHeight();
		}

		std::vector<TreeItem*> visibleItems;		

		populateVisiblityList( visibleItems );

		std::vector<TreeItem*>::iterator it = visibleItems.begin();
		while ( it != visibleItems.end() ) {
			TreeItem* item = *it;
			
			visibleItemsHeight_ += item->getBounds()->getHeight();
			it ++;
		}

		scrollable->setVirtualViewHeight( visibleItemsHeight_ );

		if ( (getHeight() > visibleItemsHeight_) && (scrollable->getVerticalPosition() > 0.0) ) {
			scrollable->setVerticalPosition( 0.0 );
		}
		else if ( oldVisibleHeight > visibleItemsHeight_ ) {
			double newPos = minVal<double>( abs((long)(visibleItemsHeight_ - getHeight()))+1.0, scrollable->getVerticalPosition() );
			
			scrollable->setVerticalPosition( newPos );
			
		}
	}
}

void TreeListControl::paintItem( TreeItem* item, GraphicsContext* context, Rect* paintRect )
{
	bool isALeaf = item->isLeaf();

	visibleItemsHeight_ += paintRect->getHeight();

	if ( displayOptions_ & TreeListControl::tdoShowRowLines ) {
		context->setColor( &rowLineColor_ );
		context->moveTo( paintRect->left_, paintRect->bottom_ );
		context->lineTo( paintRect->right_, paintRect->bottom_ );
		context->strokePath();
	}

	item->setBounds( paintRect );

	TreeModel* treeModel = getTreeModel();
	ColumnModel* columnModel = header_->getColumnModel();

	double indent = getCurrentIndent( item );

	Rect captionRect = *paintRect;
	captionRect.left_ = paintRect->left_ + indent + itemHeight_;

	if ( columnModel->getCount() > 0 ) {
		ColumnItem* col = columnModel->getItemFromIndex( 0 );
		if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
			captionRect.right_ = maxVal<double>( captionRect.left_ + 1.0,
												paintRect->left_ + col->getWidth() );
		}
		else {
			captionRect.right_ = captionRect.left_ + context->getTextWidth( item->getCaption() ) + 5;
		}
	}
	else {
		captionRect.right_ = captionRect.left_ + context->getTextWidth( item->getCaption() ) + 5;
	}

	captionRect.right_ -= 3;


	double textH = context->getTextHeight( item->getCaption() );
	captionRect.top_ = captionRect.top_ + ((captionRect.getHeight() / 2.0) - textH/2.0);
	captionRect.bottom_ = captionRect.top_ + textH;

	if ( TreeListControl::tdoShowHierarchyLines & displayOptions_ ) {
		hierarchyHeightMap_[item] = paintRect->top_ + itemHeight_/2.0;

		if ( false == item->isRoot() ) {
			TreeItem* parent = item->getParent();
			std::map<TreeItem*,double>::iterator found = hierarchyHeightMap_.find( parent );
			if ( found != hierarchyHeightMap_.end() ) {
				double baseIndent = getItemIndent() *  item->getLevel() - 1;
				double parentIndent = getItemIndent() * parent->getLevel() - 1;

				Color oldColor = *(context->getColor());
				Color* selectedColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
				context->setColor( selectedColor );

				context->moveTo( paintRect->left_ + baseIndent + itemHeight_/2.0, paintRect->top_ + itemHeight_/2.0 );
				context->lineTo( paintRect->left_ + parentIndent + itemHeight_/2.0, paintRect->top_ + itemHeight_/2.0 );

				context->lineTo( paintRect->left_ + parentIndent + itemHeight_/2.0, found->second );
				context->strokePath();

				context->setColor( &oldColor );
			}
		}
	}




	if ( true == item->isSelected() ) {

		Color oldColor = *(context->getColor());
		Color* selectedColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION );
		context->setColor( selectedColor );
		Rect tmp = *paintRect;

		if ( displayOptions_ & TreeListControl::tdoShowFullRowSelection ) {
			//tmp.inflate( -2, -2 );
		}
		else {
			tmp.left_ = paintRect->left_ + indent + itemHeight_ - 1;

			tmp.right_ = captionRect.right_;
			//tmp.inflate( 0, -2 );
		}

		tmp.right_ = maxVal<double>( tmp.left_, tmp.right_ );

		context->rectangle( &tmp );

		if ( true == isFocused() ) {
			context->fillPath();
			DrawUIState state;
			state.setFocused( true );
			state.setActive( true );
			
			context->drawThemeSelectionRect( &tmp, state );
		}
		else {
			context->strokePath();
		}

		context->setColor( &oldColor );
	}


	bool stateNeedsDrawing = false;
	bool imageNeedsDrawing = false;

	//determine if we have an image list present
	if ( NULL != imageList_ ) {
		imageNeedsDrawing = true;
	}

	if ( Item::idsNone != item->getState() ) {
		stateNeedsDrawing = true;
	}

	if ( true == stateNeedsDrawing ) {
		paintItemState( item, context, paintRect, (long)indent );
	}

	if ( true == imageNeedsDrawing ) {
		paintItemImage( item, context, paintRect, (long)indent );
	}

	if ( false == isALeaf ) {
		paintExpander( item, context, paintRect );
	}

	long drawOptions = GraphicsContext::tdoNone;
	drawOptions |= GraphicsContext::tdoLeftAlign;

	Color oldColor = *(context->getCurrentFont()->getColor());

	if ( (true == item->isSelected()) && (true == isFocused()) ) {
		Color* selectedColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );		
		context->getCurrentFont()->setColor( selectedColor );
	}
	else {
		context->getCurrentFont()->setColor( item->getTextColor() );
	}

	context->getCurrentFont()->setBold( item->getTextBold() );

	captionRect.right_ -= 5;

	context->textBoundedBy( &captionRect, item->getCaption(), drawOptions );

	context->getCurrentFont()->setColor( &oldColor );

	if ( item->canPaint() ) {
		item->paint( context, paintRect );
	}

	if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {

		Enumerator<ColumnItem*>* columns =  columnModel->getItems();
		int columnIndex = 0;

		if ( NULL != columns ) {
			Rect subItemRect = *paintRect;
			subItemRect.left_ -= 2;
			while ( true == columns->hasMoreElements() ) {
				ColumnItem* col = columns->nextElement();

				if ( columnIndex > 0 ) {
					subItemRect.right_ = subItemRect.left_ + col->getWidth();
					paintSubItem( item, context, columnIndex, &subItemRect );
				}
				subItemRect.left_ += col->getWidth();
				columnIndex++;
			}
		}
	}

}

void TreeListControl::paintSubItem( TreeItem* item, GraphicsContext* context, const ulong32& subItemIndex, Rect* paintRect )
{
	if ( displayOptions_ & TreeListControl::tdoShowColumnLines ) {

		context->setColor( &columnLineColor_ );

		ColumnModel* columnModel = header_->getColumnModel();

		context->moveTo( paintRect->left_, paintRect->top_ );
		context->lineTo( paintRect->left_, paintRect->bottom_ );
		context->strokePath();

		if ( (columnModel->getCount()-1) == subItemIndex ) {
			context->moveTo( paintRect->right_, paintRect->top_ );
			context->lineTo( paintRect->right_, paintRect->bottom_ );
			context->strokePath();
		}
	}

	if ( subItemIndex > 0 ) {
		if ( (true == item->isSelected()) && (true == isFocused()) ) {
			Color* selectedColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );		
			context->getCurrentFont()->setColor( selectedColor );
		}
		else {
			context->getCurrentFont()->setColor( item->getTextColor() );
		}

		TreeItem::SubItem* subItem = item->getSubItem( subItemIndex-1 );
		if ( NULL != subItem ) {

			long drawOptions = GraphicsContext::tdoNone;
			drawOptions |= GraphicsContext::tdoLeftAlign;
			Rect captionRect = *paintRect;
			captionRect.left_ += 5;
			captionRect.right_ -= 5;
			
			double textH = context->getTextHeight( "EM" );
			captionRect.top_ = captionRect.top_ + ((captionRect.getHeight() / 2.0) - textH/2.0);
			captionRect.bottom_ = captionRect.top_ + textH;

			
			
			context->textBoundedBy( &captionRect, subItem->getCaption(), drawOptions );

			if ( subItem->canPaint() ) {
				subItem->paint( context, paintRect );
			}
		}
	}
}

void TreeListControl::paintExpander( TreeItem* item, GraphicsContext* context, Rect* paintRect )
{
	double spacer = EXPANDER_SPACER;
	Rect expanderRect = *paintRect;
	double dy = expanderRect.getHeight() - getFont()->getHeight();

	expanderRect.left_ = getItemIndent() *  item->getLevel() + 1;


	expanderRect.inflate( 0.0, -(dy/2.0) );

	expanderRect.right_ = expanderRect.left_ + expanderRect.getHeight();
#define TRIANGLE_BTN

#ifndef TRIANGLE_BTN
	//expanderRect.inflate( -expanderRect.getWidth()/4.0, -expanderRect.getHeight()/4.0 );

	context->setColor( Color::getColor("white") );
	context->rectangle( &expanderRect );
	context->fillPath();

	context->setColor( Color::getColor("black") );
	context->rectangle( &expanderRect );
	context->strokePath();

	if ( true == item->isExpanded() ) {
		context->moveTo( expanderRect.left_ + expanderRect.getWidth()/2.0 - expanderRect.getWidth()/4.0,
						expanderRect.top_ + expanderRect.getHeight()/2.0 );

		context->lineTo( expanderRect.right_ - expanderRect.getWidth()/2.0 + expanderRect.getWidth()/4.0,
						expanderRect.top_ + expanderRect.getHeight()/2.0 );

		context->strokePath();

	}
	else {
		context->moveTo( expanderRect.left_ + expanderRect.getWidth()/2.0 - expanderRect.getWidth()/4.0,
						expanderRect.top_ + expanderRect.getHeight()/2.0 );

		context->lineTo( expanderRect.right_ - expanderRect.getWidth()/2.0 + expanderRect.getWidth()/4.0,
						expanderRect.top_ + expanderRect.getHeight()/2.0 );

		context->strokePath();


		context->moveTo( expanderRect.left_ + expanderRect.getWidth()/2.0 -0.5 ,
						 expanderRect.top_ + expanderRect.getHeight()/2.0 - expanderRect.getHeight()/4.0 );

		context->lineTo( expanderRect.left_ + expanderRect.getWidth()/2.0 - 0.5,
						 expanderRect.bottom_ - expanderRect.getHeight()/2.0 + expanderRect.getHeight()/4.0 + 1.0);

		context->strokePath();
	}
#else
	std::vector<Point> triangle(4);

	if ( true == item->isExpanded() ) {
		//triangle width is 9, and height is 9
		//triangle.resize(6);
		triangle[0].x_ = expanderRect.left_+spacer;
		triangle[0].y_ = (int)(((expanderRect.top_ + expanderRect.getHeight()/2.0) - 9.0/2.0)  + 0.5);
		//triangle[1] = triangle[0];
		//triangle[1].y_ += 1;
		triangle[1].x_ = (int)((triangle[0].x_ + 9.0/2.0) + 0.0);
		triangle[1].y_ = triangle[0].y_ + 9;
		triangle[2] = triangle[0];
		triangle[2].x_ += 9;
		triangle[3] = triangle[0];
		//triangle[4].x_ += 9;
		//triangle[5] = triangle[0];



		
		//triangle[1] = Point( triangle[0].x_ + (expanderRect.getWidth()), triangle[0].y_ ) );
		//triangle[2] = Point( triangle[0].x_ + (expanderRect.getWidth()/2.0), triangle[0].y_ + (expanderRect.getHeight()/2.0);
		//triangle[3] = Point( triangle[0].x_, triangle[0].y_ );
	}
	else {
		//triangle width is 10, and height is 11
		triangle[0].x_ = expanderRect.left_+spacer;
		triangle[0].y_ = (int)(((expanderRect.top_ + expanderRect.getWidth()/2.0) - 11/2.0) + 0.5);

		triangle[1] = triangle[0];
		triangle[1].y_ += 11;

		triangle[2].x_ = triangle[0].x_ + 10;
		triangle[2].y_ = (int)((triangle[0].y_ + 11.0/2.0) + 0.5);
		triangle[3] = triangle[0];
	}


	context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW ) );
	context->polyline( triangle );
	context->fillPath();
/*
	if ( true == item->isExpanded() ) {
		context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW ) );
		context->moveTo( triangle[1].x_-1, triangle[1].y_ );
		context->lineTo( triangle[0].x_, triangle[0].y_ );
		context->lineTo( triangle[2].x_, triangle[2].y_ );
		context->strokePath();

		context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT ) );
		context->moveTo( triangle[2].x_, triangle[2].y_ );
		context->lineTo( triangle[1].x_-1, triangle[1].y_ );
		context->strokePath();
	}
	else {
		context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW ) );
		context->moveTo( triangle[1].x_, triangle[1].y_-1 );
		context->lineTo( triangle[0].x_, triangle[0].y_ );
		context->lineTo( triangle[2].x_+1, triangle[2].y_+1 );
		context->strokePath();

		context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT ) );
		context->moveTo( triangle[2].x_, triangle[2].y_+1 );
		context->lineTo( triangle[1].x_, triangle[1].y_ );
		context->strokePath();
	}
	*/

#endif
}

void TreeListControl::paintItemState( TreeItem* item, GraphicsContext* context, Rect* paintRect, const long& currentIndent )
{
	Rect stateRect = getStateRect( item, currentIndent );

	stateRect.inflate( -1, -1 );

	if ( NULL != stateImageList_ ) {
		stateImageList_->draw( context, item->getStateImageIndex(), &stateRect );
	}
	else {
		stateRect.inflate( -1, -1 );
		long state = item->getState();

		ButtonState buttonState;
		buttonState.setActive( true );
		buttonState.setPressed( state == Item::idsChecked ? true : false );
		context->drawThemeCheckboxRect( &stateRect, buttonState );
/*
		if ( state == Item::idsChecked )
		{
			stateRect.inflate(-2,-2);
			stateRect.setRight(stateRect.getRight()-4);
			context->setColor(Color::getColor("blue"));
			context->rectangle(&stateRect);
			context->fillPath();
			// Below draws an X for a checked entry
			context->setAntiAliasingOn(true);
			context->moveTo(stateRect.getTopLeft());
			context->lineTo(stateRect.getBottomRight());
			context->moveTo(stateRect.getTopRight());
			context->lineTo(stateRect.getBottomLeft());
			context->strokePath();

		}
		*/
	}
}

void TreeListControl::paintItemImage( TreeItem* item, GraphicsContext* context, Rect* paintRect, const long& currentIndent )
{
	Rect imageRect;
	imageRect.left_ += currentIndent;
	imageRect.right_ = imageRect.left_ + imageList_->getImageWidth();

	ulong32 index = item->getImageIndex();
	if ( (true == item->isExpanded()) && (item->getExpandedImageIndex() < imageList_->getImageCount()) ) {
		index = item->getExpandedImageIndex();
	}

	imageRect.top_ = paintRect->top_ + (paintRect->getHeight()/2.0 - imageList_->getImageHeight()/2.0);
	imageRect.bottom_ = imageRect.top_ + imageList_->getImageHeight();

	if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
		//get the first column width
		ColumnItem* item = header_->getColumnModel()->getItemFromIndex(0);
		Rect tmp = *paintRect;
		tmp.left_ += item->getWidth();
		if ( imageRect.right_ > tmp.left_ ) {
			imageRect.right_ = maxVal<double>( imageRect.left_, tmp.left_ );
		}
	}

	if ( false == imageRect.isEmpty() ) {

		imageRect.inflate( -1, -1 );

		imageList_->draw( context, index, &imageRect );
	}
}


void TreeListControl::paint( GraphicsContext * context )
{
	CustomControl::paint( context );

	paintChildren( context );
	
	visibleItemsHeight_ = 0;

	hierarchyHeightMap_.clear();

	Rect borderRect = getClientBounds();

	
	Rect itemRect;

	double prevTop = borderRect.top_ + header_->getHeight();

	Rect clipRect = context->getViewableBounds();

	context->setClippingRect( &clipRect );

	std::vector<TreeItem*> visibleItems;

	populateVisiblityList( visibleItems );

	std::vector<TreeItem*>::iterator it = visibleItems.begin();

	itemRect.left_ = borderRect.left_;
	itemRect.right_ = borderRect.right_;
	Rect tmp;
	Rect intersection;
	while ( it != visibleItems.end() ) {
		TreeItem* item = *it;

		itemRect.top_ = prevTop;
		itemRect.bottom_ = itemRect.top_ + getDefaultItemHeight();
		tmp = itemRect;

		// *MASSIVE* speedup for large trees by only drawing items that are visible on screen!! -aroman
		intersection = clipRect.makeIntersection(&itemRect);
		if (intersection.getWidth() > 0 && intersection.getHeight() > 0)
		{
			paintItem( item, context, &itemRect );
		}

		prevTop += (itemRect.bottom_ - tmp.top_);

		it ++;
	}
}


void TreeListControl::addItem( TreeItem* item, TreeItem* parent )
{
	treeModel_->addNodeItem( item, parent );
	item->setControl( this );
	if ( NULL != parent ) {
		parent->expand( true );
	}
	repaint();
}

TreeItem* TreeListControl::addItem( TreeItem* parent, const String& caption, const ulong32 imageIndex )
{
	DefaultTreeItem* result = new DefaultTreeItem( caption, this, treeModel_ );
	result->setImageIndex( imageIndex );
	addItem( result, parent );
	return result;
}

TreeItem* TreeListControl::hitTest( Point* pt )
{
	TreeItem* result = NULL;
	Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();
	while ( rootChildren->hasMoreElements() ) {
		TreeItem* rootItem = rootChildren->nextElement();
		result = hitTest( pt, rootItem );
		if ( NULL != result ) {
			break;
		}
	}

	return result;
}

TreeItem* TreeListControl::hitTest( Point* pt, TreeItem* itemToTest )
{
	TreeItem* result = NULL;

	if ( true == itemToTest->containsPoint( pt ) ) {
		if ( ! (displayOptions_ & TreeListControl::tdoShowFullRowSelection) ) {
			if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
				ColumnItem* column = header_->getColumnModel()->getItemFromIndex(0);
				Rect tmp = *itemToTest->getBounds();
				tmp.right_ = tmp.left_ + column->getWidth();
				if ( true == tmp.containsPt( pt ) ) {
					result = itemToTest;
				}
			}
			else {
				GraphicsContext* ctx = getContext();
				double w = ctx->getTextWidth( itemToTest->getCaption() );
				Rect tmp = *itemToTest->getBounds();
				tmp.right_ = tmp.left_ + w + getCurrentIndent(itemToTest) ;
				if ( true == tmp.containsPt( pt ) ) {
					result = itemToTest;
				}
			}
		}
		else {
			result = itemToTest;
		}
	}
	else {
		if ( (false == itemToTest->isLeaf()) && (true == itemToTest->isExpanded()) ) {
			Enumerator<TreeItem*>* children = itemToTest->getChildren();
			while ( true == children->hasMoreElements() ) {
				TreeItem* item = children->nextElement();
				result = hitTest( pt, item );
				if ( NULL != result ) {
					break;
				}
			}
		}
	}

	return result;
}


bool TreeListControl::stateHitTest( Point* pt, TreeItem* itemToTest )
{
	bool result = false;

	Rect stateRect = getStateRect( itemToTest, getCurrentIndent( itemToTest ) );

	result = stateRect.containsPt( pt );

	return result;
}

void TreeListControl::setItemIndent( const ulong32& itemIndent )
{
	itemIndent_ = itemIndent;
	repaint();
}

bool TreeListControl::multiSelectionChange( MouseEvent* event )
{
	bool result = false;

	TreeItem* foundItem = NULL;
	Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();

	TreeItem* currentlySelectedItem = getSelectedItem();

	while ( rootChildren->hasMoreElements() ) {
		TreeItem* rootItem = rootChildren->nextElement();
		foundItem = hitTest( event->getPoint(), rootItem );
		if ( NULL != foundItem ) {
			Rect expanderRect;

			ulong32 level = foundItem->getLevel();
			expanderRect = *foundItem->getBounds();
			expanderRect.left_ += (level * itemIndent_);
			expanderRect.right_ = expanderRect.left_ + itemIndent_;

			//currentSelectedItem_ = foundItem;

			if ( true == expanderRect.containsPt( event->getPoint() ) ) {
				foundItem->expand( !foundItem->isExpanded() );
				ItemEvent event( this, ITEM_EVENT_CHANGED );
				ItemExpanded.fireEvent( &event );
			}
			else if ( true == stateHitTest( event->getPoint(), foundItem ) ) {
				long state = foundItem->getState();
				//probably need to come up with better id's
				//for enum values so that we can mask together
				//as opposed to doing a direct
				//assignment
				if ( Item::idsChecked == state ) {
					state = Item::idsUnChecked;
				}
				else if ( Item::idsUnChecked == state ) {
					state = Item::idsChecked;
				}

				foundItem->setState( state );
				ItemEvent event( foundItem, TreeListControl::ITEM_STATECHANGE_REQUESTED );
				ItemStateChangeRequested.fireEvent( &event );
			}
			else if ( (true == event->hasLeftButton()) && (true == event->hasShiftKey()) && NULL!=currentlySelectedItem ) {
				rootChildren->reset();
				clearSelectedItems();

				std::vector<TreeItem*> selectedItems;

				bool startFound = false;
				Rect* bounds1 = currentlySelectedItem->getBounds();
				Rect* bounds2 = foundItem->getBounds();
				TreeItem* firstItem = currentlySelectedItem;
				TreeItem* lastItem = foundItem;
				if ( bounds2->top_ < bounds1->top_ ) {
					firstItem = foundItem;
					lastItem = currentlySelectedItem;
				}

				selectedItems.push_back( firstItem );

				while ( rootChildren->hasMoreElements() ) {
					TreeItem* rootItem = rootChildren->nextElement();
					bool done = listSelectedItems( selectedItems, firstItem, lastItem, rootItem, startFound );
					if ( true == done ) {
						break;
					}
				}

				std::vector<TreeItem*>::iterator it = selectedItems.begin();
				while ( it != selectedItems.end() ) {
					setSelectedItem( *it, true );
					it ++;
				}
			}
			else {
				setSelectedItem( foundItem, !foundItem->isSelected() );
				result = true;
			}
			repaint();
			break;
		}
		else if ( (true == event->hasLeftButton()) && (false == draggingSelectionRect_) ){
			//null item - start a selection drag
			draggingSelectionRect_ = true;
			dragPoint_ = *event->getPoint();
			dragSelectionRect_.setRect( dragPoint_.x_, dragPoint_.y_, dragPoint_.x_, dragPoint_.y_ );
		}
	}

	return result;
}

void TreeListControl::clearSelectedItems()
{
	std::vector<TreeItem*>::iterator it = selectedItems_.begin();
	while ( it != selectedItems_.end() ) {
		TreeItem* item = *it;
		item->setSelected( false );
		ItemEvent event( this, ITEM_EVENT_UNSELECTED );
		event.setUserData( (void*)item );
		ItemSelected.fireEvent( &event );
		it ++;
	}
	selectedItems_.clear();
	repaint();
}

void TreeListControl::mouseClick(  MouseEvent* event )
{
	CustomControl::mouseClick( event );

	
}

void TreeListControl::mouseDblClick(  MouseEvent* event )
{
	CustomControl::mouseDblClick( event );

	TreeItem* item = getSelectedItem();

	if ( NULL != item ) {
		
		Rect expanderRect;
		
		ulong32 level = item->getLevel();
		expanderRect = *item->getBounds();
		expanderRect.left_ += (level * itemIndent_);
		expanderRect.right_ = expanderRect.left_ + itemIndent_;	
		
		if ( !expanderRect.containsPt( event->getPoint() ) &&
				!stateHitTest( event->getPoint(), item ) ) {

			item->expand( !item->isExpanded() );
			ItemEvent event( this, ITEM_EVENT_CHANGED );
			ItemExpanded.fireEvent( &event );
			
			recalcScrollable();
		}
		repaint();
	}
}

Rect TreeListControl::getExpanderRect( TreeItem* item )
{
	Rect result;

	ulong32 level = item->getLevel();
	result = *item->getBounds();
	result.left_ += (level * itemIndent_);
	result.right_ = result.left_ + itemIndent_;

	return result;
}

bool TreeListControl::singleSelectionChange( MouseEvent* event )
{
	bool result = false;

	TreeItem* foundItem = NULL;
	Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();
	TreeItem* prevSelectedItem = getSelectedItem();

	while ( rootChildren->hasMoreElements() ) {
		TreeItem* rootItem = rootChildren->nextElement();
		foundItem = hitTest( event->getPoint(), rootItem );
		if ( NULL != foundItem ) {

			Rect expanderRect;

			ulong32 level = foundItem->getLevel();
			expanderRect = *foundItem->getBounds();
			expanderRect.left_ += (level * itemIndent_);
			expanderRect.right_ = expanderRect.left_ + itemIndent_;

			//currentSelectedItem_ = foundItem;

			if ( expanderRect.containsPt( event->getPoint() ) ) {
				foundItem->expand( !foundItem->isExpanded() );
				ItemEvent event( this, ITEM_EVENT_CHANGED );
				ItemExpanded.fireEvent( &event );

				recalcScrollable();

				if ( !foundItem->isExpanded() ) {
					if ( NULL != prevSelectedItem ) {
						if ( prevSelectedItem->getParent() == foundItem ) {
							setSelectedItem( prevSelectedItem, false );
							setSelectedItem( foundItem, true );							
							result = true;
							repaint();
						}
					}
				}
			}
			else if ( stateHitTest( event->getPoint(), foundItem ) ) {
				long state = foundItem->getState();
				//probably need to come up with better id's
				//for enum values so that we can mask together
				//as opposed to doing a direct
				//assignment
				if ( Item::idsChecked == state ) {
					state = Item::idsUnChecked;
				}
				else if ( Item::idsUnChecked == state ) {
					state = Item::idsChecked;
				}

				foundItem->setState( state );
				ItemEvent event( foundItem, TreeListControl::ITEM_STATECHANGE_REQUESTED );
				ItemStateChangeRequested.fireEvent( &event );
			}
			else {

				if ( prevSelectedItem != NULL ) {
					if ( prevSelectedItem != foundItem ) {
						setSelectedItem( prevSelectedItem, false );
					}
				}

				result = (prevSelectedItem != foundItem);

				setSelectedItem( foundItem, true );
			}
			repaint();
			break;
		}
	}

	if ( NULL == foundItem ) {
		if ( prevSelectedItem != NULL ) {
			if ( prevSelectedItem != foundItem ) {
				setSelectedItem( prevSelectedItem, false );
			}
		}
	}
	
	return result;
}

Rect TreeListControl::getBoundsForEdit( TreeItem* item, int column )
{
	Rect result;

	if ( column == -1 ) {
		return result;
	}


	ColumnModel* cm = header_->getColumnModel();
	Enumerator<ColumnItem*>* columnItems = cm->getItems();

	result = *item->getBounds();

	int index = 0;
	while ( columnItems->hasMoreElements() ) {
		ColumnItem* col = columnItems->nextElement();
		result.right_ = result.left_ + col->getWidth();

		if ( index == column ) {

			if ( 0 == column ) {
				//adjust for state and image icons
				Rect expanderRect = getExpanderRect( item );
		
				if ( !item->isLeaf() ) {
					result.left_ = expanderRect.right_;
				}

				Rect stateRect = getStateRect( item, getCurrentIndent( item ) );

				if ( !stateRect.isEmpty() && !stateRect.isNull() ) {
					result.left_ = maxVal<>( stateRect.right_, result.left_ );
				}
			}

			//adjust for scrollers
			Scrollable* scrollable = getScrollable();
			if ( NULL != scrollable ) {
				result.offset( -scrollable->getHorizontalPosition(), -scrollable->getVerticalPosition());
				Rect clientBounds = getClientBounds();
				double w = clientBounds.getWidth();
				double h = clientBounds.getHeight();

				if ( scrollable->isVerticalScrollbarVisible() ) {
					result.right_ = minVal<>( result.right_, 
											w - scrollable->getVerticalScrollbarWidth() );
				}
				
				if ( scrollable->isHorizontalScrollbarVisible() ) {
					result.bottom_ = minVal<>( result.bottom_, 
											h - scrollable->getHorizontalScrollbarHeight() );
				}
			}

			break;
		}
		result.left_ += col->getWidth();
		index++;
	}

	return result;
}

int TreeListControl::hitTestForEditColumn( Point* pt )
{
	int result = -1;

	TreeItem* item = hitTest( pt );
	if ( NULL != item ) {
		if ( item->getSubItemCount() > 0 ) {

			result = 0;
				 
			ColumnModel* cm = header_->getColumnModel();
			Enumerator<ColumnItem*>* columnItems = cm->getItems();

			Rect subItemRect = *item->getBounds();
			subItemRect.right_ = subItemRect.left_ + cm->getItemFromIndex( 0 )->getWidth();

			if ( !subItemRect.containsPt( pt ) ) {
				subItemRect.left_ += cm->getItemFromIndex( 0 )->getWidth();
				result ++;


				bool found = false;
				Enumerator<TreeItem::SubItem*>* subItems = item->getSubItems();
				while ( columnItems->hasMoreElements() && subItems->hasMoreElements() ) {
					TreeItem::SubItem* subItem = subItems->nextElement();
					ColumnItem* column = columnItems->nextElement();				
					
					subItemRect.right_ = subItemRect.left_ + column->getWidth();
					
					if ( subItemRect.containsPt( pt ) ) {
						found = true;
						break;
					}
					
					subItemRect.left_ += column->getWidth();
					
					result++;
				}
				
				if ( !found ) {
					result = -1;
				}
			}
		}
		else {
			result = 0;
		}
	}

	return result;
}

TreeItem* TreeListControl::getNextItem( TreeItem* item, bool skipChildren )
{
	TreeModel* tm = getTreeModel();
	TreeItem* result = NULL;

	if ( NULL != item ) {
		TreeItem* nextItem = NULL;		
		
		if ( !item->isLeaf() && item->isExpanded() && !skipChildren ) {
			Enumerator<TreeItem*>* items = item->getChildren();
			//get first item!
			if ( items->hasMoreElements() ) {
				nextItem = items->nextElement();
			}
		}
		else if ( item->getParent() == NULL ) {
			Enumerator<TreeItem*>* items = tm->getRootItems();				
			while ( items->hasMoreElements() ) {
				nextItem = items->nextElement();
				if ( nextItem == item ) {
					//skip one more if possible
					if ( items->hasMoreElements() ) {
						nextItem = items->nextElement();								
					}
					break;
				}
			}
		}
		else {
			nextItem = item->getNextChildNodeItem();
			while ( nextItem == NULL ) {
				TreeItem* parent = item->getParent();
				if ( NULL != parent ) {
					nextItem = getNextItem( parent, true );
				}
				else { 
					nextItem = item;
					break; //use item!
				}
			}
		}
		
		result = nextItem;
	}
	else {
		Enumerator<TreeItem*>* items = tm->getRootItems();
		//get first item!
		if ( items->hasMoreElements() ) {
			result = items->nextElement();
		}
	}
	
	return result;
}

TreeItem* TreeListControl::getPrevItem( TreeItem* item )
{
	TreeItem* result = NULL;

	TreeModel* tm = getTreeModel();

	if ( NULL != item ) {
		TreeItem* prevItem = item->getPrevChildNodeItem();

		if ( NULL == prevItem ) {
			if ( item->getParent() ) {
				prevItem = item->getParent();
			}
			else {
				Enumerator<TreeItem*>* items = tm->getRootItems();
				TreeItem* nextItem = NULL;
				if ( items->hasMoreElements() ) {
					prevItem = items->nextElement();
				}

				while ( items->hasMoreElements() ) {					
					nextItem = items->nextElement();

					if ( nextItem == item ) {						
						break;
					}

					if ( prevItem == item ) { //first element, return the parent
						prevItem = item->getParent();
						break;
					}

					prevItem = nextItem;
				}
			}
		}

		result = prevItem;
	}
	else {
		Enumerator<TreeItem*>* items = tm->getRootItems();
		//get first item!
		if ( items->hasMoreElements() ) {
			result = items->nextElement();
		}
	}

	return result;
}

void TreeListControl::scrollToNextItem( TreeItem* item, bool scrollDown )
{
	Scrollable* scrollable = getScrollable();
	if ( NULL != scrollable ) {
		Rect clientBounds = getClientBounds();
		Rect itemBounds = *item->getBounds();
		
		
		double virtualHeight = scrollable->getVirtualViewHeight();

		if ( scrollDown ) {
			//skip at least one item ahead, so double the item height
			double adjustedBottom = (itemBounds.getHeight()*2 + itemBounds.top_) - scrollable->getVerticalPosition();

			if ( adjustedBottom > clientBounds.bottom_ ) {
				double newPos = item->getBounds()->getHeight() + 
					scrollable->getVerticalPosition();
				if ( (adjustedBottom - clientBounds.bottom_) < (itemBounds.getHeight()*2) ) {
					newPos += ((itemBounds.getHeight()*2) - (adjustedBottom - clientBounds.bottom_));
				}
				
				newPos = minVal<double>( newPos, virtualHeight );
				
				//move the scroll down
				scrollable->setVerticalPosition( newPos );
			}
		}
		else {
			double adjustedTop = (itemBounds.top_ - itemBounds.getHeight()*2 ) - scrollable->getVerticalPosition();

			if ( adjustedTop < clientBounds.top_ ) {
				double newPos = scrollable->getVerticalPosition() -
									item->getBounds()->getHeight();
/*
				adjustedTop = abs(adjustedTop);
				if ( (adjustedTop - clientBounds.top_) < (itemBounds.getHeight()*2) ) {
					newPos += ((itemBounds.getHeight()*2) + (adjustedTop - clientBounds.top_));
				}
*/
				newPos = maxVal<double>( newPos, 0 );

				scrollable->setVerticalPosition( newPos );
			}
		}
	}
}

void TreeListControl::keyDown( KeyboardEvent* e )
{
	CustomControl::keyDown( e );

	switch( e->getVirtualCode() ) {
		case vkReturn : {

			//editCell( clickCell_, Point() );

		}
		break;

		case vkDownArrow : {
			

			TreeItem* item = getSelectedItem();
			TreeItem* prevItem = item;

			item = getNextItem( prevItem );

			if ( (NULL != prevItem) && (!e->hasShiftKey() || !getAllowsMultipleSelection()) ) {
				setSelectedItem( prevItem, false );
			}
			if ( NULL != item ) {
				scrollToNextItem( item, true );
				setSelectedItem( item, true );				
			}			
		}
		break;

		case vkLeftArrow : {
			TreeItem* item = getSelectedItem();	
			if ( NULL != item ) {
				if ( item->isExpanded() ) {
					item->expand( false );
					recalcScrollable();
				}
				else {
					if ( NULL != item->getParent() ) {
						setSelectedItem( item, false );
						setSelectedItem( item->getParent(), true );
					}
				}
			}
		}
		break;

		case vkRightArrow : {
			TreeItem* item = getSelectedItem();	
			if ( NULL != item ) {
				if ( item->isExpanded() ) {
					Enumerator<TreeItem*>* items = item->getChildren();
					//get first item!
					if ( items->hasMoreElements() ) {
						setSelectedItem( item, false );
						setSelectedItem( items->nextElement(), true );
					}
				}
				else {
					item->expand( true );
					recalcScrollable();
				}
			}
		}
		break;

		case vkUpArrow : {
			TreeItem* item = getSelectedItem();
			
			TreeItem* prevItem = item;

			item = getPrevItem( prevItem );

			if ( (!e->hasShiftKey() || !getAllowsMultipleSelection()) && (NULL != prevItem) ) {
				setSelectedItem( prevItem, false );
			}

			if ( NULL != item ) {
				scrollToNextItem( item, false );
				setSelectedItem( item, true );				
			}
		}
		break;
	}
}

void TreeListControl::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );

	finishEditing();

	draggingSelectionRect_ = false;
	Point pt = *event->getPoint();
	draggingSelectedItems_.clear();	

	if ( event->hasLeftButton() ) {
		allowMultipleSelection_ = (event->hasControlKey()  || event->hasShiftKey() );
		//setAllowsMultipleSelection(  );

		if ( allowMultipleSelection_ ) {
			multiSelectionChange( event );
		}
		else {
			singleSelectionChange( event );
		}
	}	
}


bool TreeListControl::hitTest( Rect* rect, TreeItem* item, std::vector<TreeItem*>& hitTestList )
{
	bool result = false;
	TreeItem* foundItem = NULL;

	Rect itemBounds = *item->getBounds();

	if ( ! (displayOptions_ & TreeListControl::tdoShowFullRowSelection) ) {
		ColumnItem* column = header_->getColumnModel()->getItemFromIndex(0);

		if (NULL != column)
		{
			itemBounds.right_ = itemBounds.left_ + column->getWidth();

			if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
				//ColumnItem* column = header_->getColumnModel()->getItemFromIndex(0);
				itemBounds.right_ = itemBounds.left_ + column->getWidth();
			}
			else {
				GraphicsContext* ctx = getContext();
				double w = ctx->getTextWidth( item->getCaption() );
				itemBounds.right_ = itemBounds.right_ + w + getCurrentIndent(item) ;
			}
		}
	}



	Rect intersect = itemBounds.makeIntersection( rect );

	if ( !intersect.isEmpty() && !intersect.isNull() ) {
		hitTestList.push_back( item );
	}

	if ( (false == item->isLeaf()) && (true == item->isExpanded()) ) {
		Enumerator<TreeItem*>* children = item->getChildren();
		while ( true == children->hasMoreElements() ) {
			TreeItem* child = children->nextElement();
			hitTest( rect, child, hitTestList );
		}
	}

	return result;
}

void TreeListControl::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );
	if ( (true == event->hasLeftButton()) && (true == draggingSelectionRect_) ) {

		/**
		!!!!!!!HACK!!!!!!!
		
		We need to put this in the paint code and simply invalidate here!
		
		!!!!!!!HACK!!!!!!!
		*/
		GraphicsContext* context = getContext();
		DrawUIState state;
		state.setActive( true );
		context->drawThemeSelectionRect( &dragSelectionRect_, state );

		Point* pt = event->getPoint();
		dragSelectionRect_.setRect( dragPoint_.x_, dragPoint_.y_, pt->x_, pt->y_ );

		dragSelectionRect_.normalize();

		context->drawThemeSelectionRect( &dragSelectionRect_, state );

		bool needsRepaint = false;

		if ( !draggingSelectedItems_.empty() ) {
			std::vector<TreeItem*>::iterator it = draggingSelectedItems_.begin() ;
			while ( it != draggingSelectedItems_.end() ) {
				(*it)->setSelected( false );
				ItemEvent event( this, ITEM_EVENT_UNSELECTED );
				event.setUserData((void*)(*it));
				ItemSelected.fireEvent( &event );

				std::vector<TreeItem*>::iterator found = std::find( selectedItems_.begin(), selectedItems_.end(), *it ) ;
				if ( found != selectedItems_.end() ) {
					selectedItems_.erase( found );
				}

				it ++;
			}
			needsRepaint = true;
		}

		draggingSelectedItems_.clear();

		Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();
		while ( rootChildren->hasMoreElements() ) {
			TreeItem* rootItem = rootChildren->nextElement();
			hitTest( &dragSelectionRect_, rootItem, draggingSelectedItems_ );
		}

		if ( !draggingSelectedItems_.empty() ) {
			std::vector<TreeItem*>::iterator it = draggingSelectedItems_.begin() ;
			while ( it != draggingSelectedItems_.end() ) {
				if ( false == (*it)->isSelected() ) {
					(*it)->setSelected( true );
					selectedItems_.push_back( *it );
				}
				it ++;
			}
			needsRepaint = true;
		}

		if ( needsRepaint ) {
			repaint();
		}
	}

}

void TreeListControl::mouseUp( MouseEvent* event )
{
	CustomControl::mouseUp( event );
	if ( (true == event->hasLeftButton()) && (true == draggingSelectionRect_) ) {
		GraphicsContext* context = getContext();
		DrawUIState state;
		state.setActive(true);
		context->drawThemeSelectionRect( &dragSelectionRect_, state );

		Point* pt = event->getPoint();
		dragSelectionRect_.setRect( dragPoint_.x_, dragPoint_.y_, pt->x_, pt->y_ );

		dragSelectionRect_.normalize();

		context->drawThemeSelectionRect( &dragSelectionRect_, state );
		context->drawThemeSelectionRect( &dragSelectionRect_, state );
		repaint();
	}
}

void TreeListControl::setImageList( ImageList* imageList )
{
	if ( NULL != imageList_ ) {
		imageList_->release();
	}

	imageList_ = imageList;

	if ( NULL != imageList_ ) {
		imageList_->addRef();

		itemHeight_ = maxVal<double>( itemHeight_, maxVal<double>( imageList_->getImageWidth(), imageList_->getImageHeight() ) );
	}
}

ImageList* TreeListControl::getImageList()
{
	return imageList_;
}

ImageList* TreeListControl::getStateImageList()
{
	return stateImageList_;
}

void TreeListControl::setStateImageList( ImageList* imageList )
{
	if ( NULL != stateImageList_ ) {
		stateImageList_->release();
	}

	stateImageList_ = imageList;

	if ( NULL != stateImageList_ ) {
		stateImageList_->addRef();
	}
}

long TreeListControl::getDisplayOptions()
{
	return displayOptions_;
}

void TreeListControl::setDisplayOptions( const long& displayOptions )
{
	displayOptions_ = displayOptions;

	if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
		header_->setHeight( columnHeight_ );
	}
	else {
		header_->setHeight( 0.0 );
	}

	repaint();
}

TreeItem* TreeListControl::isPtOverItem(Point* point)
{
	TreeItem* result = NULL;
	std::vector<TreeItem*> visibleItems;

	populateVisiblityList( visibleItems );

	std::vector<TreeItem*>::iterator it = visibleItems.begin();
	while ( it != visibleItems.end() ) {
		TreeItem* item = *it;
		if ( item->containsPoint( point ) ) {
			result = item;
			break;
		}
		it ++;
	}

	return result;
}


TreeItem* TreeListControl::getSelectedItem()
{
	TreeItem* result = NULL;

	if ( false == selectedItems_.empty() ) {
		result = selectedItems_[0];
	}

	return result;
}

bool TreeListControl::getAllowLabelEditing()
{
	return allowLabelEditing_;
}

void TreeListControl::setAllowLabelEditing( const bool& allowLabelEditing )
{
	allowLabelEditing_ = allowLabelEditing;
}


void TreeListControl::onColumnWidthChanged( ItemEvent* event )
{
	ColumnItem* item = (ColumnItem*)event->getSource();

	if ( item->getIndex() == 0 ) {
		double width = item->getWidth();
		double minWidth = (itemIndent_ + stateItemIndent_) * 1.5;
		if ( width < minWidth ) {
			item->setWidth( minWidth );
		}
	}


	repaint();
}

void TreeListControl::setAllowsMultipleSelection( const bool& multiSelect )
{
	if ( (false == multiSelect) && (false == selectedItems_.empty() ) ) {

		TreeItem* first = NULL;
		if ( ! selectedItems_.empty() ) {
			first = selectedItems_[0];
		}

		clearSelectedItems();

		if ( NULL != first ) {
			selectedItems_.push_back( first );
			first->setSelected( true );
		}

		repaint();
	}
	allowMultipleSelection_ = multiSelect;
}

void TreeListControl::setSelectedItem( TreeItem* item, const bool& isSelected )
{
	if ( true == allowMultipleSelection_ ) {
		std::vector<TreeItem*>::iterator found = std::find( selectedItems_.begin(), selectedItems_.end(),
																item );
		if ( (true == isSelected) && (found == selectedItems_.end()) ) {
			selectedItems_.push_back( item );
		}
		else if ( found != selectedItems_.end() ) {
			if ( false == isSelected ) {
				selectedItems_.erase( found );
			}
		}
	}
	else {
		if ( true == isSelected ) {
			std::vector<TreeItem*>::iterator found = std::find( selectedItems_.begin(), selectedItems_.end(), item );
			if ( found == selectedItems_.end() ) {
				selectedItems_.push_back( item );
			}
		}
		else {
			clearSelectedItems();
		}
	}

	item->setSelected( isSelected );

	if ( true == isSelected ) {
		ItemEvent event( this, ITEM_EVENT_SELECTED );
		event.setUserData( (void*)item );
		ItemSelected.fireEvent( &event );
	}
	else
	{
		ItemEvent event( this, ITEM_EVENT_UNSELECTED );
		event.setUserData( (void*)item );
		ItemSelected.fireEvent( &event );
	}
}

Enumerator<TreeItem*>* TreeListControl::getSelectedItems()
{
	return selectedItemContainer_.getEnumerator();
}

bool TreeListControl::listVisibleItems( std::vector<TreeItem*>& items, TreeItem* itemToSearch, const double& top, const double& bottom )
{
	bool result = false;
	if ( NULL != itemToSearch ) {

		Rect* bounds = itemToSearch->getBounds();
		if ( bounds->isNull() || bounds->isEmpty() ) {
			bounds->setRect( 1, itemHeight_ * items.size(), getWidth()-1, itemHeight_ * items.size() + itemHeight_ );			
		}
		if ( (bounds->bottom_ >= top) || (bounds->top_ < bottom) ){
			items.push_back( itemToSearch );
			result = true;
			if ( (!itemToSearch->isLeaf()) && (itemToSearch->isExpanded()) ) {
				//check children
				Enumerator<TreeItem*>* children = itemToSearch->getChildren();
				while ( children->hasMoreElements() ) {
					TreeItem* child = children->nextElement();
					if ( false == listVisibleItems( items, child, top, bottom ) ) {
						break;
					}
				}
			}
		}
	}

	return result;
}

void TreeListControl::populateVisiblityList( std::vector<TreeItem*>& items, Rect* bounds )
{
	Enumerator<TreeItem*>* rootItems = treeModel_->getRootItems();
	Rect clientBounds;
	if ( NULL != bounds ) {
		clientBounds = *bounds;
	}
	else {
		clientBounds = getClientBounds();
		
		clientBounds.top_ += header_->getHeight();
		
		Scrollable* scrollable = getScrollable();
		if ( NULL != scrollable ) {
			clientBounds.offset( 0, scrollable->getVerticalPosition() );
		}
	}
	while ( rootItems->hasMoreElements() ) {
		TreeItem* child = rootItems->nextElement();
		if ( false == listVisibleItems( items, child, clientBounds.top_, clientBounds.bottom_ ) ) {
			break;
		}
	}	
}

double TreeListControl::getCurrentIndent( TreeItem* item )
{
	double result = getItemIndent() * item->getLevel();

	result += EXPANDER_SPACER*2;  //scootch over for the expander
	//determine if we have an image list present
	if ( NULL != imageList_ ) {
		result += imageList_->getImageWidth();
	}

	if ( Item::idsNone != item->getState() ) {
		if ( NULL != stateImageList_ ) {
			result += stateImageList_->getImageWidth();
		}
		else {
			result += stateItemIndent_;
		}
	}

	return result;
}

double TreeListControl::getDefaultItemHeight()
{
	double result = itemHeight_;
	if ( NULL != imageList_ ) {
		result = maxVal<double>( result, imageList_->getImageHeight() );
	}

	return result;
}

void TreeListControl::setDefaultItemHeight( const double& defaultItemHeight )
{
	itemHeight_ = defaultItemHeight;
}

Rect TreeListControl::getStateRect( TreeItem* item, const double& indent )
{
	Rect result;

	if ( item->getState() != Item::idsNone ) {
		Rect* itemBounds = item->getBounds();

		result = *itemBounds;

		result.left_ += indent;
		if ( NULL != stateImageList_ ) {
			result.right_ = result.left_ + stateImageList_->getImageWidth();
			result.top_ = itemBounds->top_ + (itemBounds->getHeight()/2.0 - stateImageList_->getImageHeight()/2.0);
			result.bottom_ = result.top_ + stateImageList_->getImageHeight();
		}
		else {
			result.right_ = result.left_ + stateItemIndent_;
			result.top_ = itemBounds->top_ + (itemBounds->getHeight()/2.0 - (minVal<double>(stateItemIndent_,itemHeight_)/2.0));
			result.bottom_ = result.top_ + (minVal<double>(stateItemIndent_,itemHeight_));
		}

		if ( NULL != imageList_ ) {
			if ( NULL != stateImageList_ ) {
				result.offset( -(maxVal<double>( imageList_->getImageWidth(), stateImageList_->getImageWidth() )), 0 );
			}
			else {
				result.offset( -(maxVal<double>( imageList_->getImageWidth(), stateItemIndent_ )), 0 );
			}
		}
		else {
			if ( NULL != stateImageList_ ) {
				result.offset( -(maxVal<double>( stateItemIndent_, stateImageList_->getImageWidth() )), 0 );
			}
			else {
				//result.offset( -stateItemIndent_, 0 );
			}
		}

	}
	return result;
}

void TreeListControl::showHierarchyLines( const bool& show )
{
	if ( true == show ) {
		displayOptions_ |= TreeListControl::tdoShowHierarchyLines;
	}
	else {
		displayOptions_ &= ~TreeListControl::tdoShowHierarchyLines;
	}
	repaint();
}

void TreeListControl::showRowLines( const bool& show )
{
	if ( true == show ) {
		displayOptions_ |= TreeListControl::tdoShowRowLines;
	}
	else {
		displayOptions_ &= ~TreeListControl::tdoShowRowLines;
	}
	repaint();
}

void TreeListControl::showColumnLines( const bool& show )
{
	if ( true == show ) {
		displayOptions_ |= TreeListControl::tdoShowColumnLines;
	}
	else {
		displayOptions_ &= ~TreeListControl::tdoShowColumnLines;
	}

	repaint();
}

void TreeListControl::showFullRowSelection( const bool& show )
{
	if ( true == show ) {
		displayOptions_ |= TreeListControl::tdoShowFullRowSelection;
	}
	else {
		displayOptions_ &= ~TreeListControl::tdoShowFullRowSelection;
	}

	repaint();
}

void TreeListControl::showColumnHeader( const bool& show )
{
	if ( true == show ) {
		header_->setHeight( columnHeight_ );
		displayOptions_ |= TreeListControl::tdoShowColumnHeader;
	}
	else {
		header_->setHeight( 0 );
		displayOptions_ &= ~TreeListControl::tdoShowColumnHeader;
	}

	repaint();
}

ColumnModel* TreeListControl::getColumnModel()
{
	return header_->getColumnModel();
}

double TreeListControl::getColumnWidth( const unsigned long& index )
{
	double result = -1;
	ColumnModel* model = header_->getColumnModel();
	ColumnItem* item = model->getItemFromIndex( index );
	if ( NULL != item ) {
		result = item->getWidth();
	}

	return result;
}

void TreeListControl::setColumnWidth( const unsigned long& index, const double& width )
{
	ColumnModel* model = header_->getColumnModel();
	ColumnItem* item = model->getItemFromIndex( index );
	if ( NULL != item ) {
		item->setWidth( width );
	}
}

bool TreeListControl::listSelectedItems( std::vector<TreeItem*>& items, TreeItem* firstSelectedItem, TreeItem* lastSelectedItem, TreeItem* nextItem, bool& startFound )
{
	bool result = false;

	TreeItem* next = NULL;

	if ( false == startFound ) {
		startFound = (nextItem == firstSelectedItem);
	}

	if ( (true == startFound) && (nextItem != lastSelectedItem) ){
		items.push_back( nextItem );
		result = false;
	}
	else if ( (true == startFound) && (nextItem == lastSelectedItem) ){
		items.push_back( nextItem );
		result = true;
	}

	if ( (false == result) && (false == nextItem->isLeaf()) && (true == nextItem->isExpanded()) ) {
		next = nextItem->getChildren()->nextElement();
		while ( next ) {
			if ( false == startFound ) {
				startFound = (next == firstSelectedItem);
			}

			if ( (true == startFound) && (next != lastSelectedItem) ) {
				items.push_back( next );
				result = false;
			}
			else if ( (true == startFound) && (next == lastSelectedItem) ) {
				result = true;
				items.push_back( next );
				break;
			}

			if ( false == result ) {
				result = listSelectedItems( items, firstSelectedItem, lastSelectedItem, next, startFound );
			}

			next = next->getNextChildNodeItem();
		}
	}


	return result;
}

void TreeListControl::onEditingControlKeyPressed( KeyboardEvent* event ) 
{
	switch ( event->getVirtualCode() ) {
		case vkEscape : {
			cancelEditing();
		}
		break;

		case vkReturn : {
			event->setConsumed( true );
			finishEditing();
		}
		break;

		case vkDownArrow : case vkUpArrow : {
			setFocused(); // this will kill the edit
			
			
			KeyboardEvent* event2 =
				new KeyboardEvent( this, event->getType(),
				event->getRepeatCount(),
				event->getKeyMask(),
				event->getKeyValue(),
				event->getVirtualCode() );
			
			handleEvent( event2 );
			
			event2->free();		
			
			TreeItem* item = getSelectedItem();
			if ( NULL != item ) {
				editItem( item, NULL );
			}
		}
		break;
	}
}

bool TreeListControl::finishEditingFromFocusLoss( Control* lostFocusCtrl, Control* currentFocusedCtrl )
{
	bool result = true;
	Control* parent = currentFocusedCtrl->getParent();
	while ( NULL != parent ) {
		if ( currentEditingControl_ == parent ) {
			//skip function, we don't need to do anything
			//at all!
			result = false; 
			break;
		}
		parent = parent->getParent();
	}

	return result;
}

void TreeListControl::onEditorFocusLost( Event* e ) 
{
	Control* control = (Control*)e->getSource();

	//check to see if we have lost focus because
	//we have clicked on a child control of the 
	//currentEditingControl_
	Control* currentFocused = Control::getCurrentFocusedControl();

	if ( finishEditingFromFocusLoss( control, currentFocused ) ) {
		finishEditing();
	}	
}

void TreeListControl::postFinishedEditing( Event* e ) {		
	Control* editControl = (Control*) e->getUserData();

	remove( editControl );
	removeComponent( editControl );
	editControl->free();
	repaint();		
}

void TreeListControl::cancelEditing() {
	finishEditing( false );
}

void TreeListControl::finishEditing( bool applyEdit ) {
	if ( NULL == currentEditingControl_ ) {
		return;
	}

	if ( applyEdit ) {
		
		TreeItem* item = getSelectedItem();
		finishEditingItem( item, currentEditingControl_ );
		
	}

	EventHandler* ev = getEventHandler( "TreeListControl::postFinishedEditing" );
	if ( NULL == ev ) {
		ev = 
			new GenericEventHandler<TreeListControl>( this, &TreeListControl::postFinishedEditing, "TreeListControl::postFinishedEditing" );
	}

	Event* e = new Event( this );
	e->setUserData( currentEditingControl_ );
	UIToolkit::postEvent( ev, e, false );
	currentEditingControl_ = NULL;
}

void TreeListControl::editItem( TreeItem* item, Point* point ) {
	if ( NULL != currentEditingControl_ ) {
		finishEditing();
	}
	currentEditingControl_ = NULL;
	
	if ( NULL != point ) {
		currentEditColumn_ = hitTestForEditColumn( point );			
	}
	
	Rect bounds = getBoundsForEdit( item, currentEditColumn_ );
	
	if ( currentEditColumn_ != -1 ) {
		Control* editor = createEditor( item, currentEditColumn_ );
		
		if ( NULL != editor ) {			
			editor->setBounds( &bounds );
			EventHandler* ev = getEventHandler( "TreeListControl::onEditorFocusLost" );
			editor->FocusLost += ev;

			ev = getEventHandler( "TreeListControl::onEditingControlKeyPressed" );
			editor->KeyDown.addHandler( ev );
			
			add( editor );

			editor->setVisible( true );
			editor->setFocused();	
			
			currentEditingControl_ = editor;
		}
	}		
}

/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.7  2006/03/26 16:52:10  ddiego
*fixed a bug in the treelist control that was incorrectly
*calculating the virtual height for the control.
*
*Revision 1.4.2.6  2006/03/22 03:18:20  ddiego
*fixed a glitch in scroll vert and horz position values.
*
*Revision 1.4.2.5  2006/03/21 00:57:35  ddiego
*fixed bug in table control - problem was really with casting a
*model to a table model, and having the pointer value not be right. Needed
*to use dynamic_cast() to fix it. Curiously this problem was not flagegd in
*debug at all.
*
*Revision 1.4.2.4  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.4.2.3  2005/09/14 01:50:07  ddiego
*minor adjustment to control for enable setting. and registered
*more proeprty editors.
*
*Revision 1.4.2.2  2005/09/12 03:47:04  ddiego
*more prop editor updates.
*
*Revision 1.4.2.1  2005/08/15 03:10:51  ddiego
*minor updates to vff in out streaming.
*
*Revision 1.4  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.8  2005/07/01 15:47:56  marcelloptr
*minor improvements on a message
*
*Revision 1.3.2.7  2005/03/04 04:41:55  ddiego
*fixed a bug in the tree list control that was not taking into account the tree item text color or text bold.
*
*Revision 1.3.2.6  2005/02/21 16:20:01  ddiego
*minor changes to various things, property editors, and tree list control.
*
*Revision 1.3.2.5  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.4  2005/02/10 04:38:46  augusto_roman
** Fixed rect::makeIntersection routine to correctly compute intersections when rects have common edges
** Fixed black background on image transformations (made background alpha 0)
** Fixed column selection crashing in TreeListControl
*
*Revision 1.3.2.3  2005/01/21 13:45:16  augusto_roman
*Increased TreeListControl display speed for large trees by not trying to draw items that are off the screen. - aroman
*
*Revision 1.3.2.2  2005/01/19 01:36:46  augusto_roman
*Fixed drawing of checked state in TreeListControl [ left out of last commit ]
*
*Revision 1.3.2.1  2005/01/17 22:44:51  augusto_roman
*ErrorStrings - Fixed VCF namespace in VCF_ASSERT
*ItemEvent - Added item unselected event
*TreeListControl:
*- Added handling for sending unselected event
*- Added correct state drawing for checked/unchecked items
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.1  2004/08/21 21:06:52  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/30 17:27:13  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.5  2004/07/16 04:01:46  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.4  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.44  2004/04/03 16:09:31  ddiego
*Found some more merge issues that needing resolving.
*
*Revision 1.43  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.42.2.4  2003/10/10 04:33:01  ddiego
*made the treelist look a bit better
*
*Revision 1.42.2.3  2003/10/09 22:04:08  ddiego
*menu item fix
*
*Revision 1.42.2.2  2003/09/15 02:52:36  ddiego
*miscellaneous changes
*
*Revision 1.42.2.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.42  2003/08/09 02:56:45  ddiego
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
*Revision 1.41.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.41  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.40.2.2  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.40.2.1  2003/03/12 03:13:26  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.40  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.39.2.5  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.39.2.4  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.39.2.3  2002/12/27 23:05:11  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.39.2.2  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.39.2.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.39  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.38.10.5  2002/11/16 20:31:35  ddiego
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
*Revision 1.38.10.4  2002/11/09 05:17:11  ddiego
*changes are for fixing bug [ 634798 ] Property pane not scrolling.
*ignore the inclusion of TreeListControl.cpp in this checkin.
*
*Revision 1.38.10.3  2002/10/18 03:06:36  ddiego
*changes to get the new form dialogs working
*
*Revision 1.38.10.2  2002/10/16 05:39:31  ddiego
*started working on adding support for creating a new form to a project
*
*Revision 1.38.10.1  2002/10/01 20:34:59  ddiego
*borders
*
*Revision 1.38  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.37  2002/03/31 19:54:33  ddiego
*fixed a release bug in the TreeListControl
*made sure that saving the state of a Frame works correctly
*
*Revision 1.36  2002/03/31 18:21:36  ddiego
*fixed memory leak of accelerators in UIToolkit::removeAcceleratorKeysForControl()
*
*Revision 1.35  2002/03/25 03:20:01  ddiego
*fixes a bug in TreeListControl that creates enourmous amounts of provcessing to happen
*if the visible item height is less than the control height - it was always resetting the
*vertical scroll pos and then repainting itself
*
*Revision 1.34  2002/03/22 04:30:18  ddiego
*bug fixes for weird resizing of win32 common controls (it figures) with the
*new code I put in yesterday. Put back the old code and it seems to work OK.
*Sigh...
*
*Revision 1.33  2002/03/20 02:46:54  ddiego
*fixes an issue with with changes to an items state not correctly being reflected in the
*TreeListControl
*Also makes another adjustment to the scroll positioning when collapsing nodes
*
*Revision 1.32  2002/03/19 05:05:02  ddiego
*added some more fixes for scriolling in the TreeListControl to make
*sure that the scroll position is done better
*
*Revision 1.31  2002/03/17 01:16:43  ddiego
*fixes for bug [ 529718 ] treelistcontrol scroll problem
*the virtual height for the scrollbar is now adjusted correctly
*
*Revision 1.30  2002/03/17 00:19:51  ddiego
*added support for selecting multiple items with the shift key
*
*Revision 1.29  2002/03/13 03:09:54  ddiego
*adjusted tree control drawing code when not in full row selection
*addjust buffer overrun when calculating a single line of text for a
*MultilineTextControl
*
*Revision 1.28  2002/03/13 01:26:35  ddiego
*fixes to the TreeListControl
*plus fix for bug [ 529012 ] typecombo crash in the ComboBoxControl. Caused
*by not checking a null pointer in the UIToolkits' methods for getting the
*next and previous control
*
*Revision 1.27  2002/03/09 18:14:37  ddiego
*got rid of the DefaultTreeListItem class - didn't need it anymore.
*Added a setDefaultItemHeight method to the TreeListControl
*
*Revision 1.26  2002/03/05 04:44:14  ddiego
*fixed 525664 TreeList enum bug
*fixed popup menus not appearing right when scrolled to a position beyond 0,0
*fixed multi select problems with double entries
*
*Revision 1.25  2002/03/04 05:11:43  ddiego
*fixes for bug [ 525232 ] TreeListControl no multi select
*
*Revision 1.24  2002/03/03 18:33:44  ddiego
*fixed some display errors in the TreeListControl and added support for ImagLists to
*the HeaderControl
*
*Revision 1.23  2002/03/01 02:58:44  ddiego
*added min/max constraints to the HeaderControl and TreeListControl
*
*Revision 1.22  2002/03/01 01:02:53  ddiego
*fixes bug [ 524006 ] TreeListControl crash
*makes some changes to model classes to utilize event types better
*
*Revision 1.21  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.20  2002/02/21 00:37:38  ddiego
*added three functions for feature request 520661
*these may become deprecated in the future as they are
*for convenience purposes only. Please see:
*	TreeListControl::getColumnWidth()
*	TreeListControl::setColumnWidth()
*	TreeListControl::getColumnModel()
*
*Revision 1.19  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


