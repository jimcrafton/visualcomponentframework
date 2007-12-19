//DefaultTabModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTabModel.h"


using namespace VCF;



DefaultTabModel::DefaultTabModel()
{
	
}

DefaultTabModel::~DefaultTabModel()
{
	
}


void DefaultTabModel::insertTabPage( const uint32& index, TabPage* page )
{
	TabModelEvent event( this, tmeItemAdded, page );
	TabPageAdded( &event );
	pages_.insert( pages_.begin() + index, page );
	
	CallBack* ev = getCallback( "DefaultTabModel::tabPageChange" );
	if ( NULL == ev ) {
		ev = new ClassProcedure1<ItemEvent*,DefaultTabModel>(this, &DefaultTabModel::tabPageChange, "DefaultTabModel::tabPageChange" );
	}
	page->ItemChanged += ev;
}

void DefaultTabModel::deleteTabPage( TabPage* page )
{
	TabModelEvent event( this, tmeItemRemoved, page );
	TabPageRemoved( &event );
	Array<TabPage*>::iterator found = std::find( pages_.begin(), pages_.end(), page );
	if ( found != pages_.end() ){
		TabPage* page = *found;
		//clean up memory
		page->free();
		pages_.erase( found );
	}
}

void DefaultTabModel::deleteTabPage( const uint32& index )
{
	Array<TabPage*>::iterator found = pages_.begin() + index;
	if ( found != pages_.end() ){
		TabModelEvent event( this, tmeItemRemoved, *found );
		TabPageRemoved( &event );
		TabPage* page = *found;
		//clean up memory
		page->free();
		pages_.erase( found );
	}
}

void DefaultTabModel::empty()
{
	Array<TabPage*>::iterator it = pages_.begin();
	while ( it != pages_.end() ){
		TabPage* page = *it;
		page->free();
		page = NULL;
		it++;
	}
	pages_.clear();

	Model::empty();
}

TabPage* DefaultTabModel::getPageAt( const uint32& index )
{
	TabPage* result = NULL;
	Array<TabPage*>::iterator it = pages_.begin() + index;
	if ( it != pages_.end() ){
		result = *it;
	}
	return result;
}

TabPage* DefaultTabModel::getPageFromPageName( const String& pageName )
{
	TabPage* result = NULL;
	Array<TabPage*>::iterator it = pages_.begin();
	while ( it != pages_.end() ){
		TabPage* page = *it;
		if ( page->getPageName() == pageName ) {			
			result = *it;
			break;
		}
		it ++;
	}
	return result;
}

uint32 DefaultTabModel::getItemIndex( TabPage* item )
{
	Array<TabPage*>::iterator found = std::find ( pages_.begin(), pages_.end(), item );
	if ( found != pages_.end() ) {
		return ( found - pages_.begin() );
	}
	return 0;
}

TabPage* DefaultTabModel::getSelectedPage()
{
	TabPage* result = NULL;
	Array<TabPage*>::iterator it = pages_.begin();
	while ( it != pages_.end() ){
		TabPage* page = *it;
		if ( NULL != page ){
			if ( true == page->isSelected() ){
				result = page;
				break;
			}
		}
		it++;
	}

	VCF_ASSERT( NULL != result || 0 == pages_.size() );

	return result;
}

void DefaultTabModel::setSelectedPage( TabPage* page )
{
	Array<TabPage*>::iterator it = pages_.begin();
	while ( it != pages_.end() ){
		TabPage* aPage = *it;
		if ( NULL != page ){
			aPage->setSelected( false );
		}
		it++;
	}
	page->setSelected( true );
	TabModelEvent event( this, tmeItemSelected, page );
	TabPageSelected( &event );
}

void DefaultTabModel::setSelectedPage( const uint32& index )
{
	Array<TabPage*>::iterator it = pages_.begin() + index;
	if ( it != pages_.end() ){
		TabPage* page = *it;
		setSelectedPage( page );
	}
}

Enumerator<TabPage*>* DefaultTabModel::getPages()
{
	return pages_.getEnumerator();
}

void DefaultTabModel::tabPageChange( ItemEvent* e )
{
	updateAllViews();
}


bool DefaultTabModel::isFirstPage( TabPage* page ) 
{
	bool result = false;
	if ( !pages_.empty() ) {
		if ( pages_.front() == page ) {
			result = true;
		}
	}
	return result;
}

bool DefaultTabModel::isLastPage( TabPage* page )
{
	bool result = false;
	if ( !pages_.empty() ) {
		if ( pages_.back() == page ) {
			result = true;
		}
	}
	return result;
}


TabPage* DefaultTabModel::nextPage( TabPage* page ) 
{
	TabPage* result = NULL;
	
	Array<TabPage*>::iterator found = std::find( pages_.begin(), pages_.end(), page );
	if ( found != pages_.end() ) {
		found ++;
		if ( found != pages_.end() ) {							
			result = *found;
		}
	}
	
	return result;
}

TabPage* DefaultTabModel::previousPage( TabPage* page ) 
{
	TabPage* result = NULL;
	
	Array<TabPage*>::iterator found = std::find( pages_.begin(), pages_.end(), page );
	if ( found != pages_.end() ) {
		found --;
		if ( found >= pages_.begin() ) {
			result = *found;
		}
	}
	
	return result;
}


/**
$Id$
*/
