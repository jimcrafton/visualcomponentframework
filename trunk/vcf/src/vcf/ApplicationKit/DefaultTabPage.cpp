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
	preferredHeight_(8),
	index_(0),
	component_(NULL)	
{
	tag_ = -1;
	setPageComponent( component );
}

DefaultTabPage::~DefaultTabPage()
{

}


uint32 DefaultTabPage::getIndex() const
{
	return index_;
}

void DefaultTabPage::setIndex( const uint32& index )
{
	index_ = index;
}


void DefaultTabPage::setPageName( const String& name )
{
	pageName_ = name;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged( &event );
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



/**
$Id$
*/
