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
	int32 options = GraphicsContext::tdoCenterVertAlign;
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

void DefaultTableCellItem::setImageIndex( const int32& imageIndex )
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
$Id$
*/
