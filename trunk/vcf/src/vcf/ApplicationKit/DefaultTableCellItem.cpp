//DefaultTableCellItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTableCellItem.h"
#include "vcf/ApplicationKit/BasicTableItemEditor.h"
#include "vcf/ApplicationKit/TableModel.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;



DefaultTableCellItem::DefaultTableCellItem()
{
	init();
}

DefaultTableCellItem::~DefaultTableCellItem()
{
	//delete basicItemEditor_;
	//basicItemEditor_ = NULL;
}

void DefaultTableCellItem::init()
{
	tag_ = -1;
	imageIndex_ = 0;
	data_ = NULL;
	model_ = NULL;
	owningControl_ = NULL;
	state_ = 0;
	//basicItemEditor_ = new BasicTableItemEditor( this );
}

bool DefaultTableCellItem::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}


void* DefaultTableCellItem::getData()
{
	return data_;
}

void DefaultTableCellItem::setData( void* data )
{
	data_ = data;
}

Model* DefaultTableCellItem::getModel()
{
	return model_;
}

void DefaultTableCellItem::setModel( Model* model )
{
	model_ = model;
}

void DefaultTableCellItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	Font* f = context->getCurrentFont();
	Color oldColor = *f->getColor();

	if ( isFixed() ){
		bool bold = f->getBold();
		f->setBold( true );
		bounds_.inflate( 1, 1 );

		Light3DBorder border;

		border.setInverted( false );

		TableModel* tm = (TableModel*)model_;
		if ( NULL != tm ) {
			TableCellItem* focusedCell = tm->getFocusedCell();

			if ( NULL != focusedCell ) {
				CellID thisCell = tm->getCellIDForItem( this );

				CellID cell = tm->getCellIDForItem( focusedCell );

				if ( (thisCell.column == cell.column) || (thisCell.row == cell.row) ) {
					border.setInverted( true );
				}
			}
		}


		border.paint( &bounds_, context );
		f->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT ) );

		bounds_.inflate( -1, -1 );
		f->setBold( bold );
	}
	else {
		Rect tmp(bounds_);

		if ( isSelected() ){
			context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION ) );
			f->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT ) );
		}
		else {
			f->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT ) );
			context->setColor( &Color(1.0,1.0,1.0) );
		}


		context->rectangle( &tmp );
		context->fillPath();

		if ( this->isFocused() ) {
			DrawUIState state;
			state.setFocused( true );
			context->drawThemeSelectionRect( &tmp, state );
		}

	}

	double x = paintRect->left_ + 5;



	double y = paintRect->top_ + ((paintRect->getHeight() / 2) - (f->getPixelSize()/2));

	Rect textRect( x, y, paintRect->right_, paintRect->bottom_ );
	textRect.inflate( -1, -1 );
	long options = GraphicsContext::tdoCenterVertAlign;
	options |= GraphicsContext::tdoLeftAlign;

	bool bold = f->getBold();
	if ( isFixed() ){
		f->setBold( true );
	}

	context->textBoundedBy( &textRect, caption_, options );

	f->setBold( bold );

	f->setColor( &oldColor );
}

void DefaultTableCellItem::setSelected( const bool& val )
{
	bool changed = (val != isSelected());
	if ( changed ) {
		if ( val ) {
			setState( state_ | TableCellItem::tisSelected );
		}
		else {
			setState( state_ & ~TableCellItem::tisSelected );
		}
	}
}

void DefaultTableCellItem::setFixed( const bool& val )
{
	bool changed = (val != isFixed());
	if ( changed ) {
		if ( val ) {
			setState( state_ | TableCellItem::tcsFixed );
		}
		else {
			setState( state_ & ~TableCellItem::tcsFixed );
		}
	}
}

void DefaultTableCellItem::setReadonly( const bool& val )
{
	bool changed = (val != isReadonly());
	if ( changed ) {
		if ( val ) {
			setState( state_ | TableCellItem::tisReadonly );
		}
		else {
			setState( state_ & ~TableCellItem::tisReadonly );
		}
	}
}

void DefaultTableCellItem::setFocused( const bool& val )
{
	bool changed = (val != isFocused());
	if ( changed ) {
		if ( val ) {
			setState( state_ | TableCellItem::tcsFocused );
		}
		else {
			setState( state_ & ~TableCellItem::tcsFocused );
		}
	}
}

void DefaultTableCellItem::setDropHighlighted( const bool& val )
{
	bool changed = (val != isFocused());
	if ( changed ) {
		if ( val ) {
			setState( state_ | TableCellItem::tcsDropHighlighted );
		}
		else {
			setState( state_ & ~TableCellItem::tcsDropHighlighted );
		}
	}
}

/*
void DefaultTableCellItem::setSelected( const bool& selected )
{
	selected_ = selected;
	if ( true == selected_ ){

	}
	ItemEvent e( this, ITEM_EVENT_SELECTED );
	ItemSelected.fireEvent( &e );
}
*/

TableItemEditor* DefaultTableCellItem::createItemEditor()
{
	return new BasicTableItemEditor( this );
}

/*
bool DefaultTableCellItem::isItemEditable(){
	bool result = false;
	if ( false == isFixedItem_ ) {
		TableItemEditor* editor = getItemEditor();
		if ( NULL != editor ){
			result = editor->isCellEditable();
		}
	}
	return result;
}
*/



String DefaultTableCellItem::getCaption()
{
	return caption_;
}

void DefaultTableCellItem::setCaption( const String& caption )
{
	caption_ = caption;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultTableCellItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultTableCellItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
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
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.18  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.17.2.7  2004/03/12 22:15:44  ddiego
*stuff
*
*Revision 1.17.2.6  2004/03/03 05:02:53  ddiego
*Table editing is working again. The only major missing piece
*as compared to the CGridCtrl, is drag/drop support.
*
*Revision 1.17.2.5  2004/03/01 05:59:19  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.17.2.4  2004/02/27 04:42:35  ddiego
*more table control coding - some minor optimizations in the painting code
*
*Revision 1.17.2.3  2004/02/02 04:38:45  ddiego
*more table codin'
*
*Revision 1.17.2.2  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.17.2.1  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.17  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.2.2  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.16.2.1  2003/08/22 04:39:17  ddiego
*minor improvemtn to Diretory constructor, fixed bug in DefaultTableCellItem
*
*Revision 1.16  2003/08/09 02:56:45  ddiego
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
*Revision 1.15.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.15  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.14.2.1  2003/03/12 03:13:08  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.2  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.13.14.1  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.13  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:52:46  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.12.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.12  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


