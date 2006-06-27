//DefaultTabPage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTabPage.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;

DefaultTabPage::DefaultTabPage( Control* component ):
	data_(NULL),
	preferredHeight_(8),
	imageIndex_(0),
	component_(NULL)	
{
	tag_ = -1;
	setPageComponent( component );
}

DefaultTabPage::~DefaultTabPage()
{

}

bool DefaultTabPage::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}

uint32 DefaultTabPage::getIndex()
{
	return index_;
}

void DefaultTabPage::setIndex( const uint32& index )
{
	index_ = index;
}

void* DefaultTabPage::getData()
{
	return data_;
}

void DefaultTabPage::setData( void* data )
{
	data_ = data;
}

void DefaultTabPage::setPageName( const String& name )
{
	pageName_ = name;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged.fireEvent( &event );
}

String DefaultTabPage::getPageName()
{
	return pageName_;
}

Control* DefaultTabPage::getPageComponent()
{
	return component_;
}

void DefaultTabPage::setPageComponent( Control* component )
{
	if ( NULL != component_ ){
		//component_->free();
		component_ = NULL;
	}
	component_ = component;

}

bool DefaultTabPage::isSelected()
{
	return selected_;
}

void DefaultTabPage::setSelected( const bool& selected )
{
	selected_ = selected;
	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemSelected.fireEvent( &event );
}

void DefaultTabPage::paint( GraphicsContext* context, Rect* paintRect )
{	
	Control* control = getControl();
	String text = pageName_;
	if ( this->getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		text = System::getCurrentThreadLocale()->translate( pageName_ );
	}

	TabState state;
	state.setEnabled( true );
	state.setPressed( isSelected() );
	state.tabCaption_ = text;

	

	context->drawThemeTab( paintRect, state );

	bounds_.setRect( paintRect->left_, paintRect->top_, paintRect->right_, paintRect->bottom_ );
}

uint32 DefaultTabPage::getPreferredHeight()
{
	uint32 result = preferredHeight_;
	Control* control = getPageComponent();
	if ( NULL != control ) {
		result = (uint32)control->getContext()->getTextHeight( "EM" );
	}
	return result;
}


void DefaultTabPage::setImageIndex( const int32& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultTabPage::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}


/**
$Id$
*/
