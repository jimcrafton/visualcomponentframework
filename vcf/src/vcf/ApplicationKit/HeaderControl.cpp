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
	columnModel_(NULL),
	textAlignment_(taTextLeft),
	draggingColumnItem_(NULL),
	pressedColumn_(NULL),
	minColumnWidth_(5)
{
	setColumnModel( new ColumnModel() );
	addComponent( getViewModel() );

	aligment_ = AlignTop;
	setHeight( getPreferredHeight() );
	setTabStop(false);
}

HeaderControl::~HeaderControl()
{
	
}

void HeaderControl::setColumnModel( ColumnModel* model )
{
	columnModel_ = model;

	setViewModel( columnModel_ );
}

ColumnItem* HeaderControl::addColumn( const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new ColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->add( result );

	return result;
}

void HeaderControl::addColumn( ColumnItem* column )
{
	columnModel_->add( column );
}

ColumnItem* HeaderControl::insertColumn( const uint32& index, const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new ColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->insert( index, result );

	return result;
}

void HeaderControl::insertColumn( const uint32& index, ColumnItem* column )
{
	columnModel_->insert( index, column );
}

void HeaderControl::deleteColumn( const uint32& index )
{
	columnModel_->remove( index );
}

String HeaderControl::getColumnName( const uint32& index )
{
	return columnModel_->getAsString( index );
}

void HeaderControl::setColumnName( const uint32& index, const String& columnName )
{
	columnModel_->setAsString( index, columnName, false );	
}

double HeaderControl::getColumnWidth( const uint32& index )
{
//	ColumnItem* item = columnModel_->getItemFromIndex( index );
	return 0;//item->getWidth();
}

void HeaderControl::setColumnWidth( const uint32& index, const double& width )
{
	//ColumnItem* item = columnModel_->getItemFromIndex( index );
	//item->setWidth( width );
	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ColumnWidthChanged( &event );
}

void HeaderControl::setImageList( ImageList* imageList )
{
	this->imageList_ = imageList;
}

ColumnItem* HeaderControl::isPtOverItem(Point* point)
{
	ColumnItem* result = NULL;
/*
	Enumerator<ColumnItem*>* columns = columnModel_->getItems();
	Rect r = getClientBounds();
	r.right_ = r.left_;
	while ( true == columns->hasMoreElements() ) {
		ColumnItem* item = columns->nextElement();
		r.right_ += item->getWidth();
		if ( true == r.containsPt( point ) ) {
			result = item;
			break;
		}
		r.left_ = r.right_;
	}
*/
	return result;
}

void HeaderControl::paint( GraphicsContext * context )
{
	CustomControl::paint( context );

	Rect r = getClientBounds();
	r.right_ = r.left_;

/*
	Enumerator<ColumnItem*>* columns = columnModel_->getItems();
	uint32 colCount = columnModel_->getCount();


	uint32 index = 0;
	while ( columns->hasMoreElements() ) {
		ColumnItem* item = columns->nextElement();
		r.right_ += item->getWidth();
		paintColumn( context, &r, index, item );
		r.left_ = r.right_;
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
	*/
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

/**
$Id$
*/
