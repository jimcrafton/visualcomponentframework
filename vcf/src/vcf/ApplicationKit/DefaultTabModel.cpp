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
	container_.initContainer( this->pages_ );
}

DefaultTabModel::~DefaultTabModel()
{
	this->clearTabPages();
}

void DefaultTabModel::addTabPage( TabPage* page )
{
	TabModelEvent event( this, TAB_MODEL_EVENT_ITEM_ADDED, page );
	TabPageAdded.fireEvent( &event );
	pages_.push_back( page );

	EventHandler* ev = getEventHandler( "DefaultTabModel::tabPageChange" );
	if ( NULL == ev ) {
		ev = new ItemEventHandler<DefaultTabModel>(this, &DefaultTabModel::tabPageChange, "DefaultTabModel::tabPageChange" );
	}
	page->addItemChangedHandler( ev );
}

void DefaultTabModel::insertTabPage( const ulong32& index, TabPage* page )
{
	TabModelEvent event( this, TAB_MODEL_EVENT_ITEM_ADDED, page );
	TabPageAdded.fireEvent( &event );
	pages_.insert( pages_.begin() + index, page );
}

void DefaultTabModel::deleteTabPage( TabPage* page )
{
	TabModelEvent event( this, TAB_MODEL_EVENT_ITEM_REMOVED, page );
	TabPageRemoved.fireEvent( &event );
	std::vector<TabPage*>::iterator found = std::find( pages_.begin(), pages_.end(), page );
	if ( found != pages_.end() ){
		TabPage* page = *found;
		//clean up memory
		page->free();
		pages_.erase( found );
	}
}

void DefaultTabModel::deleteTabPage( const ulong32& index )
{
	std::vector<TabPage*>::iterator found = pages_.begin() + index;
	if ( found != pages_.end() ){
		TabModelEvent event( this, TAB_MODEL_EVENT_ITEM_REMOVED, *found );
		TabPageRemoved.fireEvent( &event );
		TabPage* page = *found;
		//clean up memory
		page->free();
		pages_.erase( found );
	}
}

void DefaultTabModel::clearTabPages()
{
	std::vector<TabPage*>::iterator it = pages_.begin();
	while ( it != pages_.end() ){
		TabPage* page = *it;
		delete page;
		page = NULL;
		it++;
	}
	pages_.clear();
}

TabPage* DefaultTabModel::getPageAt( const ulong32& index )
{
	TabPage* result = NULL;
	std::vector<TabPage*>::iterator it = pages_.begin() + index;
	if ( it != pages_.end() ){
		result = *it;
	}
	return result;
}

TabPage* DefaultTabModel::getPageFromPageName( const String& pageName )
{
	TabPage* result = NULL;
	std::vector<TabPage*>::iterator it = pages_.begin();
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

ulong32 DefaultTabModel::getItemIndex( TabPage* item )
{
	std::vector<TabPage*>::iterator found = std::find ( pages_.begin(), pages_.end(), item );
	if ( found != pages_.end() ) {
		return ( found - pages_.begin() );
	}
	return 0;
}

TabPage* DefaultTabModel::getSelectedPage()
{
	TabPage* result = NULL;
	std::vector<TabPage*>::iterator it = pages_.begin();
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
	std::vector<TabPage*>::iterator it = pages_.begin();
	while ( it != pages_.end() ){
		TabPage* aPage = *it;
		if ( NULL != page ){
			aPage->setSelected( false );
		}
		it++;
	}
	page->setSelected( true );
	TabModelEvent event( this, TAB_MODEL_EVENT_ITEM_SELECTED, page );
	TabPageSelected.fireEvent( &event );
}

void DefaultTabModel::setSelectedPage( const ulong32& index )
{
	std::vector<TabPage*>::iterator it = pages_.begin() + index;
	if ( it != pages_.end() ){
		TabPage* page = *it;
		setSelectedPage( page );
	}
}

Enumerator<TabPage*>* DefaultTabModel::getPages()
{
	return this->container_.getEnumerator();
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
	
	std::vector<TabPage*>::iterator found = std::find( pages_.begin(), pages_.end(), page );
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
	
	std::vector<TabPage*>::iterator found = std::find( pages_.begin(), pages_.end(), page );
	if ( found != pages_.end() ) {
		found --;
		if ( found >= pages_.begin() ) {
			result = *found;
		}
	}
	
	return result;
}
/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2005/01/01 20:31:07  ddiego
*made an adjustment to quitting and event loop, and added some changes to the DefaultTabModel.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/19 04:08:52  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.13  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.2.3  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.12.2.2  2004/02/12 14:39:09  marcelloptr
*added member function getItemIndex
*
*Revision 1.12  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.2  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.11.4.1  2003/08/22 16:34:39  ddiego
*fixed a mistake in the tabbed pages modle and item
*
*Revision 1.11  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:13:07  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.9.2.3  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.2.1  2002/12/27 23:05:01  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.8.4.1  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.8  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.6.1  2002/07/26 04:24:29  ddiego
*added more support for properly querying modified document, and removing the
*documents from the doc tab pages, made some changes in TabbedPages to support
*this as well
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.2  2002/04/27 15:52:46  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


