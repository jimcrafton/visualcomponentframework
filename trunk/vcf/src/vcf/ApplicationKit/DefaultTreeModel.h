#ifndef _VCF_DEFAULTTREEMODEL_H__
#define _VCF_DEFAULTTREEMODEL_H__
//DefaultTreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif





#ifndef _VCF_ABSTRACTTREEMODEL_H__
#include "vcf/ApplicationKit/TreeModel.h"
#endif //_VCF_ABSTRACTTREEMODEL_H__



namespace VCF{

#define DEFAULTTREEMODEL_CLASSID		"3126B226-2819-11d4-B53A-00C04F0196DA"

/**
\class DefaultTreeModel DefaultTreeModel.h "vcf/ApplicationKit/DefaultTreeModel.h"
*/
class APPLICATIONKIT_API DefaultTreeModel : public TreeModel {
public:	
	DefaultTreeModel();

	virtual ~DefaultTreeModel();


	virtual void empty();    

	virtual Key insert( const VariantData& value, const Key& parentKey=RootKey );

	virtual void remove( const Key& key );

	virtual VariantData get( const Key& key );

	virtual String getAsString( const Key& key );

	virtual void set( const Key& key, const VariantData& value );

	virtual void setAsString( const Key& key, const String& value );

	virtual void copy( const Key& srcKey, const Key& destKey, bool deepCopy=false );

	virtual void move( const Key& srcKey, const Key& destParentKey );

	virtual bool getChildren(const Key& key, std::vector<Key>& children );

	virtual Key getParent( const Key& key );

	virtual Key getNextSibling( const Key& key );

	virtual Key getPrevSibling( const Key& key );

	virtual Key getFirstChild( const Key& key );

	virtual bool isLeaf( const Key& key );

	virtual uint32 getCount();

	virtual uint32 getChildCount( const Key& key );

protected:

	struct TreeValRef {
		
		TreeValRef(): parent(NULL),nextSibling(NULL),prevSibling(NULL){}
		
		VariantData data;
		TreeModel::Key key;
		
		TreeValRef* parent;
		TreeValRef* nextSibling;
		TreeValRef* prevSibling;
	};


	typedef std::map<TreeModel::Key, TreeValRef> DataMap;
	typedef std::multimap<TreeModel::Key,TreeModel::Key> HierarchyMap;
	typedef std::pair<HierarchyMap::iterator,HierarchyMap::iterator> HierarchyRange;
	typedef HierarchyMap::value_type HierarchyValue;

	DataMap data_;
	HierarchyMap hierarchy_;
	uint32 lastKey_;


	TreeModel::Key removeFromHierarchy( TreeModel::Key key );

	void insertRef( TreeValRef& ref, TreeModel::Key parentKey );
};

};


#endif // _VCF_DEFAULTTREEMODEL_H__

/**
$Id$
*/
