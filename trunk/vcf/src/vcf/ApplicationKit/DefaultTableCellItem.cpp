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


DefaultTableCellItem::ColorMap DefaultTableCellItem::tableCellsColorMap;
DefaultTableCellItem::FontMap DefaultTableCellItem::tableCellsFontMap;

static int defaultTableCellItemCount = 0;


DefaultTableCellItem::DefaultTableCellItem():
	tableModel_(NULL),
	color_(NULL),
	font_(NULL)
{
	init();
	defaultTableCellItemCount ++;
}

DefaultTableCellItem::~DefaultTableCellItem()
{
	//delete basicItemEditor_;
	//basicItemEditor_ = NULL;
	--defaultTableCellItemCount;

	if ( 0 == defaultTableCellItemCount ) {
		DefaultTableCellItem::tableCellsColorMap.clear();
		DefaultTableCellItem::tableCellsFontMap.clear();
	}
}

void DefaultTableCellItem::init()
{
	tag_ = -1;
	imageIndex_ = 0;
	data_ = NULL;
	model_ = NULL;
	owningControl_ = NULL;
	itemState_ = 0;
	color_ = NULL;
	font_ = NULL;
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

double DefaultTableCellItem::getTextCellWidth( GraphicsContext* context )
{
	double result = context->getTextWidth( getCaption() ) + (5*2) + 2;
	if ( isFixed() ) {
		result += 2;
	}
	return result;
}

double DefaultTableCellItem::getTextCellHeight( GraphicsContext* context )
{
	return (context->getTextHeight( getCaption() ) + 2) * 1.15;
}

void DefaultTableCellItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	const Font& currentFont = getFont();	
	const Color& currentColor = getColor();
	double fontPixelSize = currentFont.getPixelSize();

	if ( isFixed() ){
		
		Font fixedFont(currentFont);

		fixedFont.setBold( true );
		
		bounds_.right_ += 1;
		bounds_.bottom_ += 1;

		//Light3DBorder border;
		Basic3DBorder border;

		border.setInverted( false );

		//TableModel* tm = dynamic_cast<TableModel*>(model_);
		if ( NULL != tableModel_ ) {
			TableCellItem* focusedCell = tableModel_->getFocusedCell();

			if ( NULL != focusedCell ) {
				CellID thisCell = tableModel_->getCellIDForItem( this );

				CellID cell = tableModel_->getCellIDForItem( focusedCell );

				if ( (thisCell.column == cell.column) || (thisCell.row == cell.row) ) {
					border.setInverted( true );
				}
			}
		}


		border.paint( &bounds_, context );

		bounds_.right_ -= 1;
		bounds_.bottom_ -= 1;

		fontPixelSize = fixedFont.getPixelSize();

		context->setCurrentFont( &fixedFont );
		
	}
	else {
		
		Rect tmp(bounds_);

		if ( isSelected() ){
			context->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION ) );
		}
		else {
			context->setColor( &currentColor );
		}


		context->rectangle( &tmp );
		context->fillPath();

		if ( this->isFocused() ) {
			DrawUIState state;
			state.setFocused( true );
			context->drawThemeSelectionRect( &tmp, state );
		}

		context->setCurrentFont( &currentFont );		
	}

	double x = paintRect->left_ + 5;



	double y = paintRect->top_ + ((paintRect->getHeight() / 2) - (fontPixelSize/2));

	Rect textRect( x, y, paintRect->right_, paintRect->bottom_ );
	textRect.inflate( -1, -1 );
	long options = GraphicsContext::tdoCenterVertAlign;
	if ( isFixed() ){
		options |= GraphicsContext::tdoCenterHorzAlign;
	}
	else {
		options |= GraphicsContext::tdoLeftAlign;
	}

	context->textBoundedBy( &textRect, caption_, options );	
}

void DefaultTableCellItem::setSelected( const bool& val )
{
	bool changed = (val != isSelected());
	if ( changed ) {
		if ( val ) {
			setState( itemState_ | TableCellItem::tisSelected );
		}
		else {
			setState( itemState_ & ~TableCellItem::tisSelected );
		}
	}
}

void DefaultTableCellItem::setFixed( const bool& val )
{
	bool changed = (val != isFixed());
	if ( changed ) {
		if ( val ) {
			setState( itemState_ | TableCellItem::tcsFixed );
		}
		else {
			setState( itemState_ & ~TableCellItem::tcsFixed );
		}
	}
}

void DefaultTableCellItem::setReadonly( const bool& val )
{
	bool changed = (val != isReadonly());
	if ( changed ) {
		if ( val ) {
			setState( itemState_ | TableCellItem::tisReadonly );
		}
		else {
			setState( itemState_ & ~TableCellItem::tisReadonly );
		}
	}
}

void DefaultTableCellItem::setFocused( const bool& val )
{
	bool changed = (val != isFocused());
	if ( changed ) {
		if ( val ) {
			setState( itemState_ | TableCellItem::tcsFocused );
		}
		else {
			setState( itemState_ & ~TableCellItem::tcsFocused );
		}
	}
}

