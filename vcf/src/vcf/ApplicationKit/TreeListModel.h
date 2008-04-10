#ifndef _VCF_TREELISTMODEL_H__
#define _VCF_TREELISTMODEL_H__
//TreeListModel.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_DEFAULTTREEMODEL_H__
#include "vcf/ApplicationKit/DefaultTreeModel.h"
#endif //_VCF_DEFAULTTREEMODEL_H__



namespace VCF {


class TreeListModel : public DefaultTreeModel {
public:

	TreeListModel(){}

	virtual ~TreeListModel(){}
protected:
	virtual bool doInsertSubItem( const Key& key, const uint32 & subItemIndex, const VariantData& value );

	virtual bool doRemoveSubItem( const Key& key, const uint32 & subItemIndex );

	virtual VariantData getSubItem( const Key& key, const uint32& subItemIndex );

	virtual bool doSetSubItem( const Key& key, const uint32& subItemIndex, const VariantData& value );

	virtual uint32 getSubItemsCount( const Key& key );

	virtual bool getSubItems( const Key& key, std::vector<VariantData>& items );

	typedef std::multimap<TreeModel::Key,VariantData> SubItemMap;
	typedef std::pair<SubItemMap::iterator,SubItemMap::iterator> SubItemIteratorPair;
	typedef SubItemMap::value_type SubItemPair;

	SubItemMap subItemData_;
};


};



#endif //_VCF_TREELISTMODEL_H__

