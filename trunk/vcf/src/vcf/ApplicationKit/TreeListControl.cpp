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

	header_->ColumnWidthChanged +=
							new ClassProcedure1<ItemEvent*,TreeListControl>( this,
																	&TreeListControl::onColumnWidthChanged,
																	"TreeListControl::onColumnWidthChanged" );

	setDisplayOptions( TreeListControl::tdoNone );

	setUseColorForBackground( true );

	CallBack* ev = 
			new ClassProcedure1<Event*,TreeListControl>( this, &TreeListControl::onEditorFocusLost, "TreeListControl::onEditorFocusLost" );

	ev = new ClassProcedure1<KeyboardEvent*,TreeListControl>( this, &TreeListControl::onEditingControlKeyPressed, "TreeListControl::onEditingControlKeyPressed" );
}

void TreeListControl::setTreeModel(TreeModel * model)
{
	if ( NULL != treeModel_ ) {
		EventHandler* handler = (EventHandler*)getCallback( "TreeListControl::onModelChanged" );
		if ( NULL != handler ) {
			treeModel_->NodeAdded -= handler;
			treeModel_->NodeRemoved -= handler;
		}
		getViewModel()->removeView( this );
	}

	treeModel_ = model;

	if ( NULL != treeModel_ ) {
		Model* tm = dynamic_cast<Model*>(treeModel_);

		tm->addView( this );

		CallBack* handler = getCallback( "TreeListControl::onModelChanged" );
		if ( NULL == handler ) {
			handler = 
				new ClassProcedure1<TreeModelEvent*,TreeListControl>( this, &TreeListControl::onModelChanged, "TreeListControl::onModelChanged" );
			
			//JC - commented this out - this is unneccesary
			//addEventHandler( "TreeListControl::onModelChanged", handler );
		}

		treeModel_->NodeAdded += handler;
		treeModel_->NodeRemoved += handler;
		
		handler = getCallback( "TreeListControl::onModelEmptied" );
		if ( NULL == handler ) {
			handler = new ClassProcedure1<Event*,TreeListControl>( this, &TreeListControl::onModelEmptied, "TreeListControl::onModelEmptied" );
		}
		tm->ModelChanged += (ModelHandler*)handler;
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
	/*////MVC
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
*/

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
			
			visibleItemsHeight_ += item->getBounds().getHeight();
			it ++;
		}

		scrollable->setVirtualViewHeight( visibleItemsHeight_ );

		if ( (getHeight() > visibleItemsHeight_) && (scrollable->getVerticalPosition() > 0.0) ) {
			scrollable->setVerticalPosition( 0.0 );
		}
		else if ( oldVisibleHeight > visibleItemsHeight_ ) {
			double newPos = minVal<double>( abs((int32)(visibleItemsHeight_ - getHeight()))+1.0, scrollable->getVerticalPosition() );
			
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

	item->setBounds( *paintRect );

	TreeModel* treeModel = getTreeModel();
	ColumnModel* columnModel = header_->getColumnModel();

	double indent = getCurrentIndent( item );

	Rect captionRect = *paintRect;
	captionRect.left_ = paintRect->left_ + indent + itemHeight_;

	if ( columnModel->getCount() > 0 ) {
		/*
		ColumnItem* col = columnModel->getItemFromIndex( 0 );
		if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
			captionRect.right_ = maxVal<double>( captionRect.left_ + 1.0,
												paintRect->left_ + col->getWidth() );
		}
		else {
			captionRect.right_ = captionRect.left_ + context->getTextWidth( item->getCaption() ) + 5;
		}
		*/
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

	if ( Item::idsNone != item->getDisplayState() ) {
		stateNeedsDrawing = true;
	}

	if ( true == stateNeedsDrawing ) {
		paintItemState( item, context, paintRect, (int32)indent );
	}

	if ( true == imageNeedsDrawing ) {
		paintItemImage( item, context, paintRect, (int32)indent );
	}

	if ( false == isALeaf ) {
		paintExpander( item, context, paintRect );
	}

	int32 drawOptions = GraphicsContext::tdoNone;
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

/*		Enumerator<ColumnItem*>* columns =  columnModel->getItems();
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
		*/
	}

}

void TreeListControl::paintSubItem( TreeItem* item, GraphicsContext* context, const uint32& subItemIndex, Rect* paintRect )
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

			int32 drawOptions = GraphicsContext::tdoNone;
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

void TreeListControl::paintItemState( TreeItem* item, GraphicsContext* context, Rect* paintRect, const int32& currentIndent )
{
	Rect stateRect = getStateRect( item, currentIndent );

	stateRect.inflate( -1, -1 );

	if ( NULL != stateImageList_ ) {
		stateImageList_->draw( context, item->getStateImageIndex(), &stateRect );
	}
	else {
		stateRect.inflate( -1, -1 );
		int32 state = item->getDisplayState();

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

void TreeListControl::paintItemImage( TreeItem* item, GraphicsContext* context, Rect* paintRect, const int32& currentIndent )
{
	Rect imageRect;
	imageRect.left_ += currentIndent;
	imageRect.right_ = imageRect.left_ + imageList_->getImageWidth();

	uint32 index = item->getImageIndex();
	if ( (true == item->isExpanded()) && (item->getExpandedImageIndex() < imageList_->getImageCount()) ) {
		index = item->getExpandedImageIndex();
	}

	imageRect.top_ = paintRect->top_ + (paintRect->getHeight()/2.0 - imageList_->getImageHeight()/2.0);
	imageRect.bottom_ = imageRect.top_ + imageList_->getImageHeight();

	if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
		//get the first column width
/*		ColumnItem* item = header_->getColumnModel()->getItemFromIndex(0);
		Rect tmp = *paintRect;
		tmp.left_ += item->getWidth();
		if ( imageRect.right_ > tmp.left_ ) {
			imageRect.right_ = maxVal<double>( imageRect.left_, tmp.left_ );
		}
		*/
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
////MVC	treeModel_->addNodeItem( item, parent );
	item->setControl( this );
	if ( NULL != parent ) {
		parent->expand( true );
	}
	repaint();
}

TreeItem* TreeListControl::addItem( TreeItem* parent, const String& caption, const uint32 imageIndex )
{
	DefaultTreeItem* result = new DefaultTreeItem( caption, this, treeModel_ );
	result->setImageIndex( imageIndex );
	addItem( result, parent );
	return result;
}

TreeItem* TreeListControl::hitTest( Point* pt )
{
	TreeItem* result = NULL;
	/*////MVC
	Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();
	while ( rootChildren->hasMoreElements() ) {
		TreeItem* rootItem = rootChildren->nextElement();
		result = hitTest( pt, rootItem );
		if ( NULL != result ) {
			break;
		}
	}
	*/

	return result;
}

TreeItem* TreeListControl::hitTest( Point* pt, TreeItem* itemToTest )
{
	TreeItem* result = NULL;

	if ( true == itemToTest->containsPoint( pt ) ) {
		if ( ! (displayOptions_ & TreeListControl::tdoShowFullRowSelection) ) {
			if ( displayOptions_ & TreeListControl::tdoShowColumnHeader ) {
/*				ColumnItem* column = header_->getColumnModel()->getItemFromIndex(0);
				Rect tmp = *itemToTest->getBounds();
				tmp.right_ = tmp.left_ + column->getWidth();
				if ( true == tmp.containsPt( pt ) ) {
					result = itemToTest;
				}
				*/
			}
			else {
				GraphicsContext* ctx = getContext();
				double w = ctx->getTextWidth( itemToTest->getCaption() );
				Rect tmp = itemToTest->getBounds();
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

void TreeListControl::setItemIndent( const uint32& itemIndent )
{
	itemIndent_ = itemIndent;
	repaint();
}

bool TreeListControl::multiSelectionChange( MouseEvent* event )
{
	bool result = false;

	TreeItem* foundItem = NULL;
	/* ////MVC
	Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();

	TreeItem* currentlySelectedItem = getSelectedItem();

	while ( rootChildren->hasMoreElements() ) {
		TreeItem* rootItem = rootChildren->nextElement();
		foundItem = hitTest( event->getPoint(), rootItem );
		if ( NULL != foundItem ) {
			Rect expanderRect;

			uint32 level = foundItem->getLevel();
			expanderRect = foundItem->getBounds();
			expanderRect.left_ += (level * itemIndent_);
			expanderRect.right_ = expanderRect.left_ + itemIndent_;

			//currentSelectedItem_ = foundItem;

			if ( true == expanderRect.containsPt( event->getPoint() ) ) {
				foundItem->expand( !foundItem->isExpanded() );
				ItemEvent event( this, ITEM_EVENT_CHANGED );
				ItemExpanded( &event );
			}
			else if ( true == stateHitTest( event->getPoint(), foundItem ) ) {
				int32 state = foundItem->getDisplayState();
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
				ItemStateChangeRequested( &event );
			}
			else if ( (true == event->hasLeftButton()) && (true == event->hasShiftKey()) && NULL!=currentlySelectedItem ) {
				rootChildren->reset();
				clearSelectedItems();

				std::vector<TreeItem*> selectedItems;

				bool startFound = false;
				Rect bounds1 = currentlySelectedItem->getBounds();
				Rect bounds2 = foundItem->getBounds();
				TreeItem* firstItem = currentlySelectedItem;
				TreeItem* lastItem = foundItem;
				if ( bounds2.top_ < bounds1.top_ ) {
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

  */
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
		ItemSelected( &event );
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
		
		uint32 level = item->getLevel();
		expanderRect = item->getBounds();
		expanderRect.left_ += (level * itemIndent_);
		expanderRect.right_ = expanderRect.left_ + itemIndent_;	
		
		if ( !expanderRect.containsPt( event->getPoint() ) &&
				!stateHitTest( event->getPoint(), item ) ) {

			item->expand( !item->isExpanded() );
			ItemEvent event( this, ITEM_EVENT_CHANGED );
			ItemExpanded( &event );
			
			recalcScrollable();
		}
		repaint();
	}
}

Rect TreeListControl::getExpanderRect( TreeItem* item )
{
	Rect result;

	uint32 level = item->getLevel();
	result = item->getBounds();
	result.left_ += (level * itemIndent_);
	result.right_ = result.left_ + itemIndent_;

	return result;
}

bool TreeListControl::singleSelectionChange( MouseEvent* event )
{
	bool result = false;

	TreeItem* foundItem = NULL;
	/*////MVC
	Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();
	TreeItem* prevSelectedItem = getSelectedItem();

	while ( rootChildren->hasMoreElements() ) {
		TreeItem* rootItem = rootChildren->nextElement();
		foundItem = hitTest( event->getPoint(), rootItem );
		if ( NULL != foundItem ) {

			Rect expanderRect;

			uint32 level = foundItem->getLevel();
			expanderRect = foundItem->getBounds();
			expanderRect.left_ += (level * itemIndent_);
			expanderRect.right_ = expanderRect.left_ + itemIndent_;

			//currentSelectedItem_ = foundItem;

			if ( expanderRect.containsPt( event->getPoint() ) ) {
				foundItem->expand( !foundItem->isExpanded() );
				ItemEvent event( this, ITEM_EVENT_CHANGED );
				ItemExpanded( &event );

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
				int32 state = foundItem->getDisplayState();
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
				ItemStateChangeRequested( &event );
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
	*/
	
	return result;
}

Rect TreeListControl::getBoundsForEdit( TreeItem* item, int column )
{
	Rect result;

	if ( column == -1 ) {
		return result;
	}


	ColumnModel* cm = header_->getColumnModel();
/*	Enumerator<ColumnItem*>* columnItems = cm->getItems();

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
	*/

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
			/*
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
			*/
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
			/*////MVC
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
			*/
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
		/*////MVC
		Enumerator<TreeItem*>* items = tm->getRootItems();
		//get first item!
		if ( items->hasMoreElements() ) {
			result = items->nextElement();
		}
		*/
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
				/*////MVC
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
				*/
			}
		}

		result = prevItem;
	}
	else {
		/*////MVC
		Enumerator<TreeItem*>* items = tm->getRootItems();
		//get first item!
		if ( items->hasMoreElements() ) {
			result = items->nextElement();
		}
		*/
	}

	return result;
}

void TreeListControl::scrollToNextItem( TreeItem* item, bool scrollDown )
{
	Scrollable* scrollable = getScrollable();
	if ( NULL != scrollable ) {
		Rect clientBounds = getClientBounds();
		Rect itemBounds = item->getBounds();
		
		
		double virtualHeight = scrollable->getVirtualViewHeight();

		if ( scrollDown ) {
			//skip at least one item ahead, so double the item height
			double adjustedBottom = (itemBounds.getHeight()*2 + itemBounds.top_) - scrollable->getVerticalPosition();

			if ( adjustedBottom > clientBounds.bottom_ ) {
				double newPos = item->getBounds().getHeight() + 
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
									item->getBounds().getHeight();
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

	Rect itemBounds = item->getBounds();

	if ( ! (displayOptions_ & TreeListControl::tdoShowFullRowSelection) ) {
		/*
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
		*/
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
				ItemSelected( &event );

				std::vector<TreeItem*>::iterator found = std::find( selectedItems_.begin(), selectedItems_.end(), *it ) ;
				if ( found != selectedItems_.end() ) {
					selectedItems_.erase( found );
				}

				it ++;
			}
			needsRepaint = true;
		}

		draggingSelectedItems_.clear();

		/*////MVC
		Enumerator<TreeItem*>* rootChildren = treeModel_->getRootItems();
		while ( rootChildren->hasMoreElements() ) {
			TreeItem* rootItem = rootChildren->nextElement();
			hitTest( &dragSelectionRect_, rootItem, draggingSelectedItems_ );
		}
		*/

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

int32 TreeListControl::getDisplayOptions()
{
	return displayOptions_;
}

void TreeListControl::setDisplayOptions( const int32& displayOptions )
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
		ItemSelected( &event );
	}
	else
	{
		ItemEvent event( this, ITEM_EVENT_UNSELECTED );
		event.setUserData( (void*)item );
		ItemSelected( &event );
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

		Rect bounds = itemToSearch->getBounds();
		if ( bounds.isNull() || bounds.isEmpty() ) {
			bounds.setRect( 1, itemHeight_ * items.size(), getWidth()-1, itemHeight_ * items.size() + itemHeight_ );			
		}
		if ( (bounds.bottom_ >= top) || (bounds.top_ < bottom) ){
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
	/*////MVC
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
	*/
}

double TreeListControl::getCurrentIndent( TreeItem* item )
{
	double result = getItemIndent() * item->getLevel();

	result += EXPANDER_SPACER*2;  //scootch over for the expander
	//determine if we have an image list present
	if ( NULL != imageList_ ) {
		result += imageList_->getImageWidth();
	}

	if ( Item::idsNone != item->getDisplayState() ) {
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

	if ( item->getDisplayState() != Item::idsNone ) {
		Rect itemBounds = item->getBounds();

		result = itemBounds;

		result.left_ += indent;
		if ( NULL != stateImageList_ ) {
			result.right_ = result.left_ + stateImageList_->getImageWidth();
			result.top_ = itemBounds.top_ + (itemBounds.getHeight()/2.0 - stateImageList_->getImageHeight()/2.0);
			result.bottom_ = result.top_ + stateImageList_->getImageHeight();
		}
		else {
			result.right_ = result.left_ + stateItemIndent_;
			result.top_ = itemBounds.top_ + (itemBounds.getHeight()/2.0 - (minVal<double>(stateItemIndent_,itemHeight_)/2.0));
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

double TreeListControl::getColumnWidth( const uint32& index )
{
	double result = -1;
	ColumnModel* model = header_->getColumnModel();
/*	ColumnItem* item = model->getItemFromIndex( index );
	if ( NULL != item ) {
		result = item->getWidth();
	}
	*/

	return result;
}

void TreeListControl::setColumnWidth( const uint32& index, const double& width )
{
	ColumnModel* model = header_->getColumnModel();
/*	ColumnItem* item = model->getItemFromIndex( index );
	if ( NULL != item ) {
		item->setWidth( width );
	}
	*/
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

	EventHandler* ev = (EventHandler*)getCallback( "TreeListControl::postFinishedEditing" );
	if ( NULL == ev ) {
		ev = 
			new ClassProcedure1<Event*,TreeListControl>( this, &TreeListControl::postFinishedEditing, "TreeListControl::postFinishedEditing" );
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
			CallBack* ev = getCallback( "TreeListControl::onEditorFocusLost" );
			editor->FocusLost += ev;

			ev = getCallback( "TreeListControl::onEditingControlKeyPressed" );
			editor->KeyDown += ev;
			
			add( editor );

			editor->setVisible( true );
			editor->setFocused();	
			
			currentEditingControl_ = editor;
		}
	}		
}


/**
$Id$
*/
