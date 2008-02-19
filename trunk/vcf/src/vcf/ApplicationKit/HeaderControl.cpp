//HeaderControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//HeaderControl.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/HeaderControl.h"
#include "vcf/ApplicationKit/ColumnModel.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;



HeaderControl::HeaderControl():
	CustomControl( false ),
	imageList_(NULL),
	textAlignment_(taTextLeft),
	draggingColumnItem_(NULL),
	pressedColumn_(NULL),
	minColumnWidth_(5),
	controlChangeToModel_(false),
	inCallbackChange_(false)
{
	aligment_ = AlignTop;
	setHeight( getPreferredHeight() );
	setTabStop(false);

	CallBack* cb = 
		new ClassProcedure1<Event*,HeaderControl>(this,&HeaderControl::onColumnAdded, "HeaderControl::onColumnAdded" );

	cb = 
		new ClassProcedure1<Event*,HeaderControl>(this,&HeaderControl::onColumnRemoved, "HeaderControl::onColumnRemoved" );
	
	cb = 
		new ClassProcedure1<Event*,HeaderControl>(this,&HeaderControl::onModelChanged, "HeaderControl::onModelChanged" );


	setColumnModel( new ColumnModel() );
}

HeaderControl::~HeaderControl()
{
	
}

void HeaderControl::modelChanged( Model* oldModel, Model* newModel )
{
	ColumnModel* cm = (ColumnModel*)oldModel;
	if ( NULL != cm ) {
		cm->ItemAdded -= getCallback( "HeaderControl::onColumnAdded" );
		cm->ItemRemoved -= getCallback( "HeaderControl::onColumnRemoved" );
		cm->ModelChanged -= getCallback( "HeaderControl::onModelChanged" );
	}

	cm = (ColumnModel*)newModel;
	if ( NULL != cm ) {
		cm->ItemAdded += getCallback( "HeaderControl::onColumnAdded" );
		cm->ItemRemoved += getCallback( "HeaderControl::onColumnRemoved" );
		cm->ModelChanged += getCallback( "HeaderControl::onModelChanged" );
	}
}

void HeaderControl::setColumnModel( ColumnModel* model )
{
	setViewModel( model );
}

ColumnItem* HeaderControl::addColumn( const String& columnName, const double& width )
{
	ColumnModel* cm = getColumnModel();
	return insertColumn( cm->getCount(), columnName, width );
}

void HeaderControl::addColumn( ColumnItem* column )
{
	//columnModel_->add( column );
}

ColumnItem* HeaderControl::insertColumn( const uint32& index, const String& columnName, const double& width )
{
	ColumnItem* result = NULL;


	ColumnModel* cm = getColumnModel();	
	
	cm->insert( index, columnName );	

	result = this->getColumnItem( index );

	return result;
}

void HeaderControl::insertColumn( const uint32& index, ColumnItem* column )
{
	//columnModel_->insert( index, column );
}

void HeaderControl::deleteColumn( const uint32& index )
{
	getColumnModel()->remove( index );
}



void HeaderControl::setImageList( ImageList* imageList )
{
	this->imageList_ = imageList;
}

ColumnItem* HeaderControl::isPtOverItem(Point* point)
{
	ColumnItem* result = NULL;

	Array<ColumnItem*>::iterator it = columnItems_.begin();

	Rect r = getClientBounds();
	r.right_ = r.left_;	
	while ( it != columnItems_.end() ) {
		ColumnItem* item = *it;
		
		r.right_ += item->getWidth();
		if ( true == r.containsPt( point ) ) {
			result = item;
			break;
		}
		r.left_ = r.right_;

		++it;
	}

	return result;
}

