//DefaultColumnModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DefaultColumnModel.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultColumnModel.h"


using namespace VCF;



DefaultColumnModel::DefaultColumnModel()
{
	init();
}

DefaultColumnModel::~DefaultColumnModel()
{
	std::vector<ColumnItem*>::iterator it = columnItems_.begin();

	while ( it != columnItems_.end() ) {
		ColumnItem* item = *it;
		delete item;
		item = NULL;
		it ++;
	}

	columnItems_.clear();
}

void DefaultColumnModel::init()
{
	columnContainer_.initContainer( columnItems_ );
}

void DefaultColumnModel::validate()
{

}

void DefaultColumnModel::empty()
{
	std::vector<ColumnItem*>::reverse_iterator it = columnItems_.rbegin();
	ColumnModelEvent event( this, COLUMN_MODEL_ITEM_DELETED );
	while ( it != columnItems_.rend() ) {
		ColumnItem* item = *it;
		event.setColumnItem( item );
		ItemDeleted.fireEvent( &event );
		delete item;
		item = NULL;
		it ++;
	}

	columnItems_.clear();
}

void DefaultColumnModel::deleteItem( ColumnItem* item)
{
	std::vector<ColumnItem*>::iterator found = std::find( columnItems_.begin(), columnItems_.end(), item );
	if ( found != columnItems_.end() ) {

		ColumnModelEvent event( this, COLUMN_MODEL_ITEM_DELETED, item );
		ItemDeleted.fireEvent( &event );

		columnItems_.erase( found );

		delete item;
	}
}

void DefaultColumnModel::deleteItem(const unsigned long & index)
{
	if ( index < columnItems_.size() ) {
		std::vector<ColumnItem*>::iterator found = columnItems_.begin() + index;
		if ( found != columnItems_.end() ) {
			std::vector<ColumnItem*>::iterator it = found+1;
			//hack - this is probably not a good idea
			//the point is to reset all the indices of the
			//items, but this is extremely slow on large data sets
			while ( it != columnItems_.end() ) {
				ColumnItem* item = *it;
				item->setIndex( item->getIndex()-1 );
				it ++;
			}

			ColumnItem* item = *found;
			ColumnModelEvent event( this, COLUMN_MODEL_ITEM_DELETED, item );
			ItemDeleted.fireEvent( &event );
			columnItems_.erase( found );
			delete item;
			item = NULL;
		}
	}
}

void DefaultColumnModel::insertItem(const unsigned long & index, ColumnItem * item)
{
	columnItems_.insert( columnItems_.begin() + index, item );
	item->setIndex( index );
	item->setModel( this );

	ColumnModelEvent event( this, COLUMN_MODEL_ITEM_ADDED, item );
	ItemAdded.fireEvent( &event );
}

void DefaultColumnModel::addItem( ColumnItem* item)
{
	columnItems_.push_back( item );
	item->setIndex( columnItems_.size() - 1 );
	item->setModel( this );
	ColumnModelEvent event( this, COLUMN_MODEL_ITEM_ADDED, item );
	ItemAdded.fireEvent( &event );
}

ColumnItem* DefaultColumnModel::getItemFromIndex( const unsigned long& index )
{
	ColumnItem* result = NULL;
	if ( index < columnItems_.size() ) {
        result = columnItems_[index];
	}
	return result;
}

Enumerator<ColumnItem*>* DefaultColumnModel::getItems()
{
	return columnContainer_.getEnumerator();
}

unsigned long DefaultColumnModel::getCount()
{
	return columnItems_.size();
}

void DefaultColumnModel::saveToStream( OutputStream * stream )
{
	Enumerator<ColumnItem*>* items = this->getItems();
	long count = this->getCount();
	stream->write( count );
	while ( items->hasMoreElements() ){
		ColumnItem* item = items->nextElement();
		if ( NULL != item ){
			Persistable* persistableItem = dynamic_cast<Persistable*>(item);
			stream->write( (bool)(persistableItem != NULL) );
			if ( NULL != persistableItem ){
				stream->write( persistableItem );
			}
			else {
				String caption = item->getCaption();
				stream->write( caption );
			}
		}
	}
}

void DefaultColumnModel::loadFromStream( InputStream * stream )
{
	long count = 0;
	stream->read( count );
	for (int i=0;i<count;i++){
		bool isPersistentItem = false;
		stream->read( isPersistentItem );		
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/05 02:28:04  ddiego
*updated the Item interface and adjusted the other classes accordingly.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.9  2004/04/03 16:09:31  ddiego
*Found some more merge issues that needing resolving.
*
*Revision 1.8  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:13:06  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.6.14.3  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6.14.2  2002/12/27 23:05:00  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6.14.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.6  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5  2002/03/22 04:30:18  ddiego
*bug fixes for weird resizing of win32 common controls (it figures) with the
*new code I put in yesterday. Put back the old code and it seems to work OK.
*Sigh...
*
*Revision 1.4.4.2  2002/04/27 15:52:45  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.4.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.4  2002/02/13 03:32:13  ddiego
*fixed bug [ #516363 ] emtying column model causes exception
*removed some redundant/incorrect code from Win32ListView.cpp
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