void DefaultTableCellItem::setDropHighlighted( const bool& val )
{
	bool changed = (val != isFocused());
	if ( changed ) {
		if ( val ) {
			setState( itemState_ | TableCellItem::tcsDropHighlighted );
		}
		else {
			setState( itemState_ & ~TableCellItem::tcsDropHighlighted );
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
	Control* control = getControl();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( caption_ );
	}

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

void DefaultTableCellItem::setModel( Model* model )
{
	TableCellItem::setModel( model );
	tableModel_ = dynamic_cast<TableModel*>(model);

	VCF_ASSERT( NULL != tableModel_ );
}

const Color& DefaultTableCellItem::getColor()
{
	if ( DefaultTableCellItem::tableCellsColorMap.empty() ) {		
		Color* color = GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );
		DefaultTableCellItem::tableCellsColorMap [color_->getColorRef32()] = 
			*color;

		ColorMap::iterator found = 
			DefaultTableCellItem::tableCellsColorMap.find( color->getColorRef32() );

		if ( found != DefaultTableCellItem::tableCellsColorMap.end() ) {
			color_ = &found->second;
		}
	}
	else if ( NULL == color_ ) {
		Color* color = GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );

		ColorMap::iterator found = 
			DefaultTableCellItem::tableCellsColorMap.find( color->getColorRef32() );

		if ( found != DefaultTableCellItem::tableCellsColorMap.end() ) {
			color_ = &found->second;
		}
	}

	VCF_ASSERT( NULL != color_ );

	return *color_;
}

void DefaultTableCellItem::setColor( Color* color )
{
	VCF_ASSERT( NULL != color );
	ColorMap::iterator found = 
		DefaultTableCellItem::tableCellsColorMap.find( color->getColorRef32() );

	if ( found != DefaultTableCellItem::tableCellsColorMap.end() ) {
		color_ = &found->second;
	}
	else { //new entry!
		DefaultTableCellItem::tableCellsColorMap [color->getColorRef32()] = *color;

		found = 
		DefaultTableCellItem::tableCellsColorMap.find( color->getColorRef32() );
		if ( found != DefaultTableCellItem::tableCellsColorMap.end() ) {
			color_ = &found->second;
		}
	}
}


String fontToString( Font* font )
{
	String result = "";
	result += font->getName();
	result += (int)font->getPixelSize();
	result += font->getBold();
	result += font->getUnderlined();
	result += font->getStrikeOut();
	result += font->getItalic();
	return result;
}

const Font& DefaultTableCellItem::getFont()
{
	UIMetricsManager* mgr = UIToolkit::getUIMetricsManager();

	if ( DefaultTableCellItem::tableCellsFontMap.empty() ) {
		Font font = mgr->getDefaultFontFor( UIMetricsManager::ftControlFont ); 
		font.setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT ) );

		String key = fontToString(&font);

		DefaultTableCellItem::tableCellsFontMap [key] = 
			font;

		FontMap::iterator found = 
			DefaultTableCellItem::tableCellsFontMap.find( key );

		if ( found != DefaultTableCellItem::tableCellsFontMap.end() ) {
			font_ = &found->second;

			EventHandler* ev = getEventHandler("DefaultTableCellItem::onFontChanged");

			if ( NULL == ev ) {
				ev = new GenericEventHandler<DefaultTableCellItem>(this,&DefaultTableCellItem::onFontChanged,"DefaultTableCellItem::onFontChanged");
			}
			font_->FontChanged += ev;			
		}
	}
	else if ( NULL == font_ ) {
		Font font = mgr->getDefaultFontFor( UIMetricsManager::ftControlFont );
		font.setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT ) );
		String key = fontToString(&font);

		FontMap::iterator found = 
			DefaultTableCellItem::tableCellsFontMap.find( key );

		if ( found != DefaultTableCellItem::tableCellsFontMap.end() ) {
			font_ = &found->second;

			EventHandler* ev = getEventHandler("DefaultTableCellItem::onFontChanged");

			if ( NULL == ev ) {
				ev = new GenericEventHandler<DefaultTableCellItem>(this,&DefaultTableCellItem::onFontChanged,"DefaultTableCellItem::onFontChanged");
			}
			font_->FontChanged += ev;
		}
	}

	VCF_ASSERT( NULL != font_ );

	if ( NULL == font_ ) {
		Dialog::showMessage( "We're fucked" );
	}

	return *font_;
}


void DefaultTableCellItem::setFont( Font* font )
{
	String key = fontToString(font);

	FontMap::iterator found = 
		DefaultTableCellItem::tableCellsFontMap.find( key );

	if ( found != DefaultTableCellItem::tableCellsFontMap.end() ) {
		font_ = &found->second;
	}
	else { //new entry!
		DefaultTableCellItem::tableCellsFontMap [key] = *font;

		found = 
		DefaultTableCellItem::tableCellsFontMap.find( key );
		if ( found != DefaultTableCellItem::tableCellsFontMap.end() ) {
			font_ = &found->second;
		}
	}
}

void DefaultTableCellItem::onFontChanged( Event* e )
{
	Font* font = (Font*)e->getSource();

	FontMap::iterator found = DefaultTableCellItem::tableCellsFontMap.begin();
	while ( found != DefaultTableCellItem::tableCellsFontMap.end() ) {
		if ( font == &found->second ) {			
			String key = fontToString(font);

			DefaultTableCellItem::tableCellsFontMap[key] = *font;

			DefaultTableCellItem::tableCellsFontMap.erase( found );
		}
		found ++;
	}
}

/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.3  2006/03/21 00:57:35  ddiego
*fixed bug in table control - problem was really with casting a
*model to a table model, and having the pointer value not be right. Needed
*to use dynamic_cast() to fix it. Curiously this problem was not flagegd in
*debug at all.
*
*Revision 1.3.2.2  2006/03/05 02:28:04  ddiego
*updated the Item interface and adjusted the other classes accordingly.
*
*Revision 1.3.2.1  2005/09/03 14:03:52  ddiego
*added a package manager to support package info instances, and
*fixed feature request 1278069 - Background color of the TableControl cells.
*
*Revision 1.3  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/02/24 05:45:02  marcelloptr
*fixed positioning of text inside a table item. Now is centered and looks better
*
*Revision 1.2.4.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2005/01/26 20:59:28  ddiego
*some fixes to table control and to teh table item editor interface
*
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


