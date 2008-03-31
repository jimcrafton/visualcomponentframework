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
	color_(NULL)
{
	tag_ = -1;
	imageIndex_ = 0;
	data_ = NULL;
	model_ = NULL;
	owningControl_ = NULL;
	displayState_ = 0;
	color_ = NULL;

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

bool DefaultTableCellItem::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}


double DefaultTableCellItem::getTextCellWidth()
{
	double result = getFont()->getTextWidth( getCaption() ) + (5*2) + 2;
	if ( isFixed() ) {
		result += 2;
	}
	return result;
}

double DefaultTableCellItem::getTextCellHeight()
{
	return (getFont()->getTextHeight( getCaption() ) + 2) * 1.15;
}

void DefaultTableCellItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	Font& currentFont = *getFont();	
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
		
		if ( this->isFocused() ) {
			border.setInverted( true );
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

	context->textBoundedBy( &textRect, getCaption(), options );	
}

bool DefaultTableCellItem::isFixed()
{
	if ( !id_.isValid() ) {
		return false;
	}

	TableModel* tm = (TableModel*) getModel();	

	return id_.row < tm->getFixedRowsCount() || id_.column < tm->getFixedColumnsCount();
}


void DefaultTableCellItem::setReadonly( const bool& val )
{
	bool changed = (val != isReadonly());
	if ( changed ) {
		if ( val ) {
			setDisplayState( displayState_ | TableCellItem::tisReadonly );
		}
		else {
			setDisplayState( displayState_ & ~TableCellItem::tisReadonly );
		}
	}
}

void DefaultTableCellItem::setFocused( const bool& val )
{
	bool changed = (val != isFocused());
	if ( changed ) {
		if ( val ) {
			setDisplayState( displayState_ | TableCellItem::tcsFocused );
		}
		else {
			setDisplayState( displayState_ & ~TableCellItem::tcsFocused );
		}
	}
}

void DefaultTableCellItem::setDropHighlighted( const bool& val )
{
	bool changed = (val != isFocused());
	if ( changed ) {
		if ( val ) {
			setDisplayState( displayState_ | TableCellItem::tcsDropHighlighted );
		}
		else {
			setDisplayState( displayState_ & ~TableCellItem::tcsDropHighlighted );
		}
	}
}

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
	TableModel* tm = (TableModel*) getModel();
	//Control* control = getControl();
	
	//if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
	//	return System::getCurrentThreadLocale()->translate( tm->getValueAsString( id_.row, id_.column ) );
	//}
	return tm->getValueAsString( id_.row, id_.column );
}

void DefaultTableCellItem::setCaption( const String& caption )
{
	TableModel* tm = (TableModel*) getModel();

	tm->setValueAsString( id_.row, id_.column, caption );
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
/*
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

			CallBack* ev = getCallback("DefaultTableCellItem::onFontChanged");

			if ( NULL == ev ) {
				ev = new ClassProcedure1<Event*,DefaultTableCellItem>(this,&DefaultTableCellItem::onFontChanged,"DefaultTableCellItem::onFontChanged");
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

			CallBack* ev = getCallback("DefaultTableCellItem::onFontChanged");

			if ( NULL == ev ) {
				ev = new ClassProcedure1<Event*,DefaultTableCellItem>(this,&DefaultTableCellItem::onFontChanged,"DefaultTableCellItem::onFontChanged");
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
*/
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