void HeaderControl::paint( GraphicsContext * context )
{
	CustomControl::paint( context );

	Rect r = getClientBounds();
	r.right_ = r.left_;


	Array<ColumnItem*>::iterator it = columnItems_.begin();

	uint32 colCount = columnItems_.size();


	uint32 index = 0;
	while ( it != columnItems_.end() ) {
		ColumnItem* item = *it;
		r.right_ += item->getWidth();
		
		paintColumn( context, &r, index, item );

		r.left_ = r.right_;

		++it;

		index ++;
	}

	if ( colCount > 0 ) {
		if ( r.right_ < getWidth() ) {
			r.right_ = getWidth() + 2;
			ButtonState state;
			state.setPressed( false );
			state.setActive( true );
			state.setEnabled( isEnabled() );
			context->drawThemeHeader( &r, state );
		}
	}
}

double HeaderControl::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtHeaderHeight );
}

double HeaderControl::getPreferredWidth()
{
	return 100;
}

void HeaderControl::setTextAlignment( const TextAlignmentType& textAlignment )
{
	textAlignment_ = textAlignment;
	repaint();
}

void HeaderControl::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );
	pressedColumn_ = NULL;
	ColumnItem* item = isPtOverItem( event->getPoint() );
	if ( NULL != item ) {
		Rect bounds = item->getBounds();
		Point* pt = event->getPoint();
		if ( pt->x_ > (bounds.right_-5) ) {
			draggingColumnItem_ = item;
			keepMouseEvents();
		}
		else {
			pressedColumn_ = item;
		}
	}
	repaint();
}

void HeaderControl::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );

	bool needsResizer = false;


	if ( NULL != draggingColumnItem_ ) {
		Rect bounds = draggingColumnItem_->getBounds();
		double width = maxVal<double>( minColumnWidth_, event->getPoint()->x_ - bounds.left_ );
		draggingColumnItem_->setWidth( width );

		ItemEvent itemEvent( draggingColumnItem_, HeaderControl::COLUMN_ITEM_WIDTHCHANGED );
		handleEvent( &itemEvent );

		repaint();
		needsResizer = true;
	}
	else {
		ColumnItem* item = isPtOverItem( event->getPoint() );
		if ( NULL != item ) {
			Rect bounds = item->getBounds();
			Point* pt = event->getPoint();
			if ( pt->x_ > (bounds.right_-5) ) {
				needsResizer = true;
			}
		}
	}

	if ( true == needsResizer ) {
		setCursorID( Cursor::SCT_SPLIT_VERT );
	}
	else {
		setCursorID( Cursor::SCT_DEFAULT );
	}
}

void HeaderControl::mouseUp( MouseEvent* event )
{
	CustomControl::mouseUp( event );
	if ( NULL != draggingColumnItem_ ) {
		Rect bounds = draggingColumnItem_->getBounds();
		double width = maxVal<double>( minColumnWidth_, event->getPoint()->x_ - bounds.left_ );
		draggingColumnItem_->setWidth( width );

		ItemEvent itemEvent( draggingColumnItem_, HeaderControl::COLUMN_ITEM_WIDTHCHANGED );
		handleEvent( &itemEvent );
		repaint();

		releaseMouseEvents();
	}
	else if ( NULL != pressedColumn_ ) {
		MouseEvent clickEvent( pressedColumn_,
								HeaderControl::COLUMN_ITEM_CLICKED,
								event->getButtonMask(),
								event->getKeyMask(),
								event->getPoint() );

		handleEvent( &clickEvent );
	}
	pressedColumn_ = NULL;
	draggingColumnItem_ = NULL;

	repaint();
}

void HeaderControl::handleEvent( Event* event )
{
	CustomControl::handleEvent( event );
	switch ( event->getType() ) {
		case HeaderControl::COLUMN_ITEM_CLICKED : {
			ColumnItemClicked( (MouseEvent*)event );
		}
		break;

		case HeaderControl::COLUMN_ITEM_WIDTHCHANGED : {
			ColumnWidthChanged( (ItemEvent*)event );
		}
		break;
	}
}

