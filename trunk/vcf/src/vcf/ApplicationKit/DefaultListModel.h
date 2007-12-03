#ifndef _VCF_DEFAULTLISTMODEL_H__
#define _VCF_DEFAULTLISTMODEL_H__
//DefaultListModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__





namespace VCF{

#define DEFAULTLISTMODEL_CLASSID			"ED88C0A9-26AB-11d4-B539-00C04F0196DA"

/**
\class DefaultListModel DefaultListModel.h "vcf/ApplicationKit/DefaultListModel.h"
*/
class APPLICATIONKIT_API DefaultListModel : public ListModel, public Persistable {
public:

	DefaultListModel();

	virtual ~DefaultListModel();


	virtual void empty();

	virtual void addItem( const VariantData& item );
	virtual void insertItem( const uint32 & index, const VariantData& item );
    
	virtual void deleteItem( const VariantData& item );
	virtual void deleteItemAtIndex( const uint32 & index );

	virtual VariantData getItem( const uint32& index );	
	virtual String getItemAsString( const uint32& index );

	virtual uint32 getItemIndex( const VariantData& item );

	virtual void setItem( const uint32& index, const VariantData& item );
	virtual void setItemAsString( const uint32& index, const String& item );

	virtual bool getItems( std::vector<VariantData>& items );
	virtual bool getItems( const uint32& start, const uint32& end, std::vector<VariantData>& items );
	virtual Enumerator<VariantData>* getItems();

	virtual uint32 getCount();

	virtual bool supportsSubItems();
	virtual VariantData getSubItem( const uint32& index, const uint32& subItemIndex ); 
	virtual String getSubItemAsString( const uint32& index, const uint32& subItemIndex );

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );
protected:
	Array<VariantData> data_;
};

};


#endif // _VCF_DEFAULTLISTMODEL_H__

/**
$Id$
*/
