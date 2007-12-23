//DefaultTabPage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTabPage.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/ApplicationKit/TabModel.h"

using namespace VCF;

DefaultTabPage::DefaultTabPage( Control* component ):
	preferredHeight_(8),
	index_(0),
	pageControl_(NULL)	
{
	tag_ = -1;
	setPageControl( component );
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
	TabModel* tm = (TabModel*) this->getModel();
	VCF_ASSERT( NULL != tm );

	tm->setAsString( index_, name );
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged( &event );
}

String DefaultTabPage::getPageName()
{
	Control* control = getControl();
	TabModel* tm = (TabModel*) getModel();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( tm->getAsString( index_ ) );
	}
	return tm->getAsString( index_ );
}

Control* DefaultTabPage::getPageControl()
{
	return pageControl_;
}

void DefaultTabPage::setPageControl( Control* component )
{
	if ( NULL != pageControl_ ){
		//pageControl_->free();
		pageControl_ = NULL;
	}
	pageControl_ = component;

}

void DefaultTabPage::paint( GraphicsContext* context, Rect* paintRect )
{	
	Control* control = getControl();
	String text = getPageName();

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
	Control* control = getPageControl();
	if ( NULL != control ) {
		result = (uint32)control->getContext()->getTextHeight( "EM" );
	}
	return result;
}



/**
$Id$
*/
