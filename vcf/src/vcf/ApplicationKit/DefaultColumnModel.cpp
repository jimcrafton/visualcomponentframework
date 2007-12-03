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

}

/*
void DefaultColumnModel::validate()
{

}
*/

void DefaultColumnModel::saveToStream( OutputStream * stream )
{
/*
	Enumerator<ColumnItem*>* items = this->getItems();
	int32 count = this->getCount();
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
	*/
}

void DefaultColumnModel::loadFromStream( InputStream * stream )
{
	/*
	int32 count = 0;
	stream->read( count );
	for (int i=0;i<count;i++){
		bool isPersistentItem = false;
		stream->read( isPersistentItem );		
	}
	*/
}


/**
$Id$
*/
