#ifndef _VCF_TREEMODEL_H__
#define _VCF_TREEMODEL_H__
//TreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class TreeItem;


typedef  uint32 TreeModelKey;




/**
\class TreeModelEvent TreeModel.h "vcf/ApplicationKit/TreeModel.h" 
*/
class APPLICATIONKIT_API TreeModelEvent : public ModelEvent {
public:
	TreeModelEvent( Object* source ):ModelEvent(source),key(-1),parentKey(-1){}

	TreeModelEvent( Object* source, const uint32& eventType ):ModelEvent(source,eventType),key(-1),parentKey(-1){}

	TreeModelEvent( const TreeModelEvent& rhs ):ModelEvent(rhs),key(-1),parentKey(-1) {
		*this = rhs;
	}

	virtual ~TreeModelEvent() {}

	TreeModelEvent& operator= ( const TreeModelEvent& rhs ) {
		ModelEvent::operator =( rhs );
		key = rhs.key;
		parentKey = rhs.parentKey;
		return *this;
	}

	virtual Object* clone( bool deep=false ) {
		return new TreeModelEvent(*this);
	}


	TreeModelKey parentKey;
	TreeModelKey key;
};





/**
TreeModelDelegate
handles the following:
\li onRootNodeChanged
\li onNodeAdded
\li onNodeDeleted
*/
typedef Delegate1<TreeModelEvent*> TreeModelDelegate; 
typedef TreeModelDelegate::ProcedureType TreeModelHandler;



/**
\class TreeModel TreeModel.h "vcf/ApplicationKit/TreeModel.h" 
*/
class APPLICATIONKIT_API TreeModel : public Model {
public:
	
	typedef TreeModelKey Key;
	

	enum {
		RootKey = 0,
		InvalidKey = (uint32)-1
	};


	/**
	@delegate RootNodeChanged
	@event
	*/
	DELEGATE(TreeModelDelegate,RootNodeChanged)

	/**
	@delegate NodeAdded
	@event
	*/
	DELEGATE(TreeModelDelegate,NodeAdded)

	/**
	@delegate NodeRemoved
	@event
	*/
	DELEGATE(TreeModelDelegate,NodeRemoved)


	TreeModel(){}

	virtual ~TreeModel(){};


	
	enum TreeModelEvents {
		TREE_MODEL_CONST = Model::MODEL_LAST_EVENT + 2000,
		ContentsDeleted = CUSTOM_EVENT_TYPES + TREE_MODEL_CONST + 1,
		ItemChanged,
		ItemAdded,
		ItemRemoved,
		ItemMoved,
	};

	/**
	inserts some data at the specified parentKey value. The specified
	key value is the "parent" of the value. The return value is the
	key that's directly associated with the data value.
	*/
	virtual Key insert( const VariantData& value, const Key& parentKey=RootKey ) = 0;

	/**
	removes any data associated with the key and any children as well
	*/
	virtual void remove( const Key& key ) = 0;

	/**
	Returns the variant data for the specified key.
	*/
	virtual VariantData get( const Key& key ) = 0;

	/**
	Returns the value associated with the key as a string.
	*/
	virtual String getAsString( const Key& key ) = 0;

	/**
	Sets the value at the specified key.
	*/
	virtual void set( const Key& key, const VariantData& value ) = 0;

	/**
	Sets the value at the specified key. The string value is converted to 
	a variant.
	*/
	virtual void setAsString( const Key& key, const String& value ) = 0;


	/**
	Copies the value at the source key, and copies (or inserts if need
	be) the value to the destination key. If deepCopy is 
	true then any children associated with the src key are copied as 
	well.
	*/
	virtual void copy( const Key& srcKey, const Key& destKey, bool deepCopy=false ) = 0;

	/**
	Moves the data at src key (removing it) and inserts it at 
	the new parent key. 
	*/
	virtual void move( const Key& srcKey, const Key& destParentKey ) = 0;

	
	/**
	Returns true if any children are found for the specified key.
	Any children will be stored as keys in the passed in vector.
	*/
	virtual bool getChildren(const Key& key, std::vector<Key>& children ) = 0;

	/**
	Get the parent key for the specified key
	*/
	virtual Key getParent( const Key& key ) = 0;

	/**
	Get the next sibling for the specified key. 
	If no sibling is found the return value of the
	key is TreeModel::InvalidKey
	*/
	virtual Key getNextSibling( const Key& key ) = 0;

	virtual Key getPrevSibling( const Key& key ) = 0;

	virtual Key getFirstChild( const Key& key ) = 0;

	/**
	Identifies whether or not the key is a
	"leaf". A "leaf" is a key that has no children.
	*/
	virtual bool isLeaf( const Key& key ) = 0;

	/**
	Returns the number of keys in this model
	*/
	virtual uint32 getCount() = 0;

	/**
	Returns the number of child keys contained
	in the specified key.
	*/
	virtual uint32 getChildCount( const Key& key ) = 0;


	virtual bool supportsSubItems() {
		return false;
	}

	virtual void insertSubItem( const Key& key, const uint32 & subItemIndex, const VariantData& value ) {}
	virtual void removeSubItem( const Key& key, const uint32 & subItemIndex ){}

	virtual VariantData getSubItem( const Key& key, const uint32& subItemIndex ) {		
		return VariantData::null();
	}

	virtual String getSubItemAsString( const Key& key, const uint32& subItemIndex ) {
		return String();
	}

	virtual void setSubItem( const Key& key, const uint32& subItemIndex, const VariantData& value, bool addMissingValues ){}

	virtual void setSubItemAsString( const Key& key, const uint32& subItemIndex, const String& value, bool addMissingValues ){}

	virtual uint32 getSubItemsCount( const Key& key ) {
		return 0;	
	}

	virtual bool getSubItems( const Key& key, std::vector<VariantData>& items ){
		items.clear();
		return false;
	}

	
};


}; //namespace VCF


#endif // _VCF_TREEMODEL_H__

/**
$Id$
*/
