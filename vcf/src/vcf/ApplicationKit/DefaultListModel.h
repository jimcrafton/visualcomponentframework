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



#ifndef _VCF_SIMPLELISTMODEL_H__
#	include "vcf/ApplicationKit/SimpleListModel.h"
#endif // _VCF_LISTMODEL_H__





namespace VCF{

#define DEFAULTLISTMODEL_CLASSID			"ED88C0A9-26AB-11d4-B539-00C04F0196DA"

/**
\class DefaultListModel DefaultListModel.h "vcf/ApplicationKit/DefaultListModel.h"
*/
class APPLICATIONKIT_API DefaultListModel : public SimpleListModel, public Persistable {
public:

	DefaultListModel();

	virtual ~DefaultListModel();

	virtual bool supportsSubItems() {
		return true;
	}	
	
	virtual VariantData getSubItem( const uint32& index, const uint32& subItemIndex );	

	virtual uint32 getSubItemsCount( const uint32& index );

	virtual bool getSubItems( const uint32& index, std::vector<VariantData>& items );

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream, const MIMEType& type=MIMEType() );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream, const MIMEType& type=MIMEType() );
protected:
	typedef std::multimap<uint32,VariantData> SubItemMap;
	typedef std::pair<SubItemMap::iterator,SubItemMap::iterator> SubItemIteratorPair;
	typedef SubItemMap::value_type SubItemPair;

	virtual bool doInsertSubItem( const uint32& index, const uint32 & subItemIndex, const VariantData& value );	
	virtual bool doRemoveSubItem( const uint32& index, const uint32 & subItemIndex );
	virtual bool doSetSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value );

	SubItemMap subItemData_;
};

};


#endif // _VCF_DEFAULTLISTMODEL_H__

/**
$Id$
*/