void HeaderControl::paintColumn( GraphicsContext* context, Rect* paintRect, const uint32& index, ColumnItem* item )
{
	int32 drawOptions = GraphicsContext::tdoNone;

	switch ( textAlignment_ ) {
		case taTextLeft : {
			drawOptions |= GraphicsContext::tdoLeftAlign;
		}
		break;

		case taTextCenter : {
			drawOptions |= GraphicsContext::tdoCenterHorzAlign;
		}
		break;

		case taTextRight : {
			drawOptions |= GraphicsContext::tdoRightAlign;
		}
		break;
	}
	drawOptions |= GraphicsContext::tdoCenterVertAlign;

	String itemText = item->getCaption();
	if ( getUseLocaleStrings() ) {
		itemText = System::getCurrentThreadLocale()->translate( itemText );
	}

	ButtonState state;
	state.setPressed( pressedColumn_ == item );
	state.setActive( true );
	state.setEnabled( isEnabled() );
	//state.buttonCaption_ = item->getCaption();
	context->drawThemeHeader( paintRect, state );

	paintRect->inflate( -5, 0 );
	Rect captionRect = *paintRect;
	if ( (NULL != this->imageList_) && (item->getImageIndex() > -1) ) {
		Rect imageRect;
		imageRect = *paintRect;
		imageRect.right_ = imageRect.left_ + imageList_->getImageWidth();

		imageRect.top_ = paintRect->top_ + (paintRect->getHeight()/2.0 - imageList_->getImageHeight()/2.0);
		imageRect.bottom_ = imageRect.top_ + imageList_->getImageHeight();

		imageRect.inflate( -1, -1 );

		imageList_->draw( context, item->getImageIndex(), &imageRect );
		captionRect.left_ = imageRect.right_ + 10;
	}

	

	captionRect.right_ -= 5;

	context->textBoundedBy( &captionRect, itemText, drawOptions );

	paintRect->inflate( 5, 0 );


	item->setBounds( *paintRect );
	if ( item->canPaint() ) {
		item->paint( context, paintRect );
	}
}

bool HeaderControl::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_HEIGHT ) {
		if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtHeaderHeight ) ) {
			strValue = CC_HEADERHEIGHT;
			return true;
		}
	}

	return Control::generatePropertyValue( fullPropertyName, property, value, strValue );
}

double HeaderControl::getItemWidth( ColumnItem* item )
{
	return 85;
}

void HeaderControl::setItemWidth( ColumnItem* item, const double& val )
{

}

TextAlignmentType HeaderControl::getItemTextAlignment( ColumnItem* item )
{
	return taTextLeft;
}

void HeaderControl::setItemTextAlignment( ColumnItem* item, const TextAlignmentType& val )
{

}

ColumnItem* HeaderControl::getColumnItem( const uint32& index )
{
	ColumnItem* result = NULL;

	if ( index < columnItems_.size() ) {
		result = columnItems_[index];
	}

	return result;
}

void HeaderControl::setColumnItem( const uint32& index, ColumnItem* item )
{
	if ( index < columnItems_.size() ) {
		ColumnItem* oldItem = columnItems_[index];
		
		columnItems_[index] = item;
		
		if ( NULL == item->getOwner() ) {
			addComponent( item );
		}

		item->setControl( this );
		item->setModel( getViewModel() );
		item->setIndex( oldItem->getIndex() );

		removeComponent( oldItem );
		oldItem->free();

		repaint();
	}
}

void HeaderControl::onColumnAdded( Event* e )
{
	if ( controlChangeToModel_ ) {
		return;
	}

	inCallbackChange_ = true;
	
	ListModelEvent* lme = (ListModelEvent*)e;


	ColumnItem* item = new ColumnItem();
	item->setControl( this );
	item->setModel( getColumnModel() );
	item->setIndex( lme->index );
	addComponent( item );
	columnItems_.insert( columnItems_.begin() + lme->index, item );


	inCallbackChange_ = false;
}

void HeaderControl::onColumnRemoved( Event* e )
{
	inCallbackChange_ = true;

	ListModelEvent* lme = (ListModelEvent*)e;

	ColumnItem* item = this->getColumnItem( lme->index );

	columnItems_.erase( columnItems_.begin() + lme->index );

	removeComponent( item );

	item->free();

	inCallbackChange_ = false;
}

void HeaderControl::onModelChanged( Event* e )
{

}

/**
$Id$
*/

