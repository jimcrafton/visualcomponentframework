//HeaderControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//HeaderControl.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/HeaderControl.h"
#include "vcf/ApplicationKit/DefaultColumnModel.h"
#include "vcf/ApplicationKit/DefaultColumnItem.h"
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
	setColumnModel( new DefaultColumnModel() );
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
	result = new DefaultColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->addItem( result );

	return result;
}

void HeaderControl::addColumn( ColumnItem* column )
{
	columnModel_->addItem( column );
}

ColumnItem* HeaderControl::insertColumn( const unsigned long& index, const String& columnName, const double& width )
{
	ColumnItem* result = NULL;
	result = new DefaultColumnItem();
	result->setCaption( columnName );
	result->setWidth( width );
	columnModel_->insertItem( index, result );

	return result;
}

void HeaderControl::insertColumn( const unsigned long& index, ColumnItem* column )
{
	columnModel_->insertItem( index, column );
}

void HeaderControl::deleteColumn( const unsigned long& index )
{
	columnModel_->deleteItem( index );
}

String HeaderControl::getColumnName( const unsigned long& index )
{
	ColumnItem* item = columnModel_->getItemFromIndex( index );
	return item->getCaption();
}

void HeaderControl::setColumnName( const unsigned long& index, const String& columnName )
{
	ColumnItem* item = columnModel_->getItemFromIndex( index );
	item->setCaption( columnName );
}

double HeaderControl::getColumnWidth( const unsigned long& index )
{
	ColumnItem* item = columnModel_->getItemFromIndex( index );
	return item->getWidth();
}

void HeaderControl::setColumnWidth( const unsigned long& index, const double& width )
{
	ColumnItem* item = columnModel_->getItemFromIndex( index );
	item->setWidth( width );
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ColumnWidthChanged.fireEvent( &event );
}

void HeaderControl::setImageList( ImageList* imageList )
{
	this->imageList_ = imageList;
}

ColumnItem* HeaderControl::isPtOverItem(Point* point)
{
	ColumnItem* result = NULL;

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

	return result;
}

void HeaderControl::paint( GraphicsContext * context )
{
	CustomControl::paint( context );

	Rect r = getClientBounds();
	r.right_ = r.left_;


	Enumerator<ColumnItem*>* columns = columnModel_->getItems();
	ulong32 colCount = columnModel_->getCount();


	ulong32 index = 0;
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
		Rect* bounds = item->getBounds();
		Point* pt = event->getPoint();
		if ( pt->x_ > (bounds->right_-5) ) {
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
		Rect* bounds = draggingColumnItem_->getBounds();
		double width = maxVal<double>( minColumnWidth_, event->getPoint()->x_ - bounds->left_ );
		draggingColumnItem_->setWidth( width );

		ItemEvent itemEvent( draggingColumnItem_, HeaderControl::COLUMN_ITEM_WIDTHCHANGED );
		handleEvent( &itemEvent );

		repaint();
		needsResizer = true;
	}
	else {
		ColumnItem* item = isPtOverItem( event->getPoint() );
		if ( NULL != item ) {
			Rect* bounds = item->getBounds();
			Point* pt = event->getPoint();
			if ( pt->x_ > (bounds->right_-5) ) {
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
		Rect* bounds = draggingColumnItem_->getBounds();
		double width = maxVal<double>( minColumnWidth_, event->getPoint()->x_ - bounds->left_ );
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
			ColumnItemClicked.fireEvent( (MouseEvent*)event );
		}
		break;

		case HeaderControl::COLUMN_ITEM_WIDTHCHANGED : {
			ColumnWidthChanged.fireEvent( (ItemEvent*)event );
		}
		break;
	}
}

void HeaderControl::paintColumn( GraphicsContext* context, Rect* paintRect, const ulong32& index, ColumnItem* item )
{
	long drawOptions = GraphicsContext::tdoNone;

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


	item->setBounds( paintRect );
	if ( item->canPaint() ) {
		item->paint( context, paintRect );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.3  2006/03/22 03:18:20  ddiego
*fixed a glitch in scroll vert and horz position values.
*
*Revision 1.2.6.2  2006/03/01 04:34:56  ddiego
*fixed tab display to use themes api.
*
*Revision 1.2.6.1  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.15  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.2.2  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.14.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.14  2003/08/09 02:56:45  ddiego
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
*Revision 1.13.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.13  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.12.2.1  2003/03/12 03:13:13  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.11.2.3  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.11.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11.2.1  2002/12/27 23:05:03  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.10.10.2  2002/11/16 20:31:35  ddiego
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
*Revision 1.10.10.1  2002/09/28 02:37:38  ddiego
*fixed up the radiobox and checkbox, label and header controls to properly
*take advantage of default heights from the UIMetricsManager
*fixed the default height for radioboxes and checkboxes in Win32 so that they are
*10 dialog units high - added the neccessary conversion code from dialog
*units to pixels
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.9  2002/03/03 18:33:44  ddiego
*fixed some display errors in the TreeListControl and added support for ImagLists to
*the HeaderControl
*
*Revision 1.8  2002/03/01 02:58:44  ddiego
*added min/max constraints to the HeaderControl and TreeListControl
*
*Revision 1.7  2002/03/01 02:11:04  ddiego
*added HeaderControl::COLUMN_ITEM_CLICKED event to HeaderControl
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


