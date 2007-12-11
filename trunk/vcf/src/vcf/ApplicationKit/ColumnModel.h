#ifndef _VCF_COLUMNMODEL_H__
#define _VCF_COLUMNMODEL_H__
//ColumnModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define COLUMNMODEL_CLASSID		"997ee959-661c-437a-9879-b884f593a864"


#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__



namespace VCF  {


#define COLUMN_MODEL_CONST				1900

#define COLUMN_MODEL_CONTENTS_DELETED		CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 1
#define COLUMN_MODEL_ITEM_CHANGED			CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 2
#define COLUMN_MODEL_ITEM_ADDED				CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 3
#define COLUMN_MODEL_ITEM_DELETED			CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 4

	
/**
\class ColumnModelEvent ColumnModel.h "vcf/ApplicationKit/ColumnModel.h"
*/
class APPLICATIONKIT_API ColumnModelEvent : public ListModelEvent {
public:
	ColumnModelEvent( Object* source ):ListModelEvent(source){}

	ColumnModelEvent( Object* source, const uint32& eventType ):ListModelEvent(source,eventType){}

	ColumnModelEvent( Object* source, VariantData* i ):ListModelEvent(source,i){}

	ColumnModelEvent( Object* source, const uint32& eventType, VariantData* i ):ListModelEvent(source,eventType,i){}

	ColumnModelEvent( const ColumnModelEvent& rhs ):ListModelEvent(rhs) {
		*this = rhs;
	}

	virtual ~ColumnModelEvent(){}


	ColumnModelEvent& operator=( const ColumnModelEvent& rhs ) {
		ListModelEvent::operator =( rhs );
		return *this;
	}

	virtual Object* clone( bool deep=false ) {
		return new ListModelEvent(*this);
	}
};

/**
\class ColumnModel ColumnModel.h "vcf/ApplicationKit/ColumnModel.h"
*The ColumnModel is a model that represent's 0 or more ColumnItems.
*You can add, remove, and insert column items in the model. In addition
*you can get an item by index, or retrieve an Enumerator of all of the
*items the model currently has in it.
*@see Model
*/
class APPLICATIONKIT_API ColumnModel : public ListModel {
public:

	ColumnModel();

	virtual ~ColumnModel(){};


	virtual void empty();

	virtual void add( const VariantData& item );
	virtual void insert( const uint32 & index, const VariantData& item );
    
	virtual void remove( const VariantData& item );
	virtual void removeAtIndex( const uint32 & index );

	virtual VariantData get( const uint32& index );	
	virtual String getAsString( const uint32& index );

	virtual uint32 getIndexOf( const VariantData& item );

	virtual void set( const uint32& index, const VariantData& item );
	virtual void setAsString( const uint32& index, const String& item );

	virtual bool getItems( std::vector<VariantData>& items );	
	virtual Enumerator<VariantData>* getItems();

	virtual bool getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items );

	virtual uint32 getCount();

	virtual bool supportsSubItems() {
		return false;
	}

	virtual VariantData getSubItem( const uint32& index, const uint32& subItemIndex ) {		
		return VariantData::null();
	}

	virtual String getSubItemAsString( const uint32& index, const uint32& subItemIndex ) {
		return String();
	}
protected:
	Array<VariantData> data_;
};


}; //end of namespace VCF


#endif // _VCF_COLUMNMODEL_H__

/**
$Id$
*/
